#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

template <class T>
class Allocator {
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
        pointer p = (pointer)::operator new((size_t)(n * sizeof(T)));
        return p;
    }

    void deallocate(pointer p, size_type n) {
        ::operator delete(p);
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