/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 19:55:14 by aoropeza          #+#    #+#             */
/*   Updated: 2024/05/18 13:05:26 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

// /Invite john #politics
void	Server::inviteCmd(std::vector<std::string> cmd, int fd)
{
	if (cmd.size() == 3)
	{
		Channel	*channel = searchChannel(cmd[2]);
		if (channel)
		{
			if (userExists(channel->getOperators(), searchUser(fd)->getNick()))
			{
				channel->addUserToInvited(*searchUser(cmd[1]));
				std::cout<<YEL<<searchUser(fd)->getNick()<<" has invited "<<cmd[1]<<" to "<<cmd[2]<<WHI<<std::endl;
			}
			else
			{
				//error: is not an operator
				std::cout<<YEL<<searchUser(fd)->getNick()<<" is not an operator"<<WHI<<std::endl;
			}
		}
		else
		{
			//error: no channel
			std::cout<<YEL<<cmd[2]<<" is not a channel"<<WHI<<std::endl;
		}
	}
	else
	{
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), cmd[0], "/INVITE [user] [#channel]"));
		std::cout<<YEL<<"Incorret arguments"<<WHI<<std::endl;
	}
}



/*Una vez incluidas las librerias ahora vamos a ponernos con el Invite
Tiene como estructura: invite <nick> #<canal>
PASOS:
1-Verificar si el usuario que invita tiene permisos, lo vamos a poner como variable nula por ahora
2-Verificar si existe el usuario invitado comprobando su nick
3-Si existe el usuario y hay permisos y existe el canal, añadirlo a la lista de invitados
3.5- Si ya existe en la lista de invitados, ignorar el comando, osea no hace nada
*/

/* void	Server::invite(std::string inv_user, Channel canal, bool needOp) //last var is temporary atm
{
	if (!channelExists(canal.getName())) //Esta comprobación es innecesaria según el protocolo pero es posible que de lugar a un error de segmentación o se crea un canal nuevo?
		return ;
	std::vector<User> users = getUsers(); //Vector for Users in the server
	std::vector<User>::iterator it = users.begin(); //Iterator for users in the server
	std::vector<User> users_ch = canal.getUsers(); //Vector for Users in the channel
	std::vector<User> ops = canal.getOperators(); //FALTA HACER ESTE GETTER
	for(it; it != users.end(); it++)
	{
		if (needOp == true)
		{
			if (it->getNick() == inv_user && !userExists(users_ch, it->getNick()) && !userExists(ops, it->getNick()))  //si existe el nick en el servidor y no está unido al canal
			{
				canal.addUserToList(*it);
				sendMessage(1, RPL_INVITING(it->getNick(), canal.getName()));
				return ;
			}
		}
		else if (needOp == false)
		{
			if (it->getNick() == inv_user && !userExists(users_ch, it->getNick()))  //si existe el nick en el servidor y no está unido al canal
				canal.addUserToList(*it);
		}
	}
	sendMessage(1, ERR_NOSUCHNICK(it->getNick())); //Si no hemos podido añadir el usuario al canal, la última opción es que no exista el usuario y por ende, no se haya podido invitar
	return ;
} */