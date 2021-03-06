/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:14:24 by ael-mous          #+#    #+#             */
/*   Updated: 2022/04/10 17:14:26 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access_of_cmd2(char **cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd[0]);
		if (access(full_path, F_OK) == 0)
		{
			return (full_path);
		}
		else
		{
			free(paths[i]);
			free(full_path);
		}
		i++;
	}
	if (ft_strnstr(cmd[0], "./", 2) != NULL
		|| ft_strnstr(cmd[0], "/", 1) != NULL)
	{
		if (access(cmd[0], R_OK & W_OK & X_OK) == 0)
			return (cmd[0]);
	}
	return (NULL);
}

void	ft_exc_cmd2(t_cmd *cmd)
{
	char	*path;

	if (cmd->cmd2[0] == NULL)
		my_perror2(cmd);
	path = check_access_of_cmd2(cmd->cmd2, cmd->paths);
	if (path == NULL)
	{
		perror(cmd->cmd2[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmd->fds[1]);
		close(cmd->fd1);
		dup2(cmd->fd2, STDOUT_FILENO);
		dup2(cmd->fds[0], STDIN_FILENO);
		if (execve(path, cmd->cmd2, cmd->env) == -1)
			perror(cmd->cmd2[0]);
	}
}
