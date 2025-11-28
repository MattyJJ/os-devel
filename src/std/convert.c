#include <std/convert.h>

char *utoa(unsigned int value, char *buffer, int base) {
    char *p = buffer;
    char *p1, *p2;
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unsigned int tmp;

    if (base < 2 || base > 36) {
        *buffer = '\0';
        return buffer;
    }

    do {
        tmp = value % base;
        *p++ = digits[tmp];
        value /= base;
    } while (value);

    *p = '\0';

    p1 = buffer;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1++ = *p2;
        *p2-- = tmp;
    }

    return buffer;
}

char *itoa(int value, char *buffer, int base) {
    char *buf = buffer;
    unsigned int uvalue;
    int is_negative = 0;

    if (base < 2 || base > 36) {
        *buffer = '\0';
        return buffer;
    }

    if (value == 0) {
        *buf++ = '0';
        *buf = '\0';
        return buffer;
    }

    if (value < 0 && base == 10) {
        is_negative = 1;
        uvalue = (unsigned int)(-(value));
    } else {
        uvalue = (unsigned int)value;
        if (value < 0)
            is_negative = 1;
    }

    utoa(uvalue, buf, base);

    if (is_negative) {
        while (*buf)
            buf++;
        do {
            *(buf + 1) = *buf;
        } while (buf-- > buffer);
        *buffer = '-';
    }

    return buffer;
}

int atoi(const char *str) {
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    int sign = 1;
    if (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -1;
        str++;
    }
    int result = 0;
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

long atol(const char *str) {
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    int sign = 1;
    if (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -1;
        str++;
    }
    long result = 0;
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

long long atoll(const char *str) {
    while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
        str++;
    int sign = 1;
    if (*str == '-' || *str == '+') {
        if (*str == '-')
            sign = -1;
        str++;
    }
    long long result = 0;
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    return sign * result;
}

long strtol(const char *nptr, char **endptr, int base) {
    while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
        nptr++;
    int sign = 1;
    if (*nptr == '-' || *nptr == '+') {
        if (*nptr == '-')
            sign = -1;
        nptr++;
    }
    if (base == 0) {
        if (*nptr == '0') {
            if (nptr[1] == 'x' || nptr[1] == 'X')
                base = 16;
            else
                base = 8;
        } else
            base = 10;
    }
    if ((base == 16) && (*nptr == '0') && (nptr[1] == 'x' || nptr[1] == 'X'))
        nptr += 2;

    long result = 0;
    while (1) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9')
            digit = *nptr - '0';
        else if (*nptr >= 'a' && *nptr <= 'z')
            digit = *nptr - 'a' + 10;
        else if (*nptr >= 'A' && *nptr <= 'Z')
            digit = *nptr - 'A' + 10;
        else
            break;
        if (digit >= base)
            break;
        result = result * base + digit;
        nptr++;
    }
    if (endptr)
        *endptr = (char *)nptr;
    return sign * result;
}

unsigned long strtoul(const char *nptr, char **endptr, int base) {
    while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
        nptr++;
    if (*nptr == '-' || *nptr == '+')
        nptr++;
    if (base == 0) {
        if (*nptr == '0') {
            if (nptr[1] == 'x' || nptr[1] == 'X')
                base = 16;
            else
                base = 8;
        } else
            base = 10;
    }
    if ((base == 16) && (*nptr == '0') && (nptr[1] == 'x' || nptr[1] == 'X'))
        nptr += 2;

    unsigned long result = 0;
    while (1) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9')
            digit = *nptr - '0';
        else if (*nptr >= 'a' && *nptr <= 'z')
            digit = *nptr - 'a' + 10;
        else if (*nptr >= 'A' && *nptr <= 'Z')
            digit = *nptr - 'A' + 10;
        else
            break;
        if (digit >= base)
            break;
        result = result * base + digit;
        nptr++;
    }
    if (endptr)
        *endptr = (char *)nptr;
    return result;
}

unsigned long long strtoull(const char *nptr, char **endptr, int base) {
    while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
        nptr++;
    if (*nptr == '-' || *nptr == '+')
        nptr++;
    if (base == 0) {
        if (*nptr == '0') {
            if (nptr[1] == 'x' || nptr[1] == 'X')
                base = 16;
            else
                base = 8;
        } else
            base = 10;
    }
    if ((base == 16) && (*nptr == '0') && (nptr[1] == 'x' || nptr[1] == 'X'))
        nptr += 2;

    unsigned long long result = 0;
    while (1) {
        int digit;
        if (*nptr >= '0' && *nptr <= '9')
            digit = *nptr - '0';
        else if (*nptr >= 'a' && *nptr <= 'z')
            digit = *nptr - 'a' + 10;
        else if (*nptr >= 'A' && *nptr <= 'Z')
            digit = *nptr - 'A' + 10;
        else
            break;
        if (digit >= base)
            break;
        result = result * base + digit;
        nptr++;
    }
    if (endptr)
        *endptr = (char *)nptr;
    return result;
}
