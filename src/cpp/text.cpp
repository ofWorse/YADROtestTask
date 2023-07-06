#include <iostream>
#include "../headers/text.h"
using namespace std;

void hello(void) {
    cout << "Тестовое задание от YADRO." << endl;
    cout << "Решение: Малания Марк Тимрович." << endl;
    cout << "Задача: реализовать эмуляцию работы с утройством типа лента." << endl;
    cout << endl;
}

void menu(const numberMenu menuNumber) {
    switch(menuNumber) {
    case(numberMenu::START_MENU):
        cout << "1 - Начать программу;" << endl;
        cout << "2 - Выйти из программы." << endl;
        cout << endl;
        break;
    case(numberMenu::MAIN_MENU):
        cout << "1 - Начать сортировку;" << endl;
		cout << "2 - Сдвинуть ленту на позицию;" << endl;
		cout << "3 - Редактировать файл конфигурации программы;" << endl;
        cout << "4 - Назад." << endl;
        cout << endl;
        break;
	case(numberMenu::SHIFT_DATA_MENU):
		cout << "В какую сторону сделать сдвиг данных?" << endl;
		cout << "1 - Вправо;" << endl;
		cout << "2 - Влево;" << endl;
		cout << "3 - Назад." << endl;
		cout << endl;
		break;
	case(numberMenu::REWRITE_PATHS_MENU):
		cout << "Данные о местоположении файла уже записаны, перезаписать?" << endl;
		cout << "1 - Да;" << endl;
		cout << "2 - Нет;" << endl;
		cout << "3 - Назад." << endl;
		cout << endl;
		break;
	}
}

