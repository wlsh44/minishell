/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sanitize_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:07:53 by schang            #+#    #+#             */
/*   Updated: 2021/01/27 20:02:11 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_position(int open, int offset)
{
	int	position;

	position = offset;
	if (open > 0)
	{
		position = offset;
		if (position != 0)
			position++;
	}
	else
		position++;
	return (position);
}

static char	*make_string(char *src, char *stock, int offset, int size)
{
	char	*tmp;
	char	*str;

	if (size <= 0)
		return (stock);
	tmp = ft_substr(src, offset, size);
	str = ft_strjoin(stock, tmp);
	free(tmp);
	free(stock);
	return (str);
}

static void	mix_string(char *src, int i, t_sanitize_quote *quote)
{
	int		open;
	int		o;
	int		pos;

	open = quote->open;
	o = quote->o;
	if (i > 0 && src[i - 1] == '\\')
		;
	else if (open == src[i] || (src[i] == '\"' || src[i] == '\''))
	{
		if (open == 0)
			open = src[i];
		else
			open = 0;
		if (i > 0)
		{
			pos = get_position(open, o);
			quote->stock = make_string(src, quote->stock, pos, i - pos);
			o = i;
		}
	}
	quote->open = open;
	quote->o = o;
}

char		*ft_sanitize_quote(char *src)
{
	t_sanitize_quote	quote;
	int					i;
	char				*str;
	int					pos;

	i = 0;
	quote.stock = ft_calloc(sizeof(char), 1);
	quote.open = 0;
	quote.o = 0;
	while (*src && ft_isspace(*src))
		src++;
	while (src[i])
		mix_string(src, i++, &quote);
	if (quote.o == 0 && src[i] == '\0')
		str = src;
	else
	{
		pos = get_position(quote.open, quote.o);
		quote.stock = make_string(src, quote.stock, pos, i - pos);
		str = ft_strdup(quote.stock);
	}
	free(quote.stock);
	return (str);
}
