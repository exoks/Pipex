/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:54:11 by oezzaou           #+#    #+#             */
/*   Updated: 2022/11/18 01:39:04 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

t_cmd	*ft_lstlast(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->next == 0)
			return (cmds);
		cmds = cmds->next;
	}
	return (0);
}

t_cmd   *ft_lstnew(char *cmd_n, int index, int ac)
{
        t_cmd   *cmds;
	char	**tab;

	tab = ft_split(cmd_n, " ");
        cmds = (t_cmd *) malloc(sizeof(t_cmd));
        if (!cmds)
                return (0);
	if (index == 1)
	{
		cmds->id = index;
		cmds->name = "cat";
		cmds->path = "/bin/cat";
		cmds->options = ft_split(ft_strjoin("cat ", tab[0]), " ");
	}
	else if (index == ac - 1)
	{
		cmds->id = index;
		cmds->name = "tee";
		cmds->path = "/usr/bin/tee";
		cmds->options = ft_split(ft_strjoin("tee ", tab[0]), " ");
	}
	else
	{
		cmds->id = index;
        	cmds->name = tab[0];
        	cmds->options = tab;
		cmds->path = ft_strjoin("/bin/", tab[0]);
        	cmds->next = 0;
	}
	return (cmds);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*s;

	if (!s1 || !s2)
		return (0);
	i = -1;
	while (s1[++i])
		;
	j = -1;
	while (s2[++j])
		;
	s = (char *) malloc(i + j + 1);
	if (!s)
		return (0);
	i = 0;
	while (*s1)
		s[i++] = *(s1++);
	while (*s2)
		s[i++] = *(s2++);
	s[i] = 0;
	return (s);
}

int	ft_is_exist(char s, char *set)
{
	while (*set && *set != s)
		set++;
	if (*set)
		return (1);
	return (0);
}

int	ft_word_counter(char *s, char *set)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (s[++i])
	{
		if (!ft_is_exist(s[i], set) && (ft_is_exist(s[i + 1], set) || s[i + 1] == 0))
			counter++;
	}
	return (counter);
}

int	ft_strlen(char *s, char *set)
{
	if (*s && !ft_is_exist(*s, set))
		return (1 + ft_strlen(++s, set));
	return (0);
}

int	ft_strcpy(char *dst, char *src, char *set)
{
	int	i;

	i = -1;
	while (src[++i] && !ft_is_exist(src[i], set))
		dst[i] = src[i];
	dst[i] = 0;
	return (i);
}

char	**ft_split(char *s, char *set)
{
	char	**tab;
	int	i;
	int	k;

	if (!s || !set)
		return (0);
	tab = malloc(sizeof(char *) * (ft_word_counter(s, set) + 1));
	if (!tab)
		return (0);
	i = 0;
	k = 0;
	while (s[i])
	{
		while (ft_is_exist(s[i], set))
			i++;
		if (s[i])
		{
			tab[k] = malloc(ft_strlen(&s[i], set) + 1);
			if (!tab[k])
				return (0);
			i += ft_strcpy(tab[k++], &s[i], set);
		}
	}
	tab[k] = 0;
	return (tab);
}
/*
int	main(int ac, char **av)
{
	printf("-----> %s\n", ft_strjoin(av[1], av[2]));
	return (0);
}*/
