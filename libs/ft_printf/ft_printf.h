/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruiferna <ruiferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 14:04:25 by ruiferna          #+#    #+#             */
/*   Updated: 2025/05/06 17:12:52 by ruiferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_putchar_pf(char c, int fd);
int	ft_format(char c, va_list args);
int	ft_putstr_pf(char *s, int fd);
int	ft_putnbr_u_pf(unsigned int n, int fd);
int	ft_putnbr_pf(int n, int fd);
int	ft_putnbr_hex(unsigned long n, char *hex, int fd);
int	ft_putpointer(void *pointer, int fd);

int	ft_printf(const char *str, ...);

#endif
