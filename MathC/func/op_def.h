#pragma once

#include <type_traits>
#include <cstdint>
#include <tuple>

namespace op {

	struct OpType{};
	struct AddOp: OpType{};
	struct SubOp: OpType{};
	struct MulOp: OpType{};
	struct DivOp: OpType{};
	struct PowOp: OpType{};
	struct ExpOp: OpType{};
	template <typename TTag>
	struct Gen1Op : OpType { using TTag = TTag; };
	template <typename TTag>
	struct Gen2Op : OpType { using TTag = TTag; };

	template <typename T, uint32_t Properties>
		requires std::is_base_of_v<OpType, T>
	struct OpProp{
		using Type = T;
		static constexpr uint32_t Prop = Properties;
	};


	//Struct usata dai tipi per definire che operazioni hanno
	//Da mettere come using Ops = op::OpList<...>
	template<typename... Ts>
		requires (std::is_base_of_v<OpType, Ts> && ...)
	struct OpList{
		static constexpr std::tuple<ut::type::Type<Ts>...> types{};

		template <typename T>
		static constexpr auto Find() {
			// Cerchiamo l'indice in cui Ts::Type è uguale a T
			constexpr size_t index = []() {
				size_t idx = 0;
				// Fold expression: incrementa l'indice finché non trova il match
				((std::is_same_v<T, typename Ts::Type> ? false : (++idx, true)) && ...);
				return idx;
				}();

			// Se l'indice è valido (minore del numero di elementi), ritorniamo il tipo trovato
			if constexpr (index < sizeof...(Ts)) {
				return std::get<index>(types);
			}
			else {
				return ut::type::Type<void>{};
			}
		}
	};
}