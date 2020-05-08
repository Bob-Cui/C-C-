
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
1.ʹ��������Ϊ����ͨ���ļ����е�һ���ڱ��������ļ���
2.������������ʵ����һ��������,Ϊ������������ļ����ṩ����
3.������ǲ�ʹ�û�����,��ά������Ĳ˵�ʱ����Ҫ���ǵ�ǰѡ�е��ļ�λ��
,���Ϊ���Ǻ���Ĳ˵��ṩ�鷳
*****************************************************/
bool Get_files(File*& header, int& num, const char* input)
{

	File* tailer = NULL;
	long handle;
	struct _finddata_t Files;
	handle = _findfirst(input, &Files);
	if (handle == -1)//˵��û���ҵ���һ���ļ�
	{
		cout << "No file found." << endl;
		return false;
	}
	do
	{
		num++;
		/*����������ķ�ʽ����һͷһβ,���м����*/

		File* temp = new(nothrow)File;
		if (temp == NULL)
		{//˵��û�пռ��ˣ���Ȼ��Ȥ
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

	_findclose(handle);/*�������ĺ���������ʲô��*/

	//ʵ�ֻ�����

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
				if ((Row >> Map[i][j]) & 1)/*˵������ط��Ѿ����ֹ�������*/
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
	
	/*ֻ������������һ�ַ����ܹ���������ظ�����ʱ���ظ���������*/
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
	printf("�����ļ���");
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

	/*��һ���ļ�ѡ��*/
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
		if ((input != 72) && (input != 80))/*72������80������*/
			continue;

		if (input == 72)
		{

			if (L == 0)
			{
				Now = Now->pre;
				File* Temp = Now;
				/*���ϵ��´�ӡ��Ӧ���ļ�������*/
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
			{//�����±߽�Ķ���
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
	/*�����ṩ��һ�ַǳ��õ�ʵ�ֻس���Ĭ�ϵ����,�ǳ���Ȥ*/


	the_file.open(Now->name);
	if (the_file.is_open())
	{
		bool MAP[MAX][MAX] = { 0 };
		int Map[MAX][MAX];
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				the_file >> Map[i][j];
		gotoxy(handle, 0, 0);
		
		printf("�������֮��Ľ����:\n");
		Check_and_Show(Map, MAP);
		Game(Map);
	
	}
	the_file.close();
};
void Game(int(*input)[MAX])
{
	//�����������û���������ֵ�
	char Word[5];
	printf("������Ϸ��ʼ,��Ϸ����������END���˳���Ϸ\n");
	printf("����5c6������Ӧ��������������������(��ע���Сд)\n");
	int Game[MAX][MAX];
//	memcpy(Game, input, 81);


	bool Solid[MAX][MAX] ;
	Location* header = NULL;
	Location* tailer = NULL;

	int Count1 = 0, Count2 = 0;
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)//��Щ�����ǲ����������ֵ�
		{
			Solid[i][j] = (input[i][j] == 0);
			Game[i][j] = input[i][j];
			Count1 = input[i][j] == 0 ? Count1 + 1 : Count1;
		}
		
	while (true)
	{
		printf("��������Ӧ�����ֻ���ֱ���˳���Ϸ");
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
				printf("���Ѿ����ʼͼ���ˡ�\n");
			Check_and_Show(Game, Solid);
			continue;
		}
		if (Word[0] > '9' || Word[0] < '0')
		{
			printf("��ʽ������������.\n");
			continue;
		}
		if (Word[1]<'a' || Word[1]>'z')
		{
			printf("��ʽ����������������.\n");
			continue;
		}
		if (Word[2] > '9' || Word[2] < '0')
		{
			printf("��ʽ������������.\n");
			continue;
		}
		Location* temp = new(nothrow)Location;
		if (temp == NULL)
		{
			printf("���ź��洢�ռ䲻������,��Ϸ�˳�.\n");
			return;
		}
		temp->X = Word[0] - '1';
		temp->Y = Word[1] - 'a';
		temp->num = Word[2] - '0';
		Game[temp->X][temp->Y] = temp->num;
		if (!Solid[temp->X][temp->Y])//��ط�֮ǰҪ����д�����ֱ����˳�
		{
			printf("�벻Ҫ��ͼ�Ķ�������ԭ�е�����\n");
			continue;
		}

		if (Check_and_Show(Game, Solid))
		{
			printf("���ִ���,���˻ز������������֡�\n");
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
			printf("��ϲ���Ѿ���ɱ�����,��Ϸ�˳���\n");
			break;
		}

	}

	return;

}