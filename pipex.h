#ifndef PIPEX_H
#define PIPEX_H
# include <unistd.h>
# include "libft/libft.h"
# include <sys/wait.h>
# include <stdio.h>
#include <fcntl.h>

typedef struct s_cmd
{
	char *cmd1;
	char *cmd2;
}	t_cmd;

void	ft_exc_cmd1(int fd1, char **cmd, char **paths);
void	ft_free(char **str);
#endif