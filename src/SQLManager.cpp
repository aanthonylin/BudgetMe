/*	For CS3307
	By Brian Au
	2021-11-30
*/
#include <iostream>
#include "SQLManager.h"

//contrusctor
SQLManager::SQLManager(){

	struct connectionID mysqlD;
    mysqlD.server = "localhost";	//server location
    mysqlD.user = "budgetme";	//mysql username
    mysqlD.password = "mysql_BUDGETME_123";	//mysql password
    mysqlD.database = "budgetme_database";	//program database name
	
	session = false;	//set default session as false as login proccess not complete
	userkey = "";
	statcanKey = "STATSCAN_database_key";

    // connect to the mysql database and create a connection ID
    conn = mysqlConnectionSetup(mysqlD);

}

//destructor
SQLManager::~SQLManager(){
	//close mysql connection
	mysql_close(conn);

}

//initialize mysql connection
MYSQL* SQLManager::mysqlConnectionSetup(struct connectionID mysql_details){
	//mysql instance
	MYSQL *connection = mysql_init(NULL);

	//connect to MySQL
	//print error if user forgot to start the MySQL server.
	if(!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, NULL, 0, NULL, 0)){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
		std::cerr << "***********************************************************************************************" << std::endl;
        std::cerr << "**** REMEMBER TO START MySQL SERVER! Enter 'sudo service mysql start' in the command line. ****" << std::endl;
		std::cerr << "**** REMEMBER TO START MySQL SERVER! Enter 'sudo service mysql start' in the command line. ****" << std::endl;
		std::cerr << "**** REMEMBER TO START MySQL SERVER! Enter 'sudo service mysql start' in the command line. ****" << std::endl;
		std::cerr << "***********************************************************************************************" << std::endl;
        exit(1);
    }

	//create the program database if it does not exist
	//modular query for creating database with specified name in Constructor
	std::string dbName = mysql_details.database;
	std::string q = "CREATE DATABASE IF NOT EXISTS " + dbName + ";";
	const char* qChar = q.c_str();
	if(mysql_query(connection, qChar)){
		std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
		exit(1);
	}

	//connect to database
	if(mysql_select_db(connection, mysql_details.database)){
		std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
		exit(1);
	}
	
	//create userid table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS userid_table (usrname varchar(15) NOT NULL,password varchar(30) NOT NULL,PRIMARY KEY (usrname));")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//create user's setting table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS user_config_table (usrname varchar(15) NOT NULL,smart BOOLEAN NOT NULL,sharing BOOLEAN NOT NULL,warning BOOLEAN NOT NULL,saved BOOLEAN NOT NULL,preferences BOOLEAN NOT NULL);")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//create app setting table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS app_config_table (database_id varchar(30) NOT NULL, cache BOOLEAN, PRIMARY KEY (database_id));")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//initialize app setting table
	q = "INSERT IGNORE INTO app_config_table (database_id, cache) VALUES ('" + statcanKey + "', false);";
	qChar = q.c_str();
	if(mysql_query(connection, qChar)){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//create StatsCan table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS statscan_table (catid int NOT NULL,catname varchar(100) NOT NULL,spending int NOT NULL,PRIMARY KEY (catid));")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//create user data table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS user_data_table (usrname varchar(15) NOT NULL, catid int NOT NULL, spending int NOT NULL, budget int NOT NULL);")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//create annual income table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS annual_income_table (usrname varchar(30) NOT NULL, income int NOT NULL, PRIMARY KEY (usrname));")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//initialize statscan income
	q = "INSERT IGNORE INTO annual_income_table (usrname, income) VALUES ('" + statcanKey + "', 0);";
	qChar = q.c_str();
	if(mysql_query(connection, qChar)){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }
	
	//create transaction table if not exist
	if(mysql_query(connection, "CREATE TABLE IF NOT EXISTS transaction_table (usrname varchar(15) NOT NULL, descript varchar(50) NOT NULL, date DATE NOT NULL, spending INT NOT NULL, catid INT NOT NULL);")){
        std::cerr << "Connection Error: " << mysql_error(connection) << std::endl;
        exit(1);
    }

	return connection;
}

//return the query result as a set
MYSQL_RES* SQLManager::mysqlPerformQuery(MYSQL *connection, const char *sql_query){

        if(mysql_query(connection, sql_query)){
                std::cerr << "MySQL Query Error from mysqlPerformQuery(): " << mysql_error(connection) << std::endl;
                exit(1);
        }

        return mysql_use_result(connection);
}

bool SQLManager::getUsrname(string name){

	MYSQL_RES *usrnameRes;     // the results
    MYSQL_ROW tblRow;      // the results rows

	//perform SQL query to get username from the database
    usrnameRes = mysqlPerformQuery(conn, "SELECT usrname FROM userid_table;");
	
	// Will return a table for the above query, check if the table is empty(i.e empty = username not in database)
	while ((tblRow = mysql_fetch_row(usrnameRes)) != NULL){
		
		//return true if username is in database
		if(tblRow[0] == name){
			mysql_free_result(usrnameRes);
			return true;
		}
    }

	mysql_free_result(usrnameRes);
	return false;

}

//add user id to database, return true if successful, false if usrname already exists.
bool SQLManager::registerLocal(string name, string passcode){

	//username already exist
	if(getUsrname(name)){
		return false;
	}

	//adding user id
	std::string addUsrQ = "INSERT INTO userid_table (usrname, password) VALUES ('" + name + "', '" + passcode + "');";
    const char* addUsrQChar = addUsrQ.c_str();
	if(mysql_query(conn, addUsrQChar)){
        std::cerr << "MySQL Query Error: " << mysql_error(conn) << std::endl;
        exit(1);
    }

	//initialize user setting (all false by default)
	addUsrQ = "INSERT INTO user_config_table (usrname, smart, sharing, warning, saved, preferences) VALUES ('" + name + "', false, false, false, false, false);";
    addUsrQChar = addUsrQ.c_str();
	if(mysql_query(conn, addUsrQChar)){
        std::cerr << "MySQL Query Error: " << mysql_error(conn) << std::endl;
        exit(1);
    }
	
	//initialize user income as 0 by default
	addUsrQ = "INSERT INTO annual_income_table (usrname, income) VALUES ('" + name + "', 0);";
	addUsrQChar = addUsrQ.c_str();
	if(mysql_query(conn, addUsrQChar)){
        std::cerr << "MySQL Query Error: " << mysql_error(conn) << std::endl;
        exit(1);
    }

	//set session as true, and the user in the session as the username used for registration
	userkey = name;
	session = true;
	return true;

}

//return true if user id in database, false if otherwise
bool SQLManager::loginLocal(string name, string passcode){

	MYSQL_RES *usridRes;     // the results
    MYSQL_ROW tblRow;      // the results rows

	//perform SQL query to get the list of usernames and passwords from the database
    usridRes = mysqlPerformQuery(conn, "SELECT usrname, password FROM userid_table;");
	
	//if name and passcode match he userid in the database return true
    while ((tblRow = mysql_fetch_row(usridRes)) != NULL){
        if(tblRow[0] == name && tblRow[1] == passcode){
            mysql_free_result(usridRes);
			userkey = name;
			session = true;
            return true;
        }
    }

    mysql_free_result(usridRes);
	return false;
}

void SQLManager::guestSession() {
	session = true;
}

bool SQLManager::hasSession() {
	return session;
}

string SQLManager::getUser(){
	return userkey;
}

// checking if the data of the Statistic Canada is stored in the application's database
bool SQLManager::isStatsCanDataSaved(){
	
	bool result;
	MYSQL_ROW resultAsArray;
	
	//perform SQL Query
	std::string q = "SELECT cache FROM app_config_table WHERE database_id = '" + statcanKey + "';";
	const char* qChar = q.c_str();
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}

bool SQLManager::isUserDataSaved(){
	
	bool result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT saved FROM user_config_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}

void SQLManager::setStatsCanDataSaved(bool saved){
	
	string boolean = "false";
	if(saved == true){
		boolean = "true";
	}
	
	//perform SQL Query
	std::string q = "UPDATE app_config_table SET cache = " + boolean + " WHERE database_id = '" + statcanKey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

void SQLManager::setUserDataSaved(bool saved){
	
	string boolean = "false";
	if(saved == true){
		boolean = "true";
	}
	
	//perform SQL Query
	std::string q = "UPDATE user_config_table SET saved = " + boolean + " WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}
		
void SQLManager::setAverageAnnualIncome(int income){
	
	string annualIncome = to_string(income);
	std::string q = "UPDATE annual_income_table SET income = " + annualIncome + " WHERE usrname = '" + statcanKey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

int SQLManager::getAverageAnnualIncome(){
	
	int result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT income FROM annual_income_table WHERE usrname = '" + statcanKey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
	
void SQLManager::setCategoryNames(vector<QString> categories){
	
	//check if statscan table is empty
	int empty = 0;
	std::string q = "SELECT EXISTS(SELECT 1 FROM statscan_table);";
	const char* qChar = q.c_str();
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	MYSQL_ROW resultAsArray = mysql_fetch_row(resultRaw);
	empty = atoi(resultAsArray[0]);
	mysql_free_result(resultRaw);
	
	int index = 0;
  
    for (auto& cat : categories) {
  
		// if the table is empty use insert, else use update
		if(empty == 0){
			q = "INSERT IGNORE INTO statscan_table (catid, catname, spending) VALUES (" + to_string(index) + " ,'" + cat.toStdString() + "', 0);";
		}
		else{
			q = "UPDATE statscan_table SET catname = '" + cat.toStdString() + "' WHERE catid = " + to_string(index) + ";";
		}
		qChar = q.c_str();
		
		if(mysql_query(conn, qChar)){
			std::cerr << "SetCategoryNames error: " << mysql_error(conn) << std::endl;
		}
		
		index++;
		
    }
	
}

vector<QString> SQLManager::getCategoryNames(){
	
	vector<QString> result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT catname FROM statscan_table;";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	while ((resultAsArray = mysql_fetch_row(resultRaw)) != NULL){
        result.push_back(QString::fromStdString(std::string(resultAsArray[0])));
    }
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
	
void SQLManager::setAverageCanadianSpending(vector<int> spendings){
	
	//check if statscan table is empty
	int empty = 0;
	std::string q = "SELECT EXISTS(SELECT 1 FROM statscan_table);";
	const char* qChar = q.c_str();
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	MYSQL_ROW resultAsArray = mysql_fetch_row(resultRaw);
	empty = atoi(resultAsArray[0]);
	mysql_free_result(resultRaw);
	
	int index = 0;
  
    for (auto& spend : spendings) {
		
		// if the table is empty use insert, else use update
		if(empty == 0){
			q = "INSERT IGNORE INTO statscan_table (catid, catname, spending) VALUES (" + to_string(index) + " ,'null', " + to_string(spend) + ");";
		}
		else{
			q = "UPDATE statscan_table SET spending = " + to_string(spend) + " WHERE catid = " + to_string(index) + ";";
		}
		qChar = q.c_str();
		
		if(mysql_query(conn, qChar)){
			std::cerr << "SetAverageCanadianSpending error: " << mysql_error(conn) << std::endl;
		}
		
		index++;
		
    }
	
}

vector<int> SQLManager::getAverageCanadianSpending(){
	
	vector<int> result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT spending FROM statscan_table;";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	while ((resultAsArray = mysql_fetch_row(resultRaw)) != NULL){
        result.push_back(atoi(resultAsArray[0]));
    }
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
		
void SQLManager::setUserAnnualIncome(int income){
	
	//perform SQL Query
	string annualIncome = to_string(income);
	std::string q = "UPDATE annual_income_table SET income = " + annualIncome + " WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

int SQLManager::getUserAnnualIncome(){
	
	int result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT income FROM annual_income_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
	
void SQLManager::setEstimatedSpending(vector<int> spendings){
	
	//check if statscan table is empty
	int empty = 0;
	std::string q = "SELECT EXISTS(SELECT 1 FROM user_data_table WHERE usrname = '" + userkey + "');";
	const char* qChar = q.c_str();
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	MYSQL_ROW resultAsArray = mysql_fetch_row(resultRaw);
	empty = atoi(resultAsArray[0]);
	mysql_free_result(resultRaw);
	
	int index = 0;
  
    for (auto& spend : spendings) {
		
		// if the table is empty use insert, else use update
		if(empty == 0){
			q = "INSERT INTO user_data_table (usrname, catid, spending, budget) VALUES ('" + userkey + "'," + to_string(index) + "," + to_string(spend) + ", 0);";
		}
		else{
			q = "UPDATE user_data_table SET spending = " + to_string(spend) + " WHERE catid = " + to_string(index) + " AND usrname = '" + userkey + "';";
		}
		qChar = q.c_str();
		
		if(mysql_query(conn, qChar)){
			std::cerr << "SetEstimatedSpending error: " << mysql_error(conn) << std::endl;
		}
		
		index++;
		
    }
	
}

vector<int> SQLManager::getEstimatedSpending(){
	
	vector<int> result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT spending FROM user_data_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	while ((resultAsArray = mysql_fetch_row(resultRaw)) != NULL){
        result.push_back(atoi(resultAsArray[0]));
    }
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
		
void SQLManager::setUserBudget(vector<int> budget){
	
	//check if statscan table is empty
	int empty = 0;
	std::string q = "SELECT EXISTS(SELECT 1 FROM user_data_table WHERE usrname = '" + userkey + "');";
	const char* qChar = q.c_str();
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	MYSQL_ROW resultAsArray = mysql_fetch_row(resultRaw);
	empty = atoi(resultAsArray[0]);
	mysql_free_result(resultRaw);
	
	int index = 0;
  
    for (auto& money : budget) {
		
		// if the table is empty use insert, else use update
		if(empty == 0){
			q = "INSERT INTO user_data_table (usrname, catid, spending, budget) VALUES ('" + userkey + "'," + to_string(index) + ", 0, " + to_string(money) + ");";
		}
		else{
			q = "UPDATE user_data_table SET budget = " + to_string(money) + " WHERE catid = " + to_string(index) + " AND usrname = '" + userkey + "';";
		}
		qChar = q.c_str();
		
		if(mysql_query(conn, qChar)){
			std::cerr << "SetEstimatedSpending error: " << mysql_error(conn) << std::endl;
		}
		
		index++;
		
    }
	
}

vector<int> SQLManager::getUserBudget(){
	
	vector<int> result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT budget FROM user_data_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	while ((resultAsArray = mysql_fetch_row(resultRaw)) != NULL){
        result.push_back(atoi(resultAsArray[0]));
    }
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
		
void SQLManager::setSmartBudget(bool smart){
	
	string boolean = "false";
	if(smart == true){
		boolean = "true";
	}
	
	//perform SQL Query
	std::string q = "UPDATE user_config_table SET smart = " + boolean + " WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

bool SQLManager::getSmartBudget(){
	
	bool result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT smart FROM user_config_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
		
void SQLManager::setWarnings(bool warn){
	
	string boolean = "false";
	if(warn == true){
		boolean = "true";
	}
	
	//perform SQL Query
	std::string q = "UPDATE user_config_table SET warning = " + boolean + " WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

bool SQLManager::getWarnings(){
	
	bool result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT warning FROM user_config_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}
		
void SQLManager::setDataSharing(bool share){
	
	string boolean = "false";
	if(share == true){
		boolean = "true";
	}
	
	//perform SQL Query
	std::string q = "UPDATE user_config_table SET sharing = " + boolean + " WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

bool SQLManager::getDataSharing(){
	
	bool result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT sharing FROM user_config_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
	
}

void SQLManager::setPreferencesSaved(bool pref){
	
	//convert bool to string for SQL query
	string boolean = "false";
	if(pref == true){
		boolean = "true";
	}
	
	//perform SQL Query
	std::string q = "UPDATE user_config_table SET preferences = " + boolean + " WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

bool SQLManager::arePreferencesSaved(){
	
	bool result;
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT preferences FROM user_config_table WHERE usrname = '" + userkey + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	resultAsArray = mysql_fetch_row(resultRaw);
	result = atoi(resultAsArray[0]);
	
	mysql_free_result(resultRaw);
	
	return result;
}

void SQLManager::saveTransaction(LocalStorageManager::transactionInfo info){
	
	std::string q = "INSERT INTO transaction_table (usrname, descript, date, spending, catid) VALUES ('" + userkey + "','" + info.name.toStdString() + "', '" + info.date.toString("yyyy-MM-dd").toStdString() + "', " + to_string(info.cost) + ", " + to_string(info.catid) + ");";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	if(mysql_query(conn, qChar)){
        std::cerr << "Update error: " << mysql_error(conn) << std::endl;
    }
	
}

vector<LocalStorageManager::transactionInfo> SQLManager::getTransactions(QDate lower, QDate upper){
	
	transactionInfo result;
	vector<transactionInfo> resultVec;
	
	MYSQL_ROW resultAsArray;
	std::string q = "SELECT * FROM transaction_table WHERE usrname = '" + userkey + "' AND date BETWEEN '" + lower.toString("yyyy-MM-dd").toStdString() + "' AND '" + upper.toString("yyyy-MM-dd").toStdString() + "';";
	const char* qChar = q.c_str();
	
	//perform SQL Query
	MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
	
	while ((resultAsArray = mysql_fetch_row(resultRaw)) != NULL){
		result.name = QString::fromStdString(std::string(resultAsArray[1]));
		result.date = QDate::fromString(QString::fromStdString(std::string(resultAsArray[2])), "yyyy-mm-dd");
		result.cost = atoi(resultAsArray[3]);
		result.catid = atoi(resultAsArray[4]);
        resultVec.push_back(result);
    }
	
	mysql_free_result(resultRaw);
	
	return resultVec;
	
}

vector<int> SQLManager::getActualSpending(QDate lower, QDate upper){
	
	vector<int> result;
	std::string q;
	const char* qChar;
	MYSQL_ROW resultAsArray;
	int size = static_cast<int> (getCategoryNames().size());
	int index = 0;
	
	//perform SQL Query for all categories
	while(index < size){
		
		q = "SELECT SUM(spending) FROM transaction_table WHERE usrname = '" + userkey + "' AND catid = " + to_string(index) + " AND date BETWEEN '" + lower.toString("yyyy-MM-dd").toStdString() + "' AND '" + upper.toString("yyyy-MM-dd").toStdString() + "';";
		qChar = q.c_str();
		MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
		
		resultAsArray = mysql_fetch_row(resultRaw);
		if(resultAsArray[0] != NULL){
			result.push_back(atoi(resultAsArray[0]));
		}
		else{
			result.push_back(0);
		}
		
		index ++;
		mysql_free_result(resultRaw);
		
	}
	
	return result;
}

void SQLManager::clearAllData(){
	
	//perform SQL Query delete database
	if(mysql_query(conn, "DROP DATABASE budgetme_database;")){
        std::cerr << "Connection Error: " << mysql_error(conn) << std::endl;
    }
	else{
		exit(0);
	}
	
}

vector<int> SQLManager::getDailySpending(QDate lower, QDate upper){
	
	vector<int> result;
	std::string q;
	const char* qChar;
	MYSQL_ROW resultAsArray;
	
	//perform SQL Query for all days between lower and upper
	while(lower <= upper){
		
		q = "SELECT SUM(spending) FROM transaction_table WHERE usrname = '" + userkey + "' AND date = '" + lower.toString("yyyy-MM-dd").toStdString() + "';";
		qChar = q.c_str();
		MYSQL_RES *resultRaw = mysqlPerformQuery(conn, qChar);
		
		resultAsArray = mysql_fetch_row(resultRaw);
		if(resultAsArray[0] != NULL){
			result.push_back(atoi(resultAsArray[0]));
		}
		else{
			result.push_back(0);
		}
		
		lower = lower.addDays(1);
		mysql_free_result(resultRaw);
		
	}
	
	return result;
	
}
		
		

	
