/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:50:48 by schang            #+#    #+#             */
/*   Updated: 2021/01/25 21:51:11 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int	parsing(t_minishell *ms);

int	get_arg_num(char *line);
int	get_arg_size(char *line);
int	get_arg_char(char **line, char *arg);
int	get_arg(char **line, char **arg);
int	get_arg_export_unset(char **line, char *arg);
int	get_arg_echo(char **line, char **arg);

int	parsing_cd(t_lstcmd *cmd, char **line);
int	parsing_echo(t_lstcmd *cmd, char **line);
int	parsing_pwd(t_lstcmd *cmd, char **line);
int	parsing_env(t_lstcmd *cmd, char **line);
int	parsing_export(t_lstcmd *cmd, char **line);
int	parsing_unset(t_lstcmd *cmd, char **line);
int	parsing_exit(t_lstcmd *cmd, char **line);
int	parsing_pipe(t_lstcmd *cmd);
int	parsing_redirect_output(t_lstcmd *cmd, char **line);
int	parsing_redirect_input(t_lstcmd *cmd, char **line);
int	parsing_double_redirect(t_lstcmd *cmd, char **line);
int	parsing_bin(t_lstcmd *cmd, char **line);

int	parsing_type(char **line);

#endif
