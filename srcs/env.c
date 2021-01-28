/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:59:11 by schang            #+#    #+#             */
/*   Updated: 2021/01/26 21:28:34 by schang           ###   ########.fr       */
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
char	*dup_env_value(t_lstenv *env, char *name, int size)
{
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail)
	{
		if (ft_strncmp(cur->name, name, size) == 0)
		{
			return (ft_strdup(cur->val));
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}

void	concatenate(char **line, char *val)
{
	char *tmp;

	tmp = *line;
	*line = ft_strjoin(*line, val);
	free(tmp);
}

int make_new_line(t_lstenv *env, char **new_line, char **sub, char *ptr)
{
	int size;
	char *val;

	size = 0;
	while (ft_isalnum(ptr[size]) || ptr[size] == '_')
		size++;
	val = dup_env_value(env, ptr, size);
	concatenate(sub, val);
	concatenate(new_line, *sub);
	free(*sub);
	free(val);
	return (size);
}

char *parsing_env_val(t_lstenv *env, char *line)
{
	char *new_line;
	char *sub;
	char *ptr;
	int size;
	int start;
	
	start = 0;
	ptr = line;
	new_line = ft_strchr(line, '$') ? ft_strdup("") : ft_strdup(line);
	while ((ptr = ft_strchr(ptr, '$')))
	{
		size = 0;
		sub = ft_substr(line, start, ptr - line - start);
		ptr++;
		size = make_new_line(env, &new_line, &sub, ptr);
		start = ptr - line + size;
		if (!ft_strchr(ptr, '$') && *ptr)
			concatenate(&new_line, line + start);
	}
	return (new_line);
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
