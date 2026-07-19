#pragma once
#include "funcs_decl.h"

template <typename TDerived, typename TDomain = void>
struct Func {
	using Derived = TDerived;
	using T = TDomain;

};
