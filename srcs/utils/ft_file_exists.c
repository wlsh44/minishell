/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_exists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schang <schang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 20:53:46 by schang            #+#    #+#             */
/*   Updated: 2021/01/31 00:01:33 by schang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_permission(struct stat status)
{
	/*
	printf("user\n");
	printf("%s", (status.st_mode & S_IRWXU) ? "o" : "-");
	printf("%s", (status.st_mode & S_IRUSR) ? "r" : "-");
	printf("%s", (status.st_mode & S_IWUSR) ? "w" : "-");
	printf("%s", (status.st_mode & S_IXUSR) ? "x" : "-");

	printf("\ngroup\n");
	printf("%s", (status.st_mode & S_IRWXG) ? "o" : "-");
	printf("%s", (status.st_mode & S_IRGRP) ? "r" : "-");
	printf("%s", (status.st_mode & S_IWGRP) ? "w" : "-");
	printf("%s", (status.st_mode & S_IXGRP) ? "x" : "-");

	printf("\nothers\n");
	printf("%s", (status.st_mode & S_IRWXO) ? "o" : "-");
	printf("%s", (status.st_mode & S_IROTH) ? "r" : "-");
	printf("%s", (status.st_mode & S_IWOTH) ? "w" : "-");
	printf("%s", (status.st_mode & S_IXOTH) ? "x" : "-");
	*/

	if (status.st_mode & S_IRWXU)
	{
		if (status.st_mode & S_IWUSR)
		{
			if (status.st_mode & S_IXUSR)
			{
				if (status.st_mode & S_IRUSR)
					return (1);
			}
		}
		else if (status.st_mode & S_IRUSR)
		{
			if (status.st_mode & S_IXUSR)
				return (1);
		}
	}
	return (0);
}

int	check_file_permission2(struct stat status)
{
	/*
	printf("user\n");
	printf("%s", (status.st_mode & S_IRWXU) ? "o" : "-");
	printf("%s", (status.st_mode & S_IRUSR) ? "r" : "-");
	printf("%s", (status.st_mode & S_IWUSR) ? "w" : "-");
	printf("%s", (status.st_mode & S_IXUSR) ? "x" : "-");

	printf("\ngroup\n");
	printf("%s", (status.st_mode & S_IRWXG) ? "o" : "-");
	printf("%s", (status.st_mode & S_IRGRP) ? "r" : "-");
	printf("%s", (status.st_mode & S_IWGRP) ? "w" : "-");
	printf("%s", (status.st_mode & S_IXGRP) ? "x" : "-");

	printf("\nothers\n");
	printf("%s", (status.st_mode & S_IRWXO) ? "o" : "-");
	printf("%s", (status.st_mode & S_IROTH) ? "r" : "-");
	printf("%s", (status.st_mode & S_IWOTH) ? "w" : "-");
	printf("%s", (status.st_mode & S_IXOTH) ? "x" : "-");
	*/

	if (status.st_mode & S_IRWXU)
	{
		if (status.st_mode & S_IXUSR)
			return (1);
		else if (status.st_mode & S_IWUSR)
		{
			if (status.st_mode & S_IXUSR)
			{
				if (status.st_mode & S_IRUSR)
					return (1);
			}
		}
		else if (status.st_mode & S_IRUSR)
		{
			if (status.st_mode & S_IXUSR)
				return (1);
		}
	}
	return (0);
}

int	ft_file_exists2(const char *file)
{
	struct stat	status;
	int			exists;

	exists = stat(file, &status);
	printf("exists: %d\n", exists);
	if (exists < 0)
	{
		g_exit_status = NO_DIRECTORY;
		return (ERR_NO_SUCH_FILE);
	}
	if (!check_file_permission2(status))
	{
		g_exit_status = PERMISSION_DENIED;
		return (0);
	}
	else if (S_ISDIR(status.st_mode))
	{
		g_exit_status = IS_A_DIRECTORY;
		return (0);
	}
	return (1);
}

int	ft_file_exists(const char *file)
{
	struct stat	status;
	int			exists;

	exists = stat(file, &status);
	if (exists < 0)
	{
		g_exit_status = NO_DIRECTORY;
		return (0);
	}
	if (!check_file_permission(status))
	{
		g_exit_status = PERMISSION_DENIED;
		return (0);
	}
	else if (S_ISDIR(status.st_mode))
	{
		g_exit_status = IS_A_DIRECTORY;
		return (0);
	}
	return (1);
}

int	ft_check_file(const char *file)
{
	struct stat	status;
	int			exists;

	exists = stat(file, &status);
	if (exists < 0)
		return (NO_DIRECTORY);
	if (!check_file_permission(status))
		return (PERMISSION_DENIED);
	if (S_ISDIR(status.st_mode))
		return (IS_A_DIRECTORY);
	printf("pass!\n");
	return (1);
}

int	ft_check_file(char *path)
{
	return (0);
}

char	**get_path_list(t_minishell *ms)
{
	char	*path;
	char	**dir;

	if (!(path = get_env_value(ms->env, "PATH"))
		|| !(dir = ft_split(path, ':')))
		return (NULL);
	return (dir);
}

int	ft_check_cmd(t_minishell *ms, char *cmd)
{
	char **dir;

	if (!(dir = get_path_list(ms)))

}
