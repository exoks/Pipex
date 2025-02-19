/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:16:33 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/09 18:26:48 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

//====<[ ft_size_in_base: ]>====================================================
int	ft_size_in_base(unsigned long int nb, int b_len, int isaddr)
{
	if (nb == 0 && isaddr)
		return (1);
	if (nb)
		return (1 + ft_size_in_base((nb / b_len), b_len, FALSE));
	return (0);
}

//====<[ ft_print_in_b: ]>======================================================
int	ft_print_in_b(unsigned long int nb, char *base, int b_len, int isaddr)
{
	if (nb == 0 && isaddr)
		ft_print_char('0', NULL);
	if (nb)
	{
		ft_print_in_b(nb / b_len, base, b_len, FALSE);
		ft_print_char(base[nb % b_len], NULL);
	}
	return (ft_size_in_base(nb, b_len, TRUE));
}
