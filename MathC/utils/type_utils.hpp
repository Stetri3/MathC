#pragma once
#include <type_traits>


namespace ut::type {
    template <typename T>
    struct Type {
        using type = T;
    };

    //Concept (usando macro) per verificare che un tipo abbia un certo metodo
#define HAS_METHOD(Type, MethodCall) \
    requires(Type t) { t.MethodCall; }
}