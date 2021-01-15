/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 20:11:29 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 20:13:00 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t size)
{
	char	*str;

	if (!(str = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strcpy(str, s, size);
	str[size] = 0;
	return (str);
}
