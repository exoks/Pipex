/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:22:41 by oezzaou           #+#    #+#             */
/*   Updated: 2025/02/23 15:12:39 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ Prototypes: forward declaration ]>=====================================
static void	ft_init_data(t_data *data);
static int	ft_print_conver(va_list *obj, t_data *data);

//====<[ ft_printf: ]>==========================================================
int	ft_printf(const char *s, ...)
{
	va_list	obj;
	t_data	data;
	int		len;
	int		i;

	len = 0;
	va_start(obj, s);
	ft_init_data(&data);
	while (*s)
	{
		if (*s == '%')
		{
			i = ft_manage_flags((char *)++s, &data);
			while (i-- > 0)
				s++;
			len += ft_print_conver(&obj, &data);
		}
		else
			len += ft_print_char(*s, NULL);
		ft_init_data(&data);
		s++;
	}
	va_end(obj);
	return (len);
}

//====<[ ft_init_data: ]>=======================================================
static void	ft_init_data(t_data *data)
{
	data->flag = 0;
	data->width = 0;
	data->prec = -1;
	data->type = 0;
}

//====<[ ft_print_conver: ]>====================================================
static int	ft_print_conver(va_list *obj, t_data *data)
{
	int	len;

	len = 0;
	if (data->type == 'c')
		len += ft_print_char((char)va_arg(*obj, int), data);
	else if (data->type == 's')
		len += ft_print_str((char *)va_arg(*obj, char *), data);
	else if (data->type == 'p')
		len += ft_putnbr_base_upx(va_arg(*obj, unsigned long int), data, HEX_B);
	else if (data->type == 'd' || data->type == 'i')
		len += ft_putnbr_base_id(va_arg(*obj, int), data, DCI_B);
	else if (data->type == 'u')
		len += ft_putnbr_base_upx((unsigned int)va_arg(*obj, int), data, DCI_B);
	else if (data->type == 'x')
		len += ft_putnbr_base_upx(va_arg(*obj, unsigned int), data, HEX_B);
	else if (data->type == 'X')
		len += ft_putnbr_base_upx(va_arg(*obj, unsigned int), data, HEX_BM);
	else if (data->type == '%')
		len += ft_print_char('%', NULL);
	return (len);
}
