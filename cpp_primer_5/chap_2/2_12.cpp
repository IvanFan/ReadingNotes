//
// Created by yifan on 7/12/20.
//

//smart pointer
//shared_ptr
//unique_ptr
//weak_ptr

shared_ptr<string> pl;
shared_ptr<string> p3 = make_shared<stromg>(10, '9');
//reference count
//destructor

// new allocate memory
// delete

shared_ptr<int> p2(new int(1024));

p2.reset(q,d);

//don't use normal pointer with smart pointer
//don't use get with smart pointer

//use shared_ptr for exception because new/delete cannot auto release with exception

//unique_ptr
// return unique_ptr p.release()

//weak_ptr
// weak_ptr will not increase the ref count of shared_ptr
//w.reset() w.use_count() w.expired()
// w.lock() if expired, return an empty shared_ptr else return a shared_ptr connected to the obj

// dynamic array
//int *p = new T[42]
// delete [] p;

//allocator class
allocator<string> alloc;
auto const p = alloc.allocate(n);
//alloc.deallocate(p, n)
//a.construct(p, args)
//a.destroy(p)

//uninitialized_copy
//uninitialized_fill

// essential concept for multi thread coding