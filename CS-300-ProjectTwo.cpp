#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

// Course structure which holds all course data
struct Course {
    string courseTitle;
    string courseNumber;
    vector<string> prerequisites;

};

// Loads all course data from our CSV file
map<string, Course> loadCourseData(const string& fileName) {
    map<string, Course> courses;
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error: Cannot open file." << endl;
        cout << "Attempted to open: " << fileName << endl; // In place to show the file path that is being attempted to open
        return courses;
    }


    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseNumber, courseTitle, prereq;
        vector<string> prerequisites;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        // Reads the prerequisites
        while(getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }


        // Creates course object
        Course course = { courseNumber, courseTitle, prerequisites };
        courses[courseNumber] = course;
    }


    file.close();
    return courses;
}

// Prints all courses in alphanumeric order
void printAllCourses(const map<string, Course>& courses) {
    vector<string> courseList;

    for (const auto& course: courses) {
        courseList.push_back(course.first);
    }
    sort(courseList.begin(),courseList.end());

    // Prints each course with its prerequisites
    for (const auto& courseNumber : courseList) {
        const Course& course = courses.at(courseNumber);
        cout << course.courseNumber << ": " << course.courseTitle << endl;

        if (!course.prerequisites.empty()) {
            cout << "  Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
        else {
            cout << "  No prerequisites" << endl;

        }
    }
}

// Function searches and prints each course using its course number
void searchCourse(const map<string, Course>& courses, const string& courseNumber) {
    auto it = courses.find(courseNumber);

    if (it != courses.end()) {
        const Course& course = it->second;
        cout << course.courseNumber << ": " << course.courseTitle << endl;

        if (!course.prerequisites.empty()) {
            cout << "  Prerequisites: ";
            for(const auto& prereq : course.prerequisites) {
                cout << prereq << " ";
            }

            cout << endl;
        }

        else {
            cout << "  No prerequisites" << endl;
        }
    }

    else {
        cout << "Course not found." << endl;
    }
}

// Main menu 
void Menu() {
    map<string, Course> courses;

    int option = 0;
    string courseNumber;

    while (option != 9) {
        cout << "\nMenu:\n";
        cout << "1. Load course data\n";
        cout << "2. Print all courses\n";
        cout << "3. Print a specific course\n";
        cout << "9. Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        switch (option) {
        case 1:
            courses = loadCourseData("course_data.csv");
            if (!courses.empty()) {
                cout << "Course data loaded." << endl;
            }
            break;

        case 2:
            if (!courses.empty()) {
                printAllCourses(courses);
            }
            else {
                cout << "Please load course data." << endl;
            }
            break;

        case 3:
            cout << "Enter course number: ";
            cin >> courseNumber;
            searchCourse(courses, courseNumber);
            break;

        case 9:
            cout << "Exiting program. Goodbye." << endl;
            break;

        default:
            cout << "Invalid option, Try again." << endl;
            break;
        }

    }
}


int main() {
    Menu();
    return 0;
}