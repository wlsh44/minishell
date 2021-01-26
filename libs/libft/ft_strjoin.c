/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:47 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/29 00:19:39 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(arr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (0);
	ft_strcpy(arr, s1, s1_len);
	ft_strcpy(arr + s1_len, s2, s2_len);
	arr[s1_len + s2_len] = 0;
	return (arr);
}
