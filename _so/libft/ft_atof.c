/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaret <souaret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 23:05:30 by souaret           #+#    #+#             */
/*   Updated: 2024/11/24 23:43:56 by souaret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*************************************************************
 * 
 * 
 * 
 *************************************************************/
static double	ft_atod(char *str)
{
	double	j;
	double	after_comma;

	j = 1;
	after_comma = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		j /= 10;
		after_comma = after_comma + (*str - '0') * j;
		str++;
	}
	return (after_comma);
}

/*************************************************************
 * 
 * 
 * 
 *************************************************************/
double	ft_atof(char *str)
{
	double		before_comma;
	double		after_comma;
	int			sign;

	before_comma = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= '\t' && *str <= '\n')))
		str++;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
		before_comma = before_comma * 10 + *str++ - '0';
	if (*str && *str == '.')
		str++;
	after_comma = ft_atod(str);
	return (sign * (before_comma + after_comma));
}
