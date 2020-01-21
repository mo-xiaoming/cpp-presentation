# C++, The Good, The Bad and The Ugly

## The Good: The Evolution of C++, From (pre) C++98 To C++17

### Newer is (Almost) Always Better

* More static checks
* More compile time calculations
* More expressive
* Faster

   and

* More (Default) Hardening Options, `_FORTIFY_SOURCE=2`, `-fstack-protector-strong` etc.

### Tips from 1,000 miles high

1. Always `constexpr`, if `constexpr` won't compile, then try to `const` everything
3. Write code if have no other choice, use existing libraries instead
4. To be a good C++ programmer, knowing template is a necessity
5. Use smart pointers, NO RAW POINTERS. More clearly, NO RAW RESOURCE MANAGMENTS
   * Normally, `make_unique` > `unique_ptr` > `make_shared` > `shared_ptr`
   * There are exceptions
6. Use std/boost::array, NO RAW ARRAYS
7. Use std/boost::algorithms, (almost) NO RAW LOOPS
8. APIs should be easy to use, and hard to misuse
9. Make a good use of STL algorithms
10. Because of move semantics, same code might run faster under new standards

## The Bad News

  > ...we are writting C++, the rule can't be that simple.
  > -- Nicolai M. Josuttis

* Multiple ways to do one thing, Even some methods are better than others, you have to be familier with all other inferior ones, because they are used by other people.
* C++11 improves C++98 in multiple ways, but there are catches.
* Sometimes, compilers have to work against C++ standard to maintain backward compatibility
* Lots of bad reputations C++ got, are caused by people thought they were writting "efficient" code

## The Ugly, Undefined Behavior
