/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 22:46:07 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 22:57:16 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quote(char *arg, int *i)
{
	int	quote;
	int	o;

	quote = 0;
	o = *i;
	if (ft_isquote(arg[o]))
	{
		quote = arg[o++];
		while (arg[o])
		{
			if (arg[o++] == quote)
			{
				*i = o;
				break ;
			}
		}
	}
	*i = o;
}

int		count_args(char *arg)
{
	int	i;
	int	cnt;
	int	offset;

	i = 0;
	cnt = 0;
	offset = 0;
	while (arg[i])
	{
		if (ft_isquote(arg[i]))
			skip_quote(arg, &i);
		else if (ft_isspace(arg[i]))
		{
			cnt++;
			while (arg[i] && ft_isspace(arg[i]))
				i++;
			offset = i;
		}
		else
			i++;
	}
	if (offset < i)
		cnt++;
	return (cnt);
}

int		check_key_quote(char *arg, int *i)
{
	int	quote;

	quote = arg[*i];
	while (arg[*i] && !(ft_isseparator(arg[*i])
		|| ft_isspace(arg[*i]) || arg[*i] == '='))
	{
		if (ft_isalpha(arg[*i]) || ft_isdigit(arg[*i]) || arg[*i] == '_')
			(*i)++;
		else if (arg[*i] == quote)
		{
			quote = 0;
			(*i)++;
			break ;
		}
		else
			return (NOT_VAILD_IDENTIFIER);
	}
	if (quote)
		return (WRONG_QUOTE);
	return (0);
}

int		check_key(char *arg)
{
	int	i;

	i = 0;
	while (is_key_char(arg[i]) || arg[i] == '\\')
	{
		if (arg[i] == '\\')
		{
			i++;
			if (!is_key_char(arg[i]))
				return (NOT_VAILD_IDENTIFIER);
		}
		else
			i++;
	}
	if (arg[i] && arg[i] != '=')
		return (NOT_VAILD_IDENTIFIER);
	return (0);
}
