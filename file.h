#include <iostream>
#include <vector>

using namespace std;

enum overwrite : int { YES = 1, NO, ABORT };

void nameFileProtected(string &filePath, bool saveOrNot);
void writeDataToFile(const string &filePath, size_t N);
vector<int> writeDataToVector(const string &path);
void writeVectorToFile(const vector<int> &tape, const string &path);
void inputDataFromFile(void);
