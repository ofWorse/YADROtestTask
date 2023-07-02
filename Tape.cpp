#include <cstdio>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <type_traits>
#include <vector>
#include "Tape.h"
#include "inputProtection.h"


void Tape::setupPaths(void) {
	cout << "Введите путь к исходной ленте." << endl;
	string path;
	nameFileProtected(path, false);
	this->input_path = path;
	cout << "Введите путь к будучи отсортированной ленте." << endl;
	nameFileProtected(path, false);
	this->output_path = path;
}

void Tape::makeTape(void) {
	srand(time(NULL));
	if(consistPaths()) {
		writeDataToFile(input_path, this->N);
		this->tape = writeDataToVector(this->input_path);
		cout << "Данные в файл " << input_path << " успешно загружены." << endl;
	}
	else {
		cout << "Для начала, введите путь к исходным файлам!" << endl;
		return;
	}
}

vector<int> merge(const vector<int> &tape1, const vector<int> &tape2) {
	vector<int> resultTape;
	size_t i = 0, j = 0;

	while(i < tape1.size() && j < tape2.size()) {
		if(tape1[i] <= tape2[j]) 
			resultTape.push_back(tape1[i++]);
		else resultTape.push_back(tape2[j++]);
	}
	while(i < tape1.size()) 
		resultTape.push_back(tape1[i++]);
	while(j < tape2.size()) 
		resultTape.push_back(tape2[j++]);
	return resultTape;
}

// TODO: очистить!!!
// NOTE: Не сохраняет результат в вектор или файл (файл output.txt пустой после данных операций)
void Tape::sortEveryFile(int begin, int countOfFiles, vector<int> &tape) {
	if(begin < countOfFiles) {
		string path1 = tmp_dir_path + "tmp" + to_string(begin) + ".txt";
		string path2 = tmp_dir_path + "tmp" + to_string(begin+1) + ".txt";
		vector<int> tape1 = writeDataToVector(path1);
		vector<int> tape2 = writeDataToVector(path2);
		sort(tape1.begin(), tape1.end());
		sort(tape2.begin(), tape2.end());
		vector<int> tmpTape = merge(tape1, tape2);
		copy(tmpTape.begin(), tmpTape.end(), tape.begin());
		sortEveryFile(begin+1, countOfFiles, tape);
	}
	else if(begin == countOfFiles) {
		string path1 = tmp_dir_path + "tmp" + to_string(begin) + ".txt";
		string path2 = tmp_dir_path + "tmpLast.txt";
		vector<int> tape1 = writeDataToVector(path1);
		vector<int> tape2 = writeDataToVector(path2);
		sort(tape1.begin(), tape1.end());
		sort(tape2.begin(), tape2.end());
		vector<int> tmpTape = merge(tape1, tape2);
		copy(tmpTape.begin(), tmpTape.end(), tape.begin());
		writeVectorToFile(tape, this->output_path);
	}
	else cout << "Ошибка в размерности вектора!" << endl;
}

void Tape::splitVectorsAndSort(void) {
	int count = (this->tape.size()) / this->M;
	vector<int> tmpTape, copyTape = this->tape;
	for(int i = 1; i <= count; i++) {
		for(int j = 0; j < this->M; j++) {
			tmpTape.push_back(copyTape.front());
			copyTape.erase(copyTape.begin());
		}
		writeVectorToFile(tmpTape, this->tmp_dir_path + "tmp" + to_string(i) + ".txt");
		tmpTape.clear();
	}
	if(!copyTape.empty()) {
		for(const auto &num : copyTape) tmpTape.push_back(num);
		writeVectorToFile(tmpTape, this->tmp_dir_path + "tmpLast.txt");
		tmpTape.clear();
	}
	// TODO: Далее требуется отсортировать tmp файлы.
	sortEveryFile(1, count, tmpTape);	
}

void Tape::sortTape(void) {
	cout << " Начало сортировки..." << endl;

	if(this->tape.size() > this->M) { //TODO: переделать
		splitVectorsAndSort();	
	}	
	else {
		sort(this->tape.begin(), this->tape.end());
		writeVectorToFile(this->tape, this->output_path);
	}

	cout << " Конец сортировки." << endl;
	cout << " Отсортированная лента записана в файл: " << this->output_path << endl;
}

void Tape::shiftLeft(void) {
	//this->shift_step %= tape.size(); // преобразование сдвига к диапозону размера вектора
	rotate(tape.begin(), tape.begin() + shift_step, tape.end());
}

void Tape::shiftRight(void) {
	//shift_amount %= tape.size(); // преобразование сдвига к диапозону размера вектора
	rotate(tape.rbegin(), tape.rbegin() + shift_step, tape.rend());
}

void Tape::moveData(bool right) {
	right ? shiftRight() : shiftLeft();
	writeVectorToFile(this->tape, this->input_path);	
}

void Tape::rewriteConfig(void) {

	string str{};
	int num;
	ofstream config(this->config_path);
	cout << "Введите новые параметры для конфигурационного файла." << endl;
	cout << "Введите длину ленты N." << endl;
	inputProtection(num, 1, INT_MAX);
	str += to_string(num) + "\n";
	cout << "Введите ограничение по использованию оперативной памяти M." << endl;
	inputProtection(num, 1, num - 1);
	str += to_string(num) + "\n";
	cout << "Введите число задержки по записи/чтению элемента ленты." << endl;
	inputProtection(num, 0, 100);
	str += to_string(num) + "\n";
	cout << "Введите число перемотки ленты." << endl;
	inputProtection(num, 0, 100);
	str += to_string(num) + "\n";
	cout << "Введите число сдвига ленты на одну позицию." << endl;
	inputProtection(num, 0, 100);
	str += to_string(num) + "\n";

	if(config) {
		config << str << endl;
	}
	else 
		cout << "Ошибка открытия файла!" << endl;
	config.close();
}

void Tape::readConfig(void) {
	ifstream config(this->config_path);
	vector<int> params;
	string line;
	while(getline(config, line)) {
		istringstream iss(line);
		string stringNumber;

		while(getline(iss, stringNumber, ' ')) {
			try {
				int number = stoi(stringNumber);
				params.push_back(number);
			} catch (const invalid_argument &e) {
				cerr << "Ошибка преобразования строки в число: " << stringNumber << "." << endl;
			}
		}
	}
	if(params.size() >= 5) {
		this->N = params.at(0);
		this->M = params.at(1);
		this->recording_delay = params.at(2);
		this->tape_rewinding = params.at(3);
		this->shift_step = params.at(4);
	}
	config.close();
}

bool Tape::consistPaths(void) {
	return !(this->input_path.empty() || this->output_path.empty());
}
