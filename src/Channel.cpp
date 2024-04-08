/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:19:31 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/08 19:55:22 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/Channel.hpp"

Channel::Channel(std::string name): _name(name)
{
    this->_setTopic = false;
    this->_limit = NOLIMIT;
    this->_invite = false;
}

Channel::~Channel()
{

}

std::vector<int> Channel::channelListUsers()
{
    std::vector<int> channelUsers;

    return (channelUsers);
}
