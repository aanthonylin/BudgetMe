#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <iostream>
#include <sstream>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

/**
* @brief Makes a request to an API
*
* This object will make request to an API. Currently it only supports making 
* POST request. It can make a request to anywhere and it is not limited.
*
* @author Anthony Lin
*/
class RequestManager
{
	private:
		/**
		* @brief The destination of the request
		* 
		* This is where the request will go when called. It is
		* defaulted to nothing ("") and must be set before use.
		*/
		std::string API_URL = "";
	public:
		/**
		* @brief Set the URL of the API
		*
		* Takses a parameter and sets the URL to the parameter
		*
		* @param URL: The URL of where to request is to be made to
		*/
		void setURL(std::string);
		
		/**
		* @brief Gets where the request is being made to
		*
		* It returns the where the API is currently set to
		*
		* @return A string that represents the URL
		*/
		std::string getURL();
		
		/**
		* @brief Makes a POST request
		*
		* It makes a POST request to the indicated API with the parameter also being sent to the 
		* API
		*
		* @param POSTBody: The JSON that should be sent to the API
		*
		* @return The response of the API
		*/
		std::string makePostRequest(std::string);
};

#endif
