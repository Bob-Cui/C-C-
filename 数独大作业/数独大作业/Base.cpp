#define _CRT_SECURE_NO_WARNINGS
/*<>���Ŵ�����ȥ������Ѱ,��֮��Ե� �� ���Ǵ��Լ�д��ͷ�ļ���ȥѰ��*/
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
ΪʲôҪʹ�����������������
*/
void Show_Files(File*header)
{
	system("cls");
	if (header == NULL)
		return;
	printf("Ŀ¼�·���Ҫ����ļ��ֱ���:\n");
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
		printf("��ȡ�ļ�ʧ��,������\n");
	}
	else
	{
		Show_Files(header);
		printf("����������Ҫ���ļ���(������Ĭ�ϵ������ѡ���ļ�sudoku.txt):\n");
		ifstream the_file;
		/*�����ṩ��һ�ַǳ��õ�ʵ�ֻس���Ĭ�ϵ����,�ǳ���Ȥ*/
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
			printf("�������֮��Ľ����:\n");
			Check_and_Show(Map,MAP);	
		}
		the_file.close();
	}
	printf("������End�뿪��ǰ����.\n");
	char input[5];
	while (true)
	{
		cin.getline(input,5);
		if (Lower(input[0]) == 'e' && Lower(input[1]) == 'n' && Lower(input[2]) == 'd')
			break;
		printf("�������������.\n");
	}
	return;
}
/*************
*
*
*�����ò�ͬ��ɫչʾ�����ĳ���
*
*
*************/
void Show_sudoku(int MAP[MAX][MAX], bool(*Wrong)[MAX], int check, bool Solid[MAX][MAX])
{/*����С����*/

	
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
				if (!MAP[i][k])//������λ������Ļ�
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

				if (!MAP[i][k])//������λ������Ļ�
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