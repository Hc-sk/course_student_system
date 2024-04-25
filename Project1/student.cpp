#include "sql_connect.h"
#include <string>

int stringToInt(const string& str) {
	return stoi(str);
}

void FIR::studentlogin(int &flag,int &s_id) {
	string  pswd;
	flag = 0;
	cout << "������ѧ��:";
	cin >> s_id;
	cout << "����������:";
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
				cout << "��¼�ɹ�" << endl;
			}
			else {
				cout << "�˺Ż������������!";
			}
		}
		else {
			cout << "��ѯʧ��!";
		}
	}
	else {
		cout << "���ݿ�����ʧ��!";
	}
}

STUDENT::STUDENT(int s_id) {
	this->s_id = s_id;
}

void STUDENT::course_sel() {
	string c_id;
	cout << "����������ѡ�εĿγ̺ţ�";
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
					cout << "����ѡ�γ̳�ͻ" << endl;
					return;
				}
			}
		}
	}
	string add_new_sql = "insert into student_course (s_id,c_id) values ('"
		+ to_string(s_id) + "','" + c_id + "');";
	if (!mysql_query(mysql, add_new_sql.c_str())) {
		cout << "ѡ�γɹ�!";
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
					cout << "δѡ��" << endl;
				}
				else {
					cout << "��ѡ�γ̣�" << endl;
					
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