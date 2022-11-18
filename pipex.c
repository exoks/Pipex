/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:49:16 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/18 15:52:36 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

t_cmd	*ft_extract_cmds(int ac, char **av, t_cmd *cmds);
void	write_to_pipe(char *path, int fdp);
void	ft_exec_cmds(t_cmd *cmds, char **env, int *fd);
void	ft_print_cmds(t_cmd *cmds);

// FINALY I DID IT
int	main(int ac, char **av, char **env)
{
	int	fd[2 * (ac - 1)];
	t_cmd	*cmds;
	int	i;
	pid_t	pid;

	printf("num of pipes : %d\n", 2 * (ac - 1));
	cmds = 0;
	if (ac < 4)
		return (0);
	i = 0;
	while (i < 2 * (ac - 1))
	{
		pipe(&fd[i]);
		i += 2;
	}
	cmds = ft_extract_cmds(ac, av, cmds);
//	ft_print_cmds(cmds);
	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == -1)
			perror("nbag \n");
		if (pid == 0)
		{
			// Child Process
			// first command
			if (cmds->id > 1)
				dup2(fd[(i * 2) - 2], 0);
			//last command
			if (cmds->id < ac - 1)
				dup2(fd[(2 * i) + 1], 1);
			//close all filedescriptor
			int j = 0;
			while (j < 2 * (ac - 1))
				close(fd[j++]);
			// execve the command
			execve(cmds->path, cmds->options, env);
		}
		i++;
		cmds = cmds->next;
	}
/*	printf("count :=> %d\n", ac - 1);
	i = -1;
	while (++i < ac - 1)
	{
		printf("i|=> %d\n", i * 2);
		printf("+1\n");
		pipe(&fd[i * 2]);
	}
	i = 0;
	while (cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			// first command (ignoring the first command)
			if (i > 0)
			{
				dup2(fd[(i * 2) - 2], 0);
				close(fd[(i * 2) - 2]);
			}
			// last comamnd (ignoring the last command)
			if (i < ac - 2)
			{
				dup2(fd[(i * 2) + 1], 1);
				close(fd[(i * 2) + 1]);
			}
			int j = -1;
			while (++j < ac - 2)
				close(fd[j]);		
			execve(cmds->path, cmds->options, env);
		}
		wait(0);
		cmds = cmds->next;
		i++;
	}*/
/*	while (i < ac - 1)
	{
		pipe(fd + (2 * i));
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			printf("(%s)-> fd[%d] <=|=> fd[%d]\n",cmds->cmd_name, i, i + 1);
			dup2(fd[i], 0);
			//if ()
			//{
				dup2(fd[i + 1], 1);
				close(fd[i + 1]);
			//}
			close(fd[i]);
			execve(cmds->path, cmds->options, env);
		}
		wait(0);
		cmds = cmds->next;
		i++;
	}
	close(fd[0]);
	close(fd[1]);*/
	return (0);
}
void	ft_print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("==============================\n");
		printf("ID --> %d\n", cmds->id);
		printf("NAME ::> %s\n", cmds->name);
		printf("PATH ==> %s\n", cmds->path);
		while (*(cmds->options))
			printf("= : %s\n", *(cmds->options)++);
		cmds = cmds->next;
	}
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

	i = 1;
	while (i < ac)
	{
		if(cmds)
		{
			tmp = ft_lstlast(cmds);
			tmp->next = ft_lstnew(av[i], i, ac);
			if (!(tmp->next))
			{
				//ft_lstclear();
				return (0);
			}
		}
		else
			cmds = ft_lstnew(av[i], i, ac);
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
