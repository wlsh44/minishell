/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:14 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/27 22:49:17 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t size)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*cp_dst;
	unsigned char	*cp_src;

	i = 0;
	cp_dst = (unsigned char *)dst;
	cp_src = (unsigned char *)src;
	cc = (unsigned char)c;
	while (i < size)
	{
		if (*cp_src == cc)
		{
			*(cp_dst++) = *(cp_src++);
			return (cp_dst);
		}
		*(cp_dst++) = *(cp_src++);
		i++;
	}
	return (0);
}
