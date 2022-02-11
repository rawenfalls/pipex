/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:28:31 by marvin            #+#    #+#             */
/*   Updated: 2022/02/11 23:28:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**cmd_str(char *argv, int i)
{
	char	**str;
	int		e;

	str = (char **)malloc(sizeof(char *) * 3);
	if (!str)
		print_error("ERROR: malloc");
	str[0] = malloc(sizeof(char) * 20);
	str[1] = malloc(sizeof(char) * 20);
	if (!str[1] || !str[0])
		print_error("ERROR: malloc");
	str[2] = NULL;
	while (argv[i] != ' ' && argv[i])
	{
		str[0][i] = argv[i];
		i++;
	}
	str[0][i] = '\0';
	e = i + 1;
	while (argv[++i] && argv[e - 1] == ' ')
		str[1][i - e] = argv[i];
	str[1][i - e] = '\0';
	return (str);
}

static void	child1(t_str *pipex, char *cmd)
{
	dup2(pipex->read_file, STDIN_FILENO);
	dup2(pipex->fd[1], STDOUT_FILENO);
	close(pipex->read_file);
	close(pipex->write_file);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execve(cmd, pipex->cmd1, NULL);
	print_error("ERROR: execve in child1");
}

static void	child2(t_str *pipex, char *cmd)
{
	dup2(pipex->fd[0], STDIN_FILENO);
	dup2(pipex->write_file, STDOUT_FILENO);
	close(pipex->read_file);
	close(pipex->write_file);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	execve(cmd, pipex->cmd2, NULL);
	print_error("ERROR: execve in child1");
}

static void	fork_proces(t_str *pipex)
{
	int		pid[2];
	char	*cmd;

	if (pipe(pipex->fd) == -1)
		print_error("ERROR: pipe - FAILED\n");
	pid[0] = fork();
	if (pid[0] < 0)
		print_error("ERROR: fork first - FAILED\n");
	cmd = cmdpath(pipex->cmd1[0]);
	if (pid[0] == 0)
		child1(pipex, cmd);
	free(cmd);
	cmd = cmdpath(pipex->cmd2[0]);
	pid[1] = fork();
	if (pid[1] < 0)
		print_error("ERROR: fork first - FAILED\n");
	if (pid[1] == 0)
		child2(pipex, cmd);
	free(cmd);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	close(pipex->read_file);
	close(pipex->write_file);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

int	main(int argc, char *argv[])
{
	t_str	*pipex;

	pipex = (t_str *)malloc(sizeof(t_str));
	if (!pipex)
		print_error("ERROR: malloc can't create a structure\n");
	if (argc != 5)
		print_error("ERROR: wrong number of input parameters\n");
	else
		parser_argv_envr(argv, &pipex);
	fork_proces(pipex);
	free(pipex->cmd1[0]);
	free(pipex->cmd1[1]);
	free(pipex->cmd1);
	free(pipex->cmd2[0]);
	free(pipex->cmd2[1]);
	free(pipex->cmd2);
	close(pipex->read_file);
	close(pipex->write_file);
	free(pipex);
	return (0);
}
