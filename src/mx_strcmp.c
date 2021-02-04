#include "main.h"

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
