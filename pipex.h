/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoore <imoore@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:08:15 by imoore            #+#    #+#             */
/*   Updated: 2022/06/27 12:33:53 by imoore           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* to write, read, close, access, pipe, dup2, execve, fork */
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

/* malloc, free, exit */
# include <stdlib.h>

/* open*/
# include <fcntl.h>

/* waitpid*/
# include <sys/wait.h>

/* strerror */
# include <string.h>

/*perror*/
# include <stdio.h>

# include <errno.h>

# define ERR_INPUT "Invalid number of arguments.\n"
# define ERR_CMD "Command not found:"

//process functions//
void	child_process(int infile, int *filedes);
void	parent_process(int outfile, int *filedes);

/* error.c */
int		error_msg(int errnum);
int		msg(char *err);
int		msg_variable(char *err, char *entered);

//main//
int		populate_n_pipe(int infile, int outfile, char **argv, char **envp);
char	*find_path(char **envp);
char	*get_cmd_path(char **paths, char *cmd);
void	execute_cmds(char *agrv, char **envp);

/* funcions */
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *src);
char	**ft_split(char const *s, char c);
int		ft_strlen(const char *r);
int		ft_strncmp(const char *s1, char *s2, size_t n);

#endif
