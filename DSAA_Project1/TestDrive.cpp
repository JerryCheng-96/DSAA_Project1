
#define _CRT_SECURE_NO_WARNINGS
#define CLISTSIZE 10000

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

void testSearch(LList* list, City** cityList);
void testSearch(ArrayList* list, City** cityList);

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
	genCityDB(name1->c_str());
	S_LinkedList* SLL = new S_LinkedList();
	City * cityList[CLISTSIZE];
	readCityList(cityList, name1->c_str());
	fillLists(SLL, cityList, CLISTSIZE);
	saveCityList(SLL, name1->c_str());

	system("pause");

	string* name2 = new string("CityList2_" + to_string(CLISTSIZE) + ".dat");
	genCityDB(name2->c_str());
	S_LinkedList* SLL2 = new S_LinkedList();
	City * cityList2[CLISTSIZE];
	readCityList(cityList2, name2->c_str());
	fillLists(SLL2, cityList2, CLISTSIZE);
	saveCityList(SLL2, name2->c_str());

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

void main() {
	genAllTestDB();
	/*
	City * cityList[CLISTSIZE];
	readCityList(cityList, "cityList1.dat");
	City * cityList2[CLISTSIZE];
	readCityList(cityList2, "cityList2.dat");
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

	//Copy main city list
	fillLists(lList, cityList, CLISTSIZE);
	cout << "LinkedList done." << endl;
	fillLists(SLList, cityList, CLISTSIZE);
	cout << "S_LinkedList done." << endl;
	fillLists(aList, cityList, CLISTSIZE);
	cout << "AList done." << endl;
	fillLists(SAList, cityList, CLISTSIZE);
	cout << "S_AList done." << endl;

	system("pause");
	system("cls");

	testSearch(lList, cityList);
	testSearch(lList, cityList2);
	system("pause");
	system("cls");

	testSearch(SLList, cityList);
	testSearch(SLList, cityList2);
	system("pause");
	system("cls");

	testSearch(aList, cityList);
	testSearch(aList, cityList2);
	system("pause");
	system("cls");

	testSearch(SAList, cityList);
	testSearch(SAList, cityList2);
	system("pause");
	system("cls");

	*/
	
}