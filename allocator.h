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

    tmplate <class U>
    struct rebind {
        typedef Allocator<U> other;
    }

    Allocator() throw();
    Allocator(const Allocator& other) throw();
    template <class U> Allocator(const Allocator<U>& other) throw();

    ~Allocator();

    pointer address(reference x) const;
    const_pointer address(const_reference x) const;

    pointer allocate(size_type n, const void* hint= 0);
    
    void deallocate(pointer p, size_type n);

    size_type max_size() const throw();

    void construct (pointer p, const_reference val);

    void destroy (pointer p);
};

#endif