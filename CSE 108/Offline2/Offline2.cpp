#include <iostream>
using namespace std;


class Course
{
    string name;
    float creditHour;

public:
    Course();

    Course(string name, float creditHour);

    string getName();
    
    float getCreditHour();
    
    void setName(string name);
    
    void  setCreditHour(float  creditHour);
    
    void display();
};


class Student
{
    string name;
    int id;
    Course* courses;
    int totalCourses;
    int maxCourses;
    float* gradePoints;

public:
    Student();

    Student(string  name,  int  id,  int  maxCourses);

    Student(const Student& stu);

    ~Student();

    void setName(string name);
    
    void setId(int id);
    
    void  setInfo(string  name,  int  id);
    
    void  addCourse(Course  c);
    
    void  addCourse(Course  course,  float  gradePoint);
    
    void  setgradePoint(Course  c,  float  gradePoint);
    
    void  setgradePoint(float*  gradePoints,  int  n);
    
    string getName();
    
    float  getCGPA();
    
    float  getgradePoint(Course  c);

    int  getTotalCourses();
    
    float  getTotalCreditHours();
    
    Course  getMostFavoriteCourse();
    
    Course  getLeastFavoriteCourse();
    
    Course*  getFailedCourses(int  &count);
    
    void  display();
};


// Global Variables
Student* students[];
int totalStudents = 0;


Student getTopper();

Student getTopper(Course c);


int main()
{
    // generate courses
    const int COURSE_COUNT = 6;
    Course courses[COURSE_COUNT] = {
        Course("CSE107", 3),
        Course("CSE105", 3),
        Course("CSE108", 1.5),
        Course("CSE106", 1.5),
        Course("EEE164", 0.75),
        Course("ME174", 0.75),
    };
    float gradePoints[COURSE_COUNT] = {4.0, 4.0, 3.5, 3.5, 4.0, 3.25};

    // generate students
    Student s1 = Student("Sheldon", 1, 5);
    students[totalStudents++] = &s1;

    // add courses to s1
    s1.addCourse(courses[0]);
    s1.addCourse(courses[1]);
    s1.addCourse(courses[2]);
    s1.addCourse(courses[3]);
    s1.addCourse(courses[4]);
    s1.addCourse(courses[5]);
    s1.setgradePoint(gradePoints, s1.getTotalCourses());
    s1.display();

    Student s2 = Student("Penny", 2, 5);
    students[totalStudents++] = &s2;
    s2.addCourse(courses[0]);
    s2.addCourse(courses[2]);
    s2.addCourse(courses[5]);
    s2.setgradePoint(gradePoints, s2.getTotalCourses());
    s2.setgradePoint(courses[0], 3.25);
    s2.display();

    Student s3 = s2;
    students[totalStudents++] = &s3;
    s3.setName("Leonard");
    s3.setId(3);
    s3.setgradePoint(gradePoints, s3.getTotalCourses());
    s3.addCourse(courses[1], 3.75);
    s3.display();

    Student s4 = s3;
    students[totalStudents++] = &s4;
    s4.setInfo("Howard", 4);
    s4.setgradePoint(gradePoints, s4.getTotalCourses());
    s4.addCourse(courses[3], 3.75);
    s4.display();

    Student s5 = s4;
    students[totalStudents++] = &s5;
    s5.setInfo("Raj", 5);
    s5.setgradePoint(gradePoints, s5.getTotalCourses());
    s5.setgradePoint(courses[0], 1.5);
    s5.setgradePoint(courses[2], 2.0);
    s5.setgradePoint(courses[5], 1.75);
    s5.setgradePoint(courses[3], 3.75);
    s5.display();

    int failedCount;
    Course *failedCourses = s5.getFailedCourses(failedCount);
    cout << "Failed Courses for " << s5.getName() << ":" << endl;
    for (int i = 0; i < failedCount; ++i)
    {
        failedCourses[i].display();
        cout << endl;
    }
    delete[] failedCourses;

    cout << "==================================" << endl;
    Student topper = getTopper();
    cout << "Topper: " << topper.getName() << endl;
    cout << "Topper CGPA: " << topper.getCGPA() << endl;
    cout << "==================================" << endl;

    for (int i = 0; i < COURSE_COUNT; ++i)
    {
        Course c = courses[i];
        Student topperInCourse = getTopper(c);
        cout << "Topper in " << c.getName() << ": " << topperInCourse.getName() << endl;
        cout << "Topper in " << c.getName() << " gradePoint: " << topperInCourse.getgradePoint(c) << endl;
        cout << "==================================" << endl;
    }

    return 0;
}


/* Expected Output

 Cannot add more courses to Sheldon
 ==================================
 Student Name: Sheldon, ID: 1
 Course Name: CSE107, Credit Hour: 3, gradePoint: 4
 Course Name: CSE105, Credit Hour: 3, gradePoint: 4
 Course Name: CSE108, Credit Hour: 1.5, gradePoint: 3.5
 Course Name: CSE106, Credit Hour: 1.5, gradePoint: 3.5
 Course Name: EEE164, Credit Hour: 0.75, gradePoint: 4
 CGPA: 3.84615
 Total Credit Hours Earned: 9.75
 Most Favorite Course: CSE107
 Least Favorite Course: CSE108
 ==================================
 ==================================
 Student Name: Penny, ID: 2
 Course Name: CSE107, Credit Hour: 3, gradePoint: 3.25
 Course Name: CSE108, Credit Hour: 1.5, gradePoint: 4
 Course Name: ME174, Credit Hour: 0.75, gradePoint: 3.5
 CGPA: 3.5
 Total Credit Hours Earned: 5.25
 Most Favorite Course: CSE108
 Least Favorite Course: CSE107
 ==================================
 ==================================
 Student Name: Leonard, ID: 3
 Course Name: CSE107, Credit Hour: 3, gradePoint: 4
 Course Name: CSE108, Credit Hour: 1.5, gradePoint: 4
 Course Name: ME174, Credit Hour: 0.75, gradePoint: 3.5
 Course Name: CSE105, Credit Hour: 3, gradePoint: 3.75
 CGPA: 3.86364
 Total Credit Hours Earned: 8.25
 Most Favorite Course: CSE107
 Least Favorite Course: ME174
 ==================================
 ==================================
 Student Name: Howard, ID: 4
 Course Name: CSE107, Credit Hour: 3, gradePoint: 4
 Course Name: CSE108, Credit Hour: 1.5, gradePoint: 4
 Course Name: ME174, Credit Hour: 0.75, gradePoint: 3.5
 Course Name: CSE105, Credit Hour: 3, gradePoint: 3.5
 Course Name: CSE106, Credit Hour: 1.5, gradePoint: 3.75
 CGPA: 3.76923
 Total Credit Hours Earned: 9.75
 Most Favorite Course: CSE107
 Least Favorite Course: ME174
 ==================================
 ==================================
 Student Name: Raj, ID: 5
 Course Name: CSE107, Credit Hour: 3, gradePoint: 1.5
 Course Name: CSE108, Credit Hour: 1.5, gradePoint: 2
 Course Name: ME174, Credit Hour: 0.75, gradePoint: 1.75
 Course Name: CSE105, Credit Hour: 3, gradePoint: 3.5
 Course Name: CSE106, Credit Hour: 1.5, gradePoint: 3.75
 CGPA: 2.55769
 Total Credit Hours Earned: 6
 Most Favorite Course: CSE106
 Least Favorite Course: CSE107
 ==================================
 Failed Courses for Raj:
 Course Name: CSE107, Credit Hour: 3
 Course Name: ME174, Credit Hour: 0.75
 ==================================
 Topper: Leonard
 Topper CGPA: 3.86364
 ==================================
 Topper in CSE107: Sheldon
 Topper in CSE107 gradePoint: 4
 ==================================
 Topper in CSE105: Sheldon
 Topper in CSE105 gradePoint: 4
 ==================================
 Topper in CSE108: Penny
 Topper in CSE108 gradePoint: 4
 ==================================
 Topper in CSE106: Howard
 Topper in CSE106 gradePoint: 3.75
 ==================================
 Topper in EEE164: Sheldon
 Topper in EEE164 gradePoint: 4
 ==================================
 Topper in ME174: Penny
 Topper in ME174 gradePoint: 3.5
 ==================================
*/