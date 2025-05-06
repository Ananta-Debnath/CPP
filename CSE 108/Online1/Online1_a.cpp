#include <iostream>
#include <cmath>
using namespace std;


class Point
{
    double x;
    double y;

public:
    Point()
    {
        setCoordinates(0, 0);
    }

    Point(double x, double y)
    {
        setCoordinates(x, y);
    }

    void setCoordinates(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Point translate(double dx, double dy)
    {
        return Point(x+dx, y+dy);
    }

    double cross(const Point& other)
    {
        return (x * other.y) - (y * other.x);
    }

    double getDistance(const Point& other)
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt((dx*dx) + (dy*dy));
    }

    void display()
    {
        cout << "(" << x << ", " << y << ")" << endl;
    }
};


class Polygon
{
    Point* vertices;
    int numVertices;

public:
    Polygon()
    {
        vertices = new Point[10];
        numVertices = 0;
    }

    Polygon(Point* vertices, int n)
    {
        this->vertices = new Point[10];
        numVertices = 0;
        for (int i = 0; i < n; i++) addVertex(vertices[i]);
    }

    Polygon(Polygon& poly)
    {
        vertices = new Point[10];
        numVertices = 0;
        for (int i = 0; i < poly.numVertices; i++) addVertex(poly.vertices[i]);
    }

    void addVertex(Point p)
    {
        vertices[numVertices] = p;
        numVertices++;
    }

    double getPerimeter()
    {
        double dist = vertices[0].getDistance(vertices[numVertices-1]);
        for (int i = 0; i < numVertices-1; i++)
            dist += vertices[i].getDistance(vertices[i+1]);
        
        return dist;
    }

    double getArea()
    {
        double area = vertices[numVertices-1].cross(vertices[0]);
        for (int i = 0; i < numVertices-1; i++)
            area += vertices[i].cross(vertices[i+1]);
        
        return area / 2;
    }

    Polygon translate(double dx, double dy)
    {
        Point* points = new Point[numVertices];
        for (int i = 0; i < numVertices; i++) points[i] = vertices[i].translate(dx, dy);
        Polygon newPoly(points, numVertices);
        delete[] points;
        return newPoly;
    }

    void display()
    {
        cout << "No. of Vertices: " << numVertices << endl;
        for (int i = 0; i < numVertices; i++) vertices[i].display();
        cout << "Perimeter: " << getPerimeter() << ", Area: " << getArea() << endl;
    }

    ~Polygon()
    {
        delete[] vertices;
    }
};


int main() {
    Point p1(0, 0);
    Point p2(4, 0);
    Point p3(4, 3);
    Point p4(0, 3);
    Point vertices[] = {p1, p2, p3};
    Polygon triangle(vertices, 3);
    Polygon translatedTriangle = triangle.translate(2, 1);
    cout << "Original Triangle:\n";
    triangle.display();
    cout << "\nTranslated Triangle:\n";
    translatedTriangle.display();
    Polygon square = triangle;
    square.addVertex(p4);
    cout << "\nSquare:\n";
    square.display();
    return 0;
}