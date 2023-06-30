#include <cstdlib>
#include <locale.h>
#include "text.h"
#include "menu.h"

int main(void) {

	setlocale(LC_ALL, "RU");
	hello();
	startmenu();
	std::system("pause");
	return EXIT_SUCCESS;
}
