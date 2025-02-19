/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 13:08:45 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/16 18:17:45 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	*cmds;
	int		*pipes;
	int		status;
	int		inout_fd[2];
	int		is_here_doc;

	if (ac <= 4)
		return (EXIT_FAILURE);
	pipes = NULL;
	is_here_doc = (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1])));
	pipes = ft_manage_pipes(pipes, ac - 3, PIPE);
	if (is_here_doc)
		av = ft_here_doc(ac--, av, pipes);
	cmds = ft_extract_cmds(ac, av, env, is_here_doc);
	if (!cmds)
		return (EXIT_FAILURE);
	cmds->files->infile = av[1];
	cmds->files->outfile = av[ac - 1];
	cmds->files->ncmds = ac - 3;
	get_inout_files(cmds, &inout_fd[0]);
	ft_exec_cmds(cmds, env, pipes, inout_fd);
	ft_close_all_fd(cmds, pipes, inout_fd);
	ft_wait_child_ps(cmds, &status);
	ft_clear(cmds, pipes, av, 0);
	return (*((char *) &status + 1));
}

void	ft_wait_child_ps(t_cmd *cmds, int *status)
{
	while (cmds->id)
		if (waitpid((*cmds++).pid, status, 0) == -1)
			exit(EXIT_FAILURE);
}

int	get_inout_files(t_cmd *cmds, int *inout_fd)
{
	int		flag;
	char	*tmp;

	tmp = ft_strjoin("pipex: ", cmds->files->infile);
	flag = O_APPEND * (cmds->hdoc) + O_TRUNC * (!cmds->hdoc);
	inout_fd[1] = open(cmds->files->outfile, O_CREAT | O_WRONLY | flag, 0644);
	if (inout_fd[1] == -1)
		exit(EXIT_FAILURE);
	if (access(cmds->files->infile, F_OK | R_OK) && !cmds->hdoc)
		perror(tmp);
	if (!cmds->hdoc)
		inout_fd[0] = open(cmds->files->infile, O_RDONLY);
	free(tmp);
	return (0);
}

int	ft_exec_cmds(t_cmd *cmds, char **env, int *pipes, int *inout_fd)
{
	while (cmds->id)
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			perror("Error creating child process \n");
		if (cmds->pid == 0)
		{
			if (cmds->id == 1 && inout_fd[0] == -1)
				return (EXIT_FAILURE);
			if (cmds->id == 1 && inout_fd[0] != -1)
				dup2(inout_fd[0] * !cmds->hdoc + (pipes[0] * cmds->hdoc), 0);
			if (cmds->id > 1)
				dup2(pipes[2 * (cmds->id - 1) - (2 * (!cmds->hdoc))], 0);
			if (cmds->id < cmds->files->ncmds)
				dup2(pipes[2 * (cmds->id - 1) + 1 + (2 * cmds->hdoc)], 1);
			if (cmds->id == cmds->files->ncmds)
				dup2(inout_fd[1], 1);
			ft_close_all_fd(cmds, pipes, inout_fd);
			if (execve(cmds->path, cmds->args, env) == -1)
				exit (ft_print_err_msg(cmds));
		}
		cmds++;
	}
	return (0);
}

int	*ft_manage_pipes(int *pipes, int ncmds, int flag)
{
	int	i;

	if (flag == PIPE)
		pipes = malloc(sizeof(int) * (2 * ncmds - 2));
	if (!pipes)
		exit(EXIT_FAILURE);
	i = -1;
	while (flag == PIPE && ++i < 2 * ncmds - 2)
		pipe(&pipes[i++]);
	i = -1;
	while (flag == CLOSE && ++i < 2 * ncmds - 2)
		close(pipes[i]);
	return (pipes);
}
