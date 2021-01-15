/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:11:01 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 20:13:04 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcpy(char *dest, const char *src, size_t n)
{
	size_t i;

	if (dest == 0 && src == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (1);
}
