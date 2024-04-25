#pragma once
#include <iostream>
#include <winsock.h>
#include "mysql.h"
using namespace std;

class MYSQL_CONN {
private:
	const char* user, * pswd, * host, * database;
	int port;
public:
	static MYSQL* mysql;	//mysql连接句柄
	MYSQL_CONN();			//constructor
	int connect();			//连接mysql函数
	void close();			//关闭mysql
	MYSQL* getmysql();
};

class STUDENT {
private:
	int s_id;
public:
	STUDENT(int s_id);
	void course_sel();		//选课
	void get_course();
};

class MANAGER {
private:
	string name;
public:
	MANAGER(string name);
	bool studentExists(MYSQL* mysql, int s_id);
	bool courseExists(MYSQL* mysql, int c_id);
	void add_student();		//添加学生记录
	void add_course();
	void select_course();
	void select_student();
	void showall_course();
	void showall_student();
	void change_student();
	void change_course();
	bool is_integer_input(const string& input);
	void delete_student();
	void delete_course();
	void count_students();
	void count_courses();
	void count_students_for_course();
};



class MENU {
public:
	MENU() {};
	void Menu1();
	void Menu2();
	void Menu3();
};
class FIR :public MENU {
public:
	void menu1();
	void menu2();
	void menu3();
	void studentlogin(int &flag,int &s_id);
	void managerlogin(int &flag);
};
void  choose1();
void  choose2();
