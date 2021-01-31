/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 21:48:57 by schang            #+#    #+#             */
/*   Updated: 2021/01/30 22:29:29 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

# define ERR_NO_DIRECTORY 1
# define ERR_SYNTAX_ERROR 2
# define ERR_PERMISSION_DENIED 126
# define ERR_IS_A_DIRECTORY 126
# define ERR_COMMAND_NOT_FOUND 127
# define ERR_NO_SUCH_FILE 127

void	cmd_error(int err);
void	execute_error(int err);
void	shell_cmd_error(char *path, int err);
void	shell_exec_error(char *path, int err);

#endif
