#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cstdlib>

template <class T>
class Allocator {
private:
    enum {ALIGN = 8};
    enum {MAX_BYTES = 256};
    enum {NFREELEISTS = MAX_BYTES / ALIGN};

    char* start_free = 0;
    char* end_free = 0;
    size_t heap_size = 0;

    union node {
        union node* free_list_link;
        char client_data[1];
    };

    node* volatile free_list[NFREELEISTS] = 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };

    static size_t freelist_index(size_t bytes) {
        return (((bytes)+ALIGN - 1) / ALIGN - 1);
    }

    static size_t ROUND_UP(size_t bytes) {
        return (((bytes)+ALIGN - 1) & ~(ALIGN - 1));
    }

    char* chunk_alloc(size_t size, int& nobjs) {
        char* result;
        size_t total_bytes = size * nobjs;
        size_t bytes_left = end_free - start_free;
        
        if (bytes_left >= total_bytes) {
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else if (bytes_left >= size) {
            nobjs = bytes_left / size;
            total_bytes = size * nobjs;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else {
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
            if (bytes_left > 0) {
                node* volatile* my_free_list = free_list + freelist_index(bytes_left);
                ((node*)start_free)->free_list_link = *my_free_list;
                *my_free_list = (node*)start_free;
            }
            start_free = (char*)malloc(bytes_to_get);
            if (start_free == 0) {
                // no enough space
            }
            heap_size + -bytes_to_get;
            end_free = start_free + bytes_to_get;
            return (chunk_alloc(size, nobjs));
        }
    }

    void* refill(size_t n) {
        int nobjs = 20;
        char* chunk = chunk_alloc(n, nobjs);
        node* volatile* my_free_list;
        node* result;
        node* current_node, * next_node;
        int i;
        if (nobjs == 1) return chunk;
        my_free_list = this->free_list + freelist_index(n);
        result = (node*)chunk;
        *my_free_list = next_node = (node*)(chunk + n);
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
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <class U>
    struct rebind {
        typedef Allocator<U> other;
    };

    Allocator() throw() {};
    Allocator(const Allocator& other) throw() {};
    template <class U> Allocator(const Allocator<U>& other) throw() {};

    ~Allocator() {};


    pointer address(reference x) const {
        return &x;
    }
    const_pointer address(const_reference x) const {
        return (const_pointer)&x;
    }

    pointer allocate(size_type n, const void* hint = 0) {
        size_type required = n * sizeof(T);
        node* volatile* my_free_list;
        node* result;
        if (required > MAX_BYTES) {
            pointer p = (pointer)malloc(required);
            return p;
        }
        my_free_list = this->free_list + freelist_index(required);
        result = *my_free_list;
        if (result == 0) {
            void* r = refill(ROUND_UP(required));
            return (pointer)r;
        }
        *my_free_list = result->free_list_link;
        return (pointer)result;
    }

    void deallocate(pointer p, size_type n) {

        size_t required = n * sizeof(T);
        node* q = (node*)p;
        node* volatile* my_free_list;
        if (required > (size_t)MAX_BYTES) {
            free(p);
            return;
        }
        my_free_list = free_list + freelist_index(required);
        q->free_list_link = *my_free_list;
        *my_free_list = q;
    }

    size_type max_size() const throw() {
        return size_type(UINT_MAX / sizeof(T));
    }

    void construct(pointer p, const_reference val) {
        *p = val;
    }

    void destroy(pointer p) {
        p->~T();
    }
};

#endif