#pragma once
#define MAX 9
#define REPEATE (1<<10)-1 
//#define NULL nopstr
struct File
{
	char* name;
	File* pre;   //ǰһ���ļ�
	File* Next;  //��һ���ļ�
	//File():name(NULL),pre(NULL),Next(NULL){}
};
struct Location
{//���������Լ������ϵ�����
	int num,X,Y;
	Location* Next, *Pre;//Ϊ���γ�һ������

};

//int Mode;/*����������Ϸ��ģʽ*/

void Select_file();

/*���س��������*/

bool Get_files(File*& header, int& num,const char* input);
void Show_Files(File* header);
int Check_and_Show(int(*map)[MAX], bool m[MAX][MAX] );
void Game(int(*input)[MAX]);
void image_Menu(const char* Files,int Mode);
void Image_sudokus(File*header,int MAP[MAX][MAX]);
char Lower(char in);
void Deal_sudoku(Location* From, Location* To, int(*input)[MAX]);
void Show_sudoku(int MAP[MAX][MAX], bool(*Wrong)[MAX] = {0}, int check = 0, bool m[MAX][MAX] = { 0 });