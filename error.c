/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:08:20 by imoore            #+#    #+#             */
/*   Updated: 2022/06/27 12:19:47 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//writes an error message of char *err, to stderr - will print in terminal//
int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

//writes an error message of char* err and joins it with a ':' and the 'incorrect' entered character string 'char *entered'//
//used for incorrect argument error - will output to terminal something like 'argument not recognised: blah'//
int	msg_variable(char *err, char *entered)
{
	char	*temp;
	char	*error_terminal;

	temp = ft_strjoin(err, entered);
	error_terminal = ft_strjoin(temp, "\n");
	write(2, error_terminal, ft_strlen(error_terminal));
	return (0);
}

//writes an error message to terminal if a system call fails (e.g. if open fails it will return -1: this function will print 'Error: and the associated system call error message')//
int	error_msg(int errnum)
{
	if (errnum < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	return (0);
}
