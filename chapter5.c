#include "simpio.h"
#include "genlib.h"
#include "strlib.h"
#include "random.h"
#include <string.h>
#include <stdio.h>

// Question 1

static long countHHanoiMoves = 0;

void MoveSingleDiskWithCount(char start, char finish)
{
	countHHanoiMoves++;
	printf("%c -> %c\n", start, finish);
}

void NHanoiMoves(int n, char start, char finish, char temp)
{
	if (n == 1)
	{
		MoveSingleDiskWithCount(start, finish);
	}
	else
	{
		NHanoiMoves(n - 1, start, temp, finish);
		MoveSingleDiskWithCount(start, finish);
		NHanoiMoves(n - 1, temp, finish, start);
	}
}

int main(void)
{
	printf("start\n");
	NHanoiMoves(3, 'A', 'B', 'C');
	printf("%d\n", countHHanoiMoves);
	printf("end\n");

	return 0;
}

// Question 2

void MoveSingleDisk(char start, char finish)
{
	printf("%c -> %c\n", start, finish);
}

void MoveTower0(int n, char start, char finish, char temp)
{
	if (n == 0)
	{
		// MoveSingleDisk(start, finish);
		return;
	}
	else
	{
		MoveTower0(n - 1, start, temp, finish);
		MoveSingleDisk(start, finish);
		MoveTower0(n - 1, temp, finish, start);
	}
}

/*
    函数的长度在递归为终止条件为0时几乎无变化，只是在调用时会多用一层栈。
*/

// Question 3

void RecursivePermute(string permutedStr, string unPermutedStr)
{
	if (StringLength(unPermutedStr) == 0)
	{
		printf("%s\n", permutedStr);
	}
	else
	{
		for (int i = 0; i < StringLength(unPermutedStr); i++)
		{
			string character = CharToString(IthChar(unPermutedStr, i));
			string unpermute = Concat(SubString(unPermutedStr, 0, i - 1), SubString(unPermutedStr, i + 1, StringLength(unPermutedStr) - 1));


			RecursivePermute(Concat(permutedStr, character), unpermute);
		}
	}
}

// Question 4

void RecursivePermuteWithoutDuplicate(string permutedStr, string unPermutedStr, string lastChar)
{
	if (StringLength(unPermutedStr) == 0)
	{
		printf("%s\n", permutedStr);
	}
	else
	{
		for (int i = 0; i < StringLength(unPermutedStr); i++)
		{
			if (FindChar(IthChar(unPermutedStr, i), SubString(unPermutedStr, 0, i - 1), 0) == -1)
			{
				string character = CharToString(IthChar(unPermutedStr, i));
				string unpermute = Concat(SubString(unPermutedStr, 0, i - 1), SubString(unPermutedStr, i + 1, StringLength(unPermutedStr) - 1));
				RecursivePermuteWithoutDuplicate(Concat(permutedStr, character), unpermute, character);
			}
		}
	}
}

void ListPermutations(string str)
{
	RecursivePermuteWithoutDuplicate("", str, "");
}

// Question 5


void StringPermute(string ret, string vec[], int len)
{
	if (len == 0)
	{
		printf("%s\n", ret);
	}
	else
	{
		for (int i = 0; i < StringLength(vec[0]); i++)
		{
			string choosen = CharToString(IthChar(vec[0], i));
			StringPermute(Concat(ret, choosen), vec + 1, len - 1);
		}
	}
}

void ListMnemonics(string str)
{
	string vec[] = { "PRS", "ABC", "DEF" };
	StringPermute("", vec, 3);
}

// Question 6

void ListSubsetsRecursive(string unListStr, string ret)
{
	if (StringLength(unListStr) == 0)
	{
		printf("%s\n", ret);
	}
	else
	{
		for (int i = 0; i < StringLength(unListStr); i++)
		{
			string character = CharToString(IthChar(unListStr, i));
			string remain = SubString(unListStr, i + 1, StringLength(unListStr) - 1);
			ListSubsets(remain, Concat(ret, character));
		}

		if (StringCompare(ret, "") == 0)
		{
			printf("{}\n");
		}
		else
		{
			printf("%s\n", ret);
		}
		
	}
}

void ListSubsets(string str)
{
	ListSubsetsRecursive(str, "");
}

// Question 7

void GenerateBinaryCodeRecursive(unsigned int nBits, string ret)
{
	if (nBits == 0)
	{
		printf("%s\n", ret);
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			GenerateBinaryCodeRecursive(nBits - 1, Concat(ret, IntegerToString(i)));
		}
	}
}

void GenerateBinaryCode(unsigned int nBits)
{
	GenerateBinaryCodeRecursive(nBits, "");
}

// Question 8
void GenerateGrayCodeRecursive1(unsigned int nBits, string ret);
void GenerateGrayCodeRecursive2(unsigned int nBits, string ret);

void GenerateGrayCodeRecursive1(unsigned int nBits, string ret)
{
	if (nBits == 0)
	{
		printf("%s\n", ret);
	}
	else
	{
		string digit0 = IntegerToString(0);
		string digit1 = IntegerToString(1);

		GenerateGrayCodeRecursive1(nBits - 1, Concat(ret, digit0));
		GenerateGrayCodeRecursive2(nBits - 1, Concat(ret, digit1));
	}
}

void GenerateGrayCodeRecursive2(unsigned int nBits, string ret)
{
	if (nBits == 0)
	{
		printf("%s\n", ret);
	}
	else
	{
		string digit0 = IntegerToString(0);
		string digit1 = IntegerToString(1);

		GenerateGrayCodeRecursive1(nBits - 1, Concat(ret, digit1));
		GenerateGrayCodeRecursive2(nBits - 1, Concat(ret, digit0));
	}
}

void GenerateGrayCode(unsigned int nBits)
{
	GenerateGrayCodeRecursive1(nBits, "");
}

// Question 9

int NumberOfPartitions(int array[], int length, int target)
{
	if (target == 0)
	{
		return 1;
	}
	if (length == 0)
	{
		return 0;
	}
	else
	{
		//包含第一个元素的子集数
		int include = NumberOfPartitions(array + 1, length - 1, target - array[0]);
		//不包第一个元素的子集数
		int uninclude = NumberOfPartitions(array + 1, length - 1, target);

		return (include + uninclude);
	}
}

// Question 10

bool isMeasurable(int target, int weights[], int nWeights)
{
	if (target == 0)
	{
		return TRUE;
	}
	if (nWeights == 0)
	{
		return FALSE;
	}
	else
	{
		// 砝码移除
		bool remove = isMeasurable(target, weights + 1, nWeights - 1); 
		// 与砝码放在相同一边
		bool sameside = isMeasurable(target + weights[0], weights + 1, nWeights - 1); 
		// 与砝码放在不同一边
		bool otherside =  isMeasurable(target - weights[0], weights + 1, nWeights - 1); 
		
		return remove || sameside || otherside;
	}
}

// Question 11

#define HalfInchTick 0.2
#define GraduationLength 0.2

void DrawGraduations(double height)
{
	DrawLine(GraduationLength, 0);
	double currentX = GetCurrentX();
	double currentY = GetCurrentY();
	DrawLine(0, height);
	MovePen(currentX, currentY);
}

void DrawRuler(double height)
{
	if (height <= HalfInchTick)
	{
		DrawGraduations(height);
	}
	else
	{
		DrawRuler(height / 2);
		DrawGraduations(height);
		DrawRuler(height / 2);
	}
}

int main(void)
{
	InitGraphics();
	DrawRuler(1);
	return 0;
}

// Question 12

#define PI 3.1415926535

void DrawPolarLine(double r, double theta)
{
	double radians = theta / 180 * PI;

	DrawLine(r * cos(radians), r * sin(radians));
}

void DrawCoastLine(double length, double theta, int order)
{
	if (order == 0)
	{
		DrawPolarLine(length, theta);
	}
	else
	{
		DrawCoastLine(length / 3, theta, order - 1);
		DrawCoastLine(length / 3, theta + 60, order - 1);
		DrawCoastLine(length / 3, theta - 60, order - 1);
		DrawCoastLine(length / 3, theta, order - 1);
	}
}

// Question 13

#define MinLeaf 0.25
#define LengthDelta 0.15
#define ThetaDelta  20

void DrawTree(double length, double theta, bool continuedraw)
{
	if (length <= MinLeaf || continuedraw == FALSE)
	{
		DrawPolarLine(length, theta);
	}
	else
	{
		DrawPolarLine(length, theta);
		double x = GetCurrentX();
		double y = GetCurrentY();

		bool continuedraw = RandomChance(0.88);

		MovePen(x, y);
		DrawTree(length - LengthDelta, theta + ThetaDelta, continuedraw);

		MovePen(x, y);
		DrawTree(length - LengthDelta, theta - ThetaDelta, continuedraw);
	}
}

int main(void)
{
	InitGraphics();
	Randomize();
	MovePen(GetWindowWidth() / 2, 0.5);
	DrawTree(1.2, 90, TRUE);
	return 0;
}