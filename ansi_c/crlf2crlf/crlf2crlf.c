/* ----------------------------------------------------------------
# This software is part of the FreeCodeCollection project
# http://code.google.com/p/freecodecollection/
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

char *crlf2crlf(const char *text1)
{
    size_t length1;
    size_t length11;
    size_t extraLength;
    size_t i1;
    size_t length2;
    char *text2;
    size_t i2;

    // calculate number of single CRs (13 or \r) and LFs (10 or \n)

    length1 = strlen(text1);
    length11 = length1 - 1;

    extraLength = 0;

    for (i1 = 0; i1 < length1; i1++) {
        if (((10 == text1[i1]) && ((0 == i1) || (text1[i1 - 1] != 13))) || ((13 == text1[i1]) && ((i1 == length11) || (text1[i1 + 1] != 10)))) {
            extraLength++;
        }
    }

    // allocate buffer for output string

    length2 = length1 + extraLength;

    text2 = malloc(length2 + 1);

    // make convertion

    i2 = 0;

    for (i1 = 0; i1 < length1; i1++) {
        if (((10 == text1[i1]) && ((0 == i1) || (text1[i1 - 1] != 13))) || ((13 == text1[i1]) && ((i1 == length11) || (text1[i1 + 1] != 10)))) {
            text2[i2] = 13;
            i2++;
            text2[i2] = 10;
        }
        else {
            text2[i2] = text1[i1];
        }

        i2++;
    }

#ifdef CRLF2CRLF_TEST
    if (i2 != length2) {
        printf("counting failure\n");
        exit(1);
    }
#endif

    text2[length2] = 0;

    return text2;
}
