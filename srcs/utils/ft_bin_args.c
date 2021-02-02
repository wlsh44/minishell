/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bin_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:34:24 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 22:47:22 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_args(t_minishell *ms, char *arg, char **args, int count)
{
	int		i;
	char	*tmp;
	char	*env;

	i = 1;
	while (i <= count)
	{
		while (*arg && ft_isspace(*arg))
			arg++;
		args[i] = malloc(sizeof(char) * (ft_strlen(arg) + 1));
		get_arg_char_basic(&arg, args[i], endline_condition_normal);
		if (ft_strncmp(args[i], "~", 1) == 0)
		{
			tmp = args[i];
			env = dup_env_value(ms->env, "HOME", 4);
			args[i] = ft_strjoin(env, tmp + 1);
			free_and_null(tmp);
			free_and_null(env);
		}
		i++;
	}
	return (NULL);
}

char		**ft_bin_args(t_minishell *ms, char *cmd, char *arg)
{
	int		cnt;
	char	**args;

	args = NULL;
	cnt = count_args(arg);
	if (!(args = ft_calloc(sizeof(char *), cnt + 2)))
		return (NULL);
	args[0] = ft_strdup(cmd);
	get_args(ms, arg, args, cnt);
	return (args);
}
