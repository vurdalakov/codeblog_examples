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

#include "gzunpack.h"

#include <stdlib.h>
#include <string.h>

#include "zlib.h"

int readBuffer(FILE* fileHandle, void* buffer, size_t bytesToRead)
{
    size_t bytesRead;

    bytesRead = fread(buffer, 1, bytesToRead, fileHandle);

    if (ferror(fileHandle)) {
        return 0;
    }

    if (bytesRead != bytesToRead) {
        return 0;
    }

    return 1;
}

char* readZeroTerminatedString(FILE* fileHandle)
{
    long filePosition;
    int length;
    unsigned char byte;
    char* string;

    filePosition = ftell(fileHandle);

    if (-1 == filePosition) {
        return 0;
    }

    length = 0;
    while (1) {
        byte = fgetc(fileHandle);
        if (ferror(fileHandle)) {
            return 0;
        }

        length++;

        if (0 == byte) {
            break;
        }
    }

    if (fseek(fileHandle, filePosition, SEEK_SET)) {
        return 0;
    }

    string = malloc(length);

    length = 0;
    while (1) {
        byte = fgetc(fileHandle);
        if (ferror(fileHandle)) {
            return 0;
        }

        string[length] = byte;

        if (0 == byte) {
            break;
        }

        length++;
    }

    return string;
}

GzFileHeader *gzUnpackHeader(FILE *packedFileHandle)
{
    unsigned short signature;
    GzFileHeader* gzFileHeader;

    if (!readBuffer(packedFileHandle, &signature, 2)) {
        return 0;
    }

    if (signature != 0x8B1F) {
        return 0;
    }

    gzFileHeader = malloc(sizeof(GzFileHeader));
    memset(gzFileHeader, 0, sizeof(GzFileHeader));

    if (!readBuffer(packedFileHandle, &gzFileHeader->compressionMethod, 1)) {
        return 0;
    }

    if (!readBuffer(packedFileHandle, &gzFileHeader->flags, 1)) {
        return 0;
    }

    if (!readBuffer(packedFileHandle, &gzFileHeader->modificationTime, 4)) {
        return 0;
    }

    if (!readBuffer(packedFileHandle, &gzFileHeader->extraFlags, 1)) {
        return 0;
    }

    if (!readBuffer(packedFileHandle, &gzFileHeader->operatingSystem, 1)) {
        return 0;
    }

    if (gzFileHeader->flags & 0x04) {
        if (!readBuffer(packedFileHandle, &gzFileHeader->extraFieldLength, 2)) {
            return 0;
        }

        if (!readBuffer(packedFileHandle, &gzFileHeader->extraField, gzFileHeader->extraFieldLength)) {
            return 0;
        }
    }

    if (gzFileHeader->flags & 0x08) {
        gzFileHeader->originalFileName = readZeroTerminatedString(packedFileHandle);
    }

    if (gzFileHeader->flags & 0x10) {
        gzFileHeader->fileComment = readZeroTerminatedString(packedFileHandle);
    }

    if (gzFileHeader->flags & 0x02) {
        if (!readBuffer(packedFileHandle, &gzFileHeader->headerCrc, 2)) {
            return 0;
        }
    }

    return gzFileHeader;
}

void gzFreeHeader(GzFileHeader *gzFileHeader)
{
    if (0 == gzFileHeader) {
        return;
    }

    free(gzFileHeader->extraField);
    free(gzFileHeader->originalFileName);
    free(gzFileHeader->fileComment);

    free(gzFileHeader);
}

int gzUnpackFile(FILE *packedFileHandle, FILE *unpackedFileHandle)
{
    z_stream stream;
    int result;
    unsigned char input_buffer[65536];
    unsigned char output_buffer[65536];
    unsigned int size;

    stream.zalloc = 0;
    stream.zfree = 0;
    stream.opaque = 0;
    stream.next_in  = 0;
    stream.avail_in = 0;

    result = inflateInit2(&stream, 16 + MAX_WBITS);
    if (result != Z_OK) {
        return 1;
    }

    do
    {
        stream.avail_in = fread(input_buffer, 1, sizeof(input_buffer), packedFileHandle);
        if (ferror(packedFileHandle)) {
            (void)inflateEnd(&stream);
            return 2;
        }
        if (0 == stream.avail_in) {
            break;
        }
        stream.next_in = input_buffer;

        do {
            stream.avail_out = sizeof(output_buffer);
            stream.next_out = output_buffer;

            result = inflate(&stream, Z_NO_FLUSH);
            switch (result)
            {
                case Z_NEED_DICT:
                    result = Z_DATA_ERROR;
                case Z_STREAM_ERROR:
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    (void)inflateEnd(&stream);
                    return 3;
            }

            size = sizeof(output_buffer) - stream.avail_out;
            if ((fwrite(output_buffer, 1, size, unpackedFileHandle) != size) || ferror(unpackedFileHandle)) {
                (void)inflateEnd(&stream);
                return 4;
            }
        } while (0 == stream.avail_out);

    } while (result != Z_STREAM_END);

    inflateEnd(&stream);

    return 0;
}
