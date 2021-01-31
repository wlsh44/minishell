/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:59:11 by schang            #+#    #+#             */
/*   Updated: 2021/01/29 01:22:52 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parsing_env_val(t_lstenv *env, char *line)
{
	char	*newline;
	int		quote;
	int		i;
	int		len;

	i = 0;
	quote = 0;
	len = ft_strlen(line);
	newline = ft_calloc(sizeof(char), (len + 1));
	while (*line)
	{
		if (*line == '$' && not_env_key(line[1]))
			newline[i++] = *line++;
		else if (*line == '$' && !quote)
			i += make_new_line(env, &newline, &line, &len);
		else
		{
			if (*line == '\\' && line[1] == '$')
				line++;
			else if (*line == '\'')
				quote = quote ? 0 : 1;
			newline[i++] = *line++;
		}
	}
	return (newline);
}

void	delete_env(t_lstenv *env, char *name)
{
	t_env_node	*cur;

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
			free(name);
			if (cur->val)
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
