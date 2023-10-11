/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:07:03 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/10/06 20:49:18 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		if (access(cmd, 0) == 0)
			return (cmd);
		tmp = ft_strnjoin(*paths, "/");
		command = ft_strnjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

char	**cmd_split(char *cmd)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '\"')
		{
			j = i + 1;
			while (cmd[j] != cmd[i] && cmd[j])
				j++;
			if (cmd[j])
			{
				cmd[i] = 26;
				cmd[j] = 26;
				i = j;
			}
		}
		else if (cmd[i] == ' ')
			cmd[i] = 26;
		i++;
	}
	return (ft_split(cmd, 26));
}

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.cmd_args = cmd_split(argv[2]);
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		msg_pipe(pipex.cmd_args[0]);
		child_free(&pipex);
		exit(127);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		exit(1);
	exit (0);
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.cmd_args = cmd_split(argv[3]);
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		msg_pipe(pipex.cmd_args[0]);
		child_free(&pipex);
		exit(127);
	}
	if (execve(pipex.cmd, pipex.cmd_args, envp) == -1)
		exit(1);
	exit (0);
}
