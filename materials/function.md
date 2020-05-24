
##### A sample implementation of `std::move`, which better be memorized as `rvalue_cast`

```cpp
template <typename T>
decltype(auto) move(T&& param) {
    return static_cast<std::remove_reference_t<T>&&>(param);
}
```

##### Don't declare objects `const` if you want to be able to move from them
```cpp
#include <string>

struct S {
    S(const std::string text)
    : value(std::move(text)) {}

    std::string value;
}
```
`std::string` was copied, not moved. The move constructor takes an rvalue reference to a *non-*`const std::string`, and `std::move(text)` is a `const std::string`, it can be passed to the copy constructor, because an lvalue-reference-to-const is permitted to bind to a `const` rvalue.


##### When to use `std::move`/`std::forward` on return value
Answer: Only when a function returns by *value*, and you're returning an object bound to an rvalue reference or a universal reference.

Compilers may elide the copying (or moving) of a **local object** in a function that returns a value if
1. the type of the local object is the same as that returned by the function

2. the local object is what's being returned

```cpp
struct S {};

S foo() {
    S s;
    return std::move(s);
}
```
gives a warning, because of RVO
>moving a local object in a return statement prevents copy elision [-Wpessimizing-move]

```cpp
struct S {};

S foo(S&& s) {
    return std::move(s);
}
```
is a valid optimization

##### Standard says that if the condition for the RVO are met, but compilers choose not to perform copy elision, the object being returned *must be treated as an rvalue*

The standard requires that when the RVO is permitted, either copy elision takes place or `std::move` is implicitly applied to local objects being returned.

```cpp
S foo() {
    S s;
    return s;
}
```

In the worst case scenario, it is treated as
```cpp
S foo() {
    S s;
    return std::move(s);
}
```

```cpp
S foo(S s) {
    return s;
}
```
must be treated as
```cpp
S foo(S s) {
    return std::move(s);
}
```

##### And `std::forward` implementation?
```cpp
template <typename T>
T&& forward(std::remove_reference_t<T>& param) {
    return static_cast<T&&>(param);
}
```

```cpp
template <typename T>
void foo(T&& param);
```
1. When an lvalue is passed as an argument, `T` is an lvalue reference

2. When an rvalue is passed, `T` is a non-reference

If an lvalue `Widget widget` passed to `foo`, then `T` is type `Widget&`

If an rvalue passed to `foo`, then `T` is type `Widget`

**reference collaping**
>If either reference is an lvalue reference, the result is an lvalue reference. Otherwise (i.e., if both are rvalue references) the result is an rvalue reference

In lvalue's case
```cpp
Widget& && forward(std::remove_reference_t<Widget&>& param) {
    retrun static_cast<Widget& &&>(param);
}
```
transfers to
```cpp
Widget& forward(Widget& param) {
    return static<Widget&>(param);
}
```
In rvalue's case
```cpp
Widget&& forward(std::remove_reference_t<Widget&&>& param) {
    return static_cast<Widget>(param);
}
```
transfer to
```cpp
Widget&& forward(Widget& param) {   // basically a std::move
    return static_cast<Widget>(param);
}
```

##### `auto&&` folows the same rule
```cpp
Widget w;

auto&& w1 = w;  // lvalue, so Widget& for auto, Widget& && collapses to Widget&

auto&& w2 = widgetFactory();    // rvalue, so auto is Widget, done
```

Such a beautiful language
>When compilers generate a reference to a reference in a reference collapsing context, the result becomes a single reference. If either of the original references is an lvalue reference, the result is an lvalue reference. Otherwise it’s an rvalue reference.
#### Passing by value
Consider passing objects by value when you know you'll copy them
```cpp
struct S {
    S(std::string n) {   // replace T&& ctor
    : name(std::move(n)) {}

    std::string name;
};
```

#### Use Tag dispatch
```cpp
struct S {
    template <typename T, typename std::enable_if_t<
            !std::is_same_v<S, std::decay_t<T>>>
    >
    S(T&& n);
};
```

Solving the derived class ctor problem, change it to
```cpp
struct S {
    template <typename T, typename std::enable_if_t<
            !std::is_base_of<S, std::decay_t<T>>>
    >
    S(T&& n);
};
```

To distinguish it from other constructors
```cpp
struct S {
    template <typename T, typename std::enable_if_t<
            !std::is_base_of<Person, std::decay_t<T>>
            &&
            !std::is_integral<std::remove_reference_t<T>>
    >>
    S(T&& n): name(std::forward<T>(n)) {
        static_cast(std::is_constructible<std::string, T>); // gives a better error message
    }

    S(int ind): name(foo(idx)) {}

    std::string name;
};
```
```cpp
shared_ptr<widget> get_widget(int id) {
	static map<int, weak_ptr<widget>> cache;
	static mutex m;
	
	lock_guard hold{m};
	auto sp = cache[id].lock();
	if (!sp) cache[id] = sp = load_widget(id);
	return sp;
}
```

```cpp
enum class Width {};
enum class Height {};
```

这样`Width`和`Height`类型在传参时无法隐性转换，不再有搞错顺序的问题

然后一位仁兄发现了以下的代码居然可以编译，然后大家全都傻了

```cpp
enum class Apple {};
enum class Orange {};

int main() {
    Orange o;
    //Apple y = o; // this does not compile
    Apple x{o}; // this does?!
}
```
橘子可以放进苹果里？！这个好像是C++标准本身的bug......

> C++ has so many corners it's practically a circle. -- Matt Calabrese

Nicolai Josuttis说过，别在返回值上用括号，当然他指的是返回类型如果是```decltype(auto)```的话，```return (...)```返回的可能是指向局部变量的引用

下面也是一个返回值上用括号引发==奇怪==行为的例子
```cpp
#include <iostream>
#include <string>

struct X {
    ~X() { std::cout << s << '\n'; }
    std::string &s;
};

std::string foo() {
    std::string s{"Can you see me?"};
    X x{s};
    return (s);
}

int main() {
    foo();
}
```


clang9编译，**正常**打印```Can you see me?```。但是gcc9.2编译，即使什么优化选项都不开，结果是什么也不打印？！

这是因为gcc编译的时候，发生了NRVO(named return value optimization)，```foo```中的```s```整个被优化掉了，而```X.s```又是指向它的引用，于是在这种情况下，它的行为是什么都打印不出来

谁对谁错，我也不知道🤷‍♂️

P.S. 如果把```return (s)```的括号去掉，两者都正常打印```Can you see me?```
They are different conceptually.

For the first pattern, you have decorators going (transparently) over a core functionality class, each adding their own twist/specialization to an existing implementation.

The relationship the first pattern models is "is-a" (MyTypeWithMixins is a Mixin1<MyType> specialization, Mixin1<MyType> is a MyType specialization).

This is a good approach when you are implementing functionality within a rigid interface (as all types will implement the same interface).

For the second pattern, you have functionality parts used as implementation details (possibly within different, unrelated classes).

The relationship modeled here is "is implemented in terms of" (MyTypeWithMixins is a MyType specialization, implemented in terms of Mixin1 and Mixin2 functionality). In many CRTP implementation, the CRTP templated base is inherited as private or protected.

This is a good approach when you are implementing common functionality accross different, unrelated components (i.e. not with the same interface). This is because two classes inheriting from Mixin1 will not have the same base class.

To provide a concrete example for each:

For the first case, consider the modeling of a GUI library. Each visual control would have a (for example) display function, which in a ScrollableMixin would add scroll-bars, if required; The scrollbars mixin would be a base class for most controls that are re-sizable (but all of them a part of the "control/visual component/displayable" class hierarchy.

class control {
    virtual void display(context& ctx) = 0;
    virtual some_size_type display_size() = 0;
};

template<typename C>class scrollable<C>: public C { // knows/implements C's API
    virtual void display(context& ctx) override {
        if(C::display_size() > display_size())
            display_with_scrollbars(ctx);
        else
            C::display(canvas);
    }
    ... 
};

using scrollable_messagebox = scrollable<messagebox>;
In this case, all mixin types would override (for example) a display method, and delegate parts of it's functionality (the specialized drawing part) to the decorated type (the base).

For the second case, consider a case when you would implement an internal system for adding a version number to serialized objects within the application. The implementation would look like this:

template<typename T>class versionable<T> { // doesn't know/need T's API
    version_type version_;
protected:
    version_type& get_version();
};

class database_query: protected versionable<database_query> {};
class user_information: protected versionable<user_information> {};
In this case, both database_query and user_information store their settings with a version number, but they are in no way in the same object hierarchy (they don't have a common base).
