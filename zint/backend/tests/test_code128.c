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

/* Note BARCODE_GS1_128, BARCODE_EAN14, BARCODE_NVE18 also tested in test_gs1.c */

#include "testcommon.h"

static void test_large(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int output_options;
        char *pattern;
        int length;
        int ret;
        int expected_width;
    };
    /*
       é U+00E9 (\351, 233), UTF-8 C3A9, CodeB-only extended ASCII
    */
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_CODE128, -1, "A", 99, 0, 1124 },
        /*  1*/ { BARCODE_CODE128, -1, "A", 100, ZINT_ERROR_TOO_LONG, -1 },
        /*  2*/ { BARCODE_CODE128, -1, "A", 257, ZINT_ERROR_TOO_LONG, -1 },
        /*  3*/ { BARCODE_CODE128, READER_INIT, "A", 99, 0, 1135 },
        /*  4*/ { BARCODE_CODE128, READER_INIT, "A", 100, ZINT_ERROR_TOO_LONG, -1 },
        /*  5*/ { BARCODE_CODE128, READER_INIT, "A", 257, ZINT_ERROR_TOO_LONG, -1 },
        /*  6*/ { BARCODE_CODE128, -1, "\351A", 66, 0, 1124 },
        /*  7*/ { BARCODE_CODE128, -1, "\351A", 67, ZINT_ERROR_TOO_LONG, -1 }, /* 67 chars (+ 34 shifts) */
        /*  8*/ { BARCODE_CODE128, -1, "0", 198, 0, 1124 },
        /*  9*/ { BARCODE_CODE128, -1, "0", 199, ZINT_ERROR_TOO_LONG, -1 },
        /* 10*/ { BARCODE_CODE128, -1, "0", 257, ZINT_ERROR_TOO_LONG, -1 },
        /* 11*/ { BARCODE_CODE128AB, -1, "A", 99, 0, 1124 },
        /* 12*/ { BARCODE_CODE128AB, -1, "A", 100, ZINT_ERROR_TOO_LONG, -1 },
        /* 13*/ { BARCODE_CODE128AB, -1, "0", 99, 0, 1124 },
        /* 14*/ { BARCODE_CODE128AB, -1, "0", 100, ZINT_ERROR_TOO_LONG, -1 },
        /* 15*/ { BARCODE_GS1_128, -1, "[90]123456789012345678901234567890[91]1234567890123456789012345678901234567890123456789012345678901234567890[92]1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678", -1, ZINT_WARN_HRT_TRUNCATED, 1135 }, /* 196 nos + 3 FNC1s */
        /* 16*/ { BARCODE_GS1_128, -1, "[90]123456789012345678901234567890[91]1234567890123456789012345678901234567890123456789012345678901234567890[92]12345678901234567890123456789012345678901234567890123456789012345678901234567890123456789", -1, ZINT_ERROR_TOO_LONG, -1 }, /* 196 nos + CodeA + single no. + 3 FNC1s */
        /* 17*/ { BARCODE_GS1_128, -1, "[90]123456789012345678901234567890[91]1234567890123456789012345678901234567890123456789012345678901234567890[92]123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", -1, ZINT_ERROR_TOO_LONG, -1 }, /* 198 nos + 3 FNC1s */
        /* 18*/ { BARCODE_GS1_128, -1, "A", 257, ZINT_ERROR_TOO_LONG, -1 },
        /* 19*/ { BARCODE_EAN14, -1, "1234567890123", -1, 0, 134 },
        /* 20*/ { BARCODE_EAN14, -1, "12345678901234", -1, ZINT_ERROR_TOO_LONG, -1 },
        /* 21*/ { BARCODE_NVE18, -1, "12345678901234567", -1, 0, 156 },
        /* 22*/ { BARCODE_NVE18, -1, "123456789012345678", -1, ZINT_ERROR_TOO_LONG, -1 },
        /* 23*/ { BARCODE_HIBC_128, -1, "1", 110, 0, 684 },
        /* 24*/ { BARCODE_HIBC_128, -1, "1", 111, ZINT_ERROR_TOO_LONG, -1 },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char data_buf[4096];

    testStartSymbol("test_large", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        if (data[i].length != -1) {
            testUtilStrCpyRepeat(data_buf, data[i].pattern, data[i].length);
            assert_equal(data[i].length, (int) strlen(data_buf), "i:%d length %d != strlen(data_buf) %d\n", i, data[i].length, (int) strlen(data_buf));
        } else {
            strcpy(data_buf, data[i].pattern);
        }

        length = testUtilSetSymbol(symbol, data[i].symbology, -1 /*input_mode*/, -1 /*eci*/, -1 /*option_1*/, -1, -1, data[i].output_options, data_buf, data[i].length, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data_buf, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (ret < ZINT_ERROR) {
            assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d\n", i, symbol->width, data[i].expected_width);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_hrt(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int input_mode;
        int option_2;
        char *data;
        int length;

        char *expected;
    };
    /*
       é U+00E9 (\351, 233), UTF-8 C3A9, CodeB-only extended ASCII
    */
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_CODE128, UNICODE_MODE, -1, "1234567890", -1, "1234567890" },
        /*  1*/ { BARCODE_CODE128, UNICODE_MODE, -1, "\000ABC\000DEF\000", 9, " ABC DEF " },
        /*  2*/ { BARCODE_CODE128AB, UNICODE_MODE, -1, "12345\00067890", 11, "12345 67890" },
        /*  3*/ { BARCODE_CODE128, UNICODE_MODE, -1, "12345\01167890\037\177", -1, "12345 67890  " },
        /*  4*/ { BARCODE_CODE128, UNICODE_MODE, -1, "abcdé", -1, "abcdé" },
        /*  5*/ { BARCODE_CODE128, DATA_MODE, -1, "abcd\351", -1, "abcdé" },
        /*  6*/ { BARCODE_CODE128, DATA_MODE, -1, "ab\240cd\351", -1, "ab\302\240cdé" }, /* NBSP */
        /*  7*/ { BARCODE_CODE128, ESCAPE_MODE | EXTRA_ESCAPE_MODE, -1, "\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C1234567890\\^C123456789012345678", -1, "123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678" }, /* Max length 198 + 19 special escapes = 99 + 19*3 = 255 */
        /*  8*/ { BARCODE_CODE128AB, UNICODE_MODE, -1, "abcdé", -1, "abcdé" },
        /*  9*/ { BARCODE_CODE128AB, DATA_MODE, -1, "abcd\351", -1, "abcdé" },
        /* 10*/ { BARCODE_HIBC_128, UNICODE_MODE, -1, "1234567890", -1, "*+12345678900*" },
        /* 11*/ { BARCODE_HIBC_128, UNICODE_MODE, -1, "a99912345", -1, "*+A999123457*" }, /* Converts to upper */
        /* 12*/ { BARCODE_DPD, UNICODE_MODE, -1, "000393206219912345678101040", -1, "0003 932 0621 9912 3456 78 101 040 9" }, /* DPDAPPD 4.0.2 - Illustration 7 */
        /* 13*/ { BARCODE_DPD, UNICODE_MODE, -1, "007110601782532948375101276", -1, "0071 106 0178 2532 9483 75 101 276 X" }, /* DPDAPPD 4.0.2 - Illustration 6, figure's HRT seems incorrect */
        /* 14*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020028101276", -1, "0081 827 0998 0000 0200 28 101 276 B" }, /* DPDPLS Section 4 */
        /* 15*/ { BARCODE_DPD, UNICODE_MODE, -1, "007110601632532948375179276", -1, "0071 106 0163 2532 9483 75 179 276 A" }, /* DPDPLS Section 4.6 */
        /* 16*/ { BARCODE_DPD, UNICODE_MODE, -1, "001990009980000020084109203", -1, "0019 900 0998 0000 0200 84 109 203 1" }, /* DPDPLS Section 5.1 */
        /* 17*/ { BARCODE_DPD, UNICODE_MODE, 1, "007110601632532948375101276", -1, "0071 106 0163 2532 9483 75 101 276 O" }, /* DPDPLS Section 6.1.2 relabel, figure is actually 8.7.2 with mislabelled HRT */
        /* 18*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020029136276", -1, "0081 827 0998 0000 0200 29 136 276 3" }, /* DPDPLS Section 8.1 */
        /* 19*/ { BARCODE_DPD, UNICODE_MODE, -1, "001234509980000020031105276", -1, "0012 345 0998 0000 0200 31 105 276 L" }, /* DPDPLS Section 8.2 */
        /* 20*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020032154276", -1, "0081 827 0998 0000 0200 32 154 276 J" }, /* DPDPLS Section 8.3 */
        /* 21*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020030109276", -1, "0081 827 0998 0000 0200 30 109 276 W" }, /* DPDPLS Section 8.4 */
        /* 22*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020033350276", -1, "0081 827 0998 0000 0200 33 350 276 C" }, /* DPDPLS Section 8.5.1 */
        /* 23*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020034179276", -1, "0081 827 0998 0000 0200 34 179 276 I" }, /* DPDPLS Section 8.5.2 */
        /* 24*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020035225276", -1, "0081 827 0998 0000 0200 35 225 276 H" }, /* DPDPLS Section 8.5.3 */
        /* 25*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020036155276", -1, "0081 827 0998 0000 0200 36 155 276 5" }, /* DPDPLS Section 8.5.4 */
        /* 26*/ { BARCODE_DPD, UNICODE_MODE, -1, "000280009980000020037155056", -1, "0002 800 0998 0000 0200 37 155 056 6" }, /* DPDPLS Section 8.5.5 */
        /* 27*/ { BARCODE_DPD, UNICODE_MODE, -1, "007855009980000020041302840", -1, "0078 550 0998 0000 0200 41 302 840 U" }, /* DPDPLS Section 8.5.6 */
        /* 28*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020042102276", -1, "0081 827 0998 0000 0200 42 102 276 R" }, /* DPDPLS Section 8.6.1 */
        /* 29*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020043113276", -1, "0081 827 0998 0000 0200 43 113 276 Y" }, /* DPDPLS Section 8.7.1 */
        /* 30*/ { BARCODE_DPD, UNICODE_MODE, 1, "006376209980000020044118276", -1, "0063 762 0998 0000 0200 44 118 276 I" }, /* DPDPLS Section 8.7.2 relabel */
        /* 31*/ { BARCODE_DPD, UNICODE_MODE, -1, "007160009980000020050294276", -1, "0071 600 0998 0000 0200 50 294 276 C" }, /* DPDPLS Section 8.8 */
        /* 32*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020045327276", -1, "0081 827 0998 0000 0200 45 327 276 N" }, /* DPDPLS Section 8.9.1 */
        /* 33*/ { BARCODE_DPD, UNICODE_MODE, -1, "006374309980000020047337276", -1, "0063 743 0998 0000 0200 47 337 276 O" }, /* DPDPLS Section 8.9.2 */
        /* 34*/ { BARCODE_DPD, UNICODE_MODE, 1, "006374109980978004757332276", -1, "0063 741 0998 0978 0047 57 332 276 M" }, /* DPDPLS Section 8.9.3 relabel, figure's HRT seems incorrect */
        /* 35*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020051106276", -1, "0081 827 0998 0000 0200 51 106 276 M" }, /* DPDPLS Section 9.1 */
        /* 36*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020052110276", -1, "0081 827 0998 0000 0200 52 110 276 W" }, /* DPDPLS Section 9.2 */
        /* 37*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020053161276", -1, "0081 827 0998 0000 0200 53 161 276 O" }, /* DPDPLS Section 9.3 */
        /* 38*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020054352276", -1, "0081 827 0998 0000 0200 54 352 276 B" }, /* DPDPLS Section 9.4 */
        /* 39*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020055191276", -1, "0081 827 0998 0000 0200 55 191 276 A" }, /* DPDPLS Section 9.5 */
        /* 40*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020056237276", -1, "0081 827 0998 0000 0200 56 237 276 K" }, /* DPDPLS Section 9.6 */
        /* 41*/ { BARCODE_UPU_S10, UNICODE_MODE, -1, "EE876543216CA", -1, "EE 876 543 216 CA" }, /* UPU S10 Annex A */
        /* BARCODE_GS1_128, BARCODE_EAN14, BARCODE_NVE18 hrt tested in test_gs1.c */
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    testStartSymbol("test_hrt", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        memset(symbol->text, 0xDD, sizeof(symbol->text)); /* Detect non-NUL terminated HRT */

        length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data[i].data, data[i].length, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_zero(ret, "i:%d ZBarcode_Encode ret %d != 0 %s\n", i, ret, symbol->errtxt);

        assert_zero(strcmp((char *) symbol->text, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->text, data[i].expected);

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_reader_init(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int input_mode;
        int output_options;
        char *data;
        int ret;
        int expected_rows;
        int expected_width;
        char *expected;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { BARCODE_CODE128, UNICODE_MODE, READER_INIT, "A", 0, 1, 57, "(5) 104 96 33 60 106", "StartA FNC3 A" },
        /*  1*/ { BARCODE_CODE128, UNICODE_MODE, READER_INIT, "12", 0, 1, 68, "(6) 104 96 99 12 22 106", "StartB FNC3 CodeC 12" },
        /*  2*/ { BARCODE_CODE128AB, UNICODE_MODE, READER_INIT, "\0371234", 0, 1, 101, "(9) 103 96 95 17 18 19 20 6 106", "StartA FNC3 US 1 2 3 4" },
        /*  3*/ { BARCODE_GS1_128, GS1_MODE, READER_INIT, "[90]12", 0, 1, 68, "(6) 105 102 90 12 11 106", "StartC FNC1 90 12 (Reader Initialise not supported by GS1 barcodes (use CODE128))" },
        /*  4*/ { BARCODE_EAN14, GS1_MODE, READER_INIT, "12", 0, 1, 134, "(12) 105 102 1 0 0 0 0 0 1 23 12 106", "StartC FNC1 01 00 (5) 01 23 (Reader Initialise not supported by GS1 barcodes (use CODE128))" },
        /*  5*/ { BARCODE_NVE18, GS1_MODE, READER_INIT, "12", 0, 1, 156, "(14) 105 102 0 0 0 0 0 0 0 0 1 23 58 106", "StartC FNC1 00 (8) 01 23 (Reader Initialise not supported by GS1 barcodes (use CODE128))" },
        /*  6*/ { BARCODE_HIBC_128, UNICODE_MODE, READER_INIT, "A", 0, 1, 79, "(7) 104 96 11 33 24 5 106", "StartA FNC3 + A 8 (check) (Not sensible, use CODE128)" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];

    testStartSymbol("test_reader_init", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        symbol->debug = ZINT_DEBUG_TEST; /* Needed to get codeword dump in errtxt */

        length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, -1 /*eci*/, -1 /*option_1*/, -1 /*option_2*/, -1, data[i].output_options, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %s, %s, %s, \"%s\", %s, %d, %d, \"%s\", \"%s\" },\n",
                    i, testUtilBarcodeName(data[i].symbology), testUtilInputModeName(data[i].input_mode), testUtilOutputOptionsName(data[i].output_options),
                    testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->rows, symbol->width, symbol->errtxt, data[i].comment);
        } else {
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d (%s)\n", i, symbol->rows, data[i].expected_rows, data[i].data);
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);
            }
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->errtxt, data[i].expected);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int input_mode;
        char *data;
        int length;
        int ret;
        int expected_width;
        int bwipp_cmp;
        char *expected;
        char *comment;
    };
    /*
       NUL U+0000, CodeA-only
       US U+001F (\037, 31), CodeA-only
       a U+0061 (\141, 97), CodeB-only
       b U+0062 (\142, 98), CodeB-only
       PAD U+0080 (\200, 128), UTF-8 C280 (\302\200), CodeA-only extended ASCII, not in ISO 8859-1
       APC U+009F (\237, 159), UTF-8 C29F, CodeA-only extended ASCII, not in ISO 8859-1
       ß U+00DF (\337, 223), UTF-8 C39F, CodeA and CodeB extended ASCII
       é U+00E9 (\351, 233), UTF-8 C3A9, CodeB-only extended ASCII
    */
    struct item data[] = {
        /*  0*/ { UNICODE_MODE, "\302\200", -1, ZINT_ERROR_INVALID_DATA, 0, 1, "Error 204: Invalid character in input data (ISO/IEC 8859-1 only)", "PAD not in ISO 8859-1" },
        /*  1*/ { DATA_MODE, "\200", -1, 0, 57, 1, "(5) 103 101 64 23 106", "PAD ok using binary" },
        /*  2*/ { UNICODE_MODE, "AIM1234", -1, 0, 101, 1, "(9) 104 33 41 45 99 12 34 87 106", "Example from Annex A.1, check char value 87" },
        /*  3*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B12345\\^C6789", -1, 0, 123, 0, "(11) 104 17 18 19 20 21 99 67 89 11 106", "Ticket #204 ZPL example; BWIPP no manual mode" },
        /*  4*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B12345\\^D6789", -1, 0, 167, 0, "(15) 104 17 18 19 20 21 60 62 36 22 23 24 25 1 106", "Unrecognized extra escape ignored; BWIPP no manual mode" },
        /*  5*/ { UNICODE_MODE | ESCAPE_MODE | EXTRA_ESCAPE_MODE, "\\^B12345\\^D6789", -1, 0, 167, 0, "(15) 104 17 18 19 20 21 60 62 36 22 23 24 25 1 106", "Unrecognized extra escape ignored; BWIPP no manual mode" },
        /*  6*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A\\^B\\^C", -1, ZINT_ERROR_INVALID_DATA, 0, 1, "Error 842: No input data", "" },
        /*  7*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A\\^^B\\^C", -1, 0, 68, 0, "(6) 103 60 62 34 80 106", "BWIPP no manual mode" },
        /*  8*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A\\^B\\^^C", -1, 0, 68, 1, "(6) 104 60 62 35 84 106", "" },
        /*  9*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^^A\\^B\\^^C", -1, 0, 101, 1, "(9) 104 60 62 33 60 62 35 14 106", "" },
        /* 10*/ { UNICODE_MODE | ESCAPE_MODE | EXTRA_ESCAPE_MODE, "\\^^A\\^B\\^^C", -1, 0, 101, 1, "(9) 104 60 62 33 60 62 35 14 106", "" },
        /* 11*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^^A", -1, 0, 68, 1, "(6) 104 60 62 33 78 106", "" },
        /* 12*/ { GS1_MODE, "[90]12", -1, ZINT_ERROR_INVALID_OPTION, 0, 1, "Error 220: Selected symbology does not support GS1 mode", "" },
        /* 13*/ { UNICODE_MODE, "1", -1, 0, 46, 1, "(4) 104 17 18 106", "StartB 1" },
        /* 14*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A1", -1, 0, 46, 0, "(4) 103 17 17 106", "StartA 1; BWIPP no manual mode" },
        /* 15*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^C1", -1, 0, 46, 1, "(4) 104 17 18 106", "StartB 1 (manual C ignored as odd); BWIPP no manual mode" },
        /* 16*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "1\\^A", -1, 0, 46, 1, "(4) 104 17 18 106", "StartB 1 (escape at end ignored); BWIPP no manual mode" },
        /* 17*/ { UNICODE_MODE, "12", -1, 0, 46, 1, "(4) 105 12 14 106", "StartC 12" },
        /* 18*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^C12", -1, 0, 46, 1, "(4) 105 12 14 106", "StartC 12" },
        /* 19*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B12", -1, 0, 57, 0, "(5) 104 17 18 54 106", "StartB 1 2; BWIPP no manual mode" },
        /* 20*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A12", -1, 0, 57, 0, "(5) 103 17 18 53 106", "StartA 1 2; BWIPP no manual mode" },
        /* 21*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A1\\^B2", -1, 0, 68, 0, "(6) 103 17 100 18 65 106", "StartA 1 CodeB 2; BWIPP no manual mode" },
        /* 22*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B1\\^A2", -1, 0, 68, 0, "(6) 104 17 101 18 68 106", "StartB 1 CodeA 2; BWIPP no manual mode" },
        /* 23*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A1\\^C2", -1, 0, 57, 0, "(5) 103 17 18 53 106", "StartA 1 2 (manual C ignored as odd); BWIPP no manual mode" },
        /* 24*/ { UNICODE_MODE, "123", -1, 0, 68, 1, "(6) 104 17 18 19 8 106", "StartB 1 2 3" },
        /* 25*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^A123", -1, 0, 68, 0, "(6) 103 17 18 19 7 106", "StartA 1 2 3; BWIPP no manual mode" },
        /* 26*/ { UNICODE_MODE, "1234", -1, 0, 57, 1, "(5) 105 12 34 82 106", "StartC 12 34" },
        /* 27*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B1234", -1, 0, 79, 0, "(7) 104 17 18 19 20 88 106", "StartB 1 2 3 4; BWIPP no manual mode" },
        /* 28*/ { UNICODE_MODE, "12345", -1, 0, 79, 1, "(7) 105 12 34 100 21 54 106", "StartC 12 34 CodeB 5" },
        /* 29*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "1234\\^A5", -1, 0, 79, 0, "(7) 105 12 34 101 21 57 106", "StartC 12 34 CodeA 5; BWIPP no manual mode" },
        /* 30*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B1\\^C2345", -1, 0, 79, 0, "(7) 104 17 99 23 45 53 106", "StartB 1 CodeC 23 45; BWIPP no manual mode" },
        /* 31*/ { UNICODE_MODE, "\037", -1, 0, 46, 1, "(4) 103 95 95 106", "StartA US" },
        /* 32*/ { UNICODE_MODE, "1\037", -1, 0, 57, 1, "(5) 103 17 95 1 106", "StartA 1 US" },
        /* 33*/ { UNICODE_MODE, "12\037", -1, 0, 68, 1, "(6) 103 17 18 95 29 106", "StartA 1 2 US" },
        /* 34*/ { UNICODE_MODE, "a\037a", -1, 0, 79, 1, "(7) 104 65 98 95 65 86 106", "StartB a Shift US a" },
        /* 35*/ { UNICODE_MODE, "1234\037a", -1, 0, 101, 0, "(9) 105 12 34 101 95 98 65 100 106", "StartC 12 34 CodeA US Shift a; BWIPP different encodation" },
        /* 36*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "1234\037\\^Ba", -1, 0, 101, 1, "(9) 105 12 34 101 95 100 65 7 106", "StartC 12 34 CodeA US CodeB a" },
        /* 37*/ { UNICODE_MODE, "\037AAa\037", -1, 0, 101, 1, "(9) 103 95 33 33 98 65 95 2 106", "StartA US A A Shift a US" },
        /* 38*/ { UNICODE_MODE, "\037AAaa\037", -1, 0, 123, 0, "(11) 103 95 33 33 100 65 65 98 95 40 106", "StartA US A A CodeB a a Shift US; BWIPP different encodation" },
        /* 39*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\037AAaa\\^A\037", -1, 0, 123, 1, "(11) 103 95 33 33 100 65 65 101 95 61 106", "StartA US A A CodeB a a CodeA US" },
        /* 40*/ { UNICODE_MODE, "AAAa12345aAA", -1, 0, 167, 1, "(15) 104 33 33 33 65 17 99 23 45 100 65 33 33 54 106", "StartB A (3) a 1 CodeC 23 45 CodeB a A A" },
        /* 41*/ { UNICODE_MODE, "a\037Aa\037\037a\037aa\037a", -1, 0, 222, 1, "(20) 104 65 98 95 33 65 101 95 95 98 65 95 100 65 65 98 95 65 96 106", "StartB a Shift US A a CodeA US US Shift a US CodeB a a Shift US a" },
        /* 42*/ { UNICODE_MODE, "\000\037ß", 4, 0, 79, 1, "(7) 103 64 95 101 63 88 106", "StartA NUL US FNC4 ß" },
        /* 43*/ { UNICODE_MODE, "\000\037é", 4, 0, 90, 0, "(8) 103 64 95 101 98 73 78 106", "StartA NUL US FNC4 Shift é; BWIPP different encodation (CodeB instead of Shift)" },
        /* 44*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\000\037\\^Bé", 7, 0, 90, 0, "(8) 103 64 95 100 100 73 83 106", "StartA NUL US CodeB FNC4 é; BWIPP different encodation (FNC4 before CodeB)" },
        /* 45*/ { UNICODE_MODE, "\000\037éa", 5, 0, 101, 0, "(9) 103 64 95 100 100 73 65 61 106", "StartA NUL US CodeB FNC4 é a; BWIPP different encodation (FNC4 before CodeB)" },
        /* 46*/ { UNICODE_MODE, "abß", -1, 0, 79, 1, "(7) 104 65 66 100 63 29 106", "StartB a b FNC4 ß" },
        /* 47*/ { DATA_MODE, "\141\142\237", -1, 0, 90, 0, "(8) 104 65 66 100 98 95 26 106", "StartB a b FNC4 Shift APC; BWIPP different encodation" },
        /* 48*/ { DATA_MODE, "\141\142\237\037", -1, 0, 101, 0, "(9) 104 65 66 101 101 95 95 96 106", "StartB a b CodeA FNC4 APC US; BWIPP different encodation" },
        /* 49*/ { UNICODE_MODE, "ééé", -1, 0, 90, 1, "(8) 104 100 100 73 73 73 44 106", "StartB LatchFNC4 é é é" },
        /* 50*/ { UNICODE_MODE, "aééééb", -1, 0, 145, 1, "(13) 104 65 100 73 100 73 100 73 100 73 66 49 106", "StartB a FNC4 é (4) b" },
        /* 51*/ { UNICODE_MODE, "aéééééb", -1, 0, 145, 1, "(13) 104 65 100 100 73 73 73 73 73 100 66 93 106", "StartB a Latch é (5) Shift b" },
        /* 52*/ { UNICODE_MODE, "aééééébc", -1, 0, 167, 1, "(15) 104 65 100 100 73 73 73 73 73 100 66 100 67 40 106", "StartB a Latch é (5) Shift b Shift c" },
        /* 53*/ { UNICODE_MODE, "aééééébcd", -1, 0, 178, 1, "(16) 104 65 100 100 73 73 73 73 73 100 100 66 67 68 66 106", "StartB a Latch é (5) Unlatch b c d" },
        /* 54*/ { UNICODE_MODE, "aééééébcde", -1, 0, 189, 1, "(17) 104 65 100 100 73 73 73 73 73 100 100 66 67 68 69 2 106", "StartB a Latch é (5) Unlatch b c d e" },
        /* 55*/ { UNICODE_MODE, "aééééébcdeé", -1, 0, 211, 0, "(19) 104 65 100 100 73 73 73 73 73 100 100 66 67 68 69 100 73 95 106", "StartB a Latch é (5) Unlatch b c d e FNC4 é; BWIPP different encodation" },
        /* 56*/ { UNICODE_MODE, "aééééébcdeéé", -1, 0, 233, 0, "(21) 104 65 100 100 73 73 73 73 73 100 100 66 67 68 69 100 73 100 73 19 106", "StartB a Latch é (5) Unlatch b c d e FNC4 é (2); BWIPP different encodation" },
        /* 57*/ { UNICODE_MODE, "aééééébcdeééé", -1, 0, 244, 1, "(22) 104 65 100 100 73 73 73 73 73 100 66 100 67 100 68 100 69 73 73 73 83 106", "StartB a Latch é (5) Shift b Shift c Shift d Shift e é (3)" },
        /* 58*/ { UNICODE_MODE, "aééééébcdefééé", -1, 0, 255, 1, "(23) 104 65 100 100 73 73 73 73 73 100 100 66 67 68 69 70 100 100 73 73 73 67 106", "StartB a Latch é (5) Unlatch b c d e f Latch é (3)" },
        /* 59*/ { DATA_MODE, "\200\200\200\200\200\101\060\060\060\060\101\200", -1, 0, 222, 1, "(20) 103 101 101 64 64 64 64 64 101 101 33 99 0 0 101 33 101 64 73 106", "StartA Latch PAD (4) Unlatch A CodeC 00 00 CodeA A FNC4 PAD" },
        /* 60*/ { UNICODE_MODE, "ÁÁÁÁÁÁ99999999999999", -1, 0, 211, 0, "(19) 104 100 100 33 33 33 33 33 33 99 99 99 99 99 99 99 99 63 106", "Okapi code128/extended-mode-exit-before-code-set-c.png (chose different solution); BWIPP different encodation" },
        /* 61*/ { UNICODE_MODE, "ÁÁÁÁÁÁ99999999999999Á", -1, 0, 233, 0, "(21) 104 100 100 33 33 33 33 33 33 99 99 99 99 99 99 99 99 100 33 91 106", "Above with trailing non-shifted (as still latched) extended; BWIPP different encodation" },
        /* 62*/ { DATA_MODE | EXTRA_ESCAPE_MODE, "@g(\302\302\302\302\3025555\302\302\302\302\302\302\302\302", -1, 0, 277, 0, "(25) 104 32 71 8 100 100 34 34 34 34 34 99 55 55 100 34 34 34 34 34 34 34 34 25 106", "Okapi code128/extended-mode-with-short-embedded-code-set-c.png (chose different solution); BWIPP different encodation" },
        /* 63*/ { DATA_MODE | EXTRA_ESCAPE_MODE, "@g(\302\302\302\302\302555555\302\302\302\302\302\302\302", -1, 0, 277, 0, "(25) 104 32 71 8 100 100 34 34 34 34 34 99 55 55 55 100 34 34 34 34 34 34 34 76 106", "Above with extra 55 instead of \xC2; BWIPP different encodation" },
        /* 64*/ { UNICODE_MODE, "ÁÁèÁÁFç7Z", -1, 0, 189, 0, "(17) 104 100 100 33 33 72 33 33 100 38 71 100 100 23 58 95 106", "Okapi code128/extended-mode-shift.png; BWIPP different encodation" },
        /* 65*/ { UNICODE_MODE, "m\nm\nm", -1, 0, 112, 1, "(10) 104 77 98 74 77 98 74 77 11 106", "Okapi code128/code-set-b-a-b-a-b.png" },
        /* 66*/ { UNICODE_MODE, "c\naDEF", -1, 0, 112, 1, "(10) 104 67 98 74 65 36 37 38 75 106", "Okapi bug-36-1.png" },
        /* 67*/ { UNICODE_MODE, "\na\nDEF", -1, 0, 112, 1, "(10) 103 74 98 65 74 36 37 38 90 106", "Okapi bug-36-2.png" },
        /* 68*/ { UNICODE_MODE, "ÿ\012àa\0121\012àAà", -1, 0, 222, 0, "(20) 104 100 95 98 74 100 64 65 98 74 17 98 74 100 64 33 100 64 61 106", "BWIPP different encodation, ShA instead of CodeA" },
        /* 69*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "ÿ\012àa\\^A\0121\012\\^BàAà", -1, 0, 222, 0, "(20) 104 100 95 98 74 100 64 65 101 74 17 74 100 100 64 33 100 64 30 106", "BWIPP different encodation, FNC4 before CodeB" },
        /* 70*/ { UNICODE_MODE, "ÿ1234\012àa\0121\0127890àAàDà\012à", -1, 0, 387, 0, "(35) 104 100 95 99 12 34 101 74 100 100 64 65 98 74 17 98 74 99 78 90 100 100 64 33 100 64", "BWIPP different encodation, CodeA instead of ShA, shorter" },
        /* 71*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "ÿ1234\012à\\^Aa\0121\012\\^C7890\\^BàAàDà\012à", -1, 0, 376, 0, "(34) 104 100 95 99 12 34 101 74 101 98 64 98 65 74 17 74 99 78 90 100 100 64 33 100 64 36", "BWIPP different encodation, FNC4 before CodeB, same width" },
        /* 72*/ { UNICODE_MODE, "yÿ1234\012àa\0121\0127890àAàDà\012à", -1, 0, 398, 0, "(36) 104 89 100 95 99 12 34 101 74 100 100 64 65 98 74 17 98 74 99 78 90 100 100 64 33 100", "BWIPP different encodation, CodeA instead of ShA, shorter" },
        /* 73*/ { UNICODE_MODE, "ÿy1234\012àa\0121\0127890àAàDà\012à", -1, 0, 398, 0, "(36) 104 100 95 89 99 12 34 101 74 100 100 64 65 98 74 17 98 74 99 78 90 100 100 64 33 100", "BWIPP different encodation, CodeA instead of ShA, shorter" },
        /* 74*/ { UNICODE_MODE, "ÿÿ1234\012àa\0121\0127890àAàDà\012à", -1, 0, 409, 0, "(37) 104 100 95 100 95 99 12 34 101 74 100 100 64 65 98 74 17 98 74 99 78 90 100 100 64 33", "BWIPP different encodation, CodeA instead of ShA, shorter" },
        /* 75*/ { UNICODE_MODE, "ÿ12345678\012à12345678abcdef\0121\01223456\012\0127890àAàBCDEFà\012\012à", -1, 0, 684, 0, "(62) 104 100 95 99 12 34 56 78 101 74 101 98 64 99 12 34 56 78 100 65 66 67 68 69 70 98 74", "BWIPP different encodation, CodeA instead of ShA, shorter" },
        /* 76*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^B\\^A12\\^C34\\^A\\^B5\\^C67\\^A\\^B\\^CA\\^B\\^A", -1, 0, 145, 0, "(13) 103 17 18 99 34 100 21 99 67 100 33 69 106", "BWIPP no manual mode" },
        /* 77*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "\\^C1234ABC12\012", -1, 0, 145, 0, "(13) 105 12 34 100 33 34 35 99 12 101 74 36 106", "StartC 12 34 CodeB A B C CodeC 12 CodeA LF; BWIPP no manual mode" },
        /* 78*/ { UNICODE_MODE | EXTRA_ESCAPE_MODE, "A\\^", -1, 0, 68, 1, "(6) 104 33 60 62 31 106", "StartC 12 34 CodeB A B C CodeC 12 CodeA LF" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];
    char cmp_buf[8192];
    char cmp_msg[1024];

    int do_bwipp = (debug & ZINT_DEBUG_TEST_BWIPP) && testUtilHaveGhostscript(); /* Only do BWIPP test if asked, too slow otherwise */
    int do_zxingcpp = (debug & ZINT_DEBUG_TEST_ZXINGCPP) && testUtilHaveZXingCPPDecoder(); /* Only do ZXing-C++ test if asked, too slow otherwise */

    testStartSymbol("test_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        symbol->debug = ZINT_DEBUG_TEST; /* Needed to get codeword dump in errtxt */

        length = testUtilSetSymbol(symbol, BARCODE_CODE128, data[i].input_mode, -1 /*eci*/, -1 /*option_1*/, -1, -1, -1 /*output_options*/, data[i].data, data[i].length, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %s, \"%s\", %d, %s, %d, %d, \"%s\", \"%s\" },\n",
                    i, testUtilInputModeName(data[i].input_mode), testUtilEscape(data[i].data, length, escaped, sizeof(escaped)), data[i].length,
                    testUtilErrorName(ret), symbol->width, data[i].bwipp_cmp, symbol->errtxt, data[i].comment);
        } else {
            assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0 (width %d)\n", i, symbol->errtxt, data[i].expected, symbol->width);
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);

                if (do_bwipp && testUtilCanBwipp(i, symbol, -1, -1, -1, debug)) {
                    if (!data[i].bwipp_cmp) {
                        if (debug & ZINT_DEBUG_TEST_PRINT) printf("i:%d %s not BWIPP compatible (%s)\n", i, testUtilBarcodeName(symbol->symbology), data[i].comment);
                    } else {
                        char modules_dump[4096];
                        assert_notequal(testUtilModulesDump(symbol, modules_dump, sizeof(modules_dump)), -1, "i:%d testUtilModulesDump == -1\n", i);
                        ret = testUtilBwipp(i, symbol, -1, -1, -1, data[i].data, length, NULL, cmp_buf, sizeof(cmp_buf), NULL);
                        assert_zero(ret, "i:%d %s testUtilBwipp ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                        ret = testUtilBwippCmp(symbol, cmp_msg, cmp_buf, modules_dump);
                        assert_zero(ret, "i:%d %s testUtilBwippCmp %d != 0 %s\n  actual: %s\nexpected: %s\n",
                                       i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_buf, modules_dump);
                    }
                }
                if (do_zxingcpp && testUtilCanZXingCPP(i, symbol, data[i].data, length, debug)) {
                    int cmp_len, ret_len;
                    char modules_dump[4096];
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

static void test_gs1_128_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int input_mode;
        char *data;
        int ret;
        int expected_width;
        char *expected;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { GS1_MODE, "[90]1[90]1", 0, 123, "(11) 105 102 90 100 17 102 25 99 1 56 106", "StartC FNC1 90 CodeB 1 FNC1 9" },
        /*  1*/ { GS1_MODE | GS1PARENS_MODE, "(90)1(90)1", 0, 123, "(11) 105 102 90 100 17 102 25 99 1 56 106", "StartC FNC1 90 CodeB 1 FNC1 9" },
        /*  2*/ { GS1_MODE, "[90]1[90]12", 0, 123, "(11) 105 102 90 100 17 99 102 90 12 13 106", "StartC FNC1 90 CodeB 1 CodeC FNC1 90 12" },
        /*  3*/ { GS1_MODE, "[90]1[90]123", 0, 134, "(12) 105 102 90 100 17 102 25 99 1 23 57 106", "StartC FNC1 90 CodeB 1 FNC1 9 CodeC 01 23" },
        /*  4*/ { GS1_MODE, "[90]12[90]1", 0, 123, "(11) 105 102 90 12 102 100 25 99 1 19 106", "StartC FNC1 90 12 FNC1 CodeB 9 CodeC 01" },
        /*  5*/ { GS1_MODE, "[90]12[90]12", 0, 101, "(9) 105 102 90 12 102 90 12 14 106", "StartC FNC1 90 12 FNC1 90 12" },
        /*  6*/ { GS1_MODE, "[90]12[90]123", 0, 134, "(12) 105 102 90 12 102 100 25 99 1 23 20 106", "StartC FNC1 90 12 FNC1 CodeB 9 CodeC 01 23" },
        /*  7*/ { GS1_MODE, "[90]123[90]1", 0, 134, "(12) 105 102 90 12 100 19 102 25 99 1 34 106", "StartC FNC1 90 12 CodeB 3 FNC1 9 CodeC 01" },
        /*  8*/ { GS1_MODE, "[90]123[90]1234", 0, 145, "(13) 105 102 90 12 100 19 99 102 90 12 34 98 106", "StartC FNC1 90 12 CodeB 3 CodeC FNC1 90 12 34" },
        /*  9*/ { GS1_MODE, "[90]1[90]1[90]1", 0, 178, "(16) 105 102 90 100 17 102 25 99 1 102 100 25 99 1 51 106", "StartC FNC1 90 CodeB 1 FNC1 9 CodeC 01 FNC1 CodeB 9 CodeC 01" },
        /* 10*/ { GS1_MODE, "[90]1[90]12[90]1", 0, 178, "(16) 105 102 90 100 17 99 102 90 12 102 100 25 99 1 8 106", "StartC FNC1 90 CodeB 1 CodeC FNC1 90 12 FNC1 CodeB 9 CodeC 01" },
        /* 11*/ { GS1_MODE, "[90]1[90]123[90]1", 0, 189, "(17) 105 102 90 100 17 102 25 99 1 23 102 100 25 99 1 70 106", "StartC FNC1 90 CodeB 1 FNC1 9 CodeC 01 23 FNC1 CodeB 9 CodeC 01" },
        /* 12*/ { GS1_MODE, "[90]12[90]123[90]1", 0, 189, "(17) 105 102 90 12 102 100 25 99 1 23 102 100 25 99 1 33 106", "StartC FNC1 90 12 FNC1 CodeB 9 CodeC 01 23 FNC1 CodeB 9 CodeC 01" },
        /* 13*/ { GS1_MODE, "[90]12[90]123[90]12", 0, 167, "(15) 105 102 90 12 102 100 25 99 1 23 102 90 12 11 106", "StartC FNC1 90 12 FNC1 CodeB 9 CodeC 01 23 FNC1 90 12" },
        /* 14*/ { GS1_MODE, "[90]123[90]1[90]1", 0, 189, "(17) 105 102 90 12 100 19 102 25 99 1 102 100 25 99 1 47 106", "StartC FNC1 90 12 CodeB 3 FNC1 9 CodeC 01 FNC1 CodeB 9 CodeC 01" },
        /* 15*/ { GS1_MODE, "[90]123[90]12[90]1", 0, 189, "(17) 105 102 90 12 100 19 99 102 90 12 102 100 25 99 1 80 106", "StartC FNC1 90 12 CodeB 3 CodeC FNC1 90 12 FNC1 CodeB 9 CodeC 01" },
        /* 16*/ { GS1_MODE, "[90]123[90]123[90]12", 0, 178, "(16) 105 102 90 12 100 19 102 25 99 1 23 102 90 12 47 106", "StartC FNC1 90 12 CodeB 3 FNC1 9 CodeC 01 23 FNC1 90 12" },
        /* 17*/ { GS1_MODE, "[90]123[90]1234[90]1", 0, 200, "(18) 105 102 90 12 100 19 99 102 90 12 34 102 100 25 99 1 26 106", "StartC FNC1 90 12 CodeB 3 CodeC FNC1 90 12 34 FNC1 CodeB 9 CodeC 01" },
        /* 18*/ { GS1_MODE, "[90]123[90]1234[90]123", 0, 211, "(19) 105 102 90 12 100 19 99 102 90 12 34 102 100 25 99 1 23 85 106", "StartC FNC1 90 12 CodeB 3 CodeC FNC1 90 12 34 FNC1 CodeB 9 CodeC 01 23" },
        /* 19*/ { GS1_MODE, "[90]12345[90]1234[90]1", 0, 211, "(19) 105 102 90 12 34 100 21 99 102 90 12 34 102 100 25 99 1 30 106", "StartC FNC1 90 12 34 CodeB 5 CodeC FNC1 90 12 34 FNC1 CodeB 9 CodeC 01" },
        /* 20*/ { GS1_MODE, "[90]1A[90]1", 0, 134, "(12) 104 102 25 16 17 33 102 25 99 1 65 106", "StartB FNC1 9 0 1 A FNC1 9 CodeC 01" },
        /* 21*/ { GS1_MODE, "[90]12A[90]123", 0, 145, "(13) 105 102 90 12 100 33 102 25 99 1 23 25 106", "StartC FNC1 90 12 CodeB A FNC1 9 CodeC 01 23" },
        /* 22*/ { GS1_MODE, "[90]123[90]A234[90]123", 0, 244, "(22) 105 102 90 12 100 19 99 102 90 100 33 18 99 34 102 100 25 99 1 23 37 106", "StartC FNC1 90 12 CodeB 3 CodeC FNC1 90 CodeB A 2 CodeC 34 FNC1 CodeB 9 CodeC 01 23" },
        /* 23*/ { GS1_MODE, "[90]12345A12345A", 0, 178, "(16) 105 102 90 12 34 100 21 33 17 99 23 45 100 33 59 106", "StartC FNC1 90 12 34 CodeB 5 A 1 CodeC 23 45 CodeB A [" },
        /* 24*/ { GS1_MODE, "[01]12345678901231[90]12345678901234567890123456789", 0, 321, "(29) 105 102 1 12 34 56 78 90 12 31 90 12 34 56 78 90 12 34 56 78 90 12 34 56 78 100 25 59", "Max length" },
        /* 25*/ { GS1_MODE, "[01]12345678901231[90]123456789012345678901234567890[91]1", ZINT_WARN_NONCOMPLIANT, 365, "Warning 843: GS1-128 input too long (48 character maximum)", "Over length" },
        /* 26*/ { GS1_MODE, "[90]123456789012345678901234567890[91]1234567890123456789012345678901234567890123456789012345678901234567890[92]12345678901234567890123456789012345678901234567890123456789012345678901234567890[93]1234", ZINT_WARN_HRT_TRUNCATED, 1135, "Warning 844: Human Readable Text truncated", "Max input" },
        /* 27*/ { GS1_MODE, "[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[3100]567890[20]34[20]78", ZINT_WARN_HRT_TRUNCATED, 1135, "Warning 844: Human Readable Text truncated", "HRT truncation warning trumps non-compliant (3100) warning" },
        /* 28*/ { GS1_MODE, "[90]123456789012345678901234567890[91]1234567890123456789012345678901234567890123456789012345678901234567890[92]12345678901234567890123456789012345678901234567890123456789012345678901234567890[93]12345", ZINT_ERROR_TOO_LONG, 0, "Error 344: Input too long (99 symbol character maximum)", "" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];

    testStartSymbol("test_gs1_128_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        memset(symbol->text, 0xDD, sizeof(symbol->text)); /* Detect non-NUL terminated HRT */

        symbol->debug = ZINT_DEBUG_TEST; /* Needed to get codeword dump in errtxt */

        length = testUtilSetSymbol(symbol, BARCODE_GS1_128, data[i].input_mode, -1 /*eci*/, -1 /*option_1*/, -1, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %s, \"%s\", %s, %d, \"%s\", \"%s\" },\n",
                    i, testUtilInputModeName(data[i].input_mode), testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->width, symbol->errtxt, data[i].comment);
        } else {
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);
                if (ret == ZINT_WARN_HRT_TRUNCATED) {
                    assert_nonzero((int) ustrlen(symbol->text) < (int) strlen(data[i].data), "i:%d len symbol->text(%s) %d >= %d (%s) (%s)\n",
                        i, symbol->text, (int) ustrlen(symbol->text), (int) strlen(data[i].data), data[i].data, symbol->errtxt);
                } else {
                    assert_equal((int) ustrlen(symbol->text), (int) strlen(data[i].data), "i:%d len symbol->text(%s) %d != %d (%s, %s) (%s)\n",
                        i, symbol->text, (int) ustrlen(symbol->text), (int) strlen(data[i].data), testUtilErrorName(ret), data[i].data, symbol->errtxt);
                }
            }
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->errtxt, data[i].expected);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_hibc_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        char *data;
        int ret;
        int expected_width;
        char *expected;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { ",", ZINT_ERROR_INVALID_DATA, -1, "Error 203: Invalid character in data (alphanumerics, space and \"-.$/+%\" only)", "" },
        /*  1*/ { "A99912345/$$52001510X3", 0, 255, "(23) 104 11 33 99 99 91 23 45 100 15 4 4 99 52 0 15 10 100 56 19 19 53 106", "Check digit 3" },
        /*  2*/ { "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-. $/+%", 0, 497, "(45) 104 11 99 1 23 45 67 89 100 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51", "Check digit +" },
        /*  3*/ { "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%", 0, 695, "(63) 104 11 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5", "Check digit Q" },
        /*  4*/ { "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%", 0, 1124, "(102) 104 11 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5", "" },
        /*  5*/ { "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%", ZINT_ERROR_TOO_LONG, -1, "Error 341: Input too long (99 symbol character maximum)", "" },
        /*  6*/ { "10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 0, 684, "(62) 104 11 99 10 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0", "Check digit %" },
        /*  7*/ { "09AZ-.19AZ-.29AZ-.39AZ-.49AZ-.59AZ-.69AZ-.79AZ-.89AZ-.99AZ", 0, 695, "(63) 104 11 16 25 33 58 13 14 17 25 33 58 13 14 18 25 33 58 13 14 19 25 33 58 13 14 20 25", "Check digit -" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];

    testStartSymbol("test_hibc_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        symbol->debug = ZINT_DEBUG_TEST; /* Needed to get codeword dump in errtxt */

        length = testUtilSetSymbol(symbol, BARCODE_HIBC_128, UNICODE_MODE, -1 /*eci*/, -1 /*option_1*/, -1, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { \"%s\", %s, %d, \"%s\", \"%s\" },\n",
                    i, testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->width, symbol->errtxt, data[i].comment);
        } else {
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);
            }
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->errtxt, data[i].expected);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_ean14_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        char *data;
        int ret;
        int expected_width;
        char *expected;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { "12345678901234", ZINT_ERROR_TOO_LONG, -1, "Error 347: Input too long (13 character maximum)", "" },
        /*  1*/ { "A", ZINT_ERROR_INVALID_DATA, -1, "Error 348: Invalid character in data (digits only)", "" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];

    testStartSymbol("test_ean14_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        symbol->debug = ZINT_DEBUG_TEST; /* Needed to get codeword dump in errtxt */

        length = testUtilSetSymbol(symbol, BARCODE_EAN14, UNICODE_MODE, -1 /*eci*/, -1 /*option_1*/, -1, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { \"%s\", %s, %d, \"%s\", \"%s\" },\n",
                    i, testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->width, symbol->errtxt, data[i].comment);
        } else {
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);
            }
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->errtxt, data[i].expected);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_dpd_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int option_2;
        int output_options;
        char *data;
        int ret;
        int expected_width;
        float expected_height;
        char *expected;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { -1, -1, "12345678901234567890123456", ZINT_ERROR_TOO_LONG, -1, 0, "Error 349: DPD input wrong length (27 or 28 characters required)", "" },
        /*  1*/ { 1, -1, "12345678901234567890123456", ZINT_ERROR_TOO_LONG, -1, 0, "Error 830: DPD relabel input wrong length (27 characters required)", "" },
        /*  2*/ { -1, -1, "123456789012345678901234567", 0, 211, 50, "(19) 104 5 17 99 23 45 67 89 1 23 45 67 89 1 23 45 67 51 106", "27 chars ok now, ident tag prefixed" },
        /*  3*/ { -1, -1, "%123456789012345678901234567", 0, 211, 50, "(19) 104 5 17 99 23 45 67 89 1 23 45 67 89 1 23 45 67 51 106", "" },
        /*  4*/ { 1, -1, "123456789012345678901234567", 0, 200, 25, "(18) 105 12 34 56 78 90 12 34 56 78 90 12 34 56 100 23 102 106", "27 chars also ok (and necessary) for relabel" },
        /*  5*/ { -1, -1, "12345678901234567890123456789", ZINT_ERROR_TOO_LONG, -1, 0, "Error 349: DPD input wrong length (27 or 28 characters required)", "" },
        /*  6*/ { 1, -1, "1234567890123456789012345678", ZINT_ERROR_TOO_LONG, -1, 0, "Error 830: DPD relabel input wrong length (27 characters required)", "" },
        /*  7*/ { -1, -1, "123456789012345678901234567,", ZINT_ERROR_INVALID_DATA, -1, 0, "Error 299: Invalid character in data (alphanumerics only after first character)", "Alphanumerics only in body" },
        /*  8*/ { -1, -1, "12345678901234567890123456,", ZINT_ERROR_INVALID_DATA, -1, 0, "Error 300: Invalid character in data (alphanumerics only)", "Alphanumerics only in body" },
        /*  9*/ { -1, -1, ",234567890123456789012345678", 0, 211, 50, "(19) 104 12 18 99 34 56 78 90 12 34 56 78 90 12 34 56 78 64 106", "Non-alphanumeric DPD ident tag (Barcode ID) allowed" },
        /* 10*/ { -1, -1, "\037234567890123456789012345678", ZINT_ERROR_INVALID_DATA, -1, 0, "Error 343: Invalid DPD identification tag (first character), ASCII values 32 to 127 only", "Control char <US> as DPD ident tag" },
        /* 11*/ { -1, -1, "é234567890123456789012345678", ZINT_ERROR_INVALID_DATA, -1, 0, "Error 343: Invalid DPD identification tag (first character), ASCII values 32 to 127 only", "Extended ASCII as DPD ident tag" },
        /* 12*/ { -1, -1, "12345678901234567890123456A", ZINT_WARN_NONCOMPLIANT, 222, 50, "Warning 831: Destination Country Code (last 3 characters) should be numeric", "" },
        /* 13*/ { -1, -1, "%12345678901234567890123456A", ZINT_WARN_NONCOMPLIANT, 222, 50, "Warning 831: Destination Country Code (last 3 characters) should be numeric", "" },
        /* 14*/ { 1, -1, "12345678901234567890123456A", ZINT_WARN_NONCOMPLIANT, 200, 25, "Warning 831: Destination Country Code (last 3 characters) should be numeric", "" },
        /* 15*/ { -1, -1, "123456789012345678901234A67", ZINT_WARN_NONCOMPLIANT, 233, 50, "Warning 831: Destination Country Code (last 3 characters) should be numeric", "" },
        /* 16*/ { -1, -1, "%123456789012345678901234A67", ZINT_WARN_NONCOMPLIANT, 233, 50, "Warning 831: Destination Country Code (last 3 characters) should be numeric", "" },
        /* 17*/ { 1, -1, "123456789012345678901234A67", ZINT_WARN_NONCOMPLIANT, 211, 25, "Warning 831: Destination Country Code (last 3 characters) should be numeric", "" },
        /* 18*/ { -1, -1, "12345678901234567890123A567", ZINT_WARN_NONCOMPLIANT, 244, 50, "Warning 832: Service Code (characters 6-4 from end) should be numeric", "" },
        /* 19*/ { -1, -1, "%12345678901234567890123A567", ZINT_WARN_NONCOMPLIANT, 244, 50, "Warning 832: Service Code (characters 6-4 from end) should be numeric", "" },
        /* 20*/ { 1, -1, "12345678901234567890123A567", ZINT_WARN_NONCOMPLIANT, 222, 25, "Warning 832: Service Code (characters 6-4 from end) should be numeric", "" },
        /* 21*/ { -1, -1, "123456789012345678901A34567", ZINT_WARN_NONCOMPLIANT, 244, 50, "Warning 832: Service Code (characters 6-4 from end) should be numeric", "" },
        /* 22*/ { -1, -1, "%123456789012345678901A34567", ZINT_WARN_NONCOMPLIANT, 244, 50, "Warning 832: Service Code (characters 6-4 from end) should be numeric", "" },
        /* 23*/ { 1, -1, "123456789012345678901A34567", ZINT_WARN_NONCOMPLIANT, 222, 25, "Warning 832: Service Code (characters 6-4 from end) should be numeric", "" },
        /* 24*/ { -1, -1, "12345678901234567890A234567", ZINT_WARN_NONCOMPLIANT, 233, 50, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
        /* 25*/ { -1, -1, "%12345678901234567890A234567", ZINT_WARN_NONCOMPLIANT, 233, 50, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
        /* 26*/ { 1, -1, "12345678901234567890A234567", ZINT_WARN_NONCOMPLIANT, 211, 25, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
        /* 27*/ { -1, -1, "12345678901A345678901234567", ZINT_WARN_NONCOMPLIANT, 244, 50, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
        /* 28*/ { -1, -1, "%12345678901A345678901234567", ZINT_WARN_NONCOMPLIANT, 244, 50, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
        /* 29*/ { 1, -1, "12345678901A345678901234567", ZINT_WARN_NONCOMPLIANT, 222, 25, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
        /* 30*/ { 1, COMPLIANT_HEIGHT, "12345678901A345678901234567", ZINT_WARN_NONCOMPLIANT, 222, 33.333332, "Warning 833: Last 10 characters of Tracking Number (characters 16-7 from end) should be numeric", "" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];

    testStartSymbol("test_dpd_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        symbol->debug = ZINT_DEBUG_TEST; /* Needed to get codeword dump in errtxt */

        length = testUtilSetSymbol(symbol, BARCODE_DPD, UNICODE_MODE, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, data[i].output_options, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %d, %s, \"%s\", %s, %d, %.8g, \"%s\", \"%s\" },\n",
                    i, data[i].option_2, testUtilOutputOptionsName(data[i].output_options),
                    testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->width, symbol->height, symbol->errtxt, data[i].comment);
        } else {
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);
                assert_equal(symbol->height, data[i].expected_height, "i:%d symbol->height %.8g != %.8g (%s)\n", i, symbol->height, data[i].expected_height, data[i].data);
            }
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->errtxt, data[i].expected);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_upu_s10_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        char *data;
        int ret;
        int expected_width;
        char *expected;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { "AB123456789ABC", ZINT_ERROR_TOO_LONG, 0, "Error 834: Input must be 12 or 13 characters long", "" },
        /*  1*/ { "AB1234567AB", ZINT_ERROR_TOO_LONG, 0, "Error 834: Input must be 12 or 13 characters long", "" },
        /*  2*/ { "1B123456789AB", ZINT_ERROR_INVALID_DATA, 0, "Error 835: Invalid character in Service Indictor (first 2 characters) (alphabetic only)", "" },
        /*  3*/ { "1B12345678AB", ZINT_ERROR_INVALID_DATA, 0, "Error 835: Invalid character in Service Indictor (first 2 characters) (alphabetic only)", "" },
        /*  4*/ { "A2123456789AB", ZINT_ERROR_INVALID_DATA, 0, "Error 835: Invalid character in Service Indictor (first 2 characters) (alphabetic only)", "" },
        /*  5*/ { "A212345678AB", ZINT_ERROR_INVALID_DATA, 0, "Error 835: Invalid character in Service Indictor (first 2 characters) (alphabetic only)", "" },
        /*  6*/ { "ABX23456789AB", ZINT_ERROR_INVALID_DATA, 0, "Error 836: Invalid character in Serial Number (middle 9 characters) (digits only)", "" },
        /*  7*/ { "AB12345678XAB", ZINT_ERROR_INVALID_DATA, 0, "Error 836: Invalid character in Serial Number (middle 9 characters) (digits only)", "" },
        /*  8*/ { "ABX2345678AB", ZINT_ERROR_INVALID_DATA, 0, "Error 836: Invalid character in Serial Number (middle 8 characters) (digits only)", "" },
        /*  9*/ { "AB1234567XAB", ZINT_ERROR_INVALID_DATA, 0, "Error 836: Invalid character in Serial Number (middle 8 characters) (digits only)", "" },
        /* 10*/ { "AB1234567891B", ZINT_ERROR_INVALID_DATA, 0, "Error 837: Invalid character in Country Code (last 2 characters) (alphabetic only)", "" },
        /* 11*/ { "AB123456781B", ZINT_ERROR_INVALID_DATA, 0, "Error 837: Invalid character in Country Code (last 2 characters) (alphabetic only)", "" },
        /* 12*/ { "AB123456789A2", ZINT_ERROR_INVALID_DATA, 0, "Error 837: Invalid character in Country Code (last 2 characters) (alphabetic only)", "" },
        /* 13*/ { "AB12345678A2", ZINT_ERROR_INVALID_DATA, 0, "Error 837: Invalid character in Country Code (last 2 characters) (alphabetic only)", "" },
        /* 14*/ { "AB123456789AB", ZINT_ERROR_INVALID_CHECK, 0, "Error 838: Invalid check digit '9', expecting '5'", "" },
        /* 15*/ { "JB123456785AB", ZINT_WARN_NONCOMPLIANT, 156, "Warning 839: Invalid Service Indicator (first character should not be any of \"JKSTW\")", "" },
        /* 16*/ { "FB123456785AB", ZINT_WARN_NONCOMPLIANT, 156, "Warning 840: Non-standard Service Indicator (first 2 characters)", "" },
        /* 17*/ { "AB123456785AB", ZINT_WARN_NONCOMPLIANT, 156, "Warning 841: Country code (last two characters) is not ISO 3166-1", "" },
        /* 18*/ { "AB123100000IE", 0, 156, "", "Check digit 10 -> 0" },
        /* 19*/ { "AB000000005IE", 0, 156, "", "Check digit 11 -> 5" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];
    char escaped2[1024];

    testStartSymbol("test_upu_s10_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, BARCODE_UPU_S10, UNICODE_MODE, -1 /*eci*/, -1 /*option_1*/, -1, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { \"%s\", %s, %d, \"%s\", \"%s\" },\n",
                    i, testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->width,
                    testUtilEscape(symbol->errtxt, (int) strlen(symbol->errtxt), escaped2, sizeof(escaped2)), data[i].comment);
        } else {
            if (ret < ZINT_ERROR) {
                assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d (%s)\n", i, symbol->width, data[i].expected_width, data[i].data);
            }
            assert_zero(strcmp(symbol->errtxt, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->errtxt, data[i].expected);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_encode(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int input_mode;
        int option_2;
        char *data;
        int ret;

        int expected_rows;
        int expected_width;
        int bwipp_cmp;
        char *comment;
        char *expected;
    };
    /* BARCODE_GS1_128 examples verified manually against GS1 General Specifications 21.0.1 (GGS) */
    /* BARCODE_DPD examples Specification DPD and primetime Parcel Despatch (DPDAPPD) Version 4.0.2, also
       DPD Parcel Label Specification (DPDPLS) Version 2.4.1 (19.01.2021) */
    struct item data[] = {
        /*  0*/ { BARCODE_CODE128, UNICODE_MODE, -1, "AIM", 0, 1, 68, 1, "ISO/IEC 15417:2007 Figure 1",
                    "11010010000101000110001100010001010111011000101110110001100011101011"
                },
        /*  1*/ { BARCODE_CODE128AB, UNICODE_MODE, -1, "AIM", 0, 1, 68, 1, "128B same",
                    "11010010000101000110001100010001010111011000101110110001100011101011"
                },
        /*  2*/ { BARCODE_CODE128, UNICODE_MODE, -1, "1234567890", 0, 1, 90, 1, "",
                    "110100111001011001110010001011000111000101101100001010011011110110100111100101100011101011"
                },
        /*  3*/ { BARCODE_CODE128AB, UNICODE_MODE, -1, "1234567890", 0, 1, 145, 1, "",
                    "1101001000010011100110110011100101100101110011001001110110111001001100111010011101101110111010011001110010110010011101100101000110001100011101011"
                },
        /*  4*/ { BARCODE_CODE128, DATA_MODE, -1, "\101\102\103\104\105\106\200\200\200\200\200", 0, 1, 178, 1, "",
                    "1101000010010100011000100010110001000100011010110001000100011010001000110001011101011110111010111101010000110010100001100101000011001010000110010100001100110110110001100011101011"
                },
        /*  5*/ { BARCODE_GS1_128, GS1_MODE, -1, "[8018]950110153123456781", 0, 1, 167, 1, "GGS Figure 2.5.2-1",
                    "11010011100111101011101010011110011001110010101111010001100110110011001000100101110011001101100011011101101110101110110001000010110010010111100101111001001100011101011"
                },
        /*  6*/ { BARCODE_GS1_128, GS1_MODE, -1, "[415]5412345678908[3911]710125", 0, 1, 189, 1, "GGS Figure 2.6.6-1 top",
                    "110100111001111010111011000100010111010001101100010001011101101110101110110001000010110011011011110100011001001101000100011000100100100110100001100110110011100101100100001001101100011101011"
                },
        /*  7*/ { BARCODE_GS1_128, GS1_MODE, -1, "[12]010425[8020]ABC123", 0, 1, 189, 1, "GGS Figure 2.6.6-1 bottom",
                    "110100111001111010111010110011100110011011001001000110011100101100101001111001100100111010111101110101000110001000101100010001000110100111001101100111001011001011100110010111001100011101011"
                },
        /*  8*/ { BARCODE_GS1_128, GS1_MODE, -1, "[253]950110153005812345678901", 0, 1, 211, 1, "GGS Figure 2.6.9-1",
                    "1101001110011110101110111001011001101000100011000101110110001001001100110110011011101110110110011001110110001010110011100100010110001110001011011000010100110111101101011110111010011100110101110110001100011101011"
                },
        /*  9*/ { BARCODE_GS1_128, GS1_MODE, -1, "[253]950110153006567890543210987", 0, 1, 211, 1, "GGS Figure 2.6.9-2",
                    "1101001110011110101110111001011001101000100011000101110110001001001100110110011011101110110110011001001011000010000101100110110111101000100110010110001110110111001001100100100011110010100101110011001100011101011"
                },
        /* 10*/ { BARCODE_GS1_128, GS1_MODE, -1, "[253]95011015300657654321", 0, 1, 189, 1, "GGS Figure 2.6.9-3",
                    "110100111001111010111011100101100110100010001100010111011000100100110011011001101110111011011001100100101100001100101000011101011000110001101101011110111010011100110111001001101100011101011"
                },
        /* 11*/ { BARCODE_GS1_128, GS1_MODE, -1, "[253]9501101530065123456", 0, 1, 167, 1, "GGS Figure 2.6.9-4",
                    "11010011100111101011101110010110011010001000110001011101100010010011001101100110111011101101100110010010110000101100111001000101100011100010110100011110101100011101011"
                },
        /* 12*/ { BARCODE_GS1_128, GS1_MODE, -1, "[01]10857674002017[10]1152KMB", 0, 1, 211, 1, "GGS Figure 4.15.1-1",
                    "1101001110011110101110110011011001100100010010011110010110010100001000011001011011001100110010011101001110011011001000100110001001001101110001010111101110101100011101011101100010001011000100111001101100011101011"
                },
        /* 13*/ { BARCODE_GS1_128, GS1_MODE, -1, "[01]09501101530003", 0, 1, 134, 1, "GGS Figure 5.1-3",
                    "11010011100111101011101100110110011001001000110001011101100010010011001101100110111011101101100110010010011000100110100001100011101011"
                },
        /* 14*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]395123451234567895", 0, 1, 156, 1, "GGS Figure 5.4.2-1",
                    "110100111001111010111011011001100110100010001101110100011101101110101110110001011001110010001011000111000101101100001010010111101000101111000101100011101011"
                },
        /* 15*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]006141411234567890", 0, 1, 156, 1, "GGS Figure 6.6.5-1. (and Figures 6.6.5-3 bottom, 6.6.5-4 bottom)",
                    "110100111001111010111011011001100110110011001100100001011000100010110001000101011001110010001011000111000101101100001010011011110110110110110001100011101011"
                },
        /* 16*/ { BARCODE_GS1_128, GS1_MODE, -1, "[403]402621[401]950110153B01001", 0, 1, 266, 0, "GGS Figure 6.6.5-2 top **NOT SAME**, different encodation for zint, BWIPP & standard, same codeword count",
                    "11010011100111101011101100010100010001011000110011001101111000101010111101110100111001101011101111011110101110110001010001100101110011000101110110001001001100110110011011101110101111011101000101100010011101100101110111101100100010011001101100101001111001100011101011"
                },
        /* 17*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]395011015300000011", 0, 1, 156, 1, "GGS Figure 6.6.5-2 bottom",
                    "110100111001111010111011011001100110100010001100010111011000100100110011011001101110111011011001100110110011001101100110011000100100100011101101100011101011"
                },
        /* 18*/ { BARCODE_GS1_128, GS1_MODE, -1, "[420]45458", 0, 1, 90, 1, "GGS Figure 6.6.5-3 top",
                    "110100111001111010111010110111000100100011001110101100011101100010111100100101100011101011"
                },
        /* 19*/ { BARCODE_GS1_128, GS1_MODE, -1, "[02]00614141000418[15]210228[10]451214[37]20", 0, 1, 255, 1, "GGS Figure 6.6.5-4 top",
                    "110100111001111010111011001100110110110011001100100001011000100010110001000101101100110010010001100110011100101011100110011011100100110011001101110011010011001000100101110110001011001110010011001110111101011101000110100011001001110100011110101100011101011"
                },
        /* 20*/ { BARCODE_GS1_128, GS1_MODE, -1, "[420]87109", 0, 1, 90, 1, "GGS Figure 6.6.5-5 top",
                    "110100111001111010111010110111000100011001001001101000011001001000111001001101100011101011"
                },
        /* 21*/ { BARCODE_GS1_128, GS1_MODE, -1, "[90]1528", 0, 1, 79, 1, "GGS Figure 6.6.5-5 middle",
                    "1101001110011110101110110111101101011100110011100110100111001100101100011101011"
                },
        /* 22*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]000521775138957172", 0, 1, 156, 1, "GGS Figure 6.6.5-5 bottom",
                    "110100111001111010111011011001100110110011001000100110011011100100111101110101101110100010001100010101111010001001101000010011000010110011011001100011101011"
                },
        /* 23*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]395011010013000129", 0, 1, 156, 1, "GGS Figure 6.6.5-6",
                    "110100111001111010111011011001100110100010001100010111011000100100110011011001101100110010011011100110110011001100110110011100110010111101101101100011101011"
                },
        /* 24*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]395011010013000129", 0, 1, 156, 1, "GGS Figure 6.6.5-6",
                    "110100111001111010111011011001100110100010001100010111011000100100110011011001101100110010011011100110110011001100110110011100110010111101101101100011101011"
                },
        /* 25*/ { BARCODE_GS1_128, GS1_MODE, -1, "[401]931234518430GR", 0, 1, 167, 1, "GGS Figure 6.6.5-7 top",
                    "11010011100111101011101100010100011001011100110110001101110110111010111011000110011100101011000111010111101110100111011001101000100011000101110100110111001100011101011"
                },
        /* 26*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]093123450000000012", 0, 1, 156, 1, "GGS Figure 6.6.5-7 bottom",
                    "110100111001111010111011011001100110010010001101100011011101101110101110110001101100110011011001100110110011001101100110010110011100110111010001100011101011"
                },
        /* 27*/ { BARCODE_GS1_128, GS1_MODE, -1, "[01]95012345678903", 0, 1, 134, 1, "GGS Figure 7.8.5.1-1 1st",
                    "11010011100111101011101100110110010111101000110011011001110110111010111011000100001011001101101111010010011000110110001101100011101011"
                },
        /* 28*/ { BARCODE_GS1_128, GS1_MODE, -1, "[3102]000400", 0, 1, 101, 1, "GGS Figure 7.8.5.1-1 2nd",
                    "11010011100111101011101101100011011001100110110110011001001000110011011001100110110111101100011101011"
                },
        /* 29*/ { BARCODE_GS1_128, GS1_MODE, -1, "[01]95012345678903[3102]000400", 0, 1, 189, 1, "GGS Figure 7.8.5.1-2",
                    "110100111001111010111011001101100101111010001100110110011101101110101110110001000010110011011011110100100110001101100011011001100110110110011001001000110011011001100100100110001100011101011"
                },
        /* 30*/ { BARCODE_GS1_128, GS1_MODE, -1, "[8005]000365", 0, 1, 101, 1, "GGS Figure 7.8.5.2-1 1st",
                    "11010011100111101011101010011110010001001100110110011001001001100010010110000100100001101100011101011"
                },
        /* 31*/ { BARCODE_GS1_128, GS1_MODE, -1, "[10]123456", 0, 1, 90, 1, "GGS Figure 7.8.5.2-1 2nd",
                    "110100111001111010111011001000100101100111001000101100011100010110110010000101100011101011"
                },
        /* 32*/ { BARCODE_GS1_128, GS1_MODE, -1, "[8005]000365[10]123456", 0, 1, 156, 1, "GGS Figure 7.8.5.2-2",
                    "110100111001111010111010100111100100010011001101100110010010011000100101100001111010111011001000100101100111001000101100011100010110101100001001100011101011"
                },
        /* 33*/ { BARCODE_GS1_128, GS1_MODE, -1, "[403]27653113+99000900090010", 0, 1, 222, 1, "DHL Leitcode https://www.dhl.de/de/geschaeftskunden/paket/information/geschaeftskunden/abrechnung/leitcodierung.html",
                    "110100111001111010111011000101000110001101101100101000011011101110110001001001011110111011001011100110001001001011101111010111011110110110011001100100100011011001100110010010001101100110011001000100110001000101100011101011"
                },
        /* 34*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]340433935039756615", 0, 1, 156, 1, "DHL Identcode https://www.dhl.de/de/geschaeftskunden/paket/information/geschaeftskunden/abrechnung/leitcodierung.html",
                    "110100111001111010111011011001100100010110001001000110010100011000101000111101100010111011010001000110000100101001000011010111001100100111001101100011101011"
                },
        /* 35*/ { BARCODE_GS1_128, GS1_MODE, -1, "[90]ABCDEfGHI", 0, 1, 167, 0, "Shift A; BWIPP different encodation, same codeword count",
                    "11010010000111101011101110010110010011101100101000110001000101100010001000110101100010001000110100010110000100110100010001100010100011000100010110010011101100011101011"
                },
        /* 36*/ { BARCODE_GS1_128, GS1_MODE, -1, "[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[00]345678901234567890[3100]121212[20]34[20]78", ZINT_WARN_HRT_TRUNCATED, 1, 1135, 1, "Max length",
                    "1101001110011110101110110110011001000101100011100010110110000101001101111011010110011100100010110001110001011011000010100110111101101101100110010001011000111000101101100001010011011110110101100111001000101100011100010110110000101001101111011011011001100100010110001110001011011000010100110111101101011001110010001011000111000101101100001010011011110110110110011001000101100011100010110110000101001101111011010110011100100010110001110001011011000010100110111101101101100110010001011000111000101101100001010011011110110101100111001000101100011100010110110000101001101111011011011001100100010110001110001011011000010100110111101101011001110010001011000111000101101100001010011011110110110110011001000101100011100010110110000101001101111011010110011100100010110001110001011011000010100110111101101101100110010001011000111000101101100001010011011110110101100111001000101100011100010110110000101001101111011011011001100100010110001110001011011000010100110111101101011001110010001011000111000101101100001010011011110110110110001101101100110010110011100101100111001011001110011001001110100010110001100100111011000010100100100110001100011101011"
                },
        /* 37*/ { BARCODE_EAN14, GS1_MODE, -1, "4070071967072", 0, 1, 134, 1, "Verified manually against TEC-IT",
                    "11010011100111101011101100110110011000101000101100001001001100010011001011100100001011001001100010011001001110110111001001100011101011"
                },
        /* 38*/ { BARCODE_NVE18, GS1_MODE, -1, "40700000071967072", 0, 1, 156, 1, "Verified manually against TEC-IT",
                    "110100111001111010111011011001100110001010001011000010011011001100110110011001001100010011001011100100001011001001100010011001001110110111011101100011101011"
                },
        /* 39*/ { BARCODE_HIBC_128, UNICODE_MODE, -1, "83278F8G9H0J2G", 0, 1, 211, 1, "ANSI/HIBC 2.6 - 2016 Section 4.1, not same, uses different encoding (eg begins StartA instead of StartB)",
                    "1101001000011000100100111010011001011101111011000110110110000101001011110111010001100010111010011001101000100011100101100110001010001001110110010110111000110011100101101000100010001001100111101010001100011101011"
                },
        /* 40*/ { BARCODE_HIBC_128, UNICODE_MODE, -1, "A123BJC5D6E71", 0, 1, 200, 1, "ANSI/HIBC 2.6 - 2016 Figure 1, same",
                    "11010010000110001001001010001100010011100110110011100101100101110010001011000101101110001000100011011011100100101100010001100111010010001101000111011011101001110011011010001000110001101101100011101011"
                },
        /* 41*/ { BARCODE_HIBC_128, UNICODE_MODE, -1, "$$52001510X3G", 0, 1, 178, 1, "ANSI/HIBC 2.6 - 2016 Figure 5, same",
                    "1101001000011000100100100100011001001000110010111011110110111000101101100110010111001100110010001001011110111011100010110110010111001101000100010110001000100011110101100011101011"
                },
        /* 42*/ { BARCODE_DPD, UNICODE_MODE, -1, "%000393206219912345678101040", 0, 1, 211, 1, "DPDAPPD 4.0.2 - Illustrations 2, 7, 8, same; NOTE: correct HRT given by Illustration 7 only",
                    "1101001000010001001100100111011001011101111011011001100110100010001100011011010011001000110111001001011101111010110011100100010110001110001011011000010100110010001001100100010011000101000101011110001100011101011"
                },
        /* 43*/ { BARCODE_DPD, UNICODE_MODE, -1, "%007110601782532948375101276", 0, 1, 211, 1, "DPDAPPD 4.0.2 - Illustration 6 **NOT SAME** HRT incorrect, also uses CodeA and inefficient encoding; verified against TEC-IT",
                    "1101001000010001001100100111011001011101111010011000100110001001001001100100011001101100110000101001110010110011000110110100010111101011110010011000010010110010001001011001110011001010000100010111101100011101011"
                },
        /* 44*/ { BARCODE_DPD, UNICODE_MODE, -1, "0123456789012345678901234567", 0, 1, 189, 1, "DPDAPPD 4.0.2 - Illustration 9, same (allowing for literal HRT)",
                    "110100111001100110110011101101110101110110001000010110011011011110110011011001110110111010111011000100001011001101101111011001101100111011011101011101100010000101100101011110001100011101011"
                },
        /* 45*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020028101276", 0, 1, 211, 1, "DPDPLS Section 4, **NOT SAME**, figure switches to CodeC after 1st char (%), zint after 2nd (0)",
                    "1101001000010001001100100111011001011101111010001100100110011100101110110010011001001000111101000101101100110011011001100110011001101101100110011100110100110010001001011001110011001010000101011110001100011101011"
                },
        /* 46*/ { BARCODE_DPD, UNICODE_MODE, -1, "007110601632532948375179276", 0, 1, 211, 1, "DPDPLS Section 4.6, **NOT SAME**, figure StartA & switches as above, zint StartB & switches as above",
                    "1101001000010001001100100111011001011101111010011000100110001001001001100100011001101100101001100001110010110011000110110100010111101011110010011000010010100111001101010111100011001010000101100010001100011101011"
                },
        /* 47*/ { BARCODE_DPD, UNICODE_MODE, -1, "001990009980000020084109203", 0, 1, 211, 1, "DPDPLS Section 5.1, **NOT SAME**, figure switches to CodeC after 1st char (%), zint after 2nd (0)",
                    "1101001000010001001100100111011001011101111011001101100101110111101101100110011001001000111101000101101100110011011001100110011001101101100110010011110100110010001001010111100010010011000100011010001100011101011"
                },
        /* 48*/ { BARCODE_DPD, UNICODE_MODE, -1, "008182709980000020029136276", 0, 1, 211, 1, "DPDPLS Section 6.1, **NOT SAME**, as above",
                    "1101001000010001001100100111011001011101111010001100100110011100101110110010011001001000111101000101101100110011011001100110011001101101100110011100110010100110111001111000101011001010000100001101001100011101011"
                },
        /* 49*/ { BARCODE_DPD, UNICODE_MODE, 1, "006376209980000020044118276", 0, 1, 200, 1, "DPDPLS Section 8.7.2 relabel, **NOT SAME**, figure begins StartB then immediate CodeC, zint just StartC",
                    "11010011100110110011001010011000011001010000110010011101011101111010100111100110110011001101100110011001001110100100011001100010001011001110010111011001001011110111011001110100110111011101100011101011"
                },
        /* 50*/ { BARCODE_UPU_S10, UNICODE_MODE, -1, "EE876543216CA", 0, 1, 156, 1, "",
                    "110100100001000110100010001101000111010011001011101111011001010000111010110001100011011010011101100101111011101000100011010100011000111000101101100011101011"
                },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];
    char cmp_buf[8192];
    char cmp_msg[1024];

    int do_bwipp = (debug & ZINT_DEBUG_TEST_BWIPP) && testUtilHaveGhostscript(); /* Only do BWIPP test if asked, too slow otherwise */
    int do_zxingcpp = (debug & ZINT_DEBUG_TEST_ZXINGCPP) && testUtilHaveZXingCPPDecoder(); /* Only do ZXing-C++ test if asked, too slow otherwise */

    testStartSymbol("test_encode", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, data[i].input_mode, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %s, %s, %d, \"%s\", %s, %d, %d, %d, \"%s\",\n",
                    i, testUtilBarcodeName(data[i].symbology), testUtilInputModeName(data[i].input_mode), data[i].option_2,
                    testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
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

                if (do_bwipp && testUtilCanBwipp(i, symbol, -1, data[i].option_2, -1, debug)) {
                    if (!data[i].bwipp_cmp) {
                        if (debug & ZINT_DEBUG_TEST_PRINT) printf("i:%d %s not BWIPP compatible (%s)\n", i, testUtilBarcodeName(symbol->symbology), data[i].comment);
                    } else {
                        ret = testUtilBwipp(i, symbol, -1, data[i].option_2, -1, data[i].data, length, NULL, cmp_buf, sizeof(cmp_buf), NULL);
                        assert_zero(ret, "i:%d %s testUtilBwipp ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                        ret = testUtilBwippCmp(symbol, cmp_msg, cmp_buf, data[i].expected);
                        assert_zero(ret, "i:%d %s testUtilBwippCmp %d != 0 %s\n  actual: %s\nexpected: %s\n",
                                       i, testUtilBarcodeName(symbol->symbology), ret, cmp_msg, cmp_buf, data[i].expected);
                    }
                }
                if (do_zxingcpp && testUtilCanZXingCPP(i, symbol, data[i].data, length, debug)) {
                    int cmp_len, ret_len;
                    char modules_dump[17984 + 1];
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

#include <time.h>

#define TEST_PERF_ITER_MILLES   10
#define TEST_PERF_ITERATIONS    (TEST_PERF_ITER_MILLES * 1000)
#define TEST_PERF_TIME(arg)     (((arg) * 1000.0) / CLOCKS_PER_SEC)

/* Not a real test, just performance indicator */
static void test_perf(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        char *data;
        int ret;

        int expected_rows;
        int expected_width;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { BARCODE_CODE128, "123456ABCD123456ABCD123456ABCD123456ABCD123456ABCD123456ABCD", 0, 1, 618, "CODE128 60" },
        /*  1*/ { BARCODE_CODE128, "123456ABCD", 0, 1, 123, "CODE128 10" },
        /*  2*/ { BARCODE_GS1_128, "[01]09501101530003", 0, 1, 134, "GS1_128 (01)" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol;

    clock_t start;
    clock_t total_create = 0, total_encode = 0, total_buffer = 0, total_buf_inter = 0, total_print = 0;
    clock_t diff_create, diff_encode, diff_buffer, diff_buf_inter, diff_print;
    int comment_max = 0;

    if (!(debug & ZINT_DEBUG_TEST_PERFORMANCE)) { /* -d 256 */
        return;
    }

    for (i = 0; i < data_size; i++) if ((int) strlen(data[i].comment) > comment_max) comment_max = (int) strlen(data[i].comment);

    printf("Iterations %d\n", TEST_PERF_ITERATIONS);

    for (i = 0; i < data_size; i++) {
        int j;

        if (testContinue(p_ctx, i)) continue;

        diff_create = diff_encode = diff_buffer = diff_buf_inter = diff_print = 0;

        for (j = 0; j < TEST_PERF_ITERATIONS; j++) {
            start = clock();
            symbol = ZBarcode_Create();
            diff_create += clock() - start;
            assert_nonnull(symbol, "Symbol not created\n");

            length = testUtilSetSymbol(symbol, data[i].symbology, DATA_MODE, -1 /*eci*/, -1 /*option_1*/, -1, -1, -1 /*output_options*/, data[i].data, -1, debug);

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

            symbol->output_options |= OUT_BUFFER_INTERMEDIATE;
            start = clock();
            ret = ZBarcode_Buffer(symbol, 0 /*rotate_angle*/);
            diff_buf_inter += clock() - start;
            assert_zero(ret, "i:%d ZBarcode_Buffer OUT_BUFFER_INTERMEDIATE ret %d != 0 (%s)\n", i, ret, symbol->errtxt);
            symbol->output_options &= ~OUT_BUFFER_INTERMEDIATE; /* Undo */

            start = clock();
            ret = ZBarcode_Print(symbol, 0 /*rotate_angle*/);
            diff_print += clock() - start;
            assert_zero(ret, "i:%d ZBarcode_Print ret %d != 0 (%s)\n", i, ret, symbol->errtxt);
            assert_zero(testUtilRemove(symbol->outfile), "i:%d testUtilRemove(%s) != 0\n", i, symbol->outfile);

            ZBarcode_Delete(symbol);
        }

        printf("%*s: encode % 8gms, buffer % 8gms, buf_inter % 8gms, print % 8gms, create % 8gms\n", comment_max, data[i].comment,
                TEST_PERF_TIME(diff_encode), TEST_PERF_TIME(diff_buffer), TEST_PERF_TIME(diff_buf_inter), TEST_PERF_TIME(diff_print), TEST_PERF_TIME(diff_create));

        total_create += diff_create;
        total_encode += diff_encode;
        total_buffer += diff_buffer;
        total_buf_inter += diff_buf_inter;
        total_print += diff_print;
    }
    if (p_ctx->index == -1) {
        printf("%*s: encode % 8gms, buffer % 8gms, buf_inter % 8gms, print % 8gms, create % 8gms\n", comment_max, "totals",
                TEST_PERF_TIME(total_encode), TEST_PERF_TIME(total_buffer), TEST_PERF_TIME(total_buf_inter), TEST_PERF_TIME(total_print), TEST_PERF_TIME(total_create));
    }
}

int main(int argc, char *argv[]) {

    testFunction funcs[] = { /* name, func */
        { "test_large", test_large },
        { "test_hrt", test_hrt },
        { "test_reader_init", test_reader_init },
        { "test_input", test_input },
        { "test_gs1_128_input", test_gs1_128_input },
        { "test_hibc_input", test_hibc_input },
        { "test_ean14_input", test_ean14_input },
        { "test_dpd_input", test_dpd_input },
        { "test_upu_s10_input", test_upu_s10_input },
        { "test_encode", test_encode },
        { "test_perf", test_perf },
    };

    testRun(argc, argv, funcs, ARRAY_SIZE(funcs));

    testReport();

    return 0;
}

/* vim: set ts=4 sw=4 et : */
