# Primitive cmake for MSVC, for static lib
# Produces gs1-syntax-engine\src\c-lib\build\Release\gs1encoders.lib if invoked as e.g.
#   cmake -A WIN32 -G "Visual Studio 17 2022" -B build
#   cmake --build build --config Release
# vim: set ts=4 sw=4 et :

cmake_minimum_required(VERSION 3.10)
project(gs1encoders)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif()

set(gs1encoders_SRCS 
    ai.c
    dl.c
    gs1encoders.c
    scandata.c
    syn.c
    syntax/gs1syntaxdictionary.c
    syntax/lint_couponcode.c
    syntax/lint_couponposoffer.c
    syntax/lint_cset39.c
    syntax/lint_cset64.c
    syntax/lint_cset82.c
    syntax/lint_csetnumeric.c
    syntax/lint_csumalpha.c
    syntax/lint_csum.c
    syntax/lint_gcppos1.c
    syntax/lint_gcppos2.c
    syntax/lint_hasnondigit.c
    syntax/lint_hh.c
    syntax/lint_hhmi.c
    syntax/lint_hyphen.c
    syntax/lint_iban.c
    syntax/lint_importeridx.c
    syntax/lint_iso3166999.c
    syntax/lint_iso3166alpha2.c
    syntax/lint_iso3166.c
    syntax/lint_iso4217.c
    syntax/lint_iso5218.c
    syntax/lint_latitude.c
    syntax/lint_longitude.c
    syntax/lint_mediatype.c
    syntax/lint_mi.c
    syntax/lint_nonzero.c
    syntax/lint_nozeroprefix.c
    syntax/lint_packagetype.c
    syntax/lint_pcenc.c
    syntax/lint_pieceoftotal.c
    syntax/lint_posinseqslash.c
    syntax/lint_ss.c
    syntax/lint__stubs.c
    syntax/lint_winding.c
    syntax/lint_yesno.c
    syntax/lint_yymmd0.c
    syntax/lint_yymmdd.c
    syntax/lint_yyyymmd0.c
    syntax/lint_yyyymmdd.c
    syntax/lint_zero.c
)

add_library(gs1encoders STATIC ${gs1encoders_SRCS})
target_compile_definitions(gs1encoders PRIVATE GS1_LINTER_ERR_STR_EN)

if(MSVC)
    target_compile_definitions(gs1encoders PRIVATE _CRT_SECURE_NO_DEPRECATE)
    target_compile_definitions(gs1encoders PRIVATE _CRT_SECURE_NO_WARNINGS)

    target_compile_options(gs1encoders PRIVATE -MD)
endif()
