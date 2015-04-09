#include <iostream>
#include <vector>
#include <string>
using namespace std;
#include "const.h"
#ifndef _algothrim_3_
int S, N, M, X, Y, K;
int A[202][202] = {0};
bool visited[202][202] = { false };
void  workrec(int depth,int &sum, char type ,int xpos, int ypos)
{
	if (xpos<0||ypos<0||xpos>M||ypos>N || depth>K||A[ypos][xpos]!=0||visited[ypos][xpos])
	{
		return ;
	}
	if (A[ypos][xpos]==A[X][Y])
	{
		sum++;
		return ;
	}
	visited[ypos][xpos] = true;
	if (type=='0')
	{
		workrec(depth , sum, 'r', xpos + 1, ypos);
		workrec(depth , sum, 'l', xpos - 1, ypos);
		workrec(depth , sum, 'u', xpos, ypos - 1);
		workrec(depth , sum, 'd', xpos, ypos + 1);
		visited[ypos][xpos] = false;
	}
	if (type =='r'||type=='l')
	{
		workrec(depth , sum, 'r', xpos + 1, ypos);
		workrec(depth  , sum, 'l', xpos - 1, ypos);
		workrec(depth + 1, sum, 'u', xpos, ypos - 1);
		workrec(depth + 1, sum, 'd', xpos, ypos + 1);
		visited[ypos][xpos] = false;
	}
	if (type=='d'||type =='u')
	{
		workrec(depth+1, sum, 'r', xpos + 1, ypos);
		workrec(depth+1, sum, 'l', xpos - 1, ypos);
		workrec(depth , sum, 'u', xpos, ypos - 1);
		workrec(depth , sum, 'd', xpos, ypos + 1);
		visited[ypos][xpos] = false;
	}
	
	
}
int main()
{
	cin >> S;
	int temps=0;
	while (temps<S)
	{
		cin >> N >> M;
		int tempN = 1;
		while (tempN<=N)
		{
			int tempM = 1;
			while (tempM<=M)
			{
				cin >> A[tempN][tempM];
				tempM++;
			}
			tempN++;
		}
		cin >> Y >> X >> K;
		//X++;
		//Y++;
		int depth = 0, sum = 0;
		workrec(depth, sum, '0', Y, X);
		cout << A[Y][X];
		cout << sum;
		temps++;
	}
}

#endif