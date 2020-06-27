#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_
#include <cstdlib>


template <class T>
class Allocator {
private:
    // 空间大小对齐到64位
    enum {ALIGN = 64};
    // 最大链表空间1024byte，1024以上直接malloc，1024以下调用链表空间
    enum {MAX_BYTES = 1024};
    // 链表个数
    enum {NFREELEISTS = MAX_BYTES / ALIGN};

    // 记录内存池空间起始和末尾
    char* start_free = 0;
    char* end_free = 0;
    size_t heap_size = 0;

    // free_list的元素，free_list_link指向相同大小的下一个node，client_data为这一个可用块的位置
    union node {
        union node* free_list_link;
        char client_data[1];
    };

    // 不同大小的free_list链表的首地址
    node* volatile free_list[NFREELEISTS] = 
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // 根据需求空间的大小找到free_list中对应的下标
    static size_t freelist_index(size_t bytes) {
        return (((bytes)+ALIGN - 1) / ALIGN - 1);
    }

    // 把空间大小对齐到8的倍数
    static size_t ROUND_UP(size_t bytes) {
        return (((bytes)+ALIGN - 1) & ~(ALIGN - 1));
    }

    // 被refill调用，从内存池分配内存，若不够则从系统内存申请
    char* chunk_alloc(size_t size, int& nobjs) {
        char* result;
        size_t total_bytes = size * nobjs;
        size_t bytes_left = end_free - start_free;
        
        // 内存池足够满足refill的需要，直接分
        if (bytes_left >= total_bytes) {
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        // 内存池不够refill的需要了，但仍然能满足本次allocate的需要，先满足allocate，然后把内存池剩下的分给free_list
        else if (bytes_left >= size) {
            nobjs = bytes_left / size;
            total_bytes = size * nobjs;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        //内存池剩余空间连一块内存都无法提供
        else {
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
            if (bytes_left > 0) {//将内存池中剩余的内存分配给合适的free_list
                node* volatile* my_free_list = free_list + freelist_index(bytes_left);
                ((node*)start_free)->free_list_link = *my_free_list;
                *my_free_list = (node*)start_free;
            }
            //向Heap申请内存
            start_free = (char*)malloc(bytes_to_get);
            if (start_free == NULL) {
                //heap空间不足，malloc失败
                //试着搜寻一下freelist中"尚有未用但足够大的内存块"
                for(size_t i = size; i < MAX_BYTES; i += ALIGN){
                    node *volatile *my_free_list = free_list + freelist_index(i);
                    node *temp = *my_free_list;
                    if (temp != NULL) {
						*my_free_list = temp->free_list_link;
						start_free = (char*)temp;
						end_free = start_free + i;
						//递归调用，调整nobjs
						return chunk_alloc(size, nobjs);
					}
                }
                //内存完全分配不出来
                end_free = NULL;
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;

            //递归调用，调整nobjs
            return (chunk_alloc(size, nobjs));
        }
    }

    // 把内存从内存池分给free_list
    void* refill(size_t n) {
        // 默认给当前大小的free_list新分配20个node，然后让chunk给分配，如果
        // 没那么多chunk会减少分配node的数量，见chunk_alloc
        int nobjs = 20;
        char* chunk = chunk_alloc(n, nobjs);
        node* volatile* my_free_list;
        node* result;
        node* current_node, * next_node;
        int i;
        // 只能从内存池分配一个node了，那就把这个node供给allocate
        if (nobjs == 1) return chunk;
        my_free_list = this->free_list + freelist_index(n);
        result = (node*)chunk;
        *my_free_list = next_node = (node*)(chunk + n);
        // 把内存挂到free_list上
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
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

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
        // 比free_list里面的最大byte数大，直接malloc
        if (required > MAX_BYTES) {
            pointer p = (pointer)malloc(required);
            return p;
        }
        // 找到当前大小的free_list
        my_free_list = this->free_list + freelist_index(required);
        // 从free_list里面调一块
        result = *my_free_list;
        // free_list不够，从内存池里多调一些出来
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
        // 大内存直接free
        if (required > (size_t)MAX_BYTES) {
            free(p);
            return;
        }
        // 送回free_list
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