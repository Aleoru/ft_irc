/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUtils.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:47:48 by aoropeza          #+#    #+#             */
/*   Updated: 2024/04/15 20:47:51 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

std::vector<std::string> Server::splitString(std::string str)
{
    std::vector<std::string> split;
    std::istringstream stm(str);
	std::string line;
    size_t pos;
	while(std::getline(stm, line))
	{
		pos = line.find_first_of("\r\n");
		if(pos != std::string::npos)
			line = line.substr(0, pos);
		split.push_back(line);
	}

    return (split);
}