#include <pqxx/pqxx>
#include <iostream>
#include <windows.h>
#include "phone.h"

Phone_BD::Phone_BD() {};

Phone_BD::Phone_BD(const std::string& host, const std::string& port, const std::string& dbname, const std::string& user, const std::string& password) :
	_host(host), _port(port), _dbname(dbname), _user(user), _password(password) {};

void Phone_BD::create()
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
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Phone_BD::new_client(const std::string& fname, const std::string& lname, const  std::string& email)
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
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Phone_BD::add_phone(const int& id_client, const std::string& phone)
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
				"WHERE phone = '" + trs.esc(phone) + "'";
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
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Phone_BD::update(const int& id_client, const std::string& new_fname, const std::string& new_lname, const std::string& new_email)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_upd_client =
			"UPDATE public.clients "
			"SET fname = ' " + trs.esc(new_fname) +
			"', lname = '" + trs.esc(new_lname) +
			"', email = '" + trs.esc(new_email) + "' "
			"WHERE id_client = " + trs.esc(std::to_string(id_client)) + ";";
		trs.exec(sql_upd_client);
		trs.commit();
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Phone_BD::del_phone(const int& id_client, const int& id_phone)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_del_phone =
			"DELETE FROM public.clients_phones "
			"WHERE id_client = " + trs.esc(std::to_string(id_client)) + " "
			"AND id_phone = " + trs.esc(std::to_string(id_phone)) + ";"

			"DELETE FROM public.phones "
			"WHERE id_phone = " + trs.esc(std::to_string(id_phone)) + ";";
		trs.exec(sql_del_phone);
		trs.commit();
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Phone_BD::del_client(const int& id_client)
{
	try
	{
		pqxx::connection connect_DB(
			"host=" + _host + " port=" + _port + " dbname=" + _dbname +
			" user=" + _user + " password=" + _password);
		pqxx::work trs{ connect_DB };
		std::string sql_del_client =
			"DELETE FROM public.clients_phones "
			"WHERE id_client = " + trs.esc(std::to_string(id_client)) + ";"

			"DELETE FROM public.clients "
			"WHERE id_client = " + trs.esc(std::to_string(id_client)) + ";";
		trs.exec(sql_del_client);
		trs.commit();
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
			"WHERE fname = '" + trs.esc(search_query) + "' OR "
			"lname = '" + trs.esc(search_query) + "' OR "
			"email = '" + trs.esc(search_query) + "';";
		int id_client = trs.query_value<int>(sql_find_client);
		trs.commit();
		return id_client;
	}
	catch (pqxx::sql_error e)
	{
		std::cout << e.what() << std::endl;
		return 0;
	}
}

