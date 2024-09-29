/*
    libzint - the open source barcode library
    Copyright (C) 2020-2023 Robin Stuart <rstuart114@gmail.com>

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. Neither the name of the project nor the names of its contributors
       may be used to endorse or promote products derived from this software
       without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
    OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
    HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
 */
/* SPDX-License-Identifier: BSD-3-Clause */

#include "testcommon.h"

static void test_large(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int eci;
        int option_1;
        int option_2;
        int output_options;
        struct zint_structapp structapp;
        char *pattern;
        int length;
        int ret;
        int expected_rows;
        int expected_width;
        const char *ret_errtxt;
    };
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_AZTEC, -1, 1, -1, -1, { 0, 0, "" }, "\xFF", 2053, 0, 151, 151, "" },
        /*  1*/ { BARCODE_AZTEC, -1, 1, -1, -1, { 0, 0, "" }, "\xFF", 2054, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /*  2*/ { BARCODE_AZTEC, -1, 1, -1, -1, { 0, 0, "" }, "\xFF", 2237, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /*  3*/ { BARCODE_AZTEC, -1, 1, -1, -1, { 0, 0, "" }, "\xFF", 2238, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
        /*  4*/ { BARCODE_AZTEC, -1, 2, -1, -1, { 0, 0, "" }, "1", 3835, 0, 151, 151, "" },
        /*  5*/ { BARCODE_AZTEC, -1, 2, -1, -1, { 0, 0, "" }, "1", 3836, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /*  6*/ { BARCODE_AZTEC, -1, 2, -1, -1, { 0, 0, "" }, "A", 3069, 0, 151, 151, "" },
        /*  7*/ { BARCODE_AZTEC, -1, 2, -1, -1, { 0, 0, "" }, "A", 3070, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /*  8*/ { BARCODE_AZTEC, -1, 2, -1, -1, { 0, 0, "" }, "\xFF", 1756, 0, 151, 151, "" },
        /*  9*/ { BARCODE_AZTEC, -1, 2, -1, -1, { 0, 0, "" }, "\xFF", 1757, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 10*/ { BARCODE_AZTEC, -1, 3, -1, -1, { 0, 0, "" }, "1", 3184, 0, 151, 151, "" },
        /* 11*/ { BARCODE_AZTEC, -1, 3, -1, -1, { 0, 0, "" }, "1", 3185, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 12*/ { BARCODE_AZTEC, -1, 3, -1, -1, { 0, 0, "" }, "A", 2548, 0, 151, 151, "" },
        /* 13*/ { BARCODE_AZTEC, -1, 3, -1, -1, { 0, 0, "" }, "A", 2549, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 14*/ { BARCODE_AZTEC, -1, 3, -1, -1, { 0, 0, "" }, "\xFF", 1457, 0, 151, 151, "" },
        /* 15*/ { BARCODE_AZTEC, -1, 3, -1, -1, { 0, 0, "" }, "\xFF", 1458, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 16*/ { BARCODE_AZTEC, -1, 4, -1, -1, { 0, 0, "" }, "1", 2485, 0, 151, 151, "" },
        /* 17*/ { BARCODE_AZTEC, -1, 4, -1, -1, { 0, 0, "" }, "1", 2486, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 18*/ { BARCODE_AZTEC, -1, 4, -1, -1, { 0, 0, "" }, "A", 1989, 0, 151, 151, "" },
        /* 19*/ { BARCODE_AZTEC, -1, 4, -1, -1, { 0, 0, "" }, "A", 1990, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 20*/ { BARCODE_AZTEC, -1, 4, -1, -1, { 0, 0, "" }, "\xFF", 1137, 0, 151, 151, "" },
        /* 21*/ { BARCODE_AZTEC, -1, 4, -1, -1, { 0, 0, "" }, "\xFF", 1138, ZINT_ERROR_TOO_LONG, -1, -1, "Error 504: Input too long (too many bits for selected ECC)" },
        /* 22*/ { BARCODE_AZTEC, -1, -1, 1, -1, { 0, 0, "" }, "\xFF", 7, 0, 15, 15, "" },
        /* 23*/ { BARCODE_AZTEC, -1, -1, 1, -1, { 0, 0, "" }, "\xFF", 8, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 24*/ { BARCODE_AZTEC, -1, -1, 1, -1, { 0, 0, "" }, "\xFF", 2078, ZINT_ERROR_TOO_LONG, -1, -1, "Error 704: Data too long for specified Aztec Code symbol size" },
        /* 25*/ { BARCODE_AZTEC, -1, -1, 2, -1, { 0, 0, "" }, "\xFF", 22, 0, 19, 19, "" },
        /* 26*/ { BARCODE_AZTEC, -1, -1, 2, -1, { 0, 0, "" }, "\xFF", 23, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 27*/ { BARCODE_AZTEC, -1, -1, 2, -1, { 0, 0, "" }, "\xFF", 2077, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 28*/ { BARCODE_AZTEC, -1, -1, 2, -1, { 0, 0, "" }, "\xFF", 2078, ZINT_ERROR_TOO_LONG, -1, -1, "Error 704: Data too long for specified Aztec Code symbol size" },
        /* 29*/ { BARCODE_AZTEC, -1, -1, 3, -1, { 0, 0, "" }, "\xFF", 39, 0, 23, 23, "" },
        /* 30*/ { BARCODE_AZTEC, -1, -1, 3, -1, { 0, 0, "" }, "\xFF", 40, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 31*/ { BARCODE_AZTEC, -1, -1, 4, -1, { 0, 0, "" }, "\xFF", 51, 0, 27, 27, "" },
        /* 32*/ { BARCODE_AZTEC, -1, -1, 4, -1, { 0, 0, "" }, "\xFF", 52, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 33*/ { BARCODE_AZTEC, -1, -1, 5, -1, { 0, 0, "" }, "\xFF", 10, 0, 19, 19, "" },
        /* 34*/ { BARCODE_AZTEC, -1, -1, 5, -1, { 0, 0, "" }, "\xFF", 11, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 35*/ { BARCODE_AZTEC, -1, -1, 5, -1, { 0, 0, "" }, "\xFF", 2077, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 36*/ { BARCODE_AZTEC, -1, -1, 5, -1, { 0, 0, "" }, "\xFF", 2078, ZINT_ERROR_TOO_LONG, -1, -1, "Error 704: Data too long for specified Aztec Code symbol size" },
        /* 37*/ { BARCODE_AZTEC, -1, -1, 6, -1, { 0, 0, "" }, "\xFF", 27, 0, 23, 23, "" },
        /* 38*/ { BARCODE_AZTEC, -1, -1, 6, -1, { 0, 0, "" }, "\xFF", 28, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 39*/ { BARCODE_AZTEC, -1, -1, 7, -1, { 0, 0, "" }, "\xFF", 47, 0, 27, 27, "" },
        /* 40*/ { BARCODE_AZTEC, -1, -1, 7, -1, { 0, 0, "" }, "\xFF", 48, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 41*/ { BARCODE_AZTEC, -1, -1, 8, -1, { 0, 0, "" }, "\xFF", 72, 0, 31, 31, "" },
        /* 42*/ { BARCODE_AZTEC, -1, -1, 8, -1, { 0, 0, "" }, "\xFF", 73, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 43*/ { BARCODE_AZTEC, -1, -1, 9, -1, { 0, 0, "" }, "\xFF", 100, 0, 37, 37, "" },
        /* 44*/ { BARCODE_AZTEC, -1, -1, 9, -1, { 0, 0, "" }, "\xFF", 101, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 45*/ { BARCODE_AZTEC, -1, -1, 10, -1, { 0, 0, "" }, "\xFF", 131, 0, 41, 41, "" },
        /* 46*/ { BARCODE_AZTEC, -1, -1, 10, -1, { 0, 0, "" }, "\xFF", 132, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 47*/ { BARCODE_AZTEC, -1, -1, 11, -1, { 0, 0, "" }, "\xFF", 166, 0, 45, 45, "" },
        /* 48*/ { BARCODE_AZTEC, -1, -1, 11, -1, { 0, 0, "" }, "\xFF", 167, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 49*/ { BARCODE_AZTEC, -1, -1, 12, -1, { 0, 0, "" }, "\xFF", 205, 0, 49, 49, "" },
        /* 50*/ { BARCODE_AZTEC, -1, -1, 12, -1, { 0, 0, "" }, "\xFF", 206, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 51*/ { BARCODE_AZTEC, -1, -1, 13, -1, { 0, 0, "" }, "\xFF", 253, 0, 53, 53, "" },
        /* 52*/ { BARCODE_AZTEC, -1, -1, 13, -1, { 0, 0, "" }, "\xFF", 254, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 53*/ { BARCODE_AZTEC, -1, -1, 14, -1, { 0, 0, "" }, "\xFF", 300, 0, 57, 57, "" },
        /* 54*/ { BARCODE_AZTEC, -1, -1, 14, -1, { 0, 0, "" }, "\xFF", 301, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 55*/ { BARCODE_AZTEC, -1, -1, 15, -1, { 0, 0, "" }, "\xFF", 349, 0, 61, 61, "" },
        /* 56*/ { BARCODE_AZTEC, -1, -1, 15, -1, { 0, 0, "" }, "\xFF", 350, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 57*/ { BARCODE_AZTEC, -1, -1, 16, -1, { 0, 0, "" }, "\xFF", 403, 0, 67, 67, "" },
        /* 58*/ { BARCODE_AZTEC, -1, -1, 16, -1, { 0, 0, "" }, "\xFF", 404, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 59*/ { BARCODE_AZTEC, -1, -1, 17, -1, { 0, 0, "" }, "\xFF", 462, 0, 71, 71, "" },
        /* 60*/ { BARCODE_AZTEC, -1, -1, 17, -1, { 0, 0, "" }, "\xFF", 463, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 61*/ { BARCODE_AZTEC, -1, -1, 18, -1, { 0, 0, "" }, "\xFF", 523, 0, 75, 75, "" },
        /* 62*/ { BARCODE_AZTEC, -1, -1, 18, -1, { 0, 0, "" }, "\xFF", 524, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 63*/ { BARCODE_AZTEC, -1, -1, 19, -1, { 0, 0, "" }, "\xFF", 588, 0, 79, 79, "" },
        /* 64*/ { BARCODE_AZTEC, -1, -1, 19, -1, { 0, 0, "" }, "\xFF", 589, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 65*/ { BARCODE_AZTEC, -1, -1, 20, -1, { 0, 0, "" }, "\xFF", 655, 0, 83, 83, "" },
        /* 66*/ { BARCODE_AZTEC, -1, -1, 20, -1, { 0, 0, "" }, "\xFF", 656, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 67*/ { BARCODE_AZTEC, -1, -1, 21, -1, { 0, 0, "" }, "\xFF", 727, 0, 87, 87, "" },
        /* 68*/ { BARCODE_AZTEC, -1, -1, 21, -1, { 0, 0, "" }, "\xFF", 728, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 69*/ { BARCODE_AZTEC, -1, -1, 22, -1, { 0, 0, "" }, "\xFF", 804, 0, 91, 91, "" },
        /* 70*/ { BARCODE_AZTEC, -1, -1, 22, -1, { 0, 0, "" }, "\xFF", 805, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 71*/ { BARCODE_AZTEC, -1, -1, 23, -1, { 0, 0, "" }, "\xFF", 883, 0, 95, 95, "" },
        /* 72*/ { BARCODE_AZTEC, -1, -1, 23, -1, { 0, 0, "" }, "\xFF", 884, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 73*/ { BARCODE_AZTEC, -1, -1, 24, -1, { 0, 0, "" }, "\xFF", 966, 0, 101, 101, "" },
        /* 74*/ { BARCODE_AZTEC, -1, -1, 24, -1, { 0, 0, "" }, "\xFF", 967, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 75*/ { BARCODE_AZTEC, -1, -1, 25, -1, { 0, 0, "" }, "\xFF", 1051, 0, 105, 105, "" },
        /* 76*/ { BARCODE_AZTEC, -1, -1, 25, -1, { 0, 0, "" }, "\xFF", 1052, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 77*/ { BARCODE_AZTEC, -1, -1, 26, -1, { 0, 0, "" }, "\xFF", 1141, 0, 109, 109, "" },
        /* 78*/ { BARCODE_AZTEC, -1, -1, 26, -1, { 0, 0, "" }, "\xFF", 1142, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 79*/ { BARCODE_AZTEC, -1, -1, 27, -1, { 0, 0, "" }, "\xFF", 1258, 0, 113, 113, "" },
        /* 80*/ { BARCODE_AZTEC, -1, -1, 27, -1, { 0, 0, "" }, "\xFF", 1259, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 81*/ { BARCODE_AZTEC, -1, -1, 28, -1, { 0, 0, "" }, "\xFF", 1357, 0, 117, 117, "" },
        /* 82*/ { BARCODE_AZTEC, -1, -1, 28, -1, { 0, 0, "" }, "\xFF", 1358, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 83*/ { BARCODE_AZTEC, -1, -1, 29, -1, { 0, 0, "" }, "\xFF", 1459, 0, 121, 121, "" },
        /* 84*/ { BARCODE_AZTEC, -1, -1, 29, -1, { 0, 0, "" }, "\xFF", 1460, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 85*/ { BARCODE_AZTEC, -1, -1, 30, -1, { 0, 0, "" }, "\xFF", 1566, 0, 125, 125, "" },
        /* 86*/ { BARCODE_AZTEC, -1, -1, 30, -1, { 0, 0, "" }, "\xFF", 1567, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 87*/ { BARCODE_AZTEC, -1, -1, 31, -1, { 0, 0, "" }, "\xFF", 1676, 0, 131, 131, "" },
        /* 88*/ { BARCODE_AZTEC, -1, -1, 31, -1, { 0, 0, "" }, "\xFF", 1677, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 89*/ { BARCODE_AZTEC, -1, -1, 32, -1, { 0, 0, "" }, "\xFF", 1789, 0, 135, 135, "" },
        /* 90*/ { BARCODE_AZTEC, -1, -1, 32, -1, { 0, 0, "" }, "\xFF", 1790, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 91*/ { BARCODE_AZTEC, -1, -1, 33, -1, { 0, 0, "" }, "\xFF", 1907, 0, 139, 139, "" },
        /* 92*/ { BARCODE_AZTEC, -1, -1, 33, -1, { 0, 0, "" }, "\xFF", 1908, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 93*/ { BARCODE_AZTEC, -1, -1, 34, -1, { 0, 0, "" }, "\xFF", 2028, 0, 143, 143, "" },
        /* 94*/ { BARCODE_AZTEC, -1, -1, 34, -1, { 0, 0, "" }, "\xFF", 2029, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 95*/ { BARCODE_AZTEC, -1, -1, 35, -1, { 0, 0, "" }, "\xFF", 2149, 0, 147, 147, "" },
        /* 96*/ { BARCODE_AZTEC, -1, -1, 35, -1, { 0, 0, "" }, "\xFF", 2150, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /* 97*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 0, 0, "" }, "\xFF", 2237, 0, 151, 151, "" },
        /* 98*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 0, 0, "" }, "\xFF", 2238, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
        /* 97*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 0, 0, "" }, "\xFF", 2205, 0, 151, 151, "" },
        /* 99*/ { BARCODE_AZTEC, -1, -1, 34, -1, { 0, 0, "" }, "1", 4429, 0, 143, 143, "" },
        /*100*/ { BARCODE_AZTEC, -1, -1, 34, -1, { 0, 0, "" }, "1", 4430, ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /*101*/ { BARCODE_AZTEC, -1, -1, 35, -1, { 0, 0, "" }, "1", 4483, 0, 147, 147, "" },
        /*102*/ { BARCODE_AZTEC, -1, -1, 35, -1, { 0, 0, "" }, "1", 4484, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
        /*103*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 0, 0, "" }, "1", 4483, 0, 151, 151, "" },
        /*104*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 0, 0, "" }, "1", 4484, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
        /*105*/ { BARCODE_AZTEC, 899, -1, 36, -1, { 0, 0, "" }, "\xFF", 2234, 0, 151, 151, "" },
        /*106*/ { BARCODE_AZTEC, 899, -1, 36, -1, { 0, 0, "" }, "\xFF", 2235, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
        /*107*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 2, 3, "1234567890123456789012" }, "\xFF", 2221, 0, 151, 151, "" },
        /*108*/ { BARCODE_AZTEC, -1, -1, 36, -1, { 2, 3, "1234567890123456789012" }, "\xFF", 2222, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
        /*109*/ { BARCODE_AZTEC, 899, -1, 36, -1, { 2, 3, "1234567890123456789012" }, "\xFF", 2218, 0, 151, 151, "" },
        /*110*/ { BARCODE_AZTEC, 899, -1, 36, -1, { 2, 3, "1234567890123456789012" }, "\xFF", 2219, ZINT_ERROR_TOO_LONG, -1, -1, "Error 502: Input too long or too many extended ASCII characters" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[8192];
    char cmp_buf[32768];
    char cmp_msg[8192];

    char data_buf[ZINT_MAX_DATA_LEN];

    int do_zxingcpp = (debug & ZINT_DEBUG_TEST_ZXINGCPP) && testUtilHaveZXingCPPDecoder(); /* Only do ZXing-C++ test if asked, too slow otherwise */

    testStartSymbol("test_large", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        testUtilStrCpyRepeat(data_buf, data[i].pattern, data[i].length);
        assert_equal(data[i].length, (int) strlen(data_buf), "i:%d length %d != strlen(data_buf) %d\n", i, data[i].length, (int) strlen(data_buf));

        length = testUtilSetSymbol(symbol, data[i].symbology, -1 /*input_mode*/, data[i].eci, data[i].option_1, data[i].option_2, -1, data[i].output_options, data_buf, data[i].length, debug);
        if (data[i].structapp.count) {
            symbol->structapp = data[i].structapp;
        }

        ret = ZBarcode_Encode(symbol, (unsigned char *) data_buf, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (ret < ZINT_ERROR) {
            assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d\n", i, symbol->rows, data[i].expected_rows);
            assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d\n", i, symbol->width, data[i].expected_width);

            if (do_zxingcpp && testUtilCanZXingCPP(i, symbol, data_buf, length, debug)) {
                int cmp_len, ret_len;
                char modules_dump[22801 + 1];
                assert_notequal(testUtilModulesDump(symbol, modules_dump, sizeof(modules_dump)), -1, "i:%d testUtilModulesDump == -1\n", i);
                ret = testUtilZXingCPP(i, symbol, data_buf, length, modules_dump, cmp_buf, sizeof(cmp_buf), &cmp_len);
                assert_zero(ret, "i:%d %s testUtilZXingCPP ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                ret = testUtilZXingCPPCmp(symbol, cmp_msg, cmp_buf, cmp_len, data_buf, length, NULL /*primary*/, escaped, &ret_len);
                assert_zero(ret, "i:%d %s testUtilZXingCPPCmp %d != 0 %s\n  actual: %.*s\nexpected: %.*s\n",
                               i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_len, cmp_buf, ret_len, escaped);
            }
        } else {
            assert_zero(strcmp(symbol->errtxt, data[i].ret_errtxt), "i:%d errtxt %s != %s\n", i, symbol->errtxt, data[i].ret_errtxt);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_options(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int input_mode;
        int output_options;
        int option_1;
        int option_2;
        struct zint_structapp structapp;
        char *data;
        int ret;

        int expected_rows;
        int expected_width;
        const char *expected_errtxt;
    };
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 0, 0, "" }, "1234567890", 0, 15, 15, "" },
        /*  1*/ { BARCODE_AZTEC, -1, -1, 1, -1, { 0, 0, "" }, "1234567890", 0, 15, 15, "" },
        /*  2*/ { BARCODE_AZTEC, -1, -1, 4, -1, { 0, 0, "" }, "1234567890", 0, 19, 19, "" },
        /*  3*/ { BARCODE_AZTEC, -1, -1, 5, -1, { 0, 0, "" }, "1234567890", ZINT_WARN_INVALID_OPTION, 15, 15, "Warning 503: Invalid error correction level - using default instead" },
        /*  4*/ { BARCODE_AZTEC, -1, -1, -1, 1, { 0, 0, "" }, "12345678901234567890", ZINT_ERROR_TOO_LONG, -1, -1, "Error 505: Data too long for specified Aztec Code symbol size" },
        /*  5*/ { BARCODE_AZTEC, -1, -1, -1, 36, { 0, 0, "" }, "1234567890", 0, 151, 151, "" },
        /*  6*/ { BARCODE_AZTEC, -1, -1, -1, 37, { 0, 0, "" }, "1234567890", ZINT_ERROR_INVALID_OPTION, -1, -1, "Error 510: Invalid Aztec Code size" },
        /*  7*/ { BARCODE_AZTEC, GS1_MODE, READER_INIT, -1, -1, { 0, 0, "" }, "[91]A", ZINT_ERROR_INVALID_OPTION, -1, -1, "Error 501: Cannot encode in GS1 and Reader Initialisation mode at the same time" },
        /*  8*/ { BARCODE_AZTEC, GS1_MODE, -1, -1, -1, { 0, 0, "" }, "[91]A", 0, 15, 15, "" },
        /*  9*/ { BARCODE_AZTEC, GS1_MODE | GS1PARENS_MODE, -1, -1, -1, { 0, 0, "" }, "(91)A", 0, 15, 15, "" },
        /* 10*/ { BARCODE_AZTEC, -1, READER_INIT, -1, 26, { 0, 0, "" }, "A", 0, 109, 109, "" }, /* 22 layers */
        /* 11*/ { BARCODE_AZTEC, -1, READER_INIT, -1, 27, { 0, 0, "" }, "A", ZINT_ERROR_TOO_LONG, -1, -1, "Error 506: Data too long for reader initialisation symbol" }, /* 23 layers */
        /* 12*/ { BARCODE_AZTEC, -1, READER_INIT, -1, 1, { 0, 0, "" }, "A", 0, 15, 15, "" }, /* Compact 1 layer */
        /* 13*/ { BARCODE_AZTEC, -1, READER_INIT, -1, 2, { 0, 0, "" }, "A", 0, 19, 19, "" }, /* Compact 2 layers gets set to full 1 layer if READER_INIT set */
        /* 14*/ { BARCODE_AZRUNE, -1, -1, -1, -1, { 0, 0, "" }, "0001", ZINT_ERROR_TOO_LONG, -1, -1, "Error 507: Input too large (3 character maximum)" },
        /* 15*/ { BARCODE_AZRUNE, -1, -1, -1, -1, { 0, 0, "" }, "A", ZINT_ERROR_INVALID_DATA, -1, -1, "Error 508: Invalid character in data (digits only)" },
        /* 16*/ { BARCODE_AZRUNE, -1, -1, -1, -1, { 0, 0, "" }, "256", ZINT_ERROR_INVALID_DATA, -1, -1, "Error 509: Input out of range (0 to 255)" },
        /* 17*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 1, 2, "" }, "1234567890", 0, 15, 15, "" },
        /* 18*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 1, 2, "12345678901234567890123456789012" }, "1234567890", 0, 23, 23, "" },
        /* 19*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 1, 1, "" }, "1234567890", ZINT_ERROR_INVALID_OPTION, -1, -1, "Error 701: Structured Append count out of range (2-26)" },
        /* 20*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 0, 2, "" }, "1234567890", ZINT_ERROR_INVALID_OPTION, -1, -1, "Error 702: Structured Append index out of range (1-2)" },
        /* 21*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 3, 2, "" }, "1234567890", ZINT_ERROR_INVALID_OPTION, -1, -1, "Error 702: Structured Append index out of range (1-2)" },
        /* 22*/ { BARCODE_AZTEC, -1, -1, -1, -1, { 1, 2, "A B" }, "1234567890", ZINT_ERROR_INVALID_OPTION, -1, -1, "Error 703: Structured Append ID cannot contain spaces" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    testStartSymbol("test_options", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, -1 /*eci*/, data[i].option_1, data[i].option_2, -1, data[i].output_options, data[i].data, -1, debug);
        if (data[i].structapp.count) {
            symbol->structapp = data[i].structapp;
        }

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (ret < ZINT_ERROR) {
            assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d (%s)\n", i, symbol->rows, data[i].expected_rows, symbol->errtxt);
            assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, symbol->errtxt);
        }
        assert_zero(strcmp(symbol->errtxt, data[i].expected_errtxt), "i:%d symbol->errtxt %s != %s\n", i, symbol->errtxt, data[i].expected_errtxt);

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_encode(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int input_mode;
        int eci;
        int output_options;
        int option_1;
        int option_2;
        char *data;
        int length;
        int ret;

        int expected_rows;
        int expected_width;
        int bwipp_cmp;
        char *comment;
        char *expected;
    };
    struct item data[] = {
        /*  0*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 1, "123456789012", -1, 0, 15, 15, 1, "ISO/IEC 24778:2008 Figure 1 (left)",
                    "000111000011100"
                    "110111001110010"
                    "111100001000100"
                    "001111111111100"
                    "010100000001000"
                    "100101111101010"
                    "100101000101110"
                    "001101010101100"
                    "101101000101111"
                    "101101111101010"
                    "110100000001101"
                    "000111111111111"
                    "110001010010001"
                    "101011110101010"
                    "100010001000101"
                },
        /*  1*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "Aztec Code is a public domain 2D matrix barcode symbology of nominally square symbols built on a square grid with a distinctive square bullseye pattern at their center.", -1, 0, 41, 41, 0, "ISO/IEC 24778:2008 Figure 1 (right) NOTE: Not the same but down to single encoding mode difference (UPPER space rather than LOWER space after 2D); BWIPP same encodation as figure",
                    "00001100110010010010111000010100001011000"
                    "01000110010110110001000000100101101000001"
                    "01011100101011001110101100000001100011001"
                    "11100000010100001000010010010100110001010"
                    "10101010101010101010101010101010101010101"
                    "00110101011100000001000100011001101100010"
                    "11001000100011110101100010110100011011010"
                    "01000101001101011011011111101100000101011"
                    "11011010111101111111101010001101111011100"
                    "01000101001000110011010101001101110100111"
                    "01011101100011100001100000101010111011001"
                    "00100101100111100101001111011011011100101"
                    "11101000000100001111101011010101101010101"
                    "00000100011101100101000001011110110000000"
                    "01001101010001111111111111110101101011100"
                    "00110000000010100000000000110100010000111"
                    "00001011011111101111111110100110000011110"
                    "00000111010010101000000010110011101100000"
                    "11001001010101101011111010111111100010111"
                    "11110001000101101010001010100111001100011"
                    "10101010101010101010101010101010101010101"
                    "00100100010000101010001010100101100000000"
                    "00001100111110101011111010111001111010000"
                    "10010101000010101000000010110110111001010"
                    "01011101011011101111111110110000110011110"
                    "00110101011100100000000000111011010100100"
                    "00111101000010111111111111110100011011011"
                    "00000010101100011111001110001000111000010"
                    "10001000010111101001100110011000001010001"
                    "10010001111100101111011100100011110101101"
                    "01111100000001001110100011011011110011000"
                    "10000001000010110110010010010101111000000"
                    "00101100010010001011111101101111111110101"
                    "00100001101000100101010001001110010001111"
                    "10011001111110000001110100000001010010011"
                    "10110010000000111110011001111111100101011"
                    "10101010101010101010101010101010101010101"
                    "10000010011110010010000100001010001101110"
                    "10101101110100001100111100110101001010001"
                    "00010010010011001011011010000110001000101"
                    "10001000001010100110100000001001001110000"
                },
        /*  2*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "Code 2D!", -1, 0, 15, 15, 0, "ISO/IEC 24778:2008 Figure G.2; BWIPP defaults to full (see following)",
                    "000110001100000"
                    "000000110000010"
                    "101100001000101"
                    "011111111111100"
                    "111100000001101"
                    "000101111101100"
                    "100101000101111"
                    "001101010101001"
                    "001101000101010"
                    "010101111101001"
                    "100100000001011"
                    "100111111111101"
                    "010001100010010"
                    "011000011011010"
                    "111001101100000"
                },
        /*  3*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 1, "Code 2D!", -1, 0, 15, 15, 1, "ISO/IEC 24778:2008 Figure G.2; specify size",
                    "000110001100000"
                    "000000110000010"
                    "101100001000101"
                    "011111111111100"
                    "111100000001101"
                    "000101111101100"
                    "100101000101111"
                    "001101010101001"
                    "001101000101010"
                    "010101111101001"
                    "100100000001011"
                    "100111111111101"
                    "010001100010010"
                    "011000011011010"
                    "111001101100000"
                },
        /*  4*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111\015\012", -1, 0, 53, 53, 1, "ISO/IEC 24778:2008 Figure I.1 (left) (note CRLF at end!), same",
                    "00010101011010101010101010110101010101010110101010101"
                    "00101010100101010101010101001010101010101001010101010"
                    "11100101011010101010101010110101010101010110101010110"
                    "11011010100101010101010101001010101010101001010101001"
                    "00101001011010101010101010110101010101010110101011010"
                    "01010110100101010101010101001010101010101001010100101"
                    "10101010011010101010101010110101010101010110101101010"
                    "01010101100101010101010101001010101010101001010010101"
                    "10101010101010101010101010110101010101010110110101010"
                    "01010101010101010101010101001010101010101001001010101"
                    "10101010101010101010101010101010101010101010101010101"
                    "10101010100101010100000010000100011110011001010101010"
                    "01010101011010010011110110111000110101111010101010101"
                    "10101010100100011100001111011001101011001101010101010"
                    "01010101011011001111111011100110111001001010101010101"
                    "10101010100101001000001100001111011001011101010101010"
                    "01010101011001100000011100110001110001100010101010101"
                    "10101010100001100100101000011101101100111001010101010"
                    "01010101011001000110001101100101011101111110101010101"
                    "10101010100101001101101000000010011100011001010101010"
                    "01010101011111010101111111111111110111010110101010101"
                    "10101010100110110101100000000000111000100001010101010"
                    "01010101011110111010101111111110101101000110101010101"
                    "10101010100010011000101000000010100100000101010101010"
                    "01010101011111010010101011111010101011110010101010101"
                    "10101010100000010001101010001010101011010001010101010"
                    "10101010101010101010101010101010101010101010101010101"
                    "01010101010101000111101010001010111100101100101010101"
                    "10101010101111111001101011111010111101000011010101010"
                    "01010101010110010001101000000010111100111100101010101"
                    "10101010101011010100101111111110101010010011010101010"
                    "01010101010000101110100000000000101111001000101010101"
                    "10101010101001000000111111111111111110110111010101010"
                    "01010101010101101100010110000110000111110100101010101"
                    "10101010101101110101011101100001010010100111010101010"
                    "01010101010000111001101101011011011010111000101010101"
                    "10101010101001011011011100100001001001001011010101010"
                    "01010101010001110110101010000110111100000000101010101"
                    "10101010101000001110110100101011000011001111010101010"
                    "01010101010001110010110111010101111111101100101010101"
                    "10101010101100100010010111110110111100001111010101010"
                    "01010101010000011101010001000010011111011100101010101"
                    "10101010101010101010101010101010101010101010101010101"
                    "10101010010010101010101010010101010101010101010101010"
                    "01010101101101010101010101101010101010101010101010101"
                    "10101001010010101010101010010101010101010100110101010"
                    "01010110101101010101010101101010101010101011001010101"
                    "10100101010010101010101010010101010101010100101101010"
                    "01011010101101010101010101101010101010101011010010101"
                    "10010101010010101010101010010101010101010100101011010"
                    "01101010101101010101010101101010101010101011010100101"
                    "01010101010010101010101010010101010101010100101010110"
                    "10101010101101010101010101101010101010101011010101001"
                },
        /*  5*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "3333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333\015\012", -1, 0, 53, 53, 1, "ISO/IEC 24778:2008 Figure I.1 (right) (CRLF at end), same",
                    "00111111111111111111111111111111111111111111111111111"
                    "00000000000000000000000000000000000000000000000000000"
                    "11101111111111111111111111111111111111111111111111101"
                    "11100000000000000000000000000000000000000000000000001"
                    "00101011111111111111111111111111111111111111111110101"
                    "10101000000000000000000000000000000000000000000000101"
                    "10101010111111111111111111111111111111111111111010101"
                    "10101010000000000000000000000000000000000000000010101"
                    "10101010101111111111111111111111111111111111101010101"
                    "10101010100000000000000000000000000000000000001010101"
                    "10101010101010101010101010101010101010101010101010101"
                    "10101010100100101111110001000100101100100000101010101"
                    "10101010101101111101110010111000101000111010101010101"
                    "10101010100101100101101111010110010110001000101010101"
                    "10101010101101110110011100100101011101001110101010101"
                    "10101010100100101010001101001001101000011100101010101"
                    "10101010101000101001010110111111111000100110101010101"
                    "10101010100000101001101101000111100001001100101010101"
                    "10101010101001011101100000110001101011000010101010101"
                    "10101010100100000111101000000010010100011100101010101"
                    "10101010101111001011111111111111111011111110101010101"
                    "10101010100110110111100000000000111101001100101010101"
                    "10101010101111001010101111111110100000100110101010101"
                    "10101010100001001000101000000010101010000000101010101"
                    "10101010101100110010101011111010100101111110101010101"
                    "10101010100010111111101010001010100001100000101010101"
                    "10101010101010101010101010101010101010101010101010101"
                    "10101010100111000101101010001010111101001100101010101"
                    "10101010101001000011101011111010110001011010101010101"
                    "10101010100111011011101000000010111000000100101010101"
                    "10101010101011100110101111111110100100011110101010101"
                    "10101010100001010110100000000000100011100100101010101"
                    "10101010101110101100111111111111110011110010101010101"
                    "10101010100100000010010110000110000110001100101010101"
                    "10101010101110101100110100111110100111001110101010101"
                    "10101010100100011000111110000001100011101000101010101"
                    "10101010101010100111001011111011100101111110101010101"
                    "10101010100011101001111001000100101000111100101010101"
                    "10101010101101100101110101110101101010110010101010101"
                    "10101010100101000101110100010000011101011100101010101"
                    "10101010101000110100111011110110000101000010101010101"
                    "10101010100101010001100000001011100001110000101010101"
                    "10101010101010101010101010101010101010101010101010101"
                    "10101010000000000000000000000000000000000000101010101"
                    "10101010111111111111111111111111111111111110101010101"
                    "10101000000000000000000000000000000000000000001010101"
                    "10101011111111111111111111111111111111111111101010101"
                    "10100000000000000000000000000000000000000000000010101"
                    "10101111111111111111111111111111111111111111111010101"
                    "10000000000000000000000000000000000000000000000000101"
                    "10111111111111111111111111111111111111111111111110101"
                    "00000000000000000000000000000000000000000000000000001"
                    "11111111111111111111111111111111111111111111111111101"
                },
        /*  6*/ { BARCODE_AZTEC, GS1_MODE, -1, -1, -1, -1, "[01]03453120000011[17]120508[10]ABCD1234[410]9501101020917", -1, 0, 23, 23, 1, "#189 Follow embedded FLG(n) with FLG(0)",
                    "00100000101111000100100"
                    "00011101100110001010000"
                    "00000111000111101011011"
                    "01000001010100001100010"
                    "00001001100110000111110"
                    "00011011111000110101101"
                    "00001011100111101111110"
                    "11000111111111111010000"
                    "11001101000000010111110"
                    "00111011011111010111110"
                    "01000001010001011110010"
                    "00011001010101011111101"
                    "01101111010001011110011"
                    "10011001011111011011100"
                    "01011011000000010010110"
                    "00011101111111111001100"
                    "10101100110111100001101"
                    "10110101111100111010001"
                    "11101001010000011001110"
                    "00101010101010001111001"
                    "11000101000100100000100"
                    "00010001010101010101011"
                    "11101100000000000010110"
                },
        /*  7*/ { BARCODE_AZTEC, GS1_MODE, -1, -1, -1, -1, "[01]95012345678903[3103]000123", -1, 0, 19, 19, 1, "#189 Follow embedded FLG(n) with FLG(0)",
                    "0000000100001010101"
                    "0001101111011000000"
                    "0111100100010110100"
                    "0011000110100100110"
                    "0010110101010010110"
                    "0101111111111110101"
                    "0011110000000101000"
                    "0101010111110100011"
                    "1101110100010110100"
                    "1000010101010111010"
                    "0011110100010100110"
                    "1000110111110111110"
                    "0010110000000101010"
                    "1111011111111111101"
                    "1001001111001000100"
                    "1111111110110100011"
                    "0111000111101011001"
                    "1000110111011000101"
                    "1010100000101101001"
                },
        /*  8*/ { BARCODE_AZTEC, GS1_MODE, -1, -1, -1, -1, "[01]04610044273252[21]LRFX)k<C7ApWJ[91]003A[92]K8rNAqdvjmdxsmCVuj3FhaoNzQuq7Uff0sHXfz1TT/doiMaGQqNF+VPwMvwVbm1fxjzuDt6jxLCcc8o/tqbEDA==", -1, 0, 45, 45, 1, "#189 Follow embedded FLG(n) with FLG(0)",
                    "000000101110011010101010010110011000001010111"
                    "000110001111011100111101101110110000000000011"
                    "001000101100101011000011111111101110111010101"
                    "010010001000111100001101110011100111110100100"
                    "001001100110001000011011011011000101001010010"
                    "001101011110100001001101001101110111100111100"
                    "101010101010101010101010101010101010101010101"
                    "000111001111100010000000100000111001000111110"
                    "111100111010000100100111100011001110001100001"
                    "110101001000001101011100110101001110000101010"
                    "000111111010001101111110100110001011001110001"
                    "011000000000100001101100000000011000100011110"
                    "001100110100000101000111111101110100011001010"
                    "011010000111011010100100001101001111010000111"
                    "100011100111010101011110000001010111001110111"
                    "011010000001010110011000000101101011110100010"
                    "001100100001010111111111111111110010101111100"
                    "111010010111010010000000000011101100100011000"
                    "010100110000110110111111111011010010011111100"
                    "001011001110010110100000001010101111010011000"
                    "001010101101100110101111101011100111111111000"
                    "010001001100111010101000101011111100000100000"
                    "101010101010101010101010101010101010101010101"
                    "101100010101111010101000101010100000110101111"
                    "011010101100110010101111101010000001001101101"
                    "001110000010110010100000001011101111010011100"
                    "011001100001111010111111111010001010001111000"
                    "000001011101101010000000000011101100010110111"
                    "110111111111001011111111111111110101101001101"
                    "000010011011101001110000111000101101000000011"
                    "111111101001101111011111110110101010001110001"
                    "001010011011011100100101100100000100100101111"
                    "100101100101110100010111010111001100001111011"
                    "010111001001000111010101110101010111010111100"
                    "001110110000001110001010000100110011101100101"
                    "101001000110001000010101001110110010110000100"
                    "101111100000010000110111010000010111111111111"
                    "100000011010001000010001110100010100010111010"
                    "101010101010101010101010101010101010101010101"
                    "101001000011011010010001001100101110100010110"
                    "001100100111001101011011111110110010011110100"
                    "111100011011100010110001001111110011100011101"
                    "101101111001110100000011101110110100011101011"
                    "000011010110101110000101110100000111000011010"
                    "101001110101010110100011010010001111001101101"
                },
        /*  9*/ { BARCODE_HIBC_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "H123ABC01234567890", -1, 0, 19, 19, 1, "ANSI/HIBC 2.6 - 2016 Figure C1",
                    "0010111011010110001"
                    "0011011111011111101"
                    "0101100111010110010"
                    "1001010011110110110"
                    "0011110101001010101"
                    "0011111111111110110"
                    "1010110000000101110"
                    "0110110111110110110"
                    "1111010100010100111"
                    "1110010101010100000"
                    "0010110100010110110"
                    "0101110111110100000"
                    "1000010000000101011"
                    "1000011111111111011"
                    "0000000000010001000"
                    "1010100000110101111"
                    "1111100111101000001"
                    "1000010101101010001"
                    "1001001001100001100"
                },
        /* 10*/ { BARCODE_HIBC_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "/ACMRN123456/V200912190833", -1, 0, 19, 19, 1, "HIBC/PAS Section 2.2 Patient Id, same",
                    "0001110111000101110"
                    "0010000101001101000"
                    "0101011111101000101"
                    "1001011010110011000"
                    "0001110101100010100"
                    "0001111111111110010"
                    "0010110000000100011"
                    "0011010111110110010"
                    "1011010100010101011"
                    "1001110101010110011"
                    "0011010100010111110"
                    "0010010111110110001"
                    "1011110000000111101"
                    "0010011111111110000"
                    "1010000100111001100"
                    "0000000111110111100"
                    "1111010101111100001"
                    "0010110100110111011"
                    "1101111110100000110"
                },
        /* 11*/ { BARCODE_AZTEC, DATA_MODE | ESCAPE_MODE, -1, -1, -1, -1, "[)>\\R06\\G+/ACMRN123456/V2009121908334\\R\\E", -1, 0, 23, 23, 0, "HIBC/PAS Section 2.2 Patient Id Macro **NOT SAME** different encodation, Zint 1 codeword longer; BWIPP same as figure",
                    "11010110110000110111011"
                    "10111111001000110100000"
                    "11000001011011010011010"
                    "11001101001101000001100"
                    "10101000100101011100111"
                    "11000010111111111010111"
                    "01101111100111001101011"
                    "10101011111111111011111"
                    "11110111000000011110001"
                    "10000001011111011111110"
                    "11111001010001010111101"
                    "00011001010101010001001"
                    "11000111010001011011111"
                    "11000111011111010100100"
                    "11110101000000011010001"
                    "10100001111111111001000"
                    "11111000111101100110101"
                    "01001101000000011001000"
                    "10100101111001101010001"
                    "01001111101010100001111"
                    "01110000011111101011111"
                    "11110110111110011000100"
                    "10110000010101011110010"
                },
        /* 12*/ { BARCODE_HIBC_AZTEC, UNICODE_MODE, -1, -1, 3, -1, "/EO523201", -1, 0, 19, 19, 1, "HIBC/PAS Section 2.2 Purchase Order, same",
                    "0011100011001101111"
                    "0010011001010110110"
                    "0110100100101000000"
                    "1001111000110011001"
                    "0011110100101011001"
                    "0001111111111110101"
                    "0001010000000100100"
                    "0001010111110101000"
                    "1000010100010100011"
                    "1001010101010111001"
                    "0000010100010110100"
                    "0111010111110111101"
                    "1000110000000101001"
                    "1001011111111111010"
                    "0010000000111001101"
                    "0110010000010110011"
                    "1110001000101101001"
                    "0111011100001111101"
                    "1010000000101001001"
                },
        /* 13*/ { BARCODE_HIBC_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "/KN12345", -1, 0, 19, 19, 1, "HIBC/PAS Section 2.2 Asset Tag, same",
                    "0011111101100100110"
                    "0010011100111110101"
                    "0111110010101101110"
                    "1000010111011000001"
                    "0001110100101010001"
                    "0010111111111110110"
                    "0001110000000111110"
                    "0000010111110110011"
                    "1010010100010100000"
                    "1011010101010100101"
                    "0010010100010100100"
                    "1101110111110110110"
                    "0011110000000110110"
                    "0100011111111110100"
                    "1110000011111000011"
                    "1100001111010010010"
                    "1100001101001110001"
                    "0010000010110001111"
                    "1001101110111100011"
                },
        /* 14*/ { BARCODE_HIBC_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "A123ABCDEFGHI1234567891/$$420020216LOT123456789012345/SXYZ456789012345678/16D20130202", -1, 0, 27, 27, 1, "IDAutomation example, same",
                    "001010100100100010000010110"
                    "000110110110001000101000100"
                    "010010001101110110001000110"
                    "000110101101000001010111100"
                    "000101110011011000111100000"
                    "000100110000110111011011010"
                    "011100000100000111111000001"
                    "011101111110011100111011100"
                    "110001001111110110101101100"
                    "100100001111111111100110000"
                    "001000101100000001011001101"
                    "111011010101111101111010001"
                    "010010101101000101001101100"
                    "001000110101010101010011100"
                    "011011001101000101010011111"
                    "011111010101111101000100100"
                    "110000011100000001001111011"
                    "101110110111111111111001001"
                    "001110110000000110000001101"
                    "010010001010001000001011001"
                    "000100111010110100000100110"
                    "000010100010001000000111001"
                    "111100011100100010001100100"
                    "001110101000001010011010101"
                    "100001000110111011000010111"
                    "011010111000111110011011110"
                    "000010010001000011010000001"
                },
        /* 15*/ { BARCODE_AZTEC, DATA_MODE, -1, -1, -1, 2, "\377\000\000\377\300\000\017\377\376\217\300\017", 12, 0, 19, 19, 1, "6 bit words",
                    "1101000001111000001"
                    "1101011000011100000"
                    "1000001010001001001"
                    "0110011100001000011"
                    "1001110101001011011"
                    "0111111111111110100"
                    "1111010000000110101"
                    "1110110111110100001"
                    "1010010100010101001"
                    "1110010101010111111"
                    "0001110100010101011"
                    "0000010111110101101"
                    "0011010000000110011"
                    "0011011111111110011"
                    "0110000011010001001"
                    "0010101001100111111"
                    "0001000100011100011"
                    "1011110000001001011"
                    "0011111100000000010"
                },
        /* 16*/ { BARCODE_AZTEC, DATA_MODE, -1, -1, -1, 3, "\377\377\377\377\377\000\000\000\000\377\377\377\000\000\377\377\377\377\000\000\000\000\000", 23, 0, 23, 23, 1, "8 bit words",
                    "11111111111111111100000"
                    "11011101110111011110001"
                    "11110110111011010101100"
                    "01111000111100011111100"
                    "11000101111110011010100"
                    "11001111001011001100000"
                    "11000111100110101001011"
                    "10001111111111111100111"
                    "11000111000000011111011"
                    "11010111011111010001101"
                    "11000011010001011010111"
                    "10000101010101011000011"
                    "11001011010001010001011"
                    "11011011011111011101001"
                    "11001111000000011010011"
                    "10001001111111111111011"
                    "11001100000000000000111"
                    "11011011001100000010011"
                    "11000011001011110101011"
                    "10001000111111011110000"
                    "11000000001110101011000"
                    "11011100001000100010010"
                    "11111110000000000000000"
                },
        /* 17*/ { BARCODE_AZTEC, DATA_MODE, -1, -1, -1, 13, "\000\000\000\377\377\000\000\000\000\377\377\377\377\000\377\377\377\377\000\000\377\000\000", 23, 0, 53, 53, 1, "10 bit words",
                    "00011010011110010011110101110010000000111111010101001"
                    "00000010100101010010001000010100000010101101001111110"
                    "11101010001110100001111100110101111010110110110001010"
                    "11000010110001100001000100010011110110001001110110011"
                    "11101001111011111001010000100101101011101010101000100"
                    "01110000100100011010101111011100111000100001000011011"
                    "11001000001101011010001111100001101111000011010001110"
                    "00001110000100111010100000000110101111011101001101001"
                    "00101001111001011001001000110011011001110011110010111"
                    "00001110100001001111111111001011001010001101001101111"
                    "10101010101010101010101010101010101010101010101010101"
                    "00010011000110111100001100011010011010101101000001000"
                    "01110111011000100011111111111111010100110010010100110"
                    "00011101100100100001111111000100111100010101101010011"
                    "00010100011010010011101101101001100101111110110010011"
                    "00110110000001100111111101001111100011110101011110000"
                    "00111110111111001011010000100001100001101010001101110"
                    "01010011000110100110101111000100000010000000000111110"
                    "00011001011011101101110111100010000100010011111011110"
                    "00011010000111001001101000000000010100110001000111010"
                    "00000100001011100111111111111111111000010010001010101"
                    "11110000100101010111100000000000100000101101001011100"
                    "11100011101111001100101111111110111111010110000001111"
                    "11000000010100001101101000000010100100010000101010110"
                    "11011000001010101011101011111010110100101011100111110"
                    "11101111100010111000101010001010101011011001010101001"
                    "10101010101010101010101010101010101010101010101010101"
                    "11000100000110100000101010001010101100101000011000011"
                    "10110100011010000110101011111010100100100111000101100"
                    "11000001010101000101101000000010111010100100000101001"
                    "10110111011110011110101111111110110011001110000001100"
                    "00000111100110110001100000000000111000101101111011111"
                    "00100101001001100110111111111111110110100111011101000"
                    "00001100110000110010001101011000001100110001110010010"
                    "00001010111110011011011100110001001110011110100100100"
                    "00111111000010000111110111010111101010101101000100010"
                    "00110100101110101000101110100101010110101111001010100"
                    "00100100000010111111001101001100000011110001111100101"
                    "01011111101101001110100101101000000111101110110111001"
                    "00001111000100101010011111001100011101011100010011010"
                    "00001011111001000011100001100001000001111011010101111"
                    "00000101010011100101010000010010000010011001111101011"
                    "10101010101010101010101010101010101010101010101010101"
                    "00000011000011110011111000001000000110011100110110010"
                    "01100110111101101010001110101001111111000111011110000"
                    "00010110000111101110001011011110001100100100000001000"
                    "00110110011101001010011110111110111101010110001011100"
                    "00100010010011101001001010000101011011011101011100010"
                    "01101001101111101010010000110100110011000111011010000"
                    "11110001000011110111001100010011011001010001110101000"
                    "11011000101001001101101111100111101001010110111011100"
                    "11101111010111010000111101011101111011000000001011100"
                    "11111111111111110000111111111111111111100010000011111"
                },
        /* 18*/ { BARCODE_AZTEC, DATA_MODE, -1, -1, -1, 27, "\377\377\377\000\000\377\377\377\377\000\000\000\000\377\000\000\000\000\377\377\000\377\377\377\000\000\000", 27, 0, 113, 113, 1, "12 bit words",
                    "11111010101001000010110010110110001010111011100001100010111010111011011110010101111001111110001101011111100000011"
                    "11111001010001010111110100101000101000010110010011001000011010011001111000010101011110010001110101100110011001100"
                    "11101100111000011000000011000001001001111001111110000001110100001110010010001100100011101110000011010101101011011"
                    "10110010001100011001110101101111111010100000010000011010011100111110010000000111011110010111110001010010000011001"
                    "11101111110100000110110011100000101100011010001010011100110001010111001110011001100010101101000101001000110110110"
                    "11000001000111110000011001001100110001010000000001010111000100101100100000011011001001000111011001101101001111101"
                    "11011101101011110011011110111101101101001100010010101010100001111111100110011101010100011100110111111101101100000"
                    "11011110000101110011110000101111100111100101011010100010011000011100010001111000100110100101011011001101011001101"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11101110000011011000110000100100010110100010110101111111000011111011010101010011000101000110111111111011001101111"
                    "11010011100011001101011011110000010100011001100100111111111110001010111110000000001111001110000001111011110100101"
                    "11110101011101110000011001000111000101000011000110111011000110110011100100000111101100000011000100001010011111001"
                    "10111001111000101000101111110101001000001000001100011100111001011010001110110000101011001001111001100011101001010"
                    "11101000001010100010000000100110101011010100010000110101010111111011000101110100001101110110010101010101011010000"
                    "11101110101000010010010111101100100110111000111001011010110110010001111010010011011100001001011101110010110111111"
                    "11101110001111110110010000110111101100010000111100110111000110111101101001111001101010010100011010001001001110001"
                    "11111000100110000011010110111010101001001011001101111000110110001011000110100000100100001111000000000100101010001"
                    "11001110001110100010000001100110100001100010001110001011000100111100111101100000011101000001010110101111010011001"
                    "10100001101001100010010010110010111001101000010101110110111010000111100110000001110111111000110001000110100100101"
                    "00111101011000111111010101011111111011000000001110101111011101110111100100011111001100110000110000011001010001100"
                    "00000011111100000101111110100000010010101000000011011011111110011000100010011000010100011001010101001000101100001"
                    "00000010011110111000110101001101011101010011011111011111010110100000111000100001110010110001110111110101001100011"
                    "00100101101010111011111011011011100110011100100111100111101011010011100010100110101011001111111010100111111011111"
                    "00100001011101110100100001001101011101010111100001000100001000110111111100010011110001010000100001110001000001111"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01101111010111101011110101110001010000100011000111100011010110111101011101000001001011110111110101100000001010101"
                    "00011110100001100110001010110011001011011110110110110000101100100110100110001111111011111111010100111000101101111"
                    "00001100001111101101101000011101111101100100001011000001001000010111101100100011101101110001010010111001001111111"
                    "01001010110111011110001110101011101100111110100101100000101001111101010011001111110101011110101011100001100010001"
                    "11111110010100000110111001001010100011010100110101011101001000111010100100010011011111000100001100000000001100100"
                    "11101010100001010011100010010010100010001000001000110000110110000100011110001101001101111111110011001010101101110"
                    "11010001000111100010100000111000011111000110011101100001001011010110111001101011111100000000000001010011010111010"
                    "11001011110110001001101111000111101010011100001011011001101010000000110111111011100011111010100100001110100001001"
                    "11110111010110000000011100111110101000110110101110001000011011111010001001111000110010110011110110010110001100101"
                    "11011000101011000111010111110110101000001010001011111000101010110010110011000100100101001100010110100001111111110"
                    "11001100010000000000101100001110011101100111100110101110000100101010111000100001001000000001011111100100011111011"
                    "11001000101100010101000010000100110001001101101110100100100111110111011011010111100011101011001001100001110010110"
                    "10000100001000101100011001011111100110010111111111011011000011011110001100001000101110100100001010010000000001110"
                    "11001001100000100110010111011101111010111011110011100110110011110110111011011101000001111001100111111100110110010"
                    "11110100010011101010111101111011100100010001110000100010010100011110001101101100000110100110001010001100000110110"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11101010011001111101000001000100111100010111100110100011011111100010100100100100101000000000011110011010011111100"
                    "11011000110000000101010110110011111000111110100100000011100111011010110111101010110000001011111100010110111101101"
                    "11100100001010010001100001001100000011100000110001000110011110100000001101000000101000000000111111011111001011111"
                    "10110100101101001001110110110000100011111101000011110010101110001111001010010110100100001001111111101000111111111"
                    "11110111000000010110101000100110010010110011111011100001001001101110111101001101111001100101111010110110010010110"
                    "10101010111100101100111010010101101111001101011101100110101000101011110011001001011001011010000111100110110001100"
                    "00011000010111101000001001100001101110000101000100001100011010111000100100011111001101110010101010100011011000000"
                    "00000001111010100010111111010011001010011100111010010001110001111100000111000100011011101000011111000011101011111"
                    "00101011000110101001011000111011011001010100111101110110000000010011101100100011101001110111001101011110000000011"
                    "00010000101001010000110011111001001110111111011011111111111111110010110110011111010101101110111011111001111001100"
                    "00000011011110011110000101111111101001000011011010100000000000100100010101010110111110100000000101100011011100101"
                    "00010111100101101100111111000001100010011011011010101111111110110110100011001010000100111001100001101001100100010"
                    "00001011011111110001111001100001000111000000010011101000000010100011100100001110000011000100111111010001011011001"
                    "00110000100100110001100110101011100110111011100001101011111010101111100110111011010000111011011001001110110100001"
                    "00011001010000110100101000001000011000110011111011101010001010111010101001111011110010000111010001110101011110010"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01100111001110010110110100001110110000000110011110101010001010110000011001000001000101100010011011100101000111001"
                    "00101001100010010001111010100101101110111011101000101011111010100001011110110000010010101100110011011010111001101"
                    "00000100001011011100011101111011101110110010010100101000000010111010010100110110101110110000100010101100001011011"
                    "00110010111110000001110111010110010101101101000000101111111110111000110111100000001111001011010001000110101010110"
                    "00100101010110001001011100111010111001110110111111100000000000110010011000111011101110000010100011011001000001001"
                    "00000000111101111101111110111000101000011111000100111111111111110100010011100110010001101011001100111011110101110"
                    "01011111001111001111101001100010110011000001010110011110010001000110101001101111110100000000111100001101010010000"
                    "01110001111101111010111011100110010011101111011111100000100101001111010111111101100111001100101001111000100011011"
                    "11101100000100010100011100001011011101010101101101001010000101001111100101101100001100110101001010100000010000011"
                    "11001111110100111000110111111000110001001111110000010111101010000000010011100111010011111000101111100000101111101"
                    "11111011011110101010100101110100001011110000000000010001011011001111000101010000001100000111100001100110001100101"
                    "10001111111110011011110011111110001110011000010011101000101000011100111010000101111110001110011110001101100001101"
                    "00001100001010000010100001011101011100110010110010001000010010011101011001110011011001110001100111101110001001001"
                    "00100110110000000101000010110101010001001110101110000010110110101111001010011011110111101011101010011000110010000"
                    "00011111000011010010101000010001110010100110101010010101000010101111100100010010111010110000010011111100011000100"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "00100110010000010110110100011110100001000011011000110110001011000011011101101011101010100101110110101111010010101"
                    "00001100100010111111111011011000100110101110110010000111100110001100111110001110101100101100001011001101100100100"
                    "00000100000110001111010000100000100011010000011111111010011011110000111000011110001000010101100001100001010010110"
                    "01010011111111111100001010101100001010111101001111100010111110010000101010100000011100101001110011011110101011101"
                    "00100110001010001111011101101111100000000000001101010011010111010100100000010011101011100101111001111101011100101"
                    "00111011100011001100100011001110001011111010000101101001100110001110111010111110000101111100011110010110101110100"
                    "00011000001101000110001001000010010101010111011101100101010000000101100000010001111001010101100101100011001000110"
                    "00101001111001011010110111010101001010101111111011010111100111001100010010010001101010111000100111000110111101110"
                    "00001000011101110110110101111110100010100100011110000111010100000100010100101111010101110101001111000101001110010"
                    "01010111110111001101011110101101001110001011010011011111100000100011101010101110111101001111110001100010111001011"
                    "00000111000100111011101101010100001100100110010110010010011000111000010000011100000110100010000100001011011011010"
                    "00001101101110011111110010000111100110111100101011011110111111010101111111000000111110011011110000010111101100000"
                    "00010010001110011111110101110000001100010001111001101111000000101000000001010001100111100001101100010010010111110"
                    "01110011101110110110110011011101110100001010010110100110110011101011100011001111011110111110101111011101110010001"
                    "11111010000100110111101100110110111010110011110111110010000010011000011101111101001101100100111000110001011110001"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11010010010101011110111001111011101100010101010111000000011011011111101100010000000100000011100111000011010101101"
                    "11001111111111001010101010000001010001011100101100110110100110111010101011101111100100011011100110110101101010011"
                    "11110011000011100100010001101001000101000010111111010101001110110000010000000001000101010101100111010110011101100"
                    "11100101100001000110100111011001011000001100010001100110101111110110101111100101010001001100110011010101101001110"
                    "11111001000100001001110100011001001110010011001100000000011111000110010000010100001011010010100010111111000100001"
                    "11001100111001110001010011110110011110101010100001111011111010111011011011010010110010101000001111000100111100110"
                    "10010100001100111111100101101000111001110111010011011110000000110111001101100010110110100001111011001011011000100"
                    "00111010100010111011001111110001000000101010011111111111100000100101110110101010011101111010110100100001100001100"
                    "00110001010001110111011100011011110111110110100010000100011011110100000000100000101000000010010100011101010100100"
                    "00101000100110010001111010000110100101011000011111101110110000100111100011000110000010011011111100100010110011000"
                    "00000101001010101000010101000110010110110101000100100110011010100101110000110100100111010100111100100100011110111"
                    "11011100101011111001110111001000101111001001101101010111101101011110110011110110001110011001001000010010110001101"
                    "11000010011001001000100101001100111011000101100000111110011011110011100101000010101011000000110000100101011010000"
                    "11000001111010110010111011110100100100101100111101111100111010000011110010011001111110101100101000001000100110010"
                    "11110111000001001010010000001000101101110101001110110011011011011010010101111110000000000111001111010010011000111"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11000011011111001011001101010001011100100111010000101011000101111101101101000101110101110110010011100011001101100"
                    "11001000101111010000101011101000011011001010110010101000100011110101111111000001000110001101100001001110111100101"
                    "11101110000100001111001001001101100111000010011100011111001010100010101000011110000111000010101001100010010001111"
                    "10000001111010110010110010001111101001111011011100110001111111001011010010100000001011001111010010101100111010111"
                    "11110101011110010111100001100001000000010111111010101111000001100011111101110001000001000001100000100110000001011"
                    "11101101100010110000110110001100111001001101000101110001101010000111011110000001111001011010110100011101110011100"
                    "11000000001000001011101101101101101001100000101000000000010111000000100101000110010000110010000011000101011111000"
                    "11100000100000001110111110110000111110011100000010001110101010101111000011001011111001101101010010001011111011101"
                },
        /* 19*/ { BARCODE_AZTEC, UNICODE_MODE, -1, READER_INIT, -1, 1, "A", -1, 0, 15, 15, 1, "",
                    "000011000111101"
                    "001110010011000"
                    "011100100000100"
                    "011111111111110"
                    "101100000001010"
                    "110101111101100"
                    "111101000101010"
                    "100101010101000"
                    "100101000101111"
                    "100101111101101"
                    "000100000001010"
                    "100111111111100"
                    "100011001110001"
                    "110110000101100"
                    "010001010010110"
                },
        /* 20*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 2, "121212121abcd", -1, 0, 19, 19, 1, "#210",
                    "1101101111001101010"
                    "1101111011110110000"
                    "0001111101100010000"
                    "0100011111001001001"
                    "1010110100101010010"
                    "1000111111111111101"
                    "0001110000000111110"
                    "0111010111110110100"
                    "1001010100010101010"
                    "1001010101010101100"
                    "0010010100010101100"
                    "0110110111110111011"
                    "1001110000000111010"
                    "1011011111111110010"
                    "0011000011111001100"
                    "0110100001100101011"
                    "1001001010110011011"
                    "0011111001001010011"
                    "1001101000100100001"
                },
        /* 21*/ { BARCODE_AZTEC, DATA_MODE, 3, -1, -1, 1, "\101\300", -1, 0, 15, 15, 1, "AÀ",
                    "000000101011100"
                    "000100010100111"
                    "001100000110110"
                    "011111111111111"
                    "001100000001100"
                    "001101111101000"
                    "011101000101110"
                    "000101010101011"
                    "100101000101010"
                    "101101111101111"
                    "101100000001111"
                    "000111111111111"
                    "100011000110001"
                    "110001000111110"
                    "111001100011011"
                },
        /* 22*/ { BARCODE_AZTEC, UNICODE_MODE, 26, -1, -1, 1, "AÀ", -1, 0, 15, 15, 1, "AÀ",
                    "001111011000101"
                    "000110100011000"
                    "001100001000111"
                    "011111111111111"
                    "001100000001101"
                    "000101111101100"
                    "010101000101101"
                    "011101010101001"
                    "001101000101001"
                    "100101111101001"
                    "010100000001011"
                    "000111111111111"
                    "000001100010010"
                    "001100010010010"
                    "011110110011000"
                },
        /* 23*/ { BARCODE_AZTEC, UNICODE_MODE, 100, -1, -1, 1, "A", -1, 0, 15, 15, 1, "FLG(3)",
                    "001101001111101"
                    "000000111011100"
                    "001100000100101"
                    "011111111111110"
                    "001100000001111"
                    "000101111101001"
                    "011101000101001"
                    "010101010101001"
                    "100101000101101"
                    "011101111101010"
                    "100100000001100"
                    "010111111111111"
                    "000011011110011"
                    "100011101111100"
                    "000111110001110"
                },
        /* 24*/ { BARCODE_AZTEC, UNICODE_MODE, 1000, -1, -1, 1, "A", -1, 0, 15, 15, 1, "FLG(4)",
                    "001010100011011"
                    "001000100000101"
                    "001100000100111"
                    "011111111111110"
                    "001100000001110"
                    "000101111101000"
                    "011101000101010"
                    "100101010101001"
                    "000101000101101"
                    "011101111101011"
                    "100100000001101"
                    "010111111111100"
                    "000011011110011"
                    "101000000111010"
                    "000001110101111"
                },
        /* 25*/ { BARCODE_AZTEC, UNICODE_MODE, 10000, -1, -1, 1, "A", -1, 0, 15, 15, 1, "FLG(5)",
                    "000100110110010"
                    "000001000010111"
                    "001100000110101"
                    "011111111111111"
                    "000100000001010"
                    "001101111101101"
                    "011101000101110"
                    "100101010101100"
                    "100101000101101"
                    "010101111101100"
                    "101100000001011"
                    "010111111111111"
                    "000011110110011"
                    "101010001110110"
                    "000000011000101"
                },
        /* 26*/ { BARCODE_AZTEC, UNICODE_MODE, 100000, -1, -1, 1, "A", -1, 0, 15, 15, 1, "FLG(6)",
                    "000010010000010"
                    "001101000100110"
                    "001100000110111"
                    "011111111111111"
                    "001100000001110"
                    "001101111101010"
                    "011101000101111"
                    "110101010101011"
                    "000101000101001"
                    "011101111101101"
                    "101100000001110"
                    "010111111111101"
                    "000011000110011"
                    "101010100011011"
                    "000000000111010"
                },
        /* 27*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", -1, 0, 61, 61, 0, "Zint website example gui3.png NOTE now ends with D/L . instead of P/S .; BWIPP same encodation but estimates number of Data/ECC codewords differently",
                    "0010110111101110101100000101001101110100010000100111011100001"
                    "0001100000000000001101110010000100010101110011000001000011110"
                    "0001111110101010100101000110101101000110011000101111011100110"
                    "0011000000001001101011010000010110111000011110000000010001001"
                    "0111001010111110010111100000001111101100011100100000001000000"
                    "1001100111000000001000011101000000001011001100000111100110000"
                    "1101101000101111010010010000101100010100100100111011011100000"
                    "1100100110001001100001110100100101001100011000001010110010000"
                    "0000101001000010000101001001101011110000000000100000001011111"
                    "1011100100011001100110101001100001100011110111010110110101001"
                    "0001101000110010111010000000001010111101010000100001001000100"
                    "0110100010001101000100011011100011000110000011011111001010010"
                    "0010000010110011001111011110101001010101001010100110000010000"
                    "1110001010110000110011000100010001111110110000011011001111001"
                    "1010101010101010101010101010101010101010101010101010101010101"
                    "0010110110101001010101000111110011001011000111000011100111001"
                    "1100110100101111110010000000111011110100100011101100110001100"
                    "0001001001100101000010011100000111100000111010011000000001101"
                    "1101000001000011101100000010011100001110110010101001000010010"
                    "1010110011000101100001111000100001001111100010001100111001100"
                    "0010011111000011101101000010101100001001000100100110000100001"
                    "0000100101100001111110111011010011101000011010000100000011101"
                    "1010011010011110110000000000011010110110101001111101010001000"
                    "1000100001011000111011111010100000110100010111010001010001110"
                    "1001100110000011001011011111111111111110011010101011001000000"
                    "1011110010100101000001001000000000001100001001011011001000000"
                    "0000011111110010010001111011111111101000000001110010001110100"
                    "1100000001001100110101011010000000101000010110011110010011110"
                    "0110010000111011111010111010111110101010111010111111001000010"
                    "0001001001111101111000011010100010101011100000000000000001010"
                    "1010101010101010101010101010101010101010101010101010101010101"
                    "1010111000100000110011111010100010101011100001000111100001010"
                    "1101101000101111100010101010111110101001110111100010010101110"
                    "0010000101101001111100101010000000101101111100011110110111110"
                    "1100101110001111000000111011111111101101000101101000010100011"
                    "1000011000011101111101111000000000001111100100010100010011000"
                    "0010000010010111001010001111111111111110000100101110110111011"
                    "0001000100011000011111100010110001100011001101000000010000100"
                    "1010001010001110100101011010001101011111010011111000011001110"
                    "0110000110110101011111001110000010010001010111000101000010100"
                    "0110101001110010110010011100001010001100000111111100011000000"
                    "1010110110000001111100011001000011011001111100010110000100000"
                    "0000011010001010000011011001101001110010001100101000111011010"
                    "0001001010100100010010000010110110101110101100010101010001011"
                    "1100010000010110110110101101101011111001101111110100011000011"
                    "0110001101000001111010001100110011001111011111010010100011000"
                    "1010101010101010101010101010101010101010101010101010101010101"
                    "1011000001100100011100000111010101011110110011001000100000010"
                    "0000111101110110001110101001001101000011110010100000101001010"
                    "0100100001011000000001000100000010001011110101010011110110000"
                    "0001001110010110101001011101101010001101000000100001101000010"
                    "1110010011010000011001010010010101000100110100011010001101100"
                    "0011001010010010011100110100011000111011100100110001001001001"
                    "0000111010110000100100000001110011001110001101010100001010101"
                    "1100010010110111011011111100001011001011001011100011100000101"
                    "0110111000011101110110010111100000010000011101011010001110101"
                    "0001000000111010000000001100001010101111100010100000010011101"
                    "0101000010010000110000000010000001110010000111000111100011000"
                    "0110100111000110011010010101111110001000000011101100000100101"
                    "1110000011010000000000100001100001000111011110011010000000001"
                    "0000010101001111100010001001111100101000010001110010010101101"
                },
        /* 28*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "Colon: etc. NUM. 12345, num. 12345 @, 123. . . . . @.¡.!A ", -1, 0, 27, 27, 0, "BWIPP different encodation (better use of D/L and B/S)",
                    "001011011101101011011110111"
                    "101001010000010000111010101"
                    "011101001100101111010111111"
                    "110110011100000110101001100"
                    "001111101101100101101110001"
                    "100111011111010110000110011"
                    "001000010001011010000001001"
                    "001000110100110011000111111"
                    "110110111111101100110000010"
                    "011110001111111111110110000"
                    "100101000100000001011101100"
                    "001110100101111101010001111"
                    "001101111101000101100011111"
                    "110100110101010101100001010"
                    "111010100101000101110000101"
                    "000010101101111101000101010"
                    "000010011100000001011100010"
                    "001000100111111111101010010"
                    "010101000000010100010000000"
                    "011011001101111000010001010"
                    "001010001110010110111001111"
                    "110011011101100111101010100"
                    "011011101110010010110011101"
                    "011111111001010010100110111"
                    "011101011001001010010111111"
                    "000000111111011010100010100"
                    "010000011101011110110000100"
                },
        /* 29*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "1. 1a @ A@@ @@!!@@!!1!!!!¡a ", -1, 0, 23, 23, 0, "BWIPP different encodation (better use of B/S)",
                    "11110101100111101010011"
                    "11111111110111111001011"
                    "00000000001000011111000"
                    "01011101110100100010110"
                    "11100111000010110111010"
                    "10001110100110000111101"
                    "10110111100111001011101"
                    "00000111111111111000101"
                    "10010101000000010101010"
                    "01100001011111010100010"
                    "11000001010001010101000"
                    "11111001010101011000100"
                    "01010011010001010110100"
                    "11110001011111010110111"
                    "00111001000000010110100"
                    "00110001111111111110100"
                    "01111000110001100101100"
                    "00100010011001110001000"
                    "00001101111011011111001"
                    "01011001100100111010101"
                    "11010001100000011111100"
                    "01100011101111001100010"
                    "11000011000010110000011"
                },
        /* 30*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, -1, "1234\01512\015AB\015AB\015ab\015ab\01512\015ab\015!\015!\015a,a,1,a,@,", -1, 0, 27, 27, 0, "BWIPP different encodation (better use of P/S CRs)",
                    "111111110000010110000011001"
                    "110110110010011110100000101"
                    "000011100001000111001100111"
                    "010010110001110000100100110"
                    "101001010011110101010100011"
                    "100111100011101010001101110"
                    "001001011111111011000000011"
                    "100011010101001101001011110"
                    "100010001111100110110101110"
                    "111011011111111111100110011"
                    "000110011100000001110110111"
                    "001010001101111101110000010"
                    "000000011101000101101010000"
                    "000011001101010101101110001"
                    "011110001101000101000100100"
                    "001100111101111101110100101"
                    "111111000100000001010101000"
                    "011010110111111111111011100"
                    "001111010001101110010011100"
                    "000001011010011101101000000"
                    "000011010100101100000000101"
                    "000101100011010101010110010"
                    "000000101000011010111000000"
                    "110000000111001101111000001"
                    "110010101110100110101001000"
                    "000110100001100100110010100"
                    "101110010000110000111111101"
                },
        /* 31*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 6, "AA!! ", -1, 0, 23, 23, 1, "",
                    "00110111000010111110110"
                    "01011001101100101011001"
                    "00101000101000011110111"
                    "00011011100111110011101"
                    "10011100001000000010001"
                    "00001111111111111110000"
                    "00010100000000000100111"
                    "00011101111111110100111"
                    "01000101000000010101101"
                    "11110101011111010110011"
                    "00110101010001010110010"
                    "01010101010101010101010"
                    "00010101010001010100011"
                    "00100101011111010101001"
                    "00100101000000010101010"
                    "11001101111111110111100"
                    "00011100000000000101000"
                    "00110111111111111111011"
                    "01100000101000010001001"
                    "11101001010111001100010"
                    "11110100110010110001111"
                    "00111110110110100011111"
                    "10010010100010101110001"
                },
        /* 32*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 36, "Lorem ipsum dolor sit amet.", -1, 0, 151, 151, 1, "Max version 151x151",
                    "0110011000001101111010100010010110101010100001110111111001101101010000111100111111111001000011100001010000101001010001001010101001000111101011111001101"
                    "1011011111111000001111111001010101111011100101110110001011011000101000010101101100000110011110100000010100110111100111111011011110001000110100111100100"
                    "1110001110001111110101011110010010011011001011001000001010000010000110101010101011111110110010000010000111000010000011011110001111111001000010000000111"
                    "1111111110111100000010100111101000111010110101100001000110010111110111110011110100111110101100011000001010110110100001111101110111001101001101011100001"
                    "0001111011000111110101010100010001011101110011011100001110100100111111001010100000010111000001100010110011100000111110011000101100011011000010100100001"
                    "1010011111011100100000000001110110111000110110010101110001011100100001101101111010100110101101111101111101011101101111001001010010011000011110010111000"
                    "0010100000000010010111100000011001110011011011101010011101101010000010010110110100010010010001000100001011100011011010101010001000010011001010110111111"
                    "0111111001111100110000010101000101011011100110110110010011011110101110111011000100111001101100111001011011110101000100101111101001100011010100010101110"
                    "0010010101101010010100100100110010111100100010111001000100000101000110110000110110100000011010001001101010100010011110101100110010010100011010001011011"
                    "1110101000010010000001001011111110111011001110110000111011111010110010001011111101011101110100100000010101110001010101101001101101101110011110100001110"
                    "0001011111001011100101100010111101000010011010000010010100000111011111100010110101100000101011011101001000000011000001011110001001001011101001101001000"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "1110101001101000000110000100110101010101001011110010001100001111110110010000101011100011011001000110101100100110110100001010001011101111011000001110110"
                    "0000111010111110110101010011100110100110111101010000011001110011001101100011100001000000100100110101110111010011010110011101110111100101011110001001001"
                    "1110100110100000100100001010111100110000001000000100001010000010010110001010001111111010111001010110111100100001110110011000100011100011011001100001000"
                    "1001000111111111011011001111011110111000011110101110011100011101110001010111001111001010100110010010000101011100110010001001011100010010111100110111101"
                    "0001001001001100010001111110010110001101000011010111000011001000111110011110000100111111100010011001100111001001110111110000110101110001100010001000010"
                    "0000000100011110100100000011010101101011010111110000000110110010011111110111010110100001111110011000010001110100101110000101011100001000111101100000010"
                    "1001000010101000000001001000101000111110010000110111000111100111111010100100111101101001101010100010010010101001110011001100010001110001000000101001111"
                    "1011010010111100010011100001111110100001100100010001001010110101111101010101111101010101011101110101011111110110011011101101001110000101110111010010110"
                    "1000010000000110100010011000100011000000100000011111111101100001010111000010000101100110101011011010000100000100100111100010000010110100010011100010110"
                    "1010110100110111101010110101000000001111001111011001111000010011010111001111110000111011000101000110010011011100110111101001111001000001110100001101001"
                    "0001100110001110101110000010000000111100000011111000101110101111100111001110011001000110001011100101001100101110010000000000011111101011011011001010110"
                    "1110001000010100000011010011011100011000010111101010111111010011001010011101010110011010001111101001100101011101100100011111111111000001010101011001011"
                    "0100110011100111100111010110010011000001010011001100110010101000101001001010100111100110000001001101011101101000111001100100011010011000001001100111110"
                    "0011001110110110101100000101000111010001110110010110101000010111111110100001101011000110011111000000101011011000110001010001101111000111000101000101101"
                    "1001000100101010110101111010011011011101101000011000001011001000000011110000011110100111100011100001011001001011011100111010010100101110000000111011110"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "1101101101100010000110100110000001010101011010111011011010101100010100000100100110011100011000100111010110100100111011101010110111100011011000011011101"
                    "0010011010011111011100111101111001010010101100001000011000111101010100111001011100010101011100110001001100110001101111101111000110110000010111001011111"
                    "1101000110001011110100100110010100000011000000010000111010001001010100000010110101000010000000001010000001100011101011001110011011000111101011111001000"
                    "1001000010110011011110000111100001100001111100111111001100010111011101101111111101011101110110101110111011011100111101110001110010110001000101011011000"
                    "0000000100100000011011001110011011001010000011110000101001100000011100110010101010010010001010010011101100100100001001101000110111000000010010011111000"
                    "0010111110111010010000100001111110010010100111100010001100110000100111011011010111010101100110110010000010011010111011010111011111111000000101110101110"
                    "1010101111000010110010011010101001101010111000010010010001001110010111111100110111010110111001101100000000001010101100100000101011100101100011100100101"
                    "0110101110110100101100111001111000011000001101000011100011011010110011010011001100011101011101011100110001110110000000100011011111011100101110111100110"
                    "0111110110101000001001001000100101011000100001110011100000000000111111100100010101001100010010011101010011000110111100010000111000000111011000100100001"
                    "1010010111111010001001100001001101111100100110101101011000011110010111001101101001101000000101111000010010010111001100111101110110010001101101010100000"
                    "0011100010101101110010100010101000010011001000100000010110100110110010001100001100111100001010101101001010101000011110010110110101100101001000110000001"
                    "0000001010011110010101110111001100001101011110000011110111111010101111001101111000110000110100110001101000111100010111010011001000001010100100010111110"
                    "1100110111001001100100000000100000000001001000011001011011100000001111100110001110001111000011111001010111100111000111111110101011100101011000000100001"
                    "0101110000110100000101101001001011011110110101011010110110010110000001101001011001110110000101101000000011111000101100101101001100101001001110010010001"
                    "1000000100101010101110001010101010000110100000000010010101100100001000000000100110010100001011010001110100000111110110111010011110000000000011101100001"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "0010101101101101000001101000100111100101010000110001010010101000010000000000000010111010100010010000000010101111100001010010001101001110001001101000001"
                    "0111010100111101011001001101101001000011000111111111110011010101000000010011101010101010010100000100110001011000100110100011110000110110000111111001101"
                    "0001001101101100100010100000100110100000011001110010000110001011100100010010101011011000011000101011011110101011100100101000111001010001100011011100100"
                    "1101011011011101000110100111100100011011110110101010011010011100101010000101000101000110101110001011000100110100101001011001000100011000011101000010101"
                    "0011100100101001100001000100011011110010100000000110010100100101001000010000100111101100001011010010001101100111111000010010110000110110011001000001011"
                    "0011100010111011110010111101010001000110110100110011101011110011111100101101011001101011001111000110111111010100100100101001111110010000100111000001010"
                    "1100101101000011110101001110110011011100100011000011101101001001100011011000000111101011110010001100111101101100011000111100001010110100100011100100010"
                    "0100110010010111110000101011101111111101111110000001010011111011111111101001110110001001011101100101110000111111101110000101101010010010010111110101010"
                    "0011001100000011000111111000101001000010011011000010001111100001111011010100100110000100101000110010010011001110000100011100010111011101101001011111001"
                    "0111110110010111010011000001010110110101010100011101001111011010001000011101100000001101101110000011000111010010100110010001110110100010010110001101100"
                    "0110011111100110111111101000111110100100011001100010100101001100110100100010001010101110101010000110011111000001010101101100100011011100000001001110000"
                    "0111110101010110000101100011100010010110000100110000001111110001111010010101010101100111001100011100001010010001001000101111110101001011111101001100001"
                    "0111011010000001000101011010110010110011100010110110010011001101110011011100011110010000011001100100011001101101000110001000001000101010101010111000000"
                    "0100000101011111110001001011011111000101011111101011101100011111001001110111110001010101011101101010110011111101100110100011001101010000000101001011001"
                    "0011001010101111100011001010010011100001001011100111111111101111010011011100011110000110101001001101101100000100010001101010100101100001111011101001010"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "0000011100101011001000111110011011101100011010001011010010001110111011101000101001011111010011001010100011001000000000101110010010010111010010001111010"
                    "1001100110011100011111000101000000100000011101110101110011111000000100011011000001110011100110001001101110010011001110101101100100100100001101000010111"
                    "0001010010100000011111001110101010100111011011000111110100000010111111101010111001000001110000111000001111101011000010100000111000001000111001111000000"
                    "1011111100010010110100100101010100010010001110100000101001011111110011110101101110000000110101001011100011111001111101111111111010110101010110100100001"
                    "0101111011100000110101111100110110000000000011011101110011101111000101111100011101111000111010110110100100001111101110000010101011110010110011011010011"
                    "1110100100110011000110110101000010010011000110110100011000010010111011000111010100110100010111111100110000010011101011000011010001011100000110000100001"
                    "0001111101001000101110001100100001011100011010101000001111100000111100111110010100011101011001010101101001001010101101001110110110001100100010000100011"
                    "0101010000110101111110010101100100001101101101111000101000110011100101001011001111101001001110100001101111111101111011100101111001001000010101011001110"
                    "1001010000001111111000000010011001010011100000010111101101100101010111111110000000111010000010100111010010000100000110010010011110110111110001011100100"
                    "1010111001010011111110000101000100010101001110101101111110110101101111111111111111100100110101111001010000111001101101110001111110111010110101110011111"
                    "1000000100100010010101011110110111100111011011101000111111001110001001000000000001010110010000000110100001100000101111001000001010100101101000010001001"
                    "1110011000111101010011001111011010010011001100101100101110010101101111011111111101010101011110111001010001110000000010000001011110101110010111001100111"
                    "1100100000000011110001110010001100000011001011011000111101101001001001010000000101110011010010000011011100000000101100000010000101100110111010011101000"
                    "1001001010110111111111010011010101111010101111000101110111011011110101010111110101001000001111111111010100111001111110010101001100110100000100110000000"
                    "1110010000000011010111110000001010000110010011100111111100000001000011010100010101101111011010110000010000000010000110111100010001001011100000000101110"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "0111000010101100001110010100000100001100111001111010010011001110111001010100010101100001010000111111001010101010100010100010100001110101010001001110000"
                    "1100010110010000110000100101001011111100111100101100001001111101011001010111110101000101010100111111001101011000111000010111000001011100000110000010011"
                    "0000100111000001011000100110100010111000001010011101111100001111000101010000000101010101000011100110100101000011101100010110001001110001010000111000100"
                    "1111110010010110011010100111010110000100111101111101111110110100000001011111111101000010010110101000010101010111010010100111010110011101110110000100011"
                    "1100111010101111110010110100100110100010101010111111101010001101100011000000000001100010001000011110100001000001010010010000110011000001000010100011001"
                    "1010111010010000101001111001111011111011001100101100000011010101100001111111111111111101001100110010010001110010100010010011000011100111011100110001110"
                    "0101101101000000010100101000000111000000011011001000110000001110011000100110100010000101100000101011010110101110111111101100010111111000100001000100000"
                    "0001101001011101010111101101111101011000001111111110000100010111011101101011010000101000110100010100100001010011111101011101110010001011101100000100100"
                    "1101101111100101000111111110111010110101100010101010001101100000011001000110000010011001100011001101000100100111101000001100110101110101011011011010100"
                    "1110001010010010110101010011011100000111101101111100001011111111001001010101010101001001111100010000010101011101101101001001011011110000110101101101000"
                    "1110001011100111101011001100111010010111000001100111110001101110001101111010000011011000111010100001101011100010110010111100110111111010101000000010101"
                    "0010100101111110111110001111000001101110100100100110011111010001001010010101000001111100100111110100001110110011111001011111010001100100101100010000001"
                    "1010001010100100110110111010011010100010101001010101010101000011011000011110110111010010101000110101101111101011110110011100101000101101111011011011110"
                    "0110000100010000100101110101101010010101010100001111011000111101011010110101010101101100001110011001001010111110001101100101000111011101000101101101000"
                    "0111011011000001110010111100100001111100000011000000011010000101101010100010100101010000010001011001101101000100111100101110001100111001101001000111000"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "1001000110000001010110111110000011111101101010010001111000101001010100010010100110001100100001001000000000000100111101111110001001000111000000000010101"
                    "1101000100010100111100010111111111001010011111100111101011111010101110110011101010010101100101111111001100011111111111110101011000110101001110001110000"
                    "1100010101100000000000111000000001011101010011010111000100000011100111100010010001000011101001000100010101001001110101011010010011100001010011101000000"
                    "1011100010110110110000100101100000000010010111010101100111110101001110000101111011100110101111100010101011110011110100101111101111011011101101111111110"
                    "1001101001000101000101000110110101001110111000011011110000100000110101110010011011100111111011100101111001001100101011000000011100010111111011010110100"
                    "1110100111010111100010100011100000010001101101110101000001111011010000000011000110100100110101101000110000110010101001101101110100100111110111000111001"
                    "1110011001100100010111011010001010010100001001110101001101000001101100001010110111000010001010011010100111101100000101010100001011101110001001101110111"
                    "0011001000011100100111111111000111111100110100100100001011010101011110101101110100101101101101110111101110011101001101100111100111001101100100010110111"
                    "1101011110001110111110100110001001000111111010011001010000100011110110110100000001101101000010010010111011101010100111101100001000100011010011111111011"
                    "1001100111010000100111100111010110111100010110111000010011110100110010011101100110101101010111001101100100111101001011001101010110100010111110010100010"
                    "1010100000100101000100111010101101000101011010000010011101001100110101001010001001010011010010111101000111101011011001101000001011111011010001111010011"
                    "0001111010010010001100110101111111101100001101101001000101111111111101010001111011001011101111111010011101010110111111001111100110001101100101001100110"
                    "0101000000101011000000010000101001011110111011111101001101000010101100101100011000000100000000001011100101001101111100110100010010100010111010011110011"
                    "1100010010110101000101011011110100001011100101001011011101111101000111101011000000100011001111100110011010111111101001010001001100000101011101001001010"
                    "1011111100100010001111101100010001011011001010000111110000101010000100010100101010000000011000101001100011100111010111010110010100010101111010110011000"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "1010011001001000111101011100011010101000111000111111111111001001110110001010010101100001011010110111010101101100011101111100010111101001010011100001111"
                    "1010000001011110101000101111001000110010000110001010111000011010110010111111110111100011001111111010001000110001111100010001100110100110100110110111100"
                    "1110100110001001111000011110010110101001100000011010010010101110100011100110011100000010000000100100001000100101100001000000100110100011101010101110101"
                    "0010111110010111100101011001100101010001010101101001001101011111011010011011000110001011101111001111011111011001010100010001110011101101011111101010010"
                    "0110111010101110011111101100101011000110011011101001110100101101101100010010111101000111010010010010111100001100101010011000001000000111100010011000100"
                    "1111111100011101110010111001000110010000101100101011101011011100110111000111010100001101001101111001001100011010111011110111111000010111010101000010100"
                    "0101111000101010101001011010011111101111011011010010100110001110010010101010000010101111011010100000011100001101000001111110110111000100011011100111100"
                    "0110000000011011110101001001011010100001010110010100011100111011000010000101010000001011110111111111100001010111010001110011001101010100110110000000000"
                    "1100110001000100110100011010110011110110000011010100111010100100011000000000010000110000110000111100010001100101101101111110101110011110000010101111011"
                    "1100110111110000010100001011001000001111001111101101010000011111001011100101110100100011110101110101011111111100001100100101100100111111010110011010110"
                    "0110110011000111100000011110111001110001101011101000100010101101101101110100100011100110010011100111101111100101100111011110001100111011010001110001101"
                    "0111001010110101011001001011000101101001001100110000000001111101011010001101001000010010011110101101111110011111101110100011101111001001011100101111101"
                    "0010011101101010100111100010011100010011000011010101101000001010100011101010111111100110001000000001101100100110110000000110011001011001111011101100001"
                    "1000110111011110100100110001000010010000100111011010001000011010111100010101001100011111101100010110000011011111101000001011111100110001101110110101011"
                    "1101011001101010111110000110100101010000100001001110101110000100010110001110010001010011100010110101010110001100000001101000010011101010000000111101011"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "0001001110100100001101000110101001111011101001011011001100101100111110000010101011101111010000000000100110101101001101011100000100000011011000010011101"
                    "1000010101110010110001111011101111111001101111011011101101011110001011110101010101011011010101100011101101010100111001111001100100010000001101111001011"
                    "1001110110000010011011111000101000110010000010000111001101100100100101110000101010011110111011010000001010101111011110100110011011100000111001100111011"
                    "0110000100011001011000111101110001111001000101000011111110011110110101000001111101111101100111110010101010110001011011000101011001101111110100110101011"
                    "1010100111100111101110010100001010110011000000010110011000000010100001000010101000111011100001001001010111001101010100100000110001011100011001100100100"
                    "1101011100111100110101110101001111100100010100110111011000010110100000000101001001001100011100101011110011110101001100110011010011111011010100100011100"
                    "0001111101101100011000100010110100110011100011011110110011101000101010010100110110010000011010100100101001100100011011111100101100101000110001100000010"
                    "0110110101010101011000000011101100110000010110111001001100111011011100000111110110111110110111101011000010010111010101110001110101110010111101011011101"
                    "1011010000100001101110101100011101011001000010110111111001000111101101011010110010010111010011000111101000100000110000011000010010110001011011110111110"
                    "0011101110011110110100001101100111100101101110100010001100011100001001001001000111001000000100100110001100111011100100001101101000011101010101100000010"
                    "0101000110101100011100101110101011111000001000010101011000000011001100101000110010100000101010110001111101101011010010010100011000001010001010010100111"
                    "1000100000111011001011000011100010110110100111011111001000111111111110011101010011100001010100111010011011011001001001011001010001011001011101011111110"
                    "0111110000100111111101001110011000101101110000010010101111101101000010000010000011100101011000101000011110101111100010000110010010100100110011011110010"
                    "0110100111111100001111000011010011010101101110001001110101111011000001000001001000100010001110100100001110010010010110100011001101000001100111110101001"
                    "0010011011100100101100011110010110011010001010001110111000101011100101001000101001001001101000010110000110101000011110110010101110101000011000000010110"
                    "0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "0000111011001011101000110110100010010000000011011011011101001010110100101110110100001010100000001000101100000100011011001100001001101011011000111010100"
                    "1011101011110000100011110101010110111100011110111001011001010000001011111111010111001100010111110011111000110011001011111111010010110100111101001111101"
                    "0111100100101010000001010010000101011001000001001101110000101010110000111110010110010101000010000011001011101001000110010010000011101010110001100111100"
                    "1000101111010011001101110101000110000001001100111110010110010010010001011001010111100110110111001001001001111101101101010001011111100101110100011110100"
                    "1101000111101110010011001110111100100110010000000110001101001001110000111100010101011100010011001101111100101110111100001000001111100000101011110110100"
                    "0110111110110001100101011101000011111001001111010100100101110011010000111111101100100111010111000101000001010011110011100011010001111011100111001101100"
                    "0101010101101010010000110100111010110010110001110011110011101100011111110000000101010001000011001011111100000111101000010010111111011111101000110010001"
                    "1100111000010101000011100001001001101000111101110011001001010111011111001001011011100001101100100010000001111100101001001111110000000110101111001100111"
                    "1001101001000001000111111110110101001101010000110110110011101100000101011010111100101000001011001101101010000010101000010110001101101011110001110010001"
                    "1000000100011011110011111011110000011111110111001111111010110101100011000111010100100010001111000101110110110100000111000011101011011101111111000011111"
                    "1000110110001001001111110010011100000100011010101101101101101001001001011110101010011110010011011110100111100111110111111110000101100111110000101010011"
                },
        /* 33*/ { BARCODE_AZTEC, DATA_MODE, -1, -1, -1, 31, "aztec barcode", -1, 0, 131, 131, 1, "Layers 27 example from Andre Maute, mailing list 2020-12-16",
                    "10101111100010101000001110000100001111111110110110010011000100100000011000101001100000001111111010100010010101111010001011001110001"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10001110111111000001001111011100100100010011110010101011110111111000000110101100000110101010110000010101101110010010010101001001001"
                    "01011001101100001111011110100110011101100100000111011100011110111100111011101100010001000101010011011110111101111101110001011110110"
                    "00010011111010010000101100000000000101100100001110001110011110010010100010101111100000011110100000010100110001100001010010110011000"
                    "11001001110100100101100011010001110000110110011111011000000100010101001010000111111010010011110101110011001111010110000101111111010"
                    "10111000100010000011110011100111101111010100001010111010110011010010101010001111000010011101110110111101011100010001111010011110100"
                    "01100011011111101110100010111100110000110010011111010011011010110110001000110011110010100110011111000101011001011110001011010101111"
                    "10111011100010110001000011000011001010001000111010011010000011000000101101111011000100110001111110110001010011100001101001000110101"
                    "01101011010010000111110000000000010100010111001001101011100011010110011001110011110000000101011001010011011110101111100101010011010"
                    "00101000011001101010110101101101100000111101001100100001110011101001000010100001000100001111001010100001010111010011110010111101100"
                    "01001111101011110101110001001000111001011110110101101011000010010111101001110001110011000110000101010011000010011111100111011001011"
                    "10101100000010001010110001101001001000111110110100111110111001011011101010111000001101111011011100011111101101011000100001111101001"
                    "01001001100010001100011111110001110000101100101001010010001010010101110111011111011100000100011011111001111001110110000110000101011"
                    "00100100111100100010001110101011101010001011011110110001100000110010000010100010100110100100111110111001110001100000110111101010100"
                    "01011001010010101111111010000100110000111000011001100111010101111110011101100011010000100011101101010001101111001100010100111011111"
                    "00000110100101111000011110111001001111101001100000001101001101101010000000110111001101010110100000111111101111001011100000010010001"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "00010001111000001001010101001011001100010011011110101010111011101010001010001000100111101100101110111010000110100001000101111100101"
                    "11000000111111110111010110110110011001111100111011010111010010101100100000001111010100001010000011101010111111110111001110001101011"
                    "00010111001101000010010100010101001011100101000010011000100010101011101010110100101101111000001100100111111101111000011101100111000"
                    "11101100100010000101010011011101110110110000100111100000001001000101101110011001111000000111010101001111101100010111001001010000011"
                    "00001100100011000001100101011111100101110001010100011100100110001001111101011000001101010000101000100111110100111010001101100100100"
                    "01100111110100011101010010110000011010110001111011010110011010100111001101101001011101001000000001110001010001000110100001101010010"
                    "00100000001100011011000001111010000110011001001100111110101110111000100000110011001101010100110100011000000110111011111100111010000"
                    "01010000101101010101110101101101110010001000000101010001011100101110101000000010111101000110000011100111101001110101110111111000010"
                    "10110110101101011011001101001000000011000000010010010100101000011010110111011000001001101101011110001000010000100001011101000111001"
                    "01001011100011001110101011100111111001111110010101001111111011100100010111111000011110101011011101110010100011000101001110000001011"
                    "10011001111000000000001111011101000111011111110000010110000111111001001011101100001010110000110010100001000001100010000000001101100"
                    "01111111110110110110111011000110110111010000000101000111011111000101001011111010011101110011100111001110011100110111110101111001111"
                    "00000010101110011001001111000100001011110001010000001011101010011010100110000100001011101101101100111010011110111011101001001010000"
                    "01000001101111101101100110000100010111000001101001011011011110010100001001000100010101001001000111101111101011100100011001100111110"
                    "00011110000110100011011011001100100110011111011010111001001010100010101101001000101000001010101110101100111010000000101110011010100"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10001110011000100010010001101100000110110000101100111001100100110001111111110011000111011101111010011110011111001011001000010000001"
                    "11000000010111110110000011011100011110000110010111111111111001011111010111010110011110011000101101110011011101001100011001000000110"
                    "00111011101000001010000010100010100001111010110000110110101011110000001000011111101110100010111010110101101101100010010110100000000"
                    "11000110110101110101111000000101011001101100101011100000010001000111111111111110110110001101111101100111101101101100010011001101111"
                    "10101111001011100011010011000110000101100011111000001000111110011000000011011100001100011001111100101110010110100000101010101110100"
                    "01111100001011001111100010011101110111101100000001110001101000000100100110000001011101101010111101101000110001111110000001110101010"
                    "00001100111011011001110001010001100010110011010010001111000110100001111110001110000110101011000010001000001111001001101011001000000"
                    "01110110101101011100010100001001110110111001011101011101010111000111110011001011011010110010011011110111000100011111101010101100010"
                    "00110110110101010011001000111101001110101111000010100111111110110000010100001011101011110100011000001100010111111011010100000001001"
                    "01100000111100110110110010101010110011101101010101001111111110011100111000001110111000111101011101001101011000001101001110011101110"
                    "00010011010001100010010000001110000001001011001000111111000111000011101010000011001101001010010000011010101000000001010001000010000"
                    "11011000101000110111001100011101111000011000011001100111011010110110101101011011010000001111101001110100110010111110100000011000010"
                    "00011110000110001001000010101000100100110111010010000100001111100000001111010010100010110011001100100010000100011001010101100000100"
                    "01011101100100110111011100110000011100100101011001010000111110101110100110010001110110000111000011010000101010001111110011011001110"
                    "00111101100111011000010100100110100011000110000000010010100001101000001111010100100110010010011000101010110100110010111001110100101"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "00111000001111011001000100110111100100110001000110001011000101010001001100111100101101000011111100111101000100101001010110101011101"
                    "01011111010111010110011110110010111110101001000011011110011110010100100101000110010110010110101001001010000011011100101110011010111"
                    "00001000010011010001000110010011000010111100000100001001101001110001010101001111001010100001101100000001010011001000100101100100001"
                    "01101010100101111100001001001000111010111111001111100000110001101111001001000100010010001010001011000101010010011111000101000011011"
                    "00000011010001101000111111100100001001100111011100000110101011111011000100001110100110011001001100110010001010111000011010101000100"
                    "11010101010100001110111111011001011010100000100001010100110101010101011110011011111011010100110111001000011011100110000110110011010"
                    "00000101001101101010100100111011101111101101100110101010010011000011011011110011001100101101000000101000000010110011001111010100101"
                    "11110110001100110111101101010110010100011001001111001001001010001110010010100000011011010010100001110011110101101111111001010111111"
                    "00110001011100010011111000001001100110011101011100111010001111010000000011110011101110010100111100110010111101001010111101001110100"
                    "01101001000110001110111111010101110010101011100111011100101111111111111110010000110110000010011111111000011010100110101010100010111"
                    "00111011111011000001100101100100001101011101011010001000101100000000000101000001001110101111000110111111110110000010001110101000001"
                    "11010010101110010111101110011111110011001100100101000010011101111111110101101111111000101000010001010110001110100101101010111000010"
                    "00001011001111111010000010001001001110111000000110001001001101000000010101011010001011011110001100001101100100011011111010101101000"
                    "11000011000000101100000010010001110001101010111001101011111101011111010110111111111001100001100111000000111011001111101110001101110"
                    "10101011010001000010001110011110100001110000001110110000101101010001010100000100001111011001111010000110000101100001001000111111000"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10000001101001111011010001101101000110011100001100110111111101010001010111111001100110010110000100111101111011101011111100000000000"
                    "01100010100010111111110001011100110011010001010011011001010101011111010100111001111000011100111101111101011101010111001000000111010"
                    "10001110101111110001001100101101100010101101100010111110000101000000010111101110000010111100101110100110011001101010111101011001100"
                    "11101000101001111101011101100011110101111011000111011100111101111111110101101100010010010011001011100010111010100110101110000110111"
                    "00011111000101111010101101100110101010101111111010101000110100000000000101011100100111111000010010011111011101011001011111101101100"
                    "01001110110110000111110101110101110001011110111111011110110111111111111110000001010000000110110011000011111111001110101101110100011"
                    "10000001101010010011110100000101000010110100110100110000110010010001011000100011100101100010010110000001110010101010010101001001101"
                    "11001101011000110101110001111010111101101010100111001000000100011110111100010001110001110110000111000100111001110111000100001101110"
                    "10010000001010100000100110001010000001010010101010010000111101100010010010100110001100011011101010011100110111000011010111100101000"
                    "01001101110110000101100001001111010110010100111111101110100001100101000101011101011001101110100011100100100110010100011110110110110"
                    "10111001110000110011100100001010001001011111111010010101011001111011000010010011000011001111111010011111011000110000001001111110100"
                    "01010010101010011110101111101100110100001110110111100010001111010100010011111000010110010100011001110110111000011110101101000010010"
                    "10101001111100001000011101000001000011001011010010111011100000101001000000101101100101011100111010101110001010111010011100000011001"
                    "11010111100100000111010000000100011011101010001101011001010100000100101000111001011110101110001111111001111001111111011100101001011"
                    "10001001111001001011100001100101000001100011010000100001000111110001001111100000001000111101010100011010101010011011110101110110100"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "00100101110111111001101000000010100111110001011010010011110100011010000010010100101111011111110110001100110100011010101100000010100"
                    "01001101110010000100000101001100010001000101010011101000000100000100100110100111111101010100100001010001000011000111110110001111011"
                    "10001001010001101010010110011111100010001000010100010101100001100011000110011000100101111100100010001010110110010001111001000110000"
                    "11100111010001110110100001001111010111001001110111001101100001001111010110110011011000011100101001000001010101100100000010111011011"
                    "10010100010000000001111110100111101111000000011100100100000101011001001101101010101101101100011010101000101101110000111101101000001"
                    "11011100101111010111010100100101110010100100100101001011110110000111110011110010110001111101101001110001101010100110100101110100010"
                    "00110011101011000000110000010110101001111000110000111001110111110001110101110001000000011111100010110011111111100010011001010100100"
                    "11001011110000000101011010000001011010000010011001100000001001011110000000010001010000101000110001110110000001110111001000101010111"
                    "00011100000000110001101011111110100000010001101110001011000110100011011101000100000101101011011100111000001010100011101111010101001"
                    "01010001010010011100101101001001110110100011111011100000001111010100001100010000110001011100101101110100110011111110010010000101110"
                    "10000001010011100010000000111111100010010000100010111011110010101000101100000101100100010011010010000101000111001010101101001111101"
                    "01110011110111111110011110000010111100100011010101111100100100011110100100011001011100101100011111110011101101010111111111101100110"
                    "00100101011010001011010000100110000110101010110110110110001101000000000100011000001010001000010010101111000100011011100001111000101"
                    "11100110011100011100101010011100011011010000011111100111101100010100000011010000010100100000001011111101001100111110000110100101011"
                    "10010100001110110000000111101110001001001101111110010100100100101011011010001111001000101011000110011001011111101011110110000000100"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10111000010101100001100011100000000100000100101000000111111011100000111011101101100000011111111000011011101010100001111001011010101"
                    "01100100010101101110101010001011011011011100111011001000000100010110111001010000110011010000101011000101111000010100111001101001011"
                    "10001110010010010011011100101001000011000110100010110111001000101011010001110001000001100101101100000000101111001011011100111111000"
                    "01000101001011111111111101011111111001000011100011010000110011101110111110000001111101001100110101101001010000000101101010010100111"
                    "00111010101100100011110010101001101000110110101110011000111011101000111000110110001101000001010100000011100110110010000100101111101"
                    "11111011101000100111000000011000110110111111110011011100110111110101101000010011111000110000011001010101100011110111011101000101110"
                    "10001110101010101001011000000100001101010101111010000111110110101000111000010010101001010010001100111111000001010010100111111000100"
                    "11100111011000100100001000011010011001110000000001111001101010001111111111000010110001000101000001011010011000111101010000101101111"
                    "00001011101001000001100010010001001110101010010010011100111000001001110101010101101110010001100010110101001000010000101110010111000"
                    "11011101100000111111001001111001010001110001100111111000100101101110101010101110011001011011000111000011011010111111101011011110111"
                    "10010100110100100010001111000110001110000001101010000000101011001001011101111111101001000000000010111100011000110001101000011110101"
                    "11101100000100111100101100101100111010011110111111010100101101010111001101001100111110000000111111011011000101001111011011100110111"
                    "10101001100001010011101100011100101001111010011000000110110001011000001000000101001111111001101010011110111000111011101000101110101"
                    "01001010100101101101010100000001010000011001101111000001000011101110000011111000011110000001000001111101111111111111101110100100011"
                    "10101101000110101010100000000001000111110111111010011000111001011000101101101101000011000101011100010010000000110011100101001000101"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10011011001010011011111010010110100001000101010110001110001011111000110110010001000110001100111000010001100101110001000111100011101"
                    "11100100101011001110001010000011010110011000010111110000001000011101100110111010111011000110000001100111110001000100110100001000110"
                    "10101001001011011000111000110010001010011101110000110110010000010000011111000000000010100001010100111001011111011010001001011011101"
                    "01100000001011001101101000101111111011001010011101011110011001011100110000001010011000010000010111111001111110101101001101110110110"
                    "10000011011100100001000010111111101011010011010010011111011010010001000001000001101000101000111010111100110000110011011010100000100"
                    "11001001000110111111000011001101110110101101000111000011001000010100100011001100110000100110010111000001000000010101011111000011111"
                    "10101010101001111010010101110100001100110100110000001010101010010000110011101001001001110111111010100100100001010001111001010101001"
                    "11110000111000111111110010110001011000010001111101101100110100001101000110011101011000000001000111011011101110000101010000100010010"
                    "10110001100000011010111110000101100101000000110000010110101100011001110001101000101001101001010000010010111000100000111010100010001"
                    "11110010110100011101100100111100010111011100001111011101101100000111011110011111111001000010111111101100111111110101110000101001010"
                    "00010111010101110011011101100100101011000101001000111100101110111000101001111110101111000010011110010111011110000011100010011001100"
                    "01000100010011111110101010011101110011010101110001001100110111100101001111010001111000111011011101111001001011111101101111100101011"
                    "00011000000101000011011001001011100101101100001110101000010111001011101011001100100010001000011110010010011010011010001101000101001"
                    "11001101000110000101110000001101110010010111000111001111110111011101100110011000010110000101011001011001110110010110100111100010011"
                    "00110011100010101000010110010101100101101100000110100010100010111011101100111001101100111101011100001101010111110000101110101001001"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10111010011101110010010111100011101001001011100010101101110000011000110101000011100000011000101000101010001110100000000100101100001"
                },
        /* 34*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 6, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 23, 23, 1, "Full 2 layers example",
                    "00000100110001011110010"
                    "01111011110100100101111"
                    "00001011010000010011001"
                    "00100010100111000001110"
                    "11011100001000000011000"
                    "00001111111111111110101"
                    "10101100000000000101011"
                    "00111101111111110111111"
                    "01101101000000010100101"
                    "01110101011111010110001"
                    "00110101010001010100110"
                    "01010101010101010101010"
                    "11111101010001010110111"
                    "00100101011111010101101"
                    "01110101000000010111101"
                    "11000101111111110100000"
                    "01010100000000000100110"
                    "00110111111111111110111"
                    "00110011101001010001110"
                    "10110101100101100001001"
                    "01011101000010010010001"
                    "11001100111110110000000"
                    "00011010100010111001011"
                },
        /* 35*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 7, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEF", -1, 0, 27, 27, 1, "Full 3 layers example",
                    "001011111011101010010010000"
                    "011111001111111001111010110"
                    "001111101101101100001011101"
                    "000111010111111110001101000"
                    "110110011001101010110001111"
                    "000101101010111110111000100"
                    "101010110001000000001011000"
                    "000110111111111111111111010"
                    "010000010000000000010100000"
                    "010000110111111111011001011"
                    "000000110100000001010010101"
                    "110100110101111101010010110"
                    "000110110101000101011011010"
                    "010101010101010101010101010"
                    "010100010101000101011100011"
                    "111100110101111101010001010"
                    "010001110100000001010101101"
                    "000100010111111111011111110"
                    "000000110000000000011011000"
                    "101100011111111111111111111"
                    "010101000110000010100001111"
                    "011011100110110000101110010"
                    "010100100000000000010000110"
                    "000010001010110110001101111"
                    "101110000100101100101000001"
                    "110011110110011010110100110"
                    "101010010111000001000111010"
                },
        /* 36*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 8, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNO", -1, 0, 31, 31, 1, "Full 4 layers example",
                    "0011101110100110101001010110000"
                    "0110000101110011101111001100111"
                    "0000011000110010000001101101001"
                    "0000001011011011101101001001100"
                    "1110010001100000000001110010100"
                    "0011000011010111111111101010010"
                    "1010011101100110010010100000111"
                    "0010000010100111010110001111110"
                    "0101011111000110000000111001000"
                    "0111110111111111111111101101111"
                    "0011011011000000000001011111100"
                    "1101110111011111111101100010110"
                    "0001101001010000000101110101010"
                    "0100001101010111110101000100100"
                    "1101100001010100010101011001001"
                    "0101010101010101010101010101010"
                    "0100001001010100010101110011000"
                    "0011110111010111110101011001111"
                    "0001011011010000000101010010000"
                    "1001110101011111111101110111000"
                    "0111100111000000000001111101110"
                    "0101000001111111111111110011100"
                    "0110100100101100000010011001011"
                    "0001111100111001110001110100001"
                    "1011000010001110101000011000010"
                    "1100010011010111001000010010010"
                    "0111011000111100110110011000111"
                    "1000111101100011010111010010010"
                    "0001111001001110001001100111001"
                    "1111011001010111010011101111110"
                    "1001011100001000011100011001100"
                },
        /* 37*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 9, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 37, 37, 1, "5 layers example",
                    "0010010100110011001011100010000111101"
                    "0101111010111110110100101101010011001"
                    "1010101010101010101010101010101010101"
                    "0001001001000101010011001101011011010"
                    "0011101000110101001111010000001100110"
                    "1101110001001110100000000100100100011"
                    "0011111110001101101110101010000111100"
                    "1001101001001001100100011011010100001"
                    "0011101111010010101101011010101010110"
                    "0100000100110001010001101101000010011"
                    "0111111000100111111111110000101010101"
                    "0001001100111001000000000110001010000"
                    "1110100111011111111111111110101011110"
                    "0000110010111000000000001100101000010"
                    "0110110010001011111111101010000100110"
                    "1100111110001010000000101000011111001"
                    "0110010100101010111110101011011011100"
                    "0001000100101010100010101000101100000"
                    "1010101010101010101010101010101010101"
                    "0001010101101010100010101001001011010"
                    "1011011000101010111110101011111101111"
                    "0101000110001010000000101100101011010"
                    "0110100111111011111111101110110100100"
                    "0100101110001000000000001110010001011"
                    "0011000111101111111111111111101101100"
                    "1001110101100010000100100011111010010"
                    "1111011001101110001110011101111010110"
                    "0100101111001010110011000101110111000"
                    "1010010110011001011001001101100111101"
                    "0000001100011000010110011000001101000"
                    "1110010010110101111001110110100101111"
                    "0100100011100010100010110111000100000"
                    "0111111101000100101011001011111000100"
                    "1100001100101101000100111000110110010"
                    "1010101010101010101010101010101010101"
                    "0101001010110100110101111101011110000"
                    "0111100001000111001011001100101001111"
                },
        /* 38*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 12, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 49, 49, 1, "8 layers example",
                    "0001000111011100100000001101000011110011100000101"
                    "0110100001000100011100000000110110101100010111110"
                    "0000011110010100101100001010000010000100110110111"
                    "0010100100100011101001100011101110100000001100111"
                    "1101110011111100000010101100111100100000101101011"
                    "0000101100100011001001000001100111010011010110101"
                    "1010000011100101011110011101101101010000100001110"
                    "0010001100111110101001000110100111001101011101110"
                    "1010101010101010101010101010101010101010101010101"
                    "0110001000111011110001110011101110001010001110111"
                    "0111011011101100000011101100110100100001110010110"
                    "0010101101101011110010100101110101110000001001001"
                    "1110111011000011001011011100011100110110100000010"
                    "0001001001100011000110100100000011100110010101100"
                    "0111010011110000000100011010101101010101111000011"
                    "1111101000111011000011110100001011011110000010011"
                    "0101101011101100110100101101111110001100111110010"
                    "0011110101011011111001110000000100000100001101010"
                    "0010100111011111011111111111111100100110100001011"
                    "1011110000101110001000000000001110100111011101101"
                    "0111111111110000111011111111101010011001101110110"
                    "0100110101101001011010000000101010110100011011010"
                    "0111010111000111001010111110101000110111110011110"
                    "0000010000100101101010100010101010110010001011101"
                    "1010101010101010101010101010101010101010101010101"
                    "1000110000111010011010100010101011100100010010101"
                    "1101000110010010111010111110101001100111101100011"
                    "0111001100100011001010000000101010111010001100100"
                    "1010100110000111111011111111101000000000110001110"
                    "0001100000100111001000000000001100101001001001110"
                    "1101011111000000101111111111111111011011101010101"
                    "0100110001000011100000110000010010100110010010010"
                    "0101111010111100010000001100100000101101111011100"
                    "1111111100101100010000010001101110000001010111110"
                    "0010100010100110111100011011110111101011110110000"
                    "1101100101100001111101000011010111011101001000101"
                    "1100101111001010110100001110010010111000101100111"
                    "1001111000101110001011010010000110011111010101011"
                    "0001010010010001101011101001100111100100100001100"
                    "0100110000100100010010110011010011110110010110111"
                    "1010101010101010101010101010101010101010101010101"
                    "0000111101100010110011110010010010110010000110110"
                    "0101001110100101001010111000010110011100101111010"
                    "1011111101011011100000000101100101100001000111111"
                    "0100111010000100000101011110011011011000110111000"
                    "0100110000101001100111000101110010010101000010001"
                    "0001011010100111000000011110001110011101100100110"
                    "1001110101111010111101010001000110101110000111011"
                    "1110001110011001010011001001010000100100101000001"
                },
        /* 39*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 14, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 57, 57, 1, "10 layers example",
                    "001011000011100111111010110111010001110110001110011100010"
                    "011110001010001111111111000000100000100100110001001011111"
                    "000101001001111111010111010010011011111011101011010110010"
                    "001101001101010110010000101100001011010000100010101001010"
                    "110001110000100110110111101011101101110111111011110011111"
                    "001000001010001001111110010100110111010100100001000011101"
                    "100001100100100100110111010110110100110010011100001101101"
                    "001101001011000011101110000100000100000010010010010011111"
                    "011010010000100000010101010111100000101011111001010001101"
                    "010101110001000111000100011100100000001010100111111111101"
                    "001000010011100111010010111111101001000111011011001010010"
                    "110110010100001100010010111100010100000100110010111111110"
                    "101010101010101010101010101010101010101010101010101010101"
                    "000011000011011100011001111001000100110110100100000101111"
                    "010001011111111010000110010111100100011000111001000010011"
                    "111110001100011000101110011000010001010000100000110100000"
                    "011101100010110100110111100011100101110011001100011010100"
                    "001111001101010010010000110100011110110011000001001010011"
                    "000000100001101001111001110110100111101010011010001101110"
                    "100010010100001011110100111000010101011011100010101001101"
                    "010000111011111110010010000110100100010110001101011100010"
                    "010101001000001101101110100100000001011011100000101100100"
                    "010001101110111011011111111111111111100111001110100011100"
                    "000111111110010000100010000000000010111001110001101111000"
                    "101110110001111001000110111111111011110001101101000000000"
                    "110000011101010010110010100000001011100000100010001111001"
                    "011000110110100111011010101111101010110101011111001101111"
                    "101110101010000100001010101000101010110000100111110010101"
                    "101010101010101010101010101010101010101010101010101010101"
                    "001110101111000000001110101000101011010110100000100110100"
                    "110001010000101101111010101111101010101001111111111010111"
                    "010100001011011110011110100000001010011100000011010010101"
                    "010110011010100011111010111111111010101101011101101101110"
                    "111101011000010010111010000000000011111101000001000100110"
                    "000001110011110000101011111111111111110010101110000001011"
                    "110100010110010111100001001100100100000011100101111110010"
                    "110010010101100101010010101010100110011100101011110111001"
                    "100001110011010011101111010101001101110111010010011100010"
                    "001101100101101011110101110011100101010111111101111110000"
                    "011110100011001000111101011000010101010010100100011010011"
                    "000000110100110010011000010111011101110001101010001010011"
                    "011010010000000101100101111001011001011101100110110100110"
                    "101001111101100101111011010110001101000011001101001011110"
                    "011000110011010000100110011001100010010001100000101100111"
                    "101010101010101010101010101010101010101010101010101010101"
                    "011101000001000000101010010000100101010101100110001110101"
                    "000101110010111001100111111010101010011111011001100000110"
                    "111001011110011010010100010100001100010001000101011010010"
                    "100001011011111001111111000110000001110010001101010011010"
                    "101110010110000110111100011101011110001110010101010010101"
                    "011110101000111011101001001111000010010010011010000111001"
                    "010000111011011100110010000000000010100001110010001010011"
                    "011001011001111000000000110111101001000100111000010010000"
                    "101000000111010010001110010001011111010011100001011110110"
                    "110000001000101001010101111011101111111000111011110111010"
                    "111101011110010100100011010101100011100110010111011001001"
                    "001100101001110000101000010011000100001101011001011100010"
                },
        /* 40*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 16, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 67, 67, 1, "12 layers example",
                    "0000000100001010000100101101101010101011010000001010001111010001101"
                    "0101010101010101010101010101010101010101010101010101010101010101010"
                    "0001010100101010100010110000101110111100001101110000000100111010001"
                    "0101010001000111110000111000011001010000010100011101100010001100010"
                    "0000100110000001101101111100111100011010010011001001100110010100001"
                    "0101101110100101011101011001100101111000010111111100011110001100010"
                    "0010001011011001000011001101000000100000110010111001101011100110001"
                    "0101110111011110010011010000110011100000100010100100111010010000010"
                    "0000010101010101101010100010111010101010000101101011111111000100001"
                    "1110010111100110011001000000100011110100001110101110110110011111111"
                    "0001110101110011000010101001011000101000100101001010111011101011001"
                    "1100001111100101010101101011110101001111111001100111000000100101111"
                    "0000001000110001000001110100000110111001000010011000010110100100101"
                    "0110000110101111011000101000001101101110100010101100001000010010011"
                    "0010100111001101101010011101000010001110001000100011111110000000000"
                    "0101111101000011011011000101000011011000001011101100011111110010010"
                    "1010111111101111000111110110101100110001011111100010101110100010100"
                    "0101010101010101010101010101010101010101010101010101010101010101010"
                    "0000100101011110100111010100111100110010111000001011100100110011000"
                    "0110101101111000010010001001000101001110001101010101010100000001011"
                    "1010110001110101001110001110011100111100110001011011111111110001100"
                    "0110101111111101010010011101000101000101101000110110001111001101111"
                    "0000011000010101100011101010011100010001101000000001000101010100100"
                    "0101101110111001110100011011010011111101001011010101111100101100111"
                    "1000001110011011001011001110111100010101000101001010011110000111000"
                    "0110011010101001010110110110111111101010101100110111000001000110111"
                    "0011111101101010100111010011010110000000101101011000011100010000101"
                    "0111101001000000011101011011111111111111111000111110010011100000111"
                    "0001011101010110100000110011000000000001000001000011111001011110001"
                    "1101010101010101111001110001011111111101100101100111100010100111111"
                    "1010011000000001100101111001010000000101100101011010100010101001100"
                    "0111011000110110010000001111010111110101001101111111101110100111010"
                    "1001000010001111100111111011010100010101010010101010100101110111100"
                    "0101010101010101010101010101010101010101010101010101010101010101010"
                    "0001011111111110101010010001010100010101100110001001010001011111100"
                    "1110101100000101010001001111010111110101000101111101111010011101110"
                    "0010101000010111101100110101010000000101100000010000100010111001101"
                    "0111000011001011011011001011011111111101001011010101000110110001011"
                    "1010000111010100100000010001000000000001001001111010110100100101100"
                    "0100000101111000110111110001111111111111111000011110111001000110110"
                    "1010110101011111101011100000001110001000010000010000001001111101001"
                    "1111010101100010011001101001111011011100010110011110110011010001011"
                    "1000000000100101100000110010110110111011101110100011110110010000100"
                    "0101100111100000111111100001010011000101110010100111110010010110011"
                    "0010111101110110001011101010110110101011011110001011111010100111001"
                    "0101001000111010010000101110001101110111101000110100010001101101010"
                    "0010110010010110000100010110111010100110100111100001110000011001100"
                    "1100000111010011011110001010110101110011101001101110111110001000011"
                    "0011011000010000101111110110111100010111110011111001111001101100100"
                    "0101010101010101010101010101010101010101010101010101010101010101010"
                    "0011101101101001001111001101110010010111111111011011010111011100001"
                    "0101110101011001010011011011011111111001000011101100111001101001110"
                    "1010000001101110000101100110111000001110010000011011010010100010101"
                    "1100000111101011111011001010010111010111001001011101111010110000011"
                    "1000011011100101001110001101101010110100000101111001000110110110100"
                    "0110000101001111010101000010100011010111111101001101100100011000110"
                    "0010010111010010001011011101010010000010100001001000001110001011101"
                    "0111110100111110010111011001110011111010100110011101010110111010110"
                    "1001100111110010001011110100001010110001010010110001010110010010001"
                    "1110001101100001110010100110000011101110001110010101001101000110110"
                    "0010001001101100001010101110111110011001101100101000101000000001000"
                    "0110000001011110111100001001011111111100010000011111000101111010111"
                    "1010111110100001101100101010000010011111011101010011001101101010101"
                    "1111100010001010010010100001000001111110010010011111010111010010110"
                    "0010111101010010000110101110001110001100111101100010101101001110100"
                    "0101010101010101010101010101010101010101010101010101010101010101010"
                    "0001010011000010100000100100010000011010100101110000010001110001101"
                },
        /* 41*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 17, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 71, 71, 1, "13 layers example",
                    "00001101010011011010101011001110001000011100011011001100101000001110111"
                    "01110010110000100111001011100101010101000111011001110000100101100001100"
                    "00000111000100010100111110101011100011011010001110001000101100010000011"
                    "01010101010101010101010101010101010101010101010101010101010101010101010"
                    "00100110000001101010101001010110000000010000000110001111111110011110110"
                    "11111011011100101101100110010110000101000110110000010110111101000111101"
                    "00100100011011100000100110101111110010000001001111001100101100010000001"
                    "10010100011010101101010010110110011100010111111011110000001111101101111"
                    "00101011101010011110011111000110001010001111100000101000010111110100100"
                    "01110001010111010011110110011111111100101111111001011100111100011011100"
                    "01001001100010010110100101100111110001111001011100101000100110100000111"
                    "00111011011110001101101010110101100110110111010000111101110110010111000"
                    "11100111101101001110101011000000111010010000100010000101111000001100101"
                    "00011011100101000111101010000111010100110111111101111000101001110101011"
                    "01100100100100100000010011001111011001010011001101100110001110111100101"
                    "11110010010011101001011110000011001100100010111101110000111011011111101"
                    "01000111000110000110001010111001100001001011100111000101101100101100111"
                    "00110100101011100111001111001111001110000111000111110000100010110101110"
                    "00000111110111111100110101001001001001100011101110000110011010001000110"
                    "01010101010101010101010101010101010101010101010101010101010101010101010"
                    "10000101100111000100101000001101000010110101001101100100111010001010111"
                    "01011011111000001111011101111111001101100011110110010001111010100011011"
                    "01000010010111011000001001111011001000011000100001000011001010100100110"
                    "01110011011110011011100001110010100111001011111010010011001000001111000"
                    "00100101100110111110000000010010110011011001101011000011000001011000001"
                    "10010001110001111001100001100110111100000100011111010111101101010101001"
                    "11001010010000000000000101100010100001011010000110001100101101101010110"
                    "01011000101110000111010111001100011100000100010001110011111010001011110"
                    "10100111001100111100000011001101100000000011101101000000001100001000001"
                    "00010111100101001111111110011111111111111111000100111111100111110111001"
                    "11100110100001111000100100011100000000000101100000000110010000011010000"
                    "01110010100000111011111000111101111111110110011101010000001000110111111"
                    "01100111111000100000100000110101000000010110110110001001100110111100101"
                    "11111101010100110011110111001101011111010100010111110010110100111111101"
                    "00000010000011011000111110100101010001010101100010101100011010101010001"
                    "01010101010101010101010101010101010101010101010101010101010101010101010"
                    "11101010011010111110000101111101010001010111110001101111011111100110010"
                    "11111000010111000011001010001101011111010110000110010100001001010101111"
                    "10101101110110101100001101111101000000010101110001101010110011011100010"
                    "00010001010100100011111010111101111111110101100000111101001010100111111"
                    "01001001110011110010100010011100000000000101000101100011010001001100000"
                    "00110111000011011101110110100111111111111111001110110010011010111101000"
                    "01000010111100100100011110010000110011101000011100000011000111010000100"
                    "10010110110100111001110100010010111101010010110011011011010000110101011"
                    "01001100010010011110111001010010001011010000100001100000110010010010001"
                    "01110101100000011011110001100001000100110010011101111111100111111011100"
                    "00000111000110110110011000000010010000100001111100001111000000010000111"
                    "11110100111001010111101010111011001101100011101000010110111110110111000"
                    "10100110001000100010101000110110111010110111110101101100001111001110111"
                    "10111100101000101011001010100010010101101001111110111110100100101101010"
                    "01001010000101010100100111000100011010110101111111101000110001100100101"
                    "01010101010101010101010101010101010101010101010101010101010101010101010"
                    "01101001110000100110110110101111100011010010001011101011100101001100110"
                    "01111001011010100001010111001110100110001010001010010000010111000001101"
                    "10100011101001010010001011100001001001001001110101001111110000001110110"
                    "11110000101000001011000101001101000111000001111001010101000100101001001"
                    "01101110001101111000101110100110001000010000010111101011111110100010110"
                    "01011001110010010011000001110110010110110111111010011010100000101001000"
                    "11100100101011000000111111111010100011011010000101101000100100101010001"
                    "11111000111001101001011101010101011100000111110011111000011001010011011"
                    "00001100000111101100001000101010010010000111000001001000001000101010000"
                    "01011111111000111101111111111110001100100100111000111000101100011101100"
                    "10000000010111011110110011111110001010010101010000100100001101100010110"
                    "01011000010000001101110010111000011100011100100010110101001000101111101"
                    "11101111101001111010001100010101110010001100101011101010110100000010010"
                    "01111001000010110011011101001100111101001011011010110111110011101101011"
                    "01000111110011011110000000100111100000100100010000001100011100100110111"
                    "01010101010101010101010101010101010101010101010101010101010101010101010"
                    "10100010010010011010011000100001010010000100000111000010111000111010010"
                    "10110010001101011101001110011001111101100101011010011110111110101111111"
                    "10000010100001001000010000110101001001110000100011100001100110010100001"
                },
        /* 42*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 20, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 83, 83, 1, "16 layers example",
                    "00001011100001101001010010111011000000000010110111001100101011111010100110010011011"
                    "00001100111101010101111001100010000000000101110110000101011100011010011001001000011"
                    "00000001101101111000000010100101011010101011110011000000000101010100111000110101100"
                    "00000001011011010000100001100100010011100110110001111100010100101011001101001110010"
                    "00000000001100010001111100100000001101101000111011001101101011111111010100111100001"
                    "01011111010001000100000101001101101011110110010101101000111100110110111111001000110"
                    "00111110001001101111110110110000101111111001111010001110000001101000001110111111110"
                    "00110010111000100000000111010110011100011101100000000010111101100111010111101110110"
                    "11011011101100101010111100101000011100101011000101011101101011111110000000101110111"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "00110001000101001110111100101110011110101000010110101001001001101111000100000111101"
                    "10011101011000000101011001011010000000001111011101011010011001001010111011010000001"
                    "00111100001111010001011100011111101011001001001100001100100010101101010010101000000"
                    "01111001010000111000000001010111001100010100001010111111111001110111000001100000110"
                    "01101011100101100000011100100111101100011011100101100100001000111101110100110000111"
                    "00101100111100001101101011101001000111110101011000100001010001101100010111011000000"
                    "11011101000101000011001000001000000011110010000011101010101000101010111000000000001"
                    "00011101111101011010111111101010010100111101101011001101010100101011101111110101111"
                    "01101110000001111101010010100001010110000011111101010110100000110110000000011001001"
                    "11000001110010000001100111100100111001000101101111011101011111010001001001001101110"
                    "01100110000000010011100010000111110100100000101000110000100011101001111110101001010"
                    "00001111010111011000000101110100010000011101010100001111110111011110110001111000100"
                    "00111010101011000001000110111000100100101011101100101010001101000001101000101111001"
                    "10110111010010111011110101111110100100010110000000001100010111001110011111100001111"
                    "01101101100100001111000100000111001100001001110101101100101100101100010010011110111"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "01110001101010111110111100010111000111100011010010001011000000000111010100010010101"
                    "01000101011101011111111011100111110001100101000010110011011011110110001001011011110"
                    "00000001001010111010100110100011111101101011111001001010000111001110011000000110011"
                    "10101001010110101101101011010111010010110101110011010101111010110101011111011011110"
                    "11000011001101110110001100010011111001010000011111101000001000110100001000100110111"
                    "01000101110110100100100001101101111011010100100100000111011111000010111011101101011"
                    "10111011000000000101001110100101010001000010111011001100001001100101001010001000101"
                    "00000111111101000001110111101111001000011111111010001011111011111111000101100111011"
                    "11001101100110010001111000110100011101111000000010010100100101101001111100101100011"
                    "01011110110011100111011111100111101111111111111110011110111011110101001111101111100"
                    "01110011000000010011101100101010100100000000000101110011101011111000000100010111010"
                    "11111101011100100010001101101010110101111111110110000001010110000101110011101011110"
                    "00100001001100000101010010110011111101000000010111101000000111011010000100101111001"
                    "11011100010110000010010001001111011101011111010101001101110011011001101011001001101"
                    "11101001101001001111010000100000100101010001010100111101101100010110101110001110111"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10001010101001111000110000011010010101010001010110000001000001101000100110100101001"
                    "00100110111111000010100111101100000101011111010111100000010101110010110111111011000"
                    "01101101000101001111110100101001001101000000010111110101100110001011010100000010001"
                    "00000011010001111111111101010110001101111111110110101111111101001001101101010111001"
                    "01010110001110111110111000110011111100000000000100101100000000000100011100010110001"
                    "10110011111001010101010001111010100111111111111111001001110011010111000001010000010"
                    "01000010100111101000001100010111110001101001110000010101001010111000110010010010011"
                    "01100111111110101001111011111101010100010110010010001110011011111111111001100111011"
                    "00100011001101000111011100101001001001100001100101011011100011110011111000010111110"
                    "11011011110110101000101011010011110000011111010000101110010101111000100001110110010"
                    "10010010101100000111011110000000100001001000100001101101000110111110100010110111110"
                    "10101001111111001000010001101100110000110101100010110111110110100110010111011100001"
                    "01000001000111010001111110111111111000100010010010111100100101101101000000010100101"
                    "01111110011010101101000101101100000001011110000001011111111110000111010101110100111"
                    "01110010101100000101000110010101100011111000100011111111100101100111111010110110011"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10000100000010001111001100010111111110010000110011111111001101000010101000111001001"
                    "11000000111010001001010011010101001001000110000111000001011011110011010011101010100"
                    "01101001001101001110011000011110010000101011110100101100001100101101000110000111111"
                    "01010001111101101001110011000111110101111111100111000001010011111010001001011010001"
                    "11010010101100011011111000000111001110101011101000101001001001011111010000000101001"
                    "11010001010011100100101101111000110010110101010011001101111111010011011101001101101"
                    "00001011001000000110010010110001101100111011001100011000000100111101010010011111101"
                    "01011011010110000101011001010111010100111101011100010001111001100101001011011000111"
                    "10000111100010000100110010011101010001010010111100101001001001110000101010001011110"
                    "01110010110000111011111011001101000001100101000111001001011010010101110111111000110"
                    "11101100100011010010011000010101000001110010000000000011001010001101001100011110111"
                    "01111011010111101010000111100110011001110100001110010011010010000100011101001001010"
                    "01110010000100001001111000111000010100000011100110110110001110010010110110110000010"
                    "10000011111001001010110011111011010110100110010110000101111100110100101101100011011"
                    "11010111100101001010100000100100111101101010000011111011000001000101000000001000010"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "00101011001111111000100010100110010110011001101010011100101000100000110110010100001"
                    "01100010110000110001111001101000010101111111001011110110111001000011110001111000010"
                    "00111101101110011011001110101000110011001011010100101110000011011011011000100010101"
                    "00000011010101100010010101100000100010100101011010110000110101010001011011110100110"
                    "11101001100011110111001010010010110100111011111000001010100100110010111110011111011"
                    "00001111110100011001011111110000110111011100110000110010010111111111110001110101100"
                    "10000100101110100001110110110100010111011001010001001011101111100110111100010011011"
                    "01101011110001110011001111101100101011010101110111110101111101011001011101100001111"
                    "00001001000010000110101000101110000100011010001100110010100011011111011100001101110"
                },
        /* 43*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 23, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 95, 95, 1, "19 layers example",
                    "00010001011000001001011100000100010100011110001000101101010001101011000110101100111011100100000"
                    "00111000100000010000111101010111001010100110100100101001100010111101100100110001001101001001000"
                    "00110000001000100010001011100100111100110000000000111101000101101101011010001100100111011100010"
                    "01000100100101111001001010000001100000000101010101110011011001011010010100011101001001000011000"
                    "00101111101010001000101101000010011110001100011000111111010100000111001010110110110101101101010"
                    "00111111010111010011111101110101100100110110001101101100101100011011100100010011000100111001010"
                    "11101010001110000010010101101110001111100000010001011101000000101110000000001000000111001110101"
                    "00100011110001011110011110101101000010100100010100010111110100011100011111101101110111110101110"
                    "10001011010111101011011111001110110001111011000010000001111000100101111010011100011110110110001"
                    "00100000101111111110100011110111110110001110001111101101011100110000101000110111100010000110110"
                    "01100110110110101010111001100110101000001100000011111100010010001101101100010010011110100101000"
                    "01100010011010110110011110011011111101001000101100001110011111010011101000100101100101110111101"
                    "00001111111110100100100001100000001101100100101011010000001100100000000011111100010100100110100"
                    "11000101101001011011100110011111001101001001000111000101010100010011001000001101110000111010110"
                    "00011000111010001000000000101110111001011011100011110001101100100001111100011010000010000011100"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "01011010011001000111000110001100110100010000101010100100111100100011100110000100111101001011101"
                    "11011011000111011011010011011011110010100111000110010010000110111011000000000111011001101110010"
                    "01110000011101101111111010011110011001010001101001010010110101100101100101010100100000111100100"
                    "00110001000001011011111101101101010100011111111111010110110011110001001111101101111011000101101"
                    "00011010010000100011001110111010111000100000001000100110001111100110111100100010000011101001110"
                    "10010110011011110010010101010101011111100000011101001000010011110101110101101011000100010010011"
                    "01100000110110000010000011110110110011111000000000010000000111000010111001111010001101010101101"
                    "01001010010110011010010011101111100101101101010111100111101110110011000000101101001000001110110"
                    "01001010011011100101000110110100011101010010010000100001110110000011001110011000000101011010010"
                    "00011001000011111010010100011111000000000001010100000001001101111011010011011001010101101110100"
                    "10010011100101100001101111011100011100001011110000010011101010000110110001010110101000010001000"
                    "11000010110010111010100000001001101001110000001101011110001101110101101011110001100010010011111"
                    "01011010000011000011000100111100010110110001111001101111101110000000011010101100011111010110101"
                    "10000001011000011001101011100011101100111011000100110001000101011111100111101101010111110111000"
                    "00110000010000101100001100000110111011001001001010111111011110100110110110101010101100110110000"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "11010111001000000101101001011100001001101101010000001000110100001011000101100000101100111111000"
                    "01110111000111010011011111011101001011111110101100000110001000111001000101111001000101101001001"
                    "01100110101010000001010011010010001011111111000000111010001011100110000010000110010111100111111"
                    "11100010100101110110001011000111101110100001011101101100101001110100100110010101101001111011000"
                    "00101000011100101100011011000110111010111110011001101111010110100101101111111110110110000011110"
                    "11110000110000011010000000001001111111011011110111111001011100110001101010100111110110101000011"
                    "11010101111011100101010000110010100001011011000010101111001000100010111111011000001101000011001"
                    "10110001111101010011111000010011100001100010101101110010100001110011001111011001101101111100100"
                    "00111001100101001100010001001110000011011110010000000011101110101000100100101010010101010010010"
                    "01110001111100111000100111110011001111101111111111111111100010110010111111101111000101011001010"
                    "00011011010000101000111001110100010110010100000000000101011110001000101001001110000010011011001"
                    "01111010111000010100101010011011111100010101111111110111110010011110001000111011010001111010011"
                    "10101110000010100000101011001010100110100101000000010111001111001001100011100010101000000000000"
                    "01001101110011110110001110110111101010101101011111010101111000011000110000110001010100011101100"
                    "01011111110001000010110011100110111101010101010001010101111000000100010010100010011000000100111"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "00000010101000100011000011010010000101100101010001010110110010000101100100111010011001101110010"
                    "11100010100011011000010011011011001100101101011111010111110101011011111110011011101100000100000"
                    "10010101010100000101011101011010000110010101000000010111001100000110100010000100000111100011001"
                    "10001110100011011100001111001011101100011101111111110111110101010001001001011101000110101000001"
                    "01011111101100101110111100010110110001010100000000000101011010000101101001011110010101100100111"
                    "01111000000011010010111111110011101110000111111111111111001011111111100110100111110101100000111"
                    "01011111000011101101011100001110111011010010001000001001100110000001001010011000010011011100100"
                    "10111010000000011110100110101101100111110001111100110000100010111111111111110111101011011011010"
                    "11000110000000101110011100000100001101000011101011011010000011101100011101011100110000100110111"
                    "01010111011001010011010011001001110000010100000110001001000001110011011001111111111011000010110"
                    "01000000100101100001100110101000101110111001101001010001010001100110100000000100111111111101101"
                    "11110111110000011001100011100111001001010010010101001011100011110001011010110111011011110000101"
                    "11110010001001000001110100000000011010110001100000111001111010000001111011010100010000111001010"
                    "00000111111001110100101001000001100000110111111110010111010000010110110000111101101100000111001"
                    "01100101110110101111001110110000011101011000011000011011000000000101011000010100001010010011010"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "10100001000100001111001010110010010001111001001000101000111001101111110100011110111110100111111"
                    "01100110111001111110100110111111010011110000100101011011101011011100111001101101011010001111001"
                    "11010000111000000010001001010010001110101011100000100100100111000011010000000000110111101100000"
                    "01001110110011011000000011100111011001000010110100101001011110011011111111111101001111010111111"
                    "01110100111010101011111111100110110010000110110001111010111001101011100111110010010101100111101"
                    "10000101000110111010010110101111100100111001100101100110100110110001000011011111100001000101111"
                    "11001100110001001101100000101000010001100001000011000111000110100101100110010000011101011011110"
                    "00110110010010010101101011100011010011010010101111110101001111111001100100010111100010101101110"
                    "01010010011100000100001000011010100001110001011010011111011010001110010100001010000001111111010"
                    "00110110101001010111001111000101111100100111011100011010100011110101011000100011011110100110001"
                    "00111100001001100101101001010010111001001000101010100101000110100010111010001000001011111110000"
                    "11010011100001111110011111100011010101111001110111011101111010110001000100001011100010101101100"
                    "00011011101100101011100110010010000000111110100010010111110110001100101100001000110101101101011"
                    "10100010010001010101110110000001010001111000110110010111110111010101011000111111111100100001000"
                    "00010010001111000011001100110100001100110010111011100101100110000011011101010000011011010000001"
                    "01010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010"
                    "01100000010110001101101110100010101101000000110011011110001101001010000011100000001111110101101"
                    "01110001010111010111111110111101110001101011111101001010101001010101101100100101111101100101000"
                    "00000001010101101110101101000110000011111100111011101010000111100100000011101000001001100011100"
                    "11101010010110010110001010100101101000011001111110001001000101111000100011001011110111010110000"
                    "00011001011111001111011100100000100111000111111001100011001111100010001010000110111011011100110"
                    "01000110101001111011010101001011011111011101001100110001001000010101111011010111001110010101100"
                    "11100001111001100100011000110000011111101110101000111000111000101100001011000010001011000010000"
                    "01101000001000111101110010101101011110011101110110011110101101111001111110111011101001111011101"
                    "00111100110101100100101111000010111011101111101000001000000001101110000011110100010100001001101"
                    "00110111011110010010110101011101010011110000101101111100010011010111110011101011001100100100000"
                    "10010000100010101001110111000100110101101011010011000110011000101000010010110100000111100010001"
                    "01000011010111010110000110110101011011011010000101010010011100110100100100010111000100000100111"
                    "01100100000110001010101110110010101010010010111011110001000101101101110000110010111000000101000"
                    "10011001111011010101011010011101111110101111010101011110010010111111000001000011100100110011001"
                    "00110101001011100000100011100010100110010100111000001111111101000000001100011000110110100110000"
                },
        /* 44*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 24, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 101, 101, 1, "20 layers example",
                    "00100011001001111011101000010101101000001111011011100001010111001110100001111011101010011110100110110"
                    "01001011101010010001000100010011010011001011100001000010011001000001100110100110000010001111010101011"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "00011101001110011000001000011100000111111011100011011000101010111101001110101000000011011011110001001"
                    "00110111010001010011110011111010101101000010101011110101001010101111101001000101011101001111011000100"
                    "11001010100111011100111011110011110001010100111110011110111100001101011011001110000100101011011011000"
                    "00110100001010001111000000000101101111111001110100111110000110010010010011011000101011001011100110100"
                    "10000110100100110101111010110111000100110001100001000001101110111001001101010010000110101111110110010"
                    "00100011010001010111111111100010101100000001111010101000101111110110100011011111101000001100110001100"
                    "01000110010011000000111011000010100100000001010111000111111010110000011001001010000010011100101001010"
                    "01100011010010000010010101111011011000011100110111101001001010000011011110101011011111001000011000111"
                    "00010000111110010000001101100011010101111110110100010100011110101100110111101111110011100000011110000"
                    "11111100100111001110001101010111011100101010100001110010101011101010110110011111001000001100111101101"
                    "00011100100001110000011111100100100101101001010101001001001100100001111100000110000110110110101101010"
                    "01111001011110101111000110100111001110000011100110101000111111111111011000101001011101011101000100110"
                    "11001000000111000101110111100111010101011010100001011110100001011000011010001101100010001000011010010"
                    "01111110010110100111101101011001011011100010110101110011001110000110011101111001001010111000101010110"
                    "00001101111011011101010000010110010111000000100100001110010101110101100001101111000000011000101010010"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "00010100101100011101111110100010100110101101011111001110100111100101101100010100000110111101000110011"
                    "10110000011000101111000110011001101010010011001110110110000110001111100101001101111101011111010101111"
                    "01001111101010011001101000100000000101110000000110001111011111000101110100111011010000011001111011011"
                    "01101110111000111010111010011000011000011110011001101101110011000111001110100010111010011011110110100"
                    "01011100100011000101110000001001100110100100010011011111101100001100100110110100010100110011000111010"
                    "00101001110100011010101001100110101100010001010100110001011110101011000011010101011110110111001010101"
                    "10000100100001011101111110100011110100110100111100001110010110111000101000000111000100100011000000011"
                    "11111001010111111111001000010000001011011011011110100011000010000010100101010110001100101011001110110"
                    "01010000101110101000001100110010100001100111000101000110000101000100100011001011100010100011100101001"
                    "10100110000100100111010011011000001011101110000010111001000010111110010010011011111010100100011111110"
                    "00001000100001011101111101110001100110001010000101010100111000001000010100110100000000011110000010011"
                    "11101110010011000111010101010001101010001011100111111110011111101010011001111101001100111010000000100"
                    "01011010000001001001100110100000000111001100111010011100101101101000101001011100000010000000111010011"
                    "01101000010101111110001110011010011101110111000101110001001110000111110100100001101100101011011110110"
                    "11011011100011101100001111101101110000010111010011010100111011101101110111101000010110011001011111011"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "00010100100001011000001100010010110110000100101100001111100010110000110100110010000010111111001011000"
                    "11110001000011101011010001000011111001101110011000110000011111000010101000110011101101000111000011111"
                    "11010101000010010100101111111101110111000110111100001110010000011001100010001001000000000000001001000"
                    "10101110111111110111011111110010001001111100110101111001000001000110110110000001101010100001110001110"
                    "00000101111110111101100010010011010011101110100111001001111001110000001011010100110111011001111110010"
                    "01111110110110001110110011000111001010001001001110100011000101111111011000100000001111011011111000110"
                    "00010001011011011101010001010000000010000010001101000010001001001100000100010100010000011101101110001"
                    "01101011110011010110100000111101011111101010001010111001001101000010011110000111101101001111010001101"
                    "10011000000010000100111110000001000001110111110011000000010001001101010001100000000100010010011110000"
                    "01101110010110111010010011001100101000010001111111111111111011101111101000110110111001100010000100101"
                    "01011100000011010101110001100001010110000010100000000000101101000001010001110011000001000000000011000"
                    "00110100110000010110100101001001001001001010101111111110110101110011001010101110001011000011000111101"
                    "11001001011101001000101011110001110110101001101000000010110101010000111100010010100100000010110001000"
                    "10101001011101010110001001010101011011100100101011111010101011001111111111001100001111111010101101100"
                    "10001010101011010100101010000000010110110001101010001010100001100101111001111110000100111111101110011"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01010000110011111100010011010101100111110100101010001010111011111001010100110011110101111100110000010"
                    "01101001100001110110010011011000001110000001101011111010111110000010101101101100111001010100111100110"
                    "01000100000111101101110000110111010110110011101000000010110001101000011100101001100011100010111011011"
                    "10110110011101100011101001001100011101010110101111111110101100001111001100111100101110101011110000101"
                    "11011100001010001000101011011111010001100010100000000000111011011001001011000101110000100110000100010"
                    "01110010000010110011000110010100111010110010111111111111110011011110101011010101011100010100010010101"
                    "01011011011010101100000110110100100011110000001110011111000001110100100000101011100010010110100001001"
                    "11101010010110110111100011100011011111011100100000101010111111111011110101010000111001000001010010100"
                    "11000100001000101001111011011010100010011101100100000011101001000101010111011101110010011000000100010"
                    "00110001011110100010111100011100001110010000111010111001000110001111111111111100101010000110101101100"
                    "01000110001010000000011110100110100101110011101110010111010111101100011110111001110011111110000000010"
                    "10101110010110000011011010000111011101100111100001110011000001100110010010010000011011100100111011110"
                    "01011110111010000100011001011101010000001110000111001101011011101100010010001111010011100100000110000"
                    "11111001000101000110111110011110011100001001110011110001010110001010011011011011111110100000111000111"
                    "01010011111000000000100111011011110000010010011110010100010110000100000011001110000101000101110111010"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01001011101111101001100011110110010011101001011100010001110101110100010100001000110000011100000101000"
                    "10110101000100110110111001001111001010011010100110110101101010010011110000000010101111010010010111101"
                    "11000111111001100001101000111101100010110111011101001010010110000101101100010010110110110000011001001"
                    "00110010100001100111101010101011111010100011010001110111110100111110100110110110001110001100110010101"
                    "01000111000110100100110000010100100101100010000010001101111001001101110110010001100110100101100001001"
                    "00111100001010011110101000011010001101101111010011110100111000011110110000001000001010011100101110111"
                    "00001111000100101100001100011101110110100100011000011010110100010001011011010001010110101000010110011"
                    "11101100000011011011001101011111011010111111011110101111000001001110101011011011111010111000100101111"
                    "00000111100100010000001101111011000001011100001010010000100010001001001010011111110000011111110010001"
                    "10101111110100110110100000001011111100001110100000111001111001111110010011110111101000000011101001100"
                    "00001010011111100101110101111110010110100000001101010100100011100100110001111010000001110111101010010"
                    "01111101100100110011101100000001111110011011011101111100101010111011100110010110001000101011010100100"
                    "01001110000000010001111010010001010111100010010001011100001011101000011100111110100010010110110000001"
                    "00110010100110010010001010011101011101011010100111111101111110110010001001001011001011001111010111110"
                    "11011010111010110100111111010111110111010110011100010000001011100101101010000011000100001000010110001"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "00001100011111001101010111100111110000011110111001001110000111010001110001001011100010011001000110010"
                    "01100011000010010110111111010010011011111111101101110111101011111010010111011011111100001110011110110"
                    "11000010100100011100101011010100010010101010111111001110100000011001011111100000010000110001011100010"
                    "01110101001111111111111010010101101101001000011001110100011101000111110101000010001101001011001000111"
                    "00010110110010010100100101101100000111000001110010011110000010110100001001001011110111011100110000001"
                    "00101010011111110010000110110100011100010001100011110110011101011111111010011111011000011111000010111"
                    "10000001101101100101100100001111010110010101010000001100000111001101001010011000000101111011101000011"
                    "01101001010101100111110010011111111100100011011111110001101010010011011000101000001000010000001101101"
                    "01001011110111111000111111011110100110100110010101000011100110000001010001000011000110100000110101010"
                    "01111101001011011011011000011001001101001111001011110011111100000111111110000101111111110010000010111"
                    "00000111000000001100011100010111100010010111110001010011100100001100010000111110100011010111101111010"
                    "10110011001101010010010001000110101001101001001011111111010011111010001110000110111000010110110110111"
                    "11001001000100110100001111011111000011111110101110000111010010001101010001001000000111010001000100000"
                    "01101000100001110110110000111100111111100101111000100000001011111110100011101000001000110000010110101"
                    "10001101110011001100111000100011000010110011101110000100101001011101001000100001010110011000100101001"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01011101100101011001001110111110100111101011010110010100101110001100000100001110000011101010010100001"
                    "01100101110000100011110001100110011010011000001110100010010101000111010001001111111100001101100010111"
                },
        /* 45*/ { BARCODE_AZTEC, UNICODE_MODE, -1, -1, -1, 30, "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ", -1, 0, 125, 125, 1, "26 layers example",
                    "00100110111101111000100011101010001011000100011001100001000110110101101111011010100110010101111010000000001001111011011101111"
                    "01000110110001010011111011000100001101000010100100110101101011001111101101110000100110101000000100001011010101000110110110011"
                    "00100000111011111011100111001111100011001111101001011011011111100001111010110111111101111111011010001000100011110110101111001"
                    "00011110101010010110000101011101100001000010010111101000110100011101011001011100101011110111110011011000000100010001101101011"
                    "11011010100001100110010110101010000010110100001100111000010100111111110111000111110110111111001111001100011111100001110011010"
                    "00010001000100001001011010000001000100011101100111100111010010000000010001000100010010101001100001110101101111000001110000111"
                    "10110111011001100011110110101111010100100110011101000111000101101111000110110110101111100101101000110100111100110010010100001"
                    "00111010010101001001011000110001011000001010100010000010010000000110100010011000000010110011000011111100001100000101000110100"
                    "01110010011100100011110000000011110000110101011010100101001011100110010001101111111001101110111010000101001011101110101011011"
                    "01110001110000001100010111110100010000010010000011000011011101011101100110101000111011110010010110111110110111001111101110000"
                    "00111011011000110100000011010011001110011110001010001101000111110000001101100111111100011001011011100001101101111000100011011"
                    "11010100111011010011101100010100001101010000110111011100111000011110111011000000011010111100110001010000010010011001101011111"
                    "00010000011111110101000001001110011011000101011001000001100000110011000110101111011000101111011100000001001110111100001101101"
                    "01100000101001010010110110110100100000100011000011110001111010000001000010001101110000110110110110001011110011000100101100010"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11110011000110010001101011000000101001100111110011111100100101011001100101001100101001010100010111100100110111011000011101010"
                    "01011111101011100111010001000111000011111010011101111000111111110001101101101111011001101000101000001011110010111100011110100"
                    "00111001110000001010010001101001000110100010010000010010101000000010111001101000100001001100100011101010000010010100000001000"
                    "00111100110111111100001001101111111100100111001000110101101001100100000110111111110110101111001101110111000000101001110000011"
                    "10010110000011010111010111100100001100011010000100001001011001010110000000100101101000010100110011000110100010000001100010111"
                    "01001000101011110111011100110011000011000001111100101000000111111101001111111110111010100111011101010011101101101010011011101"
                    "01101010010001011101100000110000111000100000010110110111011101001110000001111000011100011010000011011100110101011001010011011"
                    "01101000111011111100011001100111110101010101101000100010001010101010010000010010000101110100111000100101101110110100111010010"
                    "00001111010010011011100011101101010101010001010100101000110101001100010110011000001101010011000001110100000100011100110010101"
                    "10101010111111111001000010000011010011101111101010011100110111100100111000001011000010111101001101001010111000101001110110111"
                    "11000000010001011111010011111101000011001000100110100010100010001100010101100001100001100101010000100001001000000100000000010"
                    "01101100111010100111001000101110110110111010101101101110110010101011001101011110111001101111001000001001010010100011000010000"
                    "10000111001001000011110110001101011000000101110010011101000101010111101110100001010111011110010011100110101110000100101001011"
                    "00010100011000111100011011011011011000101100001110110010111111111000001111000011011100001101101011110001100101110111001100110"
                    "11110010001100000101110101010101001010011000010000110101000111001101100101110001100000000100010010010111000110000101011101010"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01111111111011011011000100001101001110101000000011110110011010000010011100001100000100000010110010100110000011000101010010100"
                    "01100101110011101011011101101110111110101011001111110110100010110011110001011010110011110111111001000110110110101001011001110"
                    "11011011000001011111011110011100100101001110100000100110100100010100010110110000000010110010110000011111011011011110100001100"
                    "00010000000001111101100111000110001101100110111101101100100000101011101101110110111100010000001100000000001001101110101010100"
                    "11000111101011011011000000111100010010111101000111110000111110001001101100010100001100011010100010100110110100000000011101010"
                    "11111011101111100010100010101010001111110101001001110011111101101001011000101111010110110111111001100001010000101100011110011"
                    "10000110000111000011010111101100010010000111110011000001110100000011110000100101100111001011110000011101001101011100110011111"
                    "00010001100111101011000001100110011110110100011101001010011101110100010111000110010010001000011101111000010011100101100011101"
                    "01010010011100010110000011011101100101010100000111111001111011000001111010101001101101100111010011010100101010001000110001111"
                    "00101110000010110000000010101010011001110100011100001101001111111010010000011111101011011111101011010100111010111101111001000"
                    "01100101000110001011101111010001111100001001010101001101001011011111001010001100110010101101010000110011100110000011110001100"
                    "10110010000011111001000101001111001101111110111101101010111111110010001101101010110011001001111111010011000010101110010101110"
                    "01110001110111000111101110000001011001000101010100011011111101000110111000110000111110010100000100000000100010010001000111100"
                    "01000101110110100011001010000010011111010101011100010110110110101010011001111110110010111110001011111101000010111101110011111"
                    "00000011111101011111111010110000010011110101110001111010010101001001010111111101011101101001110011111011001000001000010011011"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11111111110110000001100010101001100010101000000011101101101011010100101100101001010100001110100110101110110001000111111101001"
                    "10100101101011101100001001010111111000011001011010100110110110110111100011011111111000000101111011111001011000100000110110000"
                    "10000011001010011010001100111001111110100011010010101011010010010010000010101101011100100001110101101001000111010000100110000"
                    "01010000000001110100001111110011111111010110011101100011100001101110101101100010000010110001101101010000100001100001001010000"
                    "01001101000000001001110011010101011010110101100011101010100110001001111000011001111001011110000010001100001110011101010111101"
                    "01001010010011111010100000101011110001101111011101101110011001100011000001011111000100010001011011100011001100111101010001101"
                    "10111001010101001101001000100101000111001001110101000101111110000110100000110000000000100101000010111101000110000000100101011"
                    "11110010100100111011000101101010011010011000001011010000110110101000111100111010110011100010011010110000100111111010000010101"
                    "01111010010001001001011001000100110111010110100100101001111001000000010010110100100011100100010110001010011000011100110010111"
                    "01111100100011101110100110011010110000110010111111001011111111111111111001101011011001011110001111010101010110110101000101010"
                    "11100010111011011110101100101101101011100111010111110110100000000000101101110100000001011101010100111101101111001001011000111"
                    "11001010001011100000100010001111001000001010111111001011101111111110110001100110110101000110101110010100001111111000111100000"
                    "00111110010011011000000001110101000100100111110000110110101000000010100011000100010010000001000111011001101000000010001000101"
                    "01011000101101111000100110000011011110101111101110110101101011111010110010011010100111001010101011011110101001111101111000001"
                    "10001111000011000110100111100001001001010000100100000000101010001010101101100101000001011101010001000110101000010111111011101"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01000100110000011011101100101101000111011001110101101001101010001010110110001001000111101110000111100001100001010110000100000"
                    "11011000111110101001001010000010001110010101101000010100101011111010110000011010011001111100011101001110111000110010100110000"
                    "01101111011110000100101101111101101001010100110100101011101000000010110101010000011110000001010011111111111111010110000100011"
                    "01010110011010100011101010000011011010100110001000010101101111111110100000010010001000111101011001111010011110101100111010111"
                    "10100110000100011000110010110001110011000000000001110010100000000000111000001101111100010000110001000101011000001101000011001"
                    "11111101111111101101000111001110000100100010001111110000111111111111111101011010011010111100011101011101110001100111000110000"
                    "00000000001000011011100010001000101100011111010011101100010100010001001001000101111010111001010101100100000000000001001111111"
                    "01111010110010111000111010001110011011000111111001101100101101100011101000101110111101011010101101010010000010100110100000000"
                    "00000011001011010011011001010000101011111010000011000110001101000101111100011000001010001100000110010101110000010001010111010"
                    "00101110100111111001110011100111110101101110111010000000111101100001010111010011001010001011101001011111001111101100100010010"
                    "11100001001000001010011111100101001000101011010001100001010001000001101101111001100111000000110100001110000111000110101011110"
                    "00101101011011111011010101000110000010111100001111101000000010101110100110011010000000110111001100010001101001100000100110101"
                    "10100111110000011011111101110001001110011011100101111010100111000011101001000001111111001010010011011000000001011110100100000"
                    "00100010110010111111111101001011010011111011011000001010001010100000001100010010011001110101101000001011000010101100111011101"
                    "01101111001001011101010100100000110111110001100001100111100001000011100000110100101111001011000100111011100101010011110100100"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01000001101111001110000010100000011110111100010111110101001010001100011110000001110100011011000101011111111001010100110011100"
                    "00011011011001110111010100101011010010101001011001110110100110110111101100000111010010100101001010111110011110110111011010001"
                    "11000001000111000100101011101000011010000101010010011101111000000011010101001100011110000000000010110010001110010000101011111"
                    "00001000110001110110010001111111101001000100001010100110111101111110010111010111101010100100011000100000010010101110001110110"
                    "01001010000111000110111000011001000111110111100011100100010001000010010100111100010101101001000101000101001110001011001001001"
                    "11011011010100111001010111111110000111011011001100111011110001100000010110100011101001111010111010100000000110111001011010010"
                    "01000001010101001001110100010101110001011111000010001111001101010000101100001101111001000100010010111110100000001100101010111"
                    "00000011101100101011110101100110101010101000101001111010100111101100111011010011110110011011001011011001101100100100110000010"
                    "00010000011010001101110110101100010110011111000011100101010001001010000011100101011100101110110010101011001101001100011000110"
                    "10111100011001110010011011100010111111110011111110110111101011110011011011110010110101011010001001100001001000111001001001000"
                    "01001101111010011000100000000000111101011001010010110000111100001100001010110000100000110110110010100111110010000010000101001"
                    "01010100110101100100111111111110111001010101011100101001101111111100111011000110110011010010001110101001011110101110101000011"
                    "01100011001101000000110011100001000110101100100010101100101001001001111000010001010011000010100110110110011110000111001101010"
                    "00001001110100111111000100010110000000000001111011000001100101100001000011011010111101101001011101001101100101100111011110111"
                    "10100101010100010110111001000101101010111101000100001001010100011010101000100101101000000001000100010010011110011000010100100"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "11010111111010011101000100111100011010110100100100001010001011000011010110001001111110101011110000000001111110010110000000001"
                    "01101110000001101001011001111011111000100011011100011001111001101100101110101010000100001110101110011001101111101011000010110"
                    "10010010101001000010001011101101110001100000110111010010110001001010101000001100000010000010010110110110101111001001010110011"
                    "00101101000011111001001111011010010111010001111000111101000010110110111111010110101101111100011100011101011001111110010001110"
                    "11111111110001010111011001011101011011011101000101010110001010000100001110011001010111110111010011000001110000001111101001010"
                    "01110101001011100100011000011110111010101110101010001111101001101101000001010111000011110100111010000111111111111010001110011"
                    "01100001100011001111100111111100010011111111100000110110110100010110011100001100111000000011100011110011110110011111100000100"
                    "11101010100111101000011000000011000111111110111100011011011110111000010100100011101000010100011011001100001100111101100111000"
                    "00010011100110011001000010011100110110101010010111001001100100011101001100101100011011111111010001011010000010011001101000101"
                    "11000000011001111010100001011110101111110000101100010001100100110100010000110011111101101111111111001111101100111101001111000"
                    "11011101100011011111110111110001010101011001110010110101000100000100001000111001011001110000100000101010111100000101010000101"
                    "10001110001111110000111000100110101000110101111110101111100111110100001001010011110101101000001000000111000101110011111110011"
                    "00000100000010001011111100001000110010111101010000010100011110011001101001000100001110111101100100011010100001011101100001110"
                    "01011110011110101011101101101111000010001101001101101011000100111101010010001110110110011011011010100010110000110100101010100"
                    "00110100001101011010001101011001110100001010010110000100001001010111001110111100010110111100110000001101001101011101000111101"
                    "10101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101"
                    "01001111011101001001010110001100010111100100110001010110011001001000110110000001110001101001000100010001001010000001110000011"
                    "10101010010111100010001011101111011111101111111110010011000110100110001010000011001001011101001111100010001100111001010010001"
                    "01011001101000010010010010010000000000101011100111000111001100010110100111011101000010000000000001111011001010010110110110000"
                    "01100000110100111110010100010011111000000110011101011000110001110000011010111010001100111010111011100100011100111100000010011"
                    "00010011110111011110101100010001010011101111110100111101110001001010010110011000011000110001100100011011000100001100111101111"
                    "11010111110111100000011001111110011011011100001110010000011010111011010101101011100101010111111111010001001111111110110100110"
                    "10101101000111000001100010001001001110010100000010111011011111011010111001110100010011010001110101001011001011000000000100010"
                    "10101101010011111111101010100110011110100001111001111001000010101110001010010110111011101000111110010110100110110111111001011"
                    "01000100111101001111001101111001011000001100100101001000101100001011011001111001111001111101010110011100011011010100001011000"
                    "01110011100101110100000001101011011100111001011001000110011000111111101100101010001100010100111001100111101110100010110100011"
                    "01000010001110010101101011111000101110111100000000101010011010001000100011110001111111010110000000001011000100010010111011001"
                    "10111101100100101011011111010011010000111000111110010011100110101101010001011110000001100001101111111101101111110011101100101"
                    "11111010111101011001001001001000000000110100010101011110101011001010101011000101010010100111110010111001110100001111110111011"
                    "10011001010011111111011111100010010011110010001010100100000110100111000110011010110111001010011011101001111100110010110010011"
                },
        /* 46*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "0", -1, 0, 11, 11, 1, "ISO/IEC 24778:2008 Figure A.1 (1st)",
                    "11101010101"
                    "11111111111"
                    "01000000010"
                    "11011111011"
                    "01010001010"
                    "11010101011"
                    "01010001010"
                    "11011111011"
                    "01000000010"
                    "01111111111"
                    "00101010100"
                },
        /* 47*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "25", -1, 0, 11, 11, 1, "ISO/IEC 24778:2008 Figure A.1 (2nd)",
                    "11101100101"
                    "11111111111"
                    "01000000011"
                    "01011111011"
                    "01010001010"
                    "11010101011"
                    "11010001011"
                    "11011111010"
                    "11000000011"
                    "01111111111"
                    "00100100000"
                },
        /* 48*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "125", -1, 0, 11, 11, 1, "ISO/IEC 24778:2008 Figure A.1 (3rd)",
                    "11110101101"
                    "11111111111"
                    "11000000011"
                    "11011111011"
                    "01010001010"
                    "01010101010"
                    "01010001011"
                    "01011111011"
                    "11000000010"
                    "01111111111"
                    "00111101000"
                },
        /* 49*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "255", -1, 0, 11, 11, 1, "ISO/IEC 24778:2008 Figure A.1 (4th)",
                    "11010101001"
                    "11111111111"
                    "01000000011"
                    "11011111011"
                    "11010001011"
                    "01010101011"
                    "01010001010"
                    "11011111011"
                    "11000000010"
                    "01111111111"
                    "00110011100"
                },
        /* 50*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "1", -1, 0, 11, 11, 1, "",
                    "11101010101"
                    "11111111111"
                    "11000000011"
                    "11011111010"
                    "01010001010"
                    "11010101010"
                    "01010001011"
                    "01011111011"
                    "01000000011"
                    "01111111111"
                    "00100110100"
                },
        /* 51*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "15", -1, 0, 11, 11, 1, "",
                    "11101001001"
                    "11111111111"
                    "11000000011"
                    "01011111011"
                    "11010001010"
                    "01010101010"
                    "11010001011"
                    "11011111010"
                    "11000000010"
                    "01111111111"
                    "00001111100"
                },
        /* 52*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "16", -1, 0, 11, 11, 1, "",
                    "11101110101"
                    "11111111111"
                    "11000000010"
                    "01011111010"
                    "01010001011"
                    "01010101011"
                    "01010001011"
                    "11011111010"
                    "11000000011"
                    "01111111111"
                    "00111100100"
                },
        /* 53*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "63", -1, 0, 11, 11, 1, "",
                    "11100101001"
                    "11111111111"
                    "11000000011"
                    "11011111011"
                    "01010001011"
                    "11010101010"
                    "11010001011"
                    "11011111010"
                    "01000000011"
                    "01111111111"
                    "00101010000"
                },
        /* 54*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "64", -1, 0, 11, 11, 1, "",
                    "11111010101"
                    "11111111111"
                    "01000000010"
                    "01011111011"
                    "01010001010"
                    "01010101011"
                    "11010001011"
                    "01011111011"
                    "01000000011"
                    "01111111111"
                    "00111011100"
                },
        /* 55*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "65", -1, 0, 11, 11, 1, "",
                    "11111010101"
                    "11111111111"
                    "11000000011"
                    "01011111010"
                    "01010001010"
                    "01010101010"
                    "11010001010"
                    "11011111011"
                    "01000000010"
                    "01111111111"
                    "00110111100"
                },
        /* 56*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "126", -1, 0, 11, 11, 1, "",
                    "11110101001"
                    "11111111111"
                    "01000000010"
                    "01011111010"
                    "01010001011"
                    "01010101011"
                    "01010001011"
                    "11011111010"
                    "01000000011"
                    "01111111111"
                    "00110111000"
                },
        /* 57*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "127", -1, 0, 11, 11, 1, "",
                    "11110101001"
                    "11111111111"
                    "11000000011"
                    "01011111011"
                    "01010001011"
                    "01010101010"
                    "01010001010"
                    "01011111010"
                    "01000000010"
                    "01111111111"
                    "00111011000"
                },
        /* 58*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "128", -1, 0, 11, 11, 1, "",
                    "11001010101"
                    "11111111111"
                    "11000000010"
                    "01011111011"
                    "11010001010"
                    "11010101010"
                    "01010001010"
                    "01011111010"
                    "11000000010"
                    "01111111111"
                    "00100010000"
                },
        /* 59*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "191", -1, 0, 11, 11, 1, "",
                    "11000101001"
                    "11111111111"
                    "01000000011"
                    "01011111011"
                    "11010001011"
                    "11010101011"
                    "11010001011"
                    "01011111011"
                    "11000000011"
                    "01111111111"
                    "00100010100"
                },
        /* 60*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "192", -1, 0, 11, 11, 1, "",
                    "11011010101"
                    "11111111111"
                    "11000000010"
                    "11011111011"
                    "11010001010"
                    "01010101010"
                    "11010001011"
                    "11011111010"
                    "11000000011"
                    "01111111111"
                    "00110011000"
                },
        /* 61*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "225", -1, 0, 11, 11, 1, "",
                    "11010010101"
                    "11111111111"
                    "11000000011"
                    "11011111011"
                    "01010001010"
                    "01010101011"
                    "11010001011"
                    "01011111011"
                    "11000000010"
                    "01111111111"
                    "00001100100"
                },
        /* 62*/ { BARCODE_AZRUNE, UNICODE_MODE, -1, -1, -1, -1, "254", -1, 0, 11, 11, 1, "",
                    "11010101001"
                    "11111111111"
                    "11000000010"
                    "11011111010"
                    "11010001011"
                    "01010101010"
                    "01010001011"
                    "01011111011"
                    "11000000011"
                    "01111111111"
                    "00111111100"
                },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];
    char cmp_buf[32768];
    char cmp_msg[1024];

    int do_bwipp = (debug & ZINT_DEBUG_TEST_BWIPP) && testUtilHaveGhostscript(); /* Only do BWIPP test if asked, too slow otherwise */
    int do_zxingcpp = (debug & ZINT_DEBUG_TEST_ZXINGCPP) && testUtilHaveZXingCPPDecoder(); /* Only do ZXing-C++ test if asked, too slow otherwise */

    testStartSymbol("test_encode", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, data[i].eci, data[i].option_1, data[i].option_2, -1, data[i].output_options, data[i].data, data[i].length, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %s, %s, %d, %s, %d, %d, \"%s\", %d, %s, %d, %d, %d, \"%s\",\n",
                    i, testUtilBarcodeName(data[i].symbology), testUtilInputModeName(data[i].input_mode), data[i].eci, testUtilOutputOptionsName(data[i].output_options),
                    data[i].option_1, data[i].option_2, testUtilEscape(data[i].data, length, escaped, sizeof(escaped)), data[i].length,
                    testUtilErrorName(data[i].ret), symbol->rows, symbol->width, data[i].bwipp_cmp, data[i].comment);
            testUtilModulesPrint(symbol, "                    ", "\n");
            printf("                },\n");
        } else {
            if (ret < ZINT_ERROR) {
                int width, row;

                assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d (%s)\n", i, symbol->rows, data[i].expected_rows, data[i].data);
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);

                ret = testUtilModulesCmp(symbol, data[i].expected, &width, &row);
                assert_zero(ret, "i:%d testUtilModulesCmp ret %d != 0 width %d row %d (%s)\n", i, ret, width, row, data[i].data);

                if (do_bwipp && testUtilCanBwipp(i, symbol, data[i].option_1, data[i].option_2, -1, debug)) {
                    if (!data[i].bwipp_cmp) {
                        if (debug & ZINT_DEBUG_TEST_PRINT) printf("i:%d %s not BWIPP compatible (%s)\n", i, testUtilBarcodeName(symbol->symbology), data[i].comment);
                    } else {
                        ret = testUtilBwipp(i, symbol, data[i].option_1, data[i].option_2, -1, data[i].data, length, NULL, cmp_buf, sizeof(cmp_buf), NULL);
                        assert_zero(ret, "i:%d %s testUtilBwipp ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                        ret = testUtilBwippCmp(symbol, cmp_msg, cmp_buf, data[i].expected);
                        assert_zero(ret, "i:%d %s testUtilBwippCmp %d != 0 %s\n  actual: %s\nexpected: %s\n",
                                       i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_buf, data[i].expected);
                    }
                }
                if (do_zxingcpp && testUtilCanZXingCPP(i, symbol, data[i].data, length, debug)) {
                    int cmp_len, ret_len;
                    char modules_dump[22801 + 1];
                    assert_notequal(testUtilModulesDump(symbol, modules_dump, sizeof(modules_dump)), -1, "i:%d testUtilModulesDump == -1\n", i);
                    ret = testUtilZXingCPP(i, symbol, data[i].data, length, modules_dump, cmp_buf, sizeof(cmp_buf), &cmp_len);
                    assert_zero(ret, "i:%d %s testUtilZXingCPP ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                    ret = testUtilZXingCPPCmp(symbol, cmp_msg, cmp_buf, cmp_len, data[i].data, length, NULL /*primary*/, escaped, &ret_len);
                    assert_zero(ret, "i:%d %s testUtilZXingCPPCmp %d != 0 %s\n  actual: %.*s\nexpected: %.*s\n",
                                   i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_len, cmp_buf, ret_len, escaped);
                }
            }
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_encode_segs(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int input_mode;
        int output_options;
        int option_1;
        int option_2;
        struct zint_seg segs[3];
        int ret;

        int expected_rows;
        int expected_width;
        int bwipp_cmp;
        char *comment;
        char *expected;
    };
    struct item data[] = {
        /*  0*/ { UNICODE_MODE, -1, -1, 1, { { TU("¶"), -1, 0 }, { TU("Ж"), -1, 7 }, { TU(""), 0, 0 } }, 0, 15, 15, 1, "ISO/IEC 24778:2008 16.5 example",
                    "001111000011111"
                    "110111100100011"
                    "111100001000111"
                    "101111111111111"
                    "001100000001111"
                    "000101111101101"
                    "110101000101101"
                    "011101010101001"
                    "101101000101010"
                    "110101111101001"
                    "000100000001011"
                    "000111111111111"
                    "010001100010001"
                    "001010111001010"
                    "000001011100111"
                },
        /*  1*/ { UNICODE_MODE, -1, -1, 1, { { TU("¶"), -1, 0 }, { TU("Ж"), -1, 0 }, { TU(""), 0, 0 } }, ZINT_WARN_USES_ECI, 15, 15, 1, "ISO/IEC 24778:2008 16.5 example auto-ECI",
                    "001111000011111"
                    "110111100100011"
                    "111100001000111"
                    "101111111111111"
                    "001100000001111"
                    "000101111101101"
                    "110101000101101"
                    "011101010101001"
                    "101101000101010"
                    "110101111101001"
                    "000100000001011"
                    "000111111111111"
                    "010001100010001"
                    "001010111001010"
                    "000001011100111"
                },
        /*  2*/ { UNICODE_MODE, -1, -1, 2, { { TU("Ж"), -1, 7 }, { TU("¶"), -1, 0 }, { TU(""), 0, 0 } }, 0, 19, 19, 1, "ISO/IEC 24778:2008 16.5 example inverted",
                    "0000011010000000000"
                    "0000001101101010000"
                    "0111000110100011110"
                    "0010011111100001110"
                    "0001110100110010000"
                    "0110111111111111110"
                    "0000010000000100011"
                    "1100110111110110000"
                    "0011110100010110101"
                    "1100010101010100001"
                    "1110010100010100000"
                    "1001010111110100000"
                    "1001010000000100011"
                    "0011011111111110001"
                    "0100001111100000111"
                    "1011111010011010111"
                    "1111010101011010101"
                    "1000001011111001010"
                    "0100000000011100111"
                },
        /*  3*/ { UNICODE_MODE, -1, -1, 2, { { TU("Ж"), -1, 0 }, { TU("¶"), -1, 0 }, { TU(""), 0, 0 } }, ZINT_WARN_USES_ECI, 19, 19, 1, "ISO/IEC 24778:2008 16.5 example inverted auto-ECI",
                    "0000011010000000000"
                    "0000001101101010000"
                    "0111000110100011110"
                    "0010011111100001110"
                    "0001110100110010000"
                    "0110111111111111110"
                    "0000010000000100011"
                    "1100110111110110000"
                    "0011110100010110101"
                    "1100010101010100001"
                    "1110010100010100000"
                    "1001010111110100000"
                    "1001010000000100011"
                    "0011011111111110001"
                    "0100001111100000111"
                    "1011111010011010111"
                    "1111010101011010101"
                    "1000001011111001010"
                    "0100000000011100111"
                },
        /*  4*/ { UNICODE_MODE, -1, -1, -1, { { TU("product:Google Pixel 4a - 128 GB of Storage - Black;price:$439.97"), -1, 3 }, { TU("品名:Google 谷歌 Pixel 4a -128 GB的存储空间-黑色;零售价:￥3149.79"), -1, 29 }, { TU("Produkt:Google Pixel 4a - 128 GB Speicher - Schwarz;Preis:444,90 €"), -1, 17 } }, 0, 49, 49, 0, "AIM ITS/04-023:2022 Annex A example; BWIPP different encodation (better)",
                    "0000110010100000001100011100010010010010100010101"
                    "0001100000010101011010010100011100000001000100010"
                    "0001110011110000000000101101100110101001100000000"
                    "0110001001100100100100110111000111101010011110100"
                    "0001011110100011010010001000111110010110111010111"
                    "0010010001101101100111010110111000001101001111101"
                    "0110001110110010010000111001100100011001100101001"
                    "0110001101010110010001010100001101001110000110000"
                    "1010101010101010101010101010101010101010101010101"
                    "0100110100001010010110010100111110010110001010010"
                    "1110111010111110101110101010011011000100100100010"
                    "1000000100001011101010010110010011101011000101001"
                    "0101101011110000011100001001000011010101101101111"
                    "0010001100010010110111110101101001011110000011010"
                    "0100000011001011111011111011111010001101100110000"
                    "1000010001011000100111100100010100101010001101101"
                    "0101110010010100010110101010010100011001111001011"
                    "1101110001010101111001110000100101000010001111000"
                    "0001110110000111111111111111111101110001111110000"
                    "0000010101001010011000000000001110111111001001000"
                    "0000010010100111111011111111101101100011110000110"
                    "1000010100010111101010000000101011000001010011101"
                    "1110011111100110111010111110101000110101100100011"
                    "0101100000101101001010100010101011101000001111110"
                    "1010101010101010101010101010101010101010101010101"
                    "1011101100001100011010100010101111011100011001000"
                    "0011111111100111101010111110101111011100111111001"
                    "1000100100011010001010000000101010000101001110110"
                    "0111000010011110111011111111101000101101110100000"
                    "0100100101000110001000000000001010101001001111100"
                    "0110011110001110101111111111111111101101110011101"
                    "0011011000010110000010110100110010001000001001100"
                    "0001100111010000001111001101101000000111100000011"
                    "0111100000100011110011100001000110110000011010011"
                    "0110011110111110100010011001001011111111101100100"
                    "0111111001101011000101000001010010110100001101000"
                    "1101000010001010010001101010001111110111101100110"
                    "1011110000000110111001010011000110001000000110110"
                    "0000010110110000101010001110111000011101101001001"
                    "1010010100110110000011000000110100110100000100001"
                    "1010101010101010101010101010101010101010101010101"
                    "0000100100100000000110100100000001001000011010110"
                    "1000101110101110011110001000100100110100111100001"
                    "0000110101111100011101100000001111001111010100000"
                    "0101000010011111110110101100010011010010101110100"
                    "0000100101011010101001110100111010000000001010011"
                    "0001001111111100100111011100111101001111101100011"
                    "1001101000110101111010100111100011111001000100101"
                    "0001001010011000000100101101100110101000100000000"
                },
        /*  5*/ { DATA_MODE, -1, -1, 2, { { TU("\357"), 1, 0 }, { TU("\357"), 1, 7 }, { TU("\357"), 1, 0 } }, 0, 19, 19, 1, "Standard example + extra seg, data mode",
                    "1110011101010111000"
                    "1100010001011100011"
                    "1001110101000010110"
                    "0001000011101001111"
                    "0001110100111011000"
                    "1111111111111110101"
                    "1100110000000111011"
                    "0110010111110100111"
                    "1110110100010101011"
                    "1010010101010110001"
                    "0010010100010100111"
                    "0001110111110111010"
                    "0011110000000111100"
                    "0000011111111110001"
                    "0111001101000000011"
                    "0011000000111110111"
                    "1111111001101000010"
                    "0110001101100001010"
                    "0111100111100000010"
                },
        /*  6*/ { UNICODE_MODE, -1, -1, -1, { { TU("12345678"), -1, 3 }, { TU("ABCDEFGH"), -1, 4 }, { TU("123456789"), -1, 5 } }, 0, 23, 23, 0, "Mode change between segs; BWIPP different encodation",
                    "00100011011101100111000"
                    "00101011010000010111111"
                    "00011001010101011010100"
                    "01011001100000101110000"
                    "00011000100010011101100"
                    "00110000100011111111000"
                    "01001111100101001111000"
                    "01000111111111111000110"
                    "01010111000000011000101"
                    "11010101011111011111000"
                    "11111101010001011100100"
                    "00100011010101011101010"
                    "01000001010001010001111"
                    "10111101011111010110010"
                    "10001001000000010111000"
                    "00001001111111111011111"
                    "10101100101001000010000"
                    "10110011100001111000110"
                    "11101000100001111011010"
                    "00010010100111001011100"
                    "11111111000010000100001"
                    "10101100001011010010000"
                    "10001000000000111000011"
                },
    };
    int data_size = ARRAY_SIZE(data);
    int i, j, seg_count, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];
    char cmp_buf[32768];
    char cmp_msg[1024];

    int do_bwipp = (debug & ZINT_DEBUG_TEST_BWIPP) && testUtilHaveGhostscript(); /* Only do BWIPP test if asked, too slow otherwise */
    int do_zxingcpp = (debug & ZINT_DEBUG_TEST_ZXINGCPP) && testUtilHaveZXingCPPDecoder(); /* Only do ZXing-C++ test if asked, too slow otherwise */

    testStartSymbol("test_encode_segs", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        testUtilSetSymbol(symbol, BARCODE_AZTEC, data[i].input_mode, -1 /*eci*/,
                            data[i].option_1, data[i].option_2, -1, data[i].output_options, NULL, 0, debug);
        for (j = 0, seg_count = 0; j < 3 && data[i].segs[j].length; j++, seg_count++);

        ret = ZBarcode_Encode_Segs(symbol, data[i].segs, seg_count);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode_Segs ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            char escaped1[4096];
            char escaped2[4096];
            int length = data[i].segs[0].length == -1 ? (int) ustrlen(data[i].segs[0].source) : data[i].segs[0].length;
            int length1 = data[i].segs[1].length == -1 ? (int) ustrlen(data[i].segs[1].source) : data[i].segs[1].length;
            int length2 = data[i].segs[2].length == -1 ? (int) ustrlen(data[i].segs[2].source) : data[i].segs[2].length;
            printf("        /*%3d*/ { %s, %s, %d, %d, { { TU(\"%s\"), %d, %d }, { TU(\"%s\"), %d, %d }, { TU(\"%s\"), %d, %d } }, %s, %d, %d, %d, \"%s\",\n",
                    i, testUtilInputModeName(data[i].input_mode), testUtilOutputOptionsName(data[i].output_options),
                    data[i].option_1, data[i].option_2,
                    testUtilEscape((const char *) data[i].segs[0].source, length, escaped, sizeof(escaped)), data[i].segs[0].length, data[i].segs[0].eci,
                    testUtilEscape((const char *) data[i].segs[1].source, length1, escaped1, sizeof(escaped1)), data[i].segs[1].length, data[i].segs[1].eci,
                    testUtilEscape((const char *) data[i].segs[2].source, length2, escaped2, sizeof(escaped2)), data[i].segs[2].length, data[i].segs[2].eci,
                    testUtilErrorName(data[i].ret), symbol->rows, symbol->width, data[i].bwipp_cmp, data[i].comment);
            testUtilModulesPrint(symbol, "                    ", "\n");
            printf("                },\n");
        } else {
            if (ret < ZINT_ERROR) {
                int width, row;

                assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d\n", i, symbol->rows, data[i].expected_rows);
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d\n", i, symbol->width, data[i].expected_width);

                ret = testUtilModulesCmp(symbol, data[i].expected, &width, &row);
                assert_zero(ret, "i:%d testUtilModulesCmp ret %d != 0 width %d row %d\n", i, ret, width, row);

                if (do_bwipp && testUtilCanBwipp(i, symbol, data[i].option_1, data[i].option_2, -1, debug)) {
                    if (!data[i].bwipp_cmp) {
                        if (debug & ZINT_DEBUG_TEST_PRINT) printf("i:%d %s not BWIPP compatible (%s)\n", i, testUtilBarcodeName(symbol->symbology), data[i].comment);
                    } else {
                        ret = testUtilBwippSegs(i, symbol, data[i].option_1, data[i].option_2, -1, data[i].segs, seg_count, NULL, cmp_buf, sizeof(cmp_buf));
                        assert_zero(ret, "i:%d %s testUtilBwippSegs ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                        ret = testUtilBwippCmp(symbol, cmp_msg, cmp_buf, data[i].expected);
                        assert_zero(ret, "i:%d %s testUtilBwippCmp %d != 0 %s\n  actual: %s\nexpected: %s\n",
                                       i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_buf, data[i].expected);
                    }
                }
                if (do_zxingcpp && testUtilCanZXingCPP(i, symbol, (const char *) data[i].segs[0].source, data[i].segs[0].length, debug)) {
                    if (data[i].input_mode == DATA_MODE) {
                        if (debug & ZINT_DEBUG_TEST_PRINT) {
                            printf("i:%d multiple segments in DATA_MODE not currently supported for ZXing-C++ testing (%s)\n",
                                    i, testUtilBarcodeName(symbol->symbology));
                        }
                    } else {
                        int cmp_len, ret_len;
                        char modules_dump[22801 + 1];
                        assert_notequal(testUtilModulesDump(symbol, modules_dump, sizeof(modules_dump)), -1, "i:%d testUtilModulesDump == -1\n", i);
                        ret = testUtilZXingCPP(i, symbol, (const char *) data[i].segs[0].source, data[i].segs[0].length,
                                modules_dump, cmp_buf, sizeof(cmp_buf), &cmp_len);
                        assert_zero(ret, "i:%d %s testUtilZXingCPP ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                        ret = testUtilZXingCPPCmpSegs(symbol, cmp_msg, cmp_buf, cmp_len, data[i].segs, seg_count,
                                NULL /*primary*/, escaped, &ret_len);
                        assert_zero(ret, "i:%d %s testUtilZXingCPPCmpSegs %d != 0 %s\n  actual: %.*s\nexpected: %.*s\n",
                                       i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_len, cmp_buf, ret_len, escaped);
                    }
                }
            }
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

/* #181 Nico Gunkel OSS-Fuzz and #300 Andre Maute */
static void test_fuzz(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        char *data;
        int length;
        int input_mode;
        int option_1;
        int option_2;
        int ret;
    };
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_AZTEC,
                    "\133\060\060\060\135\060\125\125\125\125\140\060\125\125\125\125\060\060\060\271\060\060\125\103\164\125\125\125\377\377\125\125"
                    "\125\125\125\125\125\133\060\076\060\135\261\177\261\261\261\236\261\261\261\040\261\261\261\261\261\261\261\020\261\261\261\261"
                    "\261\261\265\261\261\261\261\261\261\261\261\261\261\261\261\040\224\261\261\261\261\261\000\000\004\000\031\060\031\031\031\031"
                    "\031\031\031\031\261\261\040\261\261\261\261\261\261\261\020\261\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\376\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\261\261\261\261\261\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\135\135\135\135\135\135"
                    "\135\335\135\060\060\010\010\010\010\010\060",
                    2251, DATA_MODE, -1, -1, ZINT_ERROR_TOO_LONG
                }, /* Original OSS-Fuzz triggering data for malloc leak */
        /*  1*/ { BARCODE_AZTEC,
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\000\060\060\060\060\000\060\060\000\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\005\060\060\060\060\060\060\060\005\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\000\000\060\350\060\060\060\060\060\350\060\345\060\343\060\060\060\005\060\060\060"
                    "\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\005\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060"
                    "\060\060\060\060\060\175\175\175\175\060\175\175\175\175\175\060\060\060\060\175\060\175\175\175\175\060\060\060\060\005\060\060"
                    "\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\005\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\000\060\060\060\060\060\005\060\060\060\060\060\005\005\060\005\060\060\060\060\060\060\005"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\353\060\060\353"
                    "\060\060\060\060\353\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060"
                    "\060\060\060\060\353\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060"
                    "\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353"
                    "\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060"
                    "\060\060\353\060\060\060\060\060\353\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060"
                    "\060\060\353\060\060\060\060\353\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060"
                    "\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060"
                    "\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060"
                    "\353\060\060\060\060\353\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353"
                    "\060\060\060\060\353\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\264\060"
                    "\060\060\060\060\264\060\060\060\060\060\264\060\060\060\060\264\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060"
                    "\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060"
                    "\353\060\060\060\060\060\353\060\060\060\060\060\353\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353"
                    "\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060"
                    "\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060"
                    "\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060"
                    "\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060"
                    "\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060"
                    "\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060"
                    "\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353"
                    "\060\060\060\060\353\060\060\060\060\060\353\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060"
                    "\060\060\060\060\353\060\060\060\060\060\353\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060"
                    "\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\060"
                    "\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\353\060\060\060\060\353\060\060\060\060\060\353\060\060\060\060\353"
                    "\060\060\060\060\060\353\060\060\060\060\060\353\060\060\353\060\060\060\343\060\060\060\060\060\060\060\060\060\005\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\377\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\005\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\361\060\060\060\060\060\361\060\060\060\060\361\060\060\060\060\060\361\060\060\060\060\060\361"
                    "\060\060\060\361\060\060\060\005\060\060\060\060\060\060\060\005\060\060\060\060\060\005\363\060\362\060\060\060\060\377\060\060"
                    "\060\177\060\060\060\060\060\263\060\060\060\060\060\060\060\060\060\000\060\060\060\060\377\177\060\060\060\362\060\362\060\363"
                    "\060\363\060\177\060\377\060\060\060\060\060\060\060\377\177\060\355\060\057\060\060\060\377\060\377\060\060\060\177\000\060\000"
                    "\060\377\060\060\060\060\060\060\005\060\060\000\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\005\060\060"
                    "\060\060\060\060\060\371\060\060\060\363\060\060\060\060\060\060\362\060\060\060\060\060\362\060\363\060\362\060\060\060\060\377"
                    "\060\177\060\060\060\060\060\263\060\060\060\060\060\060\060\060\060\060\000\060\060\060\377\177\060\060\060\362\060\362\060\363"
                    "\060\363\060\060\377\057\060\060\060\060\060\060\377\177\060\355\060\060\060\060\060\377\060\377\060\060\060\177\000\060\000\060"
                    "\377\060\353\060\060\000\060\060\060\060\060\060\060\060\060\256\060\060\060\362\060\060\060\060\060\060\060\060\005\362\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\057\060\060\060\060\060\060\060\000\060\000\060\060\060\000\060\060"
                    "\057\060\060\060\060\060\377\060\377\060\060\060\060\060\060\060\060\060\060\060\060\000\060\060\347\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\000\060\377\060\060\060\377\060\363\060\363\060\060\060\060\060\060\060\060\060\060\060\060\060\060"
                    "\362\060\060\060\060\060\060\362\347\060\354\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\005\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\005\060\060\060\000\060\000\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\344\005\060\060\005\060\342\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\005\060\000\060\060\060\060\060\060\060\060\060\060\377\060\060\060\060\005\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\005\060\060\060\060"
                    "\060\060\060\060\060\060\060\005\060\060\060\005\060\060\060\060\060\060\060\060\060\060\005\060\351\060\060\060\060\060\060\005"
                    "\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005"
                    "\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\005\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\005\060\060\060\005\060\060\060\060\005"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\005\060\060\060\175\175\060\175\060\060\060"
                    "\060\175\060\060\060\060\175\060\060\060\060\175\060\175\175\175\005\060\060\060\060\060\060\060\060\377\060\060\060\060\060\060"
                    "\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\005\060\342\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\005\060\060\060\345\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\005\060\371\060\060\060\060\060\060\060\060\060\060\060\361\060\060\060\060\060\005\361\060\060\060\060"
                    "\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\005\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\005\060\351\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\005\363\060\060\005\060\060\005\060\060\060\060\060\060\060\060\060\005\060\000\060"
                    "\060\060\060\060\060\060\362\060\060\060\060\060\060\060\060\060\060\060\005\060\005\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\000\060\060\060\060\060\060\060\060\060\005\060\377\060\005"
                    "\060\371\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\005\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060"
                    "\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\175\175\175\175\060\175\175\060\060\060\060\060\175\060\175\175"
                    "\175\005\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\005\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\005\060\060\060\060\060\060\060\060"
                    "\060\060\005\060\060\060\060\060\005\060\000\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060"
                    "\060\060\005\060\060\060\060\060\005\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060"
                    "\060\060\005\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\005\060\351\060\060\060\060\060\060\060"
                    "\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060\060\060\060\060\060\060\060\060\060\060\060\060\005\060\060\060"
                    "\060\005\060\060\060\005\060\362\060\060\060\060\060\060\060\060\060\060\060\060\377\060\060\000\177\060\060\000\060\377\060\353"
                    "\060\060\060\363\060\060\060\060\060\060\060\060\060\060\060\060\362\060\060\060\060\060\000\060\060\377\060\060\060\175\175\175"
                    "\175\060\060\060\175\175\175\175\060\060\005\060\005\060\005\060\060\060\060\000\000\060\060\060\060\060\060\377\060\060\060\060"
                    "\377\060\377\377\060\060\057\060\060\057\060\060\060\000\000\060\060",
                    2801, DATA_MODE, -1, -1, ZINT_ERROR_TOO_LONG
                }, /* Original OSS-Fuzz triggering data for binary_string buffer overrun */
        /*  2*/ { BARCODE_AZTEC,
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123",
                    4483, -1, 1, -1, 0
                }, /* 4483 = (1664 (Max codewords) - 169 (ECC codewords) - 5/12 (D/L) - 3/12 (padding)) * 3 (3 4-bit digits per 12-bit wordcode) = 4483 */
        /*  3*/ { BARCODE_AZTEC,
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123",
                    4484, -1, 1, -1, ZINT_ERROR_TOO_LONG
                },
        /*  4*/ { BARCODE_AZTEC,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXY",
                    3587, -1, 1, -1, 0
                },
        /*  5*/ { BARCODE_AZTEC,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ",
                    3588, -1, 1, -1, ZINT_ERROR_TOO_LONG
                },
        /*  6*/ { BARCODE_AZTEC,
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240",
                    2237, -1, 1, -1, 0
                },
        /*  7*/ { BARCODE_AZTEC,
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240"
                    "\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240\240",
                    2238, -1, 1, -1, ZINT_ERROR_TOO_LONG
                },
        /*  8*/ { BARCODE_AZTEC,
                    "\105\105\000\000\000\000\000\000\000\000\077\012\377\377\377\072\376\376\350\350\350\350\350\250\350\350\350\350\354\350\350\350\350\350\001\000\000\000\000\000"
                    "\000\036\103\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\002\222\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\077\012"
                    "\377\377\377\072\376\376\350\350\350\350\350\250\350\350\350\350\354\350\350\350\000\000\000\000\000\000\000\033\000\036\103\012\072\103\103\000\100\116\000\000"
                    "\000\000\000\000\000\000\000\000\000\222\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\012\000\000\000\000\072\103\103\103\103\012\012\000\365\365\365\365\365\365\374\365\365\365\365\365\000\000\001\000\000\000\000\000\100\377\337\377"
                    "\377\377\377\377\000\000\000\000\372\377\000\100\377\377\350\350\000\000\350\350\350\350\350\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\365\000"
                    "\000\000\000\000\000\000\000\000\377\377\377\350\350\350\350\350\350\350\350\350\350\350\350\350\350\061\350\350\350\350\354\350\350\350\350\350\001\000\000\000"
                    "\000\000\000\036\103\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\216\000\000\000\000\000\000\000\377\377\377\377\377\377\377\000\000"
                    "\377\365\374\365\365\365\365\001\236\365\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\064\064\064\064\064\064\064\064\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153"
                    "\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\064\064\064\064\064\064\064\064\064\064\044\064\064\064\064\064\064\064\064\064"
                    "\064\064\064\064\064\064\064\064\064\064\064\064\064\064\064\064\064\264\264\362\362\362\362\242\242\242\242\242\242\242\242\242\242\242\242\242\242\242\242\242"
                    "\242\242\242\242\242\242\242\242\242\242\242\242\242\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\222\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\012\000\000\000\000\072\103\103\103\103\012\012\000\365\365\365\365\365"
                    "\365\374\365\365\365\365\365\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\100\377\377\377\377\377\377\377\000\000\000\000"
                    "\000\000\000\100\377\377\350\350\000\000\350\350\350\350\350\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\365\000\000\000\000\000\000\000\266\266"
                    "\266\266\112\000\000\000\266\266\266\266\266\266\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\022\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\077\012\377"
                    "\377\377\072\376\376\350\350\350\350\350\000\000\000\000\001\000\000\000\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\100\116\000\000\000"
                    "\000\000\000\000\000\000\000\000\222\000\000\000\000\000\000\000\000\000\000\025\000\000\000\000\001\000\000\000\000\000\000\003\000\000\000\000\000\000\000\000"
                    "\000\000\012\000\000\000\000\072\103\103\103\103\012\012\000\365\365\365\365\365\365\374\365\365\365\365\365\000\000\000\311\000\000\000\000\100\377\337\377\377"
                    "\377\377\377\000\000\000\000\000\000\000\100\377\377\350\353\000\000\350\150\350\350\350\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\365\000\000"
                    "\000\000\000\000\000\047\000\377\377\377\350\350\350\350\350\350\350\350\350\350\350\350\350\350\254\350\350\350\350\354\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\350\350\350\350\350\001\000\000\127\000\000\000\036\103"
                    "\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\220\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\050\050\050\000\000\000"
                    "\000\000\000\000\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\266"
                    "\266\266\266\266\266\377\377\377\377\377\013\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\005\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\266\266\266\266\266\266\266\266\266\266\377\377\377\377\377\377\377\377\377\377\377\377\044"
                    "\377\377\377\377\377\377\050\064\064\064\000\000\000\000\072\376\376\350\350\350\350\350\350\377\377\377\377\377\377\377\377\377\377\377\377\377\005\377\377\377"
                    "\377\350\350\350\350\350\350\350\310\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\000\000\000\000\000\000\000\000\000\000\000\000\000\266\266"
                    "\266\266\266\266\377\377\377\377\377\013\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\005\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\266\266\266\266\266\266\266\266\266\266\377\377\377\377\377\377\377\377\377\377\377\377\044\377"
                    "\377\377\377\377\377\050\064\064\064\000\000\000\000\072\376\376\350\350\350\350\350\350\377\377\377\377\377\377\377\377\377\377\377\377\377\005\377\377\377\377"
                    "\350\350\350\350\350\350\350\310\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\000\064\064\064\064\064\064\064\064\064\064\064\064\064\064\073\064\064\064\064"
                    "\064\064\064\064\064\064\064\064\000\377\365\374\365\365\365\365\001\236\365\000\000\001\000\000\000\000\000\000\000\000\000\000\001\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\064\064\064\064\064\064\064\064\153\153\153\153\153"
                    "\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\337\266\266\266\000"
                    "\000\000\000\000\000\000\377\377\377\377\377\000\000\000\000\000\000\000\100\377\377\350\350\000\000\350\350\350\350\350\350\350\350\001\000\000\000\000\000\000"
                    "\036\103\012\072\103\365\000\000\000\000\000\000\000\000\000\377\377\377\350\350\350\350\350\350\350\350\350\350\350\350\350\350\254\350\350\350\350\354\350\350"
                    "\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\221\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\050\000\050\050\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\004\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\000\177\377\377\377"
                    "\046\000\000\000\000\000\000\027\027\027\027\027\027\027\027\027\027\027\027\000\027\027\027\027\000\004\000\000\000\000\000\135\000\044\103\000\000\377\377\377"
                    "\377\377\103\377\364\377\364",
                    2167, DATA_MODE, -1, 1, ZINT_ERROR_TOO_LONG
                }, /* #300 (#2) Andre Maute */
        /*  9*/ { BARCODE_AZTEC,
                    "111\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "111",
                    2054, DATA_MODE, 1, -1, 0
                }, /* 2048 byte block surrounded by digits */
        /* 10*/ { BARCODE_AZTEC,
                    "\105\105\000\000\000\000\000\000\000\000\077\012\377\377\377\072\376\376\350\350\350\350\350\250\350\350\350\350\354\350\350\350\350\350\001\000\000\000\000\000"
                    "\000\036\103\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\002\222\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\077\012"
                    "\377\377\377\072\376\376\350\350\350\350\350\250\350\350\350\350\354\350\350\350\000\000\000\000\000\000\000\033\000\036\103\012\072\103\103\000\100\116\000\000"
                    "\000\000\000\000\000\000\000\000\000\222\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\012\000\000\000\000\072\103\103\103\103\012\012\000\365\365\365\365\365\365\374\365\365\365\365\365\000\000\001\000\000\000\000\000\100\377\337\377"
                    "\377\377\377\377\000\000\000\000\372\377\000\100\377\377\350\350\000\000\350\350\350\350\350\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\365\000"
                    "\000\000\000\000\000\000\000\000\377\377\377\350\350\350\350\350\350\350\350\350\350\350\350\350\350\061\350\350\350\350\354\350\350\350\350\350\001\000\000\000"
                    "\000\000\000\036\103\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\216\000\000\000\000\000\000\000\377\377\377\377\377\377\377\000\000"
                    "\377\365\374\365\365\365\365\001\236\365\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\064\064\064\064\064\064\064\064\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153"
                    "\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\064\064\064\064\064\064\064\064\064\064\044\064\064\064\064\064\064\064\064\064"
                    "\064\064\064\064\064\064\064\064\064\064\064\064\064\064\064\064\064\264\264\362\362\362\362\242\242\242\242\242\242\242\242\242\242\242\242\242\242\242\242\242"
                    "\242\242\242\242\242\242\242\242\242\242\242\242\242\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\222\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\012\000\000\000\000\072\103\103\103\103\012\012\000\365\365\365\365\365"
                    "\365\374\365\365\365\365\365\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\100\377\377\377\377\377\377\377\000\000\000\000"
                    "\000\000\000\100\377\377\350\350\000\000\350\350\350\350\350\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\365\000\000\000\000\000\000\000\266\266"
                    "\266\266\112\000\000\000\266\266\266\266\266\266\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\022\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\077\012\377"
                    "\377\377\072\376\376\350\350\350\350\350\000\000\000\000\001\000\000\000\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\100\116\000\000\000"
                    "\000\000\000\000\000\000\000\000\222\000\000\000\000\000\000\000\000\000\000\025\000\000\000\000\001\000\000\000\000\000\000\003\000\000\000\000\000\000\000\000"
                    "\000\000\012\000\000\000\000\072\103\103\103\103\012\012\000\365\365\365\365\365\365\374\365\365\365\365\365\000\000\000\311\000\000\000\000\100\377\337\377\377"
                    "\377\377\377\000\000\000\000\000\000\000\100\377\377\350\353\000\000\350\150\350\350\350\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\365\000\000"
                    "\000\000\000\000\000\047\000\377\377\377\350\350\350\350\350\350\350\350\350\350\350\350\350\350\254\350\350\350\350\354\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\350\350\350\350\350\001\000\000\127\000\000\000\036\103"
                    "\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\220\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\050\050\050\000\000\000"
                    "\000\000\000\000\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\266"
                    "\266\266\266\266\266\377\377\377\377\377\013\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\005\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\172\377\377"
                    "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\266\266\266\266\266\266\266\266\266\266\377\377\377\377\377\377\377\377\377\377\377\377\044"
                    "\377\377\377\377\377\377\050\064\064\064\000\000\000\000\072\376\376\350\350\350\350\350\350\377\377\377\377\377\377\377\377\377\377\377\377\377\005\377\377\377"
                    "\377\350\350\350\350\350\350\350\310\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\310\000\064\064\064\064\064\064\064\064\064\064\064\064\064\064\073\064\064\064\064\064\064\064\064\064\064\064"
                    "\064\000\377\365\374\365\365\365\365\001\236\365\000\000\001\000\000\000\000\000\000\000\000\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\064\064\064\064\064\064\064\064\153\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\153\153\153\153"
                    "\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\153\337\266\266\266\000"
                    "\000\000\000\000\000\000\377\377\377\377\377\000\000\000\000\000\000\000\100\377\377\350\350\000\000\350\350\350\350\350\350\350\350\001\000\000\000\000\000\000"
                    "\036\103\012\072\103\365\000\000\000\000\000\000\000\000\000\377\377\377\350\350\350\350\350\350\350\350\350\350\350\350\350\350\254\350\350\350\350\354\350\350"
                    "\350\350\350\001\000\000\000\000\000\000\036\103\012\072\103\103\000\100\116\000\000\000\000\000\000\000\000\000\000\000\221\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\050\000\050\050\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\001\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\004\000\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032"
                    "\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032\032"
                    "\032\032\032\032\032\032\032\032\032\032\032\032\032\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
                    "\377\032\032\032\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\000\177\377\377\377\046\000\000\000\000\000\000\027\027\027"
                    "\027\027\027\027\027\027\027\027\027\000\027\027\027\027\000\004\000\000\000\000\000\135\000\044\103\000\000\377\377\377\377\377\103\377\364\377\364",
                    2157, DATA_MODE, -1, 1, ZINT_ERROR_TOO_LONG
                }, /* #300 (#3) Andre Maute */
        /* 11*/ { BARCODE_AZTEC,
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
                    "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000",
                    996, DATA_MODE, 2, -1, 0
                }, /* Padding 11 example causing issue with ZXing-C++ */
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[8192];
    char cmp_buf[32768];
    char cmp_msg[8192];

    int do_zxingcpp = (debug & ZINT_DEBUG_TEST_ZXINGCPP) && testUtilHaveZXingCPPDecoder(); /* Only do ZXing-C++ test if asked, too slow otherwise */

    testStartSymbol("test_fuzz", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, -1 /*eci*/, data[i].option_1, data[i].option_2, -1, -1 /*output_options*/, data[i].data, data[i].length, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (ret < ZINT_ERROR) {

            if (do_zxingcpp && testUtilCanZXingCPP(i, symbol, data[i].data, length, debug)) {
                int cmp_len, ret_len;
                char modules_dump[22801 + 1];
                assert_notequal(testUtilModulesDump(symbol, modules_dump, sizeof(modules_dump)), -1, "i:%d testUtilModulesDump == -1\n", i);
                ret = testUtilZXingCPP(i, symbol, data[i].data, length, modules_dump, cmp_buf, sizeof(cmp_buf), &cmp_len);
                assert_zero(ret, "i:%d %s testUtilZXingCPP ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                ret = testUtilZXingCPPCmp(symbol, cmp_msg, cmp_buf, cmp_len, data[i].data, length, NULL /*primary*/, escaped, &ret_len);
                assert_zero(ret, "i:%d %s testUtilZXingCPPCmp %d != 0 %s\n  actual: %.*s\nexpected: %.*s\n",
                               i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_len, cmp_buf, ret_len, escaped);
            }
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

#include <time.h>

#define TEST_PERF_ITERATIONS    1000

/* Not a real test, just performance indicator */
static void test_perf(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int input_mode;
        int option_1;
        int option_2;
        char *data;
        int ret;

        int expected_rows;
        int expected_width;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { BARCODE_AZTEC, -1, -1, -1,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                    0, 49, 49, "286 chars, 8-bit words, upper" },
        /*  1*/ { BARCODE_AZTEC, -1, -1, -1,
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                    "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890",
                    0, 79, 79, "900 chars, 10-bit words, numeric" },
        /*  2*/ { BARCODE_AZTEC, -1, -1, -1,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377",
                    0, 91, 91, "980 chars, 10-bit words, mixed" },
        /*  3*/ { BARCODE_AZTEC, -1, -1, -1,
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377"
                    "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz ~~~~~~~~~~~~~~~~~~~~~~~~~ ?????????????????????????? 12345678901234567890123456 \377\377\377\377\377\377",
                    0, 113, 113, "1540 chars, 12-bit words, mixed" },
        /*  4*/ { BARCODE_AZRUNE, -1, -1, -1,
                    "255",
                    0, 11, 11, "3 chars, AZRUNE" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol;

    clock_t start, total_encode = 0, total_buffer = 0, diff_encode, diff_buffer;

    if (!(debug & ZINT_DEBUG_TEST_PERFORMANCE)) { /* -d 256 */
        return;
    }

    for (i = 0; i < data_size; i++) {
        int j;

        if (testContinue(p_ctx, i)) continue;

        diff_encode = diff_buffer = 0;

        for (j = 0; j < TEST_PERF_ITERATIONS; j++) {
            symbol = ZBarcode_Create();
            assert_nonnull(symbol, "Symbol not created\n");

            length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, -1 /*eci*/, data[i].option_1, data[i].option_2, -1, -1 /*output_options*/, data[i].data, -1, debug);

            start = clock();
            ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
            diff_encode += clock() - start;
            assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

            assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d (%s)\n", i, symbol->rows, data[i].expected_rows, data[i].data);
            assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);

            start = clock();
            ret = ZBarcode_Buffer(symbol, 0 /*rotate_angle*/);
            diff_buffer += clock() - start;
            assert_zero(ret, "i:%d ZBarcode_Buffer ret %d != 0 (%s)\n", i, ret, symbol->errtxt);

            ZBarcode_Delete(symbol);
        }

        printf("%s: diff_encode %gms, diff_buffer %gms\n", data[i].comment, diff_encode * 1000.0 / CLOCKS_PER_SEC, diff_buffer * 1000.0 / CLOCKS_PER_SEC);

        total_encode += diff_encode;
        total_buffer += diff_buffer;
    }
    if (p_ctx->index != -1) {
        printf("totals: encode %gms, buffer %gms\n", total_encode * 1000.0 / CLOCKS_PER_SEC, total_buffer * 1000.0 / CLOCKS_PER_SEC);
    }
}

int main(int argc, char *argv[]) {

    testFunction funcs[] = { /* name, func */
        { "test_large", test_large },
        { "test_options", test_options },
        { "test_encode", test_encode },
        { "test_encode_segs", test_encode_segs },
        { "test_fuzz", test_fuzz },
        { "test_perf", test_perf },
    };

    testRun(argc, argv, funcs, ARRAY_SIZE(funcs));

    testReport();

    return 0;
}

/* vim: set ts=4 sw=4 et : */
