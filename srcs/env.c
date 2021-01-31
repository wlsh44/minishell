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

char	*get_env_value(t_lstenv *env, char *name)
{
	t_env_node	*cur;
	char		*str;

	cur = env->head->next;
	if (name[0] == '?')
		return (ft_itoa(g_exit_status));
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
	if (name[0] == '?')
		return (ft_itoa(g_exit_status));
	while (cur != env->tail)
	{
		if (ft_strncmp(cur->name, name, size) == 0 &&
			ft_strncmp(cur->name, name, ft_strlen(cur->name)) == 0)
		{
			return (ft_strdup(cur->val));
		}
		cur = cur->next;
	}
	return (ft_strdup(""));
}

void	concatenate(char **line, char *val, int len1, int len2)
{
	char *newline;
	int i;
	int j;

	j = 0;
	i = 0;
	newline = ft_calloc(sizeof(char), len1 + len2 + 1);
	while ((*line)[i])
	{
		newline[i] = (*line)[i];
		i++;
	}
	while (val[j])
		newline[i++] = val[j++];
	free(*line);
	*line = newline;
}

int make_new_line(t_lstenv *env, char **newline, char **line, int *len)
{
	int size;
	int ret;
	char *val;

	(*line)++;
	size = 0;
	while (ft_isalnum((*line)[size]) ||
		(*line)[size] == '_' || (*line)[size] == '?')
		size++;
	val = dup_env_value(env, *line, size);
	ret = ft_strlen(val);
	concatenate(newline, val, *len, ret);
	*len += ret;
	free(val);
	(*line) += size;
	return (ret);
}

bool not_env_key(char c)
{
	if (ft_isspace(c) || c == '\0' || c == '\\')
		return (true);
	return (false);
}

char *parsing_env_val(t_lstenv *env, char *line)
{
	char *newline;
	int quote;
	int i;
	int len;

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
