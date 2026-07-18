#pragma once
#include <type_traits>
#include "type_utils.hpp"
namespace cond {
    //utile: template per passare tipi a val vs const ref
    template <typename T>
    using pass_t = std::conditional_t<
        (sizeof(T) <= 16 && std::is_trivially_copyable_v<T>),
        T,
        const T&
    >;
}