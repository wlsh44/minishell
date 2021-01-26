/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:49:12 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 22:46:38 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

int	execute(t_minishell *ms);
int	execute_command(t_minishell *ms, t_node *cur);
int	ft_exit(t_minishell *ms);
int	ft_echo(t_minishell *ms, t_node *node);
int	ft_pwd(t_node *node);
int	ft_cd(t_minishell *ms, t_node *cur);
int	ft_env(t_minishell *ms);
int	ft_export(t_minishell *ms, t_node *cur);
int	ft_unset(t_minishell *ms, t_node *cur);
int	ft_bin(t_minishell *ms, t_node *cur);
int	ft_redirect_input(t_node *cur);
int	ft_redirect_output(t_minishell *ms, t_node *cur);
int	fork_process(t_minishell *ms, t_node *cur);

#endif
