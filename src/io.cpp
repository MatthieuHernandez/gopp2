#include "io.h"

#include "iostream"

using namespace std;

void printMenu(const std::string message) {
    cout << "\x1B[2J\x1B[H";
    cout << "**************************************************" << endl;
    cout << "*                   GOPP2 Menu                   *" << endl;
    cout << "**************************************************" << endl;
    cout << "* Please select one of the following:            *" << endl;
    cout << "*                                                *" << endl;
    cout << "*     1. Start a game                            *" << endl;
    cout << "*     2. Exit                                    *" << endl;
    cout << "**************************************************" << endl;
    cout << "                                                  " << endl;
    cout << message << endl;
    cout << endl;
}

int getResponseMenu() {
    int selection;
    cout << "> ";
    cin >> selection;
    return selection;
}

std::tuple<int, std::string> processResponseMenu(int selection) {
    switch (selection) {
        case 1:
            return {1, "Not yet implemented."};
        case 2:
            return {0, "Bye."};
        default:
            return {1, "Invalid selection."};
    }
}