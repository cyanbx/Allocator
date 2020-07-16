#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cstdlib>

template <class T>
class Allocator {
private:
    // align each memory piece to the multiple of ALIGN
    enum {ALIGN = 8};

    // maximum size of memory allocated by free list, use malloc directly for larger piece of memory
    enum {MAX_BYTES = 4096};
    
    // number of lists in the free_list
    enum {NFREELEISTS = MAX_BYTES / ALIGN};

    // the start and end points of the pool
    static char* start_free;
    static char* end_free;

    // present size of the pool
    static size_t heap_size;

    // node in the free_list with free_list_link pointing to next node and client_data pointing to the memory available
    union node {
        union node* free_list_link;
        char client_data[1];
    };

    // set of free lists
    static node* free_list[NFREELEISTS];

    // find the index in free_list according to the required size
    static size_t freelist_index(size_t bytes) {
        return (((bytes)+ALIGN - 1) / ALIGN - 1);
    }

    // do aligning
    static size_t ROUND_UP(size_t bytes) {
        return (((bytes)+ALIGN - 1) & ~(ALIGN - 1));
    }

    // called by refill, allocate memory from the pool to the free_list, use malloc to get
    // memory from system when out of memory
    static char* chunk_alloc(size_t size, int& nobjs) {
        char* result;
        size_t total_bytes = size * nobjs;
        size_t bytes_left = end_free - start_free;

        // there is enough memory for refilling and do allocation directly
        if (bytes_left >= total_bytes) {
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        // not enough for refilling but still enough for allocation
        // provide memory for allocation and use the rest to refill the free list
        else if (bytes_left >= size) {
            nobjs = bytes_left / size;
            total_bytes = size * nobjs;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        // the pool is out of memory, call malloc to add new memory to the pool 
        else {
            size_t bytes_to_get = 20 * total_bytes + ROUND_UP(heap_size >> 4);
            if (bytes_left > 0) {
                node* volatile* my_free_list = free_list + freelist_index(bytes_left);
                ((node*)start_free)->free_list_link = *my_free_list;
                *my_free_list = (node*)start_free;
            }
            start_free = (char*)malloc(bytes_to_get);

            // system is out of memory and malloc doesn't work
            // try to find memory in free lists of other sizes
            if (start_free == 0) {
                size_t i;
				node* volatile* my_free_list;
				node* temp;
				for (i = size; i < MAX_BYTES; i += ALIGN) {
					my_free_list = free_list + freelist_index(i);
					temp = *my_free_list;
					if (NULL != temp) {
						*my_free_list = temp->free_list_link;
						start_free = (char*)temp;
						end_free = start_free + i;
						return chunk_alloc(size, nobjs);

					}
				}
                // no more memory anywhere
				end_free = NULL;
            }
            heap_size += bytes_to_get;  
            end_free = start_free + bytes_to_get;
            return (chunk_alloc(size, nobjs));
        }
    }

    // distribute memory from the pool to the free lists
    static void* refill(size_t n) {
        // nobjs is the default number of newly refilled node
        // chunk_alloc will reduce this number if there's not enough memory in the pool
        int nobjs = 50;

        // call chunk_alloc to get memory from the pool
        char* chunk = chunk_alloc(n, nobjs);
        node* volatile* my_free_list;
        node* result;
        node* current_node, * next_node;
        int i;
        // the pool can only provide memory for 1 node, then this part of memory will be used for allocation
        if (nobjs == 1) return chunk;
        my_free_list = free_list + freelist_index(n);
        result = (node*)chunk;
        *my_free_list = next_node = (node*)(chunk + n);
        // adhere the nodes to the free lists
        for (i = 1; ; i++) {
            current_node = next_node;
            next_node = (node*)((char*)next_node + n);
            if (nobjs - 1 == i) {
                current_node->free_list_link = 0;
                break;
            }
            else {
                current_node->free_list_link = next_node;
            }
        }
        return (result);
    }

public:
    // define member types
    typedef void _Not_user_specialized;
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;

    template <class U>
    struct rebind {
        typedef Allocator<U> other;
    };

    // creates a new allocator instance
    Allocator() noexcept {};
    Allocator(const Allocator& other) noexcept {};
    template <class U> Allocator(const Allocator<U>& other) noexcept {};

    // dtor
    ~Allocator() {};

    // returns the address of a certain element;
    pointer address(reference x) const noexcept {
        return &x;
    }
    const_pointer address(const_reference x) const noexcept {
        return (const_pointer)&x;
    }

    // allocate memory with size of n * sizeof(T), which is uninitialized
    pointer allocate(size_type n, const void* hint = 0) {
        size_type required = n * sizeof(T);

        // use malloc directly for large piece of memory
        if (required > MAX_BYTES) {
            pointer p = (pointer)malloc(required);
            return p;
        }
        
        node* volatile* my_free_list;
        node* result;
        // find the list of fitable size
        my_free_list = this->free_list + freelist_index(required);
        // get the first node from the free list
        result = *my_free_list;
        // free list is out of memory, use memory in the pool to do refilling
        if (result == 0) {
            void* r = refill(ROUND_UP(required));
            return (pointer)r;
        }
        *my_free_list = result->free_list_link;
        return (pointer)result;
    }

    // deallocate the memory allocated before pointed by p
    void deallocate(pointer p, size_type n) {

        size_t required = n * sizeof(T);
        // free large chunk of memory
        if (required > (size_t)MAX_BYTES) {
            free(p);
            return;
        } 
        node* q = (node*)p;
        node* volatile* my_free_list;
        // move the piece of memory back to the free list
        my_free_list = free_list + freelist_index(required);
        q->free_list_link = *my_free_list;
        *my_free_list = q;
    }

    // deallocate the memory in use and allocate a new chunk of memory, not necessary
    pointer reallocate(pointer p, size_type originalSize, size_type newSize) {
        
        // call system function realloc directly for large chunk of memory
        if (originalSize > MAX_BYTES) {
            pointer new_p = (pointer)realloc(p, newSize);
            return new_p;
        }
        // deallocate the original memory and allocate a new piece
        else {
            deallocate(p, originalSize);

            return allocate(newSize);
        }
    }

    // return the max memory size available
    size_type max_size() const noexcept {
        return size_type(UINT_MAX / sizeof(T));
    }

    // constructs an object in allocated storage
    void construct(pointer p, const_reference val) {
        *p = val;
    }

    // destructs an object in allocated storage
    void destroy(pointer p) {
        p->~T();
    }

};

// initialize the static variables
template <class T>
char* Allocator<T>::start_free = 0;

template <class T>
char* Allocator<T>::end_free = 0;

template <class T>
size_t Allocator<T>::heap_size = 0;

template <class T>
typename Allocator<T>::node* Allocator<T>::free_list[Allocator<T>::NFREELEISTS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

#endif