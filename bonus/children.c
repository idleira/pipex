/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:07:03 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/10/13 17:05:33 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

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

void	child(t_pipex pipex, char *argv[], char *envp[])
{
	if (pipex.count > 0)
	{
		if (pipex.count + 1 == pipex.cmd_nmbs)
			dup2(pipex.outfile, STDOUT_FILENO);
		dup2(pipex.tube[-(pipex.count % 2) + 1][0], STDIN_FILENO);
		close(pipex.tube[-(pipex.count % 2) + 1][1]);
	}
	if (pipex.count + 1 < pipex.cmd_nmbs)
	{
		if (pipex.count == 0)
			dup2(pipex.infile, STDIN_FILENO);
		dup2(pipex.tube[pipex.count % 2][1], STDOUT_FILENO);
		close(pipex.tube[pipex.count % 2][0]);
	}
	pipex.cmd_args = cmd_split(argv[pipex.count + 2 + pipex.here_doc]);
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		msg_pipe(pipex.cmd_args[0]);
		child_free(&pipex);
		exit(1);
	}
	execve(pipex.cmd, pipex.cmd_args, envp);
}
