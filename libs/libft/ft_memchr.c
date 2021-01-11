/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:17 by jinhkim           #+#    #+#             */
/*   Updated: 2020/05/05 18:59:24 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*cp_ptr;

	i = 0;
	cp_ptr = (unsigned char *)ptr;
	while (i < num)
	{
		if (cp_ptr[i] == (unsigned char)value)
			return (cp_ptr + i);
		i++;
	}
	return (0);
}
