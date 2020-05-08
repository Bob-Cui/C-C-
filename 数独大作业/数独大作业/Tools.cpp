#include"Myheaders.h"
#include"Console_Tools.h"

using namespace std;



void Image_sudokus(File* header, int MAP[MAX][MAX])
{
}

char Lower(char in)
{
	if (in <= 'Z' && in >= 'A')
		return in - 'A';
	else if (in <= 'z' && in >= 'a')
		return in;
	else
		return '0';
}
void Deal_sudoku(Location* From, Location* To, int(*input)[MAX])
{

	if (From == To)
		return;
	else
	{
		while (From!=To)
		{
			
			input[From->X][From->Y] = From->num;
			From = From->Next;
		}
	}
	return;
}