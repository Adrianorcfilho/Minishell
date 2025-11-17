#include <minilibft.h>

char *ft_strchr(const char *s, int c)
{
    unsigned int    i;
    char            temp;

    temp = c;
    i = 0;
    while (s[i])
    {
        if (s[i] == temp)
            return ((char *) &s[i]);
        i++;
    }
    if (s[i] == temp)
        return ((char *) &s[i]);
    return (NULL);
}
