/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:40:18 by oezzaou           #+#    #+#             */
/*   Updated: 2022/12/16 16:30:23 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int		ft_whos_first(char *s);
char	**ft_extract_paths(char **env);
char	*ft_get_cmd_path(char *cmd_name, char **paths);
char	**ft_extract_args(char *cmd);

t_cmd	*ft_extract_cmds(int ac, char **av, char **env, int is_hdoc)
{
	t_cmd	*cmds;
	int		i;
	char	**paths;
	t_file	*file;

	paths = ft_extract_paths(env);
	cmds = (t_cmd *) malloc(sizeof(t_cmd) * ac - 2);
	file = (t_file *) malloc(sizeof(t_file));
	if (!cmds || !paths || !file)
		return (0);
	i = -1;
	while (++i < ac - 3)
	{
		cmds[i].id = i + 1;
		cmds[i].args = ft_extract_args(av[i + 2]);
		cmds[i].name = (cmds[i].args)[0];
		cmds[i].path = ft_get_cmd_path(cmds[i].name, paths);
		if (!access(cmds[i].name, F_OK & X_OK) && ft_strchr(cmds[i].name, '/'))
			cmds[i].path = ft_strdup((cmds[i].args)[0]);
		cmds[i].files = file;
		cmds[i].hdoc = is_hdoc;
	}
	cmds[i].id = 0;
	ft_clear(0, 0, 0, paths);
	return (cmds);
}

int	ft_whos_first(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && s[i] != '\'' && s[i] != '"')
		;
	if (s[i])
		return ((int) s[i]);
	return (' ');
}

char	**ft_extract_args(char *cmd)
{
	char	sep;
	char	**args;
	char	*tmp;

	if (!access(cmd, F_OK & X_OK))
		return (ft_split(cmd, '\0'));
	sep = (int) ft_whos_first(cmd);
	args = ft_split(cmd, sep);
	tmp = args[0];
	args[0] = ft_strtrim(tmp, " ");
	free(tmp);
	if (ft_strrchr(args[0], '/') && !ft_strchr(args[0], '.'))
	{
		tmp = args[0];
		args[0] = ft_strdup((ft_strrchr(args[0], '/') + 1));
		free(tmp);
	}
	return (args);
}

char	*ft_get_cmd_path(char *cmd_name, char **paths)
{
	char	*path;
	char	*tmp;

	if (!paths)
		return (0);
	path = 0;
	cmd_name = ft_strjoin("/", cmd_name);
	while (*paths)
	{
		tmp = ft_strjoin(*paths++, cmd_name);
		if (!access(tmp, F_OK & X_OK) && !path)
			path = ft_strdup(tmp);
		free(tmp);
	}
	free(cmd_name);
	return (path);
}

char	**ft_extract_paths(char **env)
{
	while (env && *env && !ft_strnstr(*env, "PATH", 4))
		env++;
	if (env && *env)
		return (ft_split(ft_strchr(*env, '=') + 1, ':'));
	return (ft_split(PATH, ':'));
}
