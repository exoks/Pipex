/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:49:16 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/15 22:03:11 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

t_cmd	*ft_extract_cmds(int ac, char **av, t_cmd *cmds);
void	write_to_pipe(char *path, int fdp);
void	ft_exec_cmds(t_cmd *cmds, char **env, int *fd);

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	char	*f_content;
	t_cmd	*cmds;

	cmds = 0;
	if (ac < 4)
		return (0);
	pipe(fd);
	write_to_pipe(av[1], fd[1]);
	cmds = ft_extract_cmds(ac, av, cmds);
	while (cmds)
	{
		ft_exec_cmds(cmds, env, fd);
		cmds = cmds->next;
	}
	char	buff[100];
	read(fd[0], buff, 100);
	printf("buff :==> %s\n", buff);
	return (0);
}

void	ft_exec_cmds(t_cmd *cmds, char **env, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return;
	if (pid == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		execve("/bin/cat", cmds->options, env);
	}
}

void	write_to_pipe(char *path, int fdp)
{
	char	buff[200];
	int	fd;
	int	re;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return;
	re = read(fd, buff, 200);
	if (re == -1)
		exit(0);
	write(fdp, buff, 200);
	close(fd);
}

t_cmd	*ft_extract_cmds(int ac, char **av, t_cmd *cmds)
{
	int	i;
	t_cmd	*tmp;

	i = 2;
	while (i < ac - 1)
	{
		if(cmds)
		{
			tmp = ft_lstlast(cmds);
			tmp->next = ft_lstnew(av[i]);
			if (!(tmp->next))
			{
				//ft_lstclear();
				return (0);
			}
		}
		else
			cmds = ft_lstnew(av[i]);
		i++;
	}
	return (cmds);
}
/*
int	main(int ac, char **av)
{
	t_cmd	*lst;

	lst = 0;
	lst = ft_extract_cmds(ac, av, lst);
	while (lst)
	{
		printf("============================\n");
		printf("NAME ::::> %s\n", lst->cmd_name);
		while(*(lst->options))
			printf("===> %s\n", *(lst->options++));
		lst = lst->next;
	}
	return (0);
}
*/
