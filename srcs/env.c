/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:59:11 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 23:24:43 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_env_val(t_minishell *ms, char *arg)
{
	if (*arg == '$')
	{
		arg++;
		if (!*arg)
			return (NULL);
		if (*arg == '?')
			return (ft_itoa(g_exit_status));
		else
			return (ft_strdup(get_env_value(ms->env, arg)));
	}
	else
		return (ft_strdup(arg));
}

char	*get_env_value(t_lstenv *env, char *name)
{
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			return (cur->val);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	delete_env(t_lstenv *env, char *name)
{
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			cur->prev->next = cur->next;
			cur->next->prev = cur->prev;
			free(cur->name);
			cur->name = NULL;
			if (cur->val)
			{
				free(cur->val);
				cur->val = NULL;
			}
			free(cur);
			break ;
		}
		cur = cur->next;
	}
}

void	update_env(t_lstenv *env, char *name, char *val)
{
	t_env_node *node;
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail)
	{
		if (ft_strcmp(cur->name, name) == 0)
		{
			free(cur->val);
			cur->val = val;
			return ;
		}
		cur = cur->next;
	}
	node = malloc(sizeof(t_env_node));
	node->name = name;
	node->val = val;
	node->prev = env->tail->prev;
	node->next = env->tail;
	env->tail->prev->next = node;
	env->tail->prev = node;
}

void	init_env(t_minishell *ms, char *envp[])
{
	char	*name;
	char	*val;
	char	*ptr;

	while (*envp && !(val = NULL))
	{
		ptr = ft_strchr(*envp, '=');
		if (ptr == NULL || !*(ptr + 1))
		{
			name = ft_strdup(*envp);
			name[ft_strlen(name) - 1] = 0;
		}
		else
		{
			*ptr++ = '\0';
			name = ft_strdup(*envp);
			val = ft_strdup(ptr);
		}
		update_env(ms->env, name, val);
		envp++;
	}
}
