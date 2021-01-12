#include "minishell.h"

char *get_env_value(t_lstenv *env, char *name) {
	t_env_node *cur;

	cur = env->head->next;
	while (cur != env->tail) {
		if (ft_strcmp(cur->name, name) == 0) {
			return (cur->val);
		}
		cur = cur->next;
	}
	return (NULL);
}



void push_back_env(t_lstenv *env, char *name, char *val) {
	t_env_node *node;

	node = malloc(sizeof(t_env_node));
	node->name = name;
	node->next = val;
	node->prev = env->tail->prev;
	node->next = env->tail;
	env->tail->prev->next = node;
	env->tail->prev = node;
}

void init_env(t_minishell *ms, char *envp[]) {
	char **buf;
	char *name;
	char *val;
	char *ptr;

	while (*envp && !(val = NULL)) {
		ptr = ft_strchr(*envp, '=');
		if (ptr == NULL || !*(ptr + 1)) {
			name = ft_strdup(*envp);
		} else {
			*ptr++ = '\0';
			name = ft_strdup(*envp);
			val = ft_strdup(ptr);
		}
		push_back_env(ms->env, name, val);
		envp++;
	}
}