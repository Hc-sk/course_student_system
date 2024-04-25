#include "sql_connect.h"
using namespace std;

FIR f;
MANAGER m("manager");

void choose1() {
    int a = 0, b = 1;
    while (b) {
        f.Menu2();
        cin >> a;
        switch (a) {
        case 1:
            m.add_student();
            break;
        case 2:
            m.add_course();
            break; 
        case 3:
            m.select_course();
            break;
        case 4:
            m.select_student();
            break;
        case 5:
            m.showall_course();
            break;
        case 6:
            m.showall_student();
            break;
        case 7:
            m.change_student();
            break;
        case 8:
            m.change_course();
            break;
        case 9:
            m.delete_student();
            break;
        case 10:
            m.delete_course();
            break;
        case 11:
            m.count_students();
            break;
        case 12:
            m.count_courses();
            break;
        case 13:
            m.count_students_for_course();
            break;
        case 14:
            b = 0;
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
}

void choose2(int s_id) {
    int a = 0, b = 1;
    STUDENT s(s_id); 
    while (b) {
        f.Menu3();
        cin >> a;
        switch (a) {
        case 1:
            s.course_sel();
            break;
        case 2:
            s.get_course();
            break;
        case 3:
            b = 0;
            system("pause");
            system("cls");
            break;
        default:
            break;
        }
    }
}

int main() {
    int h = 0, flag = 0, s_id = 0;
    while (1) {
        f.menu1();
        cin >> h;
        switch (h) {
        case 1:
            f.managerlogin(flag);
            if (flag == 1) {
                choose1();
            }
            break;
        case 2:
            f.studentlogin(flag, s_id);
            if (flag == 1) {
                choose2(s_id); 
            }
            break;
        default:
            break;
        }
    }
}