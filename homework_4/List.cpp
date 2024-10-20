#include "List.h"
#include <iostream>
#include <string>

template <typename Object>
void printList(const List<Object>& lst, const std::string& msg) {
    std::cout << msg;
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

int main() {
    // 创建一个空的整数列表
    List<int> lst;
    std::cout << "创建了一个空的列表。\n";
    std::cout << "列表是否为空: " << std::boolalpha << lst.empty() << "\n";
    std::cout << "列表大小: " << lst.size() << "\n\n";

    // 测试 push_back 操作
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    printList(lst, "在尾部插入 10, 20, 30 后: ");

    // 测试 push_front 操作
    lst.push_front(5);
    lst.push_front(2);
    printList(lst, "在头部插入 5, 2 后: ");

    // 测试 front 和 back 访问
    std::cout << "第一个元素: " << lst.front() << "\n";
    std::cout << "最后一个元素: " << lst.back() << "\n\n";

    // 测试 pop_front 操作
    lst.pop_front();
    printList(lst, "执行 pop_front 后: ");
    std::cout << "第一个元素: " << lst.front() << "\n\n";

    // 测试 pop_back 操作
    lst.pop_back();
    printList(lst, "执行 pop_back 后: ");
    std::cout << "最后一个元素: " << lst.back() << "\n\n";

    // 测试 insert 操作
    auto it = lst.begin();
    ++it; // 指向第二个元素
    lst.insert(it, 15);
    printList(lst, "在第二个位置插入 15 后: ");

    // 测试 erase 操作
    it = lst.begin();
    ++it; // 指向 15
    lst.erase(it);
    printList(lst, "删除第二个位置的元素 (15) 后: ");

    // 测试 clear 操作
    lst.clear();
    std::cout << "执行 clear 后:\n";
    std::cout << "列表是否为空: " << lst.empty() << "\n";
    std::cout << "列表大小: " << lst.size() << "\n\n";

    // 测试初始化列表构造函数
    List<std::string> strList = {"苹果", "香蕉", "樱桃"};
    printList(strList, "初始化字符串列表: ");

    // 测试拷贝构造函数
    List<std::string> copiedList = strList;
    printList(copiedList, "拷贝后的字符串列表: ");

    // 测试赋值运算符
    List<std::string> assignedList;
    assignedList = strList;
    printList(assignedList, "赋值后的字符串列表: ");

    // 测试移动构造函数
    List<std::string> movedList = std::move(strList);
    printList(movedList, "移动后的字符串列表: ");
    std::cout << "原始字符串列表在移动后大小: " << strList.size() << "\n\n";

    // 测试移动赋值运算符
    List<std::string> anotherList;
    anotherList.push_back("枣");
    anotherList.push_back("接骨木莓");
    printList(anotherList, "移动赋值前的另一个字符串列表: ");
    anotherList = std::move(movedList);
    printList(anotherList, "移动赋值后的另一个字符串列表: ");
    std::cout << "被移动的字符串列表在移动赋值后大小: " << movedList.size() << "\n";

    return 0;
}