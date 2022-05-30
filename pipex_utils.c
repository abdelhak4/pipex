/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:19:00 by ael-mous          #+#    #+#             */
/*   Updated: 2022/04/11 15:19:03 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_err_pid(t_cmd *cmd)
{
	perror("Fork: ");
	ft_free(cmd->paths);
	ft_free(cmd->cmd1);
	ft_free(cmd->cmd2);
	exit(EXIT_FAILURE);
}

void	ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

void	my_perror1(t_cmd *cmd)
{
	perror("execve");
	ft_free(cmd->cmd1);
	exit(EXIT_FAILURE);
}

void	_err_re(t_cmd *cmd)
{
	ft_free(cmd->paths);
	ft_free(cmd->cmd1);
	ft_free(cmd->cmd2);
	perror("Pipe");
	exit(EXIT_FAILURE);
}

void	_err_pid2(t_cmd *cmd)
{
	perror("Fork: ");
	ft_free(cmd->paths);
	ft_free(cmd->cmd1);
	ft_free(cmd->cmd2);
	exit(EXIT_FAILURE);
}
