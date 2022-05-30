/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 07:02:47 by ael-mous          #+#    #+#             */
/*   Updated: 2022/05/07 07:02:49 by ael-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
 *  fork() :
 * 			- The child process has a unique process ID
 * 			- The child process has a different parent process ID (i.e., the
 * 										.... process ID of the parent process).
 *		Todo: check return of split is not null ?
 *		!protect execve
 */

void	parent(t_cmd *cmd)
{
	close(cmd->fds[0]);
	close(cmd->fds[1]);
	waitpid(-1, &cmd->stat, 0);
	//waitpid(-1, &cmd->stat, 0);
}

int	ft_strline(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	return (i);
}

char	**get_paths(char **env)
{
	char	*path_paths;
	char	**tmp;
	char	**paths;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		i++;
	path_paths = ft_strnstr(env[i], "PATH=", 5);
	i = 0;
	paths = ft_split(path_paths, ':');
	tmp = malloc(sizeof(char *) * (ft_strline(paths) + 1));
	while (paths[i])
	{
		tmp[i] = ft_strjoin(paths[i], "/");
		free(paths[i]);
		i++;
	}
	free (paths);
	tmp[i] = 0;
	return (tmp);
}

void	ft_exec(t_cmd *cmd, char **av)
{
	cmd->re = pipe(cmd->fds);
	if (cmd->re < 0)
		_err_re(cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_err_pid(cmd);
	else if (cmd->pid == 0)
	{
		cmd->fd1 = open(av[1], O_RDONLY);
		if (cmd->fd1 == -1)
			_err_fd1(cmd, av);
		ft_exc_cmd1(cmd);
	}
	cmd->pid2 = fork();
	if (cmd->pid2 < 0)
		_err_pid2(cmd);
	else if (cmd->pid2 == 0)
	{
		cmd->fd2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd->fd2 == -1)
			_err_fd2(cmd, av);
		ft_exc_cmd2(cmd);
	}
	parent(cmd);
}

int	main(int ac, char *av[], char *evp[])
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (ac == 5)
	{
		cmd->env = evp;
		cmd->cmd1 = get_cmd1(av);
		cmd->cmd2 = get_cmd2(av);
		cmd->paths = get_paths(evp);
		ft_exec(cmd, av);
	}
	else
	{
		perror("Error");
		return (-1);
	}
	return (0);
}
