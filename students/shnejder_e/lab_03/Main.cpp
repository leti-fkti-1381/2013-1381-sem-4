#include <iostream>
#include "Menu.h"
#include "Village.h"

int main()
{
	setlocale(0, "Rus");
	Menu menu;
	Village village;
	bool check = false;

	menu.print_in_menu();
	if(menu.getVar_menu() == 1)
		check = village.from_file();
	if(menu.getVar_menu() == 2)
		check = village.from_keyboard();
	if(check)
	{
		village.main_function();
		menu.print_out_menu();
		if(menu.getVar_menu() == 1)
		    village.save_to_file();
	    if(menu.getVar_menu() == 2)
		    village.print_on_screen();
	}
	else
		menu.error_message();
	system("Pause");
	return 0;
}
