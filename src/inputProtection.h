#include <iostream>
#include <limits.h>

using namespace std;

template<class T>
void inputProtection(T &number, const int &lowerBound, const int &upperBound) {
	while(true) {
		cout << "Ваше число: ";
		if(cin >> number; cin.fail() || cin.get() != '\n') {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Введите число!" << endl;
			continue;
		}
		else if(number < static_cast<T>(lowerBound) || number > static_cast<T>(upperBound)) 
			cout << "Введите число от \'" << lowerBound << "\' до \'" << upperBound << "\'. " << endl;
		else break;
	}
}
