/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:01:16 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/10 13:09:18 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ Prototypes: ]>=========================================================
static int	ft_skip_rep(char *s, char c);

//====<[ ft_manage_flags: ]>====================================================
int	ft_manage_flags(char *s, t_data *data)
{
	int	i;
	int	nb;

	nb = 0;
	i = -1;
	if (ft_strchr("+- #0", s[++i]))
		data->flag = s[i];
	i += ft_skip_rep(&s[i], data->flag);
	while (ft_isdigit(s[i]))
		nb = (nb * 10) + (s[i++] - '0');
	data->width = nb;
	nb = 0;
	if (s[i] == '.')
	{
		while (ft_isdigit(s[++i]))
			nb = (nb * 10) + (s[i] - '0');
		data->prec = nb;
	}
	data->type = s[i];
	return (i);
}

//====<[ ft_skip_rep: ]>========================================================
static int	ft_skip_rep(char *s, char c)
{
	if (*s && *s == c)
		return (1 + ft_skip_rep(++s, c));
	return (0);
}
