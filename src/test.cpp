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

void Server::findComnand(std::vector<std::string> cmd, int fd, bool debug)
{
	(void)debug;
	if (!cmd[0].compare("JOIN"))
		std::cout << "Join command" << std::endl;	
	else if (!cmd[0].compare("NICK"))
	{
		std::cout << "Nick command" << std::endl;
		nickCmd(cmd[1], fd);
		User	user = searchUser(fd);
		std::cout << "Nickname " << fd << ": "<< user.getNick() << std::endl;
	}
	else if (!cmd[0].compare("USER"))
		std::cout << "User command" << std::endl;
	else if (!cmd[0].compare("PASS"))
		std::cout << "Pass command" << std::endl;
}

// Parser (de mierda xD) provisional 
void Server::parser(std::string str, int fd, bool debug)
{
	if (debug)
	{
		std::cout << "str recived: <<" << str << ">>" << std::endl;
		std::cout << "-------------------" << std::endl;
	}
	std::vector<std::string> vec = splitString(str);

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (debug)
			std::cout << "Substring [" << i << "] -> " << vec[i] << std::endl;
		std::vector<std::string> cmd = splitString2(vec[i], ' ');
		for (size_t j = 0; j < cmd.size(); j++)
		{
			if (debug)
			{
				if (j == 0)
					std::cout << "Comand -> " << cmd[j] << std::endl;
				else
					std::cout << "argument [" << j << "] -> " << cmd[j] << std::endl;
			}
		}
		findComnand(cmd, fd, debug);
	}
}

// provisional commands
void Server::nickCmd(std::string nickname, int fd)
{
	std::cout << "executing nick command " << fd << std::endl;
	User	user = searchUser(fd);
	user.setNickname(nickname);
}