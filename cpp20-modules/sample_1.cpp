/**
 * @file    sample_1.cpp
 * @brief   build/link 'print' module with main (global module fragment)
 * 
 * @note    The following projects use this file: `sample_1.vcproj`, `sample_3.vcproj`
 * @see     https://docs.microsoft.com/en-us/cpp/c-language/using-wmain?view=msvc-160
 */
#include <clocale>
#include <cstdio>

import print; // @see print.ixx

#if __has_include(<Windows.h>)
int wmain(int argc, wchar_t *argv[], wchar_t *envp[]) {
  setlocale(LC_ALL, ".65001");
  fwprint(stdout, argc, argv);
  fwprint(stdout, envp);
  return 0;
}
#else
int main(int argc, char *argv[]) {
  fwprint(stdout, argc, argv);
  return 0;
}
#endif
