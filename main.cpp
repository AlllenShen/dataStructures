#include "DataStructures.h"
#include <iostream>
#include <string>
#include <map>
#include <math.h>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;
//void PascalTriangle()
//{
//	int max, s;
//	Queue_1<int> q; 
//	cout << "max rows:";
//	cin >> max;
//	q.push(1);
//	for (int i = 0; i < max; i++)
//		cout << setw(3) << ' ';
//	cout << setw(3) << q.front() << endl;
//	for (int i = 1; i < max; i++) //output rows from 2 to max
//	{
//		for (int k = 0; k < max - i; k++)
//			cout << setw(3) << ' ';
//		s = 0;
//		for (int j = 0; j < i; j++) //out put item from 1 to i-1
//		{
//			int x = q.front();
//			q.pop();
//			q.push(s + x);
//			cout << setw(3) << s + x 
//				<< setw(3) << ' ';
//			s = x;
//		}
//		cout << setw(3) << '1' << endl;
//		q.push(1);
//	}
//}
//bool isNum(char n)
//{
//	if (n >= '0' && n <= '9')
//		return true;
//	return false;
//}
//int getNum(string exp, int &i) //获取连续数字
//{
//	Stack_1<int> temp;
//	int s = 0;
//	while (true)
//	{
//		char current = exp[i];
//		if (!isNum(current)) //连续数字全部读取
//		{
//			int size = temp.size();//size会变 要先确定
//			for (int j = 0; j < size; j++)
//			{
//				s += temp.top() * pow(10, j);
//				temp.pop();
//			}
//			i--; //指向最后一位数字
//			return s;
//		}
//		temp.push(current - 48);
//		i++;
//	}
//}
//int caculate(string exp)
//{
//	Stack_1<char> operators;
//	Stack_1<int> data;
//	map<char, int> comp; //处理优先级
//	comp['*'] = 3; comp['/'] = 3;
//	comp['+'] = 2; comp['-'] = 2;
//	comp['('] = 1;
//	comp['#'] = 0;
//
//	for (int i=0; i < exp.size(); i++)
//	{
//		char current = exp[i];
//		if (current == ' ')
//			continue;
//		if (current == '#' && operators.empty())
//		{
//			operators.push(current);
//			continue;
//		}
//	
//		if (isNum(current)) //处理连续数字
//		{
//			data.push(getNum(exp, i));
//			continue;
//		}
//		else
//		{
//			if (current == '(')
//			{
//				operators.push(current);
//				continue;
//			}
//			if (comp[operators.top()] >= comp[current])
//			{
//				int s2 = data.top();
//				data.pop();
//				int s1 = data.top();
//				data.pop();
//				switch (operators.top())
//				{
//				case '+':
//					data.push(s1 + s2); break;
//				case '-':
//					data.push(s1 - s2); break;
//				case '*':
//					data.push(s1 * s2); break;
//				case '/':
//					data.push(s1 / s2); break;
//				default:
//					break;
//				}
//				operators.pop();
//				if (operators.top() == '(')
//				{
//					operators.pop();
//					continue;
//				}
//				else if (operators.top() == '#') //finish
//					return data.top();
//				operators.push(current);
//			}
//			else
//				operators.push(current);
//		}
//	}
//}
List<int> sort(List<int> L)
{
	node<int> * m = L.start(), *p = m;
	for (int i =0; i < L.size(); i++)
	{
		while (p->next->next->next != nullptr)
		{
			node<int> * p1 = p->next, * p2 = p1->next;
			if (p2->data > p1->data)
			{
				p->next = p2;
				p1->next = p2->next;
				p2->next = p1;
			}
			p = p->next;
		}
	}
	return L;
}
void print_list(List_<int> list)
{
	cout << setw(10);
	for (int i = 1; i <= list.size(); i++)
		cout << setw(10) << list.get(i)->data;
	cout << endl << setw(10) << "address:";
	for (int i = 1; i <= list.size(); i++)
		cout << setw(10) << list.get(i);
	cout << endl << setw(10) << "next:";
	for (int i = 1; i <= list.size(); i++)
		cout << setw(10) << list.get(i)->next;
	cout << endl << setw(10) << "pre:";
	for (int i = 1; i <= list.size(); i++)
		cout << setw(10) << list.get(i)->pre;
}

void path(vector<int> & l, stack<int> & p, int i)
{
	if (i >= l.size()/* || l[i] == -1*/ )
	{
		printStack(p);
		p.pop();
	}
	else
		p.push(l[i]);
	path(l, p, i * 2);
	
	path(l, p, i * 2 + 1);
}

int main()
{
	undirectedGragh g;
	g.create();
	system("pause");
}
