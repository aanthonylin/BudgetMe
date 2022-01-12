// Author: Anthony Lin
// Date: November 18, 2021
// Purpose: To add functionaliy to the data retrieved from StatsCanada
#include "BudgetMeDataManager.h"

/**
* @brief Sets the parameters of the StatsCanadaManager to be able to get data
*
* It sends the sets the URL of the StatsCanadaManager allowing it to make request to
* retrieve the data from the source. It gets the source location from a #define directive
* in the 'BudgetMeDataManager.h' file
*/
void BudgetMeDataManager::setDataDefaults()
{
	request.setDataURL(dataLink);
}


/**
* @brief Sets the parameters of the StatsCanadaManager to be able to get metadata
*
* It sends the sets the URL of the StatsCanadaManager allowing it to make request to
* retrieve the metadata from the source. It gets the source location from a #define directive
* in the 'BudgetMeDataManager.h' file
*/
void BudgetMeDataManager::setMetadataDefaults()
{
	request.setMetadataURL(metadataLink);
}

/**
* @brief Retrieves parsed income data
*
* It calls the StatsCanadaManager with the desired vector and it returns the
* value that the API returned.
*
* @return An integer with the average income as the value
*/
int BudgetMeDataManager::getAverageIncome()
{
	BudgetMeDataManager::setDataDefaults();
	std::vector<int> result = request.getData(incomeVector);
	return result.at(0);
}

/**
* @brief Retrieves parsed spending data
*
* It calls the StatsCanadaManager with the desired vectors and it returns the
* associated value that the API returned. Order of the returned vector matches
* the order of which the vectors are listed in the file
*
* @return An vector of integers storing the associated values
*/
std::vector<int> BudgetMeDataManager::getAverageSpending()
{
	BudgetMeDataManager::setDataDefaults();
	return request.getData(expenditureFile);
}

/**
* @brief Retrieves parsed spending metadata
*
* It calls the StatsCanadaManager with the desired vectors and it returns the
* associated metadata that the API returned. Order of the returned vector matches
* the order of which the vectors are listed in the file
*
* @return An vector of QString storing the associated names
*/
std::vector<QString> BudgetMeDataManager::getCategoryNames()
{
	BudgetMeDataManager::setMetadataDefaults();
	return request.getMetadata(expenditureFile);
}

/**
* @brief Retrieves shorter names of the vector categories
*
* It reads from the vector file and reads the shorter names. It then converts
* the shorter names into a QString and stores them in a vector. The order in 
* which the shorter names are stored matches the order of the file
*
* @return An vector of QStrings storing the associated values
*/
std::vector<QString> BudgetMeDataManager::getShortNames()
{
	std::ifstream file;
	std::string shortName;
	std::string character;
	std::string line;
	std::vector<QString> nameVector;
	int i;
	bool afterVector; // Keep track if which part of the line it is reading from
	
	file.open(expenditureFile);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			afterVector = false;
			i = 0;
			shortName = "";
			while (line.at(i) != ';' || !afterVector) // While it is not done reading everything upto the second element
			{
				if (afterVector) // If it is on the second element
				{
					shortName.push_back(line.at(i));
				}
				else
				{
					if (line.at(i) == ';')
					{
						afterVector = true;
					}
				}
				i = i + 1; 
			}
			nameVector.push_back(QString::fromStdString(shortName)); // Add a command to the POST body
		}
		file.close();
		return nameVector;
	}
	else
	{
		printf("There was a error opening the file for the list of vectors");
		return nameVector;
	}
}
