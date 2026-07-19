#pragma once

#include <type_traits>
#include "func.hpp"

namespace funcs {
	template <auto val>
	struct Constant : Func<Constant, decltype(val)> {
		static constexpr auto value = val;
	};

	template <typename domain>
	struct Variable : Func<Variable, domain> {
		using T = domain;
	};
}