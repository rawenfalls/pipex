/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:26:15 by marvin            #+#    #+#             */
/*   Updated: 2022/02/11 18:26:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_str
{
	int		fd[2];
	int		read_file;
	int		write_file;
	char	**cmd1;
	char	**cmd2;
}	t_str;

void	print_error(char *str);
void	parser_argv_envr(char **argv, t_str **pipex);
char	*cmdpath(char *str);
char	**cmd_str(char *argv, int i);

#endif
