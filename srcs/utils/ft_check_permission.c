/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_permission.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 17:53:03 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 20:46:50 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_permission_check(struct stat st)
{
	if (st.st_mode & S_IRWXU && st.st_mode & S_IXUSR)
		return (1);
	return (PERMISSION_DENIED);
}

int	file_permission_check(struct stat st)
{
	if (st.st_mode & S_IRWXU && st.st_mode & S_IRUSR && st.st_mode & S_IXUSR)
		return (1);
	return (PERMISSION_DENIED);
}

int	fileread_permission_check(struct stat st)
{
	if (st.st_mode & S_IRWXU && st.st_mode & S_IRUSR)
		return (1);
	return (PERMISSION_DENIED);
}
