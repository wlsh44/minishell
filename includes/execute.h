/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:49:12 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 18:05:37 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

int		execute(t_minishell *ms);
int		execute_command(t_minishell *ms, t_node *cur);

void	swap_cmd(t_node *cur);
void	concat_node(t_node *cur, t_node *node);
void	change_cmd_to_arg(t_lstcmd *cmd);
void	sort_cmd(t_lstcmd *cmd);

int		ft_exit(t_minishell *ms);
int		ft_echo(t_minishell *ms, t_node *node);
int		ft_pwd(t_node *node);
int		ft_cd(t_minishell *ms, t_node *cur);
int		ft_env(t_minishell *ms);
int		ft_export(t_minishell *ms, t_node *cur);
int		ft_unset(t_minishell *ms, t_node *cur);
int		ft_bin(t_minishell *ms, t_node *cur);
int		ft_redirect_input(t_node *cur);
int		ft_redirect_output(t_minishell *ms, t_node *cur);
int		fork_process(t_minishell *ms, t_node *cur);

int	ft_exec_file(t_minishell *ms, t_node *node, char *path);
int	ft_exec_command(t_minishell *ms, t_node *node, char *path);

#endif
