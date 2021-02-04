#include "main.h"

char *mx_strcat(char *s1, const char *s2) {
    int i = mx_strlen(s1);
    
    while (*s2 != '\0') {
        s1[i++] = *s2;
        ++s2;
    }
    s1[i] = '\0';
    return s1;
}

char *mx_strcpy(char *dst, const char *src) {
    int i = 0;

    while (true) {
        if (&dst[i] != &src[0]) {
            dst[i] = src[i];
            if (src[i] == '\0')
                return dst;
        }
        else {
            dst[i-1] = '\0';
            return dst;
        }
        ++i;
    }
}

char *mx_strdup(const char *str) {
    int length = mx_strlen(str);
    char *copy_str = mx_strnew(length);
    
    if (copy_str == NULL)
        return "";
    
    return mx_strcpy(copy_str, str);
}

char *mx_strjoin(char const *s1, char const *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;
    else if (s1 == NULL)
        return mx_strdup(s2);
    else if (s2 == NULL)
        return mx_strdup(s1);
    
    int size_s1 = mx_strlen(s1);
    int size_s2 = mx_strlen(s2);
                            
    char *new_str = mx_strnew(size_s1 + size_s2);
    new_str = mx_strcpy(new_str, s1);
    new_str = mx_strcat(new_str, s2);
    return new_str;
}

int mx_strlen(const char *s) {
    int len = 0;
    
    while (s[len] != '\0')
        ++len;

    return len;
}

char *mx_strnew(const int size) {
    if (size <= 0)
        return NULL;
    
    char *str = (char*)malloc(size + 1);
    
    if (str == NULL)
        return NULL;
    
    int i;
    
    for (i = 0; i <= size; ++i)
        str[i] = '\0';
    
    return str;
}

int mx_strcmp(const char *s1, const char *s2) {
    while (true) {
        if (*s1 == *s2) {
            if (*s1 == '\0')
                return 0;
            ++s1;
            ++s2;
            continue;
        }
        return *s1 - *s2;
    }
}

char *gennstr(int n)
{
    char *randomString;
    randomString = (char *)malloc(sizeof(char) * (++n));
    for(int i = 0; i < n; ++i) {
        randomString[i] = (char) RAND(33,126);
    }
    randomString[n] = '\0';
    return randomString;
}

