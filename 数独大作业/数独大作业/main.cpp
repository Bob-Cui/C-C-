

#define _CRT_SECURE_NO_WARNINGS

#include<io.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
#include"Myheaders.h"
#include"Console_Tools.h"
#define MAX 9

const char* Files_input1 = "./*.txt";
const char* Files_input2 = "G:/*.pdf";
using namespace std;
int map[27][27];

void Init_()
{
	for (int i = 0; i < 20; i++)
		printf("-");
	printf("\n");
	printf("1.从文件中读取题目并用不同颜色显示冲突字母\n");
	printf("2.字符界面游戏(带回退功能)\n");
	printf("3.读取某个目录下的文件并选择\n");
	for (int i = 0; i < 20; i++)
		printf("-");
	printf("\n");
}
/*寻找文件的函数*/


int main()
{
	
	
	image_Menu(Files_input1,1);
	
	while (0)
	{
		char a = getchar();

		printf("%d\n", a);
	}
	
	char a = _getch();
	return 0;
}