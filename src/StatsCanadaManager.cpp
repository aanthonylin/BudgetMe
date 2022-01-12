// Author: Anthony Lin
// Purpose: To obtain data from Stats Canada
// Date: November 15, 2021

#include "StatsCanadaManager.h"

/**
* @brief Sets the source of the request
*
* It sets the URL of the RequestManager to the parameter.

* @param newSource: the source that the RequestManager should be set to
*
*/
void StatsCanadaManager::setSource(std::string newSource)
{
	manager.setURL(newSource);
}

/**
* @brief Makes a JSON for a POST request to StatsCanada
*
* It takes a file and reads from it. Each line should be a vector and it creates a JSON
* that ends with the user specified endBody. The JSON is used to tell Statistics Canada 
* the data that we want
*
* @param fName: The name of the file that is to be converted into a JSON
* @param bodyEnd: A string stating how the request should end for each entry in the file
*
* @return A string in the form of a JSON that can be sent to make the POST request
*/
std::string StatsCanadaManager::makePostBody(std::string fName, std::string bodyEnd)
{
	std::string POSTBody;
	std::string bodyStart;
	std::string strVector;
	std::string line;
	std::ifstream file;
	int i;
	int vector;
	
	bodyStart = "{\"vectorId\":";
	POSTBody = "[";

	file.open(fName);
	if (file.is_open())
	{
		while (getline(file, line))
		{
			vector = 0;
			i = 0;
			while (line.at(i) >= '0' && line.at(i) <= '9')
			{
				vector = vector * 10 + line.at(i) - '0';
				i = i + 1;
			}
			strVector = std::to_string(vector);
			POSTBody = POSTBody + bodyStart + strVector + bodyEnd; // Add a command to the POST body
			}
		POSTBody.at(POSTBody.length()-1) = ']'; // Change the ',' to a ']' for proper JSON format
		file.close();
		return POSTBody;
	}
	else
	{
		printf("There was a error opening the file for the list of vectors");
		return "";
	}
}

/**
* @brief Makes a request to get the data
*
* It prepares the request and makes the required parameters that will be sent during 
* the request. It then makes the request and processes the data it returns. 
*
* @param fName: A file of vectors that represent the desired data
*
* @return An vector of integers storing the associated values
*/
std::vector<int> StatsCanadaManager::getData(std::string fName)
{
	manager.setURL(StatsCanadaManager::dataURL);
	std::string pBody = makePostBody(fName, ",\"latestN\":1},");
	std::string response = manager.makePostRequest(pBody);
	return parseData(response);
}

/**
* @brief It sets where to get the data from
*
* It takes the parameter and sets the RequestManager to it so that when the request is made,
* the data sent is to the right place and therefore, the data retrieved is correct
*
* @param url: the url of where to get the data from
*/
void StatsCanadaManager::setDataURL(std::string url)
{
	dataURL = url;
}

/**
* @brief Parses the response from the API
*
* It takes the API response and removes all the 'unnecessary' data. When it comes upon the
* desired value, it stores it in the vector and continues to search for the next value until
* all the data is found
*
* @param response: The JSON that the API returned
*
* @return An vector of integers storing the associated values
*/
std::vector<int> StatsCanadaManager::parseData(std::string response)
{
	std::string SUCCESS = "SUCCESS";
	QString status_str = QString::fromStdString("status");
	QString object_str = QString::fromStdString("object");
	QString vectorDataPoint_str = QString::fromStdString("vectorDataPoint");
	QString value_str = QString::fromStdString("value");
	
	std::vector<int> dataVector = {};
	QJsonObject request;
	QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(response).toUtf8());
	QJsonArray data = document.array();
	
	for (int i = 0; i < data.size(); i++) // For every piece of information that we called
	{
		request = data.at(i).toObject();
		if (request.value(status_str).toString().operator==(SUCCESS.c_str())) // If the request was successful
		{
			dataVector.push_back(int (request.value(object_str).toObject().value(vectorDataPoint_str).toArray().takeAt(0).toObject().value(value_str).toDouble()));
		}
	}
	return dataVector;
}

/**
* @brief Makes a request to get the metadata
*
* It prepares the request and makes the required parameters that will be sent during 
* the request. It then makes the request and processes the metadata it returns. 
*
* @param fName: A file of vectors that represent the desired metadata
*
* @return An vector of QString storing the associated values
*/
std::vector<QString> StatsCanadaManager::getMetadata(std::string fName)
{
	manager.setURL(StatsCanadaManager::metadataURL);
	std::string pBody = makePostBody(fName, "},");
	std::string response = manager.makePostRequest(pBody);
	return parseMetadata(response);
}

/**
* @brief It sets where to get the metadata from
*
* It takes the parameter and sets the RequestManager to it so that when the request is made,
* the data sent is to the right place and therefore, the metadata retrieved is correct
*
* @param url: the url of where to get the metadata from
*/
void StatsCanadaManager::setMetadataURL(std::string url)
{
	metadataURL = url;
}

/**
* @brief Parses the response from the API
*
* It takes the API response and removes all the 'unnecessary' metadata. When it comes upon the
* desired value (the name of the category), it stores it in the vector and continues to search 
* for the next value until all the data is found
*
* @param response: The JSON that the API returned
*
* @return An vector of QString storing the associated values
*/
std::vector<QString> StatsCanadaManager::parseMetadata(std::string response)
{
	std::string SUCCESS = "SUCCESS";
	QString status_str = QString::fromStdString("status");
	QString object_str = QString::fromStdString("object");
	QString seriesTitle_str = QString::fromStdString("SeriesTitleEn");
	
	QJsonObject request;
	QJsonDocument document = QJsonDocument::fromJson(QString::fromStdString(response).toUtf8());
	QJsonArray data = document.array();
	std::vector<QString> metadata = {};
	
	for (int i = 0; i < data.size(); i++) // For every piece of information that we called
	{
		request = data.at(i).toObject();
		if (request.value(status_str).toString().operator==(SUCCESS.c_str())) // If the request was successful
		{
			metadata.push_back(request.value(object_str).toObject().value(seriesTitle_str).toString().section(';',-1));
		}
	}
	return metadata;
}
