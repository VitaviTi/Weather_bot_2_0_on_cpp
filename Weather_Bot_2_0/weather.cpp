#include "weather.h"

Weather::Weather(std::string api_key)
	:weathermap(std::move(api_key))
{
}

std::vector<std::string> Weather::_callbackData_()
{
	return callbackData;
}

std::vector<std::string> Weather::_text_()
{
	return text;
}

std::string Weather::textweather(std::string callbackDt)
{
	std::string cityname;
	std::string strn;
	bool slash = true;

	for (int i = 0; i < callbackDt.size(); i++)
	{
		if (callbackDt[i] == '|') {
			slash = false;
			i++;
		}
		if (slash) {
			strn += callbackDt[i];
		}
		else {
			cityname += callbackDt[i];
		}
	}

	int n = stoi(strn);
	
	nlohmann::json wwjson = weathermap.make_request_by_city(cityname);

	return wtext.weather(wwjson, n);
}

std::string  Weather::found(std::string city_name)
{
	callbackData = {};
	text = {};
	wjson = weathermap.make_request_by_city(city_name);

	button();

	if (wjson["message"] == 0) {
		return "city found";
	}
	if (wjson["message"] == "city not found") {
		return "city not found";
	}
	throw "error in the service or api key";
	return "Oops an unknown error occurred!";
}

void Weather::button()
{
	try
	{
		if (wjson["city"]["name"] == nullptr) {
			throw "in class Weather wjson[\"city\"][\"name\"] == nullptr";
		}
		if (wjson["cnt"] == 40)
		{
			text = { "now", "1 day", "2 day", "3 day", "4 day", "5 day" };
			callbackData.push_back("0|" + json_in_str(wjson["city"]["name"]));
			for (size_t i = 1; i < 40; i++)
			{
				std::string str = wjson["list"][i]["dt_txt"];
				if (str[11] == '1' && str[12] == '2') {
					callbackData.push_back(std::to_string(i) + "|" + json_in_str(wjson["city"]["name"]));
				}
			}
		} else {
			for (size_t i = 0; i < wjson["cnt"]; i++)
			{
				text.push_back(wjson["list"][i]["dt_txt"]);
				callbackData.push_back(std::to_string(i) + "|" + json_in_str(wjson["city"]["name"]));
			}
		}

		if (text.size() != callbackData.size()) {
			throw "in class Weather callbackData.size() != text.size()";
		}

	}
	catch (const char* mess) {
		std::cerr << mess << std::endl;
		text = { "error" };
		callbackData = { "error" };

	}
}

std::string Weather::json_in_str(nlohmann::json json)
{
	return json;
}