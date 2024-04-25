#include "sql_connect.h"
#include <string>


void FIR::managerlogin(int &flag) {
    string user, pswd;
    cout << "����������:";
    cin >> user;
    cout << "����������:";
    cin >> pswd;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
        MYSQL_RES* res;
        string query = "select * from manager where name='" + user + "' and password='" + pswd + "';";
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

MANAGER::MANAGER(string name) {
    this->name = name;
}


bool MANAGER::studentExists(MYSQL* mysql, int s_id) {
    string check_query = "SELECT COUNT(*) FROM student WHERE s_id = " + to_string(s_id) + ";";
    if (mysql_query(mysql, check_query.c_str())) {
        cerr << "���ѧ������ʱ���� " << mysql_error(mysql) << endl;
        return false; 
    }

    MYSQL_RES* result = mysql_store_result(mysql);
    if (!result) {
        cerr << "��ȡ��������� " << mysql_error(mysql) << endl;
        return false; 
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]); 

    mysql_free_result(result); 

    return (count > 0); 
}

bool MANAGER::courseExists(MYSQL* mysql, int c_id) {
    string check_query = "SELECT COUNT(*) FROM course WHERE c_id = " + to_string(c_id) + ";";
    if (mysql_query(mysql, check_query.c_str())) {
        cerr << "���γ̴���ʱ���� " << mysql_error(mysql) << endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(mysql);
    if (!result) {
        cerr << "��ȡ��������� " << mysql_error(mysql) << endl;
        return false;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);

    mysql_free_result(result);

    return (count > 0);
}

void MANAGER::add_student() {
    int s_id, s_age;
    string name,sex,s_class,s_phone,s_department,password;
    cout << "������ѧ��ѧ�ţ�";
    cin >> s_id;
    cout << "������ѧ��������";
    cin >> name;
    cout << "������ѧ���Ա�";
    cin >> sex;
    cout << "������ѧ�����ڰ༶��";
    cin >> s_class;
    cout << "������ѧ���ֻ��ţ�";
    cin >> s_phone;
    cout << "������ѧ�����䣺";
    cin >> s_age;
    cout << "������ѧ������ϵ��";
    cin >> s_department;
    cout << "������ѧ�����룺";
    cin >> password;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
    if (studentExists(mysql, s_id)) {
        cerr << "����: ѧ��ID " << s_id << " �Ѿ����ڣ�" << endl;
        return; 
    }


    string add_stu = "INSERT INTO student (s_id, name, sex, s_class, s_phone, s_age, s_department, password) VALUES ('"
        + to_string(s_id) + "','" + name + "','" + sex + "','" + s_class + "','" + s_phone + "','" + to_string(s_age) + "','" + s_department + "','" + password + "');";

    if (mysql_query(mysql, add_stu.c_str())) {
        cerr << "���� " << mysql_error(mysql) << endl;
    }
    else {
        cout << "ѧ����¼��ӳɹ���" << endl;
        }
    }
}

void MANAGER::add_course() {
    int c_id, c_hours, c_credit, c_term, c_nums;
    string c_name, c_character;
    cout << "������γ̺ţ�";
    cin >> c_id;
    cout << "������γ�����";
    cin >> c_name;
    cout << "������ÿγ̵����ͣ�";
    cin >> c_character;
    cout << "������ÿγ̵�ѧʱ��";
    cin >> c_hours;
    cout << "������ÿγ̵�ѧ�֣�";
    cin >> c_credit;
    cout << "������ÿγ̹��м���ѧ�ڣ�";
    cin >> c_term;
    cout << "������ÿγ����ѧ��������";
    cin >> c_nums;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
    if (courseExists(mysql, c_id)) {
        cerr << "���󣺿γ�ID" << c_id << "�Ѿ����ڣ�" << endl;
        return;
    }

    string add_cou = "INSERT INTO course (c_id, c_name, c_character, c_hours, c_credit, c_term, c_nums) VALUES ('"
        + to_string(c_id) + "','" + c_name + "','" + c_character + "','" + to_string(c_hours) + "','" + to_string(c_credit) + "','" + to_string(c_term) + "','" + to_string(c_nums) + "');";

    if (mysql_query(mysql, add_cou.c_str())) {
        cerr << "���� " << mysql_error(mysql) << endl;
    }
    else {
        cout << "�γ̼�¼��ӳɹ���" << endl;
        }
    }
}

void MANAGER::select_course() {
    int c_id;
    cout << "��������Ҫ��ѯ�Ŀγ̱�ţ�";
    cin >> c_id;

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string select_course = "SELECT * FROM COURSE WHERE c_id = " + to_string(c_id) + ";";
        if (!mysql_query(mysql, select_course.c_str())) {
            MYSQL_RES* res;
            res = mysql_store_result(mysql);
            if (res) {
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row) {
                    cout << "�γ̱�ţ�" << row[0] << endl;
                    cout << "�γ����ƣ�" << row[1] << endl;
                    cout << "�γ����ԣ�" << row[2] << endl;
                    cout << "�γ�ѧʱ��" << row[3] << endl;
                    cout << "�γ�ѧ�֣�" << row[4] << endl;
                    cout << "�γ�ѧ�ڣ�" << row[5] << endl;
                    cout << "�γ����������" << row[6] << endl;
                }
                else {
                    cout << "δ�ҵ��γ���Ϣ" << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "��ѯ���Ϊ��" << endl;
            }
        }
        else {
            cout << "��ѯʧ��" << endl;
        }
    }
}

void MANAGER::select_student() {
    string name;
    cout << "��������Ҫ��ѯѧ����������";
    cin >> name;

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
    
        string select_student = "SELECT * FROM STUDENT WHERE NAME = '" + name + "';";
        if (!mysql_query(mysql, select_student.c_str())) {
            MYSQL_RES* res;
            res = mysql_store_result(mysql);
            if (res) {
                MYSQL_ROW row = mysql_fetch_row(res);
                if (row) {
                    cout << "ѧ��ѧ�ţ�" << row[0] << endl;
                    cout << "ѧ��������" << row[1] << endl;
                    cout << "ѧ���Ա�" << row[2] << endl;
                    cout << "ѧ���༶��" << row[3] << endl;
                    cout << "ѧ���ֻ����룺" << row[4] << endl;
                    cout << "ѧ�����䣺" << row[5] << endl;
                    cout << "ѧ������ϵ��" << row[6] << endl;
                    cout << "ѧ�����룺" << row[6] << endl;
                }
                else {
                    cout << "δ�ҵ�ѧ����Ϣ" << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "��ѯ���Ϊ��" << endl;
            }
        }
        else {
            cout << "��ѯʧ��" << endl;
            }
        }
    }

void MANAGER::showall_course() {
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
        string select_all_courses = "SELECT * FROM COURSE;";

        if (!mysql_query(mysql, select_all_courses.c_str())) {
            MYSQL_RES* res;
            res = mysql_store_result(mysql);
            if (res) {
                while (MYSQL_ROW row = mysql_fetch_row(res)) {
                    cout << "�γ̱�ţ�" << row[0] << endl;
                    cout << "�γ����ƣ�" << row[1] << endl;
                    cout << "�γ����ԣ�" << row[2] << endl;
                    cout << "�γ�ѧʱ��" << row[3] << endl;
                    cout << "�γ�ѧ�֣�" << row[4] << endl;
                    cout << "�γ�ѧ�ڣ�" << row[5] << endl;
                    cout << "�γ����������" << row[6] << endl;
                    cout << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "��ѯ���Ϊ��" << endl;
            }
        }
        else {
            cout << "��ѯʧ�ܣ�" << mysql_error(mysql) << endl; 
        }
    }
}
    
void MANAGER::showall_student() {
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
        string select_all_courses = "SELECT * FROM STUDENT;";

        if (!mysql_query(mysql, select_all_courses.c_str())) {
            MYSQL_RES* res;
            res = mysql_store_result(mysql);
            if (res) {
                while (MYSQL_ROW row = mysql_fetch_row(res)) {
                    cout << "ѧ��ѧ�ţ�" << row[0] << endl;
                    cout << "ѧ��������" << row[1] << endl;
                    cout << "ѧ���Ա�" << row[2] << endl;
                    cout << "ѧ���༶��" << row[3] << endl;
                    cout << "ѧ���ֻ����룺" << row[4] << endl;
                    cout << "ѧ�����䣺" << row[5] << endl;
                    cout << "ѧ������ϵ��" << row[6] << endl;
                    cout << "ѧ�����룺" << row[6] << endl;
                    cout << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "��ѯ���Ϊ��" << endl;
            }
        }
        else {
            cout << "��ѯʧ�ܣ�" << mysql_error(mysql) << endl;
        }
    }
}

void MANAGER::change_student() {
    int s_id;
    string changeconnect;
    string changed_str;
    int changed_int;

    cout << "��������Ҫ�޸�ѧ����ѧ�ţ�";
    cin >> s_id;
    cout << "��������Ҫ�޸ĵ��ֶ�����";
    cin >> changeconnect;

    cout << "��������ϣ�������޸�Ϊ�������������������������������ַ������������ַ�������";
    if (is_integer_input(changeconnect)) { 
        cin >> changed_int;
    }
    else {
        cin.ignore(); 
        getline(cin, changed_str);
    }

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

     
        string update_query;
        if (is_integer_input(changeconnect)) {
            update_query = "UPDATE STUDENT SET " + changeconnect + " = " + to_string(changed_int) + " WHERE s_id = " + to_string(s_id);
        }
        else {
            update_query = "UPDATE STUDENT SET " + changeconnect + " = '" + changed_str + "' WHERE s_id = " + to_string(s_id);
        }

 
        if (mysql_query(mysql, update_query.c_str())) {
            cout << "����ʧ��: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "��¼�ѳɹ����£�" << endl;
        }
    }
}
bool MANAGER::is_integer_input(const string& input) {
    return input == "age" || input == "grade";
}

void MANAGER::change_course() {
    int c_id;
    string changeconnect;
    string changed_str;
    int changed_int;

    cout << "��������Ҫ�޸Ŀγ̵�ѧ�ţ�";
    cin >> c_id;
    cout << "��������Ҫ�޸ĵ��ֶ�����";
    cin >> changeconnect;

    cout << "��������ϣ�������޸�Ϊ�������������������������������ַ������������ַ�������";
    if (is_integer_input(changeconnect)) {
        cin >> changed_int;
    }
    else {
        cin.ignore();
        getline(cin, changed_str);
    }

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();


        string update_query;
        if (is_integer_input(changeconnect)) {
            update_query = "UPDATE COURSE SET " + changeconnect + " = " + to_string(changed_int) + " WHERE c_id = " + to_string(c_id);
        }
        else {
            update_query = "UPDATE COURSE SET " + changeconnect + " = '" + changed_str + "' WHERE c_id = " + to_string(c_id);
        }


        if (mysql_query(mysql, update_query.c_str())) {
            cout << "����ʧ��: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "��¼�ѳɹ����£�" << endl;
        }
    }
}

void MANAGER::delete_student() {
    int s_id;
    cout << "��������ϣ��ɾ����ѧ����¼��ѧ�ţ�";
    cin >> s_id;

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string check_query = "SELECT * FROM STUDENT WHERE s_id = " + to_string(s_id);
        if (mysql_query(mysql, check_query.c_str())) {
            cout << "��ѯʧ��: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        if (result == nullptr || mysql_num_rows(result) == 0) {
            cout << "��¼Ϊ�գ�" << endl;
            mysql_free_result(result);
            return;
        }

        mysql_free_result(result);


        string delete_query = "DELETE FROM STUDENT WHERE s_id = " + to_string(s_id);


        if (mysql_query(mysql, delete_query.c_str())) {
            cout << "ɾ��ʧ��: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "��¼�ѳɹ�ɾ����" << endl;
        }
    }
}
void MANAGER::delete_course() {
    int c_id;
    cout << "��������ϣ��ɾ���Ŀγ̼�¼�Ŀγ̺ţ�";
    cin >> c_id;

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string check_query = "SELECT * FROM COURSE WHERE c_id = " + to_string(c_id);
        if (mysql_query(mysql, check_query.c_str())) {
            cout << "��ѯʧ��: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        if (result == nullptr || mysql_num_rows(result) == 0) {
            cout << "��¼Ϊ�գ�" << endl;
            mysql_free_result(result);
            return;
        }

        mysql_free_result(result);


        string delete_query = "DELETE FROM COURSE WHERE c_id = " + to_string(c_id);


        if (mysql_query(mysql, delete_query.c_str())) {
            cout << "ɾ��ʧ��: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "��¼�ѳɹ�ɾ����" << endl;
        }
    }
}
void MANAGER::count_students() {
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string count_query = "SELECT COUNT(*) FROM STUDENT";
        if (mysql_query(mysql, count_query.c_str())) {
            cout << "��ѯʧ��: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        MYSQL_ROW row = mysql_fetch_row(result);
        int count = stoi(row[0]); 
        mysql_free_result(result);

        cout << "ѧ��������" << count << endl;
    }
}


void MANAGER::count_courses() {
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string count_query = "SELECT COUNT(*) FROM COURSE";
        if (mysql_query(mysql, count_query.c_str())) {
            cout << "��ѯʧ��: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        MYSQL_ROW row = mysql_fetch_row(result);
        int count = stoi(row[0]); 
        mysql_free_result(result);

        cout << "�γ̵�������" << count << endl;
    }
}


void MANAGER::count_students_for_course() {
    string c_id;
    cout << "������γ̺ţ�";
    cin >> c_id;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string count_query = "SELECT * FROM STUDENT_COURSE WHERE c_id = '" + c_id + "'";
        if (mysql_query(mysql, count_query.c_str())) {
            cout << "��ѯʧ��: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;

        cout << "ѡ�޿γ� \"" << c_id << "\" ��ѧ��ѧ�ţ�" << endl;
        while ((row = mysql_fetch_row(result))) {
                cout << row[0] << " ";
        }
        cout << endl;
        mysql_free_result(result);
    }
}