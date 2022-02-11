/* replace GENCODECS_DIRECTIVE() and GENCODECS_DESC() with '#' and comments,
 * respectively */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    NONE = 0,
    STRING = 1 << 0,
    DESC = 1 << 1,
    DIRECTIVE = 1 << 2
} state = NONE;

const char *closestr = "";

/* return non-zero on succesful expansion */
static int
expand_desc(char **src, const char tok[], size_t toklen)
{
    if (0 == strncmp(*src, tok, toklen - 1)) {
        state = DESC;
        *src += toklen - 1;
        closestr = " */";
        fputs("/** ", stdout);
        return 1;
    }
    return 0;
}

/* return non-zero on succesful expansion */
static int
expand_directive(char **src, const char tok[], size_t toklen)
{
    if (0 == strncmp(*src, tok, toklen - 1)) {
        state = DIRECTIVE;
        *src += toklen - 1;
        closestr = "";
        fputc('#', stdout);
        return 1;
    }
    return 0;
}

int
main(void)
{
    int open_parens = 0;
    char buf[4096], *p;

    while (fgets(buf, sizeof(buf), stdin)) {
        p = buf;

        while (*p) {
            switch (*p) {
            case '"':
                if (state & STRING)
                    state &= ~STRING;
                else
                    state |= STRING;
                if (!(state & DESC)) fputc(*p, stdout);
                ++p;
                break;
            case '(':
                if (state == DESC) ++open_parens;
                fputc(*p++, stdout);
                break;
            case ')':
                if (state == DESC || state == DIRECTIVE) {
                    if (!open_parens) {
                        state = NONE;
                        fputs(closestr, stdout);
                    }
                    else {
                        --open_parens;
                        fputc(*p, stdout);
                    }
                }
                else {
                    fputc(*p, stdout);
                }
                ++p;
                break;
            case 'G': {
                static const char tok1[] = "GENCODECS_DESC(";
                static const char tok2[] = "GENCODECS_DIRECTIVE(";

                if (state == NONE) {
                    if (expand_desc(&p, tok1, sizeof(tok1))) break;
                    if (expand_directive(&p, tok2, sizeof(tok2))) break;
                }
                fputc(*p++, stdout);
            } break;
            default:
                fputc(*p++, stdout);
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
