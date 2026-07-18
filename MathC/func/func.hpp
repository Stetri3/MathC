#pragma once
#include "funcs_decl.h"

template <typename TDerived>
struct Func {
    using Derived = TDerived;
    template <typename T>
    constexpr T operator()(T x) const noexcept {
        return static_cast<const Derived*>(this)->eval(x);
    }

    constexpr auto deriv() const noexcept {
        return static_cast<const Derived*>(this)->get_derivative();
    }
};

