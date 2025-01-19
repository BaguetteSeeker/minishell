/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:05:28 by souaret           #+#    #+#             */
/*   Updated: 2024/05/23 21:44:14 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*src;
	char		cc;

	cc = c;
	src = s;
	while (*src != 0)
		src++;
	while (s != src && *src != cc)
		src--;
	if (*src == cc)
		return ((char *)src);
	else
		return (0);
}
