#include "../inc/User.hpp"
#include "../inc/Server.hpp"
#include "../inc/Channel.hpp"
#include "../inc/replies.hpp"


/*Para el mode tenemos que hacer varias cositas, realmente es simple, es una función que solo pueden usar los administradores y que
Cambia los estados del canal, es decir, esta mañana se queda hecho, veamos el protocolo:
Dividimos el mode en 2 partes:
-Modos del canal
-Modos del usuario

********MODOS DEL CANAL********
o - give/take channel operator privileges;
	   p - private channel flag;
	   i - invite-only channel flag;
	   t - topic settable by channel operator only flag;
	   m - moderated channel;
	   l - set the user limit to channel;
	   k - set a channel key (password).

   When using the 'o' option, a restriction on a total of three
   per mode command has been imposed.


*/
std::string trim(const std::string& str)
{
	std::string::const_iterator begin = str.begin();
	std::string::const_iterator end = str.end();

	while (begin != end && std::isspace(*begin))
		++begin;
	while (begin != end && std::isspace(*(end - 1)))
		--end;
	return std::string(begin, end);
}

bool	checkFlag(std::string flag, int mode) //Esta función comprueba las flags
{
	//usamos un trim para el principio y final del string, que elimine espacios y tabulaciones
	//Después comprobamos los flags y a mamarla
	flag = trim(flag);
	if (mode == 1) //mode es 1 si estamos haciendo un cambio pa usuarios
		if (flag != "-o" && flag != "+o")
			return false; //lanzar un mensaje de flag erronea
	else //mode es 0 si metemos flags para canales
	{
		if (flag != "-i" && flag != "+i" && flag != "+t" && flag != "-t" && flag != "+l" && flag != "-l")
			return false;
	}
	return true;
}

void	Server::userMode(std::vector<std::string> cmd, int fd) //LISTO
{
	/*
		El mode del usuario es super fácil, solo tiene una flag válida, -o que lo convierte en operador
		1- Comprobar todos los cmd's para ver que solo pueda haber 3, cmd[0] = MODE, cmd[1] = #canal cmd[2] = user, cmd[3] = flag +-o
		2- Comprobar que el usuario que vamos a hacer admin está en el canal y que no es admin ya
		3- comprobar la flag y hacer admin al usuario o quitar de admin
	*/
	std::string user = cmd[2];
	std::string channel_in = cmd[1];
	std::string flag = cmd[3];
	Channel *canal = searchChannel(channel_in);
	std::vector<User> usuarios = canal->getUsers();
	std::vector<User>::iterator it;


	if (cmd.size() > 4) //Hemos comprobado que la cantidad de argumentos está bien
		sendMessage(fd, ERR_NEEDMOREPARAMS(searchUser(fd)->getNick(), "MODE", "Invalid arguments"));
	else
	{
		if (userExists(canal->getUsers(), searchUser(user)->getNick())) //prueba 2 hecha
		{
			if (!canal->operatorExists(searchUser(fd)->getNick()) && checkFlag(cmd[3], 1) && cmd[3] == "+o")
				canal->addOperatorToList(*searchUser(fd)); //No reply is sent apparently
			else if (canal->operatorExists(searchUser(fd)->getNick()) && checkFlag(cmd[3], 1) && cmd[3] == "+o")
				return ; //Silently ignore the command
			else if (!canal->operatorExists(searchUser(fd)->getNick()) && checkFlag(cmd[3], 1) && cmd[3] == "-o")
				return ;
			else
				canal->removeOperatorFromList(usuarios, *searchUser(fd));
		}
	}
}
//void	Server::channelMode(std::vector<std::string> cmd, int fd);

void	Server::pickMode(std::vector<std::string> cmd, int fd) //ACORDARSE DE COMPROBAR QUE FD TIENE QUE SER ADMIN
{
	//primero comprobamos si el argumento cmd[2] es un canal o un usuario si no es ninguno, comprobamos si es un canal y si no lo es tampoco lanzamos un error
	std::string first_string = cmd[2]; //usamos cmd[2] porque X-Chat autocompleta y cmd[1] pasa como parámetro el canal
	std::string channel_name = cmd[1];
	User *user = searchUser(first_string);
	Channel *channel = searchChannel(first_string);
	
	if (!user->getNick().empty()) //Si es un usuario
	{
		
		return ; //Es un usuario
	}
	else if (!channel->getName().empty()) //Si es un canal
	{
		return ;
	}
	else
		sendMessage(fd, ERR_NOSUCHNICK(first_string));
}