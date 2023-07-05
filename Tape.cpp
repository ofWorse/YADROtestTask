#include <cstdio>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <type_traits>
#include <iomanip>
#include <cmath>
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


// Функция для разделения вектора на чанки и их сортировки
void Tape::sortChunks(void) {
    int numChunks = ceil(tape.size() * sizeof(int) / this->M); // Количество чанков

    for (int i = 0; i < numChunks; i++) {
        int start = i * this->M / sizeof(int);
        int end = min((i + 1) * this->M / sizeof(int), this->tape.size());
        sort(this->tape.begin() + start, this->tape.begin() + end);
    }
}

// Функция для объединения чанков и записи в выходной файл
void Tape::mergeChunks(vector<string> &chunkFiles) {
    vector<ifstream> inputFiles(chunkFiles.size());
    vector<int> currentValues(chunkFiles.size());

    ofstream outputFile(this->output_path);
    if (outputFile.is_open()) {
        // Открываем все чанки
        for (size_t i = 0; i < chunkFiles.size(); i++) {
            inputFiles[i].open(chunkFiles[i]);
            if (!inputFiles[i].is_open()) {
                cout << "Unable to open file: " << chunkFiles[i] << endl;
                return;
            }
            // Читаем первое значение из каждого чанка
            inputFiles[i] >> currentValues[i];
        }

        // Пока есть непустые чанки
        while (!inputFiles.empty()) {
            int minValue = currentValues[0];
            int minIndex = 0;

            // Выбираем минимальное значение из текущих значений чанков
            for (size_t i = 1; i < currentValues.size(); i++) {
                if (currentValues[i] < minValue) {
                    minValue = currentValues[i];
                    minIndex = i;
                }
            }

            // Записываем минимальное значение в выходной файл
            outputFile << minValue << "\n";

            // Читаем следующее значение из выбранного чанка
            if (inputFiles[minIndex] >> currentValues[minIndex]) {
                // Чтение успешно
            } else {
                // Чанк закончился, удаляем из списка
                inputFiles.erase(inputFiles.begin() + minIndex);
                currentValues.erase(currentValues.begin() + minIndex);
            }
        }

        outputFile.close();

        // Закрываем и удаляем все чанки
        for (size_t i = 0; i < chunkFiles.size(); i++) {
            inputFiles[i].close();
            remove(chunkFiles[i].c_str());
        }
    } else {
        cout << "Unable to open output file: " << this->output_path << endl;
        return;
    }
}


void Tape::sortTape(void) {
	cout << " Начало сортировки..." << endl;

	if(this->tape.size()  > this->M) { 
		//splitVectorsAndSort();
		vector<string> chunkFiles;
		for(int i = 1; i <= this->M; i++) { 
			string path = "/home/oworse/Desktop/myFiles/YADROtestTask/tmp/tmp" + to_string(i) + ".txt";
			chunkFiles.push_back(path);
		}
		sortChunks();
		mergeChunks(chunkFiles);
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
