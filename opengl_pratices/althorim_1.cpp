#include <iostream>
#include <vector>
using namespace std;
int cost[100000];
pair<int, int> lands[100000];
int getmin(const pair<int, int> & v1,const pair<int, int> & v2)
{
	int a =abs( v1.first - v2.first);
	int b =abs( v1.second - v2.second);
	return a < b ? a : b;
}
bool between(const pair<int, int> & s, const pair<int, int> &e, const pair<int, int>& d,int nmin)
{
	if (nmin>=getmin(s,d) && nmin>=getmin(e,d))
	{
		return true;
	}
	return false;
}
int main()
{
	int num;
	//std::vector<std::pair<int, int> > lands;
	int x, y;
	cin >> num;
	int i, j, k;
	for ( i = 0; i < num; i++)
	{
		cin >> x >> y;
		//lands.push_back(make_pair(x, y));
		lands[i] = make_pair(x, y);
	}
	int rnum = 1;
	int nmin = getmin(lands[0], lands[num - 1]);
	for ( i = 1; i <num-1; i++)
	{
		if (between(lands[0], lands[num - 1], lands[i],nmin))
			lands[rnum++] = lands[i];
	}
	lands[rnum++] = lands[i];
	//int nsize = lands.size();
	for (k = 1; k < rnum; k++)
	{
		int mintemp = getmin(lands[0], lands[k]);
		for ( j = 1; j < k; j++)
		{
		//	mintemp = getmin(mintemp,cost[j]+getmin(lands[j], lands[k]));
			int a = abs(lands[j].first - lands[k].first);
			int b = abs(lands[j].second - lands[k].second);
			if (a>b)
			{
				a = b;
			}
			if (mintemp>(a+cost[j]))
			{
				mintemp = a + cost[j];
			}
		}
		cost[k] = mintemp;
	}
	cout << cost[rnum-1];
	return 0;
	
}