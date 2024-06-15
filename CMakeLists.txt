cmake_minimum_required(VERSION 3.2)

project(weather-smart-bot LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    Weather_Bot_2_0/Weather_Bot_2_0.cpp
    Weather_Bot_2_0/weather_api.cpp
    Weather_Bot_2_0/bot.cpp
    Weather_Bot_2_0/weather.cpp
    Weather_Bot_2_0/weather_text.cpp )
set(HEADERS
    Weather_Bot_2_0/weather_api.h
    Weather_Bot_2_0/bot.h
    Weather_Bot_2_0/weather.h
    Weather_Bot_2_0/weather_text.h )

add_executable(weather-tg-bot ${SOURCES} ${HEADERS})

file(COPY Weather_Bot_2_0/api_tgid.json DESTINATION ${PROJECT_BINARY_DIR})
