#include<iostream>
#include"phoneDB.h"

int main()
{
	//setlocale(LC_ALL, "ru-RU");
	//system("chcp 1251");

	phoneDB db("localhost", "5432", "phone", "postgres", "392260");
	db.create_tbls();





	return 0;
}