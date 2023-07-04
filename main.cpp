#include <pqxx/pqxx>
#include <iostream>
#include <windows.h>
#include "phone.h"




int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	Phone_BD phone("localhost", "5432", "phone", "postgres", "392260");
	
	phone.create();

	std::string name;
	std::cout << "Введите имя: ";
	std::cin >> name;

	phone.new_client("Йцукен", "Некуцй", "test@mail.db");
	phone.new_client("Фывап", "Рпавыф-Ввапр", "detik@mail.mog");
	phone.new_client(name, "Ропо ло", "trulolo@mail.lo");

	phone.add_phone(1, "(10-900) 24-56");
	phone.add_phone(1, "(10-147) 24-45");
	phone.add_phone(2, "(10-147) 01-45");
	phone.add_phone(3, "(10-147) 15-60");

	phone.update(1, "Pipetc", "Holo", "test@mail.dfb");

	phone.del_phone(1, 1);

	phone.add_phone(1, "(10-450) 84-00");
	phone.add_phone(1, "(10-800) 05-45");

	phone.del_client(1);
	
	int i;
	i = phone.find_client("Фывап");
	std::string res = "Клиент \"Фывап\" содержится в базе данных под id = " + std::to_string(i);
	std::cout << res << std::endl;
	i = phone.find_client("trulolo@mail.lo");
	std::cout << "Клиент \"trulolo@mail.lo\" содержится в базе данных под id = " << i;
}

