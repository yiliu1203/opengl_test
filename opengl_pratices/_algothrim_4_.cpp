#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>
#include "const.h"
#ifndef _algothrim_4_
using namespace std;
int main()
{
	string input;
	cin >> input;
	unordered_set<int> hset;
	hset.insert(1);
	hset.insert(2);
	hset.insert(3);
	hset.insert(5);
	hset.insert(8);
	hset.insert(13);
	hset.insert(21);
	
	//hash_set<string> hstring;
	vector<string> vstring;
	unordered_set<char> hchar;
	int differnum = 0;
	for (size_t i = 0; i < input.length(); i++)
	{
		hchar.clear();
		differnum = 0;
		for (size_t j = 0; j + i < input.length(); j++)
		{
			if (hchar.find(input[i+j])==hchar.end())
			{
				differnum++;
				hchar.insert(input[i + j]);
			}
			if (hset.find(differnum) != hset.end())
			{
				//hstring.insert(input.substr(i, j + 1));
				vstring.push_back(input.substr(i, j + 1));
			}
		}
	}
	sort(vstring.begin(), vstring.end());
	string prestr = *vstring.begin();
	cout << prestr<<endl;
	for (vector<string>::iterator iter = ++vstring.begin(); iter != vstring.end(); iter++)
	{
		if (*iter != prestr)
			cout << *iter<<endl;
		prestr = *iter;
	}
	
	return 0;
}
#endif