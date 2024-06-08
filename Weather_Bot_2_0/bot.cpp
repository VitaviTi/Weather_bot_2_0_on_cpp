#include "bot.h"


Bot::Bot(std::string w_bot_key, std::string n_bot_key, std::string openweathermap_key)
	: bot(std::move(w_bot_key)),
	nbot(std::move(n_bot_key)),
	weather(std::move(openweathermap_key))
{

	std::string chatid = chatidfornotificaction();	//id where notification bot messages will be sent	

	//commands
	start (bot);
	help(bot);

	city_weather (bot, weather);

	backData(bot,weather);

	notification(bot, nbot, chatid);

	//Exception
	try {
		std::cout << "Bot username: " << bot.getApi().getMe()->username << std::endl;
		bot.getApi().deleteWebhook();
		TgBot::TgLongPoll longPoll(bot);//long poll
		while (true)
		{
			std::cout << "Long poll started\n";
			longPoll.start();						//long poll
		}
	}
	catch (TgBot::TgException& e) {
		std::cout << "error: %s\n" << e.what() << std::endl;
	}
	catch (std::string message)
	{
		std::cout << "Exception: " << message << std::endl;
	}
	catch (const char* message)
	{
		std::cout << "Exception: " << message << std::endl;
	}
}

std::string Bot::chatidfornotificaction()
{
	std::ifstream file("api_tgid.json");
	nlohmann::json setting;
	if (!file.is_open()) {
		throw "setting file is not open";
	}
	file >> setting;
	if (setting["tgnbotchatid"] == nullptr) {
		throw "file configuration is wrong";
	};
	return setting["tgnbotchatid"];
}

void Bot::start(TgBot::Bot& bot)
{
	bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "Hello! This weather bot 2.0. \nFor more information use the /help command\nWeather bot 1.0: @Weather_VT_bot");

		bot.getApi().sendPhoto(message->chat->id, TgBot::InputFile::fromFile("lightning.jpg", "image / jpeg"));
		});
}

void Bot::help(TgBot::Bot& bot)
{
	bot.getEvents().onCommand("help", [&bot](TgBot::Message::Ptr message) {
		bot.getApi().sendMessage(message->chat->id, "In order to get the weather you need to write the name of your city and select the weather time");
	});
}

void Bot::city_weather(TgBot::Bot& bot, Weather& weather)
{
	bot.getEvents().onAnyMessage([&bot, &weather](TgBot::Message::Ptr message) {
		if (message->text == "/start" || message->text == "/help") {
			return;
		}
		std::string found = weather.found(message->text);

		bot.getApi().sendMessage(message->chat->id, found);

		if (found == "city found")
		{
			std::vector<std::string> text_ = weather._text_(), callbackData_ = weather._callbackData_();
			TgBot::InlineKeyboardMarkup::Ptr keyboard(new TgBot::InlineKeyboardMarkup);

			for (size_t i = 0; i < text_.size(); i++)
			{
				std::vector<TgBot::InlineKeyboardButton::Ptr> row;
				TgBot::InlineKeyboardButton::Ptr checkButton(new TgBot::InlineKeyboardButton);
				checkButton->text = text_[i];
				checkButton->callbackData = callbackData_[i];
				row.push_back(checkButton);
				keyboard->inlineKeyboard.push_back(row);
			}
			bot.getApi().sendMessage(message->chat->id, "Time:", false, 0, keyboard, "Markdown");
		}
	});


}

void Bot::backData(TgBot::Bot& bot, Weather& weather)
{
	bot.getEvents().onCallbackQuery([&bot, &weather](TgBot::CallbackQuery::Ptr query) {
		if (query->data != "/start" || query->data != "/help")
		{
			if (query->data == "error") {
				bot.getApi().sendMessage(query->message->chat->id, "Sorry, there was an error. Please try again later.");
			}
			else {
				bot.getApi().sendMessage(query->message->chat->id, weather.textweather(query->data));
			}
		}
		});
}

void Bot::notification(TgBot::Bot& bot, TgBot::Bot& nbot, std::string& chatid)
{
	bot.getEvents().onAnyMessage([&bot, &nbot, &chatid] (TgBot::Message::Ptr message) {
		uint32_t subt = message->date;
		uint32_t days = (uint32_t)floor(subt / 86400);
		uint32_t hours = (uint32_t)floor(((subt - days * 86400) / 3600) % 24);
		uint32_t minutes = (uint32_t)floor((((subt - days * 86400) - hours * 3600) / 60) % 60);
		nbot.getApi().sendMessage(chatid,
			message->from->firstName + message->from->lastName +
			"(@" + message->from->username + ") wrote: " + "\n" + message->text + "\n" +
			"date: " + std::to_string(days) + " d. " + std::to_string(hours) + " hours " + std::to_string(minutes) + " min.");

	});
}

