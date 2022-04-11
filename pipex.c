#include "pipex.h"
/*
 *  fork() :
 * 			- The child process has a unique process ID
 * 			- The child process has a different parent process ID (i.e., the
 * 										.... process ID of the parent process).
 *		Todo: check return of split is not null ?
 */

void	ft_free(char **str)
{
	int i;

	i = 0;

	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

char	**get_paths(char **env)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(env[i], ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

void	ft_exec(t_cmd *cmd, char **env)
{
	cmd->re = pipe(cmd->fds);
	if (cmd->re < 0)
		_err_re(cmd);
	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_err_pid(cmd);
	else if (cmd->pid == 0)
		ft_exc_cmd1(cmd, env);
	cmd->pid2 = fork();
	if (cmd->pid2 < 0)
		_err_pid2(cmd);
	else if (cmd->pid2 == 0)
		ft_exc_cmd2(cmd, env);

	close(cmd->fds[0]);
	close(cmd->fds[1]);
	waitpid(-1, &cmd->stat, 0);
	waitpid(-1, &cmd->stat, 0);
}

char 	**get_cmd2(char **av)
{
	char **cmd2;

	cmd2 = ft_split(av[3], ' ');
	return cmd2;
}

char 	**get_cmd1(char **av)
{
	char **cmd;

	cmd = ft_split(av[2], ' ');
	return cmd;
}

int	main(int ac, char *av[], char *evp[])
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (ac == 5)
	{
		cmd->cmd1 = get_cmd1(av);
		cmd->cmd2 = get_cmd2(av);
		if (cmd->cmd1 == NULL || cmd->cmd2 == NULL)
		{
			perror("Err");
			ft_free(cmd->cmd1);
			ft_free(cmd->cmd2);
			free(cmd);
			exit(EXIT_FAILURE);
		}
		cmd->paths = get_paths(evp);
		cmd->fd1 = open(av[1], O_RDONLY);
		cmd->fd2= open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd->fd1 == -1 && cmd->fd2 == -1)
		{
			perror("open");
			ft_free(cmd->cmd1);
			ft_free(cmd->cmd2);
			ft_free(cmd->paths);
			free(cmd);
			exit(EXIT_FAILURE);
		}
		ft_exec(cmd, evp);
	}
	else
	{
		perror("Error");
		return -1;
	}
	return (0);
}