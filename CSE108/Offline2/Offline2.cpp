#include <iostream>
using namespace std;


class Course
{
    string name;
    float creditHour;

public:
    Course()
    {
        name = "No Name";
        creditHour = 0;
    }

    Course(string name, float creditHour)
    {
        this->name = name;
        this->creditHour = creditHour;
    }

    string getName()
    {
        return name;
    }
    
    float getCreditHour()
    {
        return creditHour;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void  setCreditHour(float creditHour)
    {
        this->creditHour = creditHour;
    }

    void display()
    {
        cout << "Course Name: " << name << ", Credit Hour: " << creditHour;
    }
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
    Student()
    {
        name = "N/A";
        id = 0;
        courses = NULL;
        totalCourses = 0;
        maxCourses = 0;
        gradePoints = NULL;
    }

    Student(string name, int id, int maxCourses)
    {
        this->name = name;
        this->id = id;
        this->maxCourses = maxCourses;
        courses = new Course[maxCourses];
        totalCourses = 0;
        gradePoints = new float[maxCourses];
    }

    Student(const Student& stu)
    {
        name = stu.name;
        id = stu.id;
        maxCourses = stu.maxCourses;
        courses = new Course[maxCourses];
        totalCourses = stu.totalCourses;
        gradePoints = new float[maxCourses];

        for (int i = 0; i < totalCourses; i++)
        {
            courses[i] = stu.courses[i];
            gradePoints[i] = stu.gradePoints[i];
        }
    }

    ~Student()
    {
        delete[] courses;
        delete[] gradePoints;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setId(int id)
    {
        this->id = id;
    }

    void  setInfo(string name, int id)
    {
        setName(name);
        setId(id);
    }

    void addCourse(Course c)
    {
        addCourse(c, 0);
    }

    void addCourse(Course course, float gradePoint)
    {
        if (totalCourses < maxCourses)
        {
            for (int i = 0; i < totalCourses; i++)
            {
                if (courses[i].getName() == course.getName())
                {
                    gradePoints[i] = gradePoint;
                    return;
                }
            }

            courses[totalCourses] = course;
            gradePoints[totalCourses] = gradePoint;
            totalCourses++;
        }

        else cout << "Cannot add more courses to " << name << endl;
    }

    void setGradePoint(Course c, float gradePoint)
    {
        for (int i = 0; i < totalCourses; i++)
        {
            if (courses[i].getName() == c.getName())
            {
                gradePoints[i] = gradePoint;
                if (gradePoints[i] < 0) gradePoints[i] = 0;
                else if (gradePoints[i] > 4) gradePoints[i] = 4;
                return;
            }
        }

        cout << "No course named " << c.getName() << endl;
    }

    void setGradePoint(float* gradePoints, int n)
    {
        totalCourses = n;
        for (int i = 0; i < n; i++)
        {
            this->gradePoints[i] = gradePoints[i];
            if (gradePoints[i] < 0) gradePoints[i] = 0;
            else if (gradePoints[i] > 4) gradePoints[i] = 4;
        }
    }

    string getName()
    {
        return name;
    }

    float getCGPA()
    {
        float totalCreditHour = 0;
        float weightedGrade = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            totalCreditHour += courses[i].getCreditHour();
            weightedGrade += courses[i].getCreditHour()*gradePoints[i];
        }

        float CGPA;
        if (totalCreditHour == 0) CGPA = 0;

        else CGPA = weightedGrade / totalCreditHour;

        return CGPA;
    }

    float getGradePoint(Course c)
    {
        for (int i = 0; i < totalCourses; i++)
        {
            if (courses[i].getName() == c.getName()) return gradePoints[i];
        }
        return 0;
    }

    int getTotalCourses()
    {
        return totalCourses;
    }

    float getTotalCreditHours()
    {
        float totalCreditHours = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            if (gradePoints[i] >= 2) totalCreditHours += courses[i].getCreditHour();
        }
            
        return totalCreditHours;
    }

    Course getMostFavoriteCourse()
    {
        int idx = 0;
        for (int i = 1; i < totalCourses; i++)
        {
            if (gradePoints[i] > gradePoints[idx]) idx = i;
        }
        return courses[idx];
    }

    Course getLeastFavoriteCourse()
    {
        int idx = 0;
        for (int i = 1; i < totalCourses; i++)
        {
            if (gradePoints[i] < gradePoints[idx]) idx = i;
        }
        return courses[idx];
    }

    Course* getFailedCourses(int& count)
    {
        Course* failedCourses = new Course[totalCourses];
        count = 0;
        for (int i = 0; i < totalCourses; i++)
        {
            if (gradePoints[i] < 2)
            {
                failedCourses[count] = courses[i];
                count++;
            }
        }
        return failedCourses;
    }

    void  display()
    {
        cout << "==================================" << endl;
        cout << "Student Name: " << name << ", ID: " << id << endl;
        for (int i = 0; i < totalCourses; i++)
        {
            courses[i].display();
            cout << ", gradePoint: " << gradePoints[i] << endl;
        }
        cout << "CGPA: " << getCGPA() << endl;
        cout << "Total Credit Hours Earned: " << getTotalCreditHours() << endl;
        cout << "Most Favorite Course: " << getMostFavoriteCourse().getName() << endl;
        cout << "Least Favorite Course: " << getLeastFavoriteCourse().getName() << endl;
        cout << "==================================" << endl;
    }
};


// Global Variables
Student* students[10];
int totalStudents = 0;


Student getTopper()
{
    int idx = 0;
    float maxCGPA = students[0]->getCGPA();
    for (int i = 1; i < totalStudents; i++)
    {
        if (students[i]->getCGPA() > maxCGPA)
        {
            idx = i;
            maxCGPA = students[i]->getCGPA();
        }
    }
    return *(students[idx]);
}

Student getTopper(Course c)
{
    int idx = 0;
    float maxGrade = students[0]->getGradePoint(c);
    for (int i = 1; i < totalStudents; i++)
    {
        if (students[i]->getGradePoint(c) > maxGrade)
        {
            idx = i;
            maxGrade = students[i]->getGradePoint(c);
        }
    }
    return *(students[idx]);
}


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
    s1.setGradePoint(gradePoints, s1.getTotalCourses());
    s1.display();

    Student s2 = Student("Penny", 2, 5);
    students[totalStudents++] = &s2;
    s2.addCourse(courses[0]);
    s2.addCourse(courses[2]);
    s2.addCourse(courses[5]);
    s2.setGradePoint(gradePoints, s2.getTotalCourses());
    s2.setGradePoint(courses[0], 3.25);
    s2.display();

    Student s3 = s2;
    students[totalStudents++] = &s3;
    s3.setName("Leonard");
    s3.setId(3);
    s3.setGradePoint(gradePoints, s3.getTotalCourses());
    s3.addCourse(courses[1], 3.75);
    s3.display();

    Student s4 = s3;
    students[totalStudents++] = &s4;
    s4.setInfo("Howard", 4);
    s4.setGradePoint(gradePoints, s4.getTotalCourses());
    s4.addCourse(courses[3], 3.75);
    s4.display();

    Student s5 = s4;
    students[totalStudents++] = &s5;
    s5.setInfo("Raj", 5);
    s5.setGradePoint(gradePoints, s5.getTotalCourses());
    s5.setGradePoint(courses[0], 1.5);
    s5.setGradePoint(courses[2], 2.0);
    s5.setGradePoint(courses[5], 1.75);
    s5.setGradePoint(courses[3], 3.75);
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
        cout << "Topper in " << c.getName() << " gradePoint: " << topperInCourse.getGradePoint(c) << endl;
        cout << "==================================" << endl;
    }

    return 0;
}