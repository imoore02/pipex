/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:24:39 by imoore            #+#    #+#             */
/*   Updated: 2022/06/27 12:13:59 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//runs through the main process
//(1) error check (i havent done bonuses so if argc isnt 5 it will throw an error (defined in my header file)), 
//(2) opens the files assocaited w infile (must exit), and opens (creates, truncates, read and write) outfile
//(3) function to populate the pipe and do everything else
int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc != 5)
		return (msg("Invalid number of arguments\n"));
	infile = open(argv[1], O_RDONLY);
	error_msg(infile);
	outfile = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	error_msg(outfile);
	populate_n_pipe(infile, outfile, argv, envp);
	return (0);
}

//populates the pipe and forks the processess
//(1) set a int array of [2] to create the pipe ends by assigning the ints in the array to the filedescriptors 
//(2) create the pipe and fork the process id to create adjacent processes
//(3) child: pid == 0 (will only run on one side of the fork)
//(4) parent: pid =/= 0 (will only run on one side of the fork)
int	populate_n_pipe(int infile, int outfile, char **argv, char **envp)
{
	int	filedes[2];
	int	pid;

	pipe(filedes);
	pid = fork();
	error_msg(pid);
	if (pid == 0)
	{
		child_process(infile, filedes);
		execute_cmds(argv[2], envp);
	}
	else
	{
		parent_process(outfile, filedes);
		execute_cmds(argv[3], envp);
	}
	return (0);
}

//function to build out the write end of the pipe and prepare things for the 1st command to be executed
void	child_process(int infile, int *filedes)
{
	error_msg(dup2(filedes[1], 1));  //sets filedes[1] as the STDOUT (so that the write end of the pipe is where the STDOUT of cmd 1 goes)
	error_msg(close(filedes[0])); //closes reading end of the pipe - otherwise execution will be suspeneded until something is read
	error_msg(dup2(infile, 0)); //sets infile as the STDIN (so that infile is the STDIN of cmd 1)
	error_msg(close(infile));
}

void	parent_process(int outfile, int *filedes)
{
	error_msg(waitpid(-1, NULL, 0)); //makes the parent process wait for its child to finish execution
	error_msg(dup2(filedes[0], 0)); //sets filedes[0] as the STDIN (so that the read end of the pipe is the STDIN for cmd 2)(which now holds the STDOUT of cmd 1)
	error_msg(close(filedes[1]));
	error_msg(dup2(outfile, 1)); //sets outfile as the STDOUT (so that outfile is the STDOUT of cmd 2)
	error_msg(close(outfile));
}
