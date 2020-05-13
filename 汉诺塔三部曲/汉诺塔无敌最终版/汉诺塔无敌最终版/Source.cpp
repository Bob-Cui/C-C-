#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
#include<cstring>
#include <conio.h>
#include<iomanip>
#include <Windows.h>
#include "cmd_console_tools.h"
using namespace std;
#define TowerA 0
#define TowerB 1
#define TowerC 2

#define MAX 11

#define UP 1
#define DOWN 0


int From, To;         //��ʾ
char FROM, TO;

int Top = 2;       //�����ƶ�����ߵ�
int  HEIGHT = 8;   //����ĸ߶�
int Sleep_Type;
int Sleep_Time=100;

int Tower[3][11];
int Tops[3];

int Mode;
/*
�����е��������ȫ������Ϊ��
*/

void Empty()
{
	memset(Tower,0,sizeof(Tower));
	memset(Tops, 0, sizeof(Tops));
}




/***************
���ڲ���֮����Ϣ��ʱ��
***************/
void Sleep_time(int mode)
{
	switch (mode)
	{
	case 1:
		Sleep_Time= 300;
		break;
	case 2:
		Sleep_Time = 200;
		break;
	case 3:
		Sleep_Time = 150;
		break;
	case 4:
		Sleep_Time = 100;
		break;
	case 5:
		Sleep_Time = 5;
		break;
	default:
		Sleep_Time = 100;
		break;
	}
}








/***************************
��һ����ɫ����ָ�������귶Χ�ڽ��д�ֱ�˶�
Height ��������������ڼ�������
****************************/
void MOVE_Vertical(int Height, int Location, int Length, int Color1, bool Dir)
{//
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int op = Dir ? -1 : 1;
	int From =Dir? 20 - Height:Top;
	int target = Dir ? Top : 20 - Height;
	int X = 17 + Location * 30 -(Length - 1) / 2;
	
	
		for (int i = From; i != target + op; i += op)
		{
			showch(handle, X, i, ' ', Color1, COLOR_WHITE, Length);
			Sleep(Sleep_Time);
			if (i != target)
			{
				showch(handle, X, i, ' ', COLOR_BLACK, COLOR_WHITE, Length);
				if (i >= HEIGHT)
					showch(handle, Location * 30 + 17, i, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			}
		}
	
}
void MOVE_Horizontal( int FROM, int TO, int Length, int Color)
{
	int From = FROM * 30 + 17 - (Length - 1) / 2;
	int To = TO * 30 + 17 - (Length - 1) / 2;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int op = FROM < TO ? 1 : -1;
	for (int i = From; i != To + op; i += op)
	{
		showch(handle,i,Top, ' ', Color, COLOR_WHITE, Length);
		Sleep(Sleep_Time);	
		if(i!=To)
			showch(handle, i,Top,' ', COLOR_BLACK, COLOR_WHITE, Length);
	}
}
/****************
����Ӧ��������ָ������֮���ƶ�:

LoactionF:��ʼ������������λ��
LocationA:Ŀ��������������λ��

****************/
void MOVE_Plate(int Length, int FROM, int TO, int HeightF, int HeightA, int Color)
{
	MOVE_Vertical(HeightF, FROM, Length, Color, UP);
	MOVE_Horizontal(FROM, TO, Length, Color);
	MOVE_Vertical(HeightA, TO, Length, Color, DOWN);
}
void print()
{
	printf("A: ");
	for (int i = 1; i <= MAX; i++)
		if (Tower[TowerA][i])
			printf("%d ", Tower[TowerA][i]);
		else
			printf("  ");
	printf("B: ");
	for (int i = 1; i <= MAX; i++)
		if (Tower[TowerB][i])
			printf("%d ", Tower[TowerB][i]);
		else
			printf("  ");
	printf("C: ");
	for (int i = 1; i < MAX; i++)
		if (Tower[TowerC][i])
			printf("%d ", Tower[TowerC][i]);
		else
			printf("  ");
	printf("\n");
}
void Hanoi_of_num(int n, int A, int B, int C, int& num)//���ڵ���������ת������
{            //��A����B������ת�Ƶ�C	
	if (n == 0)
		return;
	Hanoi_of_num(n - 1, A, C, B, num);
	printf("��<%4d>�� :%c-->%c.  ", ++num, A + 'A', C + 'A');
	Tower[C][++Tops[C]] = Tower[A][Tops[A]];
	Tower[A][Tops[A]--] = 0;
	print();
	Hanoi_of_num(n - 1, B, A, C, num);
}


void Show_vector(int& num, int from, int to)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(handle,1,21);
	setcolor(handle,COLOR_BLACK,COLOR_WHITE);
	for (int i = MAX-1; i > 0; i--)
	{
		cout << "             ";
		if (Tower[TowerA][i])
			cout << "     " << Tower[TowerA][i];
		else
			cout << "      ";

		if (Tower[TowerB][i])
			cout << "      " << Tower[TowerB][i];
		else
			cout << "       ";

		if (Tower[TowerC][i])
			cout << "      " << Tower[TowerC][i];
		else
			cout << "       ";
		cout << endl;
	}
	cout << "             =============================" << endl;
    cout << "                  A      B      C     " << endl;
    printf("��%4d�� :%c-->%c.", ++num, from + 'A', to + 'A');
	print();
    Sleep(Sleep_Time);
}

void Hanoi_of_vector(int n, int A, int B, int C, int& num)//���ڵ���������ת������
{            //��A����B������ת�Ƶ�C	
	if (n == 0)
		return;
	Hanoi_of_vector(n - 1, A, C, B, num);
	
	Tower[C][++Tops[C]] = Tower[A][Tops[A]];
	Tower[A][Tops[A]--] = 0;
	Show_vector(num, A, C);
	Hanoi_of_vector(n - 1, B, A, C, num);
}
/*********************
    ����չʾ������  
*********************/
void Show_Tower1()
{
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 3; i++)
	{
		showch(handle, 5 + i * 30, 20, ' ', COLOR_HYELLOW, COLOR_WHITE, 25);
	}
	for (int k = 19; k >= 8; k--)
	{
		for (int i = 0; i < 3; i++)
		{
			showch(handle, 17 + i * 30, k, ' ', COLOR_HYELLOW, COLOR_WHITE, 1);
			Sleep(50);
		}
	}
	setcolor(handle, COLOR_BLACK, COLOR_WHITE);
	return;
}
/**********************
����ָ�������ӵ�λ���Լ����ӵ�����,������ͼ��
***********************/
void Show_Tower2(int Level,int loaction )
{
	Show_Tower1();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int k = Level; k >= 1; k--)
	{
		int height = Level - k;
		showch(handle,17-k+loaction*30,19-height,' ',k,COLOR_BLUE,2*k+1 );
	//	color++;
		Sleep(100);
	}
	setcolor(handle, COLOR_BLACK, COLOR_WHITE);
	system("pause");
	return;
}

/**********************
��һ���򵥵��ƶ�����,
ֻ������һ�������������һ�������ƶ�������һ������
***********************/
void Show_Tower3(int Level,int From,int To)
{
	Show_Tower1();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int color = COLOR_BLUE;
	for (int k = Level; k >= 1; k--)
	{
		int height = Level - k;
		showch(handle, 17 - k + From * 30, 19 - height, ' ', color, COLOR_BLUE, 2 * k + 1);
		color++;
		Sleep(50);
	}
	int Top = 2;                //�������������Сֵ
    //��Ҫ�ƶ������ӵĺ�����

	MOVE_Plate(3,From,To,Level,1,color-1);
	setcolor(handle, COLOR_BLACK, COLOR_WHITE);
	system("pause");
}
/******************
ʵ����ͼ������ĺ�ŵ����Ϸȫ����
******************/
void Hanio(int Level, int FROM, int To, int By,int &num)
{
	if (Level ==0)return;
	Hanio(Level - 1, FROM, By, To,num);
	Tower[To][++Tops[To]] = Tower[FROM][Tops[FROM]];	
	int length = 2 * (Tower[FROM][Tops[FROM]]) + 1;
	
	MOVE_Plate(length, FROM, To, Tops[FROM] + 0, Tops[To], Tower[FROM][Tops[FROM]]);
	Tower[FROM][Tops[FROM]--] = 0; 
	Show_vector(num, FROM, To);
	
	
	Hanio(Level-1, By, To, FROM,num);
}
void Hanio_(int Level, int FROM, int To, int By)
{
	if (Mode != 1)
		system("cls");
	printf("һ����%d��,��%c���ƶ���%c��", Level, FROM + 'A', To + 'A');
	for (int i = 1; i <= Level; i++)
		Tower[FROM][i] = Level - i + 1;
	Tops[FROM] = Level;

	if (Mode == 6)
		Show_Tower2(Level, FROM);
	int num = 0;
	Hanio(Level, FROM, To, By, num);
}
void  Preprocessing()
{
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(handle,COLOR_BLACK,COLOR_WHITE);
	for (int i = 0; i < 35; i++)
		printf("-");
	
	printf("\n");
	printf("1.�ڲ�������ʾ<����>\n");
	printf("2.�ڲ�������ʾ<����+����>\n");
	printf("3.ͼ�ν�-Ԥ��-������Բ��\n");
	printf("4.ͼ�ν�-Ԥ��-����ʼ�����ϻ�n������\n");
	printf("5.ͼ�ν�-Ԥ��-��һ���ƶ�\n");
	printf("6.ͼ�ν�-�Զ��ƶ��汾\n");
	printf("7.ͼ�ν�-��Ϸ��\n");
	printf("0.�˳�\n");
	
	for (int i = 0; i < 35; i++)
		printf("-");
	printf("\n");

}
int main()
{
	while (1)
	{
		int level;
		int Type;
		system("mode con cols=100 lines=100");
		Preprocessing();
		cout << "��ѡ�����ģʽ[0-7]";
		
		cin >> Mode;
		
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "�벻Ҫ������������" << endl;
			continue;
		}

		if (Mode != 3 )
		{
			while (true)
			{
				cout << "���������(1-10):";
				cin >> level;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "��������и�ʽ����";
					system("cls");
					continue;
				}
				if (level < 1 || level>10)
				{
					cout << "���ֲ�����Ҫ��";
					system("cls");
					continue;
				}

				break;
			}
			while (true)
			{
				while (true)
				{
					cout << "��������ʼ��(A--C): ";
					cin >> FROM;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "���벻�Ϸ�����������" << endl;
						continue;
					}
					if (FROM<'A' || FROM>'C')
					{
						continue;
						cout << "���벻�Ϸ�����������" << endl;
					}
					From = FROM - 'A';
					cout << endl;
					break;
				}
				while (true)
				{
					cout << "������Ŀ����(A--C): ";
					cin >> TO;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "���벻�Ϸ�����������" << endl;
						continue;
					}
					if (TO<'A' || TO>'C')
					{
						cout << "���벻�Ϸ�����������" << endl;
						continue;
					}
					To = TO - 'A';
					break;

				}
				if (FROM == TO)
				{
					cout << "��ʼ����Ŀ����������ͬһ����,����������" << endl;
					continue;
				}
				break;
			}
		}
		if (Mode < 0 || Mode>7)
		{
			cout << "��������ִ�С������" << endl;
			continue;
		}
		
		if (Mode == 0)
			break;
		else if (Mode == 1)
		{
			Empty();
			for (int i = 1; i <= level; i++)
				Tower[From][i] = level - i + 1;
			Tops[From] = level;
			int step = 0;
			Hanoi_of_num(level, From, 3 - (From + To) ,To, step);
		}
		else if (Mode == 2) {
			Empty();
			for (int i = 1; i <= level; i++)
				Tower[From][i] = level - i + 1;
			Tops[From] = level;
			int step = 0;
			Hanoi_of_vector(level, From, 3 - (From + To), To, step);
		}
		else if (Mode == 3)
			Show_Tower1();
		else if (Mode == 4)
			Show_Tower2(level, From);
		else if (Mode == 5)
			Show_Tower3(level, From, To);
		else if (Mode == 6)
		{
			while (true)
			{
				cout << "��������ʱ��ʱ�䳤��:(0-���س�������һ��,1--��ʱ�,5--��ʱ���)";
				cin >> Type;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				if (Type < 0 || Type>5)
				{
					cout << "����Ĵ�С������" << endl;
					continue;
				}
				Sleep_time(Type);
				break;
			}
			Hanio_(level, From, To, 3 - (From + To));
			
		}
		
		char a; 
		while (true)
		{
			
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n����س�������" << endl;
			a = _getch();
			if (a == '\n' || a == '\r')
				break;

		}
	}
	return 0;
}