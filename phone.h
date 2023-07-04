#pragma once
#include <iostream>

class Phone_BD
{
private:
	Phone_BD();
	std::string _host, _port, _dbname, _user, _password;
public:
	Phone_BD(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
	// Cоздать структуру БД (таблицы)
	void create();
	// Добавить нового клиента
	void new_client(const std::string&, const std::string&, const  std::string&);
	// Добавить телефон для существующего клиента
	void add_phone(const int&, const std::string&);
	// Изменить данные о клиенте
	void update(const int&, const std::string&, const std::string&, const std::string&);
	// Удалить телефон существующего клиента
	void del_phone(const int&, const int&);
	// Удалить существующего клиента
	void del_client(const int&);
	// Найти клиента по его данным (имени, фамилии, email или телефону)
	int find_client(const std::string&);
};
