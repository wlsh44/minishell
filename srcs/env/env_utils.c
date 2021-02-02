/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:29:46 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 22:53:35 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_lstenv *env, char *name)
{
	t_env_node	*cur;

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
	t_env_node	*cur;

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

bool	not_env_key(char c)
{
	if (ft_isspace(c) || c == '\0' || c == '\\')
		return (true);
	return (false);
}

void	concatenate(char **line, char *val, int len1, int len2)
{
	char	*newline;
	int		i;
	int		j;

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

int		make_new_line(t_lstenv *env, char **newline, char **line, int *len)
{
	int		size;
	int		ret;
	char	*val;

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
