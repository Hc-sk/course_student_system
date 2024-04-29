#include "sql_connect.h"
#include <string>


void FIR::managerlogin(int &flag) {
    string user, pswd;
    cout << "请输入姓名:";
    cin >> user;
    cout << "请输入密码:";
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

MANAGER::MANAGER(string name) {
    this->name = name;
}


bool MANAGER::studentExists(MYSQL* mysql, int s_id) {
    string check_query = "SELECT COUNT(*) FROM student WHERE s_id = " + to_string(s_id) + ";";
    if (mysql_query(mysql, check_query.c_str())) {
        cerr << "检查学生存在时出错： " << mysql_error(mysql) << endl;
        return false; 
    }

    MYSQL_RES* result = mysql_store_result(mysql);
    if (!result) {
        cerr << "获取结果集出错： " << mysql_error(mysql) << endl;
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
        cerr << "检查课程存在时出错： " << mysql_error(mysql) << endl;
        return false;
    }

    MYSQL_RES* result = mysql_store_result(mysql);
    if (!result) {
        cerr << "获取结果集出错： " << mysql_error(mysql) << endl;
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
    cout << "请输入学生学号：";
    cin >> s_id;
    cout << "请输入学生姓名：";
    cin >> name;
    cout << "请输入学生性别：";
    cin >> sex;
    cout << "请输入学生所在班级：";
    cin >> s_class;
    cout << "请输入学生手机号：";
    cin >> s_phone;
    cout << "请输入学生年龄：";
    cin >> s_age;
    cout << "请输入学生所在系：";
    cin >> s_department;
    cout << "请输入学生密码：";
    cin >> password;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
    if (studentExists(mysql, s_id)) {
        cerr << "错误: 学生ID " << s_id << " 已经存在！" << endl;
        return; 
    }


    string add_stu = "INSERT INTO student (s_id, name, sex, s_class, s_phone, s_age, s_department, password) VALUES ('"
        + to_string(s_id) + "','" + name + "','" + sex + "','" + s_class + "','" + s_phone + "','" + to_string(s_age) + "','" + s_department + "','" + password + "');";

    if (mysql_query(mysql, add_stu.c_str())) {
        cerr << "错误： " << mysql_error(mysql) << endl;
    }
    else {
        cout << "学生记录添加成功！" << endl;
        }
    }
}

void MANAGER::add_course() {
    int c_id, c_hours, c_credit, c_term, c_nums;
    string c_name, c_character;
    cout << "请输入课程号：";
    cin >> c_id;
    cout << "请输入课程名：";
    cin >> c_name;
    cout << "请输入该课程的类型：";
    cin >> c_character;
    cout << "请输入该课程的学时：";
    cin >> c_hours;
    cout << "请输入该课程的学分：";
    cin >> c_credit;
    cout << "请输入该课程共有几个学期：";
    cin >> c_term;
    cout << "请输入该课程最大学生数量：";
    cin >> c_nums;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();
    if (courseExists(mysql, c_id)) {
        cerr << "错误：课程ID" << c_id << "已经存在！" << endl;
        return;
    }

    string add_cou = "INSERT INTO course (c_id, c_name, c_character, c_hours, c_credit, c_term, c_nums) VALUES ('"
        + to_string(c_id) + "','" + c_name + "','" + c_character + "','" + to_string(c_hours) + "','" + to_string(c_credit) + "','" + to_string(c_term) + "','" + to_string(c_nums) + "');";

    if (mysql_query(mysql, add_cou.c_str())) {
        cerr << "错误： " << mysql_error(mysql) << endl;
    }
    else {
        cout << "课程记录添加成功！" << endl;
        }
    }
}

void MANAGER::select_course() {
    int c_id;
    cout << "请输入您要查询的课程编号：";
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
                    cout << "课程编号：" << row[0] << endl;
                    cout << "课程名称：" << row[1] << endl;
                    cout << "课程属性：" << row[2] << endl;
                    cout << "课程学时：" << row[3] << endl;
                    cout << "课程学分：" << row[4] << endl;
                    cout << "课程学期：" << row[5] << endl;
                    cout << "课程最大人数：" << row[6] << endl;
                }
                else {
                    cout << "未找到课程信息" << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "查询结果为空" << endl;
            }
        }
        else {
            cout << "查询失败" << endl;
        }
    }
}

void MANAGER::select_student() {
    string name;
    cout << "请输入您要查询学生的姓名：";
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
                    cout << "学生学号：" << row[0] << endl;
                    cout << "学生姓名：" << row[1] << endl;
                    cout << "学生性别：" << row[2] << endl;
                    cout << "学生班级：" << row[3] << endl;
                    cout << "学生手机号码：" << row[4] << endl;
                    cout << "学生年龄：" << row[5] << endl;
                    cout << "学生所在系：" << row[6] << endl;
                    cout << "学生密码：" << row[6] << endl;
                }
                else {
                    cout << "未找到学生信息" << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "查询结果为空" << endl;
            }
        }
        else {
            cout << "查询失败" << endl;
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
                    cout << "课程编号：" << row[0] << endl;
                    cout << "课程名称：" << row[1] << endl;
                    cout << "课程属性：" << row[2] << endl;
                    cout << "课程学时：" << row[3] << endl;
                    cout << "课程学分：" << row[4] << endl;
                    cout << "课程学期：" << row[5] << endl;
                    cout << "课程最大人数：" << row[6] << endl;
                    cout << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "查询结果为空" << endl;
            }
        }
        else {
            cout << "查询失败：" << mysql_error(mysql) << endl; 
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
                    cout << "学生学号：" << row[0] << endl;
                    cout << "学生姓名：" << row[1] << endl;
                    cout << "学生性别：" << row[2] << endl;
                    cout << "学生班级：" << row[3] << endl;
                    cout << "学生手机号码：" << row[4] << endl;
                    cout << "学生年龄：" << row[5] << endl;
                    cout << "学生所在系：" << row[6] << endl;
                    cout << "学生密码：" << row[6] << endl;
                    cout << endl;
                }
                mysql_free_result(res);
            }
            else {
                cout << "查询结果为空" << endl;
            }
        }
        else {
            cout << "查询失败：" << mysql_error(mysql) << endl;
        }
    }
}

void MANAGER::change_student() {
    int s_id;
    string changeconnect;
    string changed_str;
    int changed_int;

    cout << "请输入您要修改学生的学号：";
    cin >> s_id;
    cout << "请输入您要修改的字段名：";
    cin >> changeconnect;

    cout << "请输入您希望将其修改为（如果是整数，请输入整数；如果是字符串，请输入字符串）：";
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
            cout << "更新失败: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "记录已成功更新！" << endl;
        }
    }
}
bool MANAGER::is_integer_input(const string& input) {
    return input == "s_age" || input == "s_id"||input=="c_id"||input=="c_hours"||input=="c_credit"||input=="c_term"||input=="c_nums";
}

void MANAGER::change_course() {
    int c_id;
    string changeconnect;
    string changed_str;
    int changed_int;

    cout << "请输入您要修改课程的课程号：";
    cin >> c_id;
    cout << "请输入您要修改的字段名：";
    cin >> changeconnect;

    cout << "请输入您希望将其修改为（如果是整数，请输入整数；如果是字符串，请输入字符串）：";
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
            cout << "更新失败: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "记录已成功更新！" << endl;
        }
    }
}

void MANAGER::delete_student() {
    int s_id;
    cout << "请输入您希望删除的学生记录的学号：";
    cin >> s_id;

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string check_query = "SELECT * FROM STUDENT WHERE s_id = " + to_string(s_id);
        if (mysql_query(mysql, check_query.c_str())) {
            cout << "查询失败: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        if (result == nullptr || mysql_num_rows(result) == 0) {
            cout << "记录为空！" << endl;
            mysql_free_result(result);
            return;
        }

        mysql_free_result(result);


        string delete_query = "DELETE FROM STUDENT WHERE s_id = " + to_string(s_id);


        if (mysql_query(mysql, delete_query.c_str())) {
            cout << "删除失败: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "记录已成功删除！" << endl;
        }
    }
}
void MANAGER::delete_course() {
    int c_id;
    cout << "请输入您希望删除的课程记录的课程号：";
    cin >> c_id;

    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string check_query = "SELECT * FROM COURSE WHERE c_id = " + to_string(c_id);
        if (mysql_query(mysql, check_query.c_str())) {
            cout << "查询失败: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        if (result == nullptr || mysql_num_rows(result) == 0) {
            cout << "记录为空！" << endl;
            mysql_free_result(result);
            return;
        }

        mysql_free_result(result);


        string delete_query = "DELETE FROM COURSE WHERE c_id = " + to_string(c_id);


        if (mysql_query(mysql, delete_query.c_str())) {
            cout << "删除失败: " << mysql_error(mysql) << endl;
        }
        else {
            cout << "记录已成功删除！" << endl;
        }
    }
}
void MANAGER::count_students() {
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string count_query = "SELECT COUNT(*) FROM STUDENT";
        if (mysql_query(mysql, count_query.c_str())) {
            cout << "查询失败: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        MYSQL_ROW row = mysql_fetch_row(result);
        int count = stoi(row[0]); 
        mysql_free_result(result);

        cout << "学生人数：" << count << endl;
    }
}


void MANAGER::count_courses() {
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string count_query = "SELECT COUNT(*) FROM COURSE";
        if (mysql_query(mysql, count_query.c_str())) {
            cout << "查询失败: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        MYSQL_ROW row = mysql_fetch_row(result);
        int count = stoi(row[0]); 
        mysql_free_result(result);

        cout << "课程的门数：" << count << endl;
    }
}


void MANAGER::count_students_for_course() {
    string c_id;
    cout << "请输入课程号：";
    cin >> c_id;
    MYSQL_CONN mysql_conn;
    if (mysql_conn.connect()) {
        MYSQL* mysql = mysql_conn.getmysql();

        string count_query = "SELECT * FROM STUDENT_COURSE WHERE c_id = '" + c_id + "'";
        if (mysql_query(mysql, count_query.c_str())) {
            cout << "查询失败: " << mysql_error(mysql) << endl;
            return;
        }

        MYSQL_RES* result = mysql_store_result(mysql);
        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;

        cout << "选修课程 \"" << c_id << "\" 的学生学号：" << endl;
        while ((row = mysql_fetch_row(result))) {
                cout << row[0] << " ";
        }
        cout << endl;
        mysql_free_result(result);
    }
}
