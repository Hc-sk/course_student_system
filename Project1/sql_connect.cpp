#include "sql_connect.h"

MYSQL* MYSQL_CONN::mysql = NULL;

MYSQL_CONN::MYSQL_CONN() {
    this->user = "root";
    this->pswd = "gyhshaonian123";
    this->host = "127.0.0.1";
    this->database = "course_choice";
    this->port = 3306;
}

int MYSQL_CONN::connect() {
    if (MYSQL_CONN::mysql) {
        return 1;
    }
    MYSQL_CONN::mysql = new MYSQL();
    mysql_init(MYSQL_CONN::mysql);
    mysql_options(MYSQL_CONN::mysql, MYSQL_SET_CHARSET_NAME, "GB2312");
    if (mysql_real_connect(MYSQL_CONN::mysql, this->host, this->user, this->pswd, this->database, this->port, NULL, 0)) {
        return 1;
    }
    else {
        delete MYSQL_CONN::mysql; // Release allocated memory
        MYSQL_CONN::mysql = NULL;
        return 0;
    }
}

void MYSQL_CONN::close() {
    if (MYSQL_CONN::mysql) {
        mysql_close(MYSQL_CONN::mysql);
        delete MYSQL_CONN::mysql; // Release allocated memory
        MYSQL_CONN::mysql = NULL;
    }
}

MYSQL* MYSQL_CONN::getmysql() {
    return mysql;
}