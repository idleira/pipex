/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:03:54 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/10/06 20:32:34 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

# define ERR_INFILE "Error: Missing or invalid input file."
# define ERR_OUTFILE "Error: Missing or invalid output file."
# define ERR_CMD "Error: Command not found: "
# define ERR_PIPE "Error: Pipe creation failed."
# define ERR_ENVP "Error: Environment setup failed."
# define ERR_INPUT "Error: Invalid number of arguments."

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	int		infile;
	int		outfile;
	char	*paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}	t_pipex;

void	first_child(t_pipex pipex, char *argv[], char *envp[]);
void	second_child(t_pipex pipex, char *argv[], char *envp[]);

void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
int		parent2(t_pipex *pipex);

void	msg_pipe(char *arg);
void	msg_self(char *err);
void	msg_perr(char *err);

char	**cmd_split(char *cmd);
char	*find_path(char **envp);

#endif