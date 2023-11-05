#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<string> Split(string line) {
    vector<string> stringSplit;
    if (line.empty()) {
        return stringSplit;
    }
    line += " ";
    int l_bord = 0;
    for (size_t i = 0; i != line.size(); ++i) {
        if (line[i] == ' ') {
            stringSplit.push_back(line.substr(l_bord, i-l_bord));
            stringSplit.push_back(" ");
            l_bord = i+1;
        }
    }
    return stringSplit;
}

int maxRepeatLine(vector<string> line) {
    int max = 0;
    for (size_t i = 0; i != line.size() ; ++i) {
        int code_letter = (int) line[i][0];
        if (code_letter > 64 and code_letter < 91) {
            code_letter += 32;
        }
        int local_max = 1;
        for (size_t j = 1; j != line[i].size(); ++j) {
            char32_t code = (int) line[i][j];
            if (code > 122 or code < 65) { // проверяем на латинскую букву
                break;
            }
            if (code > 64 and code < 91) { // меняем capslock на строчную
                code = code + 32;
            }
            if ((int) code_letter == code) { // если буква равна первой букве слова
                local_max += 1; // добавляем к максимум один
            }
            else { // если не равна, то заканчиваем проверку слова
                break;
            }
        }
        if (local_max > max) {
            max = local_max;
        }
    }
    return max;
}

int main() {
    string line;
    vector<string> stringSplit;
    vector<string> text;
    int repeatLines[10];
    ifstream in("/Users/vladyahnovets/CLionProjects/laba6/input.txt"); // Используем абсолютный путь, тк с просто файлом не работает

    int max=0, lineNumber=0;

    if (in.is_open()) { // если файл открылся
        int i=0;
        while(getline(in, line)) { // пока получаем данные
            text.push_back(line);
            stringSplit = Split(line);
            int local_max = maxRepeatLine(stringSplit);
            if (local_max > max) {
                lineNumber = 1;
                max = local_max;
                for (int j = 0; j < 10; ++j) {
                    repeatLines[j]= 0;

                }
                repeatLines[0] = i;
            }
            else if (local_max == max) {
                repeatLines[lineNumber] = i;
                lineNumber += 1;

            }
            i += 1;
        }
    }

    else {
        cout << "Файл пустой";
        return -1;
    }

    in.close(); // закрываем файл
    cout << max << endl;
    for (int i = 0; i < 10; ++i) {
        if (i != 0 and repeatLines[i] == 0) {
            break;
        }
        cout << text[repeatLines[i]] << " " << repeatLines[i]+1 << endl;
    }
    // a - 97, z - 122, A - 65, Z - 90
    return 0;
}
