/*
	_________	 _____			|----\	 /---\	---------
		|       / 	  \			|	  \	|	  |		|
		|	   |				|_____|	|	  |		|
		|	   |    ___			|	  | |	  |		|
		|		\_____/			|_____/	 \___/		|
*/
#include "bot.h"
#include "json.hpp"

#include <fstream>

nlohmann::json read()
{
	std::ifstream file("api_tgid.json");
	try
	{		
		if (!file.is_open()){
			throw "setting file is not open";
		}		
		
	}
	catch (char mess)
	{
		std::cerr << mess << std::endl;
		terminate();
	}
	nlohmann::json res;
	file >> res;
	return res;
}

int main()
{
	nlohmann::json setting = read();
	if (setting["weathertoken"] == nullptr || setting["tgwbottoken"] == nullptr
		|| setting["tgnbottoken"] == nullptr || setting["tgnbotchatid"] == nullptr) {
		std::cerr << "file configuration is wrong" << std::endl;
		terminate();
	}
	const std::string WEATHERTOKEN = setting["weathertoken"];
	const std::string TGWBOTTOKEN = setting["tgwbottoken"];
	const std::string TGNBOTTOKEN = setting["tgnbottoken"];
	Bot bot(TGWBOTTOKEN, TGNBOTTOKEN, WEATHERTOKEN);
}