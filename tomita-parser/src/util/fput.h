#pragma once

#include <util/system/defaults.h>
#include <util/system/valgrind.h>

#include <cstdio>

#define fput_a fput
#define fget_a fget

#ifdef __FreeBSD__
#include <cstring>

#if !defined(NDEBUG) && __GNUC__==3 && __GNUC_MINOR__==4
#undef fput_a
#undef fget_a
template <class T>
inline size_t fput_a(FILE *F, const T& a) {
    if (EXPECT_TRUE(F->_w >= int(sizeof(a)))) {
        memcpy(F->_p, &a, sizeof(a));
        F->_p += sizeof(a);
        F->_w -= sizeof(a);
        return 1;
    } else {
        return fwrite(&a, sizeof(a), 1, F);
    }
}

template <class T>
inline size_t fget_a(FILE *F, T& a) {
    if (EXPECT_TRUE(F->_r >= int(sizeof(a)))) {
        memcpy(&a, F->_p, sizeof(a));
        F->_p += sizeof(a);
        F->_r -= sizeof(a);
        return 1;
    } else {
        return fread(&a, sizeof(a), 1, F);
    }
}
#endif

template <class T>
FORCED_INLINE size_t fput(FILE *F, const T& a) {
    if (EXPECT_TRUE(F->_w >= int(sizeof(a)))) {
        memcpy(F->_p, &a, sizeof(a));
        F->_p += sizeof(a);
        F->_w -= sizeof(a);
        return 1;
    } else {
        return fwrite(&a, sizeof(a), 1, F);
    }
}

template <class T>
FORCED_INLINE size_t fget(FILE *F, T& a) {
    if (EXPECT_TRUE(F->_r >= int(sizeof(a)))) {
        memcpy(&a, F->_p, sizeof(a));
        F->_p += sizeof(a);
        F->_r -= sizeof(a);
        return 1;
    } else {
        return fread(&a, sizeof(a), 1, F);
    }
}

inline size_t fsput(FILE *F, const char *s, size_t l) {
    VALGRIND_CHECK_READABLE(s, l);

    if ((size_t)F->_w >= l) {
        memcpy(F->_p, s, l);
        F->_p += l;
        F->_w -= l;
        return l;
    } else {
        return fwrite(s, 1, l, F);
    }
}

inline size_t fsget(FILE *F, char *s, size_t l) {
    if ((size_t)F->_r >= l) {
        memcpy(s, F->_p, l);
        F->_p += l;
        F->_r -= l;
        return l;
    } else {
        return fread(s, 1, l, F);
    }
}
#else
template <class T>
FORCED_INLINE size_t fput(FILE *F, const T& a) {
    return fwrite(&a, sizeof(a), 1, F);
}

template <class T>
FORCED_INLINE size_t fget(FILE *F, T& a) {
    return fread(&a, sizeof(a), 1, F);
}

inline size_t fsput(FILE *F, const char *s, size_t l) {
#ifdef WITH_VALGRIND
    VALGRIND_CHECK_READABLE(s, l);
#endif
    return fwrite(s, 1, l, F);
}

inline size_t fsget(FILE *F, char *s, size_t l) {
    return fread(s, 1, l, F);
}
#endif
