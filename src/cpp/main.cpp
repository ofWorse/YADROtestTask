#include <locale>
#include "../headers/menu.h"
#include "../headers/text.h"


int main(void) {
	setlocale(LC_ALL, "RU");

	hello();
	startMenu();
	std::system("pause");
	return EXIT_SUCCESS;
}
