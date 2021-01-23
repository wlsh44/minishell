/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:07:39 by schang            #+#    #+#             */
/*   Updated: 2021/01/15 21:10:16 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_print_env(t_lstenv *env) {
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail) {
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
		write(STDOUT_FILENO, "=", 1);
		if (cur->val) {
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, cur->val, ft_strlen(cur->val));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (0);
}

int	ft_export(t_minishell *ms, t_node *cur) {
	char *ptr;
	char **args;
	char **tmp;
	char *name;
	char *val;

	if (ft_strcmp(cur->arg, "") == 0) {
		return(export_print_env(ms->env));
	}
	args = ft_split(cur->arg, ' ');
	tmp = args;
	while (*args && !(val = NULL)) {
		ptr = ft_strchr(*args, '=');
		if (ptr == NULL) {
			if ((name = parse_env_val(ms, *args)) == NULL) {
				return (export_print_env(ms->env));
			}
		} else {
			*ptr++ = '\0';
			if ((name = parse_env_val(ms, *args)) == NULL) {
				return (NOT_VAILD_IDENTIFIER);
			}
			val = parse_env_val(ms, ptr);
			update_env(ms->env, name, val);
		}
		args++;
	}
	while (*tmp) {
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	//free(tmp);
	return(0);
}
