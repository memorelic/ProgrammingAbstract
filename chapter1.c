#include "./cslib/genlib.h"
#include "./cslib/simpio.h"

// Question 1
void CelsiusToFahrenheit(void)
{
    double C = GetReal();

	double F = 9 / 5 * C + 32;

	printf("Fahrenheit = %lf\n", F);

	return;
}

// Question 2
void MeterToInchesAndFeet(void)
{
    #define FEET 0.0254

    double meter = GetReal();

	double feet = meter / FEET;

	double inches = feet / 12;

	double remain = inches - (int)inches;

	double remainfeet = remain * 12;

	printf("%lf meter = %d inches, %lf feet", 
            meter, (int)inches, remainfeet);

    return;
}

// Question 3
void GaussSum(void)
{
    int n = 100;

    int ret = (1 + n) * n / 2;

    printf("ret = %d\n", ret);

    return;
}

// Question 4
void FrontNOddSum(void)
{
    int N = GetInteger();

	int ret = (1 + (2 * (N-1) + 1)) * N / 2;

	printf("ret = %d\n", ret);
}

// Question 5
void FindLargestValue(void)
{
    int Monitor = 1;
	int Max = 0;
	// int temp = 0;

	printf("This program finds the largest integer in a list.\n");
	printf("Enter 0 to signal the end of the list.\n");

	while (Monitor != 0)
	{
		Monitor = GetInteger();

		if (Monitor > Max)
		{
			Max = Monitor;
		}
	}

	printf("The largest value is %d\n", Max);
}

// Question 6：模仿1.5.5小节 “while” 中介绍的DigitSum函数编写一个程序，读入一个整数，显示由该整数，显示该证书数字反向的整数。
void ReverseDigit(void)
{
	printf("This program reverse the digits in an integer.\n");
	printf("Enter a positive integer:  ");

	long integer = GetLong();

	printf("The reverse number is : ");
	while (integer > 0)
	{
		int i = integer % 10;
		printf("%d", i);
		integer /= 10;
	}

	printf("\n");
}

// Question 7

bool isPerfect(int n)
{
	int monitor = 0;

	for (int i = 1; i <= n/2; i++)
	{
		if (n % i == 0)
		{
			monitor += i;
		}
	}

	// Even perfect = 2^(n-1) * (2^n - 1)  n = 1, 2, 3...
	// We haven't know if Odd perfect exist

	return (monitor == n);
}

// Question 8

void PrimeFactored(unsigned int n)
{
	printf("Enter number to be factored: ");
	int n = GetInteger();
	int i = 2;

	while (i < n)
	{
		if (n % i == 0)
		{
			printf("%d * ", i);
			n = n / i;
		}
		else
		{
			i = i + 1;
		}
	}

	printf("%d\n", n);
}

// Question 9

int Round(double x)
{
	int ret = 0;

	if (x >= 0)
	{
		double n = x - (int)x;

		if (n >= 0.5)
		{
			ret = (int)x + 1;
		}
		else
		{
			ret = (int)x;
		}
	}
	else
	{
		double n = x - (int)x;

		if (n <= -0.5)
		{
			ret = (int)x - 1;
		}
		else
		{
			ret = (int)x;
		}
	}

	return ret;
}

// Question 10
double ApproxiamatePi(int N)
{
	double pi = 1.0;

	int n = 3;

	for (int i = 1; i <= N; i++)
	{
		pi = pi - (1.0 / n) + 1.0 / (n+2);
		n = n + 4;
	}

	pi = pi * 4;

	return pi;
}

// Question 11
// R = 2 fixed 
double ApproxiamateArea(int N)
{
#define R 2
	double w = (double)R / N;
	double Area = 0;

	for (int i = 0; i < N; i++)
	{
		double x = w * i;
		double h = sqrt((double)R * R - (x + w / 2) * (x + w / 2));
		Area = Area + h * w;
	}

	return Area;
}

// Question 12
void printTens(int x) 
{
	switch (x) 
	{
	case 2: printf("twenty"); return;
	case 3: printf("thirty"); return;
	case 4: printf("fourty"); return;
	case 5: printf("fifty"); return;
	case 6: printf("sixty"); return;
	case 7: printf("seventy"); return;
	case 8: printf("eighty"); return;
	case 9: printf("ninety"); return;
	}
}

void printOneDigit(int x) 
{
	switch (x) 
	{
	case 1: printf("one"); return;
	case 2: printf("two"); return;
	case 3: printf("three"); return;
	case 4: printf("four"); return;
	case 5: printf("five"); return;
	case 6: printf("six"); return;
	case 7: printf("seven"); return;
	case 8: printf("eight"); return;
	case 9: printf("nine"); return;
	}
}

int hundreds(int x) 
{
	return x / 100;
}

int tens(int x) 
{
	return (x / 10) % 10;
}

int ones(int x) 
{
	return x % 10;
}

int thousands(int x) 
{
	return x / 1000;
}

int lastThree(int x) 
{
	return x % 1000;
}

int lastTwo(int x) 
{
	return x % 100;
}

void printNumber(int x) 
{
	if (x >= 0 && x < 10) 
	{
		printOneDigit(x);
		return;
	}

	if (hundreds(x) > 0)
	{
		printOneDigit(hundreds(x));
		printf(" hundred ");
	}

	if ((lastTwo(x) >= 10 && lastTwo(x) <= 13) || lastTwo(x) == 15 || lastTwo(x) == 18) 
	{
		switch (lastTwo(x)) 
		{
		case 10: printf("ten"); return;
		case 11: printf("eleven"); return;
		case 12: printf("twelve"); return;
		case 13: printf("thirteen"); return;
		case 15: printf("fifteen"); return;
		case 18: printf("eighteen"); return;
		}
	}

	if (lastTwo(x) == 14 || lastTwo(x) == 16 || lastTwo(x) == 17 || lastTwo(x) == 19) 
	{ 
		//Yikes, I know. But this is the reusable functions question.
		printOneDigit(x % 10);
		printf("teen");
		return;
	}

	if (tens(x) > 1) 
	{
		printTens(tens(x));
		if (ones(x) > 0) 
		{
			printf("-");
			printOneDigit(ones(x));
		}

		return;
	}

	printOneDigit(ones(x));
	return;

}

void printTotal(int x) {
	if (x > 999999) 
	{
		printf("That's too large.");
		return;
	}

	if (x == 0) 
	{
		printf("zero");
		return;
	}

	if (thousands(x) > 0) 
	{
		printNumber(thousands(x));
		printf(" thousand ");
	}
	printNumber(lastThree(x));
	return;
}

int main(void)
{
	printf("Enter numbers in their decimal form.\n");
	printf("To stop, enter a negative value.");
	
	int input;

	do
	{
		printf("\nnumber: ");
		input = GetInteger();
		printTotal(input);
	} while (input >= 0);

	return 0;

}
