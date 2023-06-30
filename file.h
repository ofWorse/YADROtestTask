#include <iostream>

using namespace std;

enum overwrite : int { YES = 1, NO, ABORT };

void nameFileProtected(string &filePath, bool saveOrNot);
void writeDataToFile(const string &filePath, size_t N);
void inputDataFromFile(void);
