#pragma once
#include <cmath>
#include "func.hpp"

namespace funcs {

    // --- 2. DEFINIZIONE DEI NODI REALI ---

    template <auto Value>
    struct Constant : Func<Constant<Value>> {
        using self_type = Constant<Value>;
        template <typename T>
        constexpr T eval(T) const noexcept { return static_cast<T>(Value); }
        constexpr auto get_derivative() const noexcept { return Constant<0.0>{}; }
        template <typename T>
        constexpr auto compose(cond::pass_t<Func<T>> other) {
            return Func<self_type>{};
        }
    };

    struct Variable : Func<Variable> {
        using self_type = Func<Variable>;
        template <typename T>
        constexpr T eval(T x) const noexcept { return x; }
        constexpr auto get_derivative() const noexcept { return Constant<1.0>{}; }
        template <typename T>
        constexpr auto compose(cond::pass_t<Func<T>> other) {
            return Func<T>{};
        }
    };


    
}