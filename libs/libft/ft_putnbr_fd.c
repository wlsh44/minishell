/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:34 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/27 23:04:26 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	rec(long n, int fd)
{
	char	tmp;

	if (n == 0)
		return ;
	tmp = n % 10 + '0';
	rec(n / 10, fd);
	write(fd, &tmp, 1);
}

void		ft_putnbr_fd(int n, int fd)
{
	long	num;

	num = (long)n;
	if (num == 0)
		write(fd, "0", 1);
	else if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
		rec(num, fd);
	}
	else
	{
		rec(num, fd);
	}
}
