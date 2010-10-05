// Zack Tillotson
// Applied Algos
// Sept 2010

#include <iostream> // cin
#include <string>
#include <vector>
#include <math.h> // sqrt
#include <stdio.h> // printf
#include <algorithm> // sort

using namespace std;

// DEFS //////////////////////////////////////////////////////

const double MAX_MIN_DIST = 10000;

struct Point {
	double x, y;
	bool operator() (const Point a, const Point b) { // We will be sorting on just the x variable
		return a.x < b.x;
	}
};

// DECS //////////////////////////////////////////////////////

vector<Point> loadList(int count);
double columnScan(vector<Point> points);

// CODE /////////////////////////////////////////////////////

int main()
{

	int pointC = 0; // Number of points in this input set

	cin >> pointC;

	// While there are input sets
	while(pointC != 0) {

		// Load the list of points and find the smallest distance between two points
		double minD = columnScan(loadList(pointC));

		// Print the results
		if(minD >= MAX_MIN_DIST)
			printf("INFINITY\n");
		else
			printf("%.4f\n", minD); // Rounds to 4 decimal places

		cin >> pointC;

	}

	return 0;

}

// Load the specified number of points from standard in
vector<Point> loadList(int pointC) {

	vector<Point> ret;

	string line;

	for(int i = 0 ; i < pointC ; i++) {

		Point p;
		cin >> p.x >> p.y;
		ret.push_back(p);

	}

	return ret;

}

// Find the smallest distance between two points
double columnScan(vector<Point> points) {

	// Sort on x
	sort(points.begin(), points.end(), Point());

	double minD = (MAX_MIN_DIST + 1) * (MAX_MIN_DIST + 1); // The squared minimum distance found between points so far, start above the maximum minimum

	// For each point
	for(int i = 0 ; i < points.size() ; i++) {

		Point a = points.at(i);

		// Compare to each other point "to the right" which could plausibly beat the current best
		for(int j = i + 1 ; j < points.size() && (points.at(j).x - a.x) <= minD ; j++) {

			Point b = points.at(j);

			double dist = (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);

			if(dist < minD)
				minD = dist;

		}

	}

	// Remember to return the actual distance, not the squared distance
	return sqrt(minD);

}
