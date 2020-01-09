
## References

### Papers

* [Working Draft](https://github.com/cplusplus/draft)
    * [N4835](https://github.com/cplusplus/draft/tree/master/papers)

### Web

* https://stackoverflow.com/questions/33307657/how-do-i-use-c-modules-in-clang
* https://vector-of-bool.github.io/2019/03/10/modules-1.html
* https://vector-of-bool.github.io/2019/03/31/modules-2.html
* https://vector-of-bool.github.io/2019/10/07/modules-3.html
* https://quuxplusone.github.io/blog/2019/11/07/modular-hello-world/
* ...

### Video

* [CppCon 2015: Gabriel Dos Reis "Large Scale C++ with Modules: What You Should Know"](https://www.youtube.com/watch?v=RwdQA0pGWa4)
* [CppCon 2018: Nathan Sidwell "C++ Modules"](https://www.youtube.com/watch?v=xi2lTaC5p0I)
* [CppCon 2019: Nathan Sidwell "Converting to C++20 Modules"](https://www.youtube.com/watch?v=KVsWIEw3TTw)
* [CppCon 2019: Gabriel Dos Reis "Programming with C++ Modules: Guide for the Working"](https://www.youtube.com/watch?v=tjSuKOz5HK4)
* ...

# Overview

C++ Modules(이하 Modules)는 이전까지 사용되던 소스코드의 복제가 아니라, **미리 컴파일된 바이너리(Binary Module Interface)를 통해서 선언/정의를 노출하도록 지원하는 것**을 의미합니다.

Modules를 도입하면서 C++ 언어에서 얻고자 하는 것은 **컴파일 모델 개선을 통한 컴파일시간 단축** 이라고 할 수 있습니다.
C 언어의 컴파일 모델, 즉 전처리기-컴파일(어셈블리)-링킹 방식은 소스코드(Translation Unit)의 크기를 크게 키운다는 특징을 가지고 있습니다.
다소 시간이 지난 자료입니다만, [Gabriel Dos Reis의 CppCon 2015 발표를 참고하면 234,276% 라는 보기 (매우) 드문 수치를 확인할 수 있습니다](https://youtu.be/RwdQA0pGWa4?t=155).
오늘날의 C++ 생태계는 많은 Header-Only 라이브러리들을 가지고 있는데, 이로 인해 소스코드의 크기와 더불어 컴파일 시간 역시 크게 길어지고 있습니다.

이런 문제에 대한 잘 알려진 대처법은 [PCH(Pre-Compiled Header)](https://docs.microsoft.com/ko-kr/cpp/build/creating-precompiled-header-files?view=vs-2019)입니다.
Modules는 여기서 '소스코드'를 쓰지 않도록 바꾼 것이라고 생각하시면 됩니다.
전처리기를 통해 헤더 파일을 복사하는 방법 대신, Module 선언이 들어간 소스코드를 컴파일하여 얻은 메타파일을 계속 재사용하는 것이죠.
때문에 Module을 도입하는 과정은 대상 프로젝트의 소스코드 구성과 빌드 절차에 지대한 영향을 줄 수 있습니다.

저희는 컴파일러들의 구현이 가용해짐에 따라 이 부분에 초점을 두고 내용을 보강해나가고자 합니다.
우선, Clang 컴파일러를 사용해서 어떻게 Modules를 사용할 수 있는지 부터 다뤄보겠습니다.
