#include <iostream>
#include <string>
#include <cstdio>
#include "BpTree.hpp"

using namespace std;

int main()
{
	char x[100];
	cin >> x;
	
	BpTree *a = new BpTree(x);
	
	/*
	long now = 0;
	for(now = 0; now < 10000; now++)
	{
		a.insert(now++, "abc");
	}
	*/
	
	int in1, in2;
	char ch[100];
	/*
	for(int i = 0; i < 1000; i++)
	{
		a.insert(i, "abc");
	}
	system("pause");
	for(int i = 0; i < 100; i++)
	{
		a.erase(i);
	}
	system("pause");
	 */
	while(true)
	{
		cin >> in1 >> in2;
		if(in1 == 0)
		{
			cin >> ch;
			cout << a->insert(in2, ch) << endl;
		}
		else if(in1 == 1)
		{
			cout << a->erase(in2) << endl;
		}
		else if(in1 == 2)
		{
			cout << a->find(in2) << endl;
		}
		else if(in1 == 3)
		{
			cout << a->get(in2).str << endl;
		}
		else
			break;
	}
   	return 0;
}