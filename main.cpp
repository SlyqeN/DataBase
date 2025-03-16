#include "student.h"
#include <unistd.h>
int main() {
    Student* students = nullptr;
    int studentCount = 0;
    const short columnWidths[] = {5, 20, 20, 20, 11, 5, 9, 13, 13, 16, 16};
    short columnCount = 12;
    int choice = 0;

    while (true) {
        system("clear");
        Student::mainMenu();
        choice = Student::InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 5);

        if (choice == 5) {
            system("clear");
            cout << "\033[1;32mВыход из программы...\033[0m\n";
            sleep(1);
            break;
        }

        switch (choice) {
            case 1:
                Student::MenuStudents(students, studentCount);
                break;               

            case 2:
                if (studentCount != 0) {
                    Student::PrintTable(students, studentCount, columnWidths, columnCount);
                    int k = Student::InputIntInRange("\033[1;32m(1) Выход.\033[0m\n\033[1;31mВаш выбор: \033[0m", 1, 1);
                    if (k == 1) {
                        system("clear");
                        cout << "\033[1;31mВыход в меню...\033[0m\n";
                        sleep(1);
                        system("clear");
                    }
                } else {
                    system("clear");
                    cout << "\033[1;31mУпс... Данные отсутствуют.\033[0m\n";
                    sleep(1);
                    system("clear");
                }
                break;
            case 3:
                Student::MenuQueries(students, studentCount, columnWidths, columnCount);
                break;

            case 4:
                Student::SaveToTextFile(students, studentCount, "students.txt");
                break;

            default:
                break;
        }
    }

    delete[] students;
    return 0;
}