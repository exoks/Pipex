/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_upx.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:10:38 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/10 12:08:14 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ Prototypes: ]>=========================================================
static int	ft_print_prefix(int nb, t_data *data);
static int	ft_print_prec_upx(int len, t_data *data);
static int	ft_print_width_upx(int nb_len, t_data *data);

//====<[ ft_putnbr_base_upx: ]>=================================================
int	ft_putnbr_base_upx(unsigned long int nb, t_data *data, char *base)
{
	int	l;
	int	base_len;
	int	nb_len;

	l = 0;
	base_len = ft_strlen((const char *) base);
	nb_len = ft_size_in_base(nb, base_len, TRUE);
	if (data->type == 'p')
		nb_len += 2;
	if (nb == 0 && data->prec > -1)
		nb_len = 0;
	if (data && data->width && (data->flag <= 0 || data->flag == '0'))
		l += ft_print_width_upx(nb_len, data);
	l += ft_print_prefix(nb, data);
	l += ft_print_prec_upx(nb_len, data);
	if (!(nb == 0 && data->prec >= 0))
		l += ft_print_in_b(nb, base, base_len, TRUE);
	else
		nb_len = 0;
	if (data && data->width && data->flag == '-')
		l += ft_print_width_upx(nb_len, data);
	return (l);
}

//====<[ ft_print_prefix: ]>====================================================
static int	ft_print_prefix(int nb, t_data *data)
{
	if (data->type == 'p' || (data->type == 'x' && data->flag == '#' && nb))
		return (ft_print_str("0x", NULL));
	if (data->type == 'X' && data->flag == '#' && nb)
		return (ft_print_str("0X", NULL));
	return (0);
}

//====<[ ft_print_prec_upx: ]>==================================================
static int	ft_print_prec_upx(int len, t_data *data)
{
	int	l;
	int	prec_tmp;

	prec_tmp = data->prec;
	l = 0;
	if (prec_tmp > len)
	{
		prec_tmp -= len;
		while ((prec_tmp)-- > 0)
			l += ft_print_char('0', NULL);
	}
	return (l);
}

//====<[ ft_print_width_upx: ]>=================================================
static int	ft_print_width_upx(int nb_len, t_data *data)
{
	int		prec;
	int		l;
	char	padding;

	padding = ' ';
	if (data->flag == '0' && data->prec == -1)
		padding = '0';
	l = 0;
	if (data->prec > nb_len)
		prec = data->width - data->prec;
	else
		prec = data->width - nb_len;
	while (prec-- > 0)
		l += ft_print_char(padding, NULL);
	return (l);
}
