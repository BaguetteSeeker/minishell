/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:47:33 by souaret           #+#    #+#             */
/*   Updated: 2024/05/30 16:37:39 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dest);
	if (!(dest < src && dest + n > src))
	{
		d = (char *)dest + n - 1;
		s = (const char *)src + n - 1;
		while (n-- > 0)
			*d-- = *s--;
	}
	else
	{
		d = (char *)dest;
		s = (const char *)src;
		while (n-- > 0)
			*d++ = *s++;
	}
	return (dest);
}
