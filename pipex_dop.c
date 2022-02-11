/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_dop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 23:34:20 by marvin            #+#    #+#             */
/*   Updated: 2022/02/11 23:34:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	exit (1);
}

void	parser_argv_envr(char **argv, t_str **pipex)
{
	int		file;

	file = open(argv[1], O_RDONLY);
	if (file == -1)
		print_error("ERROR: can't open file\n");
	(*pipex)->read_file = dup(file);
	close(file);
	file = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (file == -1)
		print_error("ERROR: can't write or create file\n");
	(*pipex)->write_file = dup(file);
	close(file);
	(*pipex)->cmd1 = cmd_str(argv[2], 0);
	(*pipex)->cmd2 = cmd_str(argv[3], 0);
}

char	*cmdpath(char *str)
{
	char	*cmd;
	char	*ret_str;
	int		i;
	int		e;

	cmd = "/bin/";
	i = -1;
	ret_str = (char *)malloc(sizeof(char) * 100);
	if (!ret_str)
		print_error("ERROR: malloc\n");
	while (cmd[++i])
		ret_str[i] = cmd[i];
	e = i;
	while (str[i - e])
	{
		ret_str[i] = str[i - e];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}
