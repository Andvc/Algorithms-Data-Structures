// Chicken.cpp

#include <iostream>
#include <cstring>

class Chicken
{
private:
    int age;
    char *name;

public:
    // 默认构造函数
    Chicken() : age(0), name(nullptr) {}

    // 参数化构造函数，仅设置年龄
    Chicken(int _age) : age(_age), name(nullptr) {}

    // 参数化构造函数，设置年龄和名称
    Chicken(int _age, const char *_name) : age(_age)
    {
        if (_name)
        {
            size_t len = std::strlen(_name) + 1;
            name = new char[len];
            std::memcpy(name, _name, len);
        }
        else
        {
            name = nullptr;
        }
    }

    // 复制构造函数，实现深度复制
    Chicken(const Chicken &other) : age(other.age)
    {
        if (other.name)
        {
            size_t len = std::strlen(other.name) + 1;
            name = new char[len];
            std::memcpy(name, other.name, len);
        }
        else
        {
            name = nullptr;
        }
    }

    // 赋值运算符，实现深度赋值和链式赋值
    Chicken& operator=(const Chicken &other)
    {
        if (this != &other) // 防止自我赋值
        {
            // 释放当前对象的资源
            delete[] name;

            // 复制年龄
            age = other.age;

            // 深度复制名称
            if (other.name)
            {
                size_t len = std::strlen(other.name) + 1;
                name = new char[len];
                std::memcpy(name, other.name, len);
            }
            else
            {
                name = nullptr;
            }
        }
        return *this; // 支持链式赋值
    }

    // 析构函数，释放动态分配的内存
    ~Chicken()
    {
        delete[] name;
    }

    // 设置年龄
    void setAge(int _age)
    {
        age = _age;
    }

    // 设置名称，支持深度赋值
    void setName(const char *_name)
    {
        // 释放之前的名称内存
        delete[] name;

        if (_name)
        {
            size_t len = std::strlen(_name) + 1;
            name = new char[len];
            std::memcpy(name, _name, len);
        }
        else
        {
            name = nullptr;
        }
    }

    // 获取名称，返回 const 指针
    const char *getName() const
    {
        return name;
    }

    // 获取年龄，返回 const 引用
    const int &getAge() const
    {
        return age;
    }
};
int main()
{
    auto print = [](const Chicken &c){
        std::cout << "Hi, everyone! My name is " << c.getName()
                  << ", I am " << c.getAge() << " years old." << std::endl;
    };

    Chicken c(24, "Kunkun");
    print(c);

    Chicken d;
    d = c;
    print(d); // 测试赋值运算符

    Chicken a = c;
    print(a); // 测试复制构造函数

    c.setName("Xukun Cai");
    print(c);
    print(a);
    print(d); // 测试深度复制

    Chicken b;
    b = d = c;
    print(b);
    print(d); // 测试连续赋值

    return 0;
}
