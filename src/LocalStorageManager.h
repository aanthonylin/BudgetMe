/*	For CS3307
	By Brian Au
	2021-11-30
*/

#ifndef LSM_CLASS_H
#define LSM_CLASS_H
#include <string>
#include <vector>
#include <QString>
#include <QDate>

/*!	@author Brian Au
	@brief Interface for database models.
	
	Interface for accessing the application's database. 
	Provide the interface for data reteieval and storage methods.
*/
class LocalStorageManager {

	public:
	
		//!	@brief A virtual destructor.
		/*!	
			A virtual destructor for LocalStorageManager.
		*/
		virtual ~LocalStorageManager(){}
		
		//!	@brief A pure virtual method for verifying StatsCan data availability.
		/*!	
			A pure virtual method for checking if the data of the Statistic Canada is stored in the application's database.
			@return the availability of StatsCan data in boolean.
		*/
		virtual bool isStatsCanDataSaved() = 0;
		
		//!	@brief A pure virtual method for verifying user data availability.
		/*!	
			A pure virtual method for checking if the data of the current application user is stored in the application's database.
			@return the availability of user data in boolean.
		*/
		virtual bool isUserDataSaved() = 0;
		
		//!	@brief A pure virtual method for setting StatsCan data availability.
		/*!	
			A pure virtual method for setting if the data of the Statistic Canada is stored in the application's database.
			@param the availability of StatsCan data in boolean.
		*/
		virtual void setStatsCanDataSaved(bool) = 0;
		
		//!	@brief A pure virtual method for setting user data availability.
		/*!	
			A pure virtual method for setting if the data of the current application user is stored in the application's database.
			@param the availability of user data in boolean.
		*/
		virtual void setUserDataSaved(bool) = 0;
		
		//!	@brief A pure virtual method for setting the average annual income of Canadian from StatsCan.
		/*!	
			A pure virtual method for storing the average annual income of Canadian from StatsCan in the application database.
			@param the average annual income of Canadian in int.
		*/
		virtual void setAverageAnnualIncome(int) = 0;
		
		//!	@brief A pure virtual method for getting the average annual income of Canadian from StatsCan.
		/*!	
			A pure virtual method for getting the average annual income of Canadian from StatsCan in the application database.
			@return the average annual income of Canadian in int.
		*/
		virtual int getAverageAnnualIncome() = 0;
		
		//!	@brief A pure virtual method for setting the catogories from StatsCan.
		/*!	
			A pure virtual method for stroing the catogories from StatsCan in the application database.
			@param the list of categories in vector<QString>.
		*/
		virtual void setCategoryNames(std::vector<QString>) = 0;
		
		//!	@brief A pure virtual method for getting the catogories from StatsCan.
		/*!	
			A pure virtual method for getting the catogories from StatsCan in the application database.
			@return the list of categories in vector<QString>.
		*/
		virtual std::vector<QString> getCategoryNames() = 0;
		
		//!	@brief A pure virtual method for setting the average Canadian spending from StatsCan.
		/*!	
			A pure virtual method for stroing the average Canadian spending from StatsCan in the application database.
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param the list of spending in vector<int>.
		*/
		virtual void setAverageCanadianSpending(std::vector<int>) = 0;
		
		//!	@brief A pure virtual method for getting the average Canadian spending from StatsCan.
		/*!	
			A pure virtual method for getting the average Canadian spending from StatsCan in the application database.
			@return the list of spending in vector<int>.
		*/
		virtual std::vector<int> getAverageCanadianSpending() = 0;
		
		//!	@brief A pure virtual method for setting the average annual income of user.
		/*!	
			A pure virtual method for setting the average annual income of current user in the application database.
			@param the average annual income of user in int.
		*/
		virtual void setUserAnnualIncome(int) = 0;
		
		//!	@brief A pure virtual method for getting the average annual income of user.
		/*!	
			A pure virtual method for getting the average annual income of current user from the application database.
			@return the average annual income of user in int.
		*/
		virtual int getUserAnnualIncome() = 0;
		
		//!	@brief A pure virtual method for setting the estimated spending of user.
		/*!	
			A pure virtual method for setting the estimated spending of current user in the application database.
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param the list of spending in vector<int>.
		*/
		virtual void setEstimatedSpending(std::vector<int>) = 0;
		
		//!	@brief A pure virtual method for getting the estimated spending of user.
		/*!	
			A pure virtual method for getting the estimated spending of current user from the application database.
			@return the list of spending in vector<int>.
		*/
		virtual std::vector<int> getEstimatedSpending() = 0;
		
		//!	@brief A pure virtual method for setting the budget of user.
		/*!	
			A pure virtual method for setting the budget of current user in the application database.
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param the list of spending in vector<int>.
		*/
		virtual void setUserBudget(std::vector<int>) = 0;
		
		//!	@brief A pure virtual method for getting the budget of user.
		/*!	
			A pure virtual method for getting the budget of current user from the application database.
			@return the list of spending in vector<int>.
		*/
		virtual std::vector<int> getUserBudget() = 0;
		
		//!	@brief A pure virtual method for setting the smart budget.
		/*!	
			A pure virtual method for setting the smart budget feature of current user in the application database.
			@param smart budget status in boolean.
		*/
		virtual void setSmartBudget(bool) = 0;
		
		//!	@brief A pure virtual method for getting the smart budget.
		/*!	
			A pure virtual method for getting the smart budget feature of current user from the application database.
			@return smart budget status in boolean.
		*/
		virtual bool getSmartBudget() = 0;
		
		//!	@brief A pure virtual method for setting the overspending warnings.
		/*!	
			A pure virtual method for setting the overspending warnings of current user in the application database.
			@param overspending warnings status in boolean.
		*/
		virtual void setWarnings(bool) = 0;
		
		//!	@brief A pure virtual method for getting the overspending warnings.
		/*!	
			A pure virtual method for getting the overspending warnings of current user from the application database.
			@return overspending warnings status in boolean.
		*/
		virtual bool getWarnings() = 0;
		
		//!	@brief A pure virtual method for setting the data sharing feature.
		/*!	
			A pure virtual method for setting the data sharing feature of current user in the application database.
			@param data sharing feature status in boolean.
		*/
		virtual void setDataSharing(bool) = 0;
		
		//!	@brief A pure virtual method for getting the data sharing feature.
		/*!	
			A pure virtual method for getting the data sharing feature of current user from the application database.
			@return data sharing feature status in boolean.
		*/
		virtual bool getDataSharing() = 0;
		
		//!	@brief A pure virtual method for setting the preference feature.
		/*!	
			A pure virtual method for setting the preference feature of current user in the application database.
			@param preference feature status in boolean.
		*/
		virtual void setPreferencesSaved(bool) = 0;
		
		//!	@brief A pure virtual method for getting the preference feature.
		/*!	
			A pure virtual method for getting the preference feature of current user from the application database.
			@return preference feature status in boolean.
		*/
		virtual bool arePreferencesSaved() = 0;
		
		//! A struct for grouping the transaction information of the current user.
		struct transactionInfo{
            QString name;
			int cost;
			QDate date;
			int catid;
        };
		
		//!	@brief A pure virtual method for saving a transaction.
		/*!	
			A pure virtual method for saving a transaction of current user to the application database.
			@param a transaction information.
		*/
		virtual void saveTransaction(transactionInfo) = 0;
		
		//!	@brief A pure virtual method for getting transactions.
		/*!	
			A pure virtual method for getting the transactions of current user between 2 specified date in the parameter from the application database.
			@param lower bound date.
			@param upper bound date.
			@return list of transaction.
		*/
		virtual std::vector<transactionInfo> getTransactions(QDate, QDate) = 0;
		
		//!	@brief A pure virtual method for getting the actual spending.
		/*!	
			A pure virtual method for getting the actual spending per categories derived fromn transaction history of current user 
			between 2 specified date in the parameter from the application database. 
			The list of spending in the parameter matches the return of getCategoryNames() accordingly to its index.
			@param lower bound date.
			@param upper bound date.
			@return a list of total spending per categories.
		*/
		virtual std::vector<int> getActualSpending(QDate, QDate) = 0;
		
		//!	@brief A pure virtual method for getting the daily spending.
		/*!	
			A pure virtual method for getting the total daily spending derived fromn transaction history of current user 
			between 2 specified date in the parameter from the application database. 
			@param lower bound date.
			@param upper bound date.
			@return a list of spending per day.
		*/
		virtual std::vector<int> getDailySpending(QDate, QDate) = 0;
		
		//!	@brief A pure virtual method for clearing the application database.
		/*!	
			A pure virtual method for clearing the application completely.
		*/
		virtual void clearAllData() = 0;
		
	
};

#endif