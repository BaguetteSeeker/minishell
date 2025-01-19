/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 22:03:47 by souaret           #+#    #+#             */
/*   Updated: 2024/11/17 00:53:47 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoh_malloc(int n)
{
	char	*str;

	str = NULL;
	str = malloc(n + 1);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, n + 1);
	return (str);
}

static char	*ft_itoh_n(long nb2, int sign)
{
	int		tab[13];
	int		compteur;
	char	*str;
	int		n;

	ft_bzero(tab, 13 * sizeof(int));
	compteur = 0;
	while (nb2 != 0)
	{
		tab[compteur++] = nb2 % 16;
		nb2 /= 16;
	}
	if (compteur == 0)
		compteur = 1;
	n = compteur;
	if (sign == -1)
		n++;
	str = ft_itoh_malloc(n + 1);
	if (str == NULL)
		return (NULL);
	while (compteur-- > 0)
		str[n - compteur - 1] = tab[compteur] + '0';
	if (sign == -1)
		str[0] = '-';
	return (str);
}

char	*ft_itoh(int n)
{
	char	*str;
	char	*str2;
	int		sign;
	long	nb2;

	sign = 1;
	nb2 = n;
	if (n < 0)
	{
		sign = -1;
		nb2 = -nb2;
	}
	str = ft_itoh_n(nb2, sign);
	str2 = ft_strjoin("0x", str);
	free(str);
	return (str2);
}
