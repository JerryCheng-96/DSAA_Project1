
#define _CRT_SECURE_NO_WARNINGS
#define CLISTSIZE 1000
#define TESTROUNDS 100
#define RANDOMSEED 1478007507
//1478006927
//1478006688
#define TESTCASES 1

#include "Project_CityDB.cpp"

using namespace std;

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

void testRandomSearchByCoordinates(LList* list, City** cityList, int testTimes);
void testRandomSearchByCoordinates(ArrayList* list, City** cityList, int testTimes);
void testRandomDeleteByCoordinates(LList* list, City** cityList, int testTimes);
void testRandomDeleteByCoordinates(ArrayList* list, City** cityList, int testTimes);

void testInsert(ArrayList* list, City** cityList, int testTimes);
void testInsert(LList* list, City** cityList, int testTimes);


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
		nowCoo[0] = rand() % 100000;
		nowCoo[1] = rand() % 100000;

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

void saveCityListText(City * cityList[], const char * name)
{
	FILE* fp = fopen(name, "w");
	string cityInfo;

	for (int i = 0; i < CLISTSIZE; i++)
	{
		fprintf(fp, cityList[i]->printStr().c_str());
	}

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}

}

void saveCityListText(LList * cityList, const char * name)
{
	FILE* fp = fopen(name, "w");

	while (cityList->curr->next)
	{
		fprintf(fp, cityList->curr->next->element->printStr().c_str());
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
		list->append(new City(ori[i]));
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
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	Link* elementFound = NULL;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

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
	cout << "Name Random Search OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
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
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	City* elementFound = NULL;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

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

	cout << "Name Random Search OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
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
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	Link* elementFound = NULL;
	string elementDeleted;
	clock_t start;
	clock_t end;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

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

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

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
	cout << "Testing name delete OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}

void testRandomDelete(ArrayList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	City* elementFound = NULL;
	string elementDeleted;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

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

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		elementDeleted = cityList[randNo]->getName();
		elementFound = list->searchBy(elementDeleted);
		if (!elementFound)
		{
			cout << "The element to delete is not exist." << endl;
			i--;
			continue;
		}
		else
		{
			elementFound = NULL;
			list->deleteBy(cityList[randNo]->getName());
			elementFound = list->searchBy(elementDeleted);

			if (elementFound)
			{
				cout << "Testing delete failed. i = " << i << ", The element: ";
				elementFound->print();
				return;
			}
			//string fileName = "DelNameAfter_" + elementDeleted + "_.txt";
			//list->saveListText(list->elements, fileName.c_str(), list->cnt);
		}
	}
	end = clock();

	cout << "Testing name delete OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}

void testHTDelete(LList * list, City ** cityList)
{
	Link* elementFound1 = NULL;
	Link* elementFound2 = NULL;

	list->deleteBy(cityList[0]->getName());
	list->deleteBy(cityList[CLISTSIZE - 1]->getName());
	elementFound1 = list->searchBy(cityList[0]->getName());
	elementFound2 = list->searchBy(cityList[CLISTSIZE - 1]->getName());

	if (!elementFound1 && !elementFound2)
	{
		cout << "HTDelete OK." << endl;
	}
	else {
		cout << "HTDelete failed." << endl;
	}
}

void testHTDelete(ArrayList * list, City ** cityList)
{
	City* elementFound1 = NULL;
	City* elementFound2 = NULL;

	list->deleteBy(cityList[0]->getName());
	list->deleteBy(cityList[CLISTSIZE - 1]->getName());
	elementFound1 = list->searchBy(cityList[0]->getName());
	elementFound2 = list->searchBy(cityList[CLISTSIZE - 1]->getName());

	if (!elementFound1 && !elementFound2)
	{
		cout << "HTDelete OK." << endl;
	}
	else {
		cout << "HTDelete failed." << endl;
	}
}


void testRandomSearchByCoordinates(LList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	Link* elementFound = NULL;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		elementFound = list->searchBy(cityList[randNo]->getCoord());

		if (!cityList[randNo]->equals(elementFound->element))
		{
			cout << "Random Search Test failed. Now at ";
			cityList[randNo]->print();
			cout << endl;
			return;
		}
	}
	end = clock();
	cout << "Coordinates Random Search OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}

void testRandomSearchByCoordinates(ArrayList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	City* elementFound = NULL;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

	start = clock();
	for (int i = 0; i < testTimes; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		elementFound = list->searchBy(cityList[randNo]->getCoord());

		if (!cityList[randNo]->equals(elementFound))
		{
			cout << "Random Search Test failed. Now at ";
			cityList[randNo]->print();
			cout << endl;
			return;
		}
	}
	end = clock();

	cout << "Coordinates Random Search OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}

void testRandomDeleteByCoordinates(LList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	Link* elementFound = NULL;
	int elementDeleted[2];
	clock_t start;
	clock_t end;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

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

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		elementDeleted[0] = cityList[randNo]->getCoord()[0];
		elementDeleted[1] = cityList[randNo]->getCoord()[1];
		list->deleteBy(cityList[randNo]->getCoord());
		elementFound = list->searchBy(elementDeleted);

		if (elementFound)
		{
			cout << "Testing delete failed. i = " << i << ", The element: ";
			elementFound->element->print();
			return;
		}

	}
	end = clock();
	cout << "Testing coordinates delete OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}

void testRandomDeleteByCoordinates(ArrayList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	City* elementFound = NULL;
	int elementDeleted[2];
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

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

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		elementDeleted[0] = cityList[randNo]->getCoord()[0];
		elementDeleted[1] = cityList[randNo]->getCoord()[1];
		list->deleteBy(cityList[randNo]->getCoord());
		elementFound = list->searchBy(elementDeleted);

		if (elementFound)
		{
			cout << "Testing delete failed. i = " << i << ", The element: ";
			elementFound->print();
			return;
		}
	}
	end = clock();

	cout << "Testing coordinates delete OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}


void testInsert(ArrayList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	City* elementFound;
	string cityInserted;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

	start = clock();
	for (int i = 0; i < testTimes - 1; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		cityInserted = cityList[randNo]->getName();
		list->append(cityList[randNo]);
		elementFound = list->searchBy(cityInserted);

		if (!elementFound)
		{
			cout << "Testing insert failed. i = " << i << ", The element: ";
			elementFound->print();
			return;
		}
	}
	end = clock();

	cout << "Testing insert OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}

void testInsert(LList * list, City ** cityList, int testTimes)
{
	int randNo;
	int* randList = (int*)malloc(sizeof(int) * testTimes);
	Link* elementFound;
	string cityInserted;
	clock_t start = 0;
	clock_t end = 0;

	if (!RANDOMSEED)
	{
		time_t nowTime = time(NULL);
		srand(nowTime);
		cout << "The seed: " << nowTime << endl;
	}
	else
	{
		srand(RANDOMSEED);
	}

	start = clock();
	for (int i = 0; i < testTimes - 1; i++)
	{
		elementFound = NULL;
		randNo = rand() % CLISTSIZE;

		for (int j = 0; j < i; j++)
		{
			if (randNo == randList[j])
			{
				randNo = rand() % CLISTSIZE;
				j = 0;
				continue;
			}
		}
		randList[i] = randNo;

		cityInserted = cityList[randNo]->getName();
		list->append(cityList[randNo]);
		elementFound = list->searchBy(cityInserted);

		if (!elementFound)
		{
			cout << "Testing insert failed. i = " << i << ", The element: ";
			elementFound->element->print();
			return;
		}
	}
	end = clock();

	cout << "Testing insert OK. " << CLISTSIZE << ", " << TESTROUNDS << ", " << end - start << endl;
}



void main() {
	//Generating all test cases
	//genAllTestDB();	

	//Initializing cityDB
	City * cityList1[CLISTSIZE];
	string* listName1 = new string("CityList1_" + to_string(CLISTSIZE) + ".dat");
	//string* listName1t = new string("CityList1_" + to_string(CLISTSIZE) + ".txt");
	readCityList(cityList1, listName1->c_str());
	//saveCityListText(cityList1, listName1t->c_str());

	City * cityList2[CLISTSIZE];
	string* listName2 = new string("CityList2_" + to_string(CLISTSIZE) + ".dat");
	//string* listName2t = new string("CityList2_" + to_string(CLISTSIZE) + ".txt");
	readCityList(cityList2, listName2->c_str());
	//saveCityListText(cityList2, listName2t->c_str());

	//Variables for timing
	clock_t start;
	clock_t end;

	//Print test parameters
	cout << "n = " << CLISTSIZE << endl;
	//cout << CLOCKS_PER_SEC << endl;

	//Initializing list variables
	//Testing DBs for Search by name, Random Delete and Insert
	LinkedList* lList = new LinkedList();
	S_LinkedList* SLList = new S_LinkedList();
	AList* aList = new AList(CLISTSIZE);
	S_AList* SAList = new S_AList(CLISTSIZE);

	//Testing DBs for HT Search and Delete
	LinkedList* lList2 = new LinkedList();
	S_LinkedList* SLList2 = new S_LinkedList();
	AList* aList2 = new AList(CLISTSIZE);
	S_AList* SAList2 = new S_AList(CLISTSIZE);

	//Testing DBs for Search and Delete by coordinates
	LinkedList* lList3 = new LinkedList();
	S_LinkedList* SLList3 = new S_LinkedList();
	AList* aList3 = new AList(CLISTSIZE);
	S_AList* SAList3 = new S_AList(CLISTSIZE);

	string* listName1_s = new string("CityList1_" + to_string(CLISTSIZE) + "_Sorted.dat");

	//Loading DBs from pre-generated files to save time
	fillLists(lList, cityList1, CLISTSIZE);
	readCityList(SLList, listName1_s->c_str());
	SLList->cnt = CLISTSIZE;
	fillLists(aList, cityList1, CLISTSIZE);
	readCityList(SAList->elements, listName1_s->c_str());
	SAList->cnt = CLISTSIZE;

	fillLists(lList2, cityList1, CLISTSIZE);
	readCityList(SLList2, listName1_s->c_str());
	SLList2->cnt = CLISTSIZE;
	fillLists(aList2, cityList1, CLISTSIZE);
	readCityList(SAList2->elements, listName1_s->c_str());
	SAList2->cnt = CLISTSIZE;

	fillLists(lList3, cityList1, CLISTSIZE);
	readCityList(SLList3, listName1_s->c_str());
	SLList3->cnt = CLISTSIZE;
	fillLists(aList3, cityList1, CLISTSIZE);
	readCityList(SAList3->elements, listName1_s->c_str());
	SAList3->cnt = CLISTSIZE;

	cout << "All DB Loaded." << endl << endl;
	
	if (TESTCASES == 0 || TESTCASES == 1)
	{
		//Testing AList
		cout << "Testing AList... " << endl;
		//Testing Search by name, Random Delete and Insert
		testRandomSearch(aList, cityList1, TESTROUNDS);
		testRandomDelete(aList, cityList1, TESTROUNDS);
		testInsert(aList, cityList2, TESTROUNDS);
		//Testing HT Search and Delete
		testHTSearch(aList2, cityList1);
		testHTDelete(aList2, cityList1);
		//Testing Search and Delete by coordinates
		testRandomSearchByCoordinates(aList3, cityList1, TESTROUNDS);
		testRandomDeleteByCoordinates(aList3, cityList1, TESTROUNDS);
		//aList3->deleteBy(aList3->elements[2]->getCoord());
		cout << endl << endl;

		//Testing S_AList
		cout << "Testing S_AList... " << endl;
		//Testing Search by name, Random Delete and Insert
		testRandomSearch(SAList, cityList1, TESTROUNDS);
		testRandomDelete(SAList, cityList1, TESTROUNDS);
		testInsert(SAList, cityList2, TESTROUNDS);
		//Testing Search and Delete by coordinates
		testRandomSearchByCoordinates(SAList3, cityList1, TESTROUNDS);
		testRandomDeleteByCoordinates(SAList3, cityList1, TESTROUNDS);
		cout << endl << endl;
	}
	
	if (TESTCASES == 0 || TESTCASES == 2)
	{
		//Testing LinkedList
		cout << "Testing LinkedList... " << endl;
		//Testing Search by name, Random Delete and Insert
		testRandomSearch(lList, cityList1, TESTROUNDS);
		testRandomDelete(lList, cityList1, TESTROUNDS);
		testInsert(lList, cityList2, TESTROUNDS);
		//Testing HT Search and Delete
		testHTSearch(lList2, cityList1);
		testHTDelete(lList2, cityList1);
		//Testing Search and Delete by coordinates
		testRandomSearchByCoordinates(lList3, cityList1, TESTROUNDS);
		testRandomDeleteByCoordinates(lList3, cityList1, TESTROUNDS);
		cout << endl << endl;

		//Testing S_LinkedList
		cout << "Testing S_LinkedList... " << endl;
		//Testing Search by name, Random Delete and Insert
		testRandomSearch(SLList, cityList1, TESTROUNDS);
		testRandomDelete(SLList, cityList1, TESTROUNDS);
		testInsert(SLList, cityList2, TESTROUNDS);
		//Testing Search and Delete by coordinates
		testRandomSearchByCoordinates(SLList3, cityList1, TESTROUNDS);
		testRandomDeleteByCoordinates(SLList3, cityList1, TESTROUNDS);
		cout << endl << endl;
	}
}
