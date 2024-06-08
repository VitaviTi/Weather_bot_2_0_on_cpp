#pragma once
#ifndef WEATHER_H
#define WEATHER_H

#include <string>
#include <vector>

#include "weather_api.h"
#include "weather_text.h"
#include "json.hpp"

class Weather
{
public:

	Weather(std::string api_key);

	std::vector<std::string> _callbackData_();	//vector of returning values ​​when a button is pressed
	std::vector<std::string> _text_();	//button names vector

	std::string textweather(std::string callbackDt);

	std::string found(std::string city_name);

private:

	weather_bot::OpenWeatherMapApi weathermap;	//weather service
	Weather_text wtext;	//json handler with weather to weather text

	nlohmann::json wjson;	//json with weather

	std::vector<std::string> callbackData, text;

	void button();

	std::string json_in_str(nlohmann::json json);
};

#endif // !WEATHER_H