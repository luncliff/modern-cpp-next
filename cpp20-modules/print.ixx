/**
 * @file    print.ixx
 * @brief   Simple primary module interface unit
 * @note    The following projects use this file: `sample_1.vcproj`, `sample_2.vcproj`
 */
module;
#include <cstdio>

export module print;

export void fwprint(FILE *fout, int argc, wchar_t *argv[]) noexcept;
export void fwprint(FILE *fout, wchar_t *envp[]) noexcept;
export void fwprint(FILE *fout, int argc, char *argv[]) noexcept;
