/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:23:03 by souaret           #+#    #+#             */
/*   Updated: 2024/05/29 21:22:43 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_write(char *str, int sign, int len, int fd)
{
	if (sign < 0)
		str[len] = '-';
	else if (len > 0)
		len--;
	while (len >= 0)
		write(fd, &str[len--], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[13];
	int		sign;
	int		len;
	long	nb;

	sign = 1;
	nb = n;
	if (nb < 0)
	{
		sign = -1;
		nb = -nb;
	}
	ft_bzero(str, 13);
	if (nb == 0)
		str[0] = '0';
	len = 0;
	while (nb != 0)
	{
		str[len++] = '0' + (nb % 10);
		nb = (nb / 10);
	}
	ft_putnbr_fd_write(str, sign, len, fd);
}
/*
	if (sign < 0)
		str[len] = '-';
	else if (len > 0)
		len--;
	while (len >= 0)
		write(fd, &str[len--], 1);
*/
/*
{
	char	*str;
	int		l;

	if (fd == 0)
		return ;
	str = ft_itoa(n);
	if (str == NULL)
		return ;
	l = ft_strlen(str);
	write(fd, str, l);
	free(str);
}
*/
