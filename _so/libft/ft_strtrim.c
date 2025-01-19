/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:54:33 by souaret           #+#    #+#             */
/*   Updated: 2024/05/29 20:41:30 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************

#include <stdio.h>	// to be removed
//printf("ftcheck_set: str='%s', set='%s' \n", str, set);

****************************************/
static int	ft_check_set(char *str, char *set)
{
	while (set && str && *str && *set)
	{
		if (*str == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_malloc_empty(void)
{
	char	*str;

	str = malloc(1);
	if (str)
		*str = '\0';
	return (str);
}

/**************************************************************

printf("len(s1) = %zu ", ft_strlen(s1));
printf("s1='%s', set='%s', n1=%d, n2=%d, ", s1, set, n1, n2);

printf("malloc = %d ", n2 + 1);

//	ft_strlcpy(str, (char *)(s + n1), n1 + n2 + 1);
printf("str='%s'\n", str);

***************************************************************/
static char	*ft_strtrim2(char const *s1, char const *set)
{
	char	*s;
	char	*d;
	char	*str;
	int		n1;
	int		n2;

	str = NULL;
	n1 = 0;
	s = (char *)s1;
	while (s && *s && (ft_check_set(s + n1, (char *)set) == 1))
			n1++;
	n2 = ft_strlen(s1) - 1;
	if (n1 == n2 + 1)
		return (ft_malloc_empty());
	while (n2 >= 0 && (ft_check_set(s + n2, (char *)set) == 1))
			n2--;
	str = malloc(n2 - n1 +1 + 1);
	if (! str)
		return (NULL);
	d = str;
	while (n1 <= n2)
		*d++ = s[n1++];
	*d = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	if (s1 == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_malloc_empty());
	if (ft_strlen(set) == 0)
		return (ft_strdup(s1));
	return (ft_strtrim2(s1, set));
}
