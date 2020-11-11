/**
 * @file    print.cpp
 * @brief   implementation for `print.ixx`
 * @note    The following projects use this file: `sample_1.vcproj`, `sample_2.vcproj`
 */
module;
#include <algorithm>
#include <cstdio>
#include <string_view>

module print;

void fwprint(FILE *fout, int argc, wchar_t *argv[]) noexcept {
  fputws(L"args:\n", fout);
  for (auto i = 0; i < argc; ++i) {
    fwprintf(fout, L" - %s\n", argv[i]);
  }
}

void fwprint(FILE *fout, wchar_t *envp[]) noexcept {
  fputws(L"env:\n", fout);
  for (wchar_t **env = envp; *env; ++env) {
    wchar_t *sep = wcsstr(*env, L"=");
    if (sep == nullptr) {
      fwprintf(fout, L" - %s\n", *env);
      continue;
    }
    std::wstring_view key{*env, static_cast<size_t>(std::distance(*env, sep))};
    std::wstring_view value{sep + 1};
    fwprintf(fout, L" - %.*s: '%.*s'\n", key.length(), key.data(),
             value.length(), value.data());
  }
}
