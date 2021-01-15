/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:08:05 by jinhkim           #+#    #+#             */
/*   Updated: 2021/01/15 20:05:11 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*cursur;
	int		i;

	cursur = (char *)str;
	i = ft_strlen(cursur);
	while (i >= 0)
	{
		if (cursur[i] == c)
			return (cursur + i);
		i--;
	}
	return (0);
}
