/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:07:01 by souaret           #+#    #+#             */
/*   Updated: 2024/09/17 21:03:49 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		n;
	char	*str;

	n = ft_strlen(s1) + ft_strlen(s2);
	str = malloc (n + 1);
	if (!str)
		return (NULL);
	ft_memset(str, 0, n + 1);
	if (s1 != 0)
		ft_strlcpy(str, s1, n + 1);
	if (s2 != 0)
		ft_strlcat(str, s2, n + 1);
	return (str);
}
