// strlen doesn't take into account the null terminator, we do need the length for malloc though.
#define STRLEN(str) strlen(str) + 1