#pragma once
//#include <pqxx/pqxx>
#include<iostream>

class phoneDB
{
public:
	phoneDB(std::string, std::string, std::string, std::string, std::string);

	~phoneDB();

	// Cоздать структуру Ѕƒ (таблицы)
	void create_tbls();

	// ƒобавить нового клиента
	void add_client(std::string, std::string, std::string, std::string);

	//ћетод, позвол€ющий добавить телефон дл€ существующего клиента
	//ћетод, позвол€ющий изменить данные о клиенте
	//ћетод, позвол€ющий удалить телефон дл€ существующего клиента
	//ћетод, позвол€ющий удалить существующего клиента
	//ћетод, позвол€ющий найти клиента по его данным(имени, фамилии, email - у или телефону)

private:
	phoneDB() {};

	std::string _host;
	std::string _port;
	std::string _name;
	std::string _user;
	std::string _password;
	pqxx::connection connectDB;

	// ”становить соединение с Ѕƒ
	void conect_DB();
};