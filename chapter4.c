#include "simpio.h"
#include "genlib.h"
#include "strlib.h"
#include "random.h"
#include <string.h>
#include <stdio.h>


// Question 1

int Cannonball(unsigned n)
{
	if (n == 1)
	{
		return n;
	}
	else
	{
		return n*n + Cannonball(n - 1);
	}
}

// Question 2

int RaiseIntToPower(int n, int k)
{
	if (n == 1)
	{
		return 1;
	}
	else if (k == 0)
	{
		return 1;
	}
	else
	{
		return n * RaiseIntToPower(n, k - 1);
	}
}

// Question 3

int gcd(int x, int y)
{
	if (x % y == 0)
	{
		return y;
	}
	else
	{
		return gcd(y, x % y);
	}
}

// Question 4

int Fib_Iter(int n)
{
	int n0 = 0;
	int n1 = 1;

	int ret = 0;

	for (int i = 0; i < n; i++)
	{
		int temp = n1;
		n1 = n0 + n1;
		n0 = temp;
	}

	ret = n0;

	return ret;
}

// Question 5

static count1 = 0;
static count2 = 0;

int CountFib1(int n)
{
	count1++;

	if (n < 2)
	{
		return n;
	}
	else
	{
		return CountFib1(n - 1) + CountFib1(n - 2);
	}
}

int AdditiveSequence(int n, int t0, int t1)
{
	count2++;

	if (n == 0)
	{
		return t0;
	}
	else if (n == 1)
	{
		return t1;
	}
	else
	{
		return AdditiveSequence(n - 1, t1, t0 + t1);
	}
}

int CountFib2(int n)
{
	return AdditiveSequence(n, 0, 1);
}

// Question 6

int DigitSum(int n)
{
	if (n < 10)
	{
		return n;
	}
	else
	{
		return n % 10 + DigitSum(n / 10);
	}
}

// Question 7

int DigitRoot(int n)
{
	if (n < 10)
	{
		return n;
	}
	else
	{
		return DigitRoot(DigitSum(n));
	}
}

// Question 8

int PascalFactorial(int n, int k)
{
	if (n == k || k == 0)
	{
		return 1;
	}
	else
	{
		return PascalFactorial(n - 1, k - 1) + PascalFactorial(n - 1, k);
	}
}

// Question 9

string ReverseString(string str, int n)
{
	if (n == 0)
	{
		return str;
	}
	else
	{
		return Concat(CharToString(IthChar(str, n)), ReverseString(SubString(str, 0, n - 1), n - 1));
	}
}

string Reverse(string str)
{
	int len = StringLength(str);

	return ReverseString(str, len);
}

// Question 10

#define ASCII_DIGIT_BEGIN 48

string MyIntegerToString(int n)
{
	if (n < 10)
	{
		return CharToString(n + ASCII_DIGIT_BEGIN);
	}
	else
	{
		return Concat(MyIntegerToString(n / 10), CharToString(n % 10 + ASCII_DIGIT_BEGIN));
	}
}

// Question 11
// 略