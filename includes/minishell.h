#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "parsing.h"
#include "errors.h"
#include "utils.h"
#include "get_next_line.h"
#include "libft.h"
#include "env.h"

#define SYSTAX_ERROR -6
#define WRONG_CMD -5
#define NOT_VAILD_ARG -4
#define WRONG_QUOTE -3
#define TOO_MANY_ARG -2
#define NOT_ENOUGH_ARG -1

#define TYPE_CD 1
#define TYPE_PWD 2
#define TYPE_ECHO 3
#define TYPE_ECHO_N 4
#define TYPE_EXPORT 5
#define TYPE_ENV 6
#define TYPE_UNSET 7
#define TYPE_PIPE 8
#define TYPE_REDIRECT 9
#define TYPE_DOUBLE_REDIRECT 10
#define TYPE_EXIT 11
#define TYPE_SEMICOLON 12


#endif