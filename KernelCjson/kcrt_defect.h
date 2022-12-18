#pragma once
#include <limits.h>
#include <ctype.h>

static unsigned long long strtoull(
    char const* _String,
    char** _EndPtr,
    int _Radix
)
{
    const char* s = _String;
    unsigned long long acc;
    int c;
    unsigned long long cutoff;
    int neg = 0, cutlim, any;
    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    }
    else if (c == '+')
        c = *s++;
    if ((_Radix == 0 || _Radix == 16) &&
        c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        _Radix = 16;
    }
    if (_Radix == 0)
        _Radix = c == '0' ? 8 : 10;
    cutoff = (unsigned long long)ULLONG_MAX / (unsigned long long)_Radix;
    cutlim = (unsigned long long)ULLONG_MAX % (unsigned long long)_Radix;
    for (acc = 0, any = 0;; c = *s++) {
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= _Radix)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= _Radix;
            acc += c;
        }
    }
    if (any < 0) {
        acc = ULLONG_MAX;
    }
    else if (neg)
        acc = 0 - acc;
    if (_EndPtr != 0)
        *_EndPtr = (char*)(any ? s - 1 : _String);
    return (acc);
}
