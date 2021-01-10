#ifndef UTILS_H
#define UTILS_H

#include "minishell.h"

void push_back(t_lstcmd *cmd, int type, char *arg);
t_node *pop(t_lstcmd *cmd);
void clear(t_lstcmd *cmd);
void show(t_lstcmd *cmd);


char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(char c);
int		ft_isalpha(char c);
int		ft_isseparator(char c);
int		ft_isquote(char c);
int		ft_isdigit(char c);


#endif