
# C++ Modules with Clang-9

이번 글에서는 Clang-9를 사용하여 C++ Modules(이하 Modules)를 어떻게 체험해볼 수 있는지 간단히 짚어보고자 합니다.

### When we use `module`

우선 매우 간단한 코드부터 시작해보겠습니다.
`module`의 이름으로는 `.`으로 접합된 단어를 사용할 수 있습니다. 각 단어에는 통상적인 C++에서의 이름처럼 알파벳과 숫자들을 사용합니다.
`namespace std`와 마찬가지로, `std.*`는 표준 모듈들을 위해 예약되어 있습니다.

아래 코드에서 `module`을 2개 확인할 수 있는데, 이들은 모두 `module`을 **구성**하는 내용입니다. 자세한 내용은 잠시 후 설명하겠습니다.

```cpp hl_lines="2 5"
// module_empty.cpp
module;
#include <unistd.h>

module next;
module :Private;
```

첫번째 *이름없는* 모듈은 바로 Global Module 입니다. 
`main()` 함수가 위치하는 모듈이기도 하며, 이름이 없도록 하여 Modules를 적용하지 않은 코드들도 변경없이 모듈에 속하도록 하는 역할을 합니다. Global namespace와 크게 다른 것이 없다고 생각하셨다면 정답입니다.

두번째로 나오는 `next`와 같이 이름이 주어진 경우, 이후의 소스코드는 이전과는 다른 방식으로 해석하게 됩니다.

이제 아래와 같이 clang-9로 컴파일하여 object파일을 생성하도록 해보겠습니다.
**참고로, 컴파일은 실패합니다.**

```makefile hl_lines="1"
CFLAGS	= -std=c++2a -fmodules-ts

module_empty: module_empty.cpp
	clang-9 $(CFLAGS) $(LDFLAGS) -o module_empty.o -c $?
```

```console
user@host:~/examples$ make module_empty
clang-9 -std=c++2a -fmodules-ts -o module_empty.o -c module_empty.cpp
module_empty.cpp:5:1: error: definition of module 'next' is not available; use -fmodule-file= to specify path to precompiled module interface
module next;
^
1 error generated.
Makefile:5: recipe for target 'module_empty' failed
make: *** [module_empty] Error 1
```

오류 메세지의 내용을 보면 `next`의 정의가 없다는 내용을 확인할 수 있습니다.
동시에 precompiled module interface를 요구하고 있습니다.

### Module Interface Unit

소스코드의 임의 지점에서 `module`을 선언하면, 이후의 내용은 최종적으로 선언한 모듈을 구성하게 됩니다. 
이를 Purview라고 합니다.
위 코드에서 문제가 되는 부분은 **module이 있다는 것만** 선언하고 있다는 것입니다.

컴파일러가 Purview에서 나타난 타입 혹은 함수들로 어떤 `module`의 일부를 구성하기 위해서는, 해당 모듈의 이름이 `export`되어야 하며, 이는 오직 Module Interface Unit에서만 가능합니다.
바로 하나 만들어보도록 하겠습니다.

```cpp hl_lines="6"
/// @see https://en.cppreference.com/w/cpp/preprocessor/replace
#if not defined(__cpp_modules)
#warning "'__cpp_modules' not defined"
#endif
#include <cstdint>
export module next;

/**
 * @brief IP v6 address. 128 bit
 */
export union address_t final {
    uint8_t _u8[16];
    uint16_t _u16[8];
    uint32_t _u32[4];
};

/**
 * @brief IP v6 address + port : 28 byte
 * Values are stored in Host Byte order.
 *
 * @see https://tools.ietf.org/html/rfc5952
 */
export struct endpoint_t final {
    uint16_t family;   // AF_INET6.
    uint16_t port;     // Transport level port number.
    uint32_t flowinfo; // IPv6 flow information.
    address_t addr;    // IPv6 address.
    uint32_t scope_id; // Set of interfaces for a scope.
};

export uint32_t lookup(endpoint_t* base, uint16_t count, //
                       const char* hostname,             //
                       const char* servname) noexcept;

```

가장 중요한 부분은 `export module ...` 입니다. 이 선언은 Primary Module Interface Unit에만 사용될 수 있으며, Primary라는 단어가 말해주듯 오직 하나의 파일에서만 사용할 수 있습니다.

각 컴파일러마다 인터페이스를 위한 파일의 확장자를 다르게 사용하고 있는데, 다행히 Clang은 이를 무시할 수 있도록 허용하고 있습니다.
소스코드로부터 BMI파일을 생성하는 방법은 아래와 같습니다.

```makefile
CFLAGS	= -std=c++2a -fmodules-ts

next.pcm:
	clang-9 $(LDFLAGS) $(CFLAGS) \
		-o next.pcm \
		--precompile -x c++-module module_ifc.cpp
```

```console
user@host:~/examples$ make next.pcm
clang-9  -std=c++2a -fmodules-ts \
        -o next.pcm \
        --precompile -x c++-module module_ifc.cpp
module_ifc.cpp:4:2: warning: "'__cpp_modules' not defined" [-W#warnings]
#warning "'__cpp_modules' not defined"
 ^
1 warning generated.

user@host:~/examples$ ls -al
...
-rwxrwxrwx 1 luncliff luncliff   1298 Jan 10 03:01 Makefile
-rwxrwxrwx 1 luncliff luncliff    947 Jan 10 02:55 module_ifc.cpp
-rwxrwxrwx 1 luncliff luncliff 109988 Jan 10 03:02 next.pcm
```

BMI 파일이 생겼으니, 이를 사용해 다시 컴파일을 시도해보겠습니다.

```makefile hl_lines="11"
CFLAGS	= -std=c++2a -fmodules-ts

next.pcm:
	clang-9 $(LDFLAGS) $(CFLAGS) \
		-o next.pcm \
		--precompile -x c++-module module_ifc.cpp

next_impl_2: module_impl_2.cpp
	make next.pcm
	clang-9 $(CFLAGS) $(LDFLAGS) \
		-fmodule-file=next.pcm \
		-o next_impl_2.o -c $?
	nm ./next_impl_2.o
```
