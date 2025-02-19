/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:49:28 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/09 17:08:00 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ ft_print_width: ]>=====================================================
static int	ft_print_width_c(t_data *data)
{
	int	l;

	l = 0;
	if (data && data->width > 1)
	{
		while (--(data->width))
			l += write(1, " ", 1);
	}
	return (l);
}

//====<[ ft_print_char: ]>======================================================
int	ft_print_char(char c, t_data *data)
{
	int	l;

	l = 0;
	if (data && data->width && data->flag == 0)
		l += ft_print_width_c(data);
	l += write(1, &c, 1);
	if (data && data->width && data->flag == '-')
		l += ft_print_width_c(data);
	return (l);
}
