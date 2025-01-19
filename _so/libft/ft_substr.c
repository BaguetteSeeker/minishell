/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:38:48 by souaret           #+#    #+#             */
/*   Updated: 2024/06/02 17:30:38 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strdup2(const char *src)
{
	int		i;
	char	*dup;

	i = 0;
	while (src[i] != '\0')
		i++;
	dup = malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (src[i] != 0)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	new_len;

	if (ft_strlen(s) < start)
	{
		str = ft_strdup2("");
		return (str);
	}
	new_len = ft_strlen(s + start);
	if (!(new_len < len))
		new_len = len;
	str = (char *)malloc(new_len + 1);
	if (!str)
		return (NULL);
	str[new_len] = 0;
	while (new_len-- > 0)
		str[new_len] = s[start + new_len];
	return (str);
}
