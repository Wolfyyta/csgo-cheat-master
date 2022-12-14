#pragma once
#include "../hash/hash.h"

#include <unordered_map>
#include <type_traits>

class CRecvTable;
namespace netvars
{
	void SetupNetvars() noexcept;

	void Dump(const std::string_view base, CRecvTable* table, const std::uint32_t offset = 0) noexcept;

	inline std::unordered_map<std::uint32_t, std::uint32_t> data = { };
}

#define NETVAR(name, var, ...) \
inline std::add_lvalue_reference_t<__VA_ARGS__> name() noexcept \
{ \
	static const std::uint32_t offset = netvars::data[hash::CompileTime(var)]; \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(std::uintptr_t(this) + offset); \
}