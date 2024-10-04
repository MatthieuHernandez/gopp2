#include <string>
#include <tuple>

void printMenu(const std::string message);

int getResponseMenu();

std::tuple<int, std::string> processResponseMenu(int selection);