/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:00:43 by schang            #+#    #+#             */
/*   Updated: 2021/02/03 22:42:09 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_option(char **line)
{
	int		flag;

	flag = false;
	while (1)
	{
		while (ft_isspace(**line))
			(*line)++;
		if (valid_echo_option(line))
			flag = true;
		else if (flag)
			return (true);
		else
			return (false);
	}
	return (false);
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
	int		len;
	char	*tmp;

	size = get_last_char(*line);
	len = ft_isspace((*line)[size]) ? -1 : 0;
	tmp = ft_calloc(sizeof(char), size + 2);
	if ((ret = get_arg_char_echo(line, tmp)) < 0)
	{
		free(tmp);
		return (ret);
	}
	len += ft_strlen(tmp);
	tmp[len] = 0;
	*arg = tmp;
	return (ret);
}

int	parsing_echo(t_minishell *ms, char **line)
{
	int		ret;
	int		type;
	char	*arg;
	char	*tmp;
	char	*tmp2;

	while (ft_isspace(**line))
		(*line)++;
	tmp = parsing_env_val(ms->env, *line);
	tmp2 = tmp;
	(*line) += get_last_char(*line);
	type = check_echo_option(&tmp) ? TYPE_ECHO_N : TYPE_ECHO;
	while (ft_isspace(*tmp))
		tmp++;
	if ((ret = get_arg_echo(&tmp, &arg)) < 0)
		return (ret);
	free(tmp2);
	push_back(ms->cmd, type, arg);
	return (0);
}
