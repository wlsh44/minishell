/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:08:07 by jinhkim           #+#    #+#             */
/*   Updated: 2020/05/01 02:11:05 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (true);
		set++;
	}
	return (false);
}

static int	get_len(const char *s, const char *set)
{
	int	len;
	int	i;

	len = 0;
	while (s[len] != 0)
		len++;
	i = len - 1;
	while (is_set(s[i], set) && i >= 0)
	{
		len--;
		i--;
	}
	i = 0;
	while (is_set(s[i], set) && s[i] != 0)
	{
		len--;
		i++;
	}
	if (len < 0)
		len = 0;
	return (len);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*s2;

	len = get_len(s1, set);
	if (!(s2 = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (is_set(*s1, set))
		s1++;
	i = 0;
	while (i < len)
		s2[i++] = *(s1++);
	s2[i] = 0;
	return (s2);
}
