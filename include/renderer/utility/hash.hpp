#pragma once

#include <bit>
#include <utility>
#include <limits>
#include <cstdint>

namespace gfx::util
{
	
	namespace detail
	{
		template<typename T>
		inline T xorshift(const T& n, int i) {
			return n ^ (n >> i);
		}

		// a hash function with another name as to not confuse with std::hash
		inline uint32_t distribute(const uint32_t& n) {
			uint32_t p = 0x55555555ul; // pattern of alternating 0 and 1
			uint32_t c = 3423571495ul; // random uneven integer constant; 
			return c * xorshift(p * xorshift(n, 16), 16);
		}

		// a hash function with another name as to not confuse with std::hash
		inline uint64_t distribute(const uint64_t& n) {
			uint64_t p = 0x5555555555555555ull; // pattern of alternating 0 and 1
			uint64_t c = 17316035218449499591ull;// random uneven integer constant; 
			return c * xorshift(p * xorshift(n, 32), 32);
		}

		inline void hash_combine(std::size_t&) {}

		// call this function with the old seed and the new key to be hashed and combined into the new seed value, respectively the final hash
		template <class T>
		inline void hash_combine(std::size_t& seed, const T& v)
		{
			seed = std::rotl(seed, std::numeric_limits<size_t>::digits / 3) ^ distribute(std::hash<T>{}(v));
		}

		template<typename T, typename... Types>
		inline void hash_combine(size_t& seed, const T& val, const Types&... args)
		{
			hash_combine(seed, val);
			hash_combine(seed, args...);
		}
	}

	template<typename... Types>
	inline size_t hash_val(const Types&... args)
	{
		size_t seed = 0;
		detail::hash_combine(seed, args...);
		return seed;
	}
}