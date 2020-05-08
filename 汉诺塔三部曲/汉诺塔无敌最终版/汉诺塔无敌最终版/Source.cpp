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


int From, To;         //启示
char FROM, TO;

int Top = 2;       //盘子移动的最高点
int  HEIGHT = 8;   //塔尖的高度
int Sleep_Type;
int Sleep_Time=100;

int Tower[3][11];
int Tops[3];

int Mode;
/***************
调节步骤之间休息的时间
***************/
void Sleep_time(int mode)
{
	switch (mode)
	{
	case 1:
		Sleep_Time= 5000;
		break;
	case 2:
		Sleep_Time = 400;
		break;
	case 3:
		Sleep_Time = 300;
		break;
	case 4:
		Sleep_Time = 200;
		break;
	case 5:
		Sleep_Time = 50;
		break;
	default:
		Sleep_Time = 100;
		break;
	}
}








/***************************
将一个颜色块在指定的坐标范围内进行垂直运动
Height 代表从下往上数第几个盘子
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
将对应的盘子在指定的塔之间移动:

LoactionF:起始塔盘子纵坐标位置
LocationA:目的塔盘子纵坐标位置

****************/
void MOVE_Plate(int Length, int FROM, int TO, int HeightF, int HeightA, int Color)
{
	MOVE_Vertical(HeightF, FROM, Length, Color, UP);
	MOVE_Horizontal(FROM, TO, Length, Color);
	MOVE_Vertical(HeightA, TO, Length, Color, DOWN);
}
void Show_Number()
{
	
	cout << "A:";
	for (int i = 1; i <= MAX - 1; i++)
	{
		if (Tower[TowerA][i])
			cout << setw(2) << Tower[TowerA][i];
		else
			cout << "   ";
	}
	cout << "B:";
	for (int i = 1; i <= MAX - 1; i++)
	{
		if (Tower[TowerB][i])
			cout << setw(2) << Tower[TowerB][i];
		else
			cout << "   ";
	}
	cout << "C:";
	for (int i = 1; i <= MAX - 1; i++)
	{
		if (Tower[TowerC][i])
			cout << setw(2) << Tower[TowerC][i];
		else
			cout << "   ";
	}
	cout << endl;
}
void Show_vector(int& num, int from, int to)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(handle,1,21);
	setcolor(handle,COLOR_BLACK,COLOR_WHITE);
	for (int i = MAX - 1; i >= 1; i--)
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
    printf("第%4d步 :%c-->%c.", ++num, from + 'A', to + 'A');
	Show_Number();
    Sleep(Sleep_Time);
}
/*********************
    用来展示三座塔  
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
	return;
}
/**********************
参数指明放盘子的位置以及盘子的数量,并画出图像
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
	return;
}

/**********************
做一个简单的移动操作,
只将其中一个塔的最上面的一个盘子移动到另外一个塔上
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
	int Top = 2;                //代表纵坐标的最小值
    //需要移动的盘子的横坐标

	MOVE_Plate(3,From,To,Level,1,color-1);
	
}
/******************
实现有图有真相的汉诺塔游戏全过程
******************/
void Hanio(int Level, int FROM, int To, int By,int &num)
{
	if (Level ==0)return;
	Hanio(Level - 1, FROM, By, To,num);
	Tower[To][++Tops[To]] = Tower[FROM][Tops[FROM]];	
	int length = 2*(Tower[FROM][Tops[FROM]])+1;
	
	if (Mode == 1)
		Show_Number();
	else
	{
		Show_vector(num, FROM, To);
		if(Mode==6)
		   MOVE_Plate(length, FROM, To, Tops[FROM], Tops[To], Tower[FROM][Tops[FROM]]);
	}
	
	Tower[FROM][Tops[FROM]--] = 0;
	Hanio(Level-1, By, To, FROM,num);
}
void Hanio_(int Level,int FROM,int To,int By)
{
	if(Mode!=1)
	  system("cls");
	printf("一共有%d层,从%c塔移动到%c塔", Level, FROM + 'A', To + 'A');
	for (int i = 1; i <= Level; i++)
		Tower[FROM][i] = Level - i + 1;
	Tops[FROM] = Level;
	
	if(Mode==6)
	   Show_Tower2(Level, FROM);
	int num = 0;
	Hanio(Level, FROM, To, By, num);
}

void Hanio_Game(int From,int To)
{



}
void  Preprocessing()
{
	system("cls");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(handle,COLOR_BLACK,COLOR_WHITE);
	for (int i = 0; i < 35; i++)
		printf("-");
	
	printf("\n");
	printf("1.内部数组显示<横向>\n");
	printf("2.内部数组显示<纵向+横向>\n");
	printf("3.图形解-预备-画三个圆柱\n");
	printf("4.图形解-预备-在起始柱子上画n个盘子\n");
	printf("5.图形解-预备-第一次移动\n");
	printf("6.图形解-自动移动版本\n");
	printf("7.图形解-游戏版\n");
	printf("0.退出\n");
	
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
		cout << "请选择操作模式[0-7]";
		
		cin >> Mode;
		
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "请不要胡乱输入数字" << endl;
			continue;
		}

		if (Mode != 3 )
		{
			while (true)
			{
				cout << "请输入层数(1-10):";
				cin >> level;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "你的输入有格式错误";
					system("cls");
					continue;
				}
				if (level < 1 || level>10)
				{
					cout << "数字不符合要求";
					system("cls");
					continue;
				}

				break;
			}
			while (true)
			{
				while (true)
				{
					cout << "请输入起始塔(A--C): ";
					cin >> FROM;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "输入不合法请重新输入" << endl;
						continue;
					}
					if (FROM<'A' || FROM>'C')
					{
						continue;
						cout << "输入不合法请重新输入" << endl;
					}
					From = FROM - 'A';
					cout << endl;
					break;
				}
				while (true)
				{
					cout << "请输入目的塔(A--C): ";
					cin >> TO;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "输入不合法请重新输入" << endl;
						continue;
					}
					if (TO<'A' || TO>'C')
					{
						cout << "输入不合法请重新输入" << endl;
						continue;
					}
					To = TO - 'A';
					break;

				}
				if (FROM == TO)
				{
					cout << "起始塔与目的塔不能是同一个塔,请重新输入" << endl;
					continue;
				}
				break;
			}
		}
		if (Mode < 0 || Mode>7)
		{
			cout << "输入的数字大小有问题" << endl;
			continue;
		}
		
		if (Mode == 0)
			break;
		else if (Mode == 1)
			Hanio_(level, From, To, 3 - (From + To));
		else if (Mode == 2)
			Hanio_(level, From, To, 3 - (From + To));
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
				cout << "请输入延时的时间长短:(0-按回车进行下一步,1--延时最短,5--延时最长)";
				cin >> Type;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				if (Type < 0 || Type>5)
				{
					cout << "输入的大小有问题" << endl;
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
			
			cout << "输入回车键返回" << endl;
			a = _getch();
			if (a == '\n' || a == '\r')
				break;

		}
	}
	return 0;
}