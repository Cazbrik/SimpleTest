# SimpleTest

A simple library inspired by [MinUnit](https://github.com/siu/minunit) for my personal projet, this doesn't attempt to provide all the functionalities that one can expect from frameworks like JUnit (for Java)or CppUnit (for C++). But only the functionalities that I think can be useful for my projet.

## _Installation_ :

Use the makefile provided in the projet to create the _.a_ or _.so_ file and include it when compile the sources files to test :

```sh
git clone https://github.com/Cazbrik/SimpleTest.git test
cd test
make
```

You may also have to include the header (_src/test.h_) file to avoid the warning during the compilation.

## _Usage_ :

Use the macro _TEST_ to set up a test, then call the function that will be created :

```C
#include <stdio.h>
#include "src/test.h"

TEST(sample, {
    printf("sample test");
})

int main(void){
    sample();
}
```

The _TEST_ macro use two other macro which are _BEFORE_TEST_ and _AFTER_TEST_ theses can be used to initialize and dispose some parameters. A function can be mocked by using  macro before the _TEST_ one :

```C
#include <stdio.h>
#include "src/test.h"

static int counter = 36;

#undef BEFORE_TEST
#define BEFORE_TEST counter = 12
TEST(sample, {
    printf("%d\n", counter);
})

#define my_func(X) printf(X)
TEST(sample2, my_func("mocked !\n"))
#undef my_func

int main(void){
    sample();
    sample2();
}
```


