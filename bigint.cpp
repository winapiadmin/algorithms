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
		BigInt(const BigInt& );

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
		friend BigInt operator/(const BigInt &, const BigInt &);

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
		int n = Length(a);//, m = Length(b);
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
		int n = Length(a);//, m = Length(b);
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

#define MAX_LIMBS 128	// Supports large numbers (~8192-bit)
#define BASE 10			// Base-10^9 (for easy printing)
#define MAX_DIGITS 2500 // Maximum number of decimal digits (logically math.log10(2**8192)=2466.03 rounded up to 2500)

	typedef unsigned long long u64;
	const u64 MAX_BASE = UINT64_MAX;
	const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	typedef struct
	{
		u64 limbs[MAX_LIMBS];
		int size; // Number of used limbs
		int sign; // 1 for positive, -1 for negative, 0 for zero
	} BigInt;

	// Initialize a BigInt with a single value
	void bigint_init(BigInt *num, long long value)
	{
		memset(num, 0, sizeof(BigInt));
		num->limbs[0] = abs(value);
		num->size = (value > 0) ? 1 : 0;
		num->sign = (value > 0) ? 1 : 0;
	}

	void bigint_add(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_subtract(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_multiply(const BigInt *a, const BigInt *b, BigInt *result);
	void bigint_divide(const BigInt *a, const BigInt *b, BigInt *quotient, BigInt *remainder);
	int bigint_compare(const BigInt *a, const BigInt *b);

	// Convert a number (as string) from base `a` to base `b`
	char *convertBase(const char *num, u64 baseA, u64 baseB)
	{
		if (baseA < 2 || baseB < 2 || baseA > MAX_BASE || baseB > MAX_BASE)
		{
			fprintf(stderr, "Error: Bases must be in range [2, UINT64_MAX]\n");
			exit(EXIT_FAILURE);
		}

		// Create a modifiable copy of the input number.
		char *input = strdup(num);
		if (!input)
		{
			fprintf(stderr, "Error: Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		// Allocate a buffer for the result using the defined maximum digits.
		char *result = (char *)malloc(MAX_DIGITS + 1);
		if (!result)
		{
			fprintf(stderr, "Error: Memory allocation failed\n");
			free(input);
			exit(EXIT_FAILURE);
		}
		int resIndex = 0;

		// Repeat division until the number becomes "0".
		while (strcmp(input, "0") != 0)
		{
			int carry = 0;
			size_t len = strlen(input);
			char *quotient = (char *)malloc(len + 1);
			if (!quotient)
			{
				fprintf(stderr, "Error: Memory allocation failed\n");
				free(input);
				free(result);
				exit(EXIT_FAILURE);
			}
			int qIndex = 0;
			for (size_t i = 0; i < len; i++)
			{
				int digit;
				char c = input[i];
				if ('0' <= c && c <= '9')
				{
					digit = c - '0';
				}
				else if ('A' <= c && c <= 'Z')
				{
					digit = c - 'A' + 10;
				}
				else if ('a' <= c && c <= 'z')
				{
					digit = c - 'a' + 10;
				}
				else
				{
					fprintf(stderr, "Error: Invalid digit in input number\n");
					free(input);
					free(result);
					free(quotient);
					exit(EXIT_FAILURE);
				}
				int value = carry * baseA + digit;
				int qdigit = value / baseB;
				carry = value % baseB;
				// Avoid leading zeros.
				if (qIndex > 0 || qdigit != 0)
				{
					quotient[qIndex++] = DIGITS[qdigit];
				}
			}
			quotient[qIndex] = '\0';

			// If quotient is empty, set it to "0" to avoid infinite loop.
			if (qIndex == 0)
			{
				strcpy(quotient, "0");
			}

			// Store the remainder digit.
			result[resIndex++] = DIGITS[carry];

			// Update the input number with the new quotient.
			free(input);
			input = strdup(quotient);
			free(quotient);
			if (!input)
			{
				fprintf(stderr, "Error: Memory allocation failed\n");
				free(result);
				exit(EXIT_FAILURE);
			}
		}
		free(input);
		result[resIndex] = '\0';
		// Reverse the result string in place.
		for (int i = 0; i < resIndex / 2; i++)
		{
			char temp = result[i];
			result[i] = result[resIndex - 1 - i];
			result[resIndex - 1 - i] = temp;
		}
		return result;
	}

	// Convert BigInt to a binary string (concatenate binary of all limbs)
	char *bigint_to_binary_string(const BigInt *num)
	{
		size_t total_bits = num->size * 64;
		char *binary_str = (char *)malloc(total_bits + 1);
		if (!binary_str)
		{
			fprintf(stderr, "Error: Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		// Construct the binary string from the limbs
		size_t pos = 0;
		for (int i = num->size - 1; i >= 0; i--)
		{
			for (int bit = 63; bit >= 0; bit--)
			{
				binary_str[pos++] = ((num->limbs[i] >> bit) & 1) ? '1' : '0';
			}
		}
		binary_str[pos] = '\0';

		return binary_str;
	}

	// Convert a BigInt (in binary) to base 10 string
	char *bigint_to_base10(const BigInt *num)
	{
		char *binary_str = bigint_to_binary_string(num);

		// Now convert the binary string to base-10 using convertBase
		char *base10_str = convertBase(binary_str, 2, BASE);

		free(binary_str); // Clean up binary string
		return base10_str;
	}

	// Function to convert a `BigInt` to a base-10 string using `binary_to_decimal`
	char *to_string(const BigInt *num)
	{
		if (num->size == 0 || num->sign == 0)
			return strdup("0");

		return bigint_to_base10(num);
	}

	// Print BigInt in base 10 or any other base
	void bigint_print(const BigInt *num)
	{
		char *result_str = to_string(num);
		printf("%s", result_str);
		free(result_str); // Clean up allocated string
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
		if (a->sign == 1 && b->sign == -1)
		{
			// a+b=a+(-b)
			BigInt *temp = (BigInt *)malloc(sizeof(BigInt));
			memcpy(temp, b, sizeof(BigInt));
			temp->sign = 1;
			bigint_add(a, temp, result);
			free(temp);
			return;
		}
		if (a->sign == -1 && b->sign == 1)
		{
			//-a+b=b-a
			BigInt *temp = (BigInt *)malloc(sizeof(BigInt));
			memcpy(temp, a, sizeof(BigInt));
			temp->sign = 1;
			bigint_add(temp, b, result);
			result->sign = -1;
			free(temp);
			return;
		}
		if (a->sign == -1 && b->sign == -1)
		{
			//-a-b=-(a+b)
			BigInt *temp = (BigInt *)malloc(sizeof(BigInt));
			memcpy(temp, a, sizeof(BigInt));
			temp->sign = 1;
			bigint_subtract(b, temp, result);
			free(temp);
			return;
		}
		memset(result, 0, sizeof(BigInt));
		u64 borrow = 0;
		int max_size = (a->size > b->size) ? a->size : b->size;
		result->size = max_size;
		// Handle subtraction limb by limb
		for (int i = 0; i < max_size; i++)
		{
			__int128 diff = (__int128)a->limbs[i] - (i < b->size ? b->limbs[i] : 0) - borrow;
			if (diff < 0)
			{
				diff += ((__int128)1 << 64);
				borrow = 1;
			}
			else
			{
				borrow = 0;
			}
			result->limbs[i] = (u64)diff;
		}
		// If there is still a borrow left, append it as a new limb
		if (borrow)
		{
			result->limbs[result->size++] = borrow;
		}
		// Set the sign based on the inputs
		if (bigint_compare(a, b) < 0)
		{
			result->sign = -1;
		}
		else
		{
			result->sign = a->sign;
		}
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
			BigInt *temp = (BigInt *)malloc(sizeof(BigInt));
			memcpy(temp, b, sizeof(BigInt));
			temp->sign = 1;
			bigint_subtract(a, temp, result);
			free(temp);
			return;
		}
		if (a->sign == -1 && b->sign == 1)
		{
			// -a + b = b - a
			BigInt *temp1 = (BigInt *)malloc(sizeof(BigInt));
			BigInt *temp2 = (BigInt *)malloc(sizeof(BigInt));
			memcpy(temp1, a, sizeof(BigInt));
			memcpy(temp2, b, sizeof(BigInt));
			temp2->sign = 1;
			bigint_subtract(temp2, temp1, result);
			free(temp1);
			free(temp2);
			return;
		}
		if (a->sign == -1 && b->sign == -1)
		{
			// -a - b = -(a + b)
			BigInt *temp = (BigInt *)malloc(sizeof(BigInt));
			memcpy(temp, a, sizeof(BigInt));
			temp->sign = 1;
			bigint_add(temp, b, result);
			result->sign = -1;
			free(temp);
			return;
		}
		memset(result, 0, sizeof(BigInt));
		u64 carry = 0;
		int max_size = (a->size > b->size) ? a->size : b->size;
		result->size = max_size;

		// Handle addition limb by limb
		for (int i = 0; i < max_size; i++)
		{
			__uint128_t sum = (__uint128_t)(i < a->size ? a->limbs[i] : 0) +
							  (i < b->size ? b->limbs[i] : 0) + carry;
			result->limbs[i] = (u64)sum;
			carry = (sum >> 64);
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
		memset(result, 0, sizeof(BigInt));
		result->size = a->size + b->size;
		result->sign = (a->sign == b->sign) ? 1 : -1;

		// Handle multiplication by zero
		if (a->size == 0 || b->size == 0)
		{
			result->size = 1;
			result->sign = 0;
			result->limbs[0] = 0;
			return;
		}

		// Multiply each limb and handle carry
		for (int i = 0; i < a->size; i++)
		{
			__uint128_t carry = 0;
			for (int j = 0; j < b->size || carry; j++)
			{
				__uint128_t prod = (__uint128_t)result->limbs[i + j] +
								   (__uint128_t)a->limbs[i] * (j < b->size ? b->limbs[j] : 0) +
								   carry;
				result->limbs[i + j] = (u64)prod;
				carry = (prod >> 64);
			}

			// Store any leftover carry in the next limb
			if (carry)
				result->limbs[i + b->size] = (u64)carry;
		}

		// Trim leading zeroes
		while (result->size > 1 && result->limbs[result->size - 1] == 0)
		{
			result->size--;
		}

		// If result is zero, force size to 1 and reset sign
		if (result->size == 1 && result->limbs[0] == 0)
		{
			result->sign = 0;
		}
	}

	void bigint_divide(const BigInt *a, const BigInt *b, BigInt *quotient, BigInt *remainder)
	{
		// Handle division by zero.
		if (b->size == 0 || (b->size == 1 && b->limbs[0] == 0))
		{
			fprintf(stderr, "Error: Division by zero\n");
			exit(EXIT_FAILURE);
		}

		memset(quotient, 0, sizeof(BigInt));
		// If a < b, then quotient = 0 and remainder = a.
		if (bigint_compare(a, b) < 0)
		{
			memcpy(remainder, a, sizeof(BigInt));
			return;
		}
		// Copy the dividend (a) to the remainder
		memcpy(remainder, a, sizeof(BigInt));

		// Iterate over each limb of the dividend to simulate long division
		for (int i = a->size - 1; i >= 0; i--)
		{
			// Shift the remainder by 1 (left shift) and bring down the next limb from dividend
			u64 carry = 0;
			for (int j = remainder->size - 1; j >= 0; j--)
			{
				u64 temp = (remainder->limbs[j] << 1) | carry;
				carry = remainder->limbs[j] >> 63;
				remainder->limbs[j] = temp;
			}
			// Add the next limb from dividend (a)
			remainder->limbs[0] = (remainder->limbs[0] << 1) | ((a->limbs[i] >> 63) & 1);

			// Now divide the remainder by the divisor (b)
			if (remainder->limbs[0] >= b->limbs[0])
			{
				// Calculate quotient digit
				quotient->limbs[i] = remainder->limbs[0] / b->limbs[0];
				u64 product = quotient->limbs[i] * b->limbs[0];

				// Subtract the product of the divisor and quotient digit from the remainder
				remainder->limbs[0] -= product;
			}
		}

		// Set the quotient's sign based on the input signs
		quotient->sign = (a->sign == b->sign) ? 1 : -1;
		remainder->sign = a->sign; // The remainder takes the sign of the dividend

		// Trim leading zeros from the quotient and remainder
		while (quotient->size > 1 && quotient->limbs[quotient->size - 1] == 0)
		{
			quotient->size--;
		}
		while (remainder->size > 1 && remainder->limbs[remainder->size - 1] == 0)
		{
			remainder->size--;
		}
	}

	// Converts a user-provided string to a BigInt given a base.
	// Supports optional leading '-' sign.
	void bigint_from_string(BigInt *num, const char *str)
	{
		while (str[0] == ' ')
			str++; // Skip leading spaces
		int sign = 1;
		if (str[0] == '-')
		{
			sign = -1;
			str++;
		}
		while (str[0] == ' ')
			str++; // Skip leading spaces

		bigint_init(num, 0);
		BigInt base_big;
		bigint_init(&base_big, 10);

		for (int i = 0; str[i] != '\0'; i++)
		{
			char c = str[i];
			u64 digit;
			if (c >= '0' && c <= '9')
				digit = c - '0';
			else
			{
				fprintf(stderr, "Error: Invalid character in input string\n");
				exit(EXIT_FAILURE);
			}
			if (digit >= 10)
			{
				fprintf(stderr, "Error: Digit out of range for given base\n");
				exit(EXIT_FAILURE);
			}

			BigInt mult, add, sum;
			bigint_multiply(num, &base_big, &mult);
			bigint_init(&add, digit);
			bigint_add(&mult, &add, &sum);
			*num = sum;
		}
		num->sign = sign;
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
bool testC(std::string s1, std::string s2) {
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
    char* sumC_str = CBigInt::to_string(&sumC);
    mpz_set_str(sumC_GMP, sumC_str, 10);
    free(sumC_str);

    // Convert prodC to GMP
    char* prodC_str = CBigInt::to_string(&prodC);
    mpz_set_str(prodC_GMP, prodC_str, 10);
    free(prodC_str);

    // ---------- Using GMP for Validation ----------
    mpz_t aGMP, bGMP, sumGMP, prodGMP;
    mpz_init(aGMP);
    mpz_init(bGMP);
    mpz_init(sumGMP);
    mpz_init(prodGMP);

    // Set GMP variables from input strings
    if (mpz_set_str(aGMP, s1.c_str(), 10) != 0 || mpz_set_str(bGMP, s2.c_str(), 10) != 0) {
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
    if (mpz_cmp(sumGMP, sumC_GMP) != 0) {
        std::cerr << "Validation failed: GMP sum does not match CBigInt sum!" << std::endl;
        valid = false;
    }
    // Compare GMP product with CBigInt product (using mpz_cmp)
    if (mpz_cmp(prodGMP, prodC_GMP) != 0) {
        std::cerr << "Validation failed: GMP product does not match CBigInt product!" << std::endl;
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
bool testCPP(std::string s1, std::string s2) {
    // ---------- Using CPPBigInt ----------
    CPPBigInt::BigInt aCPP(s1), bCPP(s2);
    CPPBigInt::BigInt sumCPP = aCPP + bCPP;
    CPPBigInt::BigInt prodCPP = aCPP * bCPP;

    mpz_t sumCPP_GMP, prodCPP_GMP;
    mpz_init(sumCPP_GMP);
    mpz_init(prodCPP_GMP);

    // Convert sumCPP to GMP
    char* sumCPP_str = strdup(to_string(sumCPP).c_str());
    mpz_set_str(sumCPP_GMP, sumCPP_str, 10);
    free(sumCPP_str);

    // Convert prodCPP to GMP
    char* prodCPP_str = strdup(to_string(prodCPP).c_str());
    mpz_set_str(prodCPP_GMP, prodCPP_str, 10);
    free(prodCPP_str);

    // ---------- Using GMP for Validation ----------
    mpz_t aGMP, bGMP, sumGMP, prodGMP;
    mpz_init(aGMP);
    mpz_init(bGMP);
    mpz_init(sumGMP);
    mpz_init(prodGMP);

    // Set GMP variables from input strings
    if (mpz_set_str(aGMP, s1.c_str(), 10) != 0 || mpz_set_str(bGMP, s2.c_str(), 10) != 0) {
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
    if (mpz_cmp(sumGMP, sumCPP_GMP) != 0) {
        std::cerr << "Validation failed: GMP sum does not match CPPBigInt::BigInt sum!" << std::endl;
        valid = false;
    }
    // Compare GMP product with CPPBigInt product (using mpz_cmp)
    if (mpz_cmp(prodGMP, prodCPP_GMP) != 0) {
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

// Function to generate a random big number as a string, positive or negative
std::string generateRandomBigNumber(size_t length)
{
	std::string number;
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
	// Generate the big number
	for (size_t i = 0; i < length; ++i)
	{
		number += std::to_string(dis(gen));
	}

	return number;
}

int main()
{
	bool C=true, CPP=true;
	for (int _=0; _<1000000; _++)
	{
		// Generate two big numbers (with 50 digits)
		std::string num1 = generateRandomBigNumber(50);
		std::string num2 = generateRandomBigNumber(50);

		// Call the test function with the big numbers
		if (!testC(num1, num2)){
			std::cout << "Test failed for numbers: " << num1 << " and " << num2 << " with engine CBigInt\n";
			C=false;
		}
		// Call the test function with the big numbers
		if (!testCPP(num1, num2)){
			std::cout << "Test failed for numbers: " << num1 << " and " << num2 << " with engine CPPBigInt::BigInt\n";
			CPP=false;
		}
	}
	if (C){
		std::cout << "All tests passed for engine CBigInt!" << '\n';
	}
	else{
		std::cout << "Some tests failed for engine CBigInt!" << '\n';
		return 1;
	}
	if (CPP){
		std::cout << "All tests passed for engine CPPBigInt::BigInt!" << '\n';
		return 0;
	}
	else{
		std::cout << "Some tests failed for engine CPPBigInt::BigInt!" << '\n';
		return 1;
	}
	return 0;
}
// Well, it doesn't work well, but a fun way of exploring performance limits.
// or not:)
