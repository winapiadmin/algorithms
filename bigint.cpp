// C++ program to implement
// the above approach
#include <bits/stdc++.h>

using namespace std;
namespace CPPBigInt
{
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
		int n = Length(a), m = Length(b);
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
		int n = Length(a), m = Length(b);
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

	void divide_by_2(BigInt & a){
		int add = 0;
		for (int i = a.digits.size() - 1; i >= 0;i--){
			int digit = (a.digits[i] >> 1) + add;
			add = ((a.digits[i] & 1) * 5);
			a.digits[i] = digit;
		}
		while(a.digits.size() > 1 && !a.digits.back())
			a.digits.pop_back();
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
			cout << (short)a.digits[i];
		return cout;
	}
}
namespace CBigInt
{

// This code is a C implementation of a BigInt library using uint64_t
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

#define MAX_LIMBS 128			   // Supports large numbers (~8192-bit)
#define BASE 10					   // Base-10^9 (for easy printing)
#define MAX_DIGITS (MAX_LIMBS * 9) // Maximum number of decimal digits

	typedef uint64_t u64;
	const u64 MAX_BASE = UINT64_MAX;
	const char DIGITS[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	typedef struct
	{
		uint64_t limbs[MAX_LIMBS];
		int size; // Number of used limbs
		int sign; // 1 for positive, -1 for negative, 0 for zero
	} BigInt;

	// Initialize a BigInt with a single value
	void bigint_init(BigInt *num, uint64_t value)
	{
		memset(num, 0, sizeof(BigInt));
		num->limbs[0] = value;
		num->size = (value > 0) ? 1 : 0;
		num->sign = (value > 0) ? 1 : 0;
	}

	// Convert a number (as string) from base `a` to base `b`
	char *convertBase(const char *num, u64 baseA, u64 baseB)
	{
		if (baseA < 2 || baseB < 2 || baseA > MAX_BASE || baseB > MAX_BASE)
		{
			fprintf(stderr, "Error: Bases must be in range [2, UINT64_MAX]\n");
			exit(EXIT_FAILURE);
		}

		// Convert input number to base 10 representation
		__uint128_t value = 0;
		for (const char *digit = num; *digit; digit++)
		{
			u64 d;
			if ('0' <= *digit && *digit <= '9')
			{
				d = *digit - '0';
			}
			else if ('A' <= *digit && *digit <= 'Z')
			{
				d = *digit - 'A' + 10;
			}
			else if ('a' <= *digit && *digit <= 'z')
			{
				d = *digit - 'a' + 10;
			}
			else
			{
				fprintf(stderr, "Error: Invalid digit in input number\n");
				exit(EXIT_FAILURE);
			}

			if (d >= baseA)
			{
				fprintf(stderr, "Error: Digit out of range for given base\n");
				exit(EXIT_FAILURE);
			}

			value = value * baseA + d;
		}

		// Convert from base 10 to base B
		char result[128]; // Assuming the result will not exceed 128 characters
		int index = 0;
		do
		{
			u64 remainder = value % baseB;
			value /= baseB;
			result[index++] = DIGITS[remainder];
		} while (value > 0);

		// Reverse the result for correct output
		char *finalResult = (char *)malloc(index + 1);
		if (!finalResult)
		{
			fprintf(stderr, "Error: Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}

		for (int i = 0; i < index; i++)
		{
			finalResult[i] = result[index - 1 - i];
		}
		finalResult[index] = '\0';

		return finalResult;
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

	// Print BigInt in base 10 or any other base
	char* to_string(const BigInt *num)
	{
		if (num->size == 0 || num->sign == 0)
			return "0";

		// Convert BigInt to base 10 string first
		char *base10_str = bigint_to_base10(num);
		// Allocate memory for the result string
		char *result_str = (char *)malloc(strlen(base10_str) + 2);
		if (!result_str)
		{
			fprintf(stderr, "Error: Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
		strcpy(result_str, base10_str); // Copy the base 10 string to result
		// If the number is negative, print the minus sign
		if (num->sign == -1)
		{
			sprintf(result_str, "-%s", result_str);
		}

		free(base10_str); // Clean up allocated string
		return result_str;
	}

	// Print BigInt in base 10 or any other base
	void bigint_print(const BigInt *num)
	{
		char *result_str = to_string(num);
		printf("%s", result_str);
		free(result_str); // Clean up allocated string
	}
	// Add two BigInts
	void bigint_add(const BigInt *a, const BigInt *b, BigInt *result)
	{
		uint64_t carry = 0;
		int max_size = (a->size > b->size) ? a->size : b->size;
		result->size = max_size;

		// Handle addition limb by limb
		for (int i = 0; i < max_size; i++)
		{
			__uint128_t sum = (__uint128_t)a->limbs[i] + b->limbs[i] + carry;
			result->limbs[i] = (uint64_t)sum;
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

	// Multiply two BigInt numbers
	void bigint_multiply(const BigInt *a, const BigInt *b, BigInt *result)
	{
		memset(result, 0, sizeof(BigInt));
		uint64_t carry = 0;
		result->size = a->size + b->size;

		// Multiply each limb and handle carry
		for (int i = 0; i < a->size; i++)
		{
			carry = 0;
			for (int j = 0; j < b->size || carry; j++)
			{
				__uint128_t prod = (__uint128_t)result->limbs[i + j] +
								   (__uint128_t)a->limbs[i] * (j < b->size ? b->limbs[j] : 0) +
								   carry;
				result->limbs[i + j] = (uint64_t)prod;
				carry = (prod >> 64);
			}
		}

		// Trim leading zeroes
		while (result->size > 1 && result->limbs[result->size - 1] == 0)
		{
			result->size--;
		}
		result->sign = (a->sign == b->sign) ? 1 : -1; // Set the sign based on the operands
	}
	// Converts a user-provided string to a BigInt given a base.
	// Supports optional leading '-' sign.
	void bigint_from_string(BigInt *num, const char *str)
	{		
		int sign = 1;
		if (str[0] == '-') {
			sign = -1;
			str++;
		}
		
		bigint_init(num, 0);
		BigInt base_big;
		bigint_init(&base_big, 10);
		
		for (int i = 0; str[i] != '\0'; i++) {
			char c = str[i];
			uint64_t digit;
			if (c >= '0' && c <= '9')
				digit = c - '0';
			else if (c >= 'A' && c <= 'Z')
				digit = c - 'A' + 10;
			else if (c >= 'a' && c <= 'z')
				digit = c - 'a' + 10;
			else {
				fprintf(stderr, "Error: Invalid character in input string\n");
				exit(EXIT_FAILURE);
			}
			if (digit >= 10) {
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
	// Helper function to compare two BigInts: returns -1 if a < b, 0 if equal, 1 if a > b.
	int bigint_compare(const BigInt *a, const BigInt *b)
	{
		if (a->size != b->size)
			return (a->size < b->size) ? -1 : 1;
		for (int i = a->size - 1; i >= 0; i--)
		{
			if (a->limbs[i] != b->limbs[i])
				return (a->limbs[i] < b->limbs[i]) ? -1 : 1;
		}
		return 0;
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
			uint64_t carry = 0;
			for (int j = remainder->size - 1; j >= 0; j--)
			{
				uint64_t temp = (remainder->limbs[j] << 1) | carry;
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
				uint64_t product = quotient->limbs[i] * b->limbs[0];

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
}
#include <sstream>
std::string to_string(const CPPBigInt::BigInt &num)
{
	std::ostringstream oss;
	oss << num;
	return oss.str();
}
bool test(std::string s1, std::string s2){
	{

		// ---------- Using CPPBigInt ----------
		CPPBigInt::BigInt aCPP(s1), bCPP(s2);
		CPPBigInt::BigInt sumCPP = aCPP + bCPP;
		CPPBigInt::BigInt prodCPP = aCPP * bCPP;

		// ---------- Using CBigInt ----------
		// For CBigInt we use the 64-bit conversion since our numbers fit in uint64_t.

		CBigInt::BigInt aC, bC, sumC, prodC;
		CBigInt::bigint_from_string(&aC, s1.c_str());
		CBigInt::bigint_from_string(&bC, s2.c_str());
		CBigInt::bigint_init(&sumC, 0);
		CBigInt::bigint_init(&prodC, 0);
		// Calculate addition
		CBigInt::bigint_add(&aC, &bC, &sumC);

		// Reinitialize operands for multiplication (since they are modified in operations)
		CBigInt::bigint_from_string(&aC, s1.c_str());
		CBigInt::bigint_from_string(&bC, s2.c_str());
		CBigInt::bigint_multiply(&aC, &bC, &prodC);
		return to_string(sumCPP) ==  std::string(CBigInt::to_string(&sumC))&&
			   to_string(prodCPP) == std::string(CBigInt::to_string(&prodC));
	}
}
#include <iostream>
#include <string>
#include <random>
#include <ctime>

// Function to generate a random big number as a string, positive or negative
std::string generateRandomBigNumber(size_t length) {
    std::string number;
    std::random_device rd;
    std::mt19937 gen(rd()); // Random number generator based on random_device
    std::uniform_int_distribution<> dis(0, 9); // Random digits 0-9

    bool isNegative = 0; // Randomly decide if the number is negative

    if (isNegative) {
        number += '-';
    }

    // Generate the big number
    for (size_t i = 0; i < length; ++i) {
        number += std::to_string(dis(gen));
    }

    return number;
}

int main() {
    // Generate two big numbers (with 50 digits)
    std::string num1 = generateRandomBigNumber(50);
    std::string num2 = generateRandomBigNumber(50);

    // Call the test function with the big numbers
    test(num1, num2);

    return 0;
}
