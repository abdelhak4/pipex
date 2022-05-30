/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 07:03:03 by ael-mous          #+#    #+#             */
/*   Updated: 2022/05/07 07:03:05 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct s_cmd
{
	int		fd1;
	int		fd2;
	char	**paths;
	char	**cmd1;
	char	**cmd2;

	int		stat;
	int		re;
	int		fds[2];
	int		pid;
	int		pid2;
	char	**env;
}	t_cmd;

void	ft_exc_cmd1(t_cmd *cmd);
void	ft_exc_cmd2(t_cmd *cmd);
void	ft_free(char **str);
void	ft_err_pid(t_cmd *cmd);
void	_err_re(t_cmd *cmd);
void	ft_free(char **str);
void	_err_pid2(t_cmd *cmd);
char	**get_cmd1(char **av);
char	**get_cmd2(char **av);
void	my_perror2(t_cmd *cmd);
void	my_perror1(t_cmd *cmd);
void	_err_fd1(t_cmd *cmd, char **av);
void	_err_fd2(t_cmd *cmd, char **av);

#endif
