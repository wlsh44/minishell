/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:07:14 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/29 00:12:40 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *str, size_t count, int c)
{
	char	*cursur;
	size_t	i;

	i = 0;
	cursur = (char *)str;
	while (*cursur && i < count)
	{
		if (*cursur == c)
			return (cursur);
		cursur++;
		i++;
	}
	return (0);
}
