/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:06:25 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/29 00:16:06 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isnum(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

static int	to_int(const char *str, long n)
{
	long	temp;

	if (!ft_isnum(*str))
		return (n);
	temp = *str - '0' + n * 10;
	str++;
	n = to_int(str, temp);
	return (n);
}

static bool	is_space(const char *str)
{
	if (*str == ' ' || (*str >= 9 && *str <= 13))
		return (true);
	return (false);
}

int			ft_atoi(const char *str)
{
	long	n;
	int		flag;

	flag = 0;
	n = 0;
	while (is_space(str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			flag = 1;
		str++;
	}
	n = to_int(str, n);
	return (flag == 1 ? (int)(n * -1) : (int)n);
}
