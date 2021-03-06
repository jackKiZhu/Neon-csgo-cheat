#pragma once

__forceinline char* s_strcpy(char *s1, const char *s2)
{
	char *s = s1;
	while ((*s++ = *s2++) != 0)
		;
	return (s1);
}

__forceinline int s_strcmp(const char *s1, const char *s2)
{
	for (; *s1 == *s2; s1++, s2++)
		if (*s1 == '\0')
			return 0;
	return ((*(unsigned char *)s1 < *(unsigned char *)s2) ? -1 : +1);
}