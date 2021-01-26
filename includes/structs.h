/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:51:18 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 22:46:58 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_env_node
{
	char				*name;
	char				*val;
	struct s_env_node	*next;
	struct s_env_node	*prev;
}				t_env_node;

typedef struct	s_lstenv
{
	t_env_node	*head;
	t_env_node	*tail;
}				t_lstenv;

typedef struct	s_node
{
	char			*name;
	char			*arg;
	int				type;
	struct s_node	*next;
	struct s_node	*prev;
}				t_node;

typedef struct	s_lstcmd
{
	t_node	*head;
	t_node	*tail;
}				t_lstcmd;

typedef struct	s_minishell
{
	t_lstcmd	*cmd;
	t_lstenv	*env;
	int			oldfd[2];
	int			newfd[2];
	int			exit_status;
	char		*cmd_line;
	char		*oldpath;
	int			err;
}				t_minishell;

#endif
