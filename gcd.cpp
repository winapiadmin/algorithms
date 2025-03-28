//-funroll-loops -ffast-math -O3 -march=native -mtune=native -pipe -flto -fwhole-program -fwhole-file -fomit-frame-pointer -faggressive-loop-optimizations
#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include <cassert>
#include <random>

using ll = long long;

//btw this is from Mozilla:)
#define MOZ_ASSERT assert
#define MOZ_ALWAYS_INLINE
#if defined(_MSC_VER)
#ifdef _M_X64
#define MOZ_BITSCAN_WINDOWS64
#define MOZ_BITSCAN_WINDOWS
#elif defined(_M_IX86)
#define MOZ_BITSCAN_WINDOWS
#endif
#endif
namespace detail {

#if defined(MOZ_BITSCAN_WINDOWS)

inline uint_fast8_t CountLeadingZeroes32(uint32_t aValue) {
  unsigned long index;
  if (!_BitScanReverse(&index, static_cast<unsigned long>(aValue))) return 32;
  return uint_fast8_t(31 - index);
}

inline uint_fast8_t CountTrailingZeroes32(uint32_t aValue) {
  unsigned long index;
  if (!_BitScanForward(&index, static_cast<unsigned long>(aValue))) return 32;
  return uint_fast8_t(index);
}

inline uint_fast8_t CountPopulation32(uint32_t aValue) {
  uint32_t x = aValue - ((aValue >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  return (((x + (x >> 4)) & 0xf0f0f0f) * 0x1010101) >> 24;
}
inline uint_fast8_t CountPopulation64(uint64_t aValue) {
  return uint_fast8_t(CountPopulation32(aValue & 0xffffffff) +
                      CountPopulation32(aValue >> 32));
}

inline uint_fast8_t CountLeadingZeroes64(uint64_t aValue) {
#  if defined(MOZ_BITSCAN_WINDOWS64)
  unsigned long index;
  if (!_BitScanReverse64(&index, static_cast<unsigned __int64>(aValue)))
    return 64;
  return uint_fast8_t(63 - index);
#  else
  uint32_t hi = uint32_t(aValue >> 32);
  if (hi != 0) {
    return CountLeadingZeroes32(hi);
  }
  return 32u + CountLeadingZeroes32(uint32_t(aValue));
#  endif
}

inline uint_fast8_t CountTrailingZeroes64(uint64_t aValue) {
#  if defined(MOZ_BITSCAN_WINDOWS64)
  unsigned long index;
  if (!_BitScanForward64(&index, static_cast<unsigned __int64>(aValue)))
    return 64;
  return uint_fast8_t(index);
#  else
  uint32_t lo = uint32_t(aValue);
  if (lo != 0) {
    return CountTrailingZeroes32(lo);
  }
  return 32u + CountTrailingZeroes32(uint32_t(aValue >> 32));
#  endif
}

#elif defined(__clang__) || defined(__GNUC__)

#  if defined(__clang__)
#    if !__has_builtin(__builtin_ctz) || !__has_builtin(__builtin_clz)
#      error "A clang providing __builtin_c[lt]z is required to build"
#    endif
#  else
// gcc has had __builtin_clz and friends since 3.4: no need to check.
#  endif

inline uint_fast8_t CountLeadingZeroes32(uint32_t aValue) {
  return static_cast<uint_fast8_t>(__builtin_clz(aValue));
}

inline uint_fast8_t CountTrailingZeroes32(uint32_t aValue) {
  return static_cast<uint_fast8_t>(__builtin_ctz(aValue));
}

inline uint_fast8_t CountPopulation32(uint32_t aValue) {
  return static_cast<uint_fast8_t>(__builtin_popcount(aValue));
}

inline uint_fast8_t CountPopulation64(uint64_t aValue) {
  return static_cast<uint_fast8_t>(__builtin_popcountll(aValue));
}

inline uint_fast8_t CountLeadingZeroes64(uint64_t aValue) {
  return static_cast<uint_fast8_t>(__builtin_clzll(aValue));
}

inline uint_fast8_t CountTrailingZeroes64(uint64_t aValue) {
  return static_cast<uint_fast8_t>(__builtin_ctzll(aValue));
}

#else
#  error "Implement these!"
inline uint_fast8_t CountLeadingZeroes32(uint32_t aValue) = delete;
inline uint_fast8_t CountTrailingZeroes32(uint32_t aValue) = delete;
inline uint_fast8_t CountPopulation32(uint32_t aValue) = delete;
inline uint_fast8_t CountPopulation64(uint64_t aValue) = delete;
inline uint_fast8_t CountLeadingZeroes64(uint64_t aValue) = delete;
inline uint_fast8_t CountTrailingZeroes64(uint64_t aValue) = delete;
#endif

}  // namespace detail
/**
 * Compute the number of low-order zero bits in the NON-ZERO number |aValue|.
 * That is, looking at the bitwise representation of the number, with the
 * lowest- valued bits at the start, return the number of zeroes before the
 * first one is observed.
 *
 * CountTrailingZeroes32(0x0100FFFF) is 0;
 * CountTrailingZeroes32(0x7000FFFE) is 1;
 * CountTrailingZeroes32(0x0080FFFC) is 2;
 * CountTrailingZeroes32(0x0080FFF8) is 3; and so on.
 */
inline uint_fast8_t CountTrailingZeroes32(uint32_t aValue) {
  MOZ_ASSERT(aValue != 0);
  return detail::CountTrailingZeroes32(aValue);
}
/** Analogous to CountTrailingZeroes32, but for 64-bit numbers. */
inline uint_fast8_t CountTrailingZeroes64(uint64_t aValue) {
  MOZ_ASSERT(aValue != 0);
  return detail::CountTrailingZeroes64(aValue);
}
template <typename T>
inline uint_fast8_t CountTrailingZeroes(T aValue) {
  static_assert(sizeof(T) <= 8);
  static_assert(std::is_integral_v<T>);
  // This casts to 32-bits
  if constexpr (sizeof(T) <= 4) {
    return CountTrailingZeroes32(aValue);
  }
  // This doesn't
  if constexpr (sizeof(T) == 8) {
    return CountTrailingZeroes64(aValue);
  }
}

template <typename T>
MOZ_ALWAYS_INLINE T GCD(T aA, T aB) {
  static_assert(std::is_integral_v<T>);

  MOZ_ASSERT(aA >= 0);
  MOZ_ASSERT(aB >= 0);

  if (aA == 0) {
    return aB;
  }
  if (aB == 0) {
    return aA;
  }

  T az = CountTrailingZeroes(aA);
  T bz = CountTrailingZeroes(aB);
  T shift = std::min<T>(az, bz);
  aA >>= az;
  aB >>= bz;

  while (aA != 0) {
    if constexpr (!std::is_signed_v<T>) {
      if (aA < aB) {
        std::swap(aA, aB);
      }
    }
    T diff = aA - aB;
    if constexpr (std::is_signed_v<T>) {
      aB = std::min<T>(aA, aB);
    }
    if constexpr (std::is_signed_v<T>) {
      aA = std::abs(diff);
    } else {
      aA = diff;
    }
    if (aA) {
      aA >>= CountTrailingZeroes(aA);
    }
  }

  return aB << shift;
}
template <typename T>
T recursive_gcd(T a, T b) {
	static_assert(std::is_integral_v<T>);
	
	MOZ_ASSERT(a >= 0);
	MOZ_ASSERT(b >= 0);

    if (b == 0) return a;
    return recursive_gcd(b, a % b);
}


// Benchmark function
typedef std::function<ll(ll, ll)> GcdFunc;

ll benchmark(GcdFunc func, const std::vector<std::pair<ll, ll>>& testCases, double timeLimit) {
    ll count = 0;
    size_t i = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (true) {
        func(testCases[i].first, testCases[i].second);
        count++;
        i = (i + 1) % testCases.size(); // Loop through test cases

        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration<double>(now - start).count() >= timeLimit) break;
    }
    return count;
}

int main() {
    const size_t TEST_CASES = 100000; // Precompute 100k test cases
    const double TIME_LIMIT = 2.0;    // Run each benchmark for 2 seconds

    // Precompute random test cases
    std::vector<std::pair<ll, ll>> testCases(TEST_CASES);
    std::mt19937_64 rng(42);
    std::uniform_int_distribution<ll> dist(1, 1e9);
    
    for (auto& [a, b] : testCases) {
        a = dist(rng);
        b = dist(rng);
    }

    std::cout << "Benchmarking Mozilla GCD..." << std::endl;
    ll moz_count = benchmark(GCD<ll>, testCases, TIME_LIMIT);
    std::cout << "Mozilla GCD calls in " << TIME_LIMIT << "s: " << moz_count << std::endl;

    std::cout << "Benchmarking Recursive Euclidean GCD..." << std::endl;
    ll rec_count = benchmark(recursive_gcd<ll>, testCases, TIME_LIMIT);
    std::cout << "Recursive GCD calls in " << TIME_LIMIT << "s: " << rec_count << std::endl;
  /*
    The result depends on the optimization of the division operation and the compiler.
    For example, with -O3 optimization and old CPUs, the recursive GCD function is slower than the Mozilla GCD function
    because the division operation is slow on very old CPUs.
    But when CPUs are optimized for faster division, the recursive GCD function is faster.
    Benchmarking Mozilla GCD...
    Mozilla GCD calls in 2s: 5548996
    Benchmarking Recursive Euclidean GCD...
    Recursive GCD calls in 2s: 10870337
    or when unoptimized:
    Benchmarking Mozilla GCD...
    Mozilla GCD calls in 2s: 4555717
    Benchmarking Recursive Euclidean GCD...
    Recursive GCD calls in 2s: 8748157
  */
    return 0;
}
