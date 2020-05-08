#define _CRT_SECURE_NO_WARNINGS
/*<>符号代表是去库中找寻,与之相对的 “ ”是从自己写的头文件中去寻找*/
#include<io.h>
#include<conio.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<Windows.h>
#include"Myheaders.h"
#include"Console_Tools.h"
using namespace std;

//const char* Files_input1 = "./*.txt";
//const char* Files_input2 = "G:/";
/*
为什么要使用链表是令人困惑的
*/
void Show_Files(File*header)
{
	system("cls");
	if (header == NULL)
		return;
	printf("目录下符合要求的文件分别是:\n");
	File* temp=header;	
	while (temp)
	{
		printf("%s\n", temp->name);
		temp = temp->Next;
	}
}
void Select_file()
{
	File* header=NULL;
	int num = 0;
	if (!Get_files(header,num, "./*.txt"))
	{
		printf("获取文件失败,请重试\n");
	}
	else
	{
		Show_Files(header);
		printf("请输入你需要的文件名(我们在默认的情况下选择文件sudoku.txt):\n");
		ifstream the_file;
		/*这里提供了一种非常好的实现回车键默认的情况,非常有趣*/
		char file_name[20]="";
		cin.getline(file_name,20);
		
		if (!strlen(file_name))
			strcpy(file_name, "sudoku.txt");
		the_file.open(file_name);
		if (the_file.is_open())
		{	
			bool MAP[MAX][MAX] = { 0 };
			int Map[MAX][MAX];
			for (int i = 0; i < MAX; i++)
				for (int j = 0; j < MAX; j++)
					the_file >> Map[i][j];
			
			Show_sudoku(Map,MAP);
			printf("经过检查之后的结果是:\n");
			Check_and_Show(Map,MAP);	
		}
		the_file.close();
	}
	printf("请输入End离开当前界面.\n");
	char input[5];
	while (true)
	{
		cin.getline(input,5);
		if (Lower(input[0]) == 'e' && Lower(input[1]) == 'n' && Lower(input[2]) == 'd')
			break;
		printf("输入错误请重试.\n");
	}
	return;
}
/*************
*
*
*用来用不同颜色展示数独的程序
*
*
*************/
void Show_sudoku(int MAP[MAX][MAX], bool(*Wrong)[MAX], int check, bool Solid[MAX][MAX])
{/*行列小方格*/

	
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	setcolor(handle, COLOR_BLACK, COLOR_WHITE);
	printf("-+-a-b-c-d-e-f-g-h-i-\n");
	if (check || Wrong || Solid)
	{

		for (int i = 0; i < MAX; i++)
		{

			//	bool Judge =  ;
			setcolor(handle, COLOR_BLACK, COLOR_WHITE);
			printf("%d| ", i + 1);

			for (int k = 0; k < MAX; k++)
			{

				bool Judge = (check >> (20 + i)) & 1 || (check >> (10 + k)) & 1 || (check >> ((3 * (i / 3) + k / 3))) & 1;
				int ColorF = (Judge ? COLOR_WHITE : COLOR_BLACK);				
				int ColorS = Wrong?((Wrong[i][k] ? COLOR_RED : COLOR_HBLUE)):COLOR_HBLUE;
				if (Solid && Solid[i][k])
					ColorS = COLOR_HYELLOW;
				if (!MAP[i][k])//如果这个位子是零的话
				{
					setcolor(handle, ColorF, COLOR_HYELLOW);

					printf("%d ", 0);
					continue;
				}
				setcolor(handle, ColorF, ColorS);
				printf("%d ", MAP[i][k]);
			}
			printf("\n");
		}

		setcolor(handle, COLOR_BLACK, COLOR_WHITE);
	}
	else
	{
		for (int i = 0; i < MAX; i++)
		{

			//	bool Judge =  ;
			setcolor(handle, COLOR_BLACK, COLOR_WHITE);
			printf("%d| ", i + 1);

			for (int k = 0; k < MAX; k++)
			{

				if (!MAP[i][k])//如果这个位子是零的话
				{
					setcolor(handle, COLOR_BLACK, COLOR_HYELLOW);
					printf("%d ", 0);
					continue;
				}
				setcolor(handle, COLOR_BLACK, COLOR_HBLUE);
				printf("%d ", MAP[i][k]);
			}
			printf("\n");
		}

		setcolor(handle, COLOR_BLACK, COLOR_WHITE);

	}
}
void SHOW_SUDOKU_MAP(int )
{





}