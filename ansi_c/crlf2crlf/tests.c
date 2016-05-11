/* ----------------------------------------------------------------
# This source code is an example from my CodeBlog:
# http://codeblog.vurdalakov.net
#
# Copyright (c) 2011 Vurdalakov
# http://www.vurdalakov.net
# vurdalakov@gmail.com
#
# Permission is hereby granted, free of charge, to any person
# obtaining a copy of this software and associated documentation
# files (the "Software"), to deal in the Software without
# restriction, including without limitation the rights to use,
# copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
---------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crlf2crlf.h"

void print_hex_string(const char *text)
{
    size_t length;
    size_t i;
    const char hexChars[] = "0123456789ABCDEF";

    length = strlen(text);

    printf("%3d: ", length);

    if (length > 16) {
        length = 16;
    }

    for (i = 0; i < length; i++)
    {
        printf("%c%c ", hexChars[(text[i] & 0xF0) >> 4], hexChars[text[i] & 0x0F]);
    }

    printf("\n");
}

void run_test(int index, const char *text, const char *expected)
{
    char *actual;
    int result;

    printf("Test %2d ", index);

    actual = crlf2crlf(text);

    if ((strlen(actual) != strlen(expected)) || (strcmp(actual, expected) != 0))
    {
        printf("failed\n");
        result = 0;
    }
    else {
        printf("OK\n");
        result = 1;
    }

    free(actual);

    if (!result) {
        print_hex_string(text);
        print_hex_string(actual);
        print_hex_string(expected);
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    run_test( 1, "\r\n", "\r\n");
    run_test( 2, "\r\n123", "\r\n123");
    run_test( 3, "123\r\n", "123\r\n");
    run_test( 4, "123\r\n123", "123\r\n123");
    run_test( 5, "\r\n123\r\n", "\r\n123\r\n");

    run_test( 6, "\n", "\r\n");
    run_test( 7, "\n123", "\r\n123");
    run_test( 8, "123\n", "123\r\n");
    run_test( 9, "123\n123", "123\r\n123");
    run_test(10, "\n123\n", "\r\n123\r\n");

    run_test(11, "\r", "\r\n");
    run_test(12, "\r123", "\r\n123");
    run_test(13, "123\r", "123\r\n");
    run_test(14, "123\r123", "123\r\n123");
    run_test(15, "\r123\r", "\r\n123\r\n");

    run_test(16, "\r\r", "\r\n\r\n");
    run_test(17, "\n\n", "\r\n\r\n");
    run_test(18, "\r\r\n\r", "\r\n\r\n\r\n");
    run_test(19, "\n\r\n\n", "\r\n\r\n\r\n");

    run_test(20, "\r123\n", "\r\n123\r\n");
    run_test(21, "\n123\r", "\r\n123\r\n");

    run_test(22, "", "");
    run_test(23, "1", "1");
    run_test(24, "123", "123");

    return 0;
}
