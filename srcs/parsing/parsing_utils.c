/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:03:18 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 22:57:36 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

int		get_arg_num(char *line)
{
	int	arg_num;
	int	flag;
	int	i;

	flag = 0;
	arg_num = 0;
	i = 0;
	while (i < get_last_char(line))
	{
		if (ft_isspace(line[i]))
		{
			flag = 0;
			skip_space(line, &i);
		}
		else
		{
			if (!flag)
			{
				flag = 1;
				arg_num++;
			}
			i++;
		}
	}
	return (arg_num);
}

int		get_arg_char_basic(char **line, char *arg, int (*endline_cond)(char c))
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

int		get_arg_char(char **line, char *arg)
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

int		get_arg(char **line, char **arg)
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
