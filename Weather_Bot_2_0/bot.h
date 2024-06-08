#pragma once
#ifndef BOT_H
#define BOT_H

#include <vector>	//vector
#include <iostream>		//cout, cerr
#include <fstream>	//ifstream

#include <tgbot/tgbot.h>//TgBot

#include "weather.h"

class Bot
{
public:
	Bot(std::string w_bot_key, std::string n_bot_key, std::string openweathermap_key); //Constructor
private:
	TgBot::Bot bot;		//weather bot
	TgBot::Bot nbot;	//notification bot
	Weather weather;	//class connecting the weather service robot and the weather text handler

	std::string chatidfornotificaction();

	void start (TgBot::Bot& bot); //command start

	void help (TgBot::Bot& bot);//command help

	void city_weather (TgBot::Bot& bot, Weather& weather);	//works with any messages received by the weather bot

	void backData (TgBot::Bot& bot, Weather& weather);	//processes input data

	void notification (TgBot::Bot& bot, TgBot::Bot& nbot, std::string& chatid);	//notification bot notifies you of all messages written to the weather bot
};

#endif // ! BOT_H