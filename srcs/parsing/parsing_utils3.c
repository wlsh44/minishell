/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:26:05 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 23:41:46 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_endline_condition(char c)
{
	if (c == 0 || ft_isspace(c) || ft_isseparator(c))
		return (1);
	return (0);
}

int	is_key_char(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (true);
	return (false);
}

int	get_arg_size(char *line)
{
	int	size;

	size = 0;
	while (ft_isspace(*line))
		line++;
	while (*line && !ft_isseparator(*line) && !ft_isspace(*line))
	{
		size++;
		line++;
	}
	return (size);
}

int	sub_cmd(char *line, char **sub, int start)
{
	int		i;
	int		quote;

	i = start;
	quote = 0;
	while (line[i])
	{
		if (ft_isquote(line[i]))
		{
			quote = line[i++];
			while (line[i])
				if (line[i++] == quote)
					break ;
		}
		else if (line[i] == ';')
			break ;
		else
			i++;
	}
	*sub = ft_substr(line, start, i - start);
	if (line[i])
		i++;
	return (i);
}
