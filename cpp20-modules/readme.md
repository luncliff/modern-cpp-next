
### References

* [A Tour of C++ Modules in Visual Studio](https://devblogs.microsoft.com/cppblog/a-tour-of-cpp-modules-in-visual-studio/)
    * [A New Decade of Visual Studio: C++20, Open STL, and More - Marian Luparu & Sy Brand - CppCon 2020](https://youtu.be/Va9-Qe3WzJ8)
* [Practical C++20 Modules and the future of tooling around C++ Modules with Cameron DaCamara](https://www.youtube.com/watch?v=ow2zV0Udd9M)
* [Practical C++ Modules - Boris Kolpackov - CppCon 2019](https://www.youtube.com/watch?v=szHV6RdQdg8)

## How To

### Setup

#### Visual Studio

[Visual Studio 2019 16.8](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes) or [later](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes-preview).

#### Visual Stuido Code

이후의 예제를 위한 [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) Extension을 위한 설정은 아래와 같이 사용합니다.  
자신의 개발환경에 맞게 수정할때는 https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference를 참고하세요.

```json
{
    "configurations": [
        {
            "name": "Windows-x64-Cpp20",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/vcpkg/installed/x64-windows/include"
            ],
            "defines": [
                "_DEBUG", "UNICODE", "_UNICODE"
            ],
            "intelliSenseMode": "msvc-x64",
            "cStandard": "c18",
            "cppStandard": "c++20",
            "compilerArgs": [
                "/W4", "/c++latest", "/utf-8"
            ],
            "windowsSdkVersion": "10.0.17134.0"
        }
    ],
    "version": 4
}
```

### Build

samples.sln 파일을 통해서 예제들을 빌드해볼 수 있습니다.

#### sample_1

> TBA

#### sample_2

> TBA

#### sample_3

> TBA

#### sample_4

> TBA

