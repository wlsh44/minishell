/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:54:34 by schang            #+#    #+#             */
/*   Updated: 2021/01/27 21:21:33 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	push_back(t_lstcmd *cmd, int type, char *arg);
void	push_back_normal(t_lstcmd *cmd, int type, char *name, char *arg);
t_node	*pop(t_lstcmd *cmd);
void	clear(t_lstcmd *cmd);
void	show(t_lstcmd *cmd);
void	delete_cmd(t_node *cur);
int		ft_file_exists(const char *file);
void	free_double_char(char **str);
char	**get_env_list(t_minishell *ms);
char	**ft_bin_args(char *cmd, char *arg);
char	*ft_check_abs_path(t_minishell *ms, char *name);
void	show(t_lstcmd *cmd);
int		endline_condition_quote(char c);

#endif
