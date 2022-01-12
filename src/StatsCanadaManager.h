#define dataLink "https://www150.statcan.gc.ca/t1/wds/rest/getDataFromVectorsAndLatestNPeriods"
#define metadataLink "https://www150.statcan.gc.ca/t1/wds/rest/getSeriesInfoFromVector"
#define defaultFile "StatsCanVectorList.txt"

#ifndef STATSCANMANAGER_H
#define STATSCANMANAGER_H

#include "RequestManager.h"
#include <fstream>
#include <string>
#include <vector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QByteArray>
#include <QString>

/**
* @brief An object that will retrieve data from Statisitcs Canada
*
* It calls the RequestManager object and makes a POST request to get data.
* This object will only work for Statistics Canada as it is designed to 
* parse their returned data and make a POST body designed for Statistics 
* Canada. To make a more general POST request, look at the 'RequestManager'
* object.
*
* @author Anthony Lin
*/
class StatsCanadaManager
{
	private:
		/**
		* @brief An object that makes request
		* 
		* This object can make request to any API but does 
		* not have a lot of functionality otherwise
		*/
		RequestManager manager;
		
		/**
		* @brief The source of the data
		* 
		* The source of the metadata. It is defaulted to "https://www150.statcan.gc.ca/t1/wds/rest/getDataFromVectorsAndLatestNPeriods"
		*/
		std::string dataURL = dataLink;
		
		/**
		* @brief The source of the metadata
		* 
		* The source of the metadata. It is defaulted to "https://www150.statcan.gc.ca/t1/wds/rest/getSeriesInfoFromVector"
		*/
		std::string metadataURL = metadataLink;
		
		/**
		* @brief Sets the source of the request
		*
		* It sets the URL of the RequestManager to the parameter.

		* @param newSource: the source that the RequestManager should be set to
		*
		*/
		void setSource(std::string);
		
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
		std::string makePostBody(std::string, std::string);
		
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
		std::vector<int> parseData(std::string);
		
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
		std::vector<QString> parseMetadata(std::string);
	public:
		/**
		* @brief It sets where to get the data from
		*
		* It takes the parameter and sets the RequestManager to it so that when the request is made,
		* the data sent is to the right place and therefore, the data retrieved is correct
		*
		* @param url: the url of where to get the data from
		*/
		void setDataURL(std::string);
		
		/**
		* @brief It sets where to get the metadata from
		*
		* It takes the parameter and sets the RequestManager to it so that when the request is made,
		* the data sent is to the right place and therefore, the metadata retrieved is correct
		*
		* @param url: the url of where to get the metadata from
		*/
		void setMetadataURL(std::string);
		
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
		std::vector<int> getData(std::string);
		
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
		std::vector<QString> getMetadata(std::string);
};

#endif
