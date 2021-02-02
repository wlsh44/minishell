/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:00:43 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 14:49:51 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_option(char **line)
{
	char	*tmp;

	tmp = *line;
	while (ft_isspace(**line))
		(*line)++;
	if (valid_echo_option(line))
		return (1);
	*line = tmp;
	return (0);
}

int	get_arg_char_echo(char **line, char *arg)
{
	int	ret;

	while (!endline_condition_quote(**line))
	{
		if (ft_isquote(**line))
		{
			if ((ret = get_arg_quote(line, &arg)) < 0)
				return (ret);
		}
		else
		{
			if (**line == '\\')
				(*line)++;
			if (ft_isspace(**line))
			{
				*(arg++) = *(*line)++;
				while (ft_isspace(**line))
					(*line)++;
			}
			else
				*(arg++) = *(*line)++;
		}
	}
	*arg = '\0';
	return (0);
}

int	get_arg_echo(char **line, char **arg)
{
	int		size;
	int		ret;
	char	*tmp;

	size = get_last_char(*line);
	tmp = ft_calloc(sizeof(char), size + 2);
	if ((ret = get_arg_char_echo(line, tmp)) < 0)
	{
		free(tmp);
		return (ret);
	}
	if (ft_strlen(tmp) && ft_isspace(tmp[ft_strlen(tmp) - 1]))
		tmp[ft_strlen(tmp) - 1] = 0;
	*arg = tmp;
	return (ret);
}

int	parsing_echo(t_lstcmd *cmd, char **line)
{
	int		ret;
	int		type;
	char	*arg;

	while (ft_isspace(**line))
		(*line)++;
	type = check_echo_option(line) ? TYPE_ECHO_N : TYPE_ECHO;
	while (ft_isspace(**line))
		(*line)++;
	if ((ret = get_arg_echo(line, &arg)) < 0)
		return (ret);
	push_back(cmd, type, arg);
	return (0);
}
