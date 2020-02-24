/*
 * project1.cpp: A program that takes in an integer followed by many doubles
 *   that are turned into points that can be graphed on a plane. These points
 *   are then used to create line segments, which are stored in an interval.
 *   Statistics about these lines are displayed as output, such as the formula
 *   of the lines, the x/y intersects of the lines, any possible intersections
 *   between lines, and so on.
 *
 *  Created on: Feb 14, 2020
 *      @author Jay Shoumaker
 */

#include <iostream>
using namespace std;

/**
 *  Finds the square root of a given number.
 *
 * 	@param num The number of which we want to find the square root of.
 * 	@return l The square root of num.
 */
double squareroot(double num) {
	double eps = 1e-6;
	double k = num;
	double l = 0.0, r, mid;

	if (k >= 1) {
		r = k;
	}
	if (k < 1) {
		r = 1;
	}

	while (l - k / l > eps || l - k / l < -eps) {
		mid = l + (r - l) / 2;
		if (mid < k / mid) {
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
}

/**
 * 	Function that rounds the input number to two digits.
 *
 * 	@param var The number we want to round.
 * 	@return value The input, rounded to two digits.
 */
double round(double var) {
	double value = (int) (var * 100.0);
	return (double) value / 100.0;
}



/**
 * 	Class that is responsible for handling any exception thrown to it.
 */
class Exception{};


/**
 * 	Class that handles exceptions specifically caused by LineSegment.
 */
class LineSegmentException: public Exception{};


/**
 * 	Class that handles exceptions specifically caused by Segments.
 */
class SegmentsException: public Exception{};

template <class DT>
class Point;
template <class DT>
ostream& operator << (ostream& s, Point<DT>& aPoint);

template <class DT>
class LineSegment;
template <class DT>
ostream& operator << (ostream& s, LineSegment<DT>& LS);

template <class DT>
class Segments;
template <class DT>
ostream& operator << (ostream& s, Segments<DT>& seg);


/**
 * 	Class that holds two doubles as a point along an x/y plane.
 */
template <class DT>
class Point {
	friend ostream& operator << (ostream& s, Point<DT>& aPoint);
protected:
	double x;
	double y;
public:
	Point();
	Point(double xVal, double yVal);
	void setLocation(double xVal, double yVal);
	double getXValue();
	double getYValue();
	void display();
	bool operator == (Point<DT>& P);

};

/**
 * 	Overloaded << operator for the Point class.
 */
template <class DT>
ostream& operator << (ostream& s, Point<DT>& aPoint){
	s << "(" << round(aPoint.x) << ", " << round(aPoint.y) << ")";
	return s;
}

template <class DT>
bool Point<DT>::operator == (Point<DT>& P){
	return ((x == P.x) && (y == P.y));
}

/**
 *  Default constructor for the Point class.
 */
template <class DT>
Point<DT>::Point() {
	x = 0.0;
	y = 0.0;
}

/**
 *  Constructor for the Point class.
 *
 *  @param xVal, yVal The coordinates of the new Point object.
 */
template <class DT>
Point<DT>::Point(double xVal, double yVal) {
	x = xVal;
	y = yVal;
}

/**
 *  Modifier for a Point's x & y variables.
 *
 * 	@param xVal, yVal The new coordinates of a Point Object.
 */
template <class DT>
void Point<DT>::setLocation(double xVal, double yVal) {
	x = xVal;
	y = yVal;
}

/**
 * 	Method that returns the X value of a Point.
 *
 * 	@return x The x coordinate of a Point.
 */
template <class DT>
double Point<DT>::getXValue() {
	return x;
}

/**
 * 	Method that returns the Y value of a Point.
 *
 * 	@return y The Y coordinate of a Point.
 */
template <class DT>
double Point<DT>::getYValue() {
	return y;
}

/**
 * 	Method that displays the Point in it's normal form
 * 	e.g. (0, 4), (-12.4, 32.39), (x, y)
 */
template <class DT>
void Point<DT>::display() {
	cout << "(" << round(x) << ", " << round(y) << ")";
}


/**
 * 	Class that holds a line segment consisting of two points along an x/y plane.
 */
template <class DT>
class LineSegment {
protected:
	Point<DT> P1;
	Point<DT> P2;
public:
	LineSegment();
	LineSegment(Point<DT> one, Point<DT> two);
	double length();
	Point<DT> midpoint();
	Point<DT> xIntercept();
	Point<DT> yIntercept();
	double slope();
	bool itIntersects(LineSegment L);
	Point<DT> intersectionPoint(LineSegment L);
	bool isParallel(LineSegment L);
	void displayEquation();
	Point<DT> getP1();
	Point<DT> getP2();
	friend ostream& operator << (ostream& s, LineSegment<DT>& LS);
};

/**
 * 	Overloaded << operator for the LineSegment class.
 */
template <class DT>
ostream& operator << (ostream& s, LineSegment<DT>& LS){
	s << "y=" << round(LS.slope()) << "*x+" << round(LS.yIntercept().getYValue());
	return s;
}

/**
 * 	Default constructor for the LineSegment class.
 */
template <class DT>
LineSegment<DT>::LineSegment() {
	P1 = Point<DT>(0, 0);
	P2 = Point<DT>(0, 0);
}

/**
 * 	Constructor for the LineSegment class.
 *
 * 	@param one, two Points that make up the line segment.
 */
template <class DT>
LineSegment<DT>::LineSegment(Point<DT> one, Point<DT> two) {
	P1 = one;
	P2 = two;
}

/**
 * 	Method that finds the length of a line segment.
 *
 * 	@return length The length of the object.
 */
template <class DT>
double LineSegment<DT>::length() {
	double length = 0.0;
	length = squareroot(((P2.getXValue() - P1.getXValue()) * (P2.getXValue() - P1.getXValue())) + ((P2.getYValue() - P1.getYValue()) * (P2.getYValue() - P1.getYValue())));
	return length;
}

/**
 *  Method that finds the midpoint of a line segment.
 *
 *  @return mid The point at the middle of the line segment.
 */
template <class DT>
Point<DT> LineSegment<DT>::midpoint() {
	Point<DT> mid;
	mid = Point<DT>(round((P1.getXValue() + P2.getXValue()) / 2), round((P1.getYValue() + P2.getYValue()) / 2));
	return mid;
}

/**
 * 	Method that finds the x-intercept of a line segment. The method assumes that the point
 * 	is a part of a whole line in order to find the intercept, rather than just the segment itself.
 *
 * 	@return xInt The x-intercept of the line.
 */
template <class DT>
Point<DT> LineSegment<DT>::xIntercept() {
	Point<DT> xInt;
	double slope = this->slope();
	double x = 0.0;
	x = -((this->yIntercept().getYValue())/slope);
	xInt = Point<DT>(x, 0);
	return xInt;
}

/**
 * 	Method that finds the y-intercept of a line segment. The method assumes that the point
 * 	is a part of a whole line in order to find the intercept, rather than just the segment itself.
 *
 * 	@return yInt The y-intercept of the line.
 */
template <class DT>
Point<DT> LineSegment<DT>::yIntercept() {
	Point<DT> yInt;
	double slope = this->slope();
	double y = 0.0;
	y = P1.getYValue() - (slope)*P1.getXValue();
	yInt = Point<DT>(0, y);
	return yInt;
}

/**
 * 	Method that finds the slope of a line segment.
 *
 * 	@return slope The slope of the line.
 */
template <class DT>
double LineSegment<DT>::slope() {
	double slope = 0.0;
	slope = ((P2.getYValue() - P1.getYValue()) / (P2.getXValue() - P1.getXValue()));
	return slope;
}

/**
 * 	Method that determines whether two line segments intersect or not.
 *
 * 	@param L The line segment that is currently being compared to.
 * 	@return intersect The status of whether the lines are intersected or not.
 */
template <class DT>
bool LineSegment<DT>::itIntersects(LineSegment L) {
	bool intersect = false;
	if (this->slope() != L.slope()){
		Point<DT> potentialIntersect = intersectionPoint(L);
		double first = this->P1.getXValue();
		double second = this->P2.getXValue();
		double third = L.P1.getXValue();
		double fourth = L.P2.getXValue();
		double potential = potentialIntersect.getXValue();
		if (first > second){
			first = this->P2.getXValue();
			second = this->P1.getXValue();
		}
		if (third > fourth){
			third = L.P2.getXValue();
			fourth = L.P1.getXValue();
		}
		if (first <= potential && potential <= second && third <= potential && potential <= fourth){
			intersect = true;
		}
	}
	return intersect;
}

/**
 * 	Method that finds the intersection of two line segments.
 *
 * 	@param L the line segment that is being used (along with the current line).
 * 	@return intersection The point at which the two segments intersect.
 */
template <class DT>
Point<DT> LineSegment<DT>::intersectionPoint(LineSegment L) {
	Point<DT> intersection;
	double x = round((L.yIntercept().getYValue() - this->yIntercept().getYValue())/(this->slope() - L.slope()));
	double y = round(((this->yIntercept().getYValue()*L.slope())-(L.yIntercept().getYValue()*this->slope()))/(L.slope() - this->slope()));
	intersection = Point<DT>(x, y);
	return intersection;
}

/**
 * 	Determines whether two line segments are parallel based on their slopes.
 *
 * 	@param L The line segment that is currently being compared to.
 * 	@return parallel The status of whether the lines are parallel or not.
 */
template <class DT>
bool LineSegment<DT>::isParallel(LineSegment L) {
	bool parallel = false;
	if (this->slope() == L.slope())
		parallel = true;
	return parallel;
}

/**
 *  Displays the line's formula as an equation in y=mx+c form.
 *  e.g. y=1.4x+5, y=-6x+-2
 */
template <class DT>
void LineSegment<DT>::displayEquation() {
	cout << "y=" << round(this->slope()) << "*x+" << round(this->yIntercept().getYValue());
}

/**
 *  Method that returns the first point of a line segment.
 *
 *  @return P1 The first point of the line segment.
 */
template <class DT>
Point<DT> LineSegment<DT>::getP1() {
	return P1;
}

/**
 *  Method that returns the second point of a line segment.
 *
 *  @return P2 The second point of the line segment.
 */
template <class DT>
Point<DT> LineSegment<DT>::getP2() {
	return P2;
}


/**
 * 	Class that holds multiple line segments to be displayed.
 */
template <class DT>
class Segments {
	protected:
		LineSegment<DT>* segments;
		int count;
		int maxSize;
	public:
		Segments();
		Segments(int size);
		void addLineSegment(LineSegment<DT> L);
		void display();
		Segments<DT>& aClosedPolygon();
		Segments<DT>& findAllIntersects(LineSegment<DT>& LS);
		~Segments();
		LineSegment<DT>& findClosest(Point<DT>& aPoint);
		int findClosestIndex(Point<DT>& aPoint);
		int getSize();
		LineSegment<DT> getSegmentAt(int index);
		friend ostream& operator << (ostream& s, Segments<DT>& seg);
};

template <class DT>
ostream& operator << (ostream& s, Segments<DT>& seg){
	//TODO
	for (int i = 0; i < seg.maxSize; i++){
		s << "Line Segment " << (i+1) << ":" << endl
		<< seg[i].getP1() << "," << seg[i].getP2() << endl
		<< "Slope:" << round(seg[i].slope()) << endl
		<< "Midpoint:" << seg[i].midpoint() << endl
		<< "X Intercept:" << round(seg[i].xIntercept().getXValue()) << endl
		<< "Y Intercept:" << round(seg[i].yIntercept().getYValue()) << endl
		<< "Length:" << round(seg[i].length()) << endl
		<< seg[i] << endl;
	}
	return s;
}

/**
 *  Default constructor for the Intervals class.
 */
template <class DT>
Segments<DT>::Segments() {
	segments = NULL;
	count = 0;
	maxSize = 0;
}

/**
 * 	Constructor for the Intervals class.
 *
 * 	@param size The length of the array of LineSegments.
 */
template <class DT>
Segments<DT>::Segments(int size) {
	segments = new LineSegment<DT> [size];
	count = 0;
	maxSize = size;
}

/**
 * 	Method that adds a Line Segment to the array of segments.
 *
 * 	@param L The line segment to be added.
 */
template <class DT>
void Segments<DT>::addLineSegment(LineSegment<DT> L){
	if (count < maxSize){
		segments[count] = L;
		count++;
	}
}

template <class DT>
double distance(Point<DT> P, LineSegment<DT> L){
	double x0, y0, m, c;
	double denominator, numerator;
	double distance;

	x0 = P.getXValue();
	y0 = P.getYValue();
	m = L.slope();
	c = L.yIntercept().getYValue();

	denominator = squareroot(1 + m * m);
	numerator = m*x0 - y0 + c;
	if (numerator < 0){
		numerator -= numerator - numerator;
	}

	distance = numerator/denominator;
	return distance;
}

/**
 * 	Displays various features of the current line segment, as well as any intersections
 * 	that may occur between line segments.
 */
template <class DT>
void Segments<DT>::display(){
	for (int i = 0; i < maxSize; i++){
		cout << "Line Segment " << (i+1) << ":" << endl;
		segments[i].getP1().display();
		cout << ",";
		segments[i].getP2().display();
		cout << endl << "Slope:" << round(segments[i].slope()) << endl
		<< "Midpoint:";
		try{
			double lengthZero = 1/round(segments[i].length());
			segments[i].midpoint().display();
		}
		catch (LineSegmentException &e) {
			cout << "Exception,length is 0" << endl;
		}
		cout << endl << "X Intercept:" << round(segments[i].xIntercept().getXValue());
		cout << endl << "Y Intercept:" << round(segments[i].yIntercept().getYValue());
		cout << endl << "Length:" << round(segments[i].length()) << endl;
		segments[i].displayEquation();
		cout << endl;
	}

	for (int i = 0; i < maxSize; i++){
		for (int j = i+1; j < maxSize; j++){
			cout << "The line segments compared are segments[" << i << "] and segments[" << j << "]: ";
			if (segments[i].isParallel(segments[j]) == true){
				cout << "Lines are Parallel"<< endl;
			}
			else if (segments[i].itIntersects(segments[j]) == false){
				cout << "Not Parallel and not Intersecting" << endl;
			}
			else{
				cout << "Intersection Point :";
				segments[i].intersectionPoint(segments[j]).display();
				cout << endl;
			}
		}
	}
}

template <class DT>
Segments<DT>& Segments<DT>::aClosedPolygon(){
	//TODO: implement this
}

template <class DT>
Segments<DT>& Segments<DT>::findAllIntersects(LineSegment<DT>& LS){
	Segments<double> intersects = Segments(maxSize);
	for (int i = 0; i < maxSize; i++){
			if (segments[i].isParallel(LS) == true){
				intersects.addLineSegment(LineSegment<double>());
			}
			else if (segments[i].itIntersects(LS) == false){
				intersects.addLineSegment(LineSegment<double>());
			}
			else{
				intersects.addLineSegment(segments[i]);
			}
		}
	return intersects;
}

template <class DT>
Segments<DT>::~Segments() {
	delete segments;
}

template <class DT>
LineSegment<DT>& Segments<DT>::findClosest(Point<DT>& aPoint){
	return segments[this->findClosestIndex(aPoint)];
}

template <class DT>
int Segments<DT>::findClosestIndex(Point<DT>& aPoint){
	double shortest = 1.79769e+308;
	int line = 0;
	for (int i = 0; i < maxSize; i++){
		double distanceFrom = distance(aPoint, segments[i]);
		if (distanceFrom < shortest){
			shortest = distanceFrom;
			line = i;
		}
	}
	return line;
}

template <class DT>
int Segments<DT>::getSize(){
	return maxSize;
}

template <class DT>
LineSegment<DT> Segments<DT>::getSegmentAt(int index){
	return (segments[index]);
}

/**
 * 	Main method which runs the program.
 */
int main() {

	char command;
	int noOfSegments;
	cin >> noOfSegments;
	Segments<double> segments = Segments<double>(noOfSegments);

	while (!cin.eof()) {
		cin >> command;
		switch (command) {
			case 'A': //Add a line segment
			{
				double P1x, P1y, P2x, P2y;
				cin >> P1x >> P1y >> P2x >> P2y;
				Point<double> one = Point<double>(P1x, P1y);
				Point<double> two = Point<double>(P2x, P2y);
				LineSegment<double> line = LineSegment<double>(one, two);
				segments.addLineSegment(line);
				cout << "Line segment added" << endl << endl;
				break;
			}
			case 'R': //Remove a line segment
			{
				double P1x, P1y, P2x, P2y;
				cin >> P1x >> P1y >> P2x >> P2y;
				int count = 0;
				Segments<double> temp = Segments<double>(noOfSegments-1);
				try{
					for (int i = 0; i < noOfSegments; i++){
						if (segments.getSegmentAt(i).getP1().getXValue() == P1x
						 && segments.getSegmentAt(i).getP1().getYValue() == P1y
						 && segments.getSegmentAt(i).getP2().getXValue() == P2x
						 && segments.getSegmentAt(i).getP2().getYValue() == P2y)
							break;
						count++;
					}
					if (count < noOfSegments){
						noOfSegments--;
						for (int i = 0; i < count; i++){
							temp.addLineSegment(segments.getSegmentAt(i));
						}
						for (int i = count; i < noOfSegments; i++){
							temp.addLineSegment(segments.getSegmentAt(i+1));
						}
						segments = temp;
					}
					else{
						throw SegmentsException();
					}
					cout << "Line segment removed" << endl << endl;
				}
				catch (SegmentsException &e) {
					cout << "Exception,line segment not found" << endl << endl;
				}
				break;
			}
			case 'D': //Display all line segments
			{
				//TODO: fix this
				cout << segments << endl;
				break;
			}
			case 'P': //Closed polygon method
			{
				//TODO: Implement this (for bonus points!)
				cout << "Command P not implemented" << endl << endl;
				break;
			}
			case 'I': //Display all intersects with a given line segment
			{
				//TODO: not printing
				double P1x, P1y, P2x, P2y;
				cin >> P1x >> P1y >> P2x >> P2y;
				Point<double> one = Point<double>(P1x, P1y);
				Point<double> two = Point<double>(P2x, P2y);
				LineSegment<double> line = LineSegment<double>(one, two);
				Segments<double> intersects = segments.findAllIntersects(line);
				int lines = 0;
				for (int i = 0; i < intersects.getSize(); i++){
					if (intersects.getSegmentAt(i).length() != 0){
						lines++;
					}
				}
				if (lines > 0){
					cout << "The lines segments intersecting with the given line segment are:" << endl;
					for (int i = 0; i < intersects.getSize(); i++){
						if (intersects.getSegmentAt(i).length() != 0){
							cout << "Line Segment " << (i+1) << endl;
						}
					}
				}
				else cout << "NO INTERSECTING LINE SEGMENTS" << endl;
				cout << endl;
				break;
			}
			case 'C': //Display line segment closest to a point
			{
				double PCx, PCy;
				cin >> PCx >> PCy;
				Point<double> chosen = Point<double>(PCx, PCy);
				cout << "The Line segment closest to the given point is:";
				cout << "Line segment " << (segments.findClosestIndex(chosen)+1) << endl << endl;
				break;
			}
			default: cout << "Invalid command" << endl << endl;
		}
	}

	delete &segments;
	return 0;
}
