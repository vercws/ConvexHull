
struct Node
{
	double x = 0.0;
	double y = 0.0;
	Node() {};
	Node(double NewX, double NewY)
	{
		x = NewX;
		y = NewY;
	}
	int indeks = 0;
};

class VectorCompare //gdy pierwsza wiêksza
{
public:
	bool operator()(const Node* n1, const Node* n2) const
	{
		if (n1->y*n2->x - n2->y*n1->x > 0) return true;
		else return false;

	}
};


class SortCompare //gdy pierwsza wiêksza i bardziej na prawo, gdy na tej samej wysokoœci
{
public:
	bool operator()(const Node* n1, const Node* n2) const
	{
		double crossprod = n1->y * n2->x - n2->y * n1->x;
		if (crossprod < 0) return false;
		else if (crossprod == 0)
		{
			if (n1->x > n2->x)
			{
				return true;
			}
			else return false;
		}
		else return true;

	}
};

class PointCompare //gdy pierwsza wiêksza i bardziej na prawo, gdy na tej samej wysokoœci
{
public:
	bool operator()(const Node* n1, const Node* n2) const
	{
		if (n1->y > n2->y) return true;
		else if (n1->y == n2->y)
		{
			if (n1->x > n2->x) return true;
			else return false;
		}
		else return false;

	}
};

template <typename T>
class DynamicArray
{
public:
	DynamicArray()
	{
		current_size = 0;
	}
	T*& operator[](int index)
	{
		return *&dane[index];
	};
	int current_size;
	T** dane = nullptr;
	void addTail(T*& data);
	template <typename Comparator>
	void Merge(Comparator comp, int left, int middle, int right);
	template <typename Comparator>
	void MergeSortHelper(Comparator comp, int left, int right);
	template <typename Comparator>
	void MergeSort(Comparator comp);
	T* returnData(int index);
	void changeData(T*& data, int index);
	void deleteAll();
	void displayAllElements();
	DynamicArray<T> copyArray(const DynamicArray<T>& source, Node* mid)
	{
		DynamicArray<T> copy;
		copy.current_size = source.current_size - 1;

		if (source.dane) {
			copy.dane = new T * [source.current_size - 1];
			int j = 0;
			for (int i = 0; i < source.current_size; i++) {

				if ((mid->x != source.dane[i]->x) || (mid->y != source.dane[i]->y)) {
					copy.dane[j] = new T(*(source.dane[i]));
					j++;
				}

			}
		}

		return copy;
	};

};
