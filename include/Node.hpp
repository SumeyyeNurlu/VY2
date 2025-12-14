#ifndef NODE_HPP
#define NODE_HPP
using namespace std;
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int veri) {
        data = veri;
        left = nullptr;
        right = nullptr;
    }
};

#endif