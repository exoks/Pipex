/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:01:10 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/09 17:53:34 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ Prototypes: ]>=========================================================
static int	ft_print_str_width(int len, t_data *data);
static int	ft_print_str_prec(char *s, int prec);

//====<[ ft_print_str: ]>=======================================================
int	ft_print_str(char *s, t_data *data)
{
	int		l;
	char	*med;
	size_t	s_len;

	l = 0;
	med = s;
	if (!s)
		med = "(null)";
	s_len = ft_strlen((const char *)med);
	if (data && data->width && data->flag != '-')
		l += ft_print_str_width(s_len, data);
	if (data && data->prec >= 0 && data->prec <= (int) s_len)
		l += ft_print_str_prec(med, data->prec);
	else
	{
		while (*med)
			l += ft_print_char(*(med++), NULL);
	}
	if (data && data->width && data->flag == '-')
		l += ft_print_str_width(s_len, data);
	return (l);
}

//====<[ ft_print_str_width: ]>=================================================
static int	ft_print_str_width(int len, t_data *data)
{
	int	l;

	l = 0;
	if (data->prec > -1 && data->prec <= len)
		data->width -= data->prec;
	else
		data->width -= len;
	while ((data->width)-- > 0)
		l += ft_print_char(' ', NULL);
	return (l);
}

//====<[ ft_print_str_prec: ]>==================================================
static int	ft_print_str_prec(char *s, int prec)
{
	int	i;

	i = -1;
	while (s[++i] && i < prec)
		ft_print_char(s[i], NULL);
	return (i);
}
