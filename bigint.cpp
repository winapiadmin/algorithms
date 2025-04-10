//-lgmp -funroll-loops -ffast-math -O3 -march=native -mtune=native -pipe -flto -fwhole-program -fwhole-file -fomit-frame-pointer -faggressive-loop-optimizations
#include <bits/stdc++.h>
using namespace std;
namespace CPPBigInt
{
	// C++ program to implement
	// the above approach

	class BigInt
	{
		string digits;

	public:
		// Constructors:
		BigInt(unsigned long long n = 0);
		BigInt(string &);
		BigInt(const char *);
		BigInt(const BigInt &);

		// Helper Functions:
		friend void divide_by_2(BigInt &a);
		friend bool Null(const BigInt &);
		friend int Length(const BigInt &);
		int operator[](const int) const;

		/* * * * Operator Overloading * * * */

		// Direct assignment
		BigInt &operator=(const BigInt &);

		// Post/Pre - Incrementation
		BigInt &operator++();
		BigInt operator++(int temp);
		BigInt &operator--();
		BigInt operator--(int temp);

		// Addition and Subtraction
		friend BigInt &operator+=(BigInt &, const BigInt &);
		friend BigInt operator+(const BigInt &, const BigInt &);
		friend BigInt operator-(const BigInt &, const BigInt &);
		friend BigInt &operator-=(BigInt &, const BigInt &);

		// Comparison operators
		friend bool operator==(const BigInt &, const BigInt &);
		friend bool operator!=(const BigInt &, const BigInt &);

		friend bool operator>(const BigInt &, const BigInt &);
		friend bool operator>=(const BigInt &, const BigInt &);
		friend bool operator<(const BigInt &, const BigInt &);
		friend bool operator<=(const BigInt &, const BigInt &);

		// Multiplication and Division
		friend BigInt &operator*=(BigInt &, const BigInt &);
		friend BigInt operator*(const BigInt &, const BigInt &);
		friend BigInt &operator/=(BigInt &, const BigInt &);
		friend BigInt operator/(BigInt &, const BigInt &);

		// Modulo
		friend BigInt operator%(const BigInt &, const BigInt &);
		friend BigInt &operator%=(BigInt &, const BigInt &);

		// Power Function
		friend BigInt &operator^=(BigInt &, const BigInt &);
		friend BigInt operator^(BigInt &, const BigInt &);

		// Square Root Function
		friend BigInt sqrt(BigInt &a);

		// Read and Write
		friend ostream &operator<<(ostream &, const BigInt &);
		friend istream &operator>>(istream &, BigInt &);

		// Others
		friend BigInt NthCatalan(int n);
		friend BigInt NthFibonacci(int n);
		friend BigInt Factorial(int n);
	};

	BigInt::BigInt(string &s)
	{
		digits = "";
		int n = s.size();
		for (int i = n - 1; i >= 0; i--)
		{
			if (!isdigit(s[i]))
				throw("ERROR");
			digits.push_back(s[i] - '0');
		}
	}
	BigInt::BigInt(unsigned long long nr)
	{
		do
		{
			digits.push_back(nr % 10);
			nr /= 10;
		} while (nr);
	}
	BigInt::BigInt(const char *s)
	{
		digits = "";
		for (int i = strlen(s) - 1; i >= 0; i--)
		{
			if (!isdigit(s[i]))
				throw("ERROR");
			digits.push_back(s[i] - '0');
		}
	}
	BigInt::BigInt(const BigInt &a)
	{
		digits = a.digits;
	}

	bool Null(const BigInt &a)
	{
		if (a.digits.size() == 1 && a.digits[0] == 0)
			return true;
		return false;
	}
	int Length(const BigInt &a)
	{
		return a.digits.size();
	}
	int BigInt::operator[](const int index) const
	{
		if (digits.size() <= index || index < 0)
			throw("ERROR");
		return digits[index];
	}
	bool operator==(const BigInt &a, const BigInt &b)
	{
		return a.digits == b.digits;
	}
	bool operator!=(const BigInt &a, const BigInt &b)
	{
		return !(a == b);
	}
	bool operator<(const BigInt &a, const BigInt &b)
	{
		int n = Length(a), m = Length(b);
		if (n != m)
			return n < m;
		while (n--)
			if (a.digits[n] != b.digits[n])
				return a.digits[n] < b.digits[n];
		return false;
	}
	bool operator>(const BigInt &a, const BigInt &b)
	{
		return b < a;
	}
	bool operator>=(const BigInt &a, const BigInt &b)
	{
		return !(a < b);
	}
	bool operator<=(const BigInt &a, const BigInt &b)
	{
		return !(a > b);
	}

	BigInt &BigInt::operator=(const BigInt &a)
	{
		digits = a.digits;
		return *this;
	}

	BigInt &BigInt::operator++()
	{
		int i, n = digits.size();
		for (i = 0; i < n && digits[i] == 9; i++)
			digits[i] = 0;
		if (i == n)
			digits.push_back(1);
		else
			digits[i]++;
		return *this;
	}
	BigInt BigInt::operator++(int temp)
	{
		BigInt aux;
		aux = *this;
		++(*this);
		return aux;
	}

	BigInt &BigInt::operator--()
	{
		if (digits[0] == 0 && digits.size() == 1)
			throw("UNDERFLOW");
		int i, n = digits.size();
		for (i = 0; digits[i] == 0 && i < n; i++)
			digits[i] = 9;
		digits[i]--;
		if (n > 1 && digits[n - 1] == 0)
			digits.pop_back();
		return *this;
	}
	BigInt BigInt::operator--(int temp)
	{
		BigInt aux;
		aux = *this;
		--(*this);
		return aux;
	}

	BigInt &operator+=(BigInt &a, const BigInt &b)
	{
		int t = 0, s, i;
		int n = Length(a), m = Length(b);
		if (m > n)
			a.digits.append(m - n, 0);
		n = Length(a);
		for (i = 0; i < n; i++)
		{
			if (i < m)
				s = (a.digits[i] + b.digits[i]) + t;
			else
				s = a.digits[i] + t;
			t = s / 10;
			a.digits[i] = (s % 10);
		}
		if (t)
			a.digits.push_back(t);
		return a;
	}
	BigInt operator+(const BigInt &a, const BigInt &b)
	{
		BigInt temp;
		temp = a;
		temp += b;
		return temp;
	}

	BigInt &operator-=(BigInt &a, const BigInt &b)
	{
		if (a < b)
			throw("UNDERFLOW");
		int n = Length(a), m = Length(b);
		int i, t = 0, s;
		for (i = 0; i < n; i++)
		{
			if (i < m)
				s = a.digits[i] - b.digits[i] + t;
			else
				s = a.digits[i] + t;
			if (s < 0)
				s += 10,
					t = -1;
			else
				t = 0;
			a.digits[i] = s;
		}
		while (n > 1 && a.digits[n - 1] == 0)
			a.digits.pop_back(),
				n--;
		return a;
	}
	BigInt operator-(const BigInt &a, const BigInt &b)
	{
		BigInt temp;
		temp = a;
		temp -= b;
		return temp;
	}

	BigInt &operator*=(BigInt &a, const BigInt &b)
	{
		if (Null(a) || Null(b))
		{
			a = BigInt();
			return a;
		}
		int n = a.digits.size(), m = b.digits.size();
		vector<int> v(n + m, 0);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
			{
				v[i + j] += (a.digits[i]) * (b.digits[j]);
			}
		n += m;
		a.digits.resize(v.size());
		for (int s, i = 0, t = 0; i < n; i++)
		{
			s = t + v[i];
			v[i] = s % 10;
			t = s / 10;
			a.digits[i] = v[i];
		}
		for (int i = n - 1; i >= 1 && !v[i]; i--)
			a.digits.pop_back();
		return a;
	}
	BigInt operator*(const BigInt &a, const BigInt &b)
	{
		BigInt temp;
		temp = a;
		temp *= b;
		return temp;
	}

	BigInt &operator/=(BigInt &a, const BigInt &b)
	{
		if (Null(b))
			throw("Arithmetic Error: Division By 0");
		if (a < b)
		{
			a = BigInt();
			return a;
		}
		if (a == b)
		{
			a = BigInt(1);
			return a;
		}
		int i, lgcat = 0, cc;
		int n = Length(a); //, m = Length(b);
		vector<int> cat(n, 0);
		BigInt t;
		for (i = n - 1; t * 10 + a.digits[i] < b; i--)
		{
			t *= 10;
			t += a.digits[i];
		}
		for (; i >= 0; i--)
		{
			t = t * 10 + a.digits[i];
			for (cc = 9; cc * b > t; cc--)
				;
			t -= cc * b;
			cat[lgcat++] = cc;
		}
		a.digits.resize(cat.size());
		for (i = 0; i < lgcat; i++)
			a.digits[i] = cat[lgcat - i - 1];
		a.digits.resize(lgcat);
		return a;
	}
	BigInt operator/(const BigInt &a, const BigInt &b)
	{
		BigInt temp;
		temp = a;
		temp /= b;
		return temp;
	}

	BigInt &operator%=(BigInt &a, const BigInt &b)
	{
		if (Null(b))
			throw("Arithmetic Error: Division By 0");
		if (a < b)
		{
			return a;
		}
		if (a == b)
		{
			a = BigInt();
			return a;
		}
		int i, lgcat = 0, cc;
		int n = Length(a); //, m = Length(b);
		vector<int> cat(n, 0);
		BigInt t;
		for (i = n - 1; t * 10 + a.digits[i] < b; i--)
		{
			t *= 10;
			t += a.digits[i];
		}
		for (; i >= 0; i--)
		{
			t = t * 10 + a.digits[i];
			for (cc = 9; cc * b > t; cc--)
				;
			t -= cc * b;
			cat[lgcat++] = cc;
		}
		a = t;
		return a;
	}
	BigInt operator%(const BigInt &a, const BigInt &b)
	{
		BigInt temp;
		temp = a;
		temp %= b;
		return temp;
	}

	BigInt &operator^=(BigInt &a, const BigInt &b)
	{
		BigInt Exponent, Base(a);
		Exponent = b;
		a = 1;
		while (!Null(Exponent))
		{
			if (Exponent[0] & 1)
				a *= Base;
			Base *= Base;
			divide_by_2(Exponent);
		}
		return a;
	}
	BigInt operator^(BigInt &a, BigInt &b)
	{
		BigInt temp(a);
		temp ^= b;
		return temp;
	}

	void divide_by_2(BigInt &a)
	{
		int add = 0;
		for (int i = a.digits.size() - 1; i >= 0; i--)
		{
			int digit = (a.digits[i] >> 1) + add;
			add = ((a.digits[i] & 1) * 5);
			a.digits[i] = digit;
		}
		while (a.digits.size() > 1 && !a.digits.back())
			a.digits.pop_back();
	}

	BigInt sqrt(BigInt &a)
	{
		BigInt left(1), right(a), v(1), mid, prod;
		divide_by_2(right);
		while (left <= right)
		{
			mid += left;
			mid += right;
			divide_by_2(mid);
			prod = (mid * mid);
			if (prod <= a)
			{
				v = mid;
				++mid;
				left = mid;
			}
			else
			{
				--mid;
				right = mid;
			}
			mid = BigInt();
		}
		return v;
	}

	BigInt NthCatalan(int n)
	{
		BigInt a(1), b;
		for (int i = 2; i <= n; i++)
			a *= i;
		b = a;
		for (int i = n + 1; i <= 2 * n; i++)
			b *= i;
		a *= a;
		a *= (n + 1);
		b /= a;
		return b;
	}

	BigInt NthFibonacci(int n)
	{
		BigInt a(1), b(1), c;
		if (!n)
			return c;
		n--;
		while (n--)
		{
			c = a + b;
			b = a;
			a = c;
		}
		return b;
	}

	BigInt Factorial(int n)
	{
		BigInt f(1);
		for (int i = 2; i <= n; i++)
			f *= i;
		return f;
	}

	istream &operator>>(istream &in, BigInt &a)
	{
		string s;
		in >> s;
		int n = s.size();
		for (int i = n - 1; i >= 0; i--)
		{
			if (!isdigit(s[i]))
				throw("INVALID NUMBER");
			a.digits[n - i - 1] = s[i];
		}
		return in;
	}

	ostream &operator<<(ostream &out, const BigInt &a)
	{
		for (int i = a.digits.size() - 1; i >= 0; i--)
			out << (short)a.digits[i];
		return out;
	}

}
namespace CBigInt
{

// This code is a C implementation of a BigInt library using u64
// to represent large integers. It includes functions for
// initialization, addition, multiplication, division, and printing
// as string. It also includes a function to convert a string
// representation of a number into a BigInt. The library is
// designed to handle very large integers that cannot be
// represented by standard data types like int or long long.
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>

#define CHUNK_BASE 1000000000ULL
#define CHUNK_DIGITS 9
#define BASE 10

	typedef unsigned long long u64;
	const u64 MAX_BASE = UINT64_MAX;

	typedef struct
	{
		u64 *limbs;
		int size;
		int capacity;
		int sign;
	} BigInt;

	// ---------- Memory Helpers ----------
	void bigint_reserve(BigInt *num, int required)
	{
		if (required <= num->capacity)
			return;

		int new_cap = (num->capacity > 0) ? num->capacity * 2 : 4;
		while (new_cap < required)
			new_cap *= 2;

		num->limbs = (u64 *)realloc(num->limbs, new_cap * sizeof(u64));
		if (!num->limbs)
		{
			fprintf(stderr, "Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		memset(num->limbs + num->capacity, 0, (new_cap - num->capacity) * sizeof(u64));
		num->capacity = new_cap;
	}

	void bigint_free(BigInt *num)
	{
		if (num->limbs)
		{
			free(num->limbs);
			num->limbs = NULL;
		}
		num->size = 0;
		num->capacity = 0;
		num->sign = 0;
	}

	void bigint_copy(BigInt *dst, const BigInt *src)
	{
		bigint_reserve(dst, src->size);
		memcpy(dst->limbs, src->limbs, src->size * sizeof(u64));
		dst->size = src->size;
		dst->sign = src->sign;
	}

	// ---------- Initialization ----------
	void bigint_init(BigInt *num, long long value)
	{
		num->limbs = NULL;
		num->size = 0;
		num->capacity = 0;
		num->sign = 0;
		bigint_reserve(num, 1);

		num->limbs[0] = (u64)((value < 0) ? -value : value);
		num->size = (value != 0) ? 1 : 0;
		num->sign = (value < 0) ? -1 : 1;
	}

	// ---------- Basic Utilities ----------
	int bigint_compare(const BigInt *a, const BigInt *b)
	{
		if (a->sign != b->sign)
			return (a->sign < b->sign) ? -1 : 1;
		if (a->size != b->size)
			return (a->size < b->size) ? -1 : 1;

		for (int i = a->size - 1; i >= 0; --i)
		{
			if (a->limbs[i] != b->limbs[i])
				return (a->limbs[i] < b->limbs[i]) ? -1 : 1;
		}
		return 0;
	}

	// ---------- Arithmetic ----------
	void bigint_add(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_subtract(const BigInt *a, const BigInt *b, BigInt *result);

	void bigint_add_u64(const BigInt *a, u64 b, BigInt *result)
	{
		bigint_copy(result, a);
		bigint_reserve(result, result->size + 1);

		u64 carry = b;
		for (int i = 0; i < result->size && carry > 0; ++i)
		{
			u64 sum = result->limbs[i] + carry;
			carry = (sum < result->limbs[i]) ? 1 : 0;
			result->limbs[i] = sum;
		}
		if (carry > 0)
		{
			result->limbs[result->size++] = carry;
		}
	}

	void bigint_multiply_u64(const BigInt *a, u64 b, BigInt *result)
	{
		if (b == 0 || a->size == 0)
		{
			bigint_reserve(result, 1);
			result->limbs[0] = 0;
			result->size = 1;
			result->sign = 0;
			return;
		}

		bigint_reserve(result, a->size + 1);
		u64 carry = 0;
		for (int i = 0; i < a->size; ++i)
		{
			__uint128_t prod = (__uint128_t)a->limbs[i] * b + carry;
			result->limbs[i] = (u64)prod;
			carry = (u64)(prod >> 64);
		}
		if (carry)
		{
			result->limbs[a->size] = carry;
			result->size = a->size + 1;
		}
		else
		{
			result->size = a->size;
		}
		result->sign = a->sign;
	}

	void bigint_subtract(const BigInt *a, const BigInt *b, BigInt *result)
	{
		BigInt temp_a, temp_b;
		bigint_init(&temp_a, 0);
		bigint_init(&temp_b, 0);
		bigint_copy(&temp_a, a);
		bigint_copy(&temp_b, b);
		temp_a.sign = temp_b.sign = 1;

		if (bigint_compare(&temp_a, &temp_b) < 0)
		{
			bigint_subtract(&temp_b, &temp_a, result);
			result->sign = -1;
			bigint_free(&temp_a);
			bigint_free(&temp_b);
			return;
		}

		bigint_reserve(result, a->size);
		u64 borrow = 0;
		for (int i = 0; i < a->size; ++i)
		{
			__int128 diff = (__int128)a->limbs[i] -
							(i < b->size ? b->limbs[i] : 0) - borrow;
			borrow = (diff < 0) ? 1 : 0;
			diff += borrow * ((__int128)1 << 64);
			result->limbs[i] = (u64)diff;
		}
		result->size = a->size;
		while (result->size > 1 && result->limbs[result->size - 1] == 0)
			result->size--;
		result->sign = 1;

		bigint_free(&temp_a);
		bigint_free(&temp_b);
	}

	void bigint_add(const BigInt *a, const BigInt *b, BigInt *result)
	{
		if (a->size == 0)
		{
			bigint_copy(result, b);
			return;
		}
		if (b->size == 0)
		{
			bigint_copy(result, a);
			return;
		}

		if (a->sign == 1 && b->sign == -1)
		{
			BigInt temp;
			bigint_init(&temp, 0);
			bigint_copy(&temp, b);
			temp.sign = 1;
			bigint_subtract(a, &temp, result);
			bigint_free(&temp);
			return;
		}
		if (a->sign == -1 && b->sign == 1)
		{
			BigInt temp;
			bigint_init(&temp, 0);
			bigint_copy(&temp, a);
			temp.sign = 1;
			bigint_subtract(b, &temp, result);
			bigint_free(&temp);
			return;
		}
		if (a->sign == -1 && b->sign == -1)
		{
			BigInt temp;
			bigint_init(&temp, 0);
			temp.sign = 1;
			bigint_add(a, b, &temp);
			temp.sign = -1;
			bigint_copy(result, &temp);
			bigint_free(&temp);
			return;
		}

		int max_size = (a->size > b->size) ? a->size : b->size;
		bigint_reserve(result, max_size + 1);

		u64 carry = 0;
		int i;
		for (i = 0; i < max_size; ++i)
		{
			__uint128_t sum = (__uint128_t)(i < a->size ? a->limbs[i] : 0) +
							  (i < b->size ? b->limbs[i] : 0) + carry;
			result->limbs[i] = (u64)sum;
			carry = (u64)(sum >> 64);
		}
		if (carry)
			result->limbs[i++] = carry;
		result->size = i;
		result->sign = 1;
	}

	// ---------- Multiplication ----------
	void bigint_multiply(const BigInt *a, const BigInt *b, BigInt *result)
	{
		if (a->size == 0 || b->size == 0 || (a->size == 1 && a->limbs[0] == 0) || (b->size == 1 && b->limbs[0] == 0))
		{
			bigint_reserve(result, 1);
			result->limbs[0] = 0;
			result->size = 1;
			result->sign = 0;
			return;
		}

		int result_size = a->size + b->size;
		bigint_reserve(result, result_size);
		memset(result->limbs, 0, result_size * sizeof(u64));
		result->size = result_size;
		result->sign = (a->sign == b->sign) ? 1 : -1;

		for (int i = 0; i < a->size; i++)
		{
			u64 carry = 0;
			for (int j = 0; j < b->size || carry > 0; j++)
			{
				__uint128_t product = (__uint128_t)a->limbs[i] *
										  (j < b->size ? b->limbs[j] : 0) +
									  result->limbs[i + j] + carry;
				result->limbs[i + j] = (u64)product;
				carry = (u64)(product >> 64);
			}
		}

		while (result->size > 1 && result->limbs[result->size - 1] == 0)
			result->size--;
	}

	// ---------- Shift Left ----------
	void bigint_shift_left(BigInt *num, int bits)
	{
		if (bits == 0 || num->size == 0)
			return;

		int limb_shift = bits / 64;
		int bit_shift = bits % 64;

		int new_size = num->size + limb_shift + (bit_shift ? 1 : 0);
		bigint_reserve(num, new_size);

		if (limb_shift > 0)
		{
			memmove(num->limbs + limb_shift, num->limbs, num->size * sizeof(u64));
			memset(num->limbs, 0, limb_shift * sizeof(u64));
		}
		if (bit_shift > 0)
		{
			u64 carry = 0;
			for (int i = limb_shift; i < new_size; ++i)
			{
				u64 current = num->limbs[i];
				num->limbs[i] = (current << bit_shift) | carry;
				carry = current >> (64 - bit_shift);
			}
			if (carry)
			{
				bigint_reserve(num, new_size + 1);
				num->limbs[new_size++] = carry;
			}
		}
		num->size = new_size;
		while (num->size > 1 && num->limbs[num->size - 1] == 0)
			num->size--;
	}

	// ---------- Divide by u64 ----------
	void bigint_divide_u64(const BigInt *input, u64 divisor, BigInt *quotient, u64 *remainder)
	{
		if (divisor == 0)
		{
			fprintf(stderr, "Error: division by zero in bigint_divide_u64\n");
			exit(EXIT_FAILURE);
		}
	
		// Fast path: divisor is 1
		if (divisor == 1)
		{
			bigint_copy(quotient, input);
			*remainder = 0;
			return;
		}
	
		// Early exit for small input
		if (input->size == 1)
		{
			bigint_reserve(quotient, 1);
			quotient->limbs[0] = input->limbs[0] / divisor;
			*remainder = input->limbs[0] % divisor;
			quotient->size = (quotient->limbs[0] != 0) ? 1 : 0;
			quotient->sign = input->sign;
			return;
		}
	
		// 🛠️ Allocate quotient limbs BEFORE use!
		bigint_reserve(quotient, input->size);
		memset(quotient->limbs, 0, sizeof(u64) * input->size);
		quotient->size = input->size;
		quotient->sign = input->sign;
	
		u64 rem = 0;
		int new_size = 0;
	
		for (int i = input->size - 1; i >= 0; i--)
		{
			__uint128_t dividend = ((__uint128_t)rem << 64) | input->limbs[i];
			quotient->limbs[i] = dividend / divisor;
			rem = dividend % divisor;
	
			if (quotient->limbs[i] != 0 && new_size == 0)
				new_size = i + 1;
		}
	
		quotient->size = (new_size == 0) ? 1 : new_size;
		*remainder = rem;
	}
	

	// ---------- From String ----------
	void bigint_from_string(BigInt *num, const char *str)
	{
		while (*str == ' ')
			str++;

		int sign = 1;
		if (*str == '-')
		{
			sign = -1;
			++str;
		}
		while (*str == ' ')
			str++;

		bigint_init(num, 0);
		size_t len = strlen(str);
		size_t start = (len % CHUNK_DIGITS == 0) ? CHUNK_DIGITS : len % CHUNK_DIGITS;

		char chunk_str[CHUNK_DIGITS + 1] = {0};
		u64 chunk;

		if (start > 0)
		{
			memcpy(chunk_str, str, start);
			chunk_str[start] = '\0';
			chunk = strtoull(chunk_str, NULL, 10);
			bigint_add_u64(num, chunk, num);
		}

		for (size_t i = start; i < len; i += CHUNK_DIGITS)
		{
			bigint_multiply_u64(num, CHUNK_BASE, num);
			memcpy(chunk_str, str + i, CHUNK_DIGITS);
			chunk_str[CHUNK_DIGITS] = '\0';
			chunk = strtoull(chunk_str, NULL, 10);
			bigint_add_u64(num, chunk, num);
		}

		num->sign = sign;
	}
	char *to_string(const BigInt *num)
	{
		if (num->size == 0 || (num->size == 1 && num->limbs[0] == 0))
			return strdup("0");

		// Estimate number of digits: log10(2) ≈ 0.30103
		int max_digits = (int)(num->size * 64 * 0.30103) + 2;
		char *buffer = (char *)malloc(max_digits);
		if (!buffer)
		{
			fprintf(stderr, "Failed to allocate buffer for BigInt string\n");
			exit(EXIT_FAILURE);
		}

		int index = 0;
		BigInt temp, quotient;
		bigint_init(&temp, 0);
		bigint_init(&quotient, 0);  // 👈 this ensures limbs = NULL, capacity = 0
		bigint_copy(&temp, num);

		u64 rem;
		while (!(temp.size == 1 && temp.limbs[0] == 0))
		{
			bigint_reserve(&quotient, temp.size);
			bigint_divide_u64(&temp, 10, &quotient, &rem);
			if (index >= max_digits - 1)
			{
				max_digits *= 2;
				buffer = (char *)realloc(buffer, max_digits);
				if (!buffer)
				{
					fprintf(stderr, "Realloc failed in to_string\n");
					exit(EXIT_FAILURE);
				}
			}
			buffer[index++] = '0' + rem;
			bigint_copy(&temp, &quotient);
		}

		if (num->sign < 0)
		{
			buffer[index++] = '-';
		}

		// Reverse the digits
		for (int i = 0; i < index / 2; ++i)
		{
			char tmp = buffer[i];
			buffer[i] = buffer[index - i - 1];
			buffer[index - i - 1] = tmp;
		}

		buffer[index] = '\0';

		bigint_free(&temp);
		bigint_free(&quotient);

		return buffer; // Caller must free()
	}

	void bigint_print(const BigInt *num)
	{
		char *str = to_string(num);
		printf("%s", str);
		free(str);
	}
}

#include <sstream>
std::string to_string(const CPPBigInt::BigInt &num)
{
	std::ostringstream oss;
	oss << num;
	return oss.str();
}
#include <gmp.h>
// Subfunction to test CBigInt
bool testC(std::string s1, std::string s2)
{
	// ---------- Using CBigInt ----------
	CBigInt::BigInt aC, bC, sumC, prodC;
	CBigInt::bigint_from_string(&aC, s1.c_str());
	CBigInt::bigint_from_string(&bC, s2.c_str());
	CBigInt::bigint_init(&sumC, 0);
	CBigInt::bigint_init(&prodC, 0);

	// Calculate addition and multiplication
	CBigInt::bigint_add(&aC, &bC, &sumC);
	CBigInt::bigint_multiply(&aC, &bC, &prodC);

	// Convert CBigInt to GMP (mpz_t)
	mpz_t sumC_GMP, prodC_GMP;
	mpz_init(sumC_GMP);
	mpz_init(prodC_GMP);

	// Convert sumC to GMP
	char *sumC_str = CBigInt::to_string(&sumC);
	mpz_set_str(sumC_GMP, sumC_str, 10);
	free(sumC_str);

	// Convert prodC to GMP
	char *prodC_str = CBigInt::to_string(&prodC);
	mpz_set_str(prodC_GMP, prodC_str, 10);
	free(prodC_str);

	// ---------- Using GMP for Validation ----------
	mpz_t aGMP, bGMP, sumGMP, prodGMP;
	mpz_init(aGMP);
	mpz_init(bGMP);
	mpz_init(sumGMP);
	mpz_init(prodGMP);

	// Set GMP variables from input strings
	if (mpz_set_str(aGMP, s1.c_str(), 10) != 0 || mpz_set_str(bGMP, s2.c_str(), 10) != 0)
	{
		std::cerr << "Error: Invalid number format for GMP." << std::endl;
		mpz_clear(aGMP);
		mpz_clear(bGMP);
		mpz_clear(sumGMP);
		mpz_clear(prodGMP);
		return false;
	}

	// Perform GMP addition and multiplication
	mpz_add(sumGMP, aGMP, bGMP);
	mpz_mul(prodGMP, aGMP, bGMP);

	// ---------- Validation ----------
	bool valid = true;
	// Compare GMP sum with CBigInt sum (using mpz_cmp)
	if (mpz_cmp(sumGMP, sumC_GMP) != 0)
	{
		std::cerr << "Validation failed: GMP sum does not match CBigInt sum!" << sumC_str << "\n";
		valid = false;
	}
	// Compare GMP product with CBigInt product (using mpz_cmp)
	if (mpz_cmp(prodGMP, prodC_GMP) != 0)
	{ 
		std::cerr << "Validation failed: GMP product does not match CBigInt product!" << prodC_str << "\n";
		valid = false;
	}

	// Clean up GMP memory
	mpz_clear(aGMP);
	mpz_clear(bGMP);
	mpz_clear(sumGMP);
	mpz_clear(prodGMP);
	mpz_clear(sumC_GMP);
	mpz_clear(prodC_GMP);

	return valid;
}

// Subfunction to test CPPBigInt::BigInt
bool testCPP(std::string s1, std::string s2)
{
	// ---------- Using CPPBigInt ----------
	CPPBigInt::BigInt aCPP(s1), bCPP(s2);
	CPPBigInt::BigInt sumCPP = aCPP + bCPP;
	CPPBigInt::BigInt prodCPP = aCPP * bCPP;

	mpz_t sumCPP_GMP, prodCPP_GMP;
	mpz_init(sumCPP_GMP);
	mpz_init(prodCPP_GMP);

	// Convert sumCPP to GMP
	char *sumCPP_str = strdup(to_string(sumCPP).c_str());
	mpz_set_str(sumCPP_GMP, sumCPP_str, 10);
	free(sumCPP_str);

	// Convert prodCPP to GMP
	char *prodCPP_str = strdup(to_string(prodCPP).c_str());
	mpz_set_str(prodCPP_GMP, prodCPP_str, 10);
	free(prodCPP_str);

	// ---------- Using GMP for Validation ----------
	mpz_t aGMP, bGMP, sumGMP, prodGMP;
	mpz_init(aGMP);
	mpz_init(bGMP);
	mpz_init(sumGMP);
	mpz_init(prodGMP);

	// Set GMP variables from input strings
	if (mpz_set_str(aGMP, s1.c_str(), 10) != 0 || mpz_set_str(bGMP, s2.c_str(), 10) != 0)
	{
		std::cerr << "Error: Invalid number format for GMP." << std::endl;
		mpz_clear(aGMP);
		mpz_clear(bGMP);
		mpz_clear(sumGMP);
		mpz_clear(prodGMP);
		return false;
	}

	// Perform GMP addition and multiplication
	mpz_add(sumGMP, aGMP, bGMP);
	mpz_mul(prodGMP, aGMP, bGMP);

	// ---------- Validation ----------
	bool valid = true;
	// Compare GMP sum with CPPBigInt sum (using mpz_cmp)
	if (mpz_cmp(sumGMP, sumCPP_GMP) != 0)
	{
		std::cerr << "Validation failed: GMP sum does not match CPPBigInt::BigInt sum!" << std::endl;
		valid = false;
	}
	// Compare GMP product with CPPBigInt product (using mpz_cmp)
	if (mpz_cmp(prodGMP, prodCPP_GMP) != 0)
	{
		std::cerr << "Validation failed: GMP product does not match CPPBigInt::BigInt product!" << std::endl;
		valid = false;
	}

	// Clean up GMP memory
	mpz_clear(aGMP);
	mpz_clear(bGMP);
	mpz_clear(sumGMP);
	mpz_clear(prodGMP);
	mpz_clear(sumCPP_GMP);
	mpz_clear(prodCPP_GMP);

	return valid;
}

#include <iostream>
#include <string>
#include <random>
#include <ctime>

std::random_device rd;
std::mt19937 gen(rd());					   // Random number generator based on random_device
std::uniform_int_distribution<> dis(0, 9); // Random digits 0-9
										   /*
											   bool isNegative = 0; // Randomly decide if the number is negative
										   
											   if (isNegative)
											   {
												   number += '-';
											   }
										   */
// Function to generate a random big number as a string, positive or negative
std::string generateRandomBigNumber(size_t length)
{
	std::string number;
	// Generate the big number
	for (size_t i = 0; i < length; ++i)
	{
		number += std::to_string(dis(gen));
	}

	return number;
}

int main()
{
	std::vector<std::pair<std::string, std::string>> tests(1);
	for (int i = 0; i < 1; i++)
	{
		// Generate two big numbers (with 50 digits)
		tests[i] = {generateRandomBigNumber(5423), generateRandomBigNumber(5345)};
	}
	bool C = true, CPP = true;
	for (auto &[num1, num2] : tests)
	{
		// Call the test function with the big numbers
		if (!testC(num1, num2))
		{
			std::cout << "Test failed for numbers: " << num1 << " and " << num2 << " with engine CBigInt\n";
			C = false;
		}
		// Call the test function with the big numbers
		if (!testCPP(num1, num2))
		{
			std::cout << "Test failed for numbers: " << num1 << " and " << num2 << " with engine CPPBigInt::BigInt\n";
			CPP = false;
		}
	}
	if (C)
		std::cout << "All tests passed for engine CBigInt!" << '\n';
	else
	{
		std::cout << "Some tests failed for engine CBigInt!" << '\n';
		return 1;
	}
	if (CPP)
	{
		std::cout << "All tests passed for engine CPPBigInt::BigInt!" << '\n';
	}
	else
	{
		std::cout << "Some tests failed for engine CPPBigInt::BigInt!" << '\n';
		return 1;
	}
	// Performance benchmarking
	std::clock_t start, end;

	// Benchmark GMP
	start = std::clock();
	for (auto &[num1, num2] : tests)
	{
		mpz_t aGMP, bGMP, sumGMP, prodGMP;
		mpz_init(aGMP);
		mpz_init(bGMP);
		mpz_init(sumGMP);
		mpz_init(prodGMP);

		mpz_set_str(aGMP, num1.c_str(), 10);
		mpz_set_str(bGMP, num2.c_str(), 10);

		mpz_add(sumGMP, aGMP, bGMP);
		mpz_mul(prodGMP, aGMP, bGMP);

		mpz_clear(aGMP);
		mpz_clear(bGMP);
		mpz_clear(sumGMP);
		mpz_clear(prodGMP);
	}
	end = std::clock();
	std::cout << "GMP Benchmark: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " ms\n";

	// Benchmark CBigInt
	start = std::clock();
	for (auto &[num1, num2] : tests)
	{
		CBigInt::BigInt aC, bC, sumC, prodC;
		CBigInt::bigint_init(&sumC, 0);
		CBigInt::bigint_init(&prodC, 0);
		CBigInt::bigint_from_string(&aC, num1.c_str());
		CBigInt::bigint_from_string(&bC, num2.c_str());
		CBigInt::bigint_add(&aC, &bC, &sumC);
		CBigInt::bigint_multiply(&aC, &bC, &prodC);
	}
	end = std::clock();
	std::cout << "CBigInt Benchmark: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " ms\n";

	// Benchmark CPPBigInt
	start = std::clock();
	for (auto &[num1, num2] : tests)
	{
		CPPBigInt::BigInt aCPP(num1), bCPP(num2);
		CPPBigInt::BigInt sumCPP = aCPP + bCPP;
		CPPBigInt::BigInt prodCPP = aCPP * bCPP;
	}
	end = std::clock();
	std::cout << "CPPBigInt Benchmark: " << 1000.0 * (end - start) / CLOCKS_PER_SEC << " ms\n";
	return 0;
}
/*
CBigInt: Suitable for very large numbers.
CPPBigInt: Suitable for small-large numbers and for beginners.
GMP: For performance and very very large numbers (as it's insanely optimized by algorithms and widely used for big number computation).
Test for both addition and multiplication of 5423 and 5345 digits number (100% CPU):
```
All tests passed for engine CBigInt!
All tests passed for engine CPPBigInt::BigInt!
GMP Benchmark: 0.041 ms
CBigInt Benchmark: 1.807 ms
CPPBigInt Benchmark: 516.056 ms
```
Proof:
```c++
	std::vector<std::pair<std::string, std::string>> tests(1);
	for (int i = 0; i < 1; i++)
	{
		// Generate two big numbers (with 50 digits)
		tests[i] = {generateRandomBigNumber(5423), generateRandomBigNumber(5345)};
	}
```
*/
/*
Old CBigInt
namespace CBigInt
{

// This code is a C implementation of a BigInt library using u64
// to represent large integers. It includes functions for
// initialization, addition, multiplication, division, and conversion
// between bases. The library supports numbers up to 8192 bits
// (128 limbs of 64 bits each). The code is designed to be efficient
// and handles various edge cases, such as division by zero and
// negative numbers. The library also includes functions for
// converting numbers to binary strings and printing them in
// different bases. The implementation is modular and can be
// easily extended to include more operations or features.
// winapiadmin and AI (contributed by AI)
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <inttypes.h>	 // for PRIu64
#define MAX_LIMBS 1024	 // Supports large numbers (~65536-bit)
#define BASE 10			 // Base-10^9 (for easy printing)
#define MAX_DIGITS 20000 // Maximum number of decimal digits (logically math.log10(2**65536)=19728.3 rounded up to 20000)

	typedef unsigned long long u64;
	const u64 MAX_BASE = UINT64_MAX;
	const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	typedef struct
	{
		u64 limbs[MAX_LIMBS];
		int size; // Number of used limbs
		int sign; // 1 for positive, -1 for negative, 0 for zero
	} BigInt;
	// Optimized BigInt initialization function
	void bigint_init(BigInt *num, long long value)
	{
		// Clear only the required fields (limbs and size/sign)
		num->limbs[0] = (unsigned long long)(value < 0 ? -value : value);
		num->size = (value != 0) ? 1 : 0; // Size is 1 if the number is non-zero, 0 if zero
		num->sign = (value < 0) ? -1 : 1; // Set the sign based on the value
	}

	void bigint_add(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_subtract(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_multiply(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_divide(const BigInt *a, const BigInt *b, BigInt *quotient, BigInt *remainder);
	int bigint_compare(const BigInt *a, const BigInt *b);
	// Helper function to shift a BigInt left by a specified number of bits
	void bigint_shift_left(BigInt *num, int bits)
	{
		if (bits == 0 || num->size == 0) return;

		int limb_shift = bits >> 8;  // Note: check if this calculation is intended (or should be bits / 64)
		int bit_shift = bits & 63;

		// Use memmove to shift limbs
		memmove(num->limbs + limb_shift, num->limbs, num->size * sizeof(u64));
		memset(num->limbs, 0, limb_shift * sizeof(u64));

		if (bit_shift > 0)
		{
			for (int i = num->size + limb_shift; i > 0; i--)
			{
				num->limbs[i] = (num->limbs[i] << bit_shift) | (num->limbs[i - 1] >> (64 - bit_shift));
			}
			num->limbs[0] <<= bit_shift;
		}

		num->size += limb_shift;
		if (num->limbs[num->size - 1] == 0)
			num->size--;
	}
	void bigint_divide_u64(const BigInt *input, u64 divisor, BigInt *quotient, u64 *remainder)
	{
		// Handle division by zero if necessary (assumes divisor != 0)
		if (divisor == 0) return;
	
		// Fast path: divisor is 1
		if (divisor == 1) {
			if (quotient != input) *quotient = *input;
			*remainder = 0;
			return;
		}
	
		// Power-of-two fast path
		if ((divisor & (divisor - 1)) == 0) {
			const int shift = __builtin_ctzll(divisor);
			const u64 mask = divisor - 1;
			u64 carry = 0;
			int new_size = 0;
	
			quotient->sign = input->sign;
			
			for (int i = input->size - 1; i >= 0; i--) {
				const u64 limb = input->limbs[i];
				quotient->limbs[i] = (carry << (64 - shift)) | (limb >> shift);
				carry = limb & mask;
				
				if (quotient->limbs[i] != 0 && i >= new_size) {
					new_size = i + 1;
				}
			}
			
			quotient->size = new_size ? new_size : 1;
			*remainder = carry;
			return;
		}
	
		// Early exit for small inputs (single limb)
		if (input->size == 1) {
			quotient->limbs[0] = input->limbs[0] / divisor;
			*remainder = input->limbs[0] % divisor;
			quotient->size = (quotient->limbs[0] == 0) ? 1 : 1;
			quotient->sign = input->sign;
			return;
		}
	
		// General case optimized with hardware division hints
		quotient->sign = input->sign;
		u64 rem = 0;
		int new_size = 0;
	
		// Process limbs in reverse order (MSB to LSB)
		for (int i = input->size - 1; i >= 0; i--) {
			// Use union for explicit 128-bit control
			__uint128_t dividend;
			dividend = (__uint128_t)rem<<64|input->limbs[i];
			
			quotient->limbs[i] = dividend / divisor;
			rem = dividend % divisor;
	
			// Track highest non-zero limb
			if (!new_size && quotient->limbs[i] != 0) {
				new_size = i + 1;
			}
		}
	
		quotient->size = new_size ? new_size : 1;
		*remainder = rem;
	}
	char *to_string(const BigInt *num)
	{
		if (num->size == 0 || (num->size == 1 && num->limbs[0] == 0))
		{
			return strdup("0");
		}
		static char buffer[MAX_DIGITS + 2]; // Static buffer to avoid dynamic allocation
		int index = 0;

		BigInt temp;
		memcpy(&temp, num, sizeof(BigInt));

		u64 rem;
		BigInt quotient;

		while (!(temp.size == 1 && temp.limbs[0] == 0))
		{
			bigint_divide_u64(&temp, 10, &quotient, &rem);
			buffer[index++] = '0' + rem;
			temp = quotient;
		}

		if (num->sign < 0)
		{
			buffer[index++] = '-';
		}

		// Reverse the result
		{
			char* left = buffer;
			char* right = buffer + index - 1;
			while (left < right) {
				char tmp = *left;
				*left++ = *right;
				*right-- = tmp;
			}
		}

		buffer[index] = '\0';
		return strdup(buffer);
	}

	// Print BigInt in base 10 or any other base
	void bigint_print(const BigInt *num)
	{
		char *result_str = to_string(num);
		printf("%s", result_str);
		free(result_str);
	}

	// Helper function to compare two BigInts: returns -1 if a < b, 0 if equal, 1 if a > b.
	int bigint_compare(const BigInt *a, const BigInt *b)
	{
		if (a->sign < 0 && b->sign > 0)
			return -1;
		if (a->sign > 0 && b->sign < 0)
			return 1;
		if (a->sign == 0 && b->sign == 0)
			return 0;
		if (a->size != b->size)
			return (a->size < b->size) ? -1 : 1;
		for (int i = a->size - 1; i >= 0; i--)
		{
			if (a->limbs[i] != b->limbs[i])
				return (a->limbs[i] < b->limbs[i]) ? -1 : 1;
		}
		return 0;
	}
	// Subtract two BigInts
	void bigint_subtract(const BigInt *a, const BigInt *b, BigInt *result)
	{
		if (a->size == 0)
		{
			memcpy(result, b, sizeof(BigInt));
			result->sign = -1;
			return;
		}

		if (b->size == 0)
		{
			memcpy(result, a, sizeof(BigInt));
			return;
		}

		// Handle cases where signs differ
		if (a->sign == 1 && b->sign == -1)
		{
			// a - (-b) = a + b
			bigint_add(a, b, result);
			return;
		}

		if (a->sign == -1 && b->sign == 1)
		{
			// (-a) - b = -(a + b)
			BigInt temp = *a;
			temp.sign = 1;
			bigint_add(&temp, b, result);
			result->sign = -1;
			return;
		}

		if (a->sign == -1 && b->sign == -1)
		{
			// (-a) - (-b) = b - a
			BigInt temp = *a;
			temp.sign = 1;
			bigint_subtract(b, &temp, result);
			result->sign = -1;
			return;
		}
		bigint_init(result, 0);

		u64 borrow = 0;
		int max_size = (a->size > b->size) ? a->size : b->size;
		result->size = max_size;

		// Perform the limb-by-limb subtraction
		for (int i = 0; i < max_size; i++)
		{
			__int128 diff = (__int128)a->limbs[i] - (i < b->size ? b->limbs[i] : 0) - borrow;
			borrow = (diff < 0) ? 1 : 0;
			diff += borrow * ((__int128)1 << 64);
			result->limbs[i] = (u64)diff;
		}

		// If there is a borrow left, append it as a new limb
		if (borrow)
		{
			result->limbs[result->size++] = borrow;
		}

		// Set the sign based on the comparison of a and b
		result->sign = (bigint_compare(a, b) < 0) ? -1 : 1;

		// Trim leading zeroes
		while (result->size > 1 && result->limbs[result->size - 1] == 0)
		{
			result->size--;
		}
	}

	// Add two BigInts
	void bigint_add(const BigInt *a, const BigInt *b, BigInt *result)
	{
		if (a->size == 0)
		{
			memcpy(result, b, sizeof(BigInt));
			return;
		}
		if (b->size == 0)
		{
			memcpy(result, a, sizeof(BigInt));
			return;
		}
		if (a->sign == 1 && b->sign == -1)
		{
			// a-b = a + (-b)
			BigInt temp = *a;
			temp.sign = 1;
			bigint_subtract(a, &temp, result);
			return;
		}
		if (a->sign == -1 && b->sign == 1)
		{
			// -a + b = b - a
			BigInt temp2 = *b;
			temp2.sign = 1;
			bigint_subtract(a, &temp2, result);
			return;
		}
		if (a->sign == -1 && b->sign == -1)
		{
			// -a - b = -(a + b)
			BigInt temp = *a;
			temp.sign = 1;
			bigint_add(&temp, b, result);
			result->sign = -1;
			return;
		}
		memset(result, 0, sizeof(BigInt));
		u64 carry = 0;
		{
			int min_size = (a->size < b->size) ? a->size : b->size;
			int i = 0;
			// Perform addition for overlapping limbs
			for (; i < min_size; i++)
			{
				__uint128_t sum = (__uint128_t)a->limbs[i] + b->limbs[i] + carry;
				result->limbs[i] = (u64)sum;
				carry = (u64)(sum >> 64);
			}

			// Add remaining limbs from the larger number
			int max_size = (a->size > b->size) ? a->size : b->size;
			const u64 *larger = (a->size > b->size) ? a->limbs : b->limbs;

			for (; i < max_size; i++)
			{
				__uint128_t sum = (__uint128_t)larger[i] + carry;
				result->limbs[i] = (u64)sum;
				carry = (u64)(sum >> 64);
			}
			result->size = max_size;
		}
		// If there is still a carry left, append it as a new limb
		if (carry)
		{
			result->limbs[result->size++] = carry;
		}
		// Set the sign based on the inputs
		result->sign = a->sign;
	}
	
	void bigint_multiply(const BigInt *a, const BigInt *b, BigInt *result)
	{
		// Handle multiplication by zero
		if (a->size == 0 || b->size == 0)
		{
			result->size = 1;
			result->sign = 0;
			result->limbs[0] = 0;
			return;
		}
		memset(result->limbs, 0, sizeof(u64) * (a->size + b->size));
		result->size = a->size + b->size;
		result->sign = (a->sign == b->sign) ? 1 : -1;

		// Use Karatsuba for large numbers
		if (a->size > 2 || b->size > 2)
		{
			BigInt high1, low1, high2, low2;
			int split = a->size / 2;

			// Split a into high1 and low1
			memcpy(low1.limbs, a->limbs, split * sizeof(u64));
			low1.size = split;
			memcpy(high1.limbs, a->limbs + split, (a->size - split) * sizeof(u64));
			high1.size = a->size - split;

			// Split b into high2 and low2
			split = b->size / 2;
			memcpy(low2.limbs, b->limbs, split * sizeof(u64));
			low2.size = split;
			memcpy(high2.limbs, b->limbs + split, (b->size - split) * sizeof(u64));
			high2.size = b->size - split;

			// Compute Z2 = high1 * high2
			BigInt z2;
			bigint_multiply(&high1, &high2, &z2);

			// Compute Z0 = low1 * low2
			BigInt z0;
			bigint_multiply(&low1, &low2, &z0);

			// Compute Z1 = (high1 + low1) * (high2 + low2) - Z2 - Z0
			BigInt sum1, sum2, z1;
			bigint_add(&high1, &low1, &sum1);
			bigint_add(&high2, &low2, &sum2);
			bigint_multiply(&sum1, &sum2, &z1);
			BigInt temp;
			bigint_subtract(&z1, &z2, &temp);
			bigint_subtract(&temp, &z0, &z1);

			// Combine results: result = Z2 * 10^(2m) + Z1 * 10^m + Z0
			bigint_shift_left(&z2, 64 * split * 2);
			bigint_shift_left(&z1, 64 * split);
			BigInt temp1;
			bigint_add(&z2, &z1, &temp1);
			bigint_add(&temp1, &z0, result);

			return;
		}

		// Naive multiplication for small numbers
		for (int i = 0; i < a->size; i++)
		{
			u64 carry = 0;
			for (int j = 0; j < b->size || carry > 0; j++)
			{
				__uint128_t product = (__uint128_t)a->limbs[i] * (j < b->size ? b->limbs[j] : 0) + result->limbs[i + j] + carry;
				result->limbs[i + j] = (u64)product;
				carry = product >> 64;
			}
		}

		// Trim leading zeros
		while (result->size > 1 && result->limbs[result->size - 1] == 0)
		{
			result->size--;
		}
	}
	void bigint_divide(const BigInt *a, const BigInt *b, BigInt *quotient, BigInt *remainder)
	{
		if (b->size == 0 || (b->size == 1 && b->limbs[0] == 0))
		{
			fprintf(stderr, "Error: Division by zero\n");
			exit(EXIT_FAILURE);
		}

		memset(quotient, 0, sizeof(BigInt));
		memset(remainder, 0, sizeof(BigInt));

		// If a < b, quotient = 0 and remainder = a
		if (bigint_compare(a, b) < 0)
		{
			memcpy(remainder, a, sizeof(BigInt));
			return;
		}

		// Copy the dividend to the remainder
		memcpy(remainder, a, sizeof(BigInt));

		// Initialize the quotient
		memset(quotient, 0, sizeof(BigInt));
		quotient->size = a->size;

		// Perform binary long division
		for (int i = a->size * 64 - 1; i >= 0; i--)
		{
			// Shift remainder left by 1 bit
			bigint_shift_left(remainder, 1);

			// Add the current bit of the dividend to the remainder
			int limb_index = i / 64;
			int bit_index = i % 64;
			u64 bit = (a->limbs[limb_index] >> bit_index) & 1;
			remainder->limbs[0] |= bit;

			// Compare remainder with divisor
			if (bigint_compare(remainder, b) >= 0)
			{
				// Subtract the divisor from the remainder
				BigInt temp;
				bigint_subtract(remainder, b, &temp);
				memcpy(remainder, &temp, sizeof(BigInt));

				// Set the corresponding bit in the quotient
				quotient->limbs[limb_index] |= ((u64)1 << bit_index);
			}
		}

		// Trim leading zeros in the quotient and remainder
		while (quotient->size > 1 && quotient->limbs[quotient->size - 1] == 0)
		{
			quotient->size--;
		}
		while (remainder->size > 1 && remainder->limbs[remainder->size - 1] == 0)
		{
			remainder->size--;
		}

		// Set the signs
		quotient->sign = (a->sign == b->sign) ? 1 : -1;
		remainder->sign = a->sign;
	}
#define CHUNK_BASE 1000000000ULL
#define CHUNK_DIGITS 9
	void bigint_add_u64(const BigInt *a, u64 b, BigInt *result)
	{
		*result = *a; // Start with a copy of a
		u64 carry = b;
		for (size_t i = 0; i < result->size && carry > 0; ++i)
		{
			u64 sum = result->limbs[i] + carry;
			carry = (sum < result->limbs[i]) ? 1 : 0;
			result->limbs[i] = sum;
		}
		if (carry > 0)
		{
			result->limbs[result->size++] = carry;
		}
	}

	void bigint_multiply_u64(const BigInt *a, u64 b, BigInt *result)
	{
		if (b == 0 || a->size == 0)
		{
			bigint_init(result, 0);
			return;
		}

		BigInt tmp;
		tmp.size = a->size;
		tmp.sign = a->sign;
		u64 carry = 0;

		for (size_t i = 0; i < a->size; ++i)
		{
			__uint128_t prod = (__uint128_t)a->limbs[i] * b + carry;
			tmp.limbs[i] = (u64)prod;
			carry = (u64)(prod >> 64);
		}

		if (carry != 0)
			tmp.limbs[tmp.size++] = carry;

		*result = tmp;
	}

	void bigint_from_string(BigInt *num, const char *str)
	{
		while (*str == ' ')
			str++;

		int sign = 1;
		if (*str == '-')
		{
			sign = -1;
			str++;
		}
		while (*str == ' ')
			str++;

		bigint_init(num, 0);

		size_t len = strlen(str);
		size_t start = (len % CHUNK_DIGITS == 0) ? CHUNK_DIGITS : len % CHUNK_DIGITS;

		char chunk_str[CHUNK_DIGITS + 1] = {0};
		u64 chunk;

		// First chunk (may be shorter than 9 digits)
		if (start > 0)
		{
			memcpy(chunk_str, str, start);
			chunk_str[start] = '\0';
			chunk = strtoull(chunk_str, NULL, 10);
			bigint_add_u64(num, chunk, num);
		}

		// Process remaining chunks
		for (size_t i = start; i < len; i += CHUNK_DIGITS)
		{
			// Multiply num by 1e9
			bigint_multiply_u64(num, CHUNK_BASE, num);

			memcpy(chunk_str, str + i, CHUNK_DIGITS);
			chunk_str[CHUNK_DIGITS] = '\0';
			chunk = strtoull(chunk_str, NULL, 10);
			bigint_add_u64(num, chunk, num);
		}

		num->sign = sign;
	}

}
*/