#include <iostream>
#include <string>

using namespace std;

//�����ࣺ����
class City
{
private:
	//���ԣ�����
	string name;
	//���ԣ�����
	int coordinates[2];

public:

	//����
	City(string iniName, int iniCoord[])
	{
		name = iniName;
		coordinates[0] = iniCoord[0];
		coordinates[1] = iniCoord[1];
	}

	City() {}

	//~City(){}

	//��ȡ����
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

	//��������
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

	//��ӡ��¼
	void print()
	{
		cout << name << ",(" << coordinates[0] << "," << coordinates[1] << ")" << endl;
		return;
	}
};


//�ڵ���
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


//���� ��ͷ�ڵ�ĵ�����
class LinkedList
{
public:
	Link* head;
	Link* curr;
	Link* tail;
	int cnt;

	//����
	LinkedList()
	{
		head = new Link();
		tail = head;
		curr = head;
		cnt = 0;
	}

	//����curr��head
	void reset()
	{
		curr = head;
	}

	//�ƶ�����һ���ڵ�
	void next()
	{
		curr = curr->next;
	}

	//��ĩβ׷�ӽڵ�
	void append(City* target)
	{
		tail->next = new Link(target, NULL);
		tail = tail->next;
		cnt++;
	}

	//��curr����Ԫ��ǰ����ڵ�
	void insert(City* target)
	{
		Link* temp = new Link(target, curr->next);
		curr->next = temp;
		cnt++;
	}

	//ɾ����ǰ��¼
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

	//���ض���¼ǰ����ڵ㣨�������ƻ����꣩
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

	//ɾ��һ����¼���������ƻ����꣩
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

	//����һ����¼���������ƻ����꣩
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

	//��ӡ��λ��Ŀ����и����뾶�ڵĳ��еļ�¼
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

//���� ˳���
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

	//��ĩβ׷�ӽڵ�
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

	//��currǰ����ڵ�
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

	//ɾ����ǰ��¼
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

	//���ض���¼ǰ����ڵ㣨�������ƻ����꣩
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

	//����һ����¼���������ƻ����꣩
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

	//ɾ��һ����¼���������ƻ����꣩
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

	//��ӡ��λ��Ŀ����и����뾶�ڵĳ��еļ�¼
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

//������ĸ˳�� ��ͷ�ڵ�ĵ�����
class S_LinkedList
{
public:
	Link* head;
	Link* curr;
	Link* tail;
	int cnt;

	//����
	S_LinkedList()
	{
		head = new Link();
		tail = head;
		curr = head;
		cnt = 0;
	}

	//����curr��head
	void reset()
	{
		curr = head;
	}

	//����ƶ�n��
	void next(int n = 1)
	{
		for (int i = 0; i < n; i++)
		{
			curr = curr->next;
		}
		return;
	}

	//׷�ӽڵ㣬��֤Ԫ��˳�򲻱�
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

	//ɾ����ǰ��¼
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

	//���ַ�����һ����¼���������ƣ�
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

	//���ַ�������ɾ��һ����¼���������ƣ�
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

	//��ӡ��λ��Ŀ����и����뾶�ڵĳ��еļ�¼
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

//������ĸ˳�� ˳���
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

	//׷�ӽڵ㣬��֤˳�򲻱�
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
	//����һ����¼���������ƻ����꣩
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

	//���ַ�����һ����¼���������ƣ�
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

	//���ַ�������ɾ��һ����¼���������ƣ�
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

	//��ӡ��λ��Ŀ����и����뾶�ڵĳ��еļ�¼
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
	//�ڵ�ǰλ��֮ǰ����Ԫ��
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

	//ɾ����ǰ��¼
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

	//����ƽ��
	int sqr(int x)
	{
		return x*x;
	}
};