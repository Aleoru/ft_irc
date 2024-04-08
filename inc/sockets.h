/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sockets.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalan-r <fgalan-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:31:37 by fgalan-r          #+#    #+#             */
/*   Updated: 2024/04/03 15:37:22 by fgalan-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETS_H
# define SOCKETS_H

# include <errno.h>
# include <netdb.h>
# include <poll.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h> 
# include <sys/poll.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <signal.h>

void	*ft_memset(void *str, int c, size_t n);
size_t	ft_strlen(const char *str);

#endif