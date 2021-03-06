/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_child.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 07:01:20 by ael-mous          #+#    #+#             */
/*   Updated: 2022/05/07 07:01:25 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access_of_cmd(char **cmd, char **paths)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd[0]);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		else
			free(full_path);
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

void	ft_exc_cmd1(t_cmd *cmd)
{
	char	*path;

	if (cmd->cmd1[0] == NULL)
		my_perror1(cmd);
	path = check_access_of_cmd(cmd->cmd1, cmd->paths);
	if (path == NULL)
	{
		ft_free(cmd->paths);
		perror(cmd->cmd1[0]);
		ft_free(cmd->cmd1);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmd->fds[0]);
		dup2(cmd->fd1, STDIN_FILENO);
		dup2(cmd->fds[1], STDOUT_FILENO);
		if (execve(path, cmd->cmd1, cmd->env) == -1)
		{
			perror(cmd->cmd1[0]);
			exit(EXIT_FAILURE);
		}
	}
}
