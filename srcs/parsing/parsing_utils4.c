/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:49:06 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 22:57:56 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_option(char *line, char **sub)
{
	int		i;
	int		quote;

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
	*sub = ft_substr(line, 0, i);
	return (i);
}

int			valid_echo_option(char **line)
{
	char	*tmp;
	char	*option;
	int		len;
	int		i;

	i = 0;
	tmp = *line;
	while (ft_isspace(**line))
		(*line)++;
	len = get_option(*line, &option);
	get_arg_char_basic(&tmp, option, ft_endline_condition);
	if (ft_strncmp(option, "-n", 2) == 0)
	{
		i += 2;
		while (option[i] && option[i] == 'n')
			i++;
		if (option[i] == 0)
		{
			(*line) += len;
			free(option);
			return (1);
		}
	}
	free(option);
	return (0);
}

int			get_last_char(char *line)
{
	int i;
	int quote;
	int last_char;

	i = 0;
	last_char = 0;
	while (!endline_condition_quote(line[i]))
	{
		if (ft_isquote(line[i]))
		{
			quote = line[i];
			while (line[++i])
			{
				if ((quote == '\'' || line[i - 1] != '\\') && line[i] == quote)
				{
					quote = 0;
					break ;
				}
			}
		}
		if (!ft_isspace(line[i++]))
			last_char = i - 1;
	}
	return (last_char ? last_char + 1 : last_char);
}
