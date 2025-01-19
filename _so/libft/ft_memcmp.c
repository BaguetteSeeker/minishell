/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:25:56 by souaret           #+#    #+#             */
/*   Updated: 2024/05/23 21:43:49 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*v1;
	const unsigned char	*v2;

	if (n == 0)
		return (0);
	v1 = (const unsigned char *)s1;
	v2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*v1 == *v2)
		{
			i++;
			v1++;
			v2++;
		}
		else
			return ((int)(*v1 - *v2));
	}
	return (0);
}
