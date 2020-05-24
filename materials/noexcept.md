```cpp
int f(int x) throw();   // C++98
int f(int x) noexcept;  // C++11
```
If exception specificatioin is violated,

C++98: the call stack is unwound to `f`'s caller, and, after some actions not relevant here, program execution is terminated.

C++11: the stack is only *possibly* unwound before program execution is terminated.

In a `noexcept` function, optimizers need not keep the runtime stack, nor must they ensure that objects in a `noexcept` function are destroyed.

`std::vector::push_back` takes advantage of this "move if you can, but copy if you must" strategy, and other functions supporting the strong exeption safety guarantee in C++98 behave the same way.

All these functions replace calls to copy operations in C++98 with calls to move operations in C++11 only if the **move operations are known to not emit exeptions**, which by calling `std::move_if_noexcept`, which calls `std::is_nothrow_move_constructible` which based on whether the move constructor has a `noexcept`/`throw()` designation.

In C++98, it was considered **bad style** to permit the memory *deallocation function* (i.e., `operator delete` and `operator delete[]`) and *destructors* to emit exceptions.

In C++11, all memory *deallocation functions* and all *destructors* -- both user-defined and compiler-generated -- are **implicitly `noexcept`**

If the destructor for an object being used by the STL emits an exception, the behavior of the program is **undefined**

