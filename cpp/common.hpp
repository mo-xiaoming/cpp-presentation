#include <cstdio>

template <typename T> struct InstanceCounter {
  InstanceCounter() { ++counter_.numDefaultConstructor; }
  InstanceCounter(InstanceCounter const &) noexcept {
    ++counter_.numCopyConstructor;
  }
  InstanceCounter &operator=(InstanceCounter const &) &noexcept {
    ++counter_.numCopyAssignment;
    return *this;
  }
  InstanceCounter(InstanceCounter &&) noexcept {
    ++counter_.numMoveConstructor;
  }
  InstanceCounter &operator=(InstanceCounter &&) &noexcept {
    ++counter_.numMoveAssignment;
    return *this;
  }
  ~InstanceCounter() { ++counter_.numDestructor; }

private:
  static inline struct Counter {
    unsigned char numDefaultConstructor : 4 = 0;
    unsigned char numCopyConstructor : 4 = 0;
    unsigned char numCopyAssignment : 4 = 0;
    unsigned char numMoveConstructor : 4 = 0;
    unsigned char numMoveAssignment : 4 = 0;
    unsigned char numDestructor : 4 = 0;
    Counter &operator=(Counter &&) = delete;
    ~Counter() {
      if (numDefaultConstructor)
        std::printf("ctor  %d\n", numDefaultConstructor);
      if (numCopyConstructor)
        std::printf("copy  %d\n", numCopyConstructor);
      if (numCopyAssignment)
        std::printf("copy= %d\n", numCopyAssignment);
      if (numMoveConstructor)
        std::printf("move  %d\n", numMoveConstructor);
      if (numMoveAssignment)
        std::printf("move= %d\n", numMoveAssignment);
      if (numDestructor)
        std::printf("dtor  %d\n", numDestructor);
    }

  } counter_;
  static_assert(sizeof(counter_) == 3);
};

template <typename T> struct Counted : T, private InstanceCounter<T> {
  using T::T;
};
