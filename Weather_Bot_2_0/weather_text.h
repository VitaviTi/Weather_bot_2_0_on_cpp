#pragma once
#ifndef WEATHER_TEXT_H
#define WEATHER_TEXT_H

#include "json.hpp"

#include <iostream>		//cout, cerr
#include <string>	//string
#include <sstream>		//stringstream

class Weather_text
{
public:
	std::string weather(const nlohmann::json &weatherjson, int n);//main func
private:
	std::string weather_text_now();	//weather of the moment
	std::string weather_text_later();	//future weather up to 5 days

	nlohmann::json wjson;	//weather of a certain time
	nlohmann::json cityjson;	//json city

	std::string instr(std::string json);	//convert jsonstring in string
	std::string convert_to_str(nlohmann::json json);	//convert json in string by using sstream

	std::string main_inf();	//cityname + country + weather description
	std::string hum();	//humidity
	std::string temp();	//temperature
	std::string wind();	//speed wind + wind direction
	std::string sun();	//sunrise + sanset
	std::string time();	//weather time

	std::string convert_unixtime(uint64_t subt);	//convert unix time in ordinary time
	std::string wind_degree(nlohmann::json _json);	// convert wind degree in direction of the wind
};

#endif // !WEATHER_TEXT_H