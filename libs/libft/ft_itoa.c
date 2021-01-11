/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:06:51 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/29 00:19:15 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_digit(long n)
{
	int	digit;

	digit = 0;
	if (n >= 10)
	{
		while (n != 0)
		{
			digit++;
			n /= 10;
		}
	}
	else
		digit = 1;
	return (digit);
}

static void		to_a(char *arr, long n, int i)
{
	if (n == 0)
		return ;
	arr[i] = n % 10 + '0';
	to_a(arr, n / 10, i - 1);
}

char			*ft_itoa(int n)
{
	char	*arr;
	int		digit;
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num = num * (-1);
		digit = get_digit(num);
		digit++;
		if (!(arr = (char *)malloc(sizeof(char) * (digit + 1))))
			return (0);
		*arr = '-';
		to_a(arr, num, digit - 1);
	}
	else
	{
		digit = get_digit(num);
		arr = (char *)malloc(sizeof(char) * (digit + 1));
		to_a(arr, num, digit - 1);
	}
	if (num == 0)
		arr[0] = '0';
	arr[digit] = 0;
	return (arr);
}
