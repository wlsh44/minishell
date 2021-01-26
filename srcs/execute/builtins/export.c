/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:07:39 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 20:49:08 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			export_print_env(t_lstenv *env)
{
	t_env_node	*cur;

	cur = env->head->next;
	while (cur != env->tail)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
		write(STDOUT_FILENO, "=", 1);
		if (cur->val)
		{
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, cur->val, ft_strlen(cur->val));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (0);
}

static bool	is_error(bool *flag, char *arg)
{
	if (ft_strchr(arg, NOT_VAILD_IDENTIFIER))
	{
		if (!*flag)
		{
			*flag = true;
			execute_error(NOT_VAILD_IDENTIFIER);
		}
		return (true);
	}
	if (ft_strchr(arg, WRONG_QUOTE))
	{
		if (!*flag)
		{
			*flag = true;
			execute_error(WRONG_QUOTE);
		}
		return (true);
	}
	return (false);
}

int			set_env(t_minishell *ms, char *arg)
{
	char	*ptr;
	char	*key;

	ptr = ft_strchr(arg, '=');
	if (ptr == NULL)
	{
		if ((key = parse_env_val(ms, arg)) == NULL)
			return (export_print_env(ms->env));
		free(key);
	}
	else
	{
		*ptr++ = '\0';
		if ((key = parse_env_val(ms, arg)) == NULL)
			return (NOT_VAILD_IDENTIFIER);
		update_env(ms->env, key, parse_env_val(ms, ptr));
	}
	return (0);
}

int			ft_export(t_minishell *ms, t_node *cur)
{
	char	**args;
	char	**tmp;
	bool	flag;
	int		ret;

	flag = false;
	if (ft_strcmp(cur->arg, "") == 0)
		return (export_print_env(ms->env));
	args = ft_split(cur->arg, ' ');
	tmp = args;
	while (*args)
	{
		if (!is_error(&flag, *args))
			if ((ret = set_env(ms, *args)) < 0 && !flag)
				execute_error(ret);
		args++;
	}
	free_double_char(tmp);
	return (0);
}
