#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	pid_t	pid;
	int	fd[3][2];
	int	i;

	i = -1;
	while (++i < 3)
		pipe(fd[i]);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0][0]);
		close(fd[1][0]);
		close(fd[1][1]);
		close(fd[2][0]);
		close(fd[2][1]);
		dup2(fd[0][1], 1);
		close(fd[0][1]);
		execve("/bin/cat", ft_split("cat file1", " "), env);	
	}
	pid_t p = fork();
	if (p == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		dup2(fd[0][0], 0);
		dup2(fd[1][1], 1);
		close(fd[0][1]);
		close(fd[1][1]);
		execve("/bin/cat", ft_split("cat -e", " "), env);
	}
	pid_t pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		close(fd[2][1]);
		dup2(fd[1][0], 0);
		close(fd[1][0]);
		execve("/usr/bin/tee", ft_split("tee file2", " "), env);
	}
//	waitpid(&pid, 0, NULL);
//	waitpid(&p, 0, NULL);
//	waitpid(&pid1, 0, NULL);
	return (0);
}
