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

#include "gzunpack.h"

int main(int argc, char *argv[])
{
    char *packedFileName;
    FILE *packedFileHandle;
    GzFileHeader *gzFileHeader;
    FILE *unpackedFileHandle;
    int result;

    printf("GZ unpack tool\n\n");

    if (argc != 2)
    {
        printf("Usage:\n\tgzunpack <gz-file-name>\n");
        return -1;
    }

    packedFileName = argv[1];

    printf("Unpacking '%s'\n\n", packedFileName);

    packedFileHandle = fopen(packedFileName, "rb");

    if (NULL == packedFileHandle) {
        printf("Error opening file '%s'\n", packedFileName);
        return 0;
    }

    gzFileHeader = gzUnpackHeader(packedFileHandle);

    if (0 == gzFileHeader) {
        printf("Error reading file header\n");
    }
    else {

        printf("Header:\n");
        printf("\tcompressionMethod = %d\n", gzFileHeader->compressionMethod);
        printf("\tflags = %d\n", gzFileHeader->flags);
        printf("\tmodificationTime = %d\n", gzFileHeader->modificationTime);
        printf("\textraFlags = %d\n", gzFileHeader->extraFlags);
        printf("\toperatingSystem = %d\n", gzFileHeader->operatingSystem);
        printf("\textraFieldLength = %d\n", gzFileHeader->extraFieldLength);
        printf("\toriginalFileName = '%s'\n", gzFileHeader->originalFileName);
        printf("\tfileComment = '%s'\n", gzFileHeader->fileComment);
        printf("\theaderCrc = %d\n\n", gzFileHeader->headerCrc);

        unpackedFileHandle = fopen(gzFileHeader->originalFileName, "wb");

        if (NULL == unpackedFileHandle) {
            printf("Error opening file '%s'\n", gzFileHeader->originalFileName);
        }
        else
        {
            if (fseek(packedFileHandle, 0, SEEK_SET)) {
                printf("Error rewinding file\n");
            }
            else {
                result = gzUnpackFile(packedFileHandle, unpackedFileHandle);
                if (result){
                    printf("Error %d unpacking file\n", result);
                }
                else {
                    printf("File '%s' unpacked successfully\n", gzFileHeader->originalFileName);
                }
            }

            fclose(unpackedFileHandle);
        }

        gzFreeHeader(gzFileHeader);
    }

    fclose(packedFileHandle);

    return 0;
}
