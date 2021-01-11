/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:06:18 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/29 00:11:19 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *ptr, size_t size)
{
	size_t			i;
	unsigned char	*arr;

	i = 0;
	arr = (unsigned char *)ptr;
	while (i < size)
		arr[i++] = 0;
	return (ptr);
}
