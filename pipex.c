#include "pipex.h"
/*
 *  fork() :
 * 			- The child process has a unique process ID
 * 			- The child process has a different parent process ID (i.e., the
 * 										.... process ID of the parent process).
 *
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

void	ft_exec(char **cmd, char **paths, int fd1, int fd2)
{
	int pid;
	int pid2;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork: ");
		ft_free(cmd);
		ft_free(paths);
		exit(EXIT_FAILURE);
	}
	else if (pid != 0)   /* parent process */
	{
		pid2 = fork();
		if (pid2 < 0)
		{
			perror("Fork: ");
			ft_free(cmd);
			ft_free(paths);
			exit(EXIT_FAILURE);
		}
		else if (pid2 == 0)
			ft_exc_cmd1(fd1, cmd, paths);
		else
		{
			//here the child 1 will exec
			printf("child \n");
		}
	}
	else // child
	{
		printf("this is parent \n");
	}
}

char	**get_paths(char **env, char **paths)
{
	int i;

	i = 0;
	paths = ft_split(env[i], ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

char 	**parsing(char **av, int ac, char **cmd)
{
	int j;
	int i;

	j = 2;
	i = 0;
	cmd = malloc(sizeof(char *) * 2);
	while (j < ac - 1)
	{
		cmd[i] = ft_strdup(av[j]);
		if (cmd[i] == NULL)
		{
			exit(EXIT_FAILURE);
		}
		i++;
		j++;
	}
	return cmd;
}

int	main(int ac, char *av[], char *evp[])
{
	int 	fd1;
	int 	fd2;
	char	**paths;
	char	**cmd;

	if (ac == 5)
	{
		cmd = parsing(av, ac, cmd);
		paths = get_paths(evp, paths);
		fd1 = open(av[0], O_RDONLY);
		fd2 = open(av[0], O_CREAT, O_RDWR);
		if (fd1 == -1 && fd2 == -1)
		{
			ft_free(cmd);
			free(paths);
			exit(EXIT_FAILURE);
		}
		ft_exec(cmd, paths, fd1, fd2);
	}
	else
	{
		perror("Error");
		return -1;
	}
	return (0);
}