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

#include <utility>

namespace good {
struct X {};

X foo0() {
    auto const x = X();
    return x;
}

X foo1(X x) { return x; }

X foo2(X x, X y) { return true ? std::move(x) : std::move(y); }

X foo3(X x, X y) {
    if (true) {
        return x;
    }
    return y;
}
} // namespace good