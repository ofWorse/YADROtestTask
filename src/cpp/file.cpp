#include "../headers/file.h"
#include "../headers/inputProtection.h"
#include <climits>
#include <fstream>
#include <string>
#include <system_error>
#include <random>
#include <vector>

void nameFileProtected(string &filePath, bool saveOrNot) {
	fstream file;
	while(true) {
		cout << "Введите местоположение файла: ";
		if(getline(cin, filePath); ifstream(filePath) && saveOrNot == true) {
			int userChoice(0);
			cout << "Файл ранее был в системе." << endl;
			cout << "1 - Перезаписать файл," << endl;
			cout << "2 - Ввести другой путь," << endl;
			cout << "3 - Отмена." << endl;
			inputProtection(userChoice, 1, 3);
			switch (userChoice) {
				case(overwrite::YES): 
					file.open(filePath, ios::trunc | ios::out);
					file.close();
					break;
				case(overwrite::NO):
					file.close();
					break;
				case(overwrite::ABORT):
					return;
					break;
			}
		}
		else if(saveOrNot == false && !ifstream(filePath)) {
			cout << "Данного файла не существует." << endl;
			continue;
		}
		file.open(filePath, ios::app);
		if(!file) {
			cout << "Файл либо для чтения, либо у вас недостаточно прав, либо путь введен некорректно!" << endl;
			file.close();
			continue;
		}
		error_code err;
		if(filePath.substr(filePath.size() - 4) != ".txt") {
			cout << "Введите наименование файла с расширением \'.txt\'!" << endl;
			continue;
		}
		break;
	}
}

void writeDataToFile(const string &filePath, size_t N) {
	ofstream out(filePath);
	if(out) {
		random_device rand;
		mt19937 generate(rand());
		uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

		for(int i = 0; i < N; ++i) 
			out << distribution(generate) << "\n"; 

		out.close();
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
}

vector<int> writeDataToVector(const string &path) {
	ifstream input(path);
	vector<int> res;
	string line;
	if(input) {
		while(getline(input, line)) {
			int number = stoi(line);
			res.push_back(number);
		}	
		input.close();
		return res;
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
}

void writeVectorToFile(const vector<int> &tape, const string &path) {
	ofstream out(path);
	if(out) {
		for(const auto &num : tape)
			out << num << "\n";
		out.close();
	}
	else {
		cout << "Ошибка открытия файла!" << endl;
	}
}
