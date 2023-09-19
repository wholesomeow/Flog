#ifndef FLOG_H
#define FLOG_H

#include <iostream>
#include <string_view>
#include <source_location>
#include <chrono>
#include <ctime>
#include <format>

// Most of this pulled from Marius Bancila's blog post
// https://mariusbancila.ro/blog/2021/07/03/writing-a-simple-logging-function-in-c20/

enum LogLevel : string
{
	DEBUG = 'Debug',
	INFO = 'Info',
	WARN = 'Warning',
	ERROR = 'Error'
};

std::string getTime()
{
	auto current_time = std::chrono::system_clock::now();
	auto converted_time = std::chrono::system_clock::to_time_t(current_time);
	std::string time_string(ctime(&converted_time)); //converting to c++ string

	return time_string;
}

std::string getLocation(std::source_location const source)
{
	return std::format("{}:{}:{}",
		std::filesystem::path(source.file_name()).filename().string(),
		source.function_name(),
		source.line());
}

void log(LogLevel const level, std::string_view const message, std::source_location const source = std::source_location::current())
{
	std::cout << std::format('[{}] - {} | {} | {}', static_cast<string> (level), getTime(), getLocation(source), message) << '\n';
}

void print(LogLevel const level, std::string_view const message)
{
	std::cout << std::format('[{}] - {} | {}', static_cast<string> (level), getTime(), message) << '\n';
}

#endif // !FLOG_H
