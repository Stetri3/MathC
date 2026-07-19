#pragma once
#include <type_traits>
#include <tuple>

namespace op {


	struct OpType {
		
	};

	struct OpAdd: OpType{
		
	};
	struct OpMul: OpType{};
	struct OpSub: OpType{};
	struct OpDiv: OpType{};
	struct OpExp: OpType{};
	struct OpPow: OpType{};
	template <typename TTag>
	struct OpGen: OpType{
		using Tag = TTag;
	};

	// 1. Everything involving the default provider goes inside the anonymous namespace
	namespace {

		template <typename T>
		using Type = ut::type::Type<T>;

		template <typename T>
		Type<T> DefType(T x) {
			return Type<T>;
		}

		template <typename OpT, typename TLH, typename TRH>
		constexpr auto opDefaultProvider = nullptr;

		template <typename OpT, typename TLH, typename TRH>
		constexpr uint32_t opDefaultProps = 0;

		// Specializations MUST be inside the same anonymous namespace block
		//Plus
		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l + r; }
		constexpr auto opDefaultProvider<OpAdd, TLH, TRH> = [](TLH a, TRH b) { return a + b; };

		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l + r; }
		constexpr uint32_t opDefaultProps<OpAdd, TLH, TRH> = static_cast<uint32_t>(12);

		//Prod
		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l * r; }
		constexpr auto opDefaultProvider<OpAdd, TLH, TRH> = [](TLH a, TRH b) { return a * b; };

		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l* r; }
		constexpr uint32_t opDefaultProps<OpAdd, TLH, TRH> = static_cast<uint32_t>(12);

		//Diff
		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l - r; }
		constexpr auto opDefaultProvider<OpAdd, TLH, TRH> = [](TLH a, TRH b) { return a - b; };

		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l - r; }
		constexpr uint32_t opDefaultProps<OpAdd, TLH, TRH> = static_cast<uint32_t>(12);

		//Div
		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l / r; }
		constexpr auto opDefaultProvider<OpMul, TLH, TRH> = [](TLH a, TRH b) { return a / b; };

		template <typename TLH, typename TRH>
			requires requires (TLH l, TRH r) { l / r; }
		constexpr uint32_t opDefaultProps<OpAdd, TLH, TRH> = static_cast<uint32_t>(12);
	
	}


	template <typename OpT, typename TLH, typename TRH>
		requires std::is_base_of_v<OpType, OpT>
	struct OpProp {
		using Type = OpT;
		using LHS = TLH;
		using RHS = TRH;
		template <uint32_t val>
	};
	
	template <typename OpT, typename TLH, typename TRH>
		requires std::is_base_of_v<OpType, OpT>
	struct OpCustom {
		inline static constexpr auto m = op::opDefaultProvider;
		inline static constexpr uint32_t prop = opDefaultProps;
	};

	

}