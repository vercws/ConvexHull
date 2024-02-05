#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Classes.h"

template <typename T>
void DynamicArray<T>::addTail(T*& data)
{

	T** tempArr = new T * [current_size + 1];
	for (int i = 0; i < current_size; i++)
	{
		tempArr[i] = dane[i];
	}

	delete[] dane;
	dane = tempArr;

	current_size++;
	dane[current_size - 1] = data;

}


template <typename T>
void DynamicArray<T>::deleteAll()
{
	for (int i = 0; i < current_size; i++)
	{
		delete dane[i];
		dane[i] = nullptr;
	}
	delete[] dane;
	dane = nullptr;
	current_size = 0;
}

template <typename T>
void DynamicArray<T>::displayAllElements()
{
	for (int i = 0; i < current_size; i++)
	{
		std::cout << "Dane pod indeksem " << i << ":" << std::endl;
		std::cout << dane[i] << "\n\n";
	}

}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::Merge(Comparator comp, int left, int middle, int right)
{
	int i, j, k;
	int n1 = middle - left + 1;
	int n2 = right - middle;

	T** leftArray = new T * [n1];
	T** rightArray = new T * [n2];

	for (i = 0; i < n1; i++)
		leftArray[i] = dane[left + i];
	for (j = 0; j < n2; j++)
		rightArray[j] = dane[middle + 1 + j];

	i = 0;
	j = 0;
	k = left;
	while (i < n1 && j < n2) {
		if (!comp(leftArray[i], rightArray[j])) {
			dane[k] = leftArray[i];
			i++;
		}
		else {
			dane[k] = rightArray[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		dane[k] = leftArray[i];
		i++;
		k++;
	}

	while (j < n2) {
		dane[k] = rightArray[j];
		j++;
		k++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::MergeSortHelper(Comparator comp, int left, int right)
{
	if (left < right) {
		int middle = left + (right - left) / 2;

		MergeSortHelper(comp, left, middle);
		MergeSortHelper(comp, middle + 1, right);

		Merge(comp, left, middle, right);
	}
}

template <typename T>
template <typename Comparator>
void DynamicArray<T>::MergeSort(Comparator comp)
{
	MergeSortHelper(comp, 0, current_size - 1);
}

template <typename T>
void DynamicArray<T>::changeData(T*& data, int index)
{
	if (index < 0 || index > current_size - 1)
	{
		std::cout << "Indeks poza zakresem tablicy" << std::endl;
		return;
	}
	else
	{
		delete dane[index];
		dane[index] = data;
		std::cout << "Dane pod wskazanym indeksem zostały zmienione" << std::endl;
	}

}

template <typename T>
T* DynamicArray<T>::returnData(int index)
{
	if (index < 0 || index > current_size - 1)
	{
		std::cout << "Indeks poza zakresem tablicy" << std::endl;
		return nullptr;
	}
	else
	{
		return dane[index];
	}
}

double comp(const Node* n1, const Node* n2)
{
	return n1->y * n2->x - n2->y * n1->x;
}

int Orientation(const Node* n1, const Node* n2, const Node* n3)
{
	//double result = (n3->y - n2->y) * (n2->x - n1->x) - (n3->x - n2->x) * (n2->y - n1->y);
	Node* temp1 = new Node(n3->x - n2->x, n3->y - n2->y);
	Node* temp2 = new Node(n2->x - n1->x, n2->y - n1->y);
	double res = comp(temp1, temp2);
	delete temp1;
	delete temp2;
	
	if (res > 0) return -1; //zakręt w lewo
	else if (res < 0) return 1; //zakręt w prawo
	else return 1; //po prostej

}

DynamicArray<Node> GrahamScan(DynamicArray<Node> points, PointCompare compare, SortCompare compare2)
{
	
	if (points.current_size < 3)
	{
		std::cout << "Za mało punktów...\n";
		return points;
	}

    Node* newMid = points[0];

    for (int i = 0; i < points.current_size; i++)
    { 
		if (compare(newMid, points[i]))
		{
			newMid = points[i];
		}
    }
	DynamicArray<Node> pointsCopy = points.copyArray(points, newMid);
	for (int i = 0; i < pointsCopy.current_size; i++)
	{
		pointsCopy.dane[i]->x = pointsCopy.dane[i]->x - newMid->x;
		pointsCopy.dane[i]->y = pointsCopy.dane[i]->y - newMid->y;
	}

	clock_t s1 = clock();
	pointsCopy.MergeSort(compare2);
	clock_t e1 = clock();
	double time1 = (e1 - s1) / (double)CLOCKS_PER_SEC;
	

	DynamicArray<Node> ConvexHull;
	ConvexHull.addTail(newMid);
	ConvexHull.addTail(pointsCopy.dane[0]);


	std::cout << "New middle: ";
	std::cout << newMid->x << " " << newMid->y << std::endl;


	clock_t s2 = clock();
	for (int i = 2; i < pointsCopy.current_size; i++)
	{
		ConvexHull.addTail(pointsCopy.dane[i]);
		std::cout << pointsCopy.dane[i]->indeks << " " << std::endl;

		while (Orientation(ConvexHull.dane[ConvexHull.current_size - 3], ConvexHull.dane[ConvexHull.current_size - 2], ConvexHull.dane[ConvexHull.current_size-1]) == 1)
		{
			std::swap(ConvexHull.dane[ConvexHull.current_size -2], ConvexHull.dane[ConvexHull.current_size-1]);
			delete ConvexHull.dane[ConvexHull.current_size-1];
			ConvexHull.dane[ConvexHull.current_size-1] = nullptr;
			ConvexHull.current_size--;
		}
		
	}
	clock_t e2 = clock();
	double time2 = (e2 - s2) / (double)CLOCKS_PER_SEC;

	std::cout << "Number of points in convex hull: " << ConvexHull.current_size << std::endl;
	std::cout << "Indexes of points in the original array: " << std::endl;
	for (int i = 0; i < ConvexHull.current_size; i++)
	{
		std::cout << ConvexHull.dane[i]->indeks << std::endl;
	}
	std::cout << "\n" << "Sorting time : " << time1 << "\n";
	std::cout << "Main loop time: " << time2;
	return ConvexHull;
}

void LoadFromFile(std::string fileName, DynamicArray<Node>& tab)
{
	std::fstream file(fileName);
	int n;
	
	file >> n;
	double X = 0;
	double Y = 0;
	for (int i = 0; i < n; i++)
	{
		file >> X >> Y;
		Node* newNode = new Node(X, Y);
		newNode->indeks = i;
		tab.addTail(newNode);
	}
	file.close();
}
