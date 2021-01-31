/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:48:40 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 21:48:53 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

void	delete_env(t_lstenv *env, char *name);
void	update_env(t_lstenv *env, char *name, char *val);
void	init_env(t_minishell *ms, char *envp[]);
char	*parsing_env_val(t_lstenv *env, char *line);

char	*get_env_value(t_lstenv *env, char *name);
char	*dup_env_value(t_lstenv *env, char *name, int size);
bool	not_env_key(char c);
void	concatenate(char **line, char *val, int len1, int len2);
int		make_new_line(t_lstenv *env, char **newline, char **line, int *len);

#endif
