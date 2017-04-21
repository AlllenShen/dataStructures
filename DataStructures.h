#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H
#include <initializer_list>
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
};
#endif // !DATASTRUCTURES_H