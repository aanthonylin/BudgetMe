// Author: Anthony Lin
// Purpose: To obtain data from any API using a POST request
// Date: October 26, 2021
/*
NOTES:
	Must use c++11 or later for compiling
	When compiling, must include the libraries 'curl' and 'curlpp'
*/
#include "RequestManager.h"

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
std::string RequestManager::makePostRequest(std::string POSTBody)
{
	try
	{
		curlpp::Cleanup cleanup;
		curlpp::Easy request;
		curlpp::Forms form;
		std::stringstream response;
		std::list<std::string> contentType;

		request.setOpt(curlpp::options::Url(std::string(API_URL))); // Sets the URL
		request.setOpt(curlpp::options::Verbose(false)); // Shows more detail about the request

		contentType.push_back("Content-Type: application/json");
		request.setOpt(curlpp::options::HttpHeader(contentType)); // Sets the content to Json

		request.setOpt(curlpp::options::PostFields(POSTBody));
		request.setOpt(curlpp::options::PostFieldSize(POSTBody.length()));

		request.setOpt(new curlpp::options::WriteStream(&response)); // Set where to send the output

		request.perform(); // Execute the request

		return response.str();
	}
	catch (...)
	{
		std::cerr << "Error when calling the API" << std::endl;
		return ""; 
	}
}

/**
* @brief Set the URL of the API
*
* Takses a parameter and sets the URL to the parameter
*
* @param URL: The URL of where to request is to be made to
*/
void RequestManager::setURL(std::string URL)
{
	API_URL = URL;
}

/**
* @brief Gets where the request is being made to
*
* It returns the where the API is currently set to
*
* @return A string that represents the URL
*/
std::string RequestManager::getURL()
{
	return API_URL;
}
