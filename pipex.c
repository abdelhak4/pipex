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

void	ft_exec(t_cmd *cmd)
{
	int i = 0;

	cmd->re = pipe(cmd->fds);
	if (cmd->re < 0)
	{
		ft_free(cmd->paths);
		ft_free(cmd->cmd1);
		ft_free(cmd->cmd2);
		perror("Pipe");
		exit(EXIT_FAILURE);
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("Fork: ");
		ft_free(cmd->paths);
		ft_free(cmd->cmd1);
		ft_free(cmd->cmd2);
		exit(EXIT_FAILURE);
	}
	/* child process 1*/
	else if (cmd->pid == 0)
	{
		ft_exc_cmd1(cmd);
	}
	cmd->pid2 = fork();
	if (cmd->pid2 < 0)
	{
		perror("Fork: ");
		ft_free(cmd->paths);
		ft_free(cmd->cmd1);
		ft_free(cmd->cmd2);
		exit(EXIT_FAILURE);
	}
	/* child process 2 */
	else if (cmd->pid2 == 0)
	{
		ft_exc_cmd2(cmd);
	}
	waitpid(cmd->pid, &cmd->stat, 0);
	waitpid(cmd->pid2, &cmd->stat, 0);
	printf("this is parent \n");
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
		cmd->paths = get_paths(evp);
		cmd->fd1 = open(av[1], O_RDONLY);
		cmd->fd2= open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (cmd->fd1 == -1 && cmd->fd2 == -1)
		{
			perror("open");
			ft_free(cmd->cmd1);
			free(cmd->paths);
			exit(EXIT_FAILURE);
		}
		ft_exec(cmd);
	}
	else
	{
		perror("Error");
		return -1;
	}
	return (0);
}