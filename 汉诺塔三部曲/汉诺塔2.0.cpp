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
int Sleep_Time;            //�м�����ʱ��
int Type;             //���ʱ�������
int From, To;         //��ʾ
char FROM, TO;
bool show;            //�Ƿ�չʾ

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
	printf("��%4d�� :%c-->%c.", ++num, from + 'A', to + 'A');
	Show_Tower1();
	Sleep(Sleep_Time);
}
void Hanoi1(int n, int A, int B, int C, int& num)//���ڵ���������ת������
{            //��A����B������ת�Ƶ�C	
	if (n == 0)
		return;
	Hanoi1(n - 1, A, C, B, num);
	Tower[C][++Tops[C]] = Tower[A][Tops[A]];
	Tower[A][Tops[A]--] = 0;
	if (!Type)                //��һ�λس���Ӧһ��
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
	//���ÿ���̨�Ĵ�С
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
		for (int i = 1; i <= level; i++)		
			Tower[TowerA][i] = level - i + 1;
	      Tops[TowerA] = level;
		
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
			To=TO-'A';
			break;
			
		}
		if (FROM == TO)
		{
			cout << "��ʼ����Ŀ����������ͬһ����,����������" << endl;
			continue;
		}
		break;
	}
	while (true)
	{
		cout << "��������ʱ��ʱ�䳤��:(0-���س�������һ��,1--��ʱ���,5--��ʱ�)";
		cin >> Type;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		if (Type< 0 || Type>5)
		{
			cout << "����Ĵ�С������" << endl;
			continue;
		}
		Sleep_time(Type);
		break;
	}
	Hanoi(level,From,3-To-From,To,num);
	return 0;
}