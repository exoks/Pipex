/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 08:19:37 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/16 18:18:04 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	ft_print_err_msg(t_cmd *cmds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Error \n");
	if (pid == 0)
	{
		dup2(2, 1);
		if (!cmds->path && ft_strnstr(cmds->name, "./", ft_strlen(cmds->name)))
			exit (ft_printf("pipex: %s: %s\n", N_FILE, cmds->name));
		if (!ft_strnstr(cmds->name, "./", ft_strlen(cmds->name)))
			ft_printf("pipex: %s: %s\n", cmds->name, NOT_FOUND);
		if (!access(cmds->name, F_OK) && access(cmds->name, X_OK)
			&& ft_strnstr(cmds->name, "./", ft_strlen(cmds->name)))
			ft_printf("pipex: %s: %s\n", P_DENIED, cmds->name);
	}
	if (!access(cmds->name, F_OK) && access(cmds->name, X_OK)
		&& ft_strnstr(cmds->name, "./", ft_strlen(cmds->name)))
		return (PERMISSION_DENIED);
	return (EXIT_ERROR);
}

void	ft_clear(t_cmd *cmds, int *pipes, char **av, char **paths)
{
	int	i;
	int	j;

	if (cmds)
		free(cmds->files);
	if (cmds && cmds->hdoc)
		free(av);
	i = -1;
	while (cmds && cmds[++i].id)
	{
		free(cmds[i].path);
		j = -1;
		while ((cmds[i].args)[++j])
			free((cmds[i].args)[j]);
		free(cmds[i].args);
	}
	i = -1;
	while (paths && paths[++i])
		free(paths[i]);
	free(pipes);
	free(paths);
	free(cmds);
}

void	ft_close_all_fd(t_cmd *cmds, int *pipes, int *inout_fd)
{
	ft_manage_pipes(pipes, cmds->files->ncmds + cmds->hdoc, CLOSE);
	ft_manage_pipes(inout_fd, 2, CLOSE);
}
