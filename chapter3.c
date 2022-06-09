#include "simpio.h"
#include "genlib.h"
#include "strlib.h"
#include "random.h"

// Question 1

void RandomAverage(void)
{
	printf("This program averages a series of random numbers between 0 and 1.\n");
	printf("How many trials: \n");
	int n = GetInteger();
	int count = n;
	double ret = 0;

	if (n > 0)
	{
		Randomize();

		while (n > 0)
		{
			ret += RandomReal(0, 1);

			n--;
		}
	}
	else
	{
		Error("Please retry a positive number.\n");
	}


	printf("The average value after 10000 trials is %lf\n", ret / count);

	return;
}


// Question 2

void ThrowCoin(void)
{
	Randomize();
	int count = 0;
	int n = 0;

	while (n < 3)
	{
		if (RandomReal(0, 1) < 0.5)
		{
			n = 0;

			printf("Tails\n");

			count++;
		}
		else
		{
			n++;

			printf("Heads\n");

			count++;
		}
	}

	printf("It took %d flips to get 3 consecutive heads.\n", count);
	return; 
}

// Question 3

#define BanditItemNum 3

typedef enum
{
	Cherry,
	Lemon,
	Orange,
	Plum,
	Bell,
	Bar
}BanditItem;

typedef struct
{
	BanditItem arm[3];
}Bandit;


BanditItem RollOneBandit(void)
{
	return RandomInteger(Cherry, Bar); // RandomInteger is random within [low, high); 
}

void RollBandit(Bandit* const bandit)
{
	for (int i = 0; i < BanditItemNum; i++)
	{
		bandit->arm[i] = RollOneBandit();
	}

	return;
}

string GetItem(BanditItem item)
{
	string retString;

	switch (item)
	{
	case Cherry:
		retString = "Cherry";
		break;
	case Lemon:
		retString = "Lemon";
		break;
	case Orange:
		retString = "Orange";
		break;
	case Plum:
		retString = "Plum";
		break;
	case Bell:
		retString = "Bell";
		break;
	case Bar:
		retString = "Bar";
		break;
	default:
		retString = "";
		break;
	}

	return retString;
}

void PrintBandit(Bandit* const bandit)
{
	for (int i = 0; i < BanditItemNum; i++)
	{
		printf(GetItem(bandit->arm[i]));
		printf("  ");
	}

	return;
}


int GetMoney(Bandit* const bandit)
{
	int retMoney = -1;

	BanditItem first = bandit->arm[0];
	BanditItem second = bandit->arm[1];
	BanditItem third = bandit->arm[2];


	if ((first == Bar) && (first == second) && (first == third))
	{
		retMoney = 250;
	}
	else if ((first == Bell) && (first == second) && (third == Bell || third == Bar))
	{
		retMoney = 20;
	}
	else if ((first == Plum) && (first == second) && (third == Plum || third == Bar))
	{
		retMoney = 14;
	}
	else if ((first == Orange) && (first == second) && (third == Orange || third == Bar))
	{
		retMoney = 10;
	}
	else if ((first == Cherry) && (first == second) && (third == first))
	{
		retMoney = 7;
	}
	else if ((first == Cherry) && (first == second) && (third != first))
	{
		retMoney = 5;
	}
	else if ((first == Cherry) && (second != first) && (third != first))
	{
		retMoney = 2;
	}
	else
	{
		retMoney = -1;
	}

	return retMoney;
}

void startBanditGaming(Bandit* const bandit, int money)
{
	string replystring = "y";

	while (money > 0)
	{
		printf("You have %d dollar. Would you like to play?(Type 'y' to continue, any key else to stop...)  ", money);
		replystring = GetLine();

		if (StringEqual(replystring, "y"))
		{
			RollBandit(bandit);

			int bonus = GetMoney(bandit);

			PrintBandit(bandit);

			money += bonus;

			if (bonus == -1)
			{
				printf("-- You lose\n");
			}
			else
			{
				printf("-- You win %d dollar\n", bonus);
			}
		}
		else
		{
			break;
		}
	}

	return;
}

int main(void)
{
	Bandit bandit;
	Randomize();

	startBanditGaming(&bandit, 50);
}

// Question 4

int strcmpPointer(const char* s1, const char* s2)
{
	char* p1 = s1, * p2 = s2;

	for (; *p1 == *p2; p1++, p2++)
	{
		if ((*p1 == '\0') && (*p2 != '\0'))
		{
			p2++;
			return ('\0' - *p2);
		}
		else if ((*p2 == '\0') && (*p1 != '\0'))
		{
			p1++;
			return (*p1 - '\0');
		}
		else if ((*p1 == '\0') && (*p2 == '\0'))
		{
			return 0;
		}
	}

	return (*p1 - *p2);
}

int strcmpArray(const char s1[], const char s2[])
{
	int i = 0;

	for (; s1[i] == s2[i]; i++)
	{
		if ((s1[i] == '\0') && (s2[i] != '\0'))
		{
			return ('\0' - s2[i + 1]);
		}
		else if ((s2[i] == '\0') && (s1[i] != '\0'))
		{
			return (s1[i + 1] - '\0');
		}
		else if ((s1[i] == '\0') && (s2[i] == '\0'))
		{
			return 0;
		}
	}

	return (s1[i] - s2[i]);
}

// Question 5

string Capitalize(const string str)
{
	return Concat(ConvertToUpperCase(CharToString(IthChar(str, 0))), SubString(str, 1, StringLength(str) - 1));
}

// Question 6

bool ANSI_isPalindrome(const char str[])
{
	int length = strlen(str);

	for (int i = 0; i < length / 2; i++)
	{
		if (str[i] != str[length - i - 1])
		{
			return FALSE;
		}
	}

	return TRUE;
}

bool Lib_isPalindrome(const string str)
{
	int length = StringLength(str);

	for (int i = 0; i < length / 2; i++)
	{
		if (IthChar(str, i) != IthChar(str, length - i - 1))
		{
			return FALSE;
		}
	}

	return TRUE;
}

// Question 7

#define CHAR_a_POS 97
#define CHAR_A_POS 65	// pos of 'A'
#define ALPHABETNUM 26

string EncodeString(string str, int keyoffset)
{
	int length = StringLength(str);

	string ret = "";

	// 处理左移右移和移动步长超过字母表一轮的情况

	int keyoffsetNum = abs(keyoffset);

	if (keyoffsetNum >= ALPHABETNUM)
	{
		keyoffsetNum = keyoffsetNum % ALPHABETNUM;
	}

	if (keyoffset < 0)
	{
		keyoffset = ALPHABETNUM - keyoffsetNum;
	}
	else
	{
		keyoffset = keyoffsetNum;
	}


	// 处理字符

	for (int i = 0; i < length; i++)
	{
		char temp = IthChar(str, i);

		if (isalpha(temp))
		{
			if (isupper(temp))
			{
				temp = CHAR_A_POS + (temp - CHAR_A_POS + keyoffset) % ALPHABETNUM;
			}
			else if (islower(temp))
			{
				temp = CHAR_a_POS + (temp - CHAR_a_POS + keyoffset) % ALPHABETNUM;
			}
		}

		ret = Concat(ret, CharToString(temp));
	}

	return ret;
}

int main(void)
{
	printf("%s\n", EncodeString("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4));
	printf("%s\n", EncodeString("This is a secret message.", 13));
	printf("%s\n", EncodeString("IBM-9000", -1));
}

// Question 8
// This Question has some problems, function obligation error; we don't know which person to manage memory;

// Question 9
void TextFileInfo(const char* filepath)
{
	FILE* file = fopen(filepath, "r");

	char temp;

	int countChar = 0, countLine = 0, countWord = 0;

	if (file != NULL)
	{
		while ((temp = getc(file)) != EOF)
		{
			countChar++;

			if (temp == '\n')
			{
				countLine++;
				countWord++;
			}

			if (temp == ' ')
			{
				countWord++;
			}
		}
	}
	else
	{
		Error("File did not exsit...");
	}

	// 处理最后文件的EOF
	countLine++;
	countWord++;
	countChar++;

	printf("Lines: %d\n", countLine);
	printf("Words: %d\n", countWord);
	printf("Chars: %d\n", countChar);

	if (file != NULL)
	{
		fclose(file);
	}
}

// Question 10
