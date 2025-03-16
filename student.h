#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class Student {
private:
    string surname;
    string name;
    string patronymic;
    string group;
    int course;
    int grant;
    string surnameElder;
    string arrear;
    string curator;
    string faculty;

public:
    Student() : course(0), grant(0) {}

    void printInfo() const;
    static size_t utf8_length(const string &str);
    static void InputString(string &str, const string &prompt, size_t max_length);
    static int InputIntInRange(const string &prompt, int min, int max);
    static void EditStudentData(Student* students, int &studentCount);
    static void DeleteStudent(Student* &students, int &studentCount);
    static void StudentsEntry(Student* &s, int &n);
    static void LoadFromTextFile(Student* &s, int &n, const char* filename);
    static void SaveToTextFile(const Student* s, int n, const char* filename);
    static void PrintTable(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void printAligned(const string &str, size_t width);
    static void printCenteredNum(int num, size_t width);
    static void printCentered(const string &str, size_t width);
    static void AddStudent(Student* &students, int &studentCount);
    static void SortStudents(Student* students, int studentCount);
    static string getFirstUtf8Char(const string &str);
    static void getFirstGroupList(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void getStudentsWithDebts(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void getGroupWithDebts(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void getPercentSecAndThirdCourses(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void getStudentsByLetter(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void getCuratorsDepartments(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void MenuQueries(const Student students[], short studentCount, const short columnWidths[], short columnCount);
    static void mainMenu();
    static void MenuStudents(Student* &students, int &studentCount);
};

#endif