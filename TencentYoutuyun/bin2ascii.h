/*
 * Copyright (c) 2013 Pavel Shramov <shramov@mexmat.net>
 *
 * json2pb is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef __BIN2ASCII_H__
#define __BIN2ASCII_H__

#include <string>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <fstream>

#define str_to_base64_len(length) \
    ((length + 2 - ((length + 2)%3))*4/3)

#define base64_to_str_len(length) \
    (length*3/4)

#define is_base64(c) \
    (isalnum(c) || (c == '+') || (c == '/'))

const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

///
/// \brief base64_encode
/// \param input
/// \param length
/// \param b64str
/// \return
///
static int base64_encode(const unsigned char *input, int length, unsigned char* b64str,int* b64len)
{
    /* http://www.adp-gmbh.ch/cpp/common/base64.html */
    int i=0, j=0, s=0;
    unsigned char char_array_3[3], char_array_4[4];

    //int b64len = ((length + 2 - ((length + 2)%3))*4/3);

    *b64len = str_to_base64_len(length);

    //char *b64str = new char[b64len + 1];

    while (length--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                b64str[s++] = base64_chars[char_array_4[i]];

            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; j < i + 1; j++)
            b64str[s++] = base64_chars[char_array_4[j]];

        while (i++ < 3)
            b64str[s++] = '=';
    }

    while(s <= *b64len)
         b64str[s++] = '\0';

    return 0;
}

///
/// \brief base64_decode
/// \param input
/// \param length
/// \param output
/// \param outlen
/// \return
///
static int base64_decode(const unsigned char *input, int length, unsigned char *output, int *outlen)
{
    int i = 0;
    int j = 0;
    int r = 0;
    int idx = 0;
    unsigned char char_array_4[4], char_array_3[3];

    //unsigned char *output = new unsigned char[length*3/4];

    while (length-- && input[idx] != '=') {
        //skip invalid or padding based chars
        if (!is_base64(input[idx])) {
            idx++;
            continue;
        }
        char_array_4[i++] = input[idx++];
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = strchr(base64_chars, char_array_4[i]) - base64_chars;

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                output[r++] = char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = strchr(base64_chars, char_array_4[j]) - base64_chars;

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++)
            output[r++] = char_array_3[j];
    }

    *outlen = r;

    return 0;
}

static std::string b64_encode(const std::string &s)
{
    std::string result;

    int base64_str_size = str_to_base64_len(s.size());
    unsigned char * base_64_buf = new unsigned char[base64_str_size+1];

    if(base_64_buf == NULL)
    {
        return result;
    }

    base64_encode((unsigned char *)s.c_str(),
            s.size(), 
            base_64_buf,
            &base64_str_size);

    result.assign((const char*)base_64_buf, base64_str_size);

    delete [] base_64_buf;
    return result;
}

static std::string b64_decode(const std::string &s)
{
    std::string result;
    int value_size = s.size();
    int decode_size = base64_to_str_len(value_size);
    unsigned char *decode_buf = new unsigned char[decode_size]; 
    if(NULL == decode_buf)
    {
        return result;
    }

    if(base64_decode((const unsigned char *)s.c_str(), value_size,
                decode_buf, &decode_size) != 0 )
    {
        return result;
    }

    result.assign((const char*)decode_buf, decode_size);

    delete [] decode_buf;
    return result;
}


#endif//__BIN2ASCII_H__
