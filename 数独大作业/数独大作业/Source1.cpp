
#define _CRT_SECURE_NO_WARNINGS

#include<io.h>
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include"Myheaders.h"
#include"Console_Tools.h"
using namespace std;
const int Loc_X = 65;
const int Loc_Y = 4;



/****************************************************
1.使用链表是为了能通过文件链中的一个节遍历整个文件链
2.这里我们有意实现了一个环链表,为后面遍历整个文件链提供便利
3.如果我们不使用环链表,在维护后面的菜单时必须要考虑当前选中的文件位置
,这会为我们后面的菜单提供麻烦
*****************************************************/
bool Get_files(File*& header, int& num, const char* input)
{

	File* tailer = NULL;
	long handle;
	struct _finddata_t Files;
	handle = _findfirst(input, &Files);
	if (handle == -1)//说明没有找到第一个文件
	{
		cout << "No file found." << endl;
		return false;
	}
	do
	{
		num++;
		/*用链表最常见的方式就是一头一尾,向中间插入*/

		File* temp = new(nothrow)File;
		if (temp == NULL)
		{//说明没有空间了，果然有趣
			cout << "No free memory" << endl;
			return false;
		}
		temp->name = new(nothrow)char[strlen(Files.name) + 1];
		if (temp->name == NULL)
		{
			cout << "No free memory for string" << endl;
			return false;
		}
		strcpy(temp->name, Files.name);
		if (header == NULL || tailer == NULL)
		{
			header = tailer = temp;
		}
		else
		{
			tailer->Next = temp;
			temp->pre = tailer;
			tailer = temp;
		}
		tailer->Next = NULL;
	} while (!_findnext(handle, &Files));

	_findclose(handle);/*这个神奇的函数究竟有什么用*/

	//实现环链表

	header->pre = tailer;
	tailer->Next = header;
	return true;
}
int Check_and_Show(int(*Map)[MAX], bool Solid[MAX][MAX])
{
	int num = 0;
	int Row_Check = 0;
	int Col_Check = 0;
	int Box_Check = 0;
	bool Wrong[MAX][MAX] = { 0 };
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			cout << Map[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < MAX; i++)
	{
		int Row = 0;
		int Col = 0;
		int Box = 0;
		for (int j = 0; j < MAX; j++)
		{
			if (Map[i][j])
			{
				if ((Row >> Map[i][j]) & 1)/*说明这个地方已经出现过数字了*/
				{
					Row_Check |= 1 << i;
					for (int k = 0; k < MAX; k++)
						if (Map[i][k] == Map[i][j])
						{
							Wrong[i][k] = true;

						}
				}
				Row |= (1 << Map[i][j]);
			}
			if (Map[j][i])
			{

				if (Col >> Map[j][i] & 1)
				{
					Col_Check |= 1 << i;
					for (register int k = 0; k < MAX; k++)
						if (Map[k][i] ==Map[j][i])
							Wrong[k][i] = true;
				}
				Col |= 1 << Map[j][i];
			}
			if (Map[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3])
			{
				if (Box >> (Map[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3]) & 1)
				{
					Box_Check |= 1 << i;
					for (register int k = 0; k < MAX; k++)
						if (Map[3 * (i / 3) + k / 3][3 * (i % 3) + k % 3] == Map[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3])
							Wrong[3 * (i / 3) + k / 3][3 * (i % 3) + k % 3] = true;
				}
				Box |= 1 << Map[3 * (i / 3) + j / 3][3 * (i % 3) + j % 3];
			}

		}
	}
	
	/*只有重新搜索这一种方法能够解决计算重复数字时的重复计数问题*/
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			num += Wrong[i][j];


	int Final = Row_Check << 20 | Col_Check << 10 | Box_Check;
	if (num == 0)
		printf("It's a right sudoku.\n");
	else
		printf("There is %d conflict.\n", num);

	Show_sudoku(Map, Wrong, Final, Solid);
	return num;
}

void image_Menu(const char* input_files,int mode)
{
	File* header;
	int num = 0;
	if (Get_files(header, num, input_files))
		cout << "Yes" << endl;
	File* temp = header;
	int i = 1;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(handle, 100, 50);
	gotoxy(handle, Loc_X, Loc_Y);
	printf("数独文件表");
	gotoxy(handle, Loc_X, Loc_Y + 1);
	printf("=====================\n");
	do
	{
		gotoxy(handle, Loc_X, Loc_Y + i + 1);

		cout << "||" << setiosflags(ios::left) << setw(17) << temp->name << " ||";

		i++;
		temp = temp->Next;
	} while (i < 9);
	gotoxy(handle, Loc_X, Loc_Y + 9);
	printf("=====================\n");

	/*第一个文件选中*/
	gotoxy(handle, Loc_X + 2, Loc_Y + 2);
	setcolor(handle, COLOR_WHITE, COLOR_BLACK);
	cout << setiosflags(ios::left) << setw(strlen(header->name)) << header->name;

	File* Now = header;
	int L = 0;
	char input;
	while ((input = _getch()) != 13)
	{
		if (input != -32)
			continue;

		input = _getch();
		if ((input != 72) && (input != 80))/*72代表上80代表下*/
			continue;

		if (input == 72)
		{

			if (L == 0)
			{
				Now = Now->pre;
				File* Temp = Now;
				/*从上到下打印相应的文件的名字*/
				for (int i = 0; i < 7; i++)
				{
					gotoxy(handle, Loc_X + 2, Loc_Y + 2 + i);
					if (i == 0)
						setcolor(handle, COLOR_WHITE, COLOR_BLACK);
					else
						setcolor(handle, COLOR_BLACK, COLOR_WHITE);

					cout << setiosflags(ios::left) << setw(18) << Temp->name;
					Temp = Temp->Next;

				}
			}

			else
			{
				Now = Now->pre;

				L--;
				gotoxy(handle, Loc_X + 2, Loc_Y + 2 + L);
				setcolor(handle, COLOR_WHITE, COLOR_BLACK);
				cout << setiosflags(ios::left) << setw(strlen(Now->name)) << Now->name;
				gotoxy(handle, Loc_X + 2, Loc_Y + 2 + L + 1);
				setcolor(handle, COLOR_BLACK, COLOR_WHITE);
				cout << setiosflags(ios::left) << setw(strlen(Now->name)) << Now->Next->name;
			}

		}
		else if (input == 80)
		{
			if (L == 6)
			{//到达下边界的顶点
				Now = Now->Next;
				File* Temp = Now;
				for (int i = 6; i >= 0; i--)
				{
					gotoxy(handle, Loc_X + 2, Loc_Y + 2 + i);
					if (i == 6)
						setcolor(handle, COLOR_WHITE, COLOR_BLACK);
					else
						setcolor(handle, COLOR_BLACK, COLOR_WHITE);

					cout << setiosflags(ios::left) << setw(18) << Temp->name;
					Temp = Temp->pre;

				}
			}
			else
			{
				Now = Now->Next;

				L++;
				gotoxy(handle, Loc_X + 2, Loc_Y + 2 + L);
				setcolor(handle, COLOR_WHITE, COLOR_BLACK);
				cout << setiosflags(ios::left) << setw(18) << Now->name;
				gotoxy(handle, Loc_X + 2, Loc_Y + 1 + L);
				setcolor(handle, COLOR_BLACK, COLOR_WHITE);
				cout << setiosflags(ios::left) << setw(18) << Now->pre->name;
			}
		}
	}
	ifstream the_file;
	/*这里提供了一种非常好的实现回车键默认的情况,非常有趣*/


	the_file.open(Now->name);
	if (the_file.is_open())
	{
		bool MAP[MAX][MAX] = { 0 };
		int Map[MAX][MAX];
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				the_file >> Map[i][j];
		gotoxy(handle, 0, 0);
		
		printf("经过检查之后的结果是:\n");
		Check_and_Show(Map, MAP);
		Game(Map);
	
	}
	the_file.close();
};
void Game(int(*input)[MAX])
{
	//最先输入的是没有填入数字的
	char Word[5];
	printf("数独游戏开始,游戏过程中输入END可退出游戏\n");
	printf("输入5c6可在相应的数独格中填入数字六(请注意大小写)\n");
	int Game[MAX][MAX];
//	memcpy(Game, input, 81);


	bool Solid[MAX][MAX] ;
	Location* header = NULL;
	Location* tailer = NULL;

	int Count1 = 0, Count2 = 0;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)//有些区域是不能填入数字的
		{
			Solid[i][j] = (input[i][j] == 0);
			Game[i][j] = input[i][j];
			Count1 = input[i][j] == 0 ? Count1 + 1 : Count1;
		}
		
	while (true)
	{
		printf("请输入相应的数字或是直接退出游戏");
		cin.getline(Word, 5);
		if (Lower(Word[0]) == 'e' && Lower(Word[1]) == 'n' && Lower(Word[2]) == 'd')
			break;
		if (Lower(Word[0]) == 'b' && Lower(Word[1]) == 'k' && tailer)
		{
			Count2--;
			Game[tailer->X][tailer->Y] = 0;
			if (tailer != header)
			{
				Location* del = tailer;
				tailer = tailer->Pre;
				delete del;
			}
			if (tailer == header)
				printf("这已经是最开始图案了。\n");
			Check_and_Show(Game, Solid);
			continue;
		}
		if (Word[0] > '9' || Word[0] < '0')
		{
			printf("格式有问题请重试.\n");
			continue;
		}
		if (Word[1]<'a' || Word[1]>'z')
		{
			printf("格式有问题请重新输入.\n");
			continue;
		}
		if (Word[2] > '9' || Word[2] < '0')
		{
			printf("格式有问题请重试.\n");
			continue;
		}
		Location* temp = new(nothrow)Location;
		if (temp == NULL)
		{
			printf("很遗憾存储空间不够用了,游戏退出.\n");
			return;
		}
		temp->X = Word[0] - '1';
		temp->Y = Word[1] - 'a';
		temp->num = Word[2] - '0';
		Game[temp->X][temp->Y] = temp->num;
		if (!Solid[temp->X][temp->Y])//这地方之前要是填写过数字必须退出
		{
			printf("请不要试图改动数独中原有的数字\n");
			continue;
		}

		if (Check_and_Show(Game, Solid))
		{
			printf("出现错误,请退回并重新输入数字。\n");
			Game[temp->X][temp->Y] = 0;
			Show_sudoku(Game);
			continue;
		}

		if (header == NULL || tailer == NULL)
			header = tailer = temp;
		else
		{
			tailer->Next = temp;
			temp->Pre = tailer;
			tailer = temp;
		}

		Count2++;
		if (Count1 == Count2)
		{
			printf("恭喜你已经完成本数独,游戏退出。\n");
			break;
		}

	}

	return;

}