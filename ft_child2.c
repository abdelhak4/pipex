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
	int 	i;

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
	return (cmd[0]);
}

void	ft_exc_cmd2(t_cmd *cmd, char **env)
{
	char	*path;

	path = check_access_of_cmd2(cmd->cmd2, cmd->paths);
	ft_free(cmd->paths);
	if (path == NULL)
	{
		perror(cmd->cmd2[0]);
		ft_free(cmd->paths);
		ft_free(cmd->cmd2);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(cmd->fds[1]);
		dup2(cmd->fd2, STDOUT_FILENO);
		dup2(cmd->fds[0], STDIN_FILENO);
		close(cmd->fd1);
		execve(path, cmd->cmd2, env);
	}
}