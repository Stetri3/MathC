#pragma once

#include "op_def.h"
#include "funcs_decl.h"



namespace op {
	template <typename Prop, typename... Args>
	struct Op : Func<Op<Prop, Args...>> {
		using Type = Prop;
	};

}