/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_id.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:59:30 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/10 13:01:52 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ Prototypes: ]>=========================================================
static int	ft_print_w_id(int nb, int len, t_data *data);
static int	ft_print_prec_id(int nb, int nb_len, t_data *data);
static int	ft_check_flags(long int nb, t_data *data);
static void	ft_is_negative_inc(long int *nb, int *nb_len);

//====<[ ft_putnbr_base_id: ]>==================================================
int	ft_putnbr_base_id(long int nb, t_data *data, char *base)
{
	int			l;
	int			nb_len;
	long int	nb_temp;

	l = 0;
	nb_len = 0;
	nb_temp = nb;
	ft_is_negative_inc(&nb_temp, &nb_len);
	nb_len += ft_size_in_base(nb_temp, ft_strlen((const char *)base), TRUE);
	l += ft_check_flags(nb, data);
	if (nb < 0 && data->prec < 0 && data->flag == '0')
		l += ft_print_char('-', NULL);
	if (data && data->width && data->flag != '-' && data->type)
		l += ft_print_w_id(nb, nb_len * (nb != 0 || data->prec < 0), data);
	if (nb < 0 && !(data->prec < 0 && data->flag == '0'))
		l += ft_print_char('-', NULL);
	l += ft_print_prec_id(nb, nb_len, data);
	if (!(nb == 0 && data->prec >= 0))
		l += ft_print_in_b(nb_temp, base, ft_strlen((const char *)base), TRUE);
	else
		nb_len = 0;
	if (data && data->width && data->flag == '-')
		l += ft_print_w_id(nb, nb_len, data);
	return (l);
}

//====<[ ft_is_negative_inc: ]>=================================================
static void	ft_is_negative_inc(long int *nb, int *nb_len)
{
	if ((*nb) < 0)
	{
		(*nb) *= -1;
		(*nb_len) += 1;
	}
}

//====<[ ft_print_w_id: ]>======================================================
static int	ft_print_w_id(int nb, int len, t_data *data)
{
	int		l;
	char	padding;
	int		prec;

	l = 0;
	padding = ' ';
	prec = data->prec;
	if (data->flag == '0' && prec == -1)
		padding = '0';
	if (nb < 0 && prec >= len)
		prec++;
	if (prec > len)
		data->width -= prec;
	else
		data->width -= len;
	while ((data->width)-- > 0)
		l += ft_print_char(padding, NULL);
	return (l);
}

//====<[ ft_print_prec_id: ]>===================================================
static int	ft_print_prec_id(int nb, int nb_len, t_data *data)
{
	int	l;
	int	prec;

	prec = data->prec;
	if (nb < 0)
		nb_len--;
	if (nb == 0 && data->prec > -1)
		nb_len--;
	l = 0;
	if (prec > nb_len)
	{
		prec -= nb_len;
		while ((prec)-- > 0)
			l += ft_print_char('0', NULL);
	}
	return (l);
}

//====<[ ft_check_flags: ]>=====================================================
static int	ft_check_flags(long int nb, t_data *data)
{
	if (nb >= 0 && (data->flag == '+' || data->flag == ' '))
		return (ft_print_char(data->flag, NULL));
	return (0);
}
