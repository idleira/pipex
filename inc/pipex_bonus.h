/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:04:27 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/10/11 16:19:42 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
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
# define ERR_HEREDOC "Error: Invalid use of here document."
# define ERR_EXECVE "Error: Execution of command failed."

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	*env_path;
	char	**cmd_paths;
	char	*cmd;
	char	**cmd_args;
	int		here_doc;
	pid_t	pid[2];
	int		cmd_nmbs;
	int		count;
	int		pipe_nmbs;
	int		idx;
	int		tube[2][2];
	char	*paths;
}	t_pipex;

int		get_next_line(char **line);
void	main_cycle(t_pipex pipex, char *argv[], char *envp[]);

void	child(t_pipex pipex, char *argv[], char *envp[]);

void	close_pipes(t_pipex *pipex);
void	parent_free(t_pipex *pipex);
void	child_free(t_pipex *pipex);
void	pipe_free(t_pipex *pipex);

void	msg_pipe(char *arg);
void	msg_self(char *err);
void	msg_perr(char *err);

char	*find_path(char **envp);
void	get_infile(char **argv, t_pipex *pipex);
void	get_outfile(char *argv, t_pipex *pipex);
int		args_in(char *arg, t_pipex *pipex);
void	here_doc(char *argv);

char	**cmd_split(char *cmd);

#endif