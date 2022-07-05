/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:08:11 by imoore            #+#    #+#             */
/*   Updated: 2022/06/27 12:18:02 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//moves through the envp array to find the relevant 'PATH' array - returns this
char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

//runs through all the path strings (e.g. bin/user' or 'ls/user/whatever' that we got from the 'PATH=' string)
//finds the cmd
char	*get_cmd_path(char **paths, char *cmd)
{
	char	*temp;
	char	*cmd_path;

	while (*paths)
	{
		temp = ft_strjoin(*paths, "/"); //puts a '/' at the end of the path string
		cmd_path = ft_strjoin(temp, cmd); //then attaches the cmd to this string as well
		free(temp);
		if (access(cmd_path, 0) == 0) //use access to determine if this is the right one -  if it is it will return 0
			return (cmd_path); //if success it will exit and return the successful cmd path
		free(cmd_path);
		paths++;
	}
	return (NULL);
}


//funciton that executes the cmds once the outputs and inputs have been properly set up
void	execute_cmds(char *argv, char **envp)
{
	char	**paths;
	char	**cmd_args;
	char	*cmd_path;

	paths = ft_split((find_path(envp)), ':'); //splits the PATH array returned by find_path and splits it by ':'
	cmd_args = ft_split(argv, ' '); //splits command from arguments e.g. "ls -l" will be split by ' ' - returns a char**
	cmd_path = get_cmd_path(paths, cmd_args[0]); //takes the first of char** from above (e.g. "ls") and puts it through get_cmd_path
	if (!cmd_path)
	{
		free(cmd_args); //free cos malloc in ft_split
		free(cmd_path);
		msg_variable("Command not found: ", argv);
		exit(EXIT_FAILURE);
	}
	execve(cmd_path, cmd_args, envp); 
	//'cmd_path' = the environment string after 'PATH=' and deliminated by ':' 
	//'cmd_args' = the arguments for the cmd e.g. ls -l == "-l" is the arg.
	//'envp' = the environment string
}
