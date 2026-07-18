#pragma once
#include <type_traits>


namespace ut::type {
    template <typename T>
    struct Type {
        using type = T;
    };
}