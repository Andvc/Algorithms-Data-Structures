#include "LinkedList.h"

int main(){

//SingleLinkedList<int>a;
SingleLinkedList<int> a{1,2,3,4,5};
int a_get = a.getCurrentVal();
std::cout << a_get << std::endl;//测试【取值】操作是否正确,包括可能的空链表测试(//部分),每种情况9分

//SingleLinkedList<char> b;
SingleLinkedList<char> b{'a','c','e'};
b.setCurrentVal('g');
b.printList();//测试【定义值】操作是否正确,包括可能的空链表测试(//部分),每种情况9分

SingleLinkedList<char> e;
std::cout << b.isEmpty()<< ""<<e.isEmpty()<<std::endl;//测试【空链表判断】操作是否正确,18分

SingleLinkedList<double>c1;
SingleLinkedList<double>c2{1.5,2.0,9.0,4.7};
SingleLinkedList<double>c3;
c3 = c2;
c1.insert(3.0);c2.insert(8.8);
bool f_c3 = c3.find(2.0);
c3.insert(8.8);c1.printList();c2.printList();c3.printList();//测试【插入】操作是否正确，每种情况6分

e.remove();
c1.remove();
bool f=c2.find(9.0);
c2.remove();
e.printList();
c1.printList();
c2.printList();//测试【删除】操作是否正确，每种情况6分
return 0;
}