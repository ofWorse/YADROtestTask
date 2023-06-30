#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
	ifstream in("input.txt");	
	ofstream out("output.txt");	
	vector<int> arr;

	// это в функцию по заносу из файла в вектор
	if(in) {
		string line;
		getline(in, line);
		istringstream iss(line);
		string numberStr;
		while (getline(iss, numberStr, ' ')) {
			arr.push_back(stoi(numberStr));
		}
	}
	cout << "unsorted: \n";
	for(int i = 0; i < arr.size(); i++) cout << arr[i] << " ";
	cout << endl;

	sort(arr.begin(), arr.end());

	for(int i = 0; i < arr.size(); i++)
		out << arr.at(i) << " ";
	out << "\n";
	in.close();
	out.close();
	return 0;
}
