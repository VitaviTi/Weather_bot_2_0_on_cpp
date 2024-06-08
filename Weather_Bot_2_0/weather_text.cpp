#include "weather_text.h"

std::string Weather_text::weather(const nlohmann::json& weatherjson, int n)
{
	wjson = weatherjson["list"][n];
	cityjson = weatherjson["city"];
	try
	{
		if (n == 0) {
			return weather_text_now();
		}
		else {
			return weather_text_later();
		}
	}
	catch (std::string exception)
	{
		std::cerr << "Exception: " << exception << std::endl;
	}
}

std::string Weather_text::weather_text_now()
{
	return main_inf() + "\n" + hum() + "\n" + temp() + "\n" + wind() + "\n" + sun();
}

std::string Weather_text::weather_text_later()
{
	return time() + "\n" + main_inf() + "\n" + temp() + "\n" + wind();
}


std::string Weather_text::instr(std::string json)
{
	return json;
}

std::string Weather_text::convert_to_str(nlohmann::json const json)
{
	std::stringstream ss; std::string res;
	ss << json;
	ss >> res;
	return res;
}


std::string Weather_text::main_inf()
{
	if (wjson["weather"][0]["description"] == nullptr || cityjson["name"] == nullptr) {
		throw "main_inf == nullptr !!!";
		return "no data available";
	}
	else {
		return "City: " + instr(cityjson["name"]) + " " + instr(cityjson["country"]) + "\n" + instr(wjson["weather"][0]["description"]);
	}
}

std::string Weather_text::hum()
{
	if (wjson["main"]["humidity"] == nullptr) {
		throw "hum == nullptr !!!";
		return "no data available";
	}
	else {
		return "Humidity: " + convert_to_str(wjson["main"]["humidity"]);
	}
}

std::string Weather_text::temp()
{
	if (wjson["main"]["temp"] == nullptr) {
		throw "temp == nullptr !!!";
		return "no data available";
	}
	else {
		return "Temperature: " + convert_to_str(wjson["main"]["temp"]);
	}
}

std::string Weather_text::wind()
{
	if (wjson["wind"]["speed"] == nullptr || wjson["wind"]["deg"] == nullptr) {
		throw "wind == nullptr !!!";
		return "no data available";
	}
	else {
		return "Wind speed: " + convert_to_str(wjson["wind"]["speed"]) + " m/s " + "\n" + wind_degree(wjson["wind"]["deg"]);
	}
}

std::string Weather_text::sun()
{
	if (cityjson["sunrise"] == nullptr || cityjson["sunset"] == nullptr) {
		throw "main_inf == nullptr !!!";
		return "no data available";
	}
	else {
		return "sunrise: " + convert_unixtime(cityjson["sunrise"]) + "\n"
			+ "sunset: " + convert_unixtime(cityjson["sunset"]);
	}
}

std::string Weather_text::time()
{
	return wjson["dt_txt"];
}

std::string Weather_text::convert_unixtime(uint64_t subt)
{
	if (cityjson["timezone"] == nullptr) {
		throw "convert_unixtime == nullptr!!!";
		return "undefined";
	}
	else {
		subt += cityjson["timezone"];
		uint32_t days = (uint32_t)floor(subt / 86400);
		uint32_t hours = (uint32_t)floor(((subt - days * 86400) / 3600) % 24);
		uint32_t minutes = (uint32_t)floor((((subt - days * 86400) - hours * 3600) / 60) % 60);

		return std::to_string(hours) + " h. " + std::to_string(minutes) + " min. ";
	}
}

std::string Weather_text::wind_degree(nlohmann::json json)
{
	std::stringstream ss1;
	float k;
	ss1 << json;
	ss1 >> k;

	int n = k / 9;

	if (n > 3 && n < 7)return "northeast wind";/*northeast*/
	if (n > 13 && n < 17)return "southeast wind";/*southeast*/
	if (n > 23 && n < 27)return "southwest wind";/*southwest*/
	if (n > 33 && n < 37)return "northwest wind";/*northwest*/

	switch (n /= 10)
	{
	case 0:
	case 4:
		return "north wind";/*north*/
	case 1:
		return "east wind";/*east*/
	case 2:
		return "south wind";/*south*/
	case 3:
		return "west wind";/*west*/
	default:
		throw "wind direction is not determined";
		return "undefined";
	}
	return "undefined";
}