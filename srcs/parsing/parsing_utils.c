/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:03:18 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 18:32:46 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_num(char *line)
{
	int	arg_num;
	int	flag;

	flag = 0;
	arg_num = 0;
	while (*line && !ft_isseparator(*line))
	{
		if (ft_isspace(*line))
		{
			flag = 0;
			while (ft_isspace(*line))
				line++;
		}
		else
		{
			if (!flag)
			{
				flag = 1;
				arg_num++;
			}
			line++;
		}
	}
	return (arg_num);
}

int	get_arg_char_basic(char **line, char *arg, int (*endline_cond)(char c))
{
	int	ret;

	ret = 0;
	while (!endline_cond(**line))
	{
		if (**line == '\\')
		{
			(*line)++;
			if (**line)
				*(arg++) = *(*line)++;
		}
		else if (ft_isquote(**line))
		{
			if ((ret = get_arg_quote(line, &arg)) < 0)
				return (ret);
		}
		else
			*(arg++) = *(*line)++;
	}
	*arg = '\0';
	return (ret);
}

int	get_arg_char(char **line, char *arg)
{
	char	ret;

	while (ft_isspace(**line))
		(*line)++;
	if ((ret = get_arg_char_basic(line, arg, ft_endline_condition)) < 0)
		return (ret);
	while (ft_isspace(**line))
		(*line)++;
	return (0);
}

int	get_arg(char **line, char **arg)
{
	int		size;
	int		ret;
	char	*tmp;

	size = get_arg_size(*line);
	tmp = malloc(sizeof(char) * (size + 1));
	if ((ret = get_arg_char(line, tmp)) < 0)
	{
		free(tmp);
		return (ret);
	}
	*arg = tmp;
	return (ret);
}

int	get_last_char(char *line)
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
			quote = line[i++];
			while (line[i])
			{
				last_char = ++i;
				if (line[i - 2] != '\\' && line[i - 1] == quote)
				{
					quote = 0;
					break ;
				}
			}
		}
		else if (!ft_isspace(line[i++]))
			last_char = i - 1;
	}
	return (*line ? last_char + 1 : last_char);
}
