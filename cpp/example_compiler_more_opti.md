[gcc 9.2 fine? but trunk is not](https://godbolt.org/z/9CcppW)

[intro.progress]
The implementation may assume that any thread will eventually do one of the following:

- terminate
- make a call to library I/O function
- read or modify a volatile object, or
- perform a synchronization operation or an atomic operation
