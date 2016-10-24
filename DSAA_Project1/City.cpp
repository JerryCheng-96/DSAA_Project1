#include <iostream>
#include <string>

using namespace std;

//数据类：城市
class City
{
private:
	//属性：名称
	string name;
	//属性：坐标
	int coordinates[2];

public:

	//构造
	City(string iniName, int iniCoord[])
	{
		name = iniName;
		coordinates[0] = iniCoord[0];
		coordinates[1] = iniCoord[1];
	}

	City() {}

	//~City(){}

	//获取属性
	string getName()
	{
		return name;
	}

	int getX()
	{
		return coordinates[0];
	}

	int getY()
	{
		return coordinates[1];
	}

	int* getCoord()
	{
		return coordinates;
	}

	//设置属性
	void setName(string iniName)
	{
		name = iniName;
	}

	void setX(int iniX)
	{
		coordinates[0] = iniX;
	}

	void setY(int iniY)
	{
		coordinates[1] = iniY;
	}

	void setCoordinates(int iniCoord[])
	{
		coordinates[0] = iniCoord[0];
		coordinates[1] = iniCoord[1];
	}

	//打印记录
	void print()
	{
		cout << name << ",(" << coordinates[0] << "," << coordinates[1] << ")" << endl;
		return;
	}
};


//节点类
//template<typename E>
class Link
{
public:

	City* element;
	Link* next;

	Link(City* iniEle, Link* iniNext = NULL)
	{
		element = iniEle;
		next = iniNext;
	}

	Link(Link* iniNext = NULL)
	{
		next = iniNext;
	}

	//~Link(){}
};


//无序 含头节点的单链表
class LinkedList
{
public:
	Link* head;
	Link* curr;
	Link* tail;
	int cnt;

	//构造
	LinkedList()
	{
		head = new Link();
		tail = head;
		curr = head;
		cnt = 0;
	}

	//重置curr至head
	void reset()
	{
		curr = head;
	}

	//移动至下一个节点
	void next()
	{
		curr = curr->next;
	}

	//在末尾追加节点
	void append(City* target)
	{
		tail->next = new Link(target, NULL);
		tail = tail->next;
		cnt++;
	}

	//在curr操作元素前插入节点
	void insert(City* target)
	{
		Link* temp = new Link(target, curr->next);
		curr->next = temp;
		cnt++;
	}

	//删除当前记录
	void deleteCurr()
	{
		if (cnt != 0)
		{
			Link* temp = curr->next;
			if (curr->next->next == NULL)
			{
				tail = curr->next;
			}
			curr->next = curr->next->next;
			delete[] temp;
			cnt--;
		}
		return;
	}

	//在特定记录前插入节点（根据名称或坐标）
	void insertAfter(City* ele, const string& targetName)
	{
		Link* temp = curr;

		for (reset(); curr->next != NULL; curr = curr->next)
		{
			if (curr->next->element->getName() == targetName)
			{
				insert(ele);
				cnt++;
				return;
			}
		}

		cout << "Target element not found." << endl;
		return;
	}

	void insertAfter(City* ele, const int targetCoord[])
	{
		Link* temp = curr;

		for (reset(); curr->next != NULL; curr = curr->next)
		{
			if (curr->next->element->getCoord()[0] == targetCoord[0] &&
				curr->next->element->getCoord()[1] == targetCoord[1])
			{
				insert(ele);
				cnt++;
				curr = temp;
				return;
			}
		}

		curr = temp;
		cout << "Target element not found." << endl;
		return;
	}

	//删除一条记录（根据名称或坐标）
	void deleteBy(const string& targetName)
	{
		if (cnt != 0)
		{
			for (reset(); curr->next != NULL; curr = curr->next)
			{
				if (curr->next->element->getName() == targetName)
				{
					deleteCurr();
					return;
				}
			}
		}
	}

	void deleteBy(const int target[])
	{
		if (cnt != 0)
		{
			for (reset(); curr->next != NULL; curr = curr->next)
			{
				if (curr->next->element->getX() == target[0] && curr->next->element->getY() == target[1])
				{
					deleteCurr();
					return;
				}
			}
		}
	}

	//搜索一条记录（根据名称或坐标）
	Link* searchBy(const string& target)
	{
		for (reset(); curr->next != NULL; curr = curr->next)
		{
			if (curr->next->element->getName() == target)
			{
				return curr->next;
			}
		}
	}

	Link* searchBy(const int target[])
	{
		for (reset(); curr->next != NULL; curr = curr->next)
		{
			if (curr->next->element->getCoord()[0] == target[0] &&
				curr->next->element->getCoord()[1] == target[1])
			{
				return curr->next;
			}
		}
	}

	//打印出位于目标城市给定半径内的城市的记录
	void printInCircle(City* point, const int radius)
	{
		Link* temp = curr;
		//Link* temp2 = searchBy(point->getName());
		int* coord = NULL;

		for (reset(); curr->next != NULL; curr = curr->next)
		{
			coord = curr->next->element->getCoord();
			if (sqr(coord[0] - point->getX()) + sqr(coord[1] - point->getY()) <= radius*radius)
			{
				curr->next->element->print();
			}
		}

		curr = temp;
		return;
	}

private:
	int sqr(int x)
	{
		return x*x;
	}
};

//无序 顺序表
class AList
{
public:
	City** elements;
	int cnt;
	int curr;
	int MAXLEN;

	AList(int maxlen)
	{
		elements = new City*[maxlen];
		MAXLEN = maxlen;
		cnt = 0;
		curr = 0;
	}

	//在末尾追加节点
	void append(City* ele)
	{
		if (cnt < MAXLEN)
		{
			elements[cnt] = ele;
			cnt++;
		}
		else
		{
			cout << "List is full.Fail to append." << endl;
		}
	}

	//在curr前插入节点
	void insert(City* ele)
	{
		if (cnt < MAXLEN)
		{
			for (int i = cnt; i > curr; i--)
			{
				elements[i] = elements[i - 1];
			}
			elements[curr] = ele;
			cnt++;
		}
		else
		{
			cout << "List is full.Fail to insert." << endl;
		}
		return;
	}

	//删除当前记录
	void deleteCurr()
	{
		if (cnt != 0 && curr < cnt)
		{
			if (curr < cnt - 1)
			{
				for (int i = curr; i < cnt - 1; i++)
				{
					elements[i] = elements[i + 1];
				}
			}
			else
			{
				delete elements[curr];
				if (cnt > 1)
				{
					curr--;
				}
			}
			cnt--;
		}
	}

	//在特定记录前插入节点（根据名称或坐标）
	void insertBefore(City* ele, const string& target)
	{
		if (cnt < MAXLEN)
		{
			int temp = curr;
			for (curr = 0; curr < cnt; curr++)
			{
				if (elements[curr]->getName() == target)
				{
					insert(ele);
					curr = temp;
					return;
				}
			}
			cout << "Target not found." << endl;
		}
		else
		{
			cout << "List is full.Fail to append." << endl;
		}
		return;
	}

	void insertBefore(City* ele, const int target[])
	{
		if (cnt < MAXLEN)
		{
			int temp = curr;
			for (curr = 0; curr < cnt; curr++)
			{
				if (target[0] == elements[curr]->getX() && target[1] == elements[curr]->getY())
				{
					insert(ele);
					curr = temp;
					return;
				}
			}
			cout << "Target not found." << endl;
		}
		else
		{
			cout << "List is full.Fail to append." << endl;
		}
		return;
	}

	//搜索一条记录（根据名称或坐标）
	City* searchBy(const string& target)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (target == elements[i]->getName())
			{
				return elements[i];
			}
		}
		cout << "Target not found." << endl;
		return NULL;
	}

	City* searchBy(const int target[])
	{
		for (int i = 0; i < cnt; i++)
		{
			if (target[0] == elements[i]->getX() && target[1] == elements[i]->getY())
			{
				return elements[i];
			}
		}
		cout << "Target not found." << endl;
		return NULL;
	}

	//删除一条记录（根据名称或坐标）
	void deleteBy(const string& target)
	{
		int i = curr;
		for (curr = 0; curr < cnt; curr++)
		{
			if (target == elements[i]->getName())
			{
				deleteCurr();
				curr = i;
				return;
			}
		}
		cout << "Target not found." << endl;
		return;
	}

	void deleteBy(const int target[])
	{
		int i = curr;
		for (curr = 0; curr < cnt; curr++)
		{
			if (target[0] == elements[i]->getX() && target[1] == elements[i]->getY())
			{
				deleteCurr();
				curr = i;
				return;
			}
		}
		cout << "Target not found." << endl;
		return;
	}

	//打印出位于目标城市给定半径内的城市的记录
	void printInCircle(City* point, const int radius)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (sqr(elements[i]->getX() - point->getX()) + sqr(elements[i]->getY() - point->getY()) <= radius*radius)
			{
				elements[i]->print();
			}
		}
		return;
	}

private:
	int sqr(int x)
	{
		return x*x;
	}
};

//姓名字母顺序 含头节点的单链表
class S_LinkedList
{
public:
	Link* head;
	Link* curr;
	Link* tail;
	int cnt;

	//构造
	S_LinkedList()
	{
		head = new Link();
		tail = head;
		curr = head;
		cnt = 0;
	}

	//重置curr至head
	void reset()
	{
		curr = head;
	}

	//向后移动n次
	void next(int n = 1)
	{
		for (int i = 0; i < n; i++)
		{
			curr = curr->next;
		}
		return;
	}

	//追加节点，保证元素顺序不变
	void append(City* target)
	{
		for (Link* temp = head; temp->next != NULL; temp = temp->next)
		{
			if (temp->next->element->getName() > target->getName())
			{
				Link* link = new Link(target, temp->next);
				temp->next = link;
				return;
			}
		}
	}

	//删除当前记录
	void deleteCurr()
	{
		if (cnt != 0)
		{
			Link* temp = curr->next;
			if (curr->next->next == NULL)
			{
				tail = curr->next;
			}
			curr->next = curr->next->next;
			delete[] temp;
			cnt--;
		}
		return;
	}

	//二分法搜索一条记录（根据名称）
	Link* searchBy(const string& target, int l, int r)
	{
		if (r <= l)
		{
			return NULL;
		}

		int c = (l + r) / 2;
		reset();
		next(c);

		if (curr->next->element->getName() > target)
		{
			return searchBy(target, l, c);
		}
		else if (curr->next->element->getName() < target)
		{
			return searchBy(target, c, r);
		}
		else if (curr->next->element->getName() == target)
		{
			return curr->next;
		}
	}

	/*
	Link* searchBy(const int target[])
	{
		for(reset();curr->next != NULL;curr = curr->next)
		{
			if(curr->next->element->getCoord()[0]==target[0]&&
				curr->next->element->getCoord()[1]==target[1])
			{
				return curr->next;
			}
		}
	}
	*/

	//二分法搜索并删除一条记录（根据名称）
	void deleteBy(const string& target, int l, int r)
	{
		if (r <= l)
		{
			return;
		}

		int c = (l + r) / 2;
		reset();
		next(c);

		if (curr->next->element->getName() > target)
		{
			deleteBy(target, l, c);
		}
		else if (curr->next->element->getName() < target)
		{
			deleteBy(target, c, r);
		}
		else if (curr->next->element->getName() == target)
		{
			deleteCurr();
		}
	}

	//打印出位于目标城市给定半径内的城市的记录
	void printInCircle(City* point, const int radius)
	{
		Link* temp = curr;
		//Link* temp2 = searchBy(point->getName());
		int* coord = NULL;

		for (reset(); curr->next != NULL; curr = curr->next)
		{
			coord = curr->next->element->getCoord();
			if (sqr(coord[0] - point->getX()) + sqr(coord[1] - point->getY()) <= radius*radius)
			{
				curr->next->element->print();
			}
		}

		curr = temp;
		return;
	}

private:
	int sqr(int x)
	{
		return x*x;
	}

};

//姓名字母顺序 顺序表
class S_AList
{
public:
	City** elements;
	int cnt;
	int curr;
	int MAXLEN;

	S_AList(int maxlen)
	{
		elements = new City*[maxlen];
		MAXLEN = maxlen;
		cnt = 0;
		curr = 0;
	}

	//追加节点，保证顺序不变
	void append(City* ele)
	{
		if (cnt < MAXLEN)
		{
			int temp = curr;
			for (curr = 0; curr < cnt; curr++)
			{
				if (elements[curr]->getName() > ele->getName())
				{
					insert(ele);
				}
			}
			cnt++;
		}
		else
		{
			cout << "List is full.Fail to append." << endl;
		}
	}

	/*
	//搜索一条记录（根据名称或坐标）
	City* searchBy(const string& target)
	{
		for(int i = 0;i<cnt;i++)
		{
			if(target==elements[i]->getName())
			{
				return elements[i];
			}
		}
		cout<<"Target not found."<<endl;
		return NULL;
	}
	*/

	//二分法搜索一条记录（根据名称）
	City* searchBy(const string& target, int l, int r)
	{
		if (r <= l)
		{
			return NULL;
		}

		int c = (l + r) / 2;
		curr = 0;
		curr += c;

		if (elements[curr]->getName() > target)
		{
			return searchBy(target, l, c);
		}
		else if (elements[curr]->getName() < target)
		{
			return searchBy(target, c, r);
		}
		else if (elements[curr]->getName() == target)
		{
			return elements[curr];
		}
	}

	//二分法搜索并删除一条记录（根据名称）
	void deleteBy(const string& target, int l, int r)
	{
		if (r <= l)
		{
			return;
		}

		int c = (l + r) / 2;
		curr = 0;
		curr += c;

		if (elements[curr]->getName() > target)
		{
			deleteBy(target, l, c);
		}
		else if (elements[curr]->getName() < target)
		{
			deleteBy(target, c, r);
		}
		else if (elements[curr]->getName() == target)
		{
			deleteCurr();
		}
	}

	//打印出位于目标城市给定半径内的城市的记录
	void printInCircle(City* point, const int radius)
	{
		for (int i = 0; i < cnt; i++)
		{
			if (sqr(elements[i]->getX() - point->getX()) + sqr(elements[i]->getY() - point->getY()) <= radius*radius)
			{
				elements[curr]->print();
			}
		}
		return;
	}

private:
	//在当前位置之前插入元素
	void insert(City* ele)
	{
		for (int i = cnt; i > curr; i--)
		{
			elements[i] = elements[i - 1];
		}
		elements[curr] = ele;
		cnt++;
		return;
	}

	//删除当前记录
	void deleteCurr()
	{
		if (cnt != 0 && curr < cnt)
		{
			if (curr < cnt - 1)
			{
				for (int i = curr; i < cnt - 1; i++)
				{
					elements[i] = elements[i + 1];
				}
			}
			else
			{
				delete elements[curr];
				if (cnt > 1)
				{
					curr--;
				}
			}
			cnt--;
		}
	}

	//计算平方
	int sqr(int x)
	{
		return x*x;
	}
};