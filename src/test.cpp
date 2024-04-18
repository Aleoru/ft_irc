#include <iostream>
#include <sstream>
#include <vector>
#include "../inc/Server.hpp"

static std::vector<std::string> splitString(const std::string str)
{
	std::vector<std::string> split;
	std::istringstream tokenStream(str);
	std::string token;
	size_t pos;

	while(std::getline(tokenStream, token))
	{
		pos = token.find_first_of("\r\n");
		if(pos != std::string::npos)
			token = token.substr(0, pos);
		split.push_back(token);
	}

	return (split);
}

static std::vector<std::string> splitString2(const std::string str, char delimiter)
{
	std::vector<std::string> split;
	std::string token;
	std::istringstream tokenStream(str);
	while (std::getline(tokenStream, token, delimiter)) 
	{
		split.push_back(token);
	}
	return (split);
}

void Server::parser(std::string str)
{
	std::cout << "str recived: <<" << str << ">>" << std::endl;
	std::cout << "-------------------" << std::endl;
	std::vector<std::string> vec = splitString(str);

	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << "Substring [" << i << "] -> " << vec[i] << std::endl;
		std::vector<std::string> cmd = splitString2(vec[i], ' ');
		for (size_t j = 0; j < cmd.size(); j++)
		{
			if (j == 0)
				std::cout << "Comand -> " << cmd[j] << std::endl;
			else
				std::cout << "argument [" << j << "] -> " << cmd[j] << std::endl;
		}
	}
}