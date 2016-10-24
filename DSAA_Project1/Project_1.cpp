#include <iostream>
#include <string>
#include <ctime>

#define CLISTSIZE 100

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

//列表总类
class Lists {
public:
	virtual void append(City*) = 0;
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
		return NULL;
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

	Link* searchBy(const string& target) {
		int headNo = 0;
		int tailNo = cnt - 1;
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


//Test Drives
//***********

void genRandomCities(City * cityList[], int n);

void fillLists(Lists* list, City* ori[], int size);

void printList(LList* list);
void printList(ArrayList* list);

void testSearch(LList* list, City** cityList);
void testSearch(ArrayList* list, City** cityList);


void main() {
	//Generating main city list
	City * cityList[CLISTSIZE];
	genRandomCities(cityList, CLISTSIZE);

	//Generating auxillary city list
	City * cityList2[CLISTSIZE];
	genRandomCities(cityList2, CLISTSIZE);

	//Variables for timing
	clock_t start;
	clock_t end;
	
	//Print main city list
	for (int i = 0; i < CLISTSIZE; i++)
	{
		cityList[i]->print();
	}
	cout << endl << endl;
	
	//Print test parameters
	cout << "n = " << CLISTSIZE << endl;
	//cout << CLOCKS_PER_SEC << endl;

	//Initializing list variables
	LinkedList* lList = new LinkedList();
	S_LinkedList* SLList = new S_LinkedList();
	AList* aList = new AList(CLISTSIZE);
	S_AList* SAList = new S_AList(CLISTSIZE);

	//Copy main city list
	fillLists(lList, cityList, CLISTSIZE);
	fillLists(SLList, cityList, CLISTSIZE);
	fillLists(aList, cityList, CLISTSIZE);
	fillLists(SAList, cityList, CLISTSIZE);

	cout << endl;
	cout << "Printing Origin List" << endl;
	printList(lList);

	system("pause");
	system("cls");

	cout << endl;
	cout << "Testing search I" << endl;
	//printList(lList);
	testSearch(lList, cityList);
	testSearch(lList, cityList2);

	system("pause");
	system("cls");

	cout << endl;
	cout << "Testing search II..." << endl;
	//printList(SLList);
	testSearch(SLList, cityList);
	testSearch(SLList, cityList2);
	
	system("pause");
	system("cls");

	cout << endl;
	cout << "Testing search III..." << endl;
	//printList(aList);
	testSearch(aList, cityList);
	testSearch(aList, cityList2);

	system("pause");
	system("cls");

	cout << endl;
	cout << "Testing search IV..." << endl;
	//printList(SAList);
	testSearch(SAList, cityList);
	testSearch(SAList, cityList2);
}

void genRandomCities(City * cityList[], int n)
{
	char nowName[11] = { '\0' };
	int nowCoo[2] = { -1, -1 };

	//Setting the seed of random number

	for (int i = 0; i < n; i++)
	{
		//Generating random city names
		nowName[0] = rand() % 26 + 65;
		for (int j = 1; j < 10; j++)
		{
			nowName[j] = rand() % 26 + 97;
		}
		string* strName = new string(nowName);
		
		//Generating random city coordinates
		nowCoo[0] = rand() % 1000;
		nowCoo[1] = rand() % 1000;

		//New City
		cityList[i] = new City(*strName, nowCoo);
	}
}

void fillLists(Lists* list, City* ori[], int size) {
	for (int i = 0; i < size; i++)
	{
		list->append(ori[i]);
	}
}


void printList(LList* list) {
	list->reset();
	while (list->curr->next != NULL)
	{
		list->curr = list->curr->next;
		list->curr->element->print();
	}
}

void printList(ArrayList* list) {
	for (int i = 0; i < list->MAXLEN; i++)
	{
		list->elements[i]->print();
	}
}

void testSearch(LList * list, City** cityList)
{
	int randNo;
	Link* elementFound = NULL;

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		cout << endl;
		cout << "The selected element: ";
		cityList[randNo]->print();
		cout << endl;

		elementFound = list->searchBy(cityList[randNo]->getName());

		if (elementFound)
		{
			cout << "The found element: ";
			elementFound->element->print();
			cout << endl;
		}
		else {
			cout << "Not found." << endl;
		}
		
	}
}

void testSearch(ArrayList* list, City** cityList)
{
	int randNo;
	City* elementFound = NULL;

	srand(time(NULL));

	for (int i = 0; i < 10; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		cout << endl;
		cout << "The selected element: ";
		cityList[randNo]->print();
		cout << endl;

		elementFound = list->searchBy(cityList[randNo]->getName());

		if (elementFound)
		{
			cout << "The found element: ";
			elementFound->print();
			cout << endl;
		}
		else {
			cout << "Not found." << endl;
		}

	}
}


