#include <iostream>
#include <vector>
#include <string>
#include "const.h"
using namespace std;
#ifndef _algothrim_2_
string house[100];
int N, M, S;
string inputkey;
pair<int, int> position_1;
pair<int, int > position_3;
pair<int, int > position_2;
void findPosition()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (house[i][j]=='1')
			{
				position_1.first = j;
				position_1.second = i;
			}
			if (house[i][j]=='3')
			{
				position_3.first = j;
				position_3.second = i;
			}
			if (house[i][j]=='2')
			{
				position_2.first = j;
				position_2.second = i;
			}
		}
	}
}
bool changePosition(int x_add, int y_add)
{
	if (position_1.first+x_add<0 || position_1.second+y_add<0)
	{
		return false;
	}

	if (position_1.first+x_add<N&& position_1.second+y_add<M&& house[position_1.second+y_add][position_1.first+x_add]!='4')
	{
		if (position_3.first == position_1.first + x_add && position_3.second == position_1.second + y_add)
		{
			
			if (position_3.first + x_add<N&& position_3.second + y_add<M&&position_3.first + x_add >= 0 && position_3.second + y_add >= 0 && house[position_3.second + y_add][position_3.first + x_add] != '4')
			{
				position_3.first += x_add;
				position_3.second += y_add;
			}
			else return false;
		}
		position_1.first += x_add;
		position_1.second += y_add;
	}
}
bool check(string & input)
{
	for (int i = 0; i < input.size();i++)
	{
		switch (input[i])
		{

		case 'r':{changePosition(1, 0); break; }
		case 'u':{changePosition(0, -1); break; }
		case 'l':{changePosition(-1, 0); break; }
		case 'd':{changePosition(0, 1); break; }
		}
		if (position_3.first==position_2.first && position_3.second ==position_2.second)
		{
			return true;
		}
		
	}
	return false;
}

int main()
{
	cin >> N >> M >> S;
	char tempchar;
	int temps = 0;
	cin.get();
	char buffer[101];
	while (temps < M)
	{
		cin.getline(buffer, 101);
		house[temps] = (string)buffer;
		temps++;
	}
	//temps = 0;
	//while (temps<N)
	//{
	//	cout << house[temps];
	//	temps++;
	//}
	temps = 0;
	findPosition();
	pair<int, int> temp_1, temp_3;
	temp_1 = position_1;
	temp_3 = position_3;
	while (temps<S)
	{
		int temp;
		cin >> temp;
		cin >> inputkey;
		//cout << inputkey;
		if (check(inputkey))
		{
			cout << "YES" << endl;
		}
		else cout << "NO" << endl;
		position_1 = temp_1;
		position_3 = temp_3;
		temps++;
	}
	return 0;

}

#endif