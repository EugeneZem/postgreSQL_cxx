#define MODE 1  // 1 - DEBUGING

#include<pqxx/pqxx>
#include<string>
#include<iostream>
#include"phoneDB.h"

phoneDB::phoneDB(std::string h, std::string p, std::string n, std::string u, std::string pw)
	: _host{ h }, _port{ p }, _name{ n }, _user{ u }, _password{ pw }
{
#if MODE == 1
	std::cout << "host=" + _host + " port=" + _port + " dbname=" + _name + " user=" + _user + "password=" + _password;
#endif
};


void phoneDB::conect_DB()
{
	try
	{
		pqxx::connection connectDB("host=" + _host + " port=" + _port + " dbname=" + _name + " user=" + _user + "password=" + _password);
	}
	catch (std::exception e)
	{
		std::cout << "Ошибка подключения к базе данных. " << e.what() << std::endl;
	}
}

void phoneDB::add_client(std::string fn, std::string ln, std::string email, std::string phone)
{
//	if (fn )
}

void phoneDB::create_tbls()
{
	try
	{
		//std::string sql =
		//	"CREATE TABLE clients ("
		//	"id_client      int NOT NULL, "
		//	"fname			text, "
		//	"lname			text, "
		//	"email			text, "
		//	"id_phone		int, "
		//	"CONSTRAINT clients_pk PRIMARY KEY (id_client)); "

		//	"CREATE TABLE phones ("
		//	"id_phone	    int NOT NULL, "
		//	"phone			text, "
		//	"CONSTRAINT phones_pk PRIMARY KEY (id_phone)); "

		//	"CREATE TABLE clients_phones ("
		//	"id_client      int NOT NULL, "
		//	"id_phone	    int NOT NULL, "
		//	"CONSTRAINT fk1 FOREIGN KEY "
		//	"(id_client) REFERENCES public.clients(id_client), "
		//	"CONSTRAINT fk2 FOREIGN KEY "
		//	"(id_phone) REFERENCES public.phones(id_phone));";
		conect_DB();
		pqxx::work trs{ connectDB };
		//trs.exec(sql);
		//trs.commit();
	}
	catch (std::exception e)
	{
		std::cout << "Ошибка подключения к базе данных. " << e.what() << std::endl;
	}
}
