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

#include "tarunpack.h"

#include <stdlib.h>
#include <string.h>

#define TAR_BLOCK_SIZE 512

__int64 tarAtol8(const char *octal, int length)
{
    __int64 number;
    __int64 multiplier;
    char *p;
    int i;
    char c;

    number = 0;
    multiplier = 1;

    p = (char*)octal + length - 1;

    for (i = length - 1; i >= 0; i--, p--) {
        c = *p;

        if (((0 == c) || (' ' == c)) && (0 == number)) { // skip trailing NULs and spaces
            continue;
        }

        if (('0' > c) || (c > '7')) {
            break;
        }

        number += (c - '0') * multiplier;

        multiplier <<= 3;
    }

    return number;
}

__int64 tarAtol256(const char *octal, int length)
{
    __int64 number;
    char *p = (char *)octal;

    number = (0x40 & *p) == 0x40 ? (__int64)-1 : 0;
    number = (number << 6) | (0x3f & *p++);

    while (--length > 0) {
        number = (number << 8) | (0xff & (__int64)*p++);
    }

    return number;
}

__int64 tarAtol(const char *octal, int length)
{
    return *octal & 0x80 ? tarAtol256(octal, length) : tarAtol8(octal, length);
}

int tarIsBlockNull(const char *block)
{
    int i;

    for (i = 0; i < TAR_BLOCK_SIZE; i++, block++) {
        if (*block) {
            return 0;
        }
    }

    return 1;
}

typedef struct
{
    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char checksum[8];
    char linkflag[1];
    char linkname[100];
    char pad[255];
} TarHeader;

int tarUnpackFile(FILE *packedFileHandle, const char* fileName, FILE *unpackedFileHandle)
{
    TarHeader tarHeader;
    __int64 offset;
    __int64 fileSize;
    char buffer[65536];
    size_t bytesToRead;
    size_t bytesRead;
    __int64 blocksToSkip;

    while (1) {
        if (TAR_BLOCK_SIZE != fread(&tarHeader, 1, sizeof(tarHeader), packedFileHandle))
        {
            return 1;
        }

        if (tarIsBlockNull((unsigned char*)&tarHeader)) {
            return 2; // end of tar
        }

        offset = _ftelli64(packedFileHandle);
        if (-1 == offset)
        {
            return 3;
        }

        fileSize = tarAtol(tarHeader.size, sizeof(tarHeader.size));

        if (0 == strcmp(tarHeader.name, fileName)) {
            while (fileSize > 0) {
                bytesToRead = (size_t)min(sizeof(buffer), fileSize);

                bytesRead = fread(buffer, 1, bytesToRead, packedFileHandle);
                if (bytesRead != bytesToRead) {
                    return 4;
                }

                if (fwrite(buffer, 1, bytesRead, unpackedFileHandle) != bytesRead) {
                    return 5;
                }

                fileSize -= bytesRead;
            }

            return 0;
        }

        blocksToSkip = fileSize / TAR_BLOCK_SIZE;
        if (fileSize % TAR_BLOCK_SIZE) {
            blocksToSkip++;
        }
        offset += blocksToSkip * TAR_BLOCK_SIZE;

        if (_fseeki64(packedFileHandle, offset, SEEK_SET) != 0) {
            return 6;
        }
    }
}
