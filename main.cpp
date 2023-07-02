#include <locale>
#include "menu.h"
#include "text.h"


int main(void) {
	setlocale(LC_ALL, "RU");

	hello();
	startMenu();
	std::system("pause");
	return EXIT_SUCCESS;
}
