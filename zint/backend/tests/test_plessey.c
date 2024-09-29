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
        int option_2;
        char *pattern;
        int length;
        int ret;
        int expected_rows;
        int expected_width;
    };
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_MSI_PLESSEY, -1, "9", 92, 0, 1, 1111 },
        /*  1*/ { BARCODE_MSI_PLESSEY, -1, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /*  2*/ { BARCODE_MSI_PLESSEY, 1, "9", 92, 0, 1, 1123 }, /* 1 mod-10 check digit */
        /*  3*/ { BARCODE_MSI_PLESSEY, 1, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /*  4*/ { BARCODE_MSI_PLESSEY, 2, "9", 92, 0, 1, 1135 }, /* 2 mod-10 check digits */
        /*  5*/ { BARCODE_MSI_PLESSEY, 2, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /*  6*/ { BARCODE_MSI_PLESSEY, 3, "9", 92, 0, 1, 1123 }, /* 1 mod-11 check digit */
        /*  7*/ { BARCODE_MSI_PLESSEY, 3, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /*  8*/ { BARCODE_MSI_PLESSEY, 3, "4", 92, 0, 1, 1135 }, /* 1 mod-11 double check digit "10" */
        /*  9*/ { BARCODE_MSI_PLESSEY, 3, "4", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /* 10*/ { BARCODE_MSI_PLESSEY, 4, "9", 92, 0, 1, 1135 }, /* 1 mod-11 and 1 mod-10 check digit */
        /* 11*/ { BARCODE_MSI_PLESSEY, 4, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /* 12*/ { BARCODE_MSI_PLESSEY, 4, "4", 92, 0, 1, 1147 }, /* 1 mod-11 double check digit "10" and 1 mod-10 check digit */
        /* 13*/ { BARCODE_MSI_PLESSEY, 4, "4", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /* 14*/ { BARCODE_MSI_PLESSEY, 5, "9", 92, 0, 1, 1123 }, /* 1 NCR mod-11 check digit */
        /* 15*/ { BARCODE_MSI_PLESSEY, 5, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /* 16*/ { BARCODE_MSI_PLESSEY, 6, "9", 92, 0, 1, 1135 }, /* 1 NCR mod-11 and 1 mod-10 check digit */
        /* 17*/ { BARCODE_MSI_PLESSEY, 6, "9", 93, ZINT_ERROR_TOO_LONG, -1, -1 },
        /* 18*/ { BARCODE_PLESSEY, -1, "A", 67, 0, 1, 1139 },
        /* 19*/ { BARCODE_PLESSEY, -1, "A", 68, ZINT_ERROR_TOO_LONG, -1, -1 },
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

        testUtilStrCpyRepeat(data_buf, data[i].pattern, data[i].length);
        assert_equal(data[i].length, (int) strlen(data_buf), "i:%d length %d != strlen(data_buf) %d\n", i, data[i].length, (int) strlen(data_buf));

        length = testUtilSetSymbol(symbol, data[i].symbology, -1 /*input_mode*/, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data_buf, data[i].length, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data_buf, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (ret < ZINT_ERROR) {
            assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d\n", i, symbol->rows, data[i].expected_rows);
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
        int option_2;
        char *data;

        char *expected;
    };
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_MSI_PLESSEY, -1, "1234567", "1234567" },
        /*  1*/ { BARCODE_MSI_PLESSEY, 0, "1234567", "1234567" },
        /*  2*/ { BARCODE_MSI_PLESSEY, 1, "1234567", "12345674" },
        /*  3*/ { BARCODE_MSI_PLESSEY, 1 + 10, "1234567", "1234567" },
        /*  4*/ { BARCODE_MSI_PLESSEY, 1, "9999999999", "99999999990" },
        /*  5*/ { BARCODE_MSI_PLESSEY, 2, "1234567", "123456741" },
        /*  6*/ { BARCODE_MSI_PLESSEY, 2 + 10, "1234567", "1234567" },
        /*  7*/ { BARCODE_MSI_PLESSEY, 2, "9999999999", "999999999900" },
        /*  8*/ { BARCODE_MSI_PLESSEY, 3, "1234567", "12345674" },
        /*  9*/ { BARCODE_MSI_PLESSEY, 3 + 10, "1234567", "1234567" },
        /* 10*/ { BARCODE_MSI_PLESSEY, 3, "9999999999", "99999999995" },
        /* 11*/ { BARCODE_MSI_PLESSEY, 4, "1234567", "123456741" },
        /* 12*/ { BARCODE_MSI_PLESSEY, 4 + 10, "1234567", "1234567" },
        /* 13*/ { BARCODE_MSI_PLESSEY, 4, "9999999999", "999999999959" },
        /* 14*/ { BARCODE_MSI_PLESSEY, 5, "1234567", "12345679" },
        /* 15*/ { BARCODE_MSI_PLESSEY, 5 + 10, "1234567", "1234567" },
        /* 16*/ { BARCODE_MSI_PLESSEY, 5, "9999999999", "999999999910" },
        /* 17*/ { BARCODE_MSI_PLESSEY, 6, "1234567", "123456790" },
        /* 18*/ { BARCODE_MSI_PLESSEY, 6 + 10, "1234567", "1234567" },
        /* 19*/ { BARCODE_MSI_PLESSEY, 6, "9999999999", "9999999999109" },
        /* 20*/ { BARCODE_MSI_PLESSEY, 1, "123456", "1234566" },
        /* 21*/ { BARCODE_MSI_PLESSEY, 2, "123456", "12345666" },
        /* 22*/ { BARCODE_MSI_PLESSEY, 3, "123456", "1234560" },
        /* 23*/ { BARCODE_MSI_PLESSEY, 4, "123456", "12345609" },
        /* 24*/ { BARCODE_MSI_PLESSEY, 3, "2211", "221110" }, /* Mod-11 check digit '10' */
        /* 25*/ { BARCODE_MSI_PLESSEY, 3 + 10, "2211", "2211" }, /* Mod-11 check digit '10' */
        /* 26*/ { BARCODE_MSI_PLESSEY, 4, "2211", "2211100" },
        /* 27*/ { BARCODE_MSI_PLESSEY, 4 + 10, "2211", "2211" },
        /* 28*/ { BARCODE_PLESSEY, -1, "0123456789ABCDEF", "0123456789ABCDEF" },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    testStartSymbol("test_hrt", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, -1 /*input_mode*/, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_zero(ret, "i:%d ZBarcode_Encode ret %d != 0 %s\n", i, ret, symbol->errtxt);

        assert_zero(strcmp((char *) symbol->text, data[i].expected), "i:%d strcmp(%s, %s) != 0\n", i, symbol->text, data[i].expected);

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_input(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int option_2;
        char *data;
        int ret;
        int expected_rows;
        int expected_width;
    };
    /* s/\/\*[ 0-9]*\*\//\=printf("\/\*%3d*\/", line(".") - line("'<")): */
    struct item data[] = {
        /*  0*/ { BARCODE_MSI_PLESSEY, -1, "1", 0, 1, 19 },
        /*  1*/ { BARCODE_MSI_PLESSEY, -1, "A", ZINT_ERROR_INVALID_DATA, -1, -1 },
        /*  2*/ { BARCODE_MSI_PLESSEY, -2, "1", 0, 1, 19 }, /* < 0 ignored */
        /*  3*/ { BARCODE_MSI_PLESSEY, 7, "1", 0, 1, 19 }, /* > 6 ignored */
        /*  4*/ { BARCODE_PLESSEY, -1, "A", 0, 1, 83 },
        /*  5*/ { BARCODE_PLESSEY, -1, "G", ZINT_ERROR_INVALID_DATA, -1, -1 },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    testStartSymbol("test_input", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, -1 /*input_mode*/, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (ret < ZINT_ERROR) {
            assert_equal(symbol->rows, data[i].expected_rows, "i:%d symbol->rows %d != %d\n", i, symbol->rows, data[i].expected_rows);
            assert_equal(symbol->width, data[i].expected_width, "i:%d symbol->width %d != %d\n", i, symbol->width, data[i].expected_width);
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

static void test_encode(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int option_2;
        char *data;
        int ret;

        int expected_rows;
        int expected_width;
        char *comment;
        char *expected;
    };
    struct item data[] = {
        /*  0*/ { BARCODE_MSI_PLESSEY, -1, "1234567890", 0, 1, 127, "Verified manually against tec-it",
                    "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001"
                },
        /*  1*/ { BARCODE_MSI_PLESSEY, 1, "1234567890", 0, 1, 139, "Verified manually against tec-it",
                    "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001001101101001"
                },
        /*  2*/ { BARCODE_MSI_PLESSEY, 2, "1234567890", 0, 1, 151, "Verified manually against tec-it",
                    "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001001101101001001001101001"
                },
        /*  3*/ { BARCODE_MSI_PLESSEY, 3, "1234567890", 0, 1, 139, "",
                    "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001001101101001"
                },
        /*  4*/ { BARCODE_MSI_PLESSEY, 4, "1234567890", 0, 1, 151, "",
                    "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001001101101001001001101001"
                },
        /*  5*/ { BARCODE_MSI_PLESSEY, 5, "1234567890", 0, 1, 139, "",
                    "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001001001001001"
                },
        /*  6*/ { BARCODE_MSI_PLESSEY, 6, "1234567890", 0, 1, 151, "",
                   "1101001001001101001001101001001001101101001101001001001101001101001101101001001101101101101001001001101001001101001001001001001001001001001101101101001"
                },
        /*  7*/ { BARCODE_MSI_PLESSEY, 3, "2211", 0, 1, 79, "Produces mod-11 '10' check digit; BWIPP (badmod11)",
                    "1101001001101001001001101001001001001101001001001101001001001101001001001001001"
                },
        /*  8*/ { BARCODE_MSI_PLESSEY, 4, "2211", 0, 1, 91, "BWIPP (badmod11)",
                    "1101001001101001001001101001001001001101001001001101001001001101001001001001001001001001001"
                },
        /*  9*/ { BARCODE_PLESSEY, -1, "0123456789ABCDEF", 0, 1, 323, "",
                    "11101110100011101000100010001000111010001000100010001110100010001110111010001000100010001110100011101000111010001000111011101000111011101110100010001000100011101110100010001110100011101000111011101110100011101000100011101110111010001110111010001110111011101110111011101110111010001000111010001000100010001110001000101110111"
                },
        /* 10*/ { BARCODE_MSI_PLESSEY, 4, "999999999999999999", 0, 1, 247, "Max value (previously); #209 check buffer not overrun",
                    "1101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001101101001001001001001001101001"
                },
    };
    int data_size = ARRAY_SIZE(data);
    int i, length, ret;
    struct zint_symbol *symbol = NULL;

    char escaped[1024];
    char bwipp_buf[4096];
    char bwipp_msg[1024];

    int do_bwipp = (debug & ZINT_DEBUG_TEST_BWIPP) && testUtilHaveGhostscript(); /* Only do BWIPP test if asked, too slow otherwise */

    testStartSymbol("test_encode", &symbol);

    for (i = 0; i < data_size; i++) {

        if (testContinue(p_ctx, i)) continue;

        symbol = ZBarcode_Create();
        assert_nonnull(symbol, "Symbol not created\n");

        length = testUtilSetSymbol(symbol, data[i].symbology, -1 /*input_mode*/, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data[i].data, -1, debug);

        ret = ZBarcode_Encode(symbol, (unsigned char *) data[i].data, length);
        assert_equal(ret, data[i].ret, "i:%d ZBarcode_Encode ret %d != %d (%s)\n", i, ret, data[i].ret, symbol->errtxt);

        if (p_ctx->generate) {
            printf("        /*%3d*/ { %s, %d, \"%s\", %s, %d, %d, \"%s\",\n",
                    i, testUtilBarcodeName(data[i].symbology), data[i].option_2, testUtilEscape(data[i].data, length, escaped, sizeof(escaped)),
                    testUtilErrorName(data[i].ret), symbol->rows, symbol->width, data[i].comment);
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
                    ret = testUtilBwipp(i, symbol, -1, data[i].option_2, -1, data[i].data, length, NULL, bwipp_buf, sizeof(bwipp_buf), NULL);
                    assert_zero(ret, "i:%d %s testUtilBwipp ret %d != 0\n", i, testUtilBarcodeName(symbol->symbology), ret);

                    ret = testUtilBwippCmp(symbol, bwipp_msg, bwipp_buf, data[i].expected);
                    assert_zero(ret, "i:%d %s testUtilBwippCmp %d != 0 %s\n  actual: %s\nexpected: %s\n",
                                   i, testUtilBarcodeName(symbol->symbology), ret, bwipp_msg, bwipp_buf, data[i].expected);
                }
            }
        }

        ZBarcode_Delete(symbol);
    }

    testFinish();
}

#include <time.h>

#define TEST_PERF_ITER_MILLES   5
#define TEST_PERF_ITERATIONS    (TEST_PERF_ITER_MILLES * 1000)
#define TEST_PERF_TIME(arg) ((arg) * 1000.0 / CLOCKS_PER_SEC)

/* Not a real test, just performance indicator */
static void test_perf(const testCtx *const p_ctx) {
    int debug = p_ctx->debug;

    struct item {
        int symbology;
        int option_2;
        char *data;
        int ret;

        int expected_rows;
        int expected_width;
        char *comment;
    };
    struct item data[] = {
        /*  0*/ { BARCODE_PLESSEY, -1, "1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1234567890ABCDEF1", 0, 1, 1107, "PLESSEY 65" },
        /*  1*/ { BARCODE_PLESSEY, -1, "123456ABCD", 0, 1, 227, "PLESSEY 10" },
        /*  2*/ { BARCODE_MSI_PLESSEY, -1, "12345678901234567890123456789012345678901234567890123456789012345", 0, 1, 787, "MSI_PLESSEY 65" },
        /*  3*/ { BARCODE_MSI_PLESSEY, -1, "1234567890", 0, 1, 127, "MSI_PLESSEY 10" },
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

            length = testUtilSetSymbol(symbol, data[i].symbology, DATA_MODE, -1 /*eci*/, -1 /*option_1*/, data[i].option_2, -1, -1 /*output_options*/, data[i].data, -1, debug);

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
        { "test_input", test_input },
        { "test_encode", test_encode },
        { "test_perf", test_perf },
    };

    testRun(argc, argv, funcs, ARRAY_SIZE(funcs));

    testReport();

    return 0;
}

/* vim: set ts=4 sw=4 et : */
