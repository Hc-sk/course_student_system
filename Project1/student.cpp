#include "sql_connect.h"
#include <string>

int stringToInt(const string& str) {
	return stoi(str);
}

void FIR::studentlogin(int &flag,int &s_id) {
	string  pswd;
	flag = 0;
	cout << "请输入学号:";
	cin >> s_id;
	cout << "请输入密码:";
	cin >> pswd;
	MYSQL_CONN mysql_conn;
	if (mysql_conn.connect()) {
		MYSQL* mysql = mysql_conn.getmysql();
		MYSQL_RES* res;
		string query = "select * from student where s_id='" + to_string(s_id) + "' and password='" + pswd + "';";
		const char* sql = query.c_str();
		if (!mysql_query(mysql, sql)) {
			res = mysql_store_result(mysql);
			if (mysql_num_rows(res)) {
				flag = 1;
				cout << "登录成功" << endl;
			}
			else {
				cout << "账号或密码输入错误!";
			}
		}
		else {
			cout << "查询失败!";
		}
	}
	else {
		cout << "数据库连接失败!";
	}
}

STUDENT::STUDENT(int s_id) {
	this->s_id = s_id;
}

void STUDENT::course_sel() {
	string c_id;
	cout << "请输入你想选课的课程号：";
	cin >> c_id;
	MYSQL_CONN mysql_conn;
	if (mysql_conn.connect()) {
	MYSQL* mysql = mysql_conn.getmysql();
	MYSQL_RES* res;
	string find_conflict_sql = "select s_id from student_course where c_id='" + c_id + "';";
	if (!mysql_query(mysql, find_conflict_sql.c_str())) {
		res = mysql_store_result(mysql);
		if (res) {
		
			while (MYSQL_ROW row = mysql_fetch_row(res)) {
			
				if (row && row[0] && stoi(row[0]) == s_id) {
					cout << "与已选课程冲突" << endl;
					return;
				}
			}
		}
	}
	string add_new_sql = "insert into student_course (s_id,c_id) values ('"
		+ to_string(s_id) + "','" + c_id + "');";
	if (!mysql_query(mysql, add_new_sql.c_str())) {
		cout << "选课成功!";
		}
	}
}
void STUDENT::get_course() {
	string find_selected_courses_sql = "SELECT c_id FROM student_course WHERE s_id='" + to_string(s_id) + "';";
	MYSQL_CONN mysql_conn;
	if (mysql_conn.connect()) {
		MYSQL* mysql = mysql_conn.getmysql();
		if (!mysql_query(mysql, find_selected_courses_sql.c_str())) {
			MYSQL_RES* res;
			res = mysql_store_result(mysql);
			if (res) {
			
				if (mysql_num_rows(res) == 0) {
					cout << "未选课" << endl;
				}
				else {
					cout << "已选课程：" << endl;
					
					while (MYSQL_ROW row = mysql_fetch_row(res)) {
						
						if (row && row[0]) {
							cout << row[0] << endl;
						}
					}
				}
			}
		}
	}
}