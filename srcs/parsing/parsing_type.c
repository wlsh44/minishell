/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 23:26:22 by schang            #+#    #+#             */
/*   Updated: 2021/01/27 00:39:17 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_type1(char **line)
{
	int	type;

	type = 0;
	if (!ft_strncmp(*line, "cd", 2))
	{
		type = TYPE_CD;
		(*line) += 2;
	}
	else if (!ft_strncmp(*line, "pwd", 3))
	{
		type = TYPE_PWD;
		(*line) += 3;
	}
	else if (!ft_strncmp(*line, "echo", 4))
	{
		type = TYPE_ECHO;
		(*line) += 4;
	}
	else if (!ft_strncmp(*line, "export", 6))
	{
		type = TYPE_EXPORT;
		(*line) += 6;
	}
	return (type);
}

int	parsing_type2(char **line)
{
	int type;

	type = 0;
	if (!ft_strncmp(*line, "env", 3))
	{
		type = TYPE_ENV;
		(*line) += 3;
	}
	else if (!ft_strncmp(*line, "unset", 5))
	{
		type = TYPE_UNSET;
		(*line) += 5;
	}
	else if (!ft_strncmp(*line, "exit", 4))
	{
		type = TYPE_EXIT;
		(*line) += 4;
	}
	else if (!ft_strncmp(*line, ">>", 2))
	{
		type = TYPE_DOUBLE_REDIRECT;
		(*line) += 2;
	}
	return (type);
}

int	parsing_type3(char **line)
{
	int	type;

	type = 0;
	if (!ft_strncmp(*line, ">", 1))
	{
		type = TYPE_REDIRECT_OUTPUT;
		(*line) += 1;
	}
	else if (!ft_strncmp(*line, "<", 1))
	{
		type = TYPE_REDIRECT_INPUT;
		(*line) += 1;
	}
	else if (!ft_strncmp(*line, "|", 1))
	{
		type = TYPE_PIPE;
		(*line) += 1;
	}
	else if (!ft_strncmp(*line, ";", 1))
	{
		type = TYPE_SEMICOLON;
		(*line) += 1;
	}
	return (type);
}

/*
bool	check_quote(char quote, char *str)
{
	while (*str && !ft_isspace(*str) && !ft_isseparator(*str))
	{
		if (quote == 0 && ft_isquote(*str))
			return (false);
		else if (*str == quote)
			return (true);
		str++;
	}
	return (false);
}
*/

int	parsing_type(char **line)
{
	char	quote;
	int		type;
	char	*tmp;

	quote = 0;
	if (ft_isquote(**line))
		quote = *(*line)++;
	type = parsing_type1(line);
	if (!type)
		type = parsing_type2(line);
	if (!type)
		type = parsing_type3(line);
	if (!type)
		type = TYPE_NORMAL;
	/*
	tmp = *line;
	if (type == TYPE_NORMAL && !check_quote(quote, tmp))
		type = WRONG_QUOTE;
	*/
	if (type != TYPE_NORMAL && quote && *(*line)++ != quote)
		type = WRONG_QUOTE;
	return (type);
}
