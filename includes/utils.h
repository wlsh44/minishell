/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:54:34 by schang            #+#    #+#             */
/*   Updated: 2021/02/02 16:13:58 by schang           ###   ########.fr       */
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
void	free_double_char(char **str);
char	**get_env_list(t_minishell *ms);
char	**ft_bin_args(t_minishell *ms, char *cmd, char *arg);

int		ft_check_abs_path(t_minishell *ms, char *name, char **path);

int		endline_condition_quote(char c);
int		endline_condition_normal(char c);
char	*get_command(char *name);
int		ft_execute_bin(t_minishell *ms, t_node *node, char *path);
int		ft_check_command(t_minishell *ms, const char *cmd, char **path);
int		ft_check_file(const char *file);
int		ft_check_file2(const char *file);
char	**ft_split_path(char *path);

int		command_permission_check(struct stat st);
int		file_permission_check(struct stat st);
int		fileread_permission_check(struct stat st);

int		free_and_null(void *ptr);

#endif
