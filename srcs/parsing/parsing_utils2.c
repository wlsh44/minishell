/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 21:01:58 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 21:06:46 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arg_quote(char **line, char **arg)
{
	int	quote;

	quote = *(*line)++;
	while (**line && !ft_isseparator(**line) && !ft_isspace(**line))
	{
		if (**line == quote)
		{
			quote = 0;
			(*line)++;
			break ;
		}
		else if (**line == '\\' && ((*line)[1] == quote || (*line)[1] == '\\'))
			(*line)++;
		*(*arg)++ = *(*line)++;
	}
	if (quote)
		return (WRONG_QUOTE);
	return (0);
}

int	get_arg_key_quote(char **line, char **arg)
{
	int	quote;

	quote = *(*line)++;
	while (**line && !(ft_isseparator(**line)
		|| ft_isspace(**line) || **line == '='))
	{
		if (ft_isalpha(**line) || ft_isdigit(**line) || **line == '_')
			*(*arg)++ = *(*line)++;
		else if (**line == quote)
		{
			quote = 0;
			(*line)++;
			break ;
		}
		else
			return (NOT_VAILD_IDENTIFIER);
	}
	if (quote)
		return (WRONG_QUOTE);
	return (0);
}

int	is_key_char(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (true);
	return (false);
}

int	get_arg_key(char **line, char **arg)
{
	int	ret;

	ret = 0;
	while (is_key_char(**line) || ft_isquote(**line)
		|| **line == '\\' || **line == '$')
	{
		if (**line == '\\')
		{
			(*line)++;
			if (!is_key_char(**line))
				return (NOT_VAILD_IDENTIFIER);
		}
		else if (ft_isquote(**line)
			&& (ret = get_arg_key_quote(line, arg)) < 0)
			return (ret);
		else
			*(*arg)++ = *(*line)++;
	}
	return (0);
}
