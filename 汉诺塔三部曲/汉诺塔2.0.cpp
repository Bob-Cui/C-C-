#include<cstdio>
#include<Windows.h>
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<time.h>
using namespace std;
#define MAX 11
#define TowerA 0
#define TowerB 1
#define TowerC 2
int Tops[3];
int Tower[3][MAX];

int level;
int Sleep_Time;            //中间间隔的时间
int Type;             //间隔时间的类型
int From, To;         //启示
char FROM, TO;
bool show;            //是否展示

void Show_Tower1()
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
void Show_Tower(int& num, int from, int to)
{
	system("cls");

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
	Show_Tower1();
	Sleep(Sleep_Time);
}
void Hanoi1(int n, int A, int B, int C, int& num)//所在的柱子与中转的柱子
{            //从A借助B将盘子转移到C	
	if (n == 0)
		return;
	Hanoi1(n - 1, A, C, B, num);
	Tower[C][++Tops[C]] = Tower[A][Tops[A]];
	Tower[A][Tops[A]--] = 0;
	if (!Type)                //按一次回车反应一次
	{
		char temp = _getch();
		while (true)
		{
			if (temp == '\n'||temp=='\r')
				break;
		}
	}
	Show_Tower(num,A,C);
	Hanoi1(n - 1, B, A, C, num);
}
void Sleep_time(int mode)
{
	switch (mode)
	{
	case 1:
		Sleep_Time
			= 1000;
		break;
	case 2:
		Sleep_Time = 800;
		break;
	case 3:
		Sleep_Time = 600;
		break;
	case 4:
		Sleep_Time = 400;
		break;
	case 5:
		Sleep_Time = 200;
		break;
	default:
		break;
	}
}
int main()
{
	int num = 0;
	level = 6;
	system("mode con cols=100 lines=30");
	//设置控制台的大小
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
		for (int i = 1; i <= level; i++)		
			Tower[TowerA][i] = level - i + 1;
	      Tops[TowerA] = level;
		
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
			To=TO-'A';
			break;
			
		}
		if (FROM == TO)
		{
			cout << "起始塔与目的塔不能是同一个塔,请重新输入" << endl;
			continue;
		}
		break;
	}
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
		if (Type< 0 || Type>5)
		{
			cout << "输入的大小有问题" << endl;
			continue;
		}
		Sleep_time(Type);
		break;
	}
	Hanoi(level,From,3-To-From,To,num);
	return 0;
}