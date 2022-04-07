#include "pipex.h"

char	*check_access_of_cmd(char **cmd, char **paths)
{
	char	*full_path;
	int 	i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd[1]);
		if (access(full_path, F_OK) == 0)
			return full_path;
		else
			free(full_path);
		i++;
	}
	return (NULL);
}
void	ft_exc_cmd1(int fd1, char **cmd, char **paths)
{
	char	*path;

	path = check_access_of_cmd(cmd, paths);
	if (path == NULL)
	{
		ft_free(paths);
		perror("Err");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%s\n", path);
	}
}