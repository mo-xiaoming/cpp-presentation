#include <cstdio>
#include <cstring>

template <typename T> struct InstanceCounter {
  constexpr InstanceCounter() { ++counter_.numDefaultConstructor; }
  constexpr InstanceCounter(InstanceCounter const &) noexcept {
    ++counter_.numCopyConstructor;
  }
  constexpr InstanceCounter &operator=(InstanceCounter const &) &noexcept {
    ++counter_.numCopyAssignment;
    return *this;
  }
  constexpr InstanceCounter(InstanceCounter &&) noexcept {
    ++counter_.numMoveConstructor;
  }
  constexpr InstanceCounter &operator=(InstanceCounter &&) &noexcept {
    ++counter_.numMoveAssignment;
    return *this;
  }
  constexpr ~InstanceCounter() { ++counter_.numDestructor; }

  static constexpr void counterReset() { std::memset(&counter_, 0, sizeof(counter_)); }

private:
  static inline struct Counter {
    unsigned char numDefaultConstructor : 4 = 0;
    unsigned char numCopyConstructor : 4 = 0;
    unsigned char numCopyAssignment : 4 = 0;
    unsigned char numMoveConstructor : 4 = 0;
    unsigned char numMoveAssignment : 4 = 0;
    unsigned char numDestructor : 4 = 0;
    constexpr Counter &operator=(Counter &&) = delete;
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
#if 0
      if (numDestructor)
        std::printf("dtor  %d\n", numDestructor);
#endif
    }

  } counter_;
  static_assert(sizeof(counter_) == 3);
};

template <typename T> struct Counted : T, private InstanceCounter<T> {
  using T::T;
  using InstanceCounter<T>::counterReset;
};
