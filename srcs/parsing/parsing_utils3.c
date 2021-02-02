/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:26:05 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 23:43:52 by schang           ###   ########.fr       */
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
	int	i;
	int	quote;

	while (ft_isspace(*line))
		line++;
	i = 0;
	quote = 0;
	while (!ft_endline_condition(line[i]))
	{
		if (ft_isquote(line[i]))
		{
			quote = line[i++];
			while (line[i])
				if (line[i++] == quote)
					break ;
		}
		else
			i++;
	}
	return (i);
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
		else if (i != 0 && line[i - 1] != '\\' && line[i] == ';')
			break ;
		else
			i++;
	}
	*sub = ft_substr(line, start, i - start);
	if (line[i])
		i++;
	return (i);
}
