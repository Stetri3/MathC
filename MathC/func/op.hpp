#pragma once

#include "op_def.h"
#include "funcs_decl.h"
#include "func.hpp"

namespace op {
	template <typename OpT, typename TLH, typename TRH>
	struct Op: Func<Op<OpT,TLH,TRH>> {
		using Prop = OpProp<OpT, TLH, TRH>;

		static constexpr auto Value() {

		}
	};
}