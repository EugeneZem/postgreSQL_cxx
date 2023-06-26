#pragma once
//#include <pqxx/pqxx>
#include<iostream>

class phoneDB
{
public:
	phoneDB(std::string, std::string, std::string, std::string, std::string);

	~phoneDB();

	// C������ ��������� �� (�������)
	void create_tbls();

	// �������� ������ �������
	void add_client(std::string, std::string, std::string, std::string);

	//�����, ����������� �������� ������� ��� ������������� �������
	//�����, ����������� �������� ������ � �������
	//�����, ����������� ������� ������� ��� ������������� �������
	//�����, ����������� ������� ������������� �������
	//�����, ����������� ����� ������� �� ��� ������(�����, �������, email - � ��� ��������)

private:
	phoneDB() {};

	std::string _host;
	std::string _port;
	std::string _name;
	std::string _user;
	std::string _password;
	pqxx::connection connectDB;

	// ���������� ���������� � ��
	void conect_DB();
};