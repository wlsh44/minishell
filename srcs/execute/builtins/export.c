/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:07:39 by schang            #+#    #+#             */
/*   Updated: 2021/02/03 00:16:49 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		export_print_env(t_lstenv *env)
{
	t_env_node	*cur;

	cur = env->head->next;
	while (cur != env->tail)
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
		if (cur->val)
		{
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, cur->val, ft_strlen(cur->val));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (0);
}

int		set_env(t_minishell *ms, char *arg)
{
	char	*ptr;
	char	*key;

	ptr = ft_strchr(arg, '=');
	if (ptr == NULL)
	{
		key = ft_strdup(arg);
		if (get_env_value(ms->env, arg) == NULL)
			update_env(ms->env, key, NULL);
	}
	else
	{
		*ptr++ = '\0';
		key = ft_strdup(arg);
		update_env(ms->env, key, ft_strdup(ptr));
	}
	return (0);
}

void	init_export(t_minishell *ms, char **tmp)
{
	char	*arg;
	int		rt;

	while (**tmp && ft_isspace(**tmp))
		(*tmp)++;
	arg = malloc(sizeof(char) * (ft_strlen(*tmp) + 1));
	if ((rt = get_arg_char_basic(tmp, arg, endline_condition_normal) < 0)
		|| ((rt = check_key(arg)) < 0))
		execute_error(rt);
	else
		set_env(ms, arg);
	free(arg);
}

int		ft_export(t_minishell *ms, t_node *cur)
{
	char	*tmp;
	int		cnt;

	if (ft_strcmp(cur->arg, "") == 0)
		return (export_print_env(ms->env));
	tmp = cur->arg;
	cnt = count_args(cur->arg);
	while (cnt--)
		init_export(ms, &tmp);
	return (0);
}
