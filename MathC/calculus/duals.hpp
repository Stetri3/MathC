#pragma once

#include <concepts>
#include <cmath>
#include <type_traits>
#include "../linalg/vectors.hpp"

template <typename T>
    requires co::RingDivInv<T>
struct Dual {
    T real;
    T dual;
    
    using ElType = T;
    template<typename T>
    using pass = co::pass_t<T>;

    // Costruttori
    constexpr Dual() : real{}, dual{} {}
    constexpr Dual(pass<T> r) : real(r), dual{} {}
    constexpr Dual(pass<T> r, pass<T> d) : real(r), dual(d) {}

    // Assegnamento e copia banalmente copiabili se T lo è
    Dual(const Dual&) = default;
    Dual(Dual&&) = default;
    constexpr Dual& operator=(const Dual&) = default;
    constexpr Dual& operator=(Dual&&) = default;

    // Operatori unari
    constexpr Dual operator+() const { return *this; }
    constexpr Dual operator-() const requires requires(T t) { -t; } {
        return { -real, -dual };
    }

    // Operatori aritmetici interni (Dual op Dual)
    constexpr Dual& operator+=(const Dual& other) {
        real += other.real;
        dual += other.dual;
        return *this;
    }
    constexpr Dual& operator-=(const Dual& other) {
        real -= other.real;
        dual -= other.dual;
        return *this;
    }

    constexpr Dual& operator*=(const Dual& other) {
        // (a + bε)(c + dε) = ac + (ad + bc)ε
        dual = real * other.dual + dual * other.real;
        real *= other.real;
        return *this;
    }

    constexpr Dual& operator/=(const Dual& other) {
        // (a + bε)/(c + dε) = a/c + ((bc - ad)/c²)ε
        T inv_real = static_cast<T>(1) / other.real;
        dual = (dual * other.real - real * other.dual) * (inv_real * inv_real);
        real *= inv_real;
        return *this;
    }

    // Operatori binari esterni
    friend constexpr Dual operator+(Dual lhs, const Dual& rhs) { return lhs += rhs; }
    friend constexpr Dual operator-(Dual lhs, const Dual& rhs) { return lhs -= rhs; }
    friend constexpr Dual operator*(Dual lhs, const Dual& rhs) { return lhs *= rhs; }
    friend constexpr Dual operator/(Dual lhs, const Dual& rhs) { return lhs /= rhs; }

    // Overload con scalari T (evita promozioni inutili)
    constexpr Dual& operator+=(const T& scalar) { real += scalar; return *this; }
    constexpr Dual& operator-=(const T& scalar) { real -= scalar; return *this; }
    constexpr Dual& operator*=(const T& scalar) { real *= scalar; dual *= scalar; return *this; }
    constexpr Dual& operator/=(const T& scalar) {
        T inv = static_cast<T>(1) / scalar;
        real *= inv;
        dual *= inv;
        return *this;
    }

    friend constexpr Dual operator+(Dual lhs, const T& rhs) { return lhs += rhs; }
    friend constexpr Dual operator+(const T& lhs, Dual rhs) { return rhs += lhs; }
    friend constexpr Dual operator-(Dual lhs, const T& rhs) { return lhs -= rhs; }
    friend constexpr Dual operator-(const T& lhs, const Dual& rhs) { return Dual(lhs) - rhs; }
    friend constexpr Dual operator*(Dual lhs, const T& rhs) { return lhs *= rhs; }
    friend constexpr Dual operator*(const T& lhs, Dual rhs) { return rhs *= lhs; }
    friend constexpr Dual operator/(Dual lhs, const T& rhs) { return lhs /= rhs; }
    friend constexpr Dual operator/(const T& lhs, const Dual& rhs) { return Dual(lhs) / rhs; }

    // Confronti (basati esclusivamente sulla parte reale)
    constexpr bool operator<=>(const Dual& other) const { real <=> other.real; }
    constexpr bool operator ==(const Dual& other) const = default;


    // Cast esplicito a T (scarta la parte duale)
    constexpr explicit operator T() const { return real; }
};