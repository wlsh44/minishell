/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:08:03 by jinhkim           #+#    #+#             */
/*   Updated: 2020/05/01 03:31:46 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_little(const char *big, const char *little, size_t i, size_t len)
{
	while (*little)
	{
		if (*little != *big || i >= len)
			return (false);
		little++;
		big++;
		i++;
	}
	return (true);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!(*little))
		return ((char *)big);
	while (i < len && *big)
	{
		if (is_little(big, little, i, len))
			return ((char *)big);
		i++;
		big++;
	}
	return (0);
}
