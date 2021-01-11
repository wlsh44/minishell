/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:22 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/27 22:49:17 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t size)
{
	size_t			i;
	unsigned char	*cp_dst;
	unsigned char	*cp_src;

	i = 0;
	if (dst == 0 && src == 0)
		return (dst);
	cp_dst = (unsigned char *)dst;
	cp_src = (unsigned char *)src;
	while (i < size)
	{
		cp_dst[i] = cp_src[i];
		i++;
	}
	return (dst);
}
