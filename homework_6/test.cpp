#include <iostream>
#include <cstring>
#include <cmath>
#include <random>
#include <vector>
#include "BST.h"
using namespace std;

class MyData{
private:
    int a, b;

public:
    MyData(int a = 0, int b = 0) : a(a), b(b) {}
    bool operator < (const MyData &rhs) const{
        return a < rhs.a || a == rhs.a && b < rhs.b;
    }
    bool operator > (const MyData &rhs) const{
        return a > rhs.a || a == rhs.a && b > rhs.b;
    }
    bool operator == (const MyData &rhs) const{
        return a == rhs.a && b == rhs.b;
    }

    static bool checkCopy;

    MyData(const MyData &rhs) : a(rhs.a), b(rhs.b) {
        if(checkCopy) cerr << "Warning: element copy happened!" << endl;
    }
    MyData& operator = (const MyData &rhs){
        a = rhs.a;
        b = rhs.b;
        if(checkCopy) cerr << "Warning: element copy happened!" << endl;
        return *this;
    }

    friend ostream& operator << (ostream& out, const MyData &rhs){
        out << "(" << rhs.a << "," << rhs.b << ")";
        return out;
    }
};

bool MyData::checkCopy = false;

class Checker : public BinarySearchTree<int>{
private:
    using BinarySearchTree<int>::root;
    using node = BinarySearchTree<int>::BinaryNode;

public:
    void createChain(int N){
        root = new node(1, nullptr, nullptr);
        root->height = N;
        auto p = root;
        for(int i = 2; i <= N; i++){
            p->right = new node(i, nullptr, nullptr);
            p = p->right;
            p->height = N - i + 1;
        }
    }
};

void testRandomData(){
    const int N = 100;
    vector<MyData> data;
    mt19937 rnd(19260817);
    BinarySearchTree<MyData> bst;
    for(int i = 0; i < N; i++){
        data.emplace_back(rnd(), rnd());
        bst.insert(data[i]);
    }
    MyData::checkCopy = true;
    for(int i = 0; i < N; i++){
        bst.remove(data[i]);
        if(i % 20 == 0) bst.printTree();
    }
    bst.printTree();
}

void testIncreasingData(){
    cout << "------------------------------" << endl;
    const int N = 300000;
    Checker bst;
    bst.createChain(N);
    for(int i = N; i >= 1; i--)
        bst.remove(i);
    bst.printTree();
}

int main(){
    testRandomData();
    testIncreasingData();
    return 0;
}