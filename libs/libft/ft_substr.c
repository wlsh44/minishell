/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:04:46 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/29 21:17:43 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (0);
	if (!(arr = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	while (i < len && i + start < s_len)
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = 0;
	return (arr);
}
