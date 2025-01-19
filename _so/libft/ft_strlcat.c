/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:47:12 by souaret           #+#    #+#             */
/*   Updated: 2024/05/30 16:41:49 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
static char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((i < n) && (src[i] != '\0'))
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_length;
	size_t	src_length;
	size_t	remaining;

	if (!dst && !src)
		return (0);
	src_length = ft_strlen((char *)src);
	if (size == 0)
		return (src_length);
	dest_length = ft_strlen(dst);
	remaining = size - dest_length;
	if (remaining <= 0)
		return (dest_length + src_length);
	j = dest_length;
	i = 0;
	while (src[i] && dest_length + i < size - 1)
		dst[j++] = src[i++];
	dst[j] = 0;
	if (dest_length >= size)
		dest_length = size;
	return (dest_length + src_length);
}
