#include "minishell.h"
#include <stdio.h>

int execute_cd(t_minishell *ms, t_node *cur) {
	if (ft_strcmp(cur->arg, "") == 0) {
		chdir(get_env_value(ms->env, "HOME"));
	} else {
		if (chdir(cur->arg) < 0) {
			return (NO_DIRECTORY);
		}
	}
	return (0);
}

int export_print_env(t_lstenv *env) {
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail) {
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
		write(STDOUT_FILENO, "=", 1);
		if (cur->val) {
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, cur->val, ft_strlen(cur->val));
			write(STDOUT_FILENO, "\"", 1);
		}
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (0);
}

int execute_export(t_minishell *ms, t_node *cur) {
	char *ptr;
	char **args;
	char **tmp;
	char *name;
	char *val;

	if (ft_strcmp(cur->arg, "") == 0) {
		return(export_print_env(ms->env));
	}
	args = ft_split(cur->arg, ' ');
	tmp = args;
	while (*args && !(val = NULL)) {
		ptr = ft_strchr(*args, '=');
		if (ptr == NULL) {
			if ((name = parse_env_val(ms->env, *args)) == NULL) {
				return (export_print_env(ms->env));
			}
		} else {
			*ptr++ = '\0';
			if ((name = parse_env_val(ms->env, *args)) == NULL) {
				return (NOT_VAILD_IDENTIFIER);
			}
			val = parse_env_val(ms->env, ptr);
			push_back_env(ms->env, name, val);
		}
		args++;
	}
	while (*tmp) {
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	//free(tmp);
	return (0);
}

int execute_env(t_minishell *ms) {
	t_env_node *cur;

	cur = ms->env->head->next;
	while (cur != ms->env->tail) {
		write(STDOUT_FILENO, cur->name, ft_strlen(cur->name));
		write(STDOUT_FILENO, "=", 1);
		if (cur->val) {
			write(STDOUT_FILENO, cur->val, ft_strlen(cur->val));
		}
		write(STDOUT_FILENO, "\n", 1);
		cur = cur->next;
	}
	return (0);
}

int execute_unset(t_minishell *ms, t_node *cur) {
	char *ptr;
	char **args;
	char **tmp;
	char *name;
	char *val;

	args = ft_split(cur->arg, ' ');
	tmp = args;
	while (*args && !(val = NULL)) {
		ptr = ft_strchr(*args, '=');
		if (ptr != NULL) {
			return (NOT_VAILD_IDENTIFIER);
		} else {
			if ((name = parse_env_val(ms->env, *args)) == NULL) {
				continue;
			}
			delete_env(ms->env, name);
		}
		args++;
	}
	while (*tmp) {
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	// free(tmp);
	// tmp = NULL;
	return (0);
}

int	execute_exit(t_minishell *ms)
{
	ft_exit(ms);
	return (0);
}

int	execute_echo(t_node *node)
{
	return (ft_echo(node));
}

int	execute_pwd(t_node *node)
{
	return (ft_pwd(node));
}

int execute(t_minishell *ms) {
	t_node *cur;
	int ret;

	cur = ms->cmd->head->next;
	while (cur != ms->cmd->tail && !(ret = 0)) {
		if (cur->type == TYPE_CD)
			ret = execute_cd(ms, cur);
		else if (cur->type == TYPE_ENV)
			ret = execute_env(ms);
		else if (cur->type == TYPE_EXPORT)
			ret = execute_export(ms, cur);
		else if (cur->type == TYPE_UNSET)
			ret = execute_unset(ms, cur);
		else if (cur->type == TYPE_EXIT)
			ret = execute_exit(ms);
		else if (cur->type == TYPE_ECHO || cur->type == TYPE_ECHO_N)
			ret = execute_echo(cur);
		else if (cur->type == TYPE_PWD)
			ret = execute_pwd(cur);
		cur = cur->next;
	}
	return (0);
}
