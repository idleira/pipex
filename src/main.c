/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibeliaie <ibeliaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 13:43:17 by ibeliaie          #+#    #+#             */
/*   Updated: 2023/10/06 20:52:47 by ibeliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	while (*envp != NULL && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (*envp == NULL)
		msg_self(ERR_ENVP);
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

int	parent2(t_pipex *pipex)
{
	int	status1;
	int	status2;
	int	error_code;

	error_code = 0;
	waitpid(pipex->pid1, &status1, 0);
	waitpid(pipex->pid2, &status2, 0);
	if (WIFEXITED(status1))
		error_code = WEXITSTATUS(status1);
	printf("status 1: %i\n", error_code);
	if (WIFEXITED(status2))
		error_code = WEXITSTATUS(status2);
	printf("status 2: %i\n", error_code);
	return (error_code);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		error_code;

	if (argc != 5)
		msg_self(ERR_INPUT);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		msg_perr(ERR_INFILE);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		msg_perr(ERR_OUTFILE);
	if (pipe(pipex.tube) < 0)
		msg_perr(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_pipes(&pipex);
	error_code = parent2(&pipex);
	parent_free(&pipex);
    exit(error_code);
}
