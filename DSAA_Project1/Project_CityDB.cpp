#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

#define SQR(x) (x)*(x)

using namespace std;

//Source Code
//***********

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

	City(City* oriCity)
	{
		name = oriCity->getName();
		coordinates[0] = oriCity->getCoord()[0];
		coordinates[1] = oriCity->getCoord()[1];
	}

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

	string printStr()
	{
		stringstream strm1;
		stringstream strm2;
		string str1;
		string str2;

		strm1 << coordinates[0];
		strm2 << coordinates[1];
		strm1 >> str1;
		strm2 >> str2;

		return name + " " + str1 + "," + str2 + " " + '\n';
	}

	bool equals(City* anotherCity) {
		if (anotherCity)
		{
			return ((this->getName() == anotherCity->getName())
				&& (this->getCoord()[0] == anotherCity->getCoord()[0])
				&& (this->getCoord()[1] == anotherCity->getCoord()[1]));
		}
		else
		{
			return false;
		}
	}
};

//节点类
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
	bool equals(Link* anotherLink) {
		if (anotherLink)
		{
			return this->element->equals(anotherLink->element);
		}
		else
		{
			return false;
		}
	}
};

//列表总类
class Lists {
public:
	virtual void append(City*) = 0;
	virtual void deleteBy(const string&) = 0;
};

//链表总类
class LList: public Lists {
public:
	Link* head;
	Link* curr;
	Link* tail;
	int cnt;

	virtual void reset() = 0;
	//virtual void next() = 0;
	virtual void append(City*) = 0;
	virtual Link* searchBy(const string&) = 0;
	virtual void deleteBy(const string&) = 0;

	void justAppend(City* target) {
		tail->next = new Link(target, NULL);
		tail = tail->next;
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
				tail = curr;
			}
			curr->next = curr->next->next;
			delete[] temp;
			cnt--;
		}
		return;
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
		return NULL;
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
			if (SQR(coord[0] - point->getX()) + SQR(coord[1] - point->getY()) <= radius*radius)
			{
				curr->next->element->print();
			}
		}

		curr = temp;
		return;
	}

};

//数组总类
class ArrayList: public Lists {
public:
	City** elements;
	int cnt;
	int curr;
	int MAXLEN;

	virtual void append(City*) = 0;
	virtual City* searchBy(const string&) = 0;
	virtual void deleteBy(const string&) = 0;


	//删除当前记录
	/*
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
	*/

	void deleteCurr()
	{
		if (curr >= 0 && curr < cnt && cnt > 0)
		{
			delete elements[curr];
			if (curr != cnt - 1)
			{
				for (int i = curr; i < cnt - 1; i++)
				{
					elements[i] = elements[i + 1];
				}
			}
			else
			{
				curr--;
			}
			cnt--;
		}
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

	virtual void deleteBy(const int target[]) = 0;

	void saveListText(City * cityList[], const char * name, int testTimes)
	{
		FILE* fp = fopen(name, "w");
		string cityInfo;

		for (int i = 0; i < testTimes; i++)
		{
			fprintf(fp, cityList[i]->printStr().c_str());
		}

		if (fp != NULL)
		{
			fclose(fp);
			fp = NULL;
		}

	}
};

//无序 含头节点的单链表
class LinkedList: public LList
{
public:

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
					curr = head;
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
		return NULL;
	}
};

//无序 顺序表
class AList: public ArrayList
{
public:
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
			elements[cnt] = new City(ele->getName(), ele->getCoord());
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
			//cout << "Target not found." << endl;
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
			//cout << "Target not found." << endl;
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
		//cout << "Target not found." << endl;
		return NULL;
	}

	//删除一条记录（根据名称或坐标）
	void deleteBy(const string& target)
	{
		int i = curr;
		for (curr = 0, i = 0; curr < cnt; curr++, i++)
		{
			if (target == elements[curr]->getName())
			{
				deleteCurr();
				curr = i;
				this->cnt--;
				return;
			}
		}
		cout << "Target not found." << endl;
		return;
	}

	void deleteBy(const int target[])
	{
		for (curr = 0; curr < cnt; curr++)
		{
			if (target[0] == elements[curr]->getX() && target[1] == elements[curr]->getY())
			{
				deleteCurr();
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
			if (SQR(elements[i]->getX() - point->getX()) + SQR(elements[i]->getY() - point->getY()) <= radius*radius)
			{
				elements[i]->print();
			}
		}
		return;
	}
};

//姓名字母顺序 含头节点的单链表
class S_LinkedList: public LList
{
public:

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
		if (cnt == 0)
		{
			Link* link = new Link(target, NULL);
			head->next = link;
			tail = tail->next;
			cnt++;
			return;
		}
		
		for (Link* temp = head; temp->next != NULL; temp = temp->next)
		{
			if (temp->next->element->getName()>target->getName())
			{
				Link* link = new Link(target, temp->next);
				temp->next = link;
				cnt++;
				return;
			}
		}
		Link* link = new Link(target, NULL);
		tail->next = link;
		tail = tail->next;
		cnt++;
		return;
	}


	//二分法搜索一条记录（根据名称）
	Link* searchBy(const string& target) {
		int headNo = 1;
		int tailNo = cnt;
		int nowNo = (headNo + tailNo) / 2;
		
		Link* nowPos = forwardTo(nowNo);

		while (!(headNo == nowNo && headNo == (tailNo - 1)))
		{
			if (nowPos->element->getName() > target)
			{
				tailNo = nowNo;
			}
			else if (nowPos->element->getName() < target)
			{
				headNo = nowNo;
			}
			else if (nowPos->element->getName() == target)
			{
				return nowPos;
			}
			nowNo = (headNo + tailNo) / 2;
			nowPos = forwardTo(nowNo);
		}

		nowPos = forwardTo(headNo);
		if (nowPos->element->getName() == target)
		{
			return nowPos;
		}
		nowPos = forwardTo(tailNo);
		if (nowPos->element->getName() == target)
		{

			return nowPos;
		}
		return NULL;
	}

	
	//二分法搜索并删除一条记录（根据名称）
	void deleteBy(const string& target)
	{
		Link* temp = searchBy(target);
		reset();
		while (temp != NULL && !(curr->next == temp)) {
			curr = curr->next;
		}
		deleteCurr();
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
			if (SQR(coord[0] - point->getX()) + SQR(coord[1] - point->getY()) <= radius*radius)
			{
				curr->next->element->print();
			}
		}

		curr = temp;
		return;
	}

private:
	Link* forwardTo(int n) {
		Link* priCurr = head;
		for (int i = 0; i < n && i < cnt; i++)
		{
			priCurr = priCurr->next;
		}
		return priCurr;
	}
};

//姓名字母顺序 顺序表
class S_AList: public ArrayList
{
public:

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
			if (cnt == 0)
			{
				insert(ele);

			}
			else {
				for (curr = 0; curr < cnt; curr++)
				{
					if (elements[curr]->getName() > ele->getName())
					{
						break;
					}
				}
				insert(ele);
			}
		}
		else
		{
			cout << "List is full.Fail to append." << endl;
		}
	}

	City* searchBy(const string& target) {
		int headNo = 0;
		int tailNo = cnt - 1;
		int nowNo = (headNo + tailNo) / 2;

		while (!(headNo == nowNo && headNo == (tailNo - 1)))
		{
			if (elements[nowNo]->getName() > target)
			{
				tailNo = nowNo;
			}
			else if (elements[nowNo]->getName() < target)
			{
				headNo = nowNo;
			}
			else if (elements[nowNo]->getName() == target)
			{
				return elements[nowNo];
			}
			nowNo = (headNo + tailNo) / 2;
		}

		nowNo = headNo;
		if (elements[nowNo]->getName() == target)
		{
			return elements[nowNo];
		}
		nowNo = tailNo;
		if (elements[nowNo]->getName() == target)
		{
			return elements[nowNo];
		}
		return NULL;
	}

	//二分法搜索并删除一条记录（根据名称）

	void deleteBy(const string& target) 
	{
		int headNo = 0;
		int tailNo = cnt - 1;
		int nowNo = (headNo + tailNo) / 2;

		this->curr = -1;

		while (!(headNo == nowNo && headNo == (tailNo - 1)))
		{
			if (elements[nowNo]->getName() > target)
			{
				tailNo = nowNo;
			}
			else if (elements[nowNo]->getName() < target)
			{
				headNo = nowNo;
			}
			else if (elements[nowNo]->getName() == target)
			{
				this->curr = nowNo;
				if (curr != -1)
				{
					deleteCurr();
				}
				return;
			}
			nowNo = (headNo + tailNo) / 2;
		}

		nowNo = headNo;
		if (elements[nowNo]->getName() == target)
		{
			this->curr = nowNo;
		}
		nowNo = tailNo;
		if (elements[nowNo]->getName() == target)
		{
			this->curr = nowNo;
		}
		if (curr != -1)
		{
			this->cnt--;
			deleteCurr();
		}
	}

	void deleteBy(const int target[])
	{
		for (curr = 0; curr < cnt; curr++)
		{
			if (target[0] == elements[curr]->getX() && target[1] == elements[curr]->getY())
			{
				deleteCurr();
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
			if (SQR(elements[i]->getX() - point->getX()) + SQR(elements[i]->getY() - point->getY()) <= radius*radius)
			{
				elements[curr]->print();
			}
		}
		return;
	}

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
};


