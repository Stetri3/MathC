#pragma once
#include "../linalg/vector_cond.hpp"
#include "../utils/type_utils.hpp"
#include <type_traits>
#include <concepts>


namespace calc {

	enum class AtomType: uint64_t{
		c,
		x,
		npow,//Needs exponent
		mnpow, //
		rpow, //
		exp,//Needs base
		sin,
		cos,
		tan,
		erf,
	};

	namespace {
		struct DefVal{};
	}

	//Alla base una funzione è definita dal dominio, del codominio importa meno
	template <typename T, AtomType type, auto atomParam>
	struct AtomFunc {
		using X = T;
		static constexpr auto FType = type;
		static constexpr auto param = atomParam;
		constexpr auto Eval(T x){}
	};
}