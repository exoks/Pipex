/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:49:58 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/18 01:34:58 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct 		s_cmd
{
	int		id;
	char		*name;
	char		**options;
	char		*path;
	struct s_cmd	*next;
}			t_cmd;

t_cmd	*ft_lstlast(t_cmd *cmds);
t_cmd	*ft_lstnew(char *cmd_n, int index, int ac);
char	**ft_split(char *s, char *set);
char	*ft_strjoin(char *s1, char *s2);
# endif
