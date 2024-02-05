#include <iomanip>
#include "ConvexHull.h"


int main()
{
	std::cout << std::setprecision(15);
	PointCompare comp1;
	SortCompare comp2;

	std::cout << "The first example:\n";
	DynamicArray<Node> points1;
	LoadFromFile("points1.txt", points1);
	DynamicArray<Node> GS1 = GrahamScan(points1, comp1, comp2);

	std::cout << "\n\nThe second example:\n";
	DynamicArray<Node> points2;
	LoadFromFile("points2.txt", points2);
	DynamicArray<Node> GS2 = GrahamScan(points2, comp1, comp2);

	std::cout << "\n\nThe third example:\n";
	DynamicArray<Node> points3;
	LoadFromFile("points3.txt", points3);
	DynamicArray<Node> GS3 = GrahamScan(points3, comp1, comp2);


	/*std::cout << "\n\nThe fourth example:\n";
	DynamicArray<Node> points4;
	LoadFromFile("points5.txt", points4);
	DynamicArray<Node> GS5 = GrahamScan(points4, comp1, comp2);*/

	return 0;
}