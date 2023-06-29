#include <pqxx/pqxx>
#include <iostream>
#include <windows.h>

// Вопросы:
//	1. Как сделать поддержку русского языка для вводимых из программы значений
//	2. Как подключить CMake заголовочный файл, чтобы перенести туда класс Phone_BD
//  3. Как сделать чтобы строчки 63 и 66 корректно отрабатывали (сейчас не вижу текст. Программа выводит только id из 66 строчки) 

class Phone_BD
{
private:
	Phone_BD();
	std::string _host, _port, _dbname, _user, _password;
public:
	Phone_BD(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
	// Cоздать структуру БД (таблицы)
	bool create();
	// Добавить нового клиента
	bool new_client(const std::string&, const std::string&, const  std::string&);
	// Добавить телефон для существующего клиента
	bool add_phone(const int&, const std::string&);
	// Изменить данные о клиенте
	bool update(const int&, const std::string&, const std::string&, const std::string&);
	// Удалить телефон существующего клиента
	bool del_phone(const int&, const int&);
	// Удалить существующего клиента
	bool del_client(const int&);
	// Найти клиента по его данным (имени, фамилии, email или телефону)
	int find_client(const std::string&);
};

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

	Phone_BD phone("localhost", "5432", "phone", "postgres", "392260");
	
	phone.create();

	phone.new_client("Real", "Reap", "test@mail.db");
	phone.new_client("Moroz", "Detik", "detik@mail.mog");
	phone.new_client("Trek", "Fents", "trulolo@mail.lo");

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
	i = phone.find_client("Moroz");
	std::string res = "Клиент Moroz содержится в базе данных под id = " + i;
	std::cout << res << std::endl;
	i = phone.find_client("Trek");
	std::cout << "Клиент Trek содержится в базе данных под id = " << i;
}

Phone_BD::Phone_BD() {};

Phone_BD::Phone_BD(const std::string& host, const std::string& port, const std::string& dbname, const std::string& user, const std::string& password):
	_host (host), _port (port), _dbname (dbname), _user (user), _password (password) {};

bool Phone_BD::create()
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_create =
			"CREATE TABLE clients ("
			"id_client      serial NOT NULL, "
			"fname			text, "
			"lname			text, "
			"email			text, "
			"CONSTRAINT clients_pk PRIMARY KEY (id_client)); "

			"CREATE TABLE phones ("
			"id_phone	    serial NOT NULL, "
			"phone			text, "
			"CONSTRAINT phones_pk PRIMARY KEY (id_phone)); "

			"CREATE TABLE clients_phones ("
			"id_client      int NOT NULL, "
			"id_phone	    int NOT NULL, "
			"CONSTRAINT fk1 FOREIGN KEY "
			"(id_client) REFERENCES public.clients(id_client), "
			"CONSTRAINT fk2 FOREIGN KEY "
			"(id_phone) REFERENCES public.phones(id_phone));";
		trs.exec(sql_create);
		trs.commit();
		return 0;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool Phone_BD::new_client(const std::string& fname, const std::string& lname, const  std::string& email)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_upd_client =
			"INSERT INTO public.clients (fname, lname, email) "
			"VALUES ('" + trs.esc(fname) + "', '" + trs.esc(lname) +
			"', '" + trs.esc(email) + "');";
		trs.exec(sql_upd_client);
		trs.commit();
		return 0;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool Phone_BD::add_phone(const int& id_client, const std::string& phone)
{
	try
	{
		{
			pqxx::connection connect_DB(
				"host=" + _host + " port=" + _port + " dbname=" + _dbname +
				" user=" + _user + " password=" + _password);
			pqxx::work trs{ connect_DB };
			std::string sql_upd_client =
				"INSERT INTO public.phones "
				"(phone) "
				"VALUES ('" + trs.esc(phone) + "'); ";
			trs.exec(sql_upd_client);
			trs.commit();
		}

		int id_phone;
		{
			pqxx::connection connect_DB(
				"host=" + _host + " port=" + _port + " dbname=" + _dbname +
				" user=" + _user + " password=" + _password);
			pqxx::work trs{ connect_DB };
			std::string sql_sel_id_phone =
				"SELECT id_phone FROM public.phones "
				"WHERE phone = '" + phone + "'";
			id_phone = trs.query_value<int>(sql_sel_id_phone);
			trs.commit();
		}

		{
			pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
			pqxx::work trs{ connect_DB };
			std::string sql_upd_client =
				"INSERT INTO public.clients_phones "
				"(id_client, id_phone) "
				"VALUES (" + trs.esc(std::to_string(id_client)) +
				", " + trs.esc(std::to_string(id_phone)) + ");";
			trs.exec(sql_upd_client);
			trs.commit();
		}
		return 0;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool Phone_BD::update(const int& id_client, const std::string& new_fname, const std::string& new_lname, const std::string& new_email)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_upd_client =
			"UPDATE public.clients "
			"SET fname = ' " + new_fname +
			"', lname = '" + new_lname +
			"', email = '" + new_email + "' "
			"WHERE id_client = " + std::to_string(id_client) + ";";
		trs.exec(sql_upd_client);
		trs.commit();
		return 0;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool Phone_BD::del_phone(const int& id_client, const int& id_phone)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_del_phone =
			"DELETE FROM public.clients_phones "
			"WHERE id_client = " + std::to_string(id_client) + " "
			"AND id_phone = " + std::to_string(id_phone) + ";"

			"DELETE FROM public.phones "
			"WHERE id_phone = " + std::to_string(id_phone) + ";";
		trs.exec(sql_del_phone);
		trs.commit();
		return 0;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

bool Phone_BD::del_client(const int& id_client)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_del_client =
			"DELETE FROM public.clients_phones "
			"WHERE id_client = " + std::to_string(id_client) + ";"

			"DELETE FROM public.clients "
			"WHERE id_client = " + std::to_string(id_client) + ";";
		trs.exec(sql_del_client);
		trs.commit();
		return 0;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

int Phone_BD::find_client(const std::string& search_query)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_find_client =
			"SELECT id_client "
			"FROM public.clients "
			"WHERE fname = '" + search_query + "' OR "
			"lname = '" + search_query + "' OR "
			"email = '" + search_query + "';";
		int id_client = trs.query_value<int>(sql_find_client);
		trs.commit();
		return id_client;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

