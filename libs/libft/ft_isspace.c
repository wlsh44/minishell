#include "libft.h"

int		ft_isspace(char c)
{
	return ((c == '\t' || c == '\v' || c == '\n' ||
c == '\r' || c == '\f' || c == ' '));
}
