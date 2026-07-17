#pragma once
//File di condizionali e concepts per tipi algebrici
#include <cstdint>
#include <type_traits>
#include <concepts>


// Dichiarazioni forward
template <uint32_t dim, typename T>
struct Vec;
template <uint32_t Rows, uint32_t Cols, typename T>
struct Mat;
template <uint32_t dim, typename T>
struct MatQ;

namespace math::cond {


    //Tipi helper
    // 
    // 
    // Helper minimale: una funzione che accetta T. 
    // Se un tipo U può essere passato qui senza cast espliciti, allora U è implicitamente convertibile a T.
    template <typename T>
    void implicit_helper(T) {};

    template <typename From, typename To>
    concept impl_conv_to = requires(From && from) {
        implicit_helper<To>(std::forward<From>(from));
    };

    //Condizionali constexpr 

    //Semigruppo (chiuso rispetto alla somma)
    template <typename T>
    concept Semigroup = requires(T a, T b) {
        { a + b } -> std::same_as<T>;
    };
    template <typename T>
    struct is_semigroup : std::bool_constant<Semigroup<T>> {};
    template <typename T>
    inline constexpr bool is_semigroup_v = is_semigroup<T>::value;

    //Gruppo (chiuso rispetto alla somma e con el. inverso/divisione)
    template <typename T>
    concept Group = Semigroup<T> && requires(T a, T b) {
        { a - b } -> std::same_as<T>;
        { -a }    -> std::same_as<T>;
    };
    template <typename T>
    struct is_group : std::bool_constant<Group<T>> {};
    template <typename T>
    inline constexpr bool is_group_v = is_group<T>::value;

    //Semigruppo per il prodotto (semigruppo rispetto a *)
    template <typename T>
    concept SemigroupProd = requires(T a, T b) {
        { a* b } -> std::same_as<T>;
    };
    template <typename T>
    struct is_semigroupprod : std::bool_constant<SemigroupProd<T>> {};
    template <typename T>
    inline constexpr bool is_semigroupprod_v = is_semigroupprod<T>::value;

    //SEMIANELLO (chiuso rispetto a + e *)
    template <typename T>
    concept Semiring = Semigroup<T> && SemigroupProd<T>;
    template <typename T>
    struct is_semiring : std::bool_constant<Semiring<T>> {};
    template <typename T>
    inline constexpr bool is_semiring_v = is_semiring<T>::value;

    //ANELLO (con + e *, con inverso additivo e inverso unario)
    template <typename T>
    concept Ring = Group<T> && SemigroupProd<T>;
    template <typename T>
    struct is_ring : std::bool_constant<Ring<T>> {};
    template <typename T>
    inline constexpr bool is_ring_v = is_ring<T>::value;

    //ANELLO CON DIVISIONE (autoesplicativo)
    template <typename T>
    concept RingDiv = Ring<T> && requires(T a, T b) {
        { a / b } -> std::same_as<T>;
    };
    template <typename T>
    struct is_ringdiv : std::bool_constant<RingDiv<T>> {};
    template <typename T>
    inline constexpr bool is_ringdiv_v = is_ringdiv<T>::value;

    //ANELLO CON DIVISIONE E ELEMENTO INVERSO
    template <typename T>
    concept RingDivInv = RingDiv<T> && requires(T t) {
        { static_cast<T>(1) / t } -> std::convertible_to<T>;
    };
    template <typename T>
    struct is_ringdivinv : std::bool_constant<RingDivInv<T>> {};
    template <typename T>
    inline constexpr bool is_ringdivinv_v = is_ringdivinv<T>::value;

    //Per campo (RingDiv + commutatività per moltiplicazione) usiamo semplicemente tipo aritmetico
    template <typename T>
    concept Field = std::is_arithmetic_v<T>;
    template <typename T>
    struct is_field : std::bool_constant<Field<T>> {};
    template <typename T>
    inline constexpr bool is_field_v = is_field<T>::value;

    //Tipi un po' più "complicati"
    //PRODOTTO CON IMMAGINE A SEMIGRUPPO: il prodotto è chiuso rispetto alla somma, ovvero esiste 
    //un'operazione prodotto (ordinato T*U) la cui immagine è chiusa rispetto alla somma, T*U + T*U = T*U
    template <typename T, typename U>
    concept ProdImageSemigroup = requires(T t, U u) {
        { t* u };
    }&& Semigroup<decltype(std::declval<T>()* std::declval<U>())>;
    template <typename T, typename U>
    struct is_prodimagesemigroup : std::bool_constant<ProdImageSemigroup<T, U>> {};
    template <typename T, typename U>
    inline constexpr bool is_prodimagesemigroup_v = is_prodimagesemigroup<T, U>::value;

    //SOMMA CON IMMAGINE A SEMIGRUPPO (la somma è chiusa rispetto al prodotto)
    //Come sopra invertendo somma con prodotto
    template <typename T, typename U>
    concept SumImageSemigroup = requires(T t, U u) {
        { t + u };
    }&& SemigroupProd<decltype(std::declval<T>() + std::declval<U>())>;
    template <typename T, typename U>
    struct is_sumimagesemigroup : std::bool_constant<SumImageSemigroup<T, U>> {};
    template <typename T, typename U>
    inline constexpr bool is_sumimagesemigroup_v = is_sumimagesemigroup<T, U>::value;

    //IDENTIFICATORI TIPI ALGEBRICI
    //Per identificare vec
    template <typename T>
    struct is_vec : std::false_type {};

    template <uint32_t dim, typename T>
    struct is_vec<Vec<dim, T>> : std::true_type {};

    // Il concetto finale
    template <typename T>
    concept VecType = is_vec<T>::value;
    //Alias constexpr bool diretto
    template <typename T>
    inline constexpr bool is_vec_v = is_vec<T>::value;


    //Per MAT::

    //Per matQ
    template <typename T>
    struct is_matQ : std::false_type {};

    template <uint32_t dim, typename T>
    struct is_matQ<MatQ<dim, T>> : std::true_type {};

    // Il concetto finale
    template <typename T>
    concept MatQType = is_matQ<T>::value;
    //Alias bool
    template <typename T>
    inline constexpr bool is_matQ_v = is_matQ<T>::value;

    //Per mat generica
    template <typename T>
    struct is_mat : std::false_type {};

    template <uint32_t Rows, uint32_t Cols, typename T>
    struct is_mat<Mat<Rows, Cols, T>> : std::true_type {};

    template <uint32_t dim, typename T>
    struct is_mat<MatQ<dim, T>> : std::true_type {};

    // Il concetto finale
    template <typename T>
    concept MatType = is_mat<T>::value;
    //Alias bool
    template <typename T>
    inline constexpr bool is_mat_v = is_mat<T>::value;

    // 2. Il concetto algebraic (Vec || Mat)
    template <typename T>
    concept AlgebraicType = VecType<T> || MatType<T>;

    // =================================================================
    // 3. Il trait "is_algebraic" definito in una riga usando il concetto
    // =================================================================
    template <typename T>
    struct is_algebraic : std::bool_constant<AlgebraicType<T>> {};

    //Constexpr bool
    template <typename T>
    inline constexpr bool is_algebraic_v = is_algebraic<T>::value;

    //Struct per ottenere il metadato _depth
    template <typename T, typename = void>
    struct get_depth {
        enum { value = 0 };
    };

    // Se il tipo ha l'enum '_depth', estrai il valore dell'enum
    template <AlgebraicType T>
    struct get_depth<T, void> {
        enum { value = T::_depth };
    };

    template <typename T>
    inline constexpr uint32_t _depth_v = get_depth<T>::value;

    //utile: template per passare tipi a val vs const ref
    template <typename T>
    using pass_t = std::conditional_t<
        (sizeof(T) <= 16 && std::is_trivially_copyable_v<T>),
        T,
        const T&
    >;


    namespace ded {
        //Strutture dedicate

        template <typename T>
        concept RadSpace = requires (T x) {
            requires impl_conv_to<decltype(x.sqrt()* x.sqrt()), T>;
        };
    }
}