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

#include "tarunpack.h"

int main(int argc, char *argv[])
{
    char *packedFileName;
    FILE *packedFileHandle;
    char *unpackedFileName;
    FILE *unpackedFileHandle;
    int result;

    printf("TAR unpack tool\n\n");

    if (argc != 3)
    {
        printf("Usage:\n\ttarunpack <tar-file-name> <file-name-to-extract>\n");
        return -1;
    }

    packedFileName = argv[1];
    unpackedFileName = argv[2];

    printf("Unpacking '%s' from '%s'\n\n", unpackedFileName, packedFileName);

    packedFileHandle = fopen(packedFileName, "rb");

    if (NULL == packedFileHandle) {
        printf("Error opening file '%s'\n", packedFileName);
        return 0;
    }

    unpackedFileHandle = fopen(unpackedFileName, "wb");

    if (NULL == unpackedFileHandle) {
        printf("Error opening file '%s'\n", unpackedFileName);
    }
    else
    {
        result = tarUnpackFile(packedFileHandle, unpackedFileName, unpackedFileHandle);

        switch (result) {
        case 0:
            printf("File '%s' unpacked successfully\n", unpackedFileName);
            break;
        case 2:
            printf("File '%s' not found in '%s'\n", unpackedFileName, packedFileName);
            break;
        default:
            printf("Error %d unpacking file\n", result);
            break;
        }

        fclose(unpackedFileHandle);
    }

    fclose(packedFileHandle);

    return 0;
}
