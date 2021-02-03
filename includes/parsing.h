/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:50:48 by schang            #+#    #+#             */
/*   Updated: 2021/02/03 22:28:33 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

int	parsing(t_minishell *ms, char *line);

int	get_arg_num(char *line);
int	get_arg_size(char *line);
int	get_arg_char(char **line, char *arg);
int	get_arg(char **line, char **arg);
int	get_arg_char_basic(char **line, char *arg, int(*endline_condition)(char c));
int get_last_char(char *line);

int	ft_endline_condition(char c);
int	get_arg_quote(char **line, char **arg);
int	get_arg_key_quote(char **line, char **arg);
int	is_key_char(char c);
int	get_arg_key(char **line, char **arg);

int	get_arg_export(char **line, char *arg);
int	get_arg_unset(char **line, char *arg);
int	get_arg_echo(char **line, char **arg);
int	parsing_cd(t_lstcmd *cmd, char **line);
int	parsing_echo(t_minishell *ms, char **line);
int	parsing_pwd(t_lstcmd *cmd, char **line);
int	parsing_env(t_lstcmd *cmd, char **line);
int	parsing_export(t_lstcmd *cmd, char **line);
int	parsing_unset(t_lstcmd *cmd, char **line);
int	parsing_exit(t_lstcmd *cmd, char **line);
int	parsing_pipe(t_lstcmd *cmd, char **line);
int	parsing_redirect_output(t_lstcmd *cmd, char **line);
int	parsing_redirect_input(t_lstcmd *cmd, char **line);
int	parsing_double_redirect(t_lstcmd *cmd, char **line);
int	parsing_bin(t_lstcmd *cmd, char **line, char *name);
int	parsing_semicolon(t_minishell *ms, char **line);

int	endline_condition_quote(char c);
int	sub_cmd(char *line, char **sub, int start);

int	valid_echo_option(char **line);

#endif
