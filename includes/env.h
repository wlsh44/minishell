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

char	*parse_env_val(t_minishell *ms, char *arg);
void	delete_env(t_lstenv *env, char *name);
void	update_env(t_lstenv *env, char *name, char *val);
void	init_env(t_minishell *ms, char *envp[]);
char	*get_env_value(t_lstenv *env, char *name);
char	*parsing_env_val(t_lstenv *env, char *line);
char	*dup_env_value(t_lstenv *env, char *name, int size);

#endif
