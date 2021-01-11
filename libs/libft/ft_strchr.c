/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:43 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/27 22:49:17 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	*cursur;
	int		i;

	i = 0;
	cursur = (char *)str;
	while (cursur[i] != 0)
	{
		if (cursur[i] == c)
			return (cursur + i);
		i++;
	}
	if (cursur[i] == c)
		return (cursur + i);
	return (0);
}
