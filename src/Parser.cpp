/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:31:58 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/27 04:46:28 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

static std::vector<std::string> splitcmd(const std::string str)
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

std::vector<std::string> Server::split(const std::string str, char delimiter)
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

void Server::findCommand(std::vector<std::string> cmd, int fd, bool debug)
{
	bool access = searchUser(fd)->getHasAccess();
	if (debug && access)
		std::cout<<"access to execute: "<<cmd[0]<<std::endl;

	if (!cmd[0].compare("PASS") && !searchUser(fd)->getCheckPass())
		passCmd(cmd, fd);
	else if (!cmd[0].compare("NICK") && searchUser(fd)->getCheckPass())
		nickCmd(cmd, fd);
	else if (!cmd[0].compare("USER") && searchUser(fd)->getCheckPass())
		userCmd(cmd, fd);
	else if (!cmd[0].compare("JOIN") && access)
		joinCmd(cmd, fd);
	else if (!cmd[0].compare("PRIVMSG") && access)
		privMsgCmd(cmd, fd);
	else if (!cmd[0].compare("PART") && access)
		partCmd(cmd, fd);
	else if (!cmd[0].compare("QUIT") && access)
		quitCmd(cmd, fd);
	else if (!cmd[0].compare("TOPIC") && access)
		changeTopic(cmd, fd);
	else if (!cmd[0].compare("KICK") && access)
		kickCmd(cmd, fd);
	else if (!cmd[0].compare("INVITE") && access)
		inviteCmd(cmd, fd);
	else if (!cmd[0].compare("MODE") && access)
		modeCmd(cmd, fd);
	else if (!cmd[0].compare("info"))
		infoServer();
	else
		std::cout<<YEL<<cmd[0]<<" error: command not found"<<WHI<<std::endl;
}

void Server::parser(std::string str, int fd, bool debug)
{
	if (debug)
	{
		std::cout << "str recived: <<" << str << ">>" << std::endl;
		std::cout << "-------------------" << std::endl;
	}
	std::string trimstr = str.substr(0, 510);
	std::vector<std::string> vec = splitcmd(str);
	if (vec[0].empty())
		return ;
	for (size_t i = 0; i < vec.size(); i++)
	{
		if (debug)
			std::cout << "Substring [" << i << "] -> " << vec[i] << std::endl;
		std::vector<std::string> cmd = split(vec[i], ' ');
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
		findCommand(cmd, fd, debug);
	}
}
