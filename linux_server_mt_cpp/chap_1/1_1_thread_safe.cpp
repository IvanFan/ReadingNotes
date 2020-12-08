//
// Created by yifan on 7/12/20.
//thread safe and life cycle
// race condition
//MutexLock -> critical section
//MutexLockGuard

// for safety, don;t pass this during construction
// construct -> init is a good way

//mutux can only make sure the function will be executed one-by-one
//but it cannot solve the race condition for delete

// if we use mutux to read/write 2 obj of one class, it may have dead lock
// one way is to always lock the one with smaller address

//one way: proxy->object, proxy always exists. if obj is empty, proxy is 0
// but race condition is still exist

// better way: reference counting
// p1 ->
//      pointer: count=2 -> obj
// p2 ->

// p1 X ->
//      pointer: count=1 -> obj
// p2 ->

// p1 X ->
//      pointer: count=0 -> obj X
// p2 X ->

//same concept of shared_ptr

// the count of shared_ptr is atomic operation, no lock

// C++ potential memory issue:
// shared_ptr can solve the majority of it
// weak_ptr can lock and become shared_ptr

// shared_ptr is not 100% safe
//if we need to use the safe shared_ptr in multi thread, use it with mutex
MutexLock mutex;// no need for ReaderWriterLock for the performance reason
shared_ptr<Foo> global_ptr;
//  function pass shared_ptr by const ref to avoid performance issue
//deconstruction process in a slow thread. Better to build a separate thread for deconstruction
//e.g. BlockingQueue<shared_ptr<void>>

// RAII, new -> shared_ptr, no delete
//owner -> shared_ptr -> child -> weak_ptr -> owner

// ace condition
// critical section
// peterson algorithm
//TLS
//priority inversion problem
//ep weakup
// semaphore up & down
// mutex

