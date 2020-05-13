#include<cstdio>
#include<windows.h>
#include<conio.h>
#include<iostream>
#include<time.h>
using namespace std;
#define MAX 11
#define TowerA 0
#define TowerB 1
#define TowerC 2
int Top[3];
int Tower[3][MAX];
int level;
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
	for (int i = 1; i <= MAX; i++)
		if (Tower[TowerC][i])
			printf("%d ", Tower[TowerC][i]);
		else
			printf("  ");
	printf("\n");
}
void Hanoi_of_num(int n, int A, int B, int C,int &num)//所在的柱子与中转的柱子
{            //从A借助B将盘子转移到C	
	if (n == 0)
		return;
	Hanoi_of_num(n - 1, A, C, B, num);
	printf("第<%4d>步 :%c-->%c.  ", ++num, A+'A', C+'A');
	Tower[C][++Top[C]] = Tower[A][Top[A]];
	Tower[A][Top[A]--] = 0;
	print();
	Hanoi_of_num(n - 1, B, A, C, num);
}
int main()
{
	int num = 0;
	 level=8;


	for (int i = 1; i <= level; i++)
		Tower[TowerA][i] = level - i+1;
	Top[TowerA] = level;
	Hanoi_of_num(level, TowerA, TowerC, TowerB, num);
	return 0;
}