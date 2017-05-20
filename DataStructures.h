#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <initializer_list>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <stack>
#include <vector>
#include <iostream>
#define MAX_LEN 100
#define NULL 0

using namespace std;

extern enum errorcode {
	success,
	overflow,
	underflow
};

template<typename T>
struct node
{
	T data;
	node * next;
};

template<typename T>
struct doubleNode
{
	T data;
	doubleNode * pre;
	doubleNode * next;
};

template<typename type>
class Stack //implemented with array
{
private:
	type data[MAX_LEN];      
	int count;
public:
	Stack() { count = 0; };
	bool empty() const { return count == 0; };
	bool full() const { return count == MAX_LEN; };
	errorcode get_top(type &x) const
	{
		if (this.empty())
			return underflow;
		x = data[count - 1];
		return success;
	};
	errorcode push(type x)
	{
		if (this.full())
			return overflow;
		data[count] = x;
		count++;
		return success;
	};
	errorcode pop()
	{
		if (this.empty())
			return underflow;
		count--;
		return success;
	};
	int size() { return count; };
};

template<typename type>
class Queue //circular queue implemented with array
{
private:
	type data[MAX_LEN];
	int front_, rear;
	int count;
public:
	
	Queue() { front_ = 0; rear = 0; count = 0; };
	bool empty() const { return front_ == rear; };
	bool full() const { return (rear + 1) % MAX_LEN == front_; };
	int size() { return count; };
	errorcode front(type &x) const
	{
		if (this.empty())
			return underflow;
		x = data[(front_ + 1) % MAX_LEN];
		return success;
	};
	errorcode append(type x)
	{
		if (this.full())
			return overflow;
		rear = (rear + 1) % MAX_LEN;
		data[rear] = x;
		count++;
		return success;
	};
	errorcode serve()
	{
		if (this.empty())
			return underflow;
		front_ = (front_ + 1) % MAX_LEN;
		count--;
		return success;
	};
};

template<typename type>
class Stack_1
{
private:
	node<type> * top_;
	int count;
public:
	Stack_1()
	{
		node<type> * top_ = new node<type>;
		count = 0;
	};
	~Stack_1()
	{
		while (count > 0)
			this.pop();
		delete top_;
	};
	bool empty() const {
		return count == 0;
	};
	int top() const
	{
		if (this.empty())
			return nullptr;
		return top_->data;
	};
	void push(type x)
	{
		node<type> * p = new node<type>;
		p->data = x;
		p->next = top_;
		top_ = p;
		count++;
	};
	void pop()
	{
		node<type> * p = top_;
		top_ = top_->next;
		delete p;
		count--;
	};
	int size() {
		return count;
	};
};

template<typename type>
class Queue_1
{
private:
	node<type> * front_;
	node<type> * back;
	int count;
public:
	Queue_1()
	{
		node<type> * front_ = new node<type>;
		node<type> * back = front_;
		count = 0;
	};
	~Queue_1()
	{
		while (count)
			this.pop();
		delete front_;
	};
	void push(type x)
	{
		node<type> * p = new note<type>;
		p->data = x;
		p->next = nullptr;
		back->next = p;
		back = p;
	};
	void pop()
	{
		node<type> * p = front_->next;
		front_->next = front_->next->next;
		delete p;
	};
	type front() { return front_->next->data; };

};

template<typename type>
class List //非循环带头结点
{
private:
	node<type> * front_;
	node<type> * back;
	int count;
public:
	List()
	{
		front_ = new node<type>;
		front_->data = NULL;
		front_->next = nullptr;
		back = front_;
		count = 0;
	};
	List(std::initializer_list<type> l) //列表初始化
	{
		front_ = new node<type>;
		front_->data = NULL;
		front_->next = nullptr;
		back = front_;
		count = l.size();
		for (auto item : l)
			this->insert(count, item);
	}
	~List()
	{
		while (count > 0)
			this->erase(1);
		delete front_;
	};

	void insert(int n, type x)
	{
		if (n > count || n < 0)
			return;
		node<type> * m = new node<type>, * p = front_;
		m->data = x;
		for (int i = 0; i < n; i++)
			p = p->next;
		p->next = m;
		if (n == count)
		{
			m->next = nullptr;
			back = m;
		}
		else
			m->next = p->next;
		count++;
	};
	void erase(int n)
	{
		if (n > count || n < 1)
			return;
 		node<type> * p = front_, * m;
		for (int i = 0; i < n - 1; i++)
			p = p->next;
		m = p->next;
		if (n == count)
		{
			back = p;
			p->next = nullptr;
		}
		else
			p->next = m->next;
		delete m;
		count--;
	};
	int locate(type x)
	{
		node<type> * p = front_;
		for (int i = 0; i < count; i++)
		{
			p = p->next;
			if (p->data == x)
				return i + 1;
		}
		return;
	};
	type get_element(int n)
	{
		if (n > count || n < 1)
			return type(NULL);
		node<type> * p = front_;
		for (int i = 0; i < n; i++)
			p = p->next;
		return p->data;
	};
	int size() { return count; };
	node<type> * start()
	{
		return front_->next;
	};
	node<type> * end()
	{
		return back;
	}
	List<type> & operator+ (List<type> & B)
	{
		this->back->next = B.start();
		this->back = B.end();
		count += B.count;
		return *this;
	}
	void sort()
	{
		node<type> * p1 = this->start(), * p2 = p1->next;
		for (int i = 0; i < count; i++)
		{
			while (p2->next != nullptr)
			{
				if (p1->data > p2->data)
				{
					type temp = p1->data;
					p1->data = p2->data;
					p2->data = temp;
				}
				p1 = p2;
				p2 = p2->next;
			}
			p1 = this->start();
			p2 = p1->next;
		}
	}
	void print()
	{
		node<type> * p = this->start();
		while (p->next != nullptr)
		{
			cout << p->data << ' ';
			p = p->next;
		}
		cout << endl;
	}
};

template<typename type>
class List_ //带头结点双向循环
{
private:
	doubleNode<type> * back;
	int count;
public:
	List_()
	{
		back = new doubleNode<type>;
		//&back->data = nullptr;
		back->next = back;
		back->pre = back;
		count = 0;
	};
	~List_()
	{
		while (count > 0)
			erase(count);
		delete back;
	};
	void insert(int n, type x)
	{
		if (n < 0 || n > count)
			return;
		doubleNode<type> * m = new doubleNode<type>, * p = back->next;
		m->data = x;
		if (n == count) //insert to end
		{
			back->next = m;
			m->pre = back;
			m->next = p;
			p->pre = m;
			back = m;
			count++;
			return;
		}
		// insert to body
		for (int i = 0; i < n - 1; i++)
			p = p->next;
		m->pre = p;
		m->next = p->next;
		p->next = m;
		m->next->pre = m;
		count++;
	};
	void erase(int n)
	{
		if (n <= 0 || n > count)
			return;
		doubleNode<type> * p = back->next;
		if (n == count) //delete back
		{
			doubleNode<type> * m = back->pre, * temp = back;
			p->pre = m;
			m->next = p;
			back = m;
			delete temp;
			count--;
			return;
		}
		for (int i = 0; i < n - 1; i++)
			p = p->next;
		doubleNode<type> * temp = p->next;
		temp->next->pre = p;
		p->next = temp->next;
		delete temp;
		count--;
	};
	int locate(type x) 
	{ 
		int l = 0;
		doubleNode<type> * p = back->next;
		while (p->next != back)
		{
			p = p->next;
			l++;
			if (p->data == x)
				return l;
		}
		return 0;
	};
	doubleNode<type> * get(int n)
	{
		doubleNode<type> * p = back->next;
		if (n < 0 || n > count)
			return nullptr;
		for (int i = 0; i < n; i++)
			p = p->next;
		return p;
	};
	int size()
	{
		return count;
	};
	doubleNode<type> * end() 
	{
		return back;
	};
	doubleNode<type> * start()
	{
		return back->next;
	};
	List_<type> reverse()
	{
		doubleNode<type> * m = back, *p1 = back->next, *p2 = back->pre;
		while (p2 != m)
		{
			back->next = p2;
			back->pre = p1;
			p1 = back;
			back = p2;
			p2 = p2->pre;
		}
		return *this;
	}
};

template<typename type>
class sequence_list //顺序表
{
private:
	type data[MAX_LEN];
	int count;
public:
	sequence_list()
	{
		count = 0;
	}
	sequence_list(std::initializer_list<type> l)
	{
		int i = 0;
		for (auto item : l)
		{
			data[i] = item;
			i++;
		}
		count = l.size();
	}

	bool full()
	{
		return count == MAX_LEN;
	}
	bool empty()
	{
		return count == 0;
	}
	void insert(int n, type x)
	{
		if (this->full() || n > MAX_LEN || n < 0)
			return;
		for (int i = count - 1; i > n - 1; i--)
			data[i + 1] = data[i];
		data[n] = x;
		count++;
	}
	void erase(int n)
	{
		if (this->empty() || n <= 0 || n > count)
			return;
		for (int i = n; i < count; i++)
			data[i - 1] = data[i];
		count--;
	}
	void print()
	{
		for (int i = 0; i < count; i++)
			cout << data[i] << ' ';
		cout << endl;
	}
	void deweight()
	{
		for (int i = 0; i < count - 1; i++)
			if (data[i + 1] == data[i])
			{
				this->erase(i + 1);
				i--;
			}
	}
};

template<typename type>
class btNdoe
{
private:
	type data_;
	int id_;
	btNdoe<type> * Lchild_;
	btNdoe<type> * Rchild_;
	btNdoe<type> * parent_;
	btNdoe<type> * brother_;
public:
	btNdoe(type data=NULL, int id=-1,
			 btNdoe<type> * parent = nullptr)
	{
		data_ = data; id_ = id;
		Lchild_ = nullptr; Rchild_ = nullptr; 
		parent_ = parent; brother_ = nullptr;
	};
	void setParent(btNdoe<type> * parent)
	{
		parent_ = parent;
	}
	void setBrother(btNdoe<type> * bro)
	{
		brother_ = bro;
	};
	void fillInfo()
	{
		if (parent_ == nullptr)
			return;
		if (parent_->Lchild() == this)
			brother_ = parent_->Rchild();
		else
			brother_ = parent_->Lchild();
	}
	void setLchild(btNdoe<type> * L)
	{
		Lchild_ = L;
		if (L != nullptr)
		{
			L->setParent(this);
			L->fillInfo();
		}
	};
	void setRchild(btNdoe<type> * R)
	{
		Rchild_ = R;
		if (R != nullptr)
		{
			R->setParent(this);
			R->fillInfo();
		}
	};
	void setData(type data)
	{
		data_ = data;
	};
	void setID(int id)
	{
		id_ = id;
	};
	//查询方法
	btNdoe<type> * parent()
	{
		return parent_;
	};
	btNdoe<type> * brother()
	{
		if (brother_ == nullptr)
			this->fillInfo();
		return brother_();
	};
	btNdoe<type> * Lchild()
	{
		return Lchild_;
	};
	btNdoe<type> * Rchild()
	{
		return Rchild_;
	};
	type data()
	{
		return data_;
	}
	int id()
	{
		return id_;
	};
	void details()
	{
		cout << "id:\t" << id_ << endl;
		cout << "data:\t" << data_ << endl;
		cout << "Left Child:\t" << Lchild_ << endl;
		cout << "Right Child:\t" << Rchild_ << endl;
		cout << "Parent:\t" << parent_ << endl;
		cout << "Brother:\t" << brother_ << endl;
	};
};

template<typename type>
class binaryTree
{
private:
	btNdoe<type> * root;
	int count;
	int height;
public:
	binaryTree()
	{
		count = 0;
		height = 0;
	};
	binaryTree(initializer_list<char> list)
	{
		count = 0;
		height = 0;
		vector<btNdoe<type>> nodes;
		queue<btNdoe<type>> nodeQueue;
		for (auto i : list)
		{
			//占位符空缺未实现
			btNdoe<type> node(i);
			nodes.push_back(node);
		}
		nodeQueue.push(nodes[0]);
		root = &nodes[0]; //定位根
		count++;
		btNdoe<type> * node;
		int index = 1; //首位已push
		while (index < nodes.size())
		{
			node = &nodeQueue.front();
			nodeQueue.pop();
			nodeQueue.push(nodes[index++]);
			node->setLchild(&nodeQueue.back());
			nodeQueue.push(nodes[index++]);
			node->setRchild(&nodeQueue.back());
			count += 2;
		}
	};
	~binaryTree()
	{
		this->deleteTree(root);
	};
	void deleteTree(btNdoe<type> * r)
	{
		if (r->Lchild() != nullptr)
			this->deleteTree(r->Lchild());
		else if (r->Rchild() != nullptr)
			this->deleteTree(r->Rchild());
		if (r->parent() != nullptr)
		{
			if (r->parent()->Lchild() == r)
				r->parent()->setLchild(nullptr);
			else r->parent()->setRchild(nullptr);
		}
		delete r;
	};
	void create()
	{

	};
	btNdoe<type> & find(type data, btNdoe<type> * r=root)
	{
		if (r->data() == data)
			return *r;
		this->find(data, r->Lchild());
		this->find(data, r->Rchild());
	};
	//
	void printPath(stack<btNdoe<type>> & q, btNdoe<type> * start=root)
	{
		q.push(start);
		if (start->Rchild() == nullptr
			&& start->Lchild() == nullptr)
		{
			stack<btNdoe<type>> t = transport(q);
			for (int i = 0; i < q.size(); i++)
			{
				btNdoe<type> item = t.top();
				cout << item.data() << endl;
				t.pop();
			}
			q.pop();
		}
		btNdoe<type> top = q.top();
		if (top.Lchild() != nullptr)
			printPath(q, &top.Lchild());
		if (top.Rchild() != nullptr)
			printPath(q, &top.Rchild());
	}
};

template<typename type>
stack<type> transport(stack<type> s) //生成逆置栈
{
	stack<type> temp;
	type t;
	for (int i = 0; i < s.size(); i++)
	{
		t = s.top();
		temp.push(t);
		s.pop();
	}
	return temp;
}

void printStack(stack<int> s)
{
	stack<int> temp = transport(s);
	while (!temp.empty())
	{
		cout << temp.top() << ' ';
		temp.pop();
	}
	cout << endl;
}

struct _btnode  //node without templet
{
	int data_;
	_btnode * left;
	_btnode * right;
};

class _binarytree //breif version
{
private:
	_btnode * _root;
public:
	_binarytree()
	{
		/*_root = new _btnode;*/
	};
	_binarytree(initializer_list<int> list)
	{
		queue<_btnode *> q;
		for (auto i : list)
		{
			_btnode * t = new _btnode;
			t->data_ = i;
			t->left = nullptr;
			t->right = nullptr;
			q.push(t);
		}
		this->create(q, _root);
	};
	void deleteTree(_btnode * r)
	{
		if (r->left != nullptr)
			deleteTree(r->left);
		else if (r->right != nullptr)
			deleteTree(r->right);
		else
			delete r;
	};
	~_binarytree()
	{
		this->deleteTree(_root);
	};
	void create() //默认先序
	{
		queue<int> q;
		queue<_btnode *> _q;
		cout << "input tree\n(using -999 as placeholder)\n";
		int a;
		while (cin >> a)
			q.push(a);
		while (!q.empty())
		{
			_btnode * t = new _btnode;
			t->data_ = q.front();
			t->left = nullptr;
			t->right = nullptr;
			q.pop();
			_q.push(t);
		}
		this->create(_q, _root);
	};
	void create(queue<_btnode *> & q, _btnode * & r)
	{
		r = q.front();
		q.pop();
		if (q.empty())
			return;
		if (!q.empty() && q.front()->data_ != -999)
		{
			r->left = q.front();
			this->create(q, r->left);
		}
		else if (!q.empty())
			q.pop();
		if (!q.empty() && q.front()->data_ != -999)
		{
			r->right = q.front();
			this->create(q, r->right);
		}
		else if (!q.empty())
			q.pop();
	};

	_btnode * root()
	{
		return _root;
	}
	void pre(_btnode *& r) const
	{
		cout << r->data_;
		if (r->left != nullptr)
			pre(r->left);
		if (r->right != nullptr)
			pre(r->right);
	};
	void in(_btnode *& r) const
	{
		if (r->left != nullptr)
			pre(r->left);
		cout << r->data_;
		if (r->right != nullptr)
			pre(r->right);
	};
	void last(_btnode *& r) const
	{
		if (r->left != nullptr)
			pre(r->left);
		if (r->right != nullptr)
			pre(r->right);
		cout << r->data_;
	};
	void printNode(_btnode * r, int k=1) const
	{
		int f = floor(log(k) / log(2)) + 1;
		cout << '(' << r->data_ << ' ' 
			<< f  << ')' << endl;
		if (r->left != nullptr)
			this->printNode(r->left, k * 2);
		if (r->right != nullptr)
			this->printNode(r->right, k * 2 + 1);
	}
};

struct huffmanNode
{
	int data;
	int frequency;
	huffmanNode * parent;
	huffmanNode * left;
	huffmanNode * right;
};
huffmanNode * newNode(int data, int frequency, huffmanNode* left = nullptr,
	              huffmanNode* right=nullptr, huffmanNode* parent = nullptr)
{
	huffmanNode * t = new huffmanNode;
	t->data = data;
	t->frequency = frequency;
	t->parent = parent;
	t->left = left;
	t->right = right;
	return t;
}
void setParent(huffmanNode* parent)
{
	if (parent->left != nullptr)
		parent->left->parent = parent;
	if (parent->right != nullptr)
		parent->right->parent = parent;
}

#define charNum 129
class huffman 
{
private:
	huffmanNode * _root;
	int frequency[charNum];
	string codes[charNum];
	string _str;
	string _encode;
public:
	huffman(string str)
	{
		_str = str;
		_root = nullptr;
		_encode = "\0";
		for (int i = 0; i < 128; i++)
		{
			frequency[i] = 0;
			codes[i] = "\0";
		}
		for (char item : str)
			frequency[item]++;
		vector<huffmanNode*> create_list;
		for (int i = 0; i < 128; i++)
			if (frequency[i] != 0)
			{
				huffmanNode * t = newNode(i, frequency[i]);
				create_list.push_back(t);
			}
		create(create_list);
		calculateCode();
	};
	void create(vector<huffmanNode*> list)
	{
		if (list.size() == 1)
		{
			_root = list[0];
			return;
		}
		huffmanNode * t1 = this->findmin(list);
		this->deleteItem(list, t1);
		huffmanNode * t2 = this->findmin(list);
		this->deleteItem(list, t2);
		huffmanNode * newnode = newNode(-1, 
						t1->frequency + t2->frequency, t1, t2);
		setParent(newnode);
		list.push_back(newnode);
		this->create(list);
		//this->calculateCode();
	}
	huffmanNode * findmin(vector<huffmanNode*> list)
	{
		huffmanNode * min = list[0];
		for (int i = 1; i < list.size() - 1; i++)
			if (list[i]->frequency < min->frequency)
				min = list[i];
		return min;
	}
	void deleteItem(vector<huffmanNode*> & list,
					  huffmanNode* item)
	{
		vector<huffmanNode*>::iterator it = list.begin();
		while (it != list.end())
		{
			if ((*it) == item)
			{
				list.erase(it);
				return;
			}
			else
				it++;
		}
	}
	~huffman()
	{
		this->deleteTree(_root);
	};
	void deleteTree(huffmanNode * r)
	{
		if (r->left != nullptr)
			deleteTree(r->left);
		else if (r->right != nullptr)
			deleteTree(r->right);
		else
			delete r;
	};

	huffmanNode* root()
	{
		return _root;
	}
	void pre(huffmanNode* r)
	{
		cout << "data:" << r->data << '\t'
			<< "frequency:" << r->frequency << endl;
		if (r->left != nullptr)
			this->pre(r->left);
		if (r->right != nullptr)
			this->pre(r->right);
	}
	void calculateCode()
	{
		vector<int> charList;
		for (int i = 0; i < charNum; i++)
			if (frequency[i] != 0)
				charList.push_back(i);
		for (int i : charList)
		{
			huffmanNode* p = nullptr;
			find(i, p, _root);
			vector<huffmanNode*> path_ = path(p);
			vector<string> code;
			string s = "\0";
			for (int j = 1; j < path_.size(); j++)
			{
				if (path_[j - 1]->left == path_[j])
					code.push_back("0");
				else
					code.push_back("1");
			}
			for (int j = 0; j < code.size(); j++)
				s += code[j];
			codes[i] = s;
		}
	};
	void find(int c, huffmanNode*& p, huffmanNode* r)
	{
		if (r->data == c)
			p = r;
		if (r->left != nullptr)
			this->find(c, p, r->left);
		if (r->right != nullptr)
			this->find(c, p, r->right);
	}
	vector<huffmanNode*> path(huffmanNode* target)
	{
		huffmanNode* p = target;
		stack<huffmanNode*> s;
		while (p != _root)
		{
			s.push(p);
			p = p->parent;
		}
		s.push(p);
		vector<huffmanNode*> Path;
		while (!s.empty())
		{
			Path.push_back(s.top());
			s.pop();
		}
		return Path;
	}
	void encode()
	{
		for (auto i : _str)
			_encode += codes[i];
		cout << "encoding...\n";
		cout << "Raw:" << _str << endl
		     << "Encoded:" << _encode << endl << endl;
	}
	void decode()
	{
		string s = "\0";
		for (int i = 0; i < _encode.size();)
		{
			huffmanNode* p = _root;
			char c;
			while (has_child(p))
			{
				if (_encode[i] == '0')
					p = p->left;
				else
					p = p->right;
				i++;
			}
			c = p->data;
			s += c;
		}
		cout << "decoding...\n"
			 << "Encoded:" << _encode << endl
			 << "Raw:" << s << endl << endl;
	}
	bool has_child(huffmanNode* r)
	{
		if (r->left != nullptr || r->right != nullptr)
			return true;
		else
			return false;
	}
};

template<typename T>
struct gVt
{
	int id;
	T data;
	int weight; //向后权重
	gVt<T>* next;
};

template<typename T>
gVt<T>* newVt(int id, T data, int w = 1, gVt<T>* next = nullptr)
{
	gVt<T>* n = new gVt<T>;
	n->id = id;
	n->weight = w;
	n->data = data;
	n->next = next;
	return n;
}

template<typename T>
void deleteItem(vector<T> & list, T item)
{
	vector<T>::iterator it = list.begin();
	while (it != list.end())
	{
		if ((*it) == item)
		{
			list.erase(it);
			return;
		}
		else
			it++;
	}
}

template<typename type>
using Input = pair<vector<type>, vector<vector<int>>>;

template<typename type>
class graph //directed
{
private:
	vector<gVt<type>*> vertexs;
	int currentNum;
public:
	graph()
	{
		currentNum = 0;
	};
	virtual ~graph()
	{
		for (int i = 0; i < currentNum; i++)
			deleteVertex(i);
	};
	void create()
	{
		Input<type> in = input();
		create(in.first, in.second);
	}
	Input<type> input()
	{
		vector<type> data;
		vector<vector<int>> dir;
		cout << "input data:" << endl;
		int a, b, w;
		while (cin >> a)
			data.push_back(a);
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "confirme:" << endl 
			<< setw(8) << "id:";
		for (int i = 0; i < data.size(); i++)
			cout << setw(5) << i;
		cout << endl << setw(8) << "data:";
		for (auto i : data)
			cout << setw(5) << i;
		cout << endl;
		cout << "input direction:\nSet weight now?(Y/N) ";
		char flag;
		cin >> flag;
		cout << "direction:\n";
		if (flag == 'Y' || flag == 'y')
			while (cin >> a >> b >> w)
			{
				vector<int> t = getDir(a, b, w);
				dir.push_back(t);
			}
		else
			while (cin >> a >> b)
			{
				vector<int> t = getDir(a, b);
				dir.push_back(t);
			}
		pair<vector<type>, vector<vector<int>>> s(data, dir);
		return s;
	}
	vector<int> getDir(int a, int b, int w = -1)
	{
		vector<int> t;
		t.push_back(a);
		t.push_back(b);
		t.push_back(w);
		return t;
	}
	void create(vector<type> v, vector<vector<int>> dir)
	{
		currentNum = v.size();
		for (int i=0; i < v.size(); i++)
		{
			gVt<type>* n = newVt(i, v[i]);
			vertexs.push_back(n);
		}
		for (vector<int> p : dir)
			insertEdge(p[0], p[1], p[2]);
	}
	gVt<type>* find_by_data(int data)
	{
		for (gVt<type>* i : vertexs)
			if (i->data == data)
				return &i;
	};
	gVt<type>* find_by_id(int id)
	{
		for (gVt<type>* i : vertexs)
			if (i->id == id)
				return i;
	};
	vector<gVt<type>*> find_all(int data)
	{
		vector<gVt<type>*> s;
		for (gVt<type>* i : vertexs)
			if (i->data == data)
				s.push_back(i);
		return s;
	};
	gVt<type>* next(gVt<type>* now)
	{
		return now->next;
	};
	virtual void insertVertex(type data, vector<vector<int>> dir)
	{
		gVt<type>* new_ = newVt(currentNum, data);
		vertexs.push_back(new_);
		for (vector<int> p : dir)
			insertEdge(p[0], p[1], p[2]);
		currentNum++;
	};
	virtual void insertEdge(int a, int b, int w)
	{
		gVt<type>* Va = find_by_id(a),
				*Vb = find_by_id(b),
				*newB = newVt(Vb->id, Vb->data, Vb->weight);
		while (Va->next != nullptr)
			Va = Va->next;
		Va->weight = w;
		Va->next = newB;
	};
	virtual void changeWeight(int a, int b, int w)
	{
		gVt<type>* Va = find_by_id(a),
			     * Vb = find_by_id(b);
		while (Va->next->id != Vb->id)
			Va = Va->next;
		Va->weight = w;
	};
	virtual void deleteVertex(int id)
	{
		gVt<type>* t = find_by_id(id);
		deleteItem(vertexs, t);
		for (gVt<type>* i : vertexs)
			deleteEdge(i->id, t->id);
		currentNum--;
	};
	virtual void deleteEdge(int a, int b)
	{
		gVt<type>* Va = find_by_id(a), *Vb = find_by_id(b),
				*p1 = Va->next, *p2 = p1->next;
		while (p2->next != nullptr)
		{
			if (p1 == Vb)
			{
				Va->next = p2;
				break;
			}
			p1 = p2;
			Va = p1;
			p2 = p2->next;
		}
		if (p2 == Vb)
			p1->next = nullptr;
	};

};

class undirectedGragh : graph<int>
{
public:
	using dir_iter = vector<vector<int>>::iterator;
	void create()
	{
		Input<int> in = graph::input();
		create(in.first, in.second);
	}
	void create(vector<int> v, vector<vector<int>> dir)
	{
		for (int i = 0; i < dir.size(); i++)
			if (!has_inverse(dir, dir[i]))
			{
				vector<int> t;
				t.push_back(dir[i][1]);
				t.push_back(dir[i][0]);
				t.push_back(dir[i][2]);
				dir.push_back(t);
			}
		graph::create(v, dir);
	}
	bool has_inverse(vector<vector<int>> v, vector<int> p)
	{
		for (auto i : v)
			if (i[0] == p[1]
				&& i[1] == p[0])
				return true;
		return false;
	}
};



#endif // !DATASTRUCTURES_H