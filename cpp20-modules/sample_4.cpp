/**
 * @file    sample_4.cpp
 * @brief   link with 'print' module with main (global module fragment)
 * 
 * @note    The following projects use this file: `sample_4.vcproj`
 */
#include <cstdio>

import print; // @see print.ixx

int main(int argc, char *argv[]) {
  fwprint(stdout, argc, argv);
  return 0;
}
