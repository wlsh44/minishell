/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhkim <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 22:07:40 by jinhkim           #+#    #+#             */
/*   Updated: 2020/04/27 22:49:17 by jinhkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_sep(char s, char sep)
{
	if (s == sep)
		return (true);
	return (false);
}

static int	get_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (!is_sep(*s, c) && *s)
	{
		len++;
		s++;
	}
	return (len);
}

static char	**get_str(char **str, const char *s, char c, int row)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < row)
	{
		j = 0;
		while (is_sep(*s, c))
			s++;
		len = get_len(s, c);
		if (!(str[i] = (char *)malloc(sizeof(char) * (len + 1))))
			return (0);
		while (!is_sep(*s, c) && *s)
		{
			str[i][j] = *s;
			j++;
			s++;
		}
		str[i++][j] = 0;
		if (*s)
			s++;
	}
	str[i] = 0;
	return (str);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		row;
	char	**str;

	i = 0;
	row = 0;
	while (s[i] != 0)
	{
		while (is_sep(s[i], c) && s[i] != 0)
			i++;
		if (s[i] != 0)
			row++;
		while (!is_sep(s[i], c) && s[i] != 0)
			i++;
	}
	if (!(str = (char **)malloc(sizeof(char *) * (row + 1))))
		return (0);
	str = get_str(str, s, c, row);
	return (str);
}
