
#define _CRT_SECURE_NO_WARNINGS
#define CLISTSIZE 10000
#define TESTROUNDS 250

#include "Project_CityDB.cpp"

//Test Drives
//***********

void genRandomCities(City * cityList[], int n);
void genCityDB(char*);
void genAllTestDB();

void saveCityList(City* cityList[], const char* name);
void saveCityList(LList* , const char* name);

void readCityList(City* cityList[], const char* name);
void readCityList(LList* cityList, const char* name);

void fillLists(Lists* list, City* ori[], int size);

void printList(LList* list);
void printList(ArrayList* list);

void testRandomSearch(LList* list, City** cityList, int testTimes);
void testRandomSearch(ArrayList* list, City** cityList, int testTimes);
void testHTSearch(LList* list, City** cityList);
void testHTSearch(ArrayList* list, City** cityList);

void testRandomDelete(LList* list, City** cityList, int testTimes);
void testRandomDelete(ArrayList* list, City** cityList, int testTimes);
void testHTDelete(LList* list, City** cityList);
void testHTDelete(ArrayList* list, City** cityList);

void genRandomCities(City * cityList[], int n)
{
	char nowName[11] = { '\0' };
	int nowCoo[2] = { -1, -1 };

	//Setting the seed of random number
	srand(time(NULL));

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

void genCityDB(const char * name)
{
	City * cityList[CLISTSIZE];
	genRandomCities(cityList, CLISTSIZE);
	saveCityList(cityList, name);
}

void genAllTestDB()
{
	string* name1 = new string("CityList1_" + to_string(CLISTSIZE) + ".dat");
	string* name1s = new string("CityList1_" + to_string(CLISTSIZE) + "_Sorted.dat");
	genCityDB(name1->c_str());
	S_LinkedList* SLL = new S_LinkedList();
	City * cityList[CLISTSIZE];
	readCityList(cityList, name1->c_str());
	fillLists(SLL, cityList, CLISTSIZE);
	saveCityList(SLL, name1s->c_str());

	system("pause");

	string* name2 = new string("CityList2_" + to_string(CLISTSIZE) + ".dat");
	string* name2s = new string("CityList2_" + to_string(CLISTSIZE) + "_Sorted.dat");
	genCityDB(name2->c_str());
	S_LinkedList* SLL2 = new S_LinkedList();
	City * cityList2[CLISTSIZE];
	readCityList(cityList2, name2->c_str());
	fillLists(SLL2, cityList2, CLISTSIZE);
	saveCityList(SLL2, name2s->c_str());

}


void saveCityList(City * cityList[], const char * name)
{
	FILE* fp = fopen(name, "wb");

	for (int i = 0; i < CLISTSIZE; i++)
	{
		fwrite(cityList[i], sizeof(City), 1, fp);
	}

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}

}

void saveCityList(LList * cityList, const char * name)
{
	FILE* fp = fopen(name, "wb");

	while (cityList->curr->next)
	{
		fwrite(cityList->curr->next->element, sizeof(City), 1, fp);
		cityList->curr = cityList->curr->next;
	}

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}


void readCityList(City * cityList[], const char * name)
{
	FILE* fp = NULL;
	fp = fopen(name, "rb");

	if (fp != NULL)
	{
		City* nowCity = (City*)malloc(sizeof(City));
		for (int i = 0; i < CLISTSIZE; i++)
		{
			fread(nowCity, sizeof(City), 1, fp);
			cityList[i] = new City(nowCity->getName(), nowCity->getCoord());
		}
		fclose(fp);
		fp = NULL;
	}
	else {
		cout << "File not found." << endl;
	}
}

void readCityList(LList * cityList, const char * name)
{
	FILE* fp = NULL;
	fp = fopen(name, "rb");

	if (fp != NULL)
	{
		City* nowCity = (City*)malloc(sizeof(City));
		for (int i = 0; i < CLISTSIZE; i++)
		{
			fread(nowCity, sizeof(City), 1, fp);
			cityList->justAppend(new City(nowCity->getName(), nowCity->getCoord()));
		}
		fclose(fp);
		fp = NULL;
	}
	else {
		cout << "File not found." << endl;
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


void testRandomSearch(LList * list, City** cityList, int testTimes)
{
	int randNo;
	Link* elementFound = NULL;
	clock_t start = 0;
	clock_t end = 0;

	srand(time(NULL));

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		elementFound = list->searchBy(cityList[randNo]->getName());

		if (!cityList[randNo]->equals(elementFound->element))
		{
			cout << "Random Search Test failed. Now at ";
			cityList[randNo]->print();
			cout << endl;
			return;
		}
	}
	end = clock();
	cout << "Random Search OK. Test rounds: " << TESTROUNDS << ", Time consumed in ms: " << end - start << endl;
}

void testHTSearch(LList * list, City** cityList)
{
	Link* elementFound1 = NULL;
	Link* elementFound2 = NULL;
	Link* elementFound3 = NULL;
	Link* elementFound4 = NULL;

	elementFound1 = list->searchBy(cityList[0]->getName());
	elementFound2 = list->searchBy(cityList[CLISTSIZE - 1]->getName());
	elementFound3 = list->searchBy("Aaaaaaaaaa");
	elementFound4 = list->searchBy("Zzzzzzzzzz");

	if (cityList[0]->equals(elementFound1->element) 
		&& cityList[CLISTSIZE -1 ]->equals(elementFound2->element)
		&& !elementFound3 && !elementFound4)
	{
		cout << "HTSearch OK." << endl;
	}
	else {
		cout << "HTSearch failed." << endl;
	}
}

void testRandomSearch(ArrayList* list, City** cityList, int testTimes)
{
	int randNo;
	City* elementFound = NULL;
	clock_t start = 0;
	clock_t end = 0;

	srand(time(NULL));

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		elementFound = list->searchBy(cityList[randNo]->getName());

		if (!cityList[randNo]->equals(elementFound))
		{
			cout << "Random Search Test failed. Now at ";
			cityList[randNo]->print();
			cout << endl;
			return;
		}
	}
	end = clock();

	cout << "Random Search OK. Test rounds: " << TESTROUNDS << ", Time consumed in ms: " << end - start << endl;
}

void testHTSearch(ArrayList* list, City** cityList)
{
	City* elementFound1 = NULL;
	City* elementFound2 = NULL;
	City* elementFound3 = NULL;
	City* elementFound4 = NULL;

	elementFound1 = list->searchBy(cityList[0]->getName());
	elementFound2 = list->searchBy(cityList[CLISTSIZE - 1]->getName());
	elementFound3 = list->searchBy("Aaaaaaaaaa");
	elementFound4 = list->searchBy("Zzzzzzzzzz");

	if (cityList[0]->equals(elementFound1)
		&& cityList[CLISTSIZE - 1]->equals(elementFound2)
		&& !elementFound3 && !elementFound4)
	{
		cout << "HTSearch OK." << endl;
	}
	else {
		cout << "HTSearch failed." << endl;
	}
}


void testRandomDelete(LList * list, City ** cityList, int testTimes)
{
	int randNo;
	Link* elementFound = NULL;
	string elementDeleted;
	clock_t start;
	clock_t end;

	srand(time(NULL));

	if (testTimes > CLISTSIZE)
	{
		cout << "Too many test rounds." << endl;
		return;
	}

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		elementDeleted = cityList[randNo]->getName();
		list->deleteBy(cityList[randNo]->getName());
		elementFound = list->searchBy(elementDeleted);

		if (elementFound)
		{
			cout << "Testing delete failed. i = " << i << ", The element: ";
			elementFound->element->print();
			return;
		}

	}
	end = clock();
	cout << "Testing delete succeeded. Test rounds: " << TESTROUNDS << ", Time consumed in ms: " << (end - start) << endl;
}

void testRandomDelete(ArrayList * list, City ** cityList, int testTimes)
{
	int randNo;
	City* elementFound = NULL;
	string elementDeleted;
	clock_t start = 0;
	clock_t end = 0;

	srand(time(NULL));

	if (testTimes > CLISTSIZE)
	{
		cout << "Too many test rounds." << endl;
		return;
	}

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		elementDeleted = cityList[randNo]->getName();
		list->deleteBy(cityList[randNo]->getName());
		elementFound = list->searchBy(elementDeleted);

		if (elementFound)
		{
			cout << "Testing delete failed. i = " << i << ", The element: ";
			elementFound->print();
			return;
		}
	}
	end = clock();

	cout << "Testing delete succeeded. Test rounds: " << TESTROUNDS << ", Time consumed in ms: " << (end - start) << endl;
}

void main() {
	//Generating all test cases
	//genAllTestDB();

	//Initializing cityDB
	City * cityList1[CLISTSIZE];
	string* listName1 = new string("CityList1_" + to_string(CLISTSIZE) + ".dat");
	readCityList(cityList1, listName1->c_str());
	City * cityList2[CLISTSIZE];
	string* listName2 = new string("CityList2_" + to_string(CLISTSIZE) + ".dat");
	readCityList(cityList2, listName2->c_str());

	//Variables for timing
	clock_t start;
	clock_t end;

	//Print test parameters
	cout << "n = " << CLISTSIZE << endl;
	//cout << CLOCKS_PER_SEC << endl;

	//Initializing list variables
	LinkedList* lList = new LinkedList();
	S_LinkedList* SLList = new S_LinkedList();
	AList* aList = new AList(CLISTSIZE);
	S_AList* SAList = new S_AList(CLISTSIZE);

	string* listName1_s = new string("CityList1_" + to_string(CLISTSIZE) + "_Sorted.dat");

	fillLists(lList, cityList1, CLISTSIZE);
	readCityList(SLList, listName1_s->c_str());
	SLList->cnt = CLISTSIZE;
	fillLists(aList, cityList1, CLISTSIZE);
	readCityList(SAList->elements, listName1_s->c_str());
	SAList->cnt = CLISTSIZE;

	cout << "All DB Loaded." << endl << endl;

	//Testing search
	cout << "Testing search..." << endl;
	cout << endl;

	//Testing search in LinkedList
	cout << "Testing search - LinkedList" << endl;
	//Testing search for elements at head/tail
	testHTSearch(lList, cityList1);
	//Testing search for elements selected randomly
	testRandomSearch(lList, cityList1, TESTROUNDS);
	//Testing search for non-existing elements
	//testRandomSearch(lList, cityList2, TESTROUNDS);
	cout << endl;

	//Testing search in S_LinkedList
	cout << "Testing search - S_LinkedList" << endl;
	testHTSearch(SLList, cityList1);
	testRandomSearch(SLList, cityList1, TESTROUNDS);
	//testRandomSearch(SLList, cityList2, TESTROUNDS);
	cout << endl;

	//Testing search in ArrayList
	cout << "Testing search - ArrayList" << endl;
	testHTSearch(aList, SAList->elements);
	testRandomSearch(aList, cityList1, TESTROUNDS);
	//testRandomSearch(aList, cityList2, TESTROUNDS);
	cout << endl;

	//Testing search in S_AList
	cout << "Testing search - S_AList" << endl;
	testHTSearch(SAList, SAList->elements);
	testRandomSearch(SAList, cityList1, TESTROUNDS);
	//testRandomSearch(SAList, cityList2, TESTROUNDS);
	cout << endl;


	//Testing delete
	cout << endl;
	cout << "Testing delete..." << endl << endl;
	cout << "Testing delete - LinkedList" << endl;
	testRandomDelete(lList, cityList1, TESTROUNDS);
	cout << endl;

	cout << "Testing delete - S_LinkedList" << endl;
	testRandomDelete(SLList, cityList1, TESTROUNDS);
	cout << endl;

	cout << "Testing delete - ArrayList" << endl;
	testRandomDelete(aList, cityList1, TESTROUNDS);
	cout << endl;

	cout << "Testing delete - S_AList" << endl;
	testRandomDelete(SAList, cityList1, TESTROUNDS);
	cout << endl;
}
