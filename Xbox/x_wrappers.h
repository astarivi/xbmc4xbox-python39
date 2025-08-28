#ifndef _X_WRAPPERS_H_
#define _X_WRAPPERS_H_

// region Stupidly unsafe wrappers.
static int wcscpy_s_wrapper(wchar_t *dest, size_t size, const wchar_t *src) {
    wcscpy(dest, src);   // ignore length for Xbox
    return 0;
}

static int wcscat_s_wrapper(wchar_t *dest, size_t size, const wchar_t *src) {
    wcscat(dest, src);   // ignore length for Xbox
    return 0;
}

static wchar_t *wcstok_s_compat(wchar_t *str, const wchar_t *delim, wchar_t **context) {
    static wchar_t *saved;
    if (str != NULL) {
        saved = str;
    } else if (saved == NULL) {
        return NULL;
    }
    wchar_t *token_start = saved;
    wchar_t *p = saved;
    while (*p) {
        if (wcschr(delim, *p)) {
            *p = L'\0';
            saved = p + 1;
            return token_start;
        }
        p++;
    }
    saved = NULL;
    return token_start;
}

#define wcstok_s wcstok_s_compat
#define wcscpy_s(dest, size, src) wcscpy_s_wrapper(dest, size, src)
#define wcscat_s(dest, size, src) wcscat_s_wrapper(dest, size, src)
#define wcsncpy_s(dest, size, src, n) wcsncpy(dest, src, n)
#define wcsnlen_s(src, maxlen) wcslen(src)
#define _chsize_s(fd, length) _chsize(fd, (long)(length))
#define memcpy_s(dest, destSize, src, count) memcpy(dest, src, count)
// endregion

#endif