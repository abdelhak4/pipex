/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 07:12:36 by ael-mous          #+#    #+#             */
/*   Updated: 2022/05/07 07:12:38 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd1(char **av)
{
	char	**cmd;

	cmd = ft_split(av[2], ' ');
	return (cmd);
}

char	**get_cmd2(char **av)
{
	char	**cmd2;

	cmd2 = ft_split(av[3], ' ');
	return (cmd2);
}

void	my_perror2(t_cmd *cmd)
{
	perror("bash");
	ft_free(cmd->cmd1);
	ft_free(cmd->cmd2);
	free(cmd);
	exit(EXIT_FAILURE);
}

void	_err_fd1(t_cmd *cmd, char **av)
{
	perror(av[0]);
	ft_free(cmd->cmd1);
	exit(EXIT_FAILURE);
}

void	_err_fd2(t_cmd *cmd, char **av)
{
	perror(av[4]);
	ft_free(cmd->cmd2);
	exit(EXIT_FAILURE);
}
