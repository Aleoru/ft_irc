#include "../inc/User.hpp"
#include "../inc/Server.hpp"
#include "../inc/Channel.hpp"

/*
El kick es un comando que va a eliminar a un usuario de un canal.
1-Solo los operadores pueden usar este comando

TODO

1. Verificar que el usuario haciendo el request está en el canal, y es admin
2. Verificar que el usuario al que va a expulsar existe
3. Expulsar al usuario eliminando su FD de la lista de ese canal

*/

/*
Esta función busca a un usuario en un vector de usuarios, devuelve verdadero si lo encuentra y falso si no
*/
bool	findUserList(std::string nick, std::vector<User> users) //PONER EN UTILS
{
	std::vector<User>::iterator it = std::find(users.begin(), users.end(), nick);
	if (it != users.end())
		return true;
	return false;
}

void	Kick(Server serv, User admin, User *user, Channel *canal, const std::string &message)
{
	//Para el kick, tengo que verificar que el usuario que lo está haciendo sea admin del canal
	//También que el usuario que vamos a expulsar exista
	std::vector<User> ops = canal->getOperators();
	std::vector<User> users = canal->getUsers();
	std::vector<User>::iterator it = users.begin();

	if (findUserList(admin.getNick(), users) && findUserList(admin.getNick(), ops)) //Si el admin es admin y está en el canal
	{
		if (findUserList(user->getNick(), users)) //Si el usuario está en el canal
		{
			for(it; it != users.end();it++) //busca al usuario y eliminalo
				if (it->getNick() == user->getNick())
					users.erase(it);
		}
		else
			serv.sendMessage(1, ERR_NOTONCHANNEL(canal->getName()));
	}
	else
		serv.sendMessage(1, ERR_CHANOPRIVSNEEDED(canal->getName()));
	return ;
}