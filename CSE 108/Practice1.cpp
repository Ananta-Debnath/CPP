/**
 * Jan25 CSE108 
 * Practice Session on Constructor, Destructor, and Function Overloading
 *  
 * 
 * Instructions:
 * * Implement the Circle class with the following functionalities:
 * *    - Default constructor
 * *    - Constructor with parameters for name, coordinates, and radius
 * *    - Copy constructor
 * *    - Method to calculate area and circumference
 * *    - Method to check if a point is inside the circle
 * *    - Method to check if another circle is inside, intersects, or outside this circle
 * *    - Method to translate the circle's position
 * *    - Method to scale the circle
 * *    - Method to display circle properties
 * *    - Setter and getter methods for name and color
 * * 
 * * After implementing the class, test it using the provided main function.
 * * Expected output is provided in the comments at the end of the code. 
 * * Be ready to explain the generated output to the evaluator.
 * 
 * 
 * 
 *  **---**
*/

#include <iostream>
#include <cstring>
#include <cmath>

#define PI 3.1416

using namespace std;

// Circle class definition
class Circle{
    double x, y;         // Coordinates of the center of the circle
    double radius;       // Radius of the circle
    char* name;          // Name of the circle
    char* color;         // Color of the circle

public:
    // Default constructor to initialize a circle with default values
    Circle()
    {
        x = 0;
        y = 0;
        radius = 0;

        name = new char[1];
        name[0] = 0;

        color = new char[6];
        strcpy(color, "White");
    }

    // Constructor with parameters for a circle's name, coordinates, and radius
    Circle(const char* name, double x, double y, double r)
    {
        this->x = x;
        this->y = y;
        radius = r;

        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        
        color = new char[6];
        strcpy(color, "White");
    }

    // Create a new circle from an existing one
    Circle(const Circle &c)
    {
        x = c.x;
        y = c.y;
        radius = c.radius;

        name = new char[strlen(c.name) + 1];
        strcpy(name, c.name);
        
        color = new char[strlen(c.color) + 1];
        strcpy(color, c.color);
    }

    // Method to calculate and return the area of the circle
    double area()
    {
        return PI * radius * radius;
    }
    
    // Method to calculate and return the circumference of the circle
    double circumference()
    {
        return 2 * PI * radius;
    }

    // Method to check if a point (x, y) is inside the circle
    void contains(double x, double y)
    {
        if ((x - this->x)*(x - this->x) + (y - this->y)*(y - this->y) < radius*radius)
        {
            cout << "Point (" << x << ", " << y << ") is inside the circle C1." << endl;
        }

        else cout << "Point (" << x << ", " << y << ") is outside the circle C1." << endl;
    }

    // Method to check if another circle is inside, intersects, or outside this circle
    void contains(Circle c)
    {
        double dist2 = (x - c.x)*(x - c.x) + (y - c.y)*(y - c.y);

        if (dist2 > (radius + c.radius)*(radius + c.radius))
        {
            cout << "Circle " << c.name << " is outside the circle C1." << endl;
        }
        else if (dist2 < (radius - c.radius)*(radius - c.radius))
        {
            cout << "Circle " << c.name << " is inside the circle C1." << endl;
        }
        else
        {
            cout << "Circle " << c.name << " intersects the circle C1." << endl;
        }
    }

    // Method to translate the circle's position by a distance (dx, dy)
    void translate(double dx, double dy)
    {
        x += dx;
        y += dy;
    }

    // Method to translate the circle in a given direction (up, down, left, right)
    void translate(string dir, double dist)
    {
        if (dir == "up") y += dist;
        else if (dir == "down") y -= dist;
        else if (dir == "left") x -= dist;
        else if (dir == "right") x += dist;
    }

    // Method to scale the circle by a given factor
    void scale(double factor)
    {
        radius *= factor;
    }

    // Method to display circle properties (name, center, radius, area, cirumference, color.)
    void display()
    {
        cout << "Circle Name: " << name << endl;
        cout << "Center: (" << x << ", " << y << ")" << endl;
        cout << "Radius: " << radius << endl;
        cout << "Area: " << area() << endl;
        cout << "Circumference: " << circumference() << endl;
        cout << "Color: " << color << endl;
    }

    // Setter method for the name of the circle
    void setName(const char* name)
    {
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    // Setter method for the color of the circle
    void setColor(const char* color)
    {
        delete[] this->color;
        this->color = new char[strlen(color) + 1];
        strcpy(this->color, color);
    }

    // Getter method for the circle's name
    char* getName()
    {
        return name;
    }

    // Getter method for the circle's color
    char* getColor()
    {
        return color;
    }

    // Destructor to clean up dynamically allocated memory
    ~Circle()
    {
        delete[] name;
        delete[] color;
    }
};

// Main function to test the Circle class
int main() {
    Circle c1("C1", 0, 0, 5);  // Create a circle with name C1 at (0,0) with radius 5
    Circle c2("C2", 6, 4, 1);  
    Circle c3("C3", 2, 2, 3);  
    Circle c4("C4", 1, 2, 2);  
    c1.setColor("Red");  // Set color of circle C1 to Red
    c2.setColor("Blue"); 

    c1.display();  // Display properties of circle C1
    cout << endl;
    c2.display();  
    cout << endl;

    // Test 
    c1.contains(3, 5);  // Point (3, 5) should be outside circle C1
    c1.contains(2, 2);  // Point (2, 2) should be inside circle C1
    c1.contains(c2);    // Check if circle C2 is inside, intersects, or outside circle C1
    c1.contains(c3);    
    c1.contains(c4);    

    // Translate circle C1 by (2, 3)
    c1.translate(2, 3);
    c1.display();
    cout << endl;

    // Translate circle C1 upwards by 2 units
    c1.translate("up", 2);
    c1.display();
    cout << endl;

    // Scale circle C1 by a factor of 2
    c1.scale(2);
    c1.display();
    return 0;
}

// Expected Output:
/*
Circle Name: C1
Center: (0, 0)
Radius: 5
Area: 78.5397
Circumference: 31.4159
Color: Red

Circle Name: C2
Center: (6, 4)
Radius: 1
Area: 3.14159
Circumference: 6.28318
Color: Blue

Point (3, 5) is outside the circle C1.
Point (2, 2) is inside the circle C1.
Circle C2 is outside the circle C1.
Circle C3 intersects with the circle C1.
Circle C4 is inside the circle C1.
Circle Name: C1
Center: (2, 3)
Radius: 5
Area: 78.5397
Circumference: 31.4159
Color: Red

Circle Name: C1
Center: (2, 5)
Radius: 5
Area: 78.5397
Circumference: 31.4159
Color: Red

Circle Name: C1
Center: (2, 5)
Radius: 10
Area: 314.159
Circumference: 62.8318
Color: Red
*/