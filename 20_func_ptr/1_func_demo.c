#include <stdlib.h>
#include <stdio.h>

extern void print(int, char);

void test01()
{
    // 先定义一个函数指针
    typedef void(FUNC_TYPE)(int, char);

    // 再赋值
    FUNC_TYPE *ptr = print;

    // 调用
    ptr(0, 'a');
}

void test02()
{
    // 先定义出函数指针类型，再定义函数指针
    typedef void (*FUNC_TYPE)(int, char);

    FUNC_TYPE ptr = print;
    ptr(3, 'b');
}

void test03()
{
    // 直接定义函数指针变量， 这个比较少
    void (*ptr)(int, char) = print;
    ptr(4, 'l');
}

void test04()
{
    // 函数指针数组
    void (*func_array[3])(int, char);
    func_array[0] = print;
    func_array[1] = print;
    func_array[2] = print;
    for (int idx = 0; idx < 3; idx++)
    {
        func_array[idx](idx * 10, idx + 56);
    }
}

int main()
{
    test01();
    test02();
    test03();
    test04();
    return EXIT_SUCCESS;
}

void print(int a, char b)
{
    printf("hello %d in %c world!\n", a, b);
}