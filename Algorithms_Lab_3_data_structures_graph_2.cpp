// Autor: Magda Szafranska, nr indeksu AHNS: 18345
// Informatyka NST, rok 2, sem. 3
// Algorytmy, laboratoria nr 3, part II

#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

class TItem
{
	friend class TList;
public: int FData;
	  TItem* FNext;
	  TItem* FPrev;

public:
	TItem(TItem* APrev, TItem* ANext, int AData)
	{
		FPrev = APrev;
		FNext = ANext;
		FData = AData;

		if (FPrev) FPrev->FNext = this;
		if (FNext) FNext->FPrev = this;
	}
	~TItem(void)
	{
		if (FPrev) FPrev->FNext = FNext;
		if (FNext) FNext->FPrev = FPrev;
	}
	TItem(TItem* ANext, int AData)
	{
		FData = AData;
		FNext = ANext;
	}
};

class TList
{
private:
	int FCount;
	TItem* FFirst;
	TItem* Flast;
	int FIndex;
	TItem* FCurr;
public:
	TList(void)
	{
		FCount = 0;
		FFirst = Flast = NULL;
		FIndex = -1;
		FCurr = NULL;
	}
	~TList(void)
	{
		Clear();
	}
	void Clear(void)
	{
		while (Flast)
		{
			if (Flast->FNext)
				delete Flast->FNext;
			Flast = Flast->FPrev;
		}
		FFirst = NULL;
		FCount = 0;
		FIndex = -1;
		FCurr = NULL;
	}

	int Add(double AData)
	{
		Flast = new TItem(Flast, NULL, AData);
		if (!FFirst) FFirst = Flast;
		return FCount++;
	}
	TItem* Get(int AIndex)
	{
		if (FIndex < 0)
		{
			FIndex = 0;
			FCurr = FFirst;
		}
		while (AIndex < FIndex)
		{
			FCurr = FCurr->FPrev;
			FIndex--;
		}
		while (AIndex > FIndex)
		{
			FCurr = FCurr->FNext;
			FIndex++;
		}
		return FCurr;
	}
	void Del(int Index)
	{
		TItem* Item = Get(Index);
		if (Item == FFirst) FFirst = Item->FNext;
		if (Item == Flast) Flast = Item->FPrev;
		delete Item;
		--FCount;
		FIndex = -1;
		FCurr = NULL;
	}
	int Count(void)
	{
		return FCount;
	}
	int operator[](int Index)
	{
		return Get(Index)->FData;
	}

	int Pop(void);
	void Push(int AData);
	bool IsExist(int AData);
};

void TList::Push(int AData)
{
	FFirst = new TItem(FFirst, AData);
}
int TList::Pop(void)
{
	int AData = FFirst->FData;
	TItem* AItem = FFirst;
	FFirst = FFirst->FNext;
	delete AItem;
	return AData;
}
bool TList::IsExist(int AData)
{
	TItem* Item = FFirst;
	while (Item)
		if (Item->FData == AData) return true;
		else Item = Item = Item->FNext;
	return false;
}

int main()
{
	TList list;
	list.Push(1);
	list.Push(2);
	list.Push(5);

	int x1 = list.Pop();
	int x2 = list.Pop();
	int x3 = list.Pop();

	cout << "x1 = " << x1 << endl;
	cout << "x2 = " << x2 << endl;
	cout << "x3 = " << x3 << endl << endl;

	// variables to writing to the text file
	fstream fTime, fCount;
	fTime.open("time_pro.txt", ios::out | ios::app);
	fCount.open("count_pro.txt", ios::out | ios::app);

	int T1, T2;
	int Count = 1000;
	int b = 500000;

	for (int j = 1; j <= 27; j += 1)			//the loop will execute 27 times
	{
		list.Clear();							// Clearing the list each time

		double Sum = 0.0;
		//Count = 10000000 +b;
		fCount << Count << endl;				// Writing current Count to the file
		cout << j << ". Count: " << Count;

		int T1 = GetTickCount64();

		while (Count--)
		{
			list.Add(rand());
		}

		for (int i = 0; i < list.Count(); ++i)
		{
			Sum += list[i];
		}
		int T2 = GetTickCount64();
		cout << "  |  Time: " << (T2 - T1) * 0.001 << " seconds." << endl;
		fTime << (T2 - T1) * 0.001 << endl;		// Writing the time of current Count to the file
		b += 500000;
		Count = 1000 + b;
	}

	fTime.close();
	fCount.close();
}