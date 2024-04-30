/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkerob <vkerob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:07:46 by vkerob            #+#    #+#             */
/*   Updated: 2022/11/22 14:05:34 by vkerob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include<unistd.h>
# include<stdarg.h>

int		ft_printf(const char *s, ...);
size_t	ft_strlen(const char *str);
int		ft_putchar_ct(char c);
int		ft_putnbr_ct_1(long nbr, char *base);
int		ft_putstr_ct(char *s);
int		ft_putnbr_ct_2(unsigned int nbr, char *base);
int		ft_adress(unsigned long nbr);

#endif
