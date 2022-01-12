/*	For CS3307
	By Brian Au
	2021-11-30
*/
#ifndef SQL_CLASS_H
#define SQL_CLASS_H

#include <mysql/mysql.h>
#include "LocalStorageManager.h"
#include "LoginLocalModel.h"

/*!	@author Brian Au.
	@brief Database model for the application.
	
	Provides access to the application's database, and data retrieval and storage methods. 
*/
class SQLManager: public LocalStorageManager, public LoginLocalModel {

	private:

		//! A private struct for grouping the database information required to access MySQL for the application.
		struct connectionID{
            const char *server, *user, *password, *database;
        };
		
		//! a private variable for application to MySQL connection
		MYSQL *conn;
		
		//!	@brief A private method for setting up connection between application to MySQL.
		/*!	
			A private method for setting up connection between application to MySQL.
			@param the application database information.
			@return the application to MySQL connection.
		*/
        MYSQL* mysqlConnectionSetup(struct connectionID mysql_details);
		
		//!	@brief A private method for getting the result of a SQL Query.
		/*!	
			A private method for getting the result as a database table of a SQL Query specified in the parameter.
			@param the application to MySQL connection.
			@param a SQL query.
			@return the Query result in a table.
		*/
        MYSQL_RES* mysqlPerformQuery(MYSQL *connection, const char *sql_query);
		
		//!	@brief A private method for verifying the username.
		/*!	
			A private method for verifying if a username is in the database.
			@param a username.
			@return the availability of the username.
		*/
		bool getUsrname(string name);
		
		//! a private variable for verifying if a user is loggin in and began a session
		bool session;
		
		//! a private variable for the user's id of the current session.
		string userkey;
		
		//! a private variable for the Statistic Canada id.
		string statcanKey;

	public:
	
		//!	@brief A constructor.
		/*!	
			A constructor for SQLManager.
		*/
		SQLManager();
		
		//!	@brief A destructor.
		/*!	
			A destructor for SQLManager.
		*/
		~SQLManager();

		// LoginLocalModel.h
		
		//!	@brief A public method for adding a user ID to database.
		/*!	
			A public method for storing a new user ID in the application's database.
			@param username
			@param password
			@return the status of the registration.
		*/
		bool registerLocal(string, string);
		
		//!	@brief A public method for checking a user ID in database.
		/*!	
			A public method for checking if a user ID exists in the application's database.
			@param username
			@param password
			@return the verification result.
		*/
		bool loginLocal(string, string);
		
		//!	@brief A public method for checking if a user has logged in.
		/*!	
			A public method for checking a user has logged in to the application and that a session has begun.
			@return session status.
		*/
		bool hasSession();
		
		//!	@brief A public method for getting the userid of the current session.
		/*!	
			A public method for getting the userid of the current session
			@return username.
		*/
		string getUser();
		
		//!	@brief A public method for checking if the session is in guess mode.
		/*!	
			A public method for checking the current session is in guess mode.
			@return session status.
		*/
		void guestSession();
		
		// LoginStorageManager.h
		
		//!	@brief A public method for verifying StatsCan data availability.
		/*!	
			A public method for checking if the data of the Statistic Canada is stored in the application's database.
			@return the availability of StatsCan data in boolean.
		*/
		bool isStatsCanDataSaved();
		
		//!	@brief A public method for verifying user data availability.
		/*!	
			A public method for checking if the data of the current application user is stored in the application's database.
			@return the availability of user data in boolean.
		*/
		bool isUserDataSaved();
		
		//!	@brief A public method for setting StatsCan data availability.
		/*!	
			A public for setting if the data of the Statistic Canada is stored in the application's database.
			@param the availability of StatsCan data in boolean.
		*/
		void setStatsCanDataSaved(bool);
		
		//!	@brief A public method for setting user data availability.
		/*!	
			A public method for setting if the data of the current application user is stored in the application's database.
			@param the availability of user data in boolean.
		*/
		void setUserDataSaved(bool);
		
		//!	@brief A public method for setting the average annual income of Canadian from StatsCan.
		/*!	
			A public method for storing the average annual income of Canadian from StatsCan in the application database.
			@param the average annual income of Canadian in int.
		*/
		void setAverageAnnualIncome(int);
		
		//!	@brief A public method for getting the average annual income of Canadian from StatsCan.
		/*!	
			A public method for getting the average annual income of Canadian from StatsCan in the application database.
			@return the average annual income of Canadian in int.
		*/
		int getAverageAnnualIncome();
		
		//!	@brief A public method for setting the catogories from StatsCan.
		/*!	
			A public method for stroing the catogories from StatsCan in the application database.
			@param the list of categories in vector<QString>.
		*/
		void setCategoryNames(vector<QString>);
		
		//!	@brief A public method for getting the catogories from StatsCan.
		/*!	
			A public method for getting the catogories from StatsCan in the application database.
			@return the list of categories in vector<QString>.
		*/
		vector<QString> getCategoryNames();
		
		//!	@brief A public method for setting the average Canadian spending from StatsCan.
		/*!	
			A public method for stroing the average Canadian spending from StatsCan in the application database.
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param the list of spending in vector<int>.
		*/
		void setAverageCanadianSpending(vector<int>);
		
		//!	@brief A public method for getting the average Canadian spending from StatsCan.
		/*!	
			A public method for getting the average Canadian spending from StatsCan in the application database.
			@return the list of spending in vector<int>.
		*/
		vector<int> getAverageCanadianSpending();
		
		//!	@brief A public method for setting the average annual income of user.
		/*!	
			A public method for setting the average annual income of current user in the application database.
			@param the average annual income of user in int.
		*/
		void setUserAnnualIncome(int);
		
		//!	@brief A public method for getting the average annual income of user.
		/*!	
			A public method for getting the average annual income of current user from the application database.
			@return the average annual income of user in int.
		*/
		int getUserAnnualIncome();
		
		//!	@brief A public method for setting the estimated spending of user.
		/*!	
			A public method for setting the estimated spending of current user in the application database.
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param the list of spending in vector<int>.
		*/
		void setEstimatedSpending(vector<int>);
		
		//!	@brief A public method for getting the estimated spending of user.
		/*!	
			A public method for getting the estimated spending of current user from the application database.
			@return the list of spending in vector<int>.
		*/
		vector<int> getEstimatedSpending();
		
		//!	@brief A public method for setting the budget of user.
		/*!	
			A public method for setting the budget of current user in the application database.
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param the list of spending in vector<int>.
		*/
		void setUserBudget(vector<int>);
		
		//!	@brief A public method for getting the budget of user.
		/*!	
			A public method for getting the budget of current user from the application database.
			@return the list of spending in vector<int>.
		*/
		vector<int> getUserBudget();
		
		//!	@brief A public method for setting the smart budget.
		/*!	
			A public method for setting the smart budget feature of current user in the application database.
			@param smart budget status in boolean.
		*/
		void setSmartBudget(bool);
		
		//!	@brief A public method for getting the smart budget.
		/*!	
			A public method for getting the smart budget feature of current user from the application database.
			@return smart budget status in boolean.
		*/
		bool getSmartBudget();
		
		//!	@brief A public method for setting the overspending warnings.
		/*!	
			A public method for setting the overspending warnings of current user in the application database.
			@param overspending warnings status in boolean.
		*/
		void setWarnings(bool);
		
		//!	@brief A public method for getting the overspending warnings.
		/*!	
			A public method for getting the overspending warnings of current user from the application database.
			@return overspending warnings status in boolean.
		*/
		bool getWarnings();
		
		//!	@brief A public method for setting the data sharing feature.
		/*!	
			A public method for setting the data sharing feature of current user in the application database.
			@param data sharing feature status in boolean.
		*/
		void setDataSharing(bool);
		
		//!	@brief A public method for getting the data sharing feature.
		/*!	
			A public method for getting the data sharing feature of current user from the application database.
			@return data sharing feature status in boolean.
		*/
		bool getDataSharing();
		
		//!	@brief A public method for setting the preference feature.
		/*!	
			A public method for setting the preference feature of current user in the application database.
			@param preference feature status in boolean.
		*/
		void setPreferencesSaved(bool);
		
		//!	@brief A public method for getting the preference feature.
		/*!	
			A public method for getting the preference feature of current user from the application database.
			@return preference feature status in boolean.
		*/
		bool arePreferencesSaved();
		
		//!	@brief A public method for saving a transaction.
		/*!	
			A public method for saving a transaction of current user to the application database.
			@param a transaction information.
		*/
		void saveTransaction(LocalStorageManager::transactionInfo);
		
		//!	@brief A public method for getting transactions.
		/*!	
			A public method for getting the transactions of current user between 2 specified date in the parameter from the application database.
			@param lower bound date.
			@param upper bound date.
			@return list of transaction.
		*/
		vector<LocalStorageManager::transactionInfo> getTransactions(QDate, QDate);
		
		//!	@brief A public method for getting the actual spending.
		/*!	
			A public method for getting the actual spending per categories derived fromn transaction history of current user 
			between 2 specified date in the parameter from the application database. 
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param lower bound date.
			@param upper bound date.
			@return a list of total spending per categories.
		*/
		vector<int> getActualSpending(QDate, QDate);
		
		//!	@brief A public method for getting the daily spending.
		/*!	
			A public method for getting the total daily spending derived fromn transaction history of current user 
			between 2 specified date in the parameter from the application database. 
			@param lower bound date.
			@param upper bound date.
			@return a list of spending per day.
		*/
		vector<int> getDailySpending(QDate, QDate);
		
		//!	@brief A public method for clearing the application database.
		/*!	
			A public method for clearing the application completely.
		*/
		void clearAllData();
		
};
#endif
