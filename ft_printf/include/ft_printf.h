/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oezzaou <oezzaou@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:15:30 by oezzaou           #+#    #+#             */
/*   Updated: 2022/10/10 16:46:34 by oezzaou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//====<[ Include guards: ]>=====================================================
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//====<[ Headers: ]>============================================================
# include "libft.h"
# include <stdarg.h>

//====<[ Macros: ]>=============================================================
# define DCI_B "0123456789"
# define HEX_B "0123456789abcdef"
# define HEX_BM "0123456789ABCDEF"
# define TRUE 1
# define FALSE 0

//====<[ struct: data ]>========================================================
typedef struct s_data
{
	char	flag;
	int		width;
	int		prec;
	char	type;
}			t_data;

//====<[ functions: prototypes ]>===============================================
int	ft_printf(const char *s, ...);
int	ft_size_in_base(unsigned long int nb, int b_len, int isaddr);
int	ft_print_in_b(unsigned long int nb, char *base, int b_len, int isaddr);
int	ft_manage_flags(char *s, t_data *data);
int	ft_print_char(char c, t_data *data);
int	ft_print_str(char *s, t_data *data);
int	ft_putnbr_base_upx(unsigned long int nb, t_data *data, char *base);
int	ft_putnbr_base_id(long int nb, t_data *data, char *base);

#endif
//==============================================================================
