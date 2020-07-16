#ifndef SALLOCATOR_H_
#define SALLOCATOR_H_

template <class T>
class sAllocator {
public:
    // define member types
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    template <class U>
    struct rebind {
        typedef sAllocator<U> other;
    };

    // creates a new allocator instance
    sAllocator() throw() {};
    sAllocator(const sAllocator& other) throw() {};
    template <class U> sAllocator(const sAllocator<U>& other) throw() {};

    // dtor
    ~sAllocator() {};

    // returns the address of a certain element;
    pointer address(reference x) const {
        return &x;
    }
    const_pointer address(const_reference x) const {
        return (const_pointer)&x;
    }

    // allocate memory with size of n * sizeof(T), which is uninitialized
    pointer allocate(size_type n, const void* hint = 0) {
        pointer p = (pointer)::operator new((size_t)(n * sizeof(T)));
        return p;
    }

    // deallocate the memory allocated before pointed by p
    void deallocate(pointer p, size_type n) {
        ::operator delete(p);
    }

    // return the max memory size available
    size_type max_size() const throw() {
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

#endif