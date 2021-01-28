/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:00:43 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 21:06:34 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	endline_condition_quote(char c)
{
	if (c == 0 || ft_isseparator(c))
		return (1);
	return (0);
}

int	check_echo_option(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (**line == '-' && (*line)[1] == 'n' && ft_isspace((*line)[2]))
	{
		(*line) += 2;
		return (1);
	}
	return (0);
}

int get_last_char(char **line)
{
	int i;
	int quote;
	int last_char;

	i = 0;
	last_char = 0;
	while (!endline_condition_quote((*line)[i]))
	{
		if (ft_isquote((*line)[i]))
		{
			quote = (*line)[i];
			while ((*line)[++i])
			{
				if ((*line)[i] == quote)
				{
					quote = 0;
					last_char = i++;
					break ;
				}
			}
		}
		else if (!ft_isspace((*line)[i++]))
			last_char = i - 1;
	}
	return (last_char + 1);
}

int	get_arg_char_echo(char **line, char *arg)
{
	int	ret;
	int i;
	int last;
	char tmp;
	char *ptr;

	while (ft_isspace(**line))
		(*line)++;
	last = get_last_char(line);
	ptr = *line;
	tmp = (*line)[last];
	(*line)[last] = 0;
	ret = get_arg_char_basic(line, arg, endline_condition_quote);
	if (ret)
		return (WRONG_QUOTE);
	ptr[last] = tmp;
	while (ft_isspace(**line))
		(*line)++;
	return (0);
}

int	get_arg_echo(char **line, char **arg)
{
	int		size;
	int		ret;
	char	*tmp;

	size = get_last_char(line);
	tmp = malloc(sizeof(char) * (size + 1));
	if ((ret = get_arg_char_echo(line, tmp)) < 0)
	{
		free(tmp);
		return (ret);
	}
	*arg = tmp;
	return (ret);
}

int	parsing_echo(t_lstcmd *cmd, char **line)
{
	int		ret;
	int		type;
	char	*arg;

	type = check_echo_option(line) ? TYPE_ECHO_N : TYPE_ECHO;
	if ((ret = get_arg_echo(line, &arg)) < 0)
		return (ret);
	push_back(cmd, type, arg);
	return (0);
}
