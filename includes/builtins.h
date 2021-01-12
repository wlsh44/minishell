/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:39:53 by schang            #+#    #+#             */
/*   Updated: 2021/01/12 22:12:57 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		execute(t_minishell *ms);
void	ft_exit(t_minishell *ms);
int		ft_echo(t_node *node);
int		ft_pwd(t_node *node);

#endif
