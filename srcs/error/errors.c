/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 22:47:42 by schang            #+#    #+#             */
/*   Updated: 2021/01/30 22:29:21 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_error(int err)
{
	if (err == TOO_MANY_ARG)
		write(1, "too many arg\n", 13);
	else if (err == WRONG_QUOTE)
		write(1, "wrong quote\n", 12);
	else if (err == NOT_ENOUGH_ARG)
		write(1, "not enough arg\n", 15);
	else if (err == NOT_VAILD_ARG)
		write(1, "not vaild arg\n", 13);
	else if (err == WRONG_CMD)
	{
		write(1, "command not found\n", 18);
		g_exit_status = ERR_COMMAND_NOT_FOUND;
	}
	else if (err == SYNTAX_ERROR)
	{
		write(1, "syntax error\n", 13);
		g_exit_status = ERR_SYNTAX_ERROR;
	}
}

void	execute_error(int err)
{
	if (err == NOT_VAILD_IDENTIFIER)
		write(1, "not a vaild identifier\n", 24);
	else if (err == NO_DIRECTORY)
	{
		write(1, "No such file or directory\n", 26);
		g_exit_status = ERR_NO_SUCH_FILE;
	}
	else if (err == WRONG_QUOTE)
		write(1, "wrong quote\n", 12);
	else if (err == IS_A_DIRECTORY)
	{
		g_exit_status = ERR_IS_A_DIRECTORY;
		ft_putendl_fd("is a directory", STDOUT_FILENO);
	}
	else if (err == PERMISSION_DENIED)
	{
		g_exit_status = ERR_PERMISSION_DENIED;
		ft_putendl_fd(strerror(EACCES), STDOUT_FILENO);
	}
}

void	shell_cmd_error(char *path, int err)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	cmd_error(err);
	free(path);
}

void	shell_exec_error(char *path, int err)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd(": ", STDOUT_FILENO);
	execute_error(err);
	free(path);
}
