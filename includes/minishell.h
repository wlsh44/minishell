/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:50:03 by schang            #+#    #+#             */
/*   Updated: 2021/01/30 12:51:08 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include "get_next_line.h"
# include "structs.h"
# include "ft_signal.h"
# include "parsing.h"
# include "errors.h"
# include "utils.h"
# include "env.h"
# include "execute.h"

# define PERMISSION_DENIED -12
# define IS_A_DIRECTORY -11
# define HEAD -10
# define TAIL -9
# define NOT_VAILD_IDENTIFIER -8
# define NO_DIRECTORY -7
# define SYNTAX_ERROR -6
# define WRONG_CMD -5
# define NOT_VAILD_ARG -4
# define WRONG_QUOTE -3
# define TOO_MANY_ARG -2
# define NOT_ENOUGH_ARG -1

# define TYPE_REDIRECT_INPUT 0
# define TYPE_SEMICOLON 1
# define TYPE_PIPE 2

# define TYPE_CD 10
# define TYPE_PWD 11
# define TYPE_ECHO_N 12
# define TYPE_EXPORT 13
# define TYPE_ENV 14
# define TYPE_UNSET 15
# define TYPE_ECHO 16
# define TYPE_EXIT 17
# define TYPE_NORMAL 18

# define TYPE_REDIRECT_OUTPUT 20
# define TYPE_DOUBLE_REDIRECT 21

# ifndef PATH_MAX
#  define PATH_MAX 1024
# endif

extern int	g_exit_status;

#endif
