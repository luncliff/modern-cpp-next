/**
 * @file    print2.cpp
 * @brief   Simple primary module interface unit
 * @note    The following projects use this file: `sample_2.vcproj`
 */
module;
#include <cstdio>

module print;

void fwprint(FILE *fout, int argc, char *argv[]) noexcept {
  fputs("args:\n", fout);
  for (auto i = 0; i < argc; ++i) {
    fprintf(fout, " - %s\n", argv[i]);
  }
}
