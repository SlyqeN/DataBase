#include "student.h"
#include <unistd.h>

void Student::printInfo() const {
    cout << "Фамилия: " << surname << endl;
    cout << "Имя: " << name << endl;
    cout << "Отчество: " << patronymic << endl;
    cout << "Группа: " << group << endl;
    cout << "Курс: " << course << endl;
    cout << "Стипендия: " << grant << endl;
    cout << "Фамилия старосты: " << surnameElder << endl;
    cout << "Задолженность: " << arrear << endl;
    cout << "Куратор: " << curator << endl;
    cout << "Факультет: " << faculty << endl;
}

size_t Student::utf8_length(const string &str) {
    size_t length = 0;
    for (size_t i = 0; i < str.length();) {
        if ((str[i] & 0x80) == 0) i += 1;
        else if ((str[i] & 0xE0) == 0xC0) i += 2;
        else if ((str[i] & 0xF0) == 0xE0) i += 3;
        else if ((str[i] & 0xF8) == 0xF0) i += 4;
        else i += 1;
        length++;
    }
    return length;
}

void Student::InputString(string &str, const string &prompt, size_t max_length) {
    bool valid = false;
    while (!valid) {
        cout << prompt;
        getline(cin, str);

        if (utf8_length(str) > max_length) {
            system("clear");
            cout << "\033[1;31mОшибка! Максимум " << max_length << " символов. Попробуйте снова.\033[0m\n";
        } else {
            valid = true;
        }
    }
}

int Student::InputIntInRange(const string &prompt, int min, int max) {
    string input;
    bool valid = false;
    int value = 0;

    while (!valid) {
        cout << prompt;
        getline(cin, input);

        valid = true;
        for (char c : input) {
            if (c < '0' || c > '9') {
                valid = false;
                break;
            }
        }

        if (valid) {
            value = 0;
            for (char c : input) {
                value = value * 10 + (c - '0');
            }

            if (value < min || value > max) {
                valid = false;
            }
        }

        if (!valid) {
            cout << "\033[1;31mОшибка! Введите число от " << min << " до " << max << ".\033[0m\n";
        }
    }
    return value;
}

void Student::EditStudentData(Student* students, int &studentCount) {
    system("clear");
    if (studentCount == 0) {
        cout << "\033[1;31mУпс... Данные отсутствуют.\033[0m\n";
        sleep(2);
        system("clear");
        return;
    }

    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m|-------------------<<<<<<<<<<< МЕНЮ ИЗМЕНЕНИЯ ДАННЫХ >>>>>>>>>>>------------------------|\033[0m\n";
    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";

    cout << "\033[1;32mСписок студентов:\033[0m\n";
    for (int i = 0; i < studentCount; ++i) {
        cout << "\033[1;36m" << i + 1 << ". " << students[i].surname << " " << students[i].name << " " << students[i].patronymic << "\033[0m\n";
    }

    int studentIndex = InputIntInRange("\033[1;32mВыберите номер студента для редактирования: \033[0m", 1, studentCount) - 1;

    system("clear");
    cout << "\033[1;32mВы выбрали студента:\033[0m\n";
    students[studentIndex].printInfo();

    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m| Выберите поле для изменения:                                                           |\033[0m\n";
    cout << "\033[1;32m| 1. Фамилия                                                                             |\033[0m\n";
    cout << "\033[1;32m| 2. Имя                                                                                 |\033[0m\n";
    cout << "\033[1;32m| 3. Отчество                                                                            |\033[0m\n";
    cout << "\033[1;32m| 4. Группа                                                                              |\033[0m\n";
    cout << "\033[1;32m| 5. Курс                                                                                |\033[0m\n";
    cout << "\033[1;32m| 6. Стипендия                                                                           |\033[0m\n";
    cout << "\033[1;32m| 7. Задолженность                                                                       |\033[0m\n";
    cout << "\033[1;32m| 8. Фамилия старосты                                                                    |\033[0m\n";
    cout << "\033[1;32m| 9. Куратор                                                                             |\033[0m\n";
    cout << "\033[1;32m| 10. Факультет                                                                          |\033[0m\n"; 
    cout << "\033[1;32m| 11. Выход в меню                                                                       |\033[0m\n";
    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";

    int fieldChoice = InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 11);

    if (fieldChoice == 11) {
        system("clear");
        cout << "\033[1;31mВыход в меню...\033[0m\n";
        sleep(1);
        system("clear");
        return;
    }

    system("clear");

    switch (fieldChoice) {
        case 1:
            InputString(students[studentIndex].surname, "\033[1;36mНовая фамилия (макс. 50 символов): \033[0m", 50);
            break;
        case 2:
            InputString(students[studentIndex].name, "\033[1;36mНовое имя (макс. 50 символов): \033[0m", 50);
            break;
        case 3:
            InputString(students[studentIndex].patronymic, "\033[1;36mНовое отчество (макс. 50 символов): \033[0m", 50);
            break;
        case 4:
            InputString(students[studentIndex].group, "\033[1;36mНовая группа (макс. 15 символов): \033[0m", 15);
            break;
        case 5:
            students[studentIndex].course = InputIntInRange("\033[1;36mНовый курс (1-6): \033[0m", 1, 6);
            break;
        case 6: {
            string hasArrear;
            InputString(hasArrear, "\033[1;36mЕсть ли задолженность (да/нет): \033[0m", 3);
            if (hasArrear == "да" || hasArrear == "Да" || hasArrear == "ДА") {
                students[studentIndex].arrear = "Да";
                students[studentIndex].grant = 0;

            } else {
                students[studentIndex].arrear = "Нет";
                students[studentIndex].grant = InputIntInRange("\033[1;33mНовая стипендия (0-100000):\033[0m ", 0, 100000);
            }
            break;
        }
        case 7: {
            string hasArrear;
            InputString(hasArrear, "\033[1;36mЕсть ли задолженность (да/нет): \033[0m", 3);
            if (hasArrear == "да" || hasArrear == "Да" || hasArrear == "ДА") {
                students[studentIndex].arrear = "Да";
                students[studentIndex].grant = 0;

            } else {
                students[studentIndex].arrear = "Нет";
                students[studentIndex].grant = InputIntInRange("\033[1;33mНовая стипендия (0-100000):\033[0m ", 0, 100000); 
            }
            break;
        }
        case 8:
            InputString(students[studentIndex].surnameElder, "\033[1;36mНовая фамилия старосты (макс. 50 символов): \033[0m", 50);
            break;
        case 9:
            InputString(students[studentIndex].curator, "\033[1;36mНовый куратор (макс. 50 символов): \033[0m", 50);
            break;
        case 10:
            InputString(students[studentIndex].faculty, "\033[1;36mНовый факультет (макс. 50 символов): \033[0m", 50);
            break;
        default:
            break;
    }

    system("clear");
    cout << "\033[1;32mДанные успешно изменены.\033[0m\n";
    sleep(1);
    system("clear");
}

void Student::DeleteStudent(Student* &students, int &studentCount) {
    system("clear");
    if (studentCount == 0) {
        cout << "\033[1;31mУпс... Данные отсутствуют.\033[0m\n";
        sleep(2);
        system("clear");
        return;
    }

    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m|-------------------<<<<<<<<<<< МЕНЮ УДАЛЕНИЯ ДАННЫХ >>>>>>>>>>>-------------------------|\033[0m\n";
    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";

    cout << "\033[1;32mСписок студентов:\033[0m\n";
    for (int i = 0; i < studentCount; ++i) {
        cout << "\033[1;36m" << i + 1 << ". " << students[i].surname << " " << students[i].name << " " << students[i].patronymic << "\033[0m\n";
    }

    int studentIndex = InputIntInRange("\033[1;32mВыберите номер студента для удаления: \033[0m", 1, studentCount) - 1;

    Student* newStudents = new Student[studentCount - 1];
    for (int i = 0, j = 0; i < studentCount; ++i) {
        if (i != studentIndex) {
            newStudents[j++] = students[i];
        }
    }

    delete[] students;
    students = newStudents;
    --studentCount;

    system("clear");
    cout << "\033[1;32mСтудент успешно удален.\033[0m\n";
    sleep(1);
    system("clear");
}

void Student::StudentsEntry(Student* &s, int &n) {
    system("clear");
    cout << "\033[1;32m+--------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m|----------------<<<<<<<<<<< МЕНЮ ВВОДА >>>>>>>>>>>------------------|\033[0m\n";
    cout << "\033[1;32m+--------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m| Выберите способ ввода студентов:                                   |\033[0m\n";
    cout << "\033[1;32m| 1. Ввести вручную.                                                 |\033[0m\n";
    cout << "\033[1;32m| 2. Загрузить из текстового файла.                                  |\033[0m\n";
    cout << "\033[1;32m| 3. Выход в меню.                                                   |\033[0m\n";
    cout << "\033[1;32m+--------------------------------------------------------------------+\033[0m\n";
    int choice = InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 3);

    switch (choice) {
        case 1: {
            system("clear");
                cout << "\033[1;32mСколько студентов вы желаете внести в базу данных?\033[0m\n";
                cout << "\033[1;32mКоличество вносимых студентов: \033[0m";

                n = InputIntInRange("", 1, 100);
                s = new Student[n];

                for (int i = 0; i < n; i++) {
                    system("clear");
                    InputString(s[i].surname, "\033[1;36mФамилия студента (макс. 50 символов):\033[0m ", 50);
                    InputString(s[i].name, "\033[1;36mИмя студента (макс. 50 символов):\033[0m ", 50);
                    InputString(s[i].patronymic, "\033[1;36mОтчество студента (макс. 50 символов): \033[0m ", 50);
                    InputString(s[i].group, "\033[1;36mВведите группу студента (макс. 15 символов):\033[0m ", 15);

                    s[i].course = InputIntInRange("\033[1;36mНа каком курсе обучается студент (1-6):\033[0m ", 1, 6);

                    system("clear");

                    string hasArrear;
                    InputString(hasArrear, "\033[1;36mЕсть ли задолженность (да/нет): \033[0m", 3);
                    if (hasArrear == "да" || hasArrear == "Да" || hasArrear == "ДА") {
                        s[i].arrear = "Да";
                        s[i].grant = 0;

                    } else {
                        s[i].arrear = "Нет";
                        cout << "\033[1;32mСтипендия студента:\033[0m\n";
                        s[i].grant = InputIntInRange("\033[1;33mСтипендия (0-100000):\033[0m ", 0, 100000);
                    }

                    system("clear");

                    InputString(s[i].surnameElder, "\033[1;36mФамилия старосты (макс. 50 символов):\033[0m ", 50);
                    InputString(s[i].curator, "\033[1;36mКуратор (макс. 50 символов):\033[0m ", 50);
                    InputString(s[i].faculty, "\033[1;36mФакультет (макс. 50 символов): \033[0m", 50);
                }
                system("clear");
                cout << "\033[1;32mДанные успешно загружены в файл...\033[0m\n";
                sleep(1);
                system("clear");
                break;
            break;
        }
        case 2: {
            char filename[100];
            bool fileLoaded = false;
            int errorCount = 0;

            while (!fileLoaded && errorCount < 2) {
                system("clear");
                cout << "\033[1;32mВведите имя текстового файла: \033[0m";
                cin >> filename;

                LoadFromTextFile(s, n, filename);
                if (n > 0) {
                    fileLoaded = true;
                } else {
                    errorCount++;
                    cout << "\033[1;31mОшибка при загрузке данных из файла. Попробуйте снова.\033[0m\n";
                    sleep(1);
                }

                string dummy;
                getline(cin, dummy);
            }

            if (errorCount >= 2) {
                system("clear");
                cout << "\033[1;31mВы превысили допустимое количество попыток. Возвращаемся в меню...\033[0m\n";
                sleep(2);
                system("clear");
            }

            break;
        }
        case 3:
            system("clear");
            cout << "\033[1;31mВыход в меню...\033[0m \n";
            sleep(1);
            system("clear");
            break;
        default:
            break;
    }
}

void Student::LoadFromTextFile(Student* &s, int &n, const char* filename) {
    ifstream inFile(filename);
    if (!inFile) {
        system("clear");
        cout << "\033[1;31mОшибка при открытии файла для чтения!\033[0m \n";
        sleep(1);
        system("clear");
        n = 0;
        return;
    }

    n = 0;
    string line;
    while (getline(inFile, line)) {
        n++;
    }

    if (n == 0) {
        inFile.close();
        cout << "\033[1;31mФайл пустой.\033[0m \n";
        sleep(1);
        system("clear");
        n = 0;
        return;
    }

    inFile.clear();
    inFile.seekg(0, ios::beg);

    s = new Student[n];

    for (int i = 0; i < n; ++i) {
        if (!(inFile >> s[i].surname >> s[i].name >> s[i].patronymic 
              >> s[i].group
              >> s[i].course
              >> s[i].grant
              >> s[i].arrear)) {
            delete[] s;
            inFile.close();
            cout << "\033[1;31mОшибка при чтении данных из файла.\033[0m \n";
            sleep(1);
            system("clear");
            n = 0;
            return;
        }

        if (!(inFile >> s[i].faculty 
              >> s[i].surnameElder
              >> s[i].curator)) {
            delete[] s;
            inFile.close();
            cout << "\033[1;31mОшибка при чтении данных из файла.\033[0m \n";
            sleep(1);
            system("clear");
            n = 0;
            return;
        }
    }

    inFile.close();
    system("clear");
    cout << "\033[1;32mДанные успешно загружены из текстового файла.\033[0m" << endl;
    sleep(1);
    system("clear");
}

void Student::MenuStudents(Student* &students, int &studentCount) {
    while (true) {
        system("clear");
        cout << "\033[1;32m+----------------------------------------------------------------------------------------------------------+\033[0m\n";
        cout << "\033[1;32m|---------------------------<<<<<<<<<<< МЕНЮ РАБОТЫ СО СПИСОМ СТУДЕНТОВ >>>>>>>>>>>------------------------|\033[0m\n";
        cout << "\033[1;32m+----------------------------------------------------------------------------------------------------------+\033[0m\n";
        cout << "\033[1;32m| 1. Ввод данных                                                                                           |\033[0m\n";
        cout << "\033[1;32m| 2. Изменение данных                                                                                      |\033[0m\n";
        cout << "\033[1;32m| 3. Удаление данных                                                                                       |\033[0m\n";
        cout << "\033[1;32m| 4. Сортировка данных                                                                                     |\033[0m\n";
        cout << "\033[1;32m| 5. Добавление данных                                                                                     |\033[0m\n";
        cout << "\033[1;32m| 6. Выход в меню                                                                                          |\033[0m\n";
        cout << "\033[1;32m+----------------------------------------------------------------------------------------------------------+\033[0m\n";

        int choice = InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 6);

        if (choice == 6) {
            system("clear");
            cout << "\033[1;31mВыход в меню...\033[0m\n";
            sleep(1);
            system("clear");
            return;
        }

        switch (choice) {
            case 1:  {
                Student::StudentsEntry(students, studentCount);
                break;
        }

            case 2: {
                Student::EditStudentData(students, studentCount);
                break;
        }

            case 3: { 
                Student::DeleteStudent(students, studentCount);
                break;
            }

            case 4: { 
                Student::SortStudents(students, studentCount);
                break;
            }
            case 5: { 
                Student::AddStudent(students, studentCount);
                break;
            }
            default:
                break;
        }
    }
}



void Student::SaveToTextFile(const Student* s, int n, const char* filename) {
    ofstream outFile(filename, ios::out);
        if (!outFile) {
            cout << "\033[1;31mОшибка при открытии файла для записи!\033[0m\n";
            sleep(1);
            system("clear");
            return;
        }

        for (int i = 0; i < n; ++i) {
            outFile << s[i].surname << " "
                    << s[i].name << " "
                    << s[i].patronymic << " "
                    << s[i].group << " "
                    << s[i].course << " "
                    << s[i].grant << " "
                    << s[i].arrear << " ";

            outFile << s[i].faculty << " "
                    << s[i].surnameElder << " "
                    << s[i].curator << "\n";
        }

        outFile.close();
        system("clear");
        cout << "\033[1;32mДанные успешно сохранены в текстовый файл.\033[0m\n";
        sleep(1);
        system("clear");
}

void Student::PrintTable(const Student students[], short studentCount, const short columnWidths[], short columnCount) {
    system("clear");
        cout << "+-----+--------------------+--------------------+--------------------+-----------+-----+---------+-------------+-------------+----------------+----------------+\n";
        cout << "|";
        printCentered("№", columnWidths[0]);
        cout << "|";
        printAligned("Фамилия", columnWidths[1]);
        cout << "|";
        printAligned("Имя", columnWidths[2]);
        cout << "|";
        printAligned("Отчество", columnWidths[3]);
        cout << "|";
        printCentered("Группа", columnWidths[4]);
        cout << "|";
        printCentered("Курс", columnWidths[5]);
        cout << "|";
        printCentered("Cтипендия", columnWidths[6]);
        cout << "|";
        printCentered("Задолженность", columnWidths[7]);
        cout << "|";
        printAligned("Факультет", columnWidths[8]);
        cout << "|";
        printAligned("Староста", columnWidths[9]);
        cout << "|";
        printAligned("Куратор", columnWidths[10]);
        cout << "|\n";
        cout << "+-----+--------------------+--------------------+--------------------+-----------+-----+---------+-------------+-------------+----------------+----------------+\n";

        for (short id = 0; id < studentCount; id++) {
            cout << "|";
            printCenteredNum(id + 1, columnWidths[0]);
            cout << "|";
            printAligned(students[id].surname, columnWidths[1]);
            cout << "|";
            printAligned(students[id].name, columnWidths[2]);
            cout << "|";
            printAligned(students[id].patronymic, columnWidths[3]);
            cout << "|";
            printCentered(students[id].group, columnWidths[4]);
            cout << "|";
            printCenteredNum(students[id].course, columnWidths[5]);
            cout << "|";
            printCenteredNum(students[id].grant, columnWidths[6]);
            cout << "|";
            printCentered(students[id].arrear, columnWidths[7]);
            cout << "|";
            printAligned(students[id].faculty, columnWidths[8]);
            cout << "|";
            printAligned(students[id].surnameElder, columnWidths[9]);
            cout << "|";
            printAligned(students[id].curator, columnWidths[10]);
            cout << "|\n";
            cout << "+-----+--------------------+--------------------+--------------------+-----------+-----+---------+-------------+-------------+----------------+----------------+\n";
        }
}

void Student::printAligned(const string &str, size_t width) {
    size_t len = utf8_length(str);
    cout << str;
    for (size_t i = 0; i < width - len; i++) {
        cout << ' ';
    }
}

void Student::printCenteredNum(int num, size_t width) {
    char buffer[12];
    sprintf(buffer, " %d", num);
    size_t len = utf8_length(buffer);
    size_t padding = (width > len) ? (width - len) / 2 : 0;
    for (size_t i = 0; i < padding; i++) {
        cout.put(' ');
    }
    cout << buffer;
    for (size_t i = 0; i < width - len - padding; i++) {
        cout.put(' ');
    }
}

void Student::printCentered(const string &str, size_t width) {
    size_t len = utf8_length(str);
    size_t padding = (width > len) ? (width - len) / 2 : 0;

    for (size_t i = 0; i < padding; i++) {
        cout.put(' ');
    }

    cout << str;

    size_t remaining = (width > len) ? (width - len - padding) : 0;
    for (size_t i = 0; i < remaining; i++) {
        cout.put(' ');
    }
}

void Student::AddStudent(Student* &students, int &studentCount) {
    system("clear");
        cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
        cout << "\033[1;32m|-------------------<<<<<<<<<<< МЕНЮ ДОБАВЛЕНИЯ ДАННЫХ >>>>>>>>>>>-----------------------|\033[0m\n";
        cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
        cout << "\033[1;32m| (1) Добавить данные.                                                                   |\033[0m\n";
        cout << "\033[1;32m| (2) Выход в меню.                                                                      |\033[0m\n";
        cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
        int choice = InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 2);
        if (choice == 2) {
            system("clear");
            cout << "\033[1;31mВыход в меню...\033[0m\n";
            sleep(1);
            system("clear");
            return;
        }
        system("clear");

        int studentsToAdd = InputIntInRange("\033[1;32mСколько студентов вы хотите добавить? \033[0m\n\033[1;32mКоличество: \033[0m", 1, 100);

        for (int j = 0; j < studentsToAdd; j++) {
            Student* newStudents = new Student[studentCount + 1];
            for (int i = 0; i < studentCount; i++) {
                newStudents[i] = students[i];
            }
            delete[] students;
            students = newStudents;

            system("clear");
            cout << "\033[1;31mВведите данные студента #" << j + 1 << " для добавления в базу данных.\033[0m\n";
            InputString(students[studentCount].surname, "\033[1;34mФамилия: \033[0m", 50);
            InputString(students[studentCount].name, "\033[1;34mИмя: \033[0m", 50);
            InputString(students[studentCount].patronymic, "\033[1;34mОтчество: \033[0m", 50);
            InputString(students[studentCount].group, "\033[1;34mГруппа: \033[0m", 15);
            students[studentCount].course = InputIntInRange("\033[1;35mКурс (1-6): \033[0m", 1, 6);

            system("clear");

            string hasArrear;
            InputString(hasArrear, "\033[1;36mЕсть ли задолженность (да/нет): \033[0m", 3);
            if (hasArrear == "да" || hasArrear == "Да" || hasArrear == "ДА") {
                students[studentCount].arrear = "Да";
                students[studentCount].grant = 0;

            } else {
                students[studentCount].arrear = "Нет";
                cout << "\033[1;32mСтипендия студента:\033[0m\n";
                students[studentCount].grant = InputIntInRange("\033[1;33mСтипендия (0-100000):\033[0m ", 0, 100000);
            }

            system("clear");

            InputString(students[studentCount].surnameElder, "\033[1;34mФамилия старосты: \033[0m", 50);
            InputString(students[studentCount].curator, "\033[1;34mКуратор: \033[0m", 50);
            InputString(students[studentCount].faculty, "\033[1;34mФакультет: \033[0m", 50);
            studentCount++;
            system("clear");
            cout << "\033[1;32mСтудент #" << j + 1 << " успешно добавлен в базу данных. \033[0m\n";
            sleep(1);
            system("clear");
        }
        cout << "\033[1;32mИспользуйте вывод данных. \033[0m\n";
        sleep(2);
        system("clear");
}

void Student::SortStudents(Student* students, int studentCount) {
    if (studentCount == 0) {
        system("clear");
        cout << "\033[1;31mУпс... Данные отсутствуют.\033[0m\n";
        sleep(2);
        system("clear");
        return;
    }

    system("clear");
    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m|---------------------------<<<<<<<<<<< МЕНЮ СОРТИРОВКИ >>>>>>>>>>>----------------------|\033[0m\n";
    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m| Выберите поле для сортировки:                                                          |\033[0m\n";
    cout << "\033[1;32m| 1. Фамилия                                                                             |\033[0m\n";
    cout << "\033[1;32m| 2. Имя                                                                                 |\033[0m\n";
    cout << "\033[1;32m| 3. Отчество                                                                            |\033[0m\n";
    cout << "\033[1;32m| 4. Группа                                                                              |\033[0m\n";
    cout << "\033[1;32m| 5. Курс                                                                                |\033[0m\n";
    cout << "\033[1;32m| 6. Стипендия                                                                           |\033[0m\n";
    cout << "\033[1;32m| 7. Задолженность                                                                       |\033[0m\n";
    cout << "\033[1;32m| 8. Факультет                                                                           |\033[0m\n";
    cout << "\033[1;32m| 9. Куратор                                                                             |\033[0m\n";
    cout << "\033[1;32m| 10. Фамилия старосты                                                                   |\033[0m\n";
    cout << "\033[1;32m| 11. Выход в меню                                                                       |\033[0m\n";
    cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";

    int fieldChoice = InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 12);

    if (fieldChoice == 11) {
        system("clear");
        cout << "\033[1;31mВыход в меню...\033[0m\n";
        sleep(1);
        system("clear");
        return;
    }

   
    cout << "\033[1;32mВыберите направление сортировки:           \033[0m\n";
    cout << "\033[1;32m| 1. По возрастанию              |\033[0m\n";
    cout << "\033[1;32m| 2. По убыванию                 |\033[0m\n";
    bool ascending = (InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 2) == 1);

    for (int i = 0; i < studentCount - 1; ++i) {
        for (int j = 0; j < studentCount - i - 1; ++j) {
            bool swap = false;

            switch (fieldChoice) {
                case 1:
                    swap = (ascending ? (students[j].surname > students[j + 1].surname)
                                    : (students[j].surname < students[j + 1].surname));
                    break;
                case 2:
                    swap = (ascending ? (students[j].name > students[j + 1].name)
                                    : (students[j].name < students[j + 1].name));
                    break;
                case 3:
                    swap = (ascending ? (students[j].patronymic > students[j + 1].patronymic)
                                    : (students[j].patronymic < students[j + 1].patronymic));
                    break;
                case 4:
                    swap = (ascending ? (students[j].group > students[j + 1].group)
                                    : (students[j].group < students[j + 1].group));
                    break;
                case 5:
                    swap = (ascending ? (students[j].course > students[j + 1].course)
                                    : (students[j].course < students[j + 1].course));
                    break;
                case 6:
                    swap = (ascending ? (students[j].grant > students[j + 1].grant)
                                    : (students[j].grant < students[j + 1].grant));
                    break;
                case 7:
                    swap = (ascending ? (students[j].arrear > students[j + 1].arrear)
                                    : (students[j].arrear < students[j + 1].arrear));
                    break;
                case 8:
                    swap = (ascending ? (students[j].faculty > students[j + 1].faculty)
                                    : (students[j].faculty < students[j + 1].faculty));
                    break;
                case 9:
                    swap = (ascending ? (students[j].curator > students[j + 1].curator)
                                    : (students[j].curator < students[j + 1].curator));
                    break;
                case 10:
                    swap = (ascending ? (students[j].surnameElder > students[j + 1].surnameElder)
                                    : (students[j].surnameElder < students[j + 1].surnameElder));
                    break;
                default:
                    break;
            }

            if (swap) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    system("clear");
    cout << "\033[1;32mСортировка завершена.\033[0m\n";
    sleep(1);
    system("clear");
}

 string Student::getFirstUtf8Char(const string &str) {
    if (str.empty()) return "";
    
    size_t i = 0;
    if ((str[i] & 0x80) == 0) return str.substr(i, 1);
    else if ((str[i] & 0xE0) == 0xC0) return str.substr(i, 2);
    else if ((str[i] & 0xF0) == 0xE0) return str.substr(i, 3);
    else if ((str[i] & 0xF8) == 0xF0) return str.substr(i, 4);
    return "";
}

void Student::getFirstGroupList(const Student students[], short studentCount, const short columnWidths[], short columnCount){
    bool hasData = false;
                system("clear");

                cout << "+-----+--------------------+--------------------+--------------------+----------------+----------------+\n";
                cout << "|";
                printCentered("№", columnWidths[0]);
                cout << "|";
                printAligned("Фамилия", columnWidths[1]);
                cout << "|";
                printAligned("Имя", columnWidths[2]);
                cout << "|";
                printAligned("Отчество", columnWidths[3]);
                cout << "|";
                printAligned("Староста", columnWidths[9]);
                cout << "|";
                printAligned("Куратор", columnWidths[10]);
                cout << "|\n";
                cout << "+-----+--------------------+--------------------+--------------------+----------------+----------------+\n";

                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].group == "1") {
                        hasData = true;
                        cout << "|";
                        printCenteredNum(i + 1, columnWidths[0]);
                        cout << "|";
                        printAligned(students[i].surname, columnWidths[1]);
                        cout << "|";
                        printAligned(students[i].name, columnWidths[2]);
                        cout << "|";
                        printAligned(students[i].patronymic, columnWidths[3]);
                        cout << "|";
                        printAligned(students[i].curator, columnWidths[9]);
                        cout << "|";
                        printAligned(students[i].surnameElder, columnWidths[10]);
                        cout << "|\n";
                        cout << "+-----+--------------------+--------------------+--------------------+----------------+----------------+\n";
                    }
                }

                if (!hasData) {
                    cout << "\033[1;31mНет данных для отображения.\033[0m\n";
                }

                int afterChoice = InputIntInRange("\033[1;32m1. Вернуться в запросы\n2. Вернуться в меню\nВаш выбор:\033[0m", 1, 2);
                if (afterChoice == 2) {
                    system("clear");
                    return;
                }
}

void Student::getStudentsWithDebts(const Student students[], short studentCount, const short columnWidths[], short columnCount){
    int count = 0; 
                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].course == 3 && students[i].faculty == "ИУК" && students[i].arrear == "Да") {
                        count++;
                    }
                }
                system("clear");
                cout << "\033[1;32mКоличество студентов 3 курса ИУК с задолженностями: " << count << "\033[0m\n";

                bool hasData = false;

                cout << "+-----+--------------------+--------------------+--------------------+----------------+----------------+\n";
                cout << "|";
                printCentered("№", columnWidths[0]);
                cout << "|";
                printAligned("Фамилия", columnWidths[1]);
                cout << "|";
                printAligned("Имя", columnWidths[2]);
                cout << "|";
                printAligned("Отчество", columnWidths[3]);
                cout << "|";
                printAligned("Староста", columnWidths[9]);
                cout << "|";
                printAligned("Куратор", columnWidths[10]);
                cout << "|\n";
                cout << "+-----+--------------------+--------------------+--------------------+----------------+----------------+\n";

                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].course == 3 && students[i].faculty == "ИУК" && students[i].arrear == "Да") {
                        hasData = true;
                        cout << "|";
                        printCenteredNum(i + 1, columnWidths[0]);
                        cout << "|";
                        printAligned(students[i].surname, columnWidths[1]);
                        cout << "|";
                        printAligned(students[i].name, columnWidths[2]);
                        cout << "|";
                        printAligned(students[i].patronymic, columnWidths[3]);
                        cout << "|";
                        printAligned(students[i].curator, columnWidths[9]);
                        cout << "|";
                        printAligned(students[i].surnameElder, columnWidths[10]);
                        cout << "|\n";
                        cout << "+-----+--------------------+--------------------+--------------------+----------------+----------------+\n";
                    }
                }

                if (!hasData) {
                    cout << "\033[1;31mНет данных для отображения.\033[0m\n";
                }

                int afterChoice = InputIntInRange("\033[1;32m1. Вернуться в запросы\n2. Вернуться в меню\nВаш выбор: \033[0m", 1, 2);
                if (afterChoice == 2) {
                    system("clear");
                    return;
                }
}

void Student::getGroupWithDebts(const Student students[], short studentCount, const short columnWidths[], short columnCount) {
    bool hasData = false;
                
                system("clear");
                cout << "+-----------+----------------+----------------+-------------+\n";
                cout << "|";
                printCentered("Группа", columnWidths[4]);
                cout << "|";
                printAligned("Куратор", columnWidths[9]);
                cout << "|";
                printAligned("Староста", columnWidths[10]);
                cout << "|";
                printAligned("Факультет", columnWidths[8]);
                cout << "|\n";
                cout << "+-----------+----------------+----------------+-------------+\n";

                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].arrear == "Да") {
                        hasData = true;
                        cout << "|";
                        printCentered(students[i].group, columnWidths[4]);
                        cout << "|";
                        printAligned(students[i].curator, columnWidths[9]);
                        cout << "|";
                        printAligned(students[i].surnameElder, columnWidths[10]);
                        cout << "|";
                        printAligned(students[i].faculty, columnWidths[8]);
                        cout << "|\n";
                        cout << "+-----------+----------------+----------------+-------------+\n";
                    }
                }

                if (!hasData) {
                    cout << "\033[1;31mНет данных для отображения.\033[0m\n";
                }

                int afterChoice = InputIntInRange("\033[1;32m1. Вернуться в запросы\n2. Вернуться в меню\nВаш выбор: \033[0m", 1, 2);
                if (afterChoice == 2) {
                    system("clear");
                    return;
                }
}

void Student::getStudentsByLetter(const Student students[], short studentCount, const short columnWidths[], short columnCount) {
    string letter;
                system("clear");
                InputString(letter, "\033[1;36mВведите первую букву фамилии: \033[0m", 1);
            
                if (letter.empty()) {
                    cout << "\033[1;31mОшибка: Введена пустая строка.\033[0m\n";
                    return;
                }
            
                bool hasData = false;
            
                system("clear");
                cout << "+--------------------+--------------------+--------------------+\n";
                cout << "|";
                printAligned("Фамилия", columnWidths[1]);
                cout << "|";
                printAligned("Имя", columnWidths[2]);
                cout << "|";
                printAligned("Отчество", columnWidths[3]);
                cout << "|\n";
                cout << "+--------------------+--------------------+--------------------+\n";
            
                for (int i = 0; i < studentCount; i++) {
                    if (!students[i].surname.empty() && 
                        getFirstUtf8Char(students[i].surname) == getFirstUtf8Char(letter) && 
                        students[i].course == 2 && 
                        students[i].faculty == "МК") 
                    {
                        hasData = true;
                        cout << "|";
                        printAligned(students[i].surname, columnWidths[1]);
                        cout << "|";
                        printAligned(students[i].name, columnWidths[2]);
                        cout << "|";
                        printAligned(students[i].patronymic, columnWidths[3]);
                        cout << "|\n";
                        cout << "+--------------------+--------------------+--------------------+\n";
                    }
                }
            
                if (!hasData) {
                    cout << "\033[1;31mНет данных для отображения.\033[0m\n";
                }
            
                int afterChoice = InputIntInRange("\033[1;32m1. Вернуться в запросы\n2. Вернуться в меню\nВаш выбор: \033[0m", 1, 2);
                if (afterChoice == 2) {
                    system("clear");
                    return;
                }
}

void Student::getPercentSecAndThirdCourses(const Student students[], short studentCount, const short columnWidths[], short columnCount) {
        int count2_3 = 0;
                for (int i = 0; i < studentCount; ++i) {
                    if (students[i].course == 2 || students[i].course == 3) {
                        count2_3++;
                    }
                }
                system("clear");
                double percentage = (double)count2_3 / studentCount * 100;
                cout << "\033[1;32mПроцент студентов 2 и 3 курсов: " << fixed << setprecision(2) << percentage << "%\033[0m\n";

               
                int afterChoice = InputIntInRange("\033[1;32m1. Вернуться в запросы\n2. Вернуться в меню\nВаш выбор: \033[0m", 1, 2);
                if (afterChoice == 2) {
                    system("clear");
                    return; 
                }
}

void Student::getCuratorsDepartments(const Student students[], short studentCount, const short columnWidths[], short columnCount){
    bool hasData = false;
            
                int curatorCount[100] = {0}; 
                string curators[100];
            
                int uniqueCuratorCount = 0;
            
                for (int i = 0; i < studentCount; ++i) {
                    bool found = false;
                    for (int j = 0; j < uniqueCuratorCount; ++j) {
                        if (students[i].curator == curators[j]) {
                            found = true;
                            curatorCount[j]++;
                            break;
                        }
                    }
            
                    if (!found) {
                        curators[uniqueCuratorCount] = students[i].curator;
                        curatorCount[uniqueCuratorCount]++;
                        uniqueCuratorCount++;
                    }
                }
                system("clear");
                cout << "\033[1;32mКураторы, являющиеся преподователями кафедр:\033[0m\n";
            
                for (int i = 0; i < uniqueCuratorCount; ++i) {
                    if (curatorCount[i] > 2) {
                        hasData = true;
                        cout << "- " << curators[i] << std::endl;
                    }
                }
            
                if (!hasData) {
                    cout << "\033[1;31mНет данных для отображения.\033[0m\n";
                }
            
                int afterChoice = InputIntInRange("\033[1;32m1. Вернуться в запросы\n2. Вернуться в меню\nВаш выбор:\033[0m", 1, 2);
                if (afterChoice == 2) {
                    system("clear");
                    return;
                }
}


void Student::MenuQueries(const Student students[], short studentCount, const short columnWidths[], short columnCount) {
    if (studentCount == 0) {
        system("clear");
        cout << "\033[1;31mУпс... Данные отсутствуют.\033[0m\n";
        sleep(2);
        system("clear");
        return;
    }

    while (true) {
        system("clear");
        cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
        cout << "\033[1;32m|-------------------<<<<<<<<<<< МЕНЮ ЗАПРОСОВ >>>>>>>>>>>--------------------------------|\033[0m\n";
        cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";
        cout << "\033[1;32m| 1. Список студентов группы 1.                                                          |\033[0m\n";
        cout << "\033[1;32m| 2. Количество студентов 3 курса ИУК факультета с задолженностями.                      |\033[0m\n";
        cout << "\033[1;32m| 3. Группы с задолженностями.                                                           |\033[0m\n";
        cout << "\033[1;32m| 4. Студенты 2 курса факультета МК с фамилией, начинающейся на указанную букву.         |\033[0m\n";
        cout << "\033[1;32m| 5. Процент студентов 2 и 3 курсов.                                                     |\033[0m\n";
        cout << "\033[1;32m| 6. Кафедры кураторов.                                                                  |\033[0m\n";
        cout << "\033[1;32m| 7. Выход в меню.                                                                       |\033[0m\n";
        cout << "\033[1;32m+----------------------------------------------------------------------------------------+\033[0m\n";

        int choice = InputIntInRange("\033[1;32mВаш выбор: \033[0m", 1, 7);

        if (choice == 7) {
            system("clear");
            cout << "\033[1;31mВыход в меню...\033[0m\n";
            sleep(1);
            system("clear");
            return;
        }

        switch (choice) {
            case 1:  {
                Student::getFirstGroupList(students, studentCount, columnWidths, columnCount);
                break;
        }

            case 2: {
                Student::getStudentsWithDebts(students, studentCount, columnWidths, columnCount);
                break;
        }

            case 3: { 
                Student::getGroupWithDebts(students, studentCount, columnWidths, columnCount);
                break;
            }

            case 4: { 
                Student::getStudentsByLetter(students, studentCount, columnWidths, columnCount);
                break;
            }
            case 5: { 
                Student::getPercentSecAndThirdCourses(students, studentCount, columnWidths, columnCount);
                break;
            }

            case 6: { 
                Student::getCuratorsDepartments(students, studentCount, columnWidths, columnCount);
                break;
            }

            default:
                break;
        }
    }
}

void Student::mainMenu() {
    cout << "\033[1;32m+-------------------------------------------------------------------------+\033[0m\n";
    cout << "\033[1;32m|\033[0m";
    cout << "\033[1;32m-----------------<<<<<<<<<<< МЕНЮ ПРОГРАММЫ >>>>>>>>>>>------------------\033[0m";
    cout << "\033[1;32m|\033[0m\n"
         << "\033[1;32m+-------------------------------------------------------------------------+\033[0m\n"
         << "\033[1;32m|  (1)Работа со списком студентов.                                        |\033[0m\n"
         << "\033[1;32m|  (2)Вывод данных.                                                       |\033[0m\n"
         << "\033[1;32m|  (3)Запросы.                                                            |\033[0m\n"
         << "\033[1;32m|  (4)Сохранить данные в текстовый файл.                                  |\033[0m\n"
         << "\033[1;32m|  (5)Выход из приложения.                                                |\033[0m\n"
         << "\033[1;32m+-------------------------------------------------------------------------+\033[0m\n";
}