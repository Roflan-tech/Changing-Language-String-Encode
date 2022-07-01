#include <stdio.h>
#include <string.h>

int utf8_length(const char *s) {
    if (*s < 128)
        return 1;   // regular ASCII byte
    if (*s < 128+64)
        return -1;  // continuation byte, invalid code point
    if (*s < 128+64+32)
        return 2;   // code-point encoded on 2 bytes
    if (*s < 128+64+32+16)
        return 3;   // code-point encoded on 3 bytes
    if (*s < 128+64+32+16+8)
        return 4;   // code-point encoded on 4 bytes
    return -1;      // invalid code point
}

void test(const char *s) {
    int len = strlen(s);
    int i, nbytes;

    printf("Hex representation of %s:\n", s);
    for (i = 0; i <= len; i++) {
        printf("%02X ", (unsigned char)s[i]);
    }
    printf("\n");
    for (i = 0; i < len; i += nbytes) {
        nbytes = utf8_length(s + i);
        if (nbytes < 0) {
            printf("invalid encoding at %d\n", i);
        } else {
            printf("%*s%.*s ",
                   nbytes * 3 - 2 - (nbytes > 2), "",
                   nbytes, s + i);
        }
    }
    printf("\n\n");
}

int main() {
    char buf[128];
    char abc[] = "Привет";

    test("hello");  // English
    test(abc);      // Russian
    test("你好");   // Mandarin

    strcpy(buf, "m");
    strcat(buf, abc + utf8_length(abc));

    printf("modified string: %s\n", buf);
    test(buf);

    return 0;
}