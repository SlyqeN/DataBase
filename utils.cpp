#include "utils.h"


void InputString(string& str, const string& prompt, size_t maxLength) {
    cout << prompt;
    getline(cin, str);
    if (str.length() > maxLength) {
        str = str.substr(0, maxLength);
        cout << "\033[1;33mСтрока была обрезана до " << maxLength << " символов.\033[0m\n";
    }
}


int InputIntInRange(const string& prompt, int minValue, int maxValue) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\033[1;31mНекорректный ввод. Попробуйте снова.\033[0m\n";
            continue;
        }

        if (value >= minValue && value <= maxValue) {
            cin.ignore(1000, '\n');
            return value;
        } else {
            cout << "\033[1;31mЗначение должно быть в диапазоне [" << minValue << ", " << maxValue << "].\033[0m\n";
        }
    }
}