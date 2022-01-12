#define incomeVector "conf/IncomeVector.txt"
#define expenditureFile "conf/SpendingVectors.txt"
#define dataLink "https://www150.statcan.gc.ca/t1/wds/rest/getDataFromVectorsAndLatestNPeriods"
#define metadataLink "https://www150.statcan.gc.ca/t1/wds/rest/getSeriesInfoFromVector"

#ifndef SCDATAMANAGER
#define SCDATAMANAGER

#include "StatsCanadaManager.h"
#include <vector>
#include <fstream>
#include <QString>

/**
* @brief An object that will retrieve data specifically for BudgetMe
*
* It is an object with a specialized purpose. It retrieves data and meta data 
* from Statistics Canada that will be required for BudgetMe. The data returned
* will only work with BudgetMe or any application that requires the same data.
* If a more general object is needed, use the StatsCanadaManagerObject. 
*
* @author Anthony Lin 
*/
class BudgetMeDataManager
{
	private:
		/**
		* @brief An object that can make request to Statistics Canada
		* 
		* It is an object that makes request to Statsistics Canada and allows for data to be 
		* retrieved for BudgetMe's needs
		*/
		StatsCanadaManager request;
	
		/**
		* @brief Sets the parameters of the StatsCanadaManager to be able to get data
		*
		* It sends the sets the URL of the StatsCanadaManager allowing it to make request to
		* retrieve the data from the source. It gets the source location from a #define directive
		* in the 'BudgetMeDataManager.h' file
		*/
		void setDataDefaults();
		
		/**
		* @brief Sets the parameters of the StatsCanadaManager to be able to get metadata
		*
		* It sends the sets the URL of the StatsCanadaManager allowing it to make request to
		* retrieve the metadata from the source. It gets the source location from a #define directive
		* in the 'BudgetMeDataManager.h' file
		*/
		void setMetadataDefaults();
	public:
		/**
		* @brief Retrieves parsed income data
		*
		* It calls the StatsCanadaManager with the desired vector and it returns the
		* value that the API returned.
		*
		* @return An integer with the average income as the value
		*/
		int getAverageIncome();
		
		/**
		* @brief Retrieves parsed spending data
		*
		* It calls the StatsCanadaManager with the desired vectors and it returns the
		* associated value that the API returned. Order of the returned vector matches
		* the order of which the vectors are listed in the file
		*
		* @return An vector of integers storing the associated values
		*/
		std::vector<int> getAverageSpending();
		
		/**
		* @brief Retrieves parsed spending metadata
		*
		* It calls the StatsCanadaManager with the desired vectors and it returns the
		* associated metadata that the API returned. Order of the returned vector matches
		* the order of which the vectors are listed in the file
		*
		* @return An vector of QString storing the associated names
		*/
		std::vector<QString> getCategoryNames();
		
		/**
		* @brief Retrieves shorter names of the vector categories
		*
		* It reads from the vector file and reads the shorter names. It then converts
		* the shorter names into a QString and stores them in a vector. The order in 
		* which the shorter names are stored matches the order of the file
		*
		* @return An vector of QStrings storing the associated values
		*/
		std::vector<QString> getShortNames();
};

#endif
