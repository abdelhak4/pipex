#include "pipex.h"

char	*check_access_of_cmd(char **cmd, char **paths)
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
	return (NULL);
}
void	ft_exc_cmd1(t_cmd *cmd, char **env)
{
	char	*path;

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
		close(cmd->fd2);
		execve(path, cmd->cmd1, env);
	}
}