
### References

* [Overview of modules in C++](https://docs.microsoft.com/en-us/cpp/cpp/modules-cpp)
* [A Tour of C++ Modules in Visual Studio](https://devblogs.microsoft.com/cppblog/a-tour-of-cpp-modules-in-visual-studio/)
    * [A New Decade of Visual Studio: C++20, Open STL, and More - CppCon 2020](https://youtu.be/Va9-Qe3WzJ8) by Marian Luparu & Sy Brand
* [Practical C++20 Modules and the future of tooling around C++ Modules with Cameron DaCamara](https://www.youtube.com/watch?v=ow2zV0Udd9M)
* [Practical C++ Modules - CppCon 2019](https://www.youtube.com/watch?v=szHV6RdQdg8) by Boris Kolpackov
* [Programming with C++ Modules: Guide for the Working - CppCon 2019](https://www.youtube.com/watch?v=tjSuKOz5HK4) by Gabriel Dos Reis

## How To

### Setup

#### Visual Studio

[Visual Studio 2019 16.8](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes) or [later](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes-preview).

설치가 완료되었다면, "Developer Powershell for VS 2019"를 열어서 실행에 문제가 없는지 확인해야 합니다.

```ps1
MSBuild.exe /version # 2020/11/11
```

일반적으로는 Visual Studio를 열어서 확인할 수 있겠지만, 이 프로젝트의 예제들은 CLI 환경에서도 손쉽게 빌드하도록 관리하려는 목표가 있기 때문에, 이런 확인과정이 필요합니다.

```console
Microsoft (R) Build Engine version 16.9.0-preview-20529-04+ab5acfbe6 for .NET Framework
Copyright (C) Microsoft Corporation. All rights reserved.

16.9.0.52904
```

#### Visual Stuido Code

이후의 예제를 위한 [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) Extension을 위한 설정은 아래와 같이 사용합니다.  
자신의 개발환경에 맞게 수정할때는 [`c_cpp_properties.json` reference](https://code.visualstudio.com/docs/cpp/c-cpp-properties-schema-reference)를 참고하세요. 이 기능을 처음 사용하신다면 [C/C++ for Visual Studio Code](https://code.visualstudio.com/docs/languages/cpp#_hello-world-tutorials)부터 시작하는것을 권장합니다.

```json
{
    "configurations": [
        {
            "name": "Windows-x64-Debug",
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
                "/W4", "/utf-8", "/c++latest", "/EHsc", "/MDd"
            ],
            "windowsSdkVersion": "10.0.17134.0"
        }
    ],
    "version": 4
}
```

가장 기본적인 옵션만 사용했는데, [Overview of modules in C++](https://docs.microsoft.com/en-us/cpp/cpp/modules-cpp)에서 언급한것과 다르게 `/experimental:module`가 빠져있습니다.  
설명글을 읽는 습관을 가지지 않은 개발자라면 _나중에서야_ 이 문제를 발견했을텐데, [RTFM](http://readthefuckingmanual.com/)을 항상 마음에 새기는 착한 개발자가 되어주세요. (제발!)

### Build

samples.sln 파일을 통해서 예제들을 빌드해볼 수 있습니다.  
아래의 예제들은, "Add References"를 사용하지 않았지만 암묵적인 의존성을 가지는 경우가 있기 때문에, **순서대로** 빌드하셔야 합니다.

#### sample_1

우선 [A Tour of C++ Modules in Visual Studio](https://devblogs.microsoft.com/cppblog/a-tour-of-cpp-modules-in-visual-studio/)에서 설명한 예시 코드를 조금 변형해서 실행해볼겁니다.

```ps1
MSBuild sample_1.vcxproj /p:verbosity=verbose 
```

#### sample_2

sample_1은 실행 프로그램(exe)을 생성하는데, 이번엔 정적 라이브러리(lib)를 만들면 어떤 것들이 바뀌게 되는지 확인해봅시다.  
컴파일러를 호출하는 명령이 어떻게 바뀌었는지 유심히 살펴볼 필요가 있습니다.

```ps1
MSBuild sample_2.vcxproj /p:verbosity=verbose 
```

#### sample_3

sample_1.cpp을 그대로 재사용하지만, sample_2 프로젝트를 참조합니다. 그러면 sample_3는 sample_2와 링킹되겠군요.  
sample_2와 sample_3 사이에 어떤 파일들이 공유되었는지 확인해보시기 바랍니다.

```ps1
MSBuild sample_3.vcxproj /p:verbosity=verbose 
```

#### sample_4

sample_2 에서 IFC 파일이 생성되었는데, 이걸 vcxproj 간에 참조(Add References)없이 사용해보고 싶습니다.  
컴파일러/링커에 어떤 인자(argument)가 추가되어야하는지 알아보겠습니다.

```ps1
MSBuild sample_4.vcxproj /p:verbosity=verbose 
```

