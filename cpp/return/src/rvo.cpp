// Avoid std::move in your return -- it will inhibit RVO
// Function return type must be the same as the type you are returning
// You can return a local variable or by-value parameter
// Multiple return statements will often prevent RVO
// Multiple return statements will not affect auto-remove
// Conditional expressions in the return statement will often prevent auto-remove
//   `return test ? std::move(x) : std::move(y);`
//   `if (test) return x; else return y;`

// In a return statement, when the operand is the name of a non-volatile
// object with automatic storage duration, which isn't a function parameter
// or a catch clause parameter, and which is of the same class type
// (ignoring cv-qualification) as the function return type. This variant of
// copy elision is known as NRVO, "named return value optimization".

#include <string>
#include <utility>

namespace {
struct X {
    std::string s;
};

X foo0(X&& x) { return std::move(x); }

X foo1(X& x) { return std::move(x); }

X foo3(bool flag, X x, X y) { // NOLINT
    return flag ? std::move(x) : std::move(y);
}

X foo4(bool flag, X x, X y) {
    if (flag) {
        return x;
    }
    return y;
}

X foo2() {
    auto const x = X();
    return x; // NOLINT // const stops it from being moved, it's a copy
}
} // namespace

int main() {
    foo0(X{});
    auto x = X();
    foo1(x);
    foo2();
    foo3(true, X(), X());
    foo4(false, X(), X());
}
