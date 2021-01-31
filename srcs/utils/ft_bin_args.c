/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:34:24 by schang            #+#    #+#             */
/*   Updated: 2021/02/01 01:15:29 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quote(char *arg, int *i)
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

static int	count_args(char *arg)
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

static char	**get_args(char *arg, char **args, int count)
{
	int		i;

	i = 1;
	while (i <= count)
	{
		//int	get_arg_char_basic(char **line, char *arg, int (*endline_cond)(char c)
		while (*arg && ft_isspace(*arg))
			arg++;
		get_arg_char_basic(&arg, args[i], ft_endline_condition);
		i++;
	}
	return (NULL);
}

char		**ft_bin_args(char *cmd, char *arg)
{
	int		cnt;
	char	**args;

	args = NULL;
	cnt = count_args(arg);
	printf("cnt: %d\n", cnt);
	if (!(args = ft_calloc(sizeof(char *), cnt + 2)))
		return (NULL);
	args[0] = ft_strdup(cmd);
	get_args(arg, args, cnt);
	return (args);
}
