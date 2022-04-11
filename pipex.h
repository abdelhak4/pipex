#ifndef PIPEX_H
#define PIPEX_H
# include <unistd.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
#include <fcntl.h>

typedef struct s_cmd
{
	int 	fd1;
	int 	fd2;
	char	**paths;
	char	**cmd1;
	char	**cmd2;

	int		stat;
	int re;
	int	fds[2];
	int pid;
	int pid2;
}	t_cmd;

void	ft_exc_cmd1(t_cmd *cmd);
void	ft_exc_cmd2(t_cmd *cmd);
void	ft_free(char **str);
#endif