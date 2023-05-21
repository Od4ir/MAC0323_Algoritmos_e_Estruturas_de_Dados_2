#include <iostream>
#include <vector>
using namespace std;

const int MAX_KEYS = 2; // Número máximo de chaves em um nó
const int MAX_CHILDREN = MAX_KEYS + 1; // Número máximo de filhos em um nó

struct Node {
    vector<int> keys; // Chaves armazenadas no nó
    vector<Node*> children; // Ponteiros para os filhos do nó
};

// Função para criar um novo nó
Node* createNode() {
    Node* newNode = new Node;
    newNode->keys.clear();
    newNode->children.clear();
    return newNode;
}

// Função para dividir um nó em dois
void splitNode(Node* parent, int index) {
    Node* leftChild = parent->children[index];
    Node* rightChild = createNode();

    // Transferir a segunda metade das chaves do nó dividido para o novo nó à direita
    for (int i = MAX_KEYS / 2 + 1; i < leftChild->keys.size(); i++) {
        rightChild->keys.push_back(leftChild->keys[i]);
    }

    // Transferir a segunda metade dos filhos do nó dividido para o novo nó à direita
    if (!leftChild->children.empty()) {
        for (int i = MAX_CHILDREN / 2; i < leftChild->children.size(); i++) {
            rightChild->children.push_back(leftChild->children[i]);
        }
    }

    // Remover as chaves e os filhos transferidos do nó dividido
    leftChild->keys.resize(MAX_KEYS / 2 + 1);
    leftChild->children.resize(MAX_CHILDREN / 2 + 1);

    // Inserir a chave central do nó dividido no pai
    parent->keys.insert(parent->keys.begin() + index, leftChild->keys[MAX_KEYS / 2]);
    
    // Inserir o novo filho à direita no pai
    parent->children.insert(parent->children.begin() + index + 1, rightChild);
}

// Função para inserir uma chave na árvore B
void insertKey(Node*& root, int key) {
    if (root == nullptr) {
        root = createNode();
        root->keys.push_back(key);
        return;
    }

    if (root->children.empty()) {
        // O nó é uma folha, apenas insira a chave no lugar certo
        root->keys.insert(lower_bound(root->keys.begin(), root->keys.end(), key), key);
        
        if (root->keys.size() > MAX_KEYS) {
            // O nó excedeu a capacidade máxima, dividir o nó
            Node* newRoot = createNode();
            newRoot->children.push_back(root);
            splitNode(newRoot, 0);
            root = newRoot;
        }
    } else {
        // O nó não é uma folha, encontre o filho apropriado para a chave e insira recursivamente
        int i = upper_bound(root->keys.begin(), root->keys.end(), key) - root->keys.begin();
        insertKey(root->children[i], key);
        
        if (root->children[i]->keys.size() > MAX_KEYS) {
            // O filho excedeu a capacidade máxima, dividir o filho
            splitNode(root, i);
        }
    }
}

// Função para imprimir a árvore B
void printTree(Node* root, int level = 0) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < root->keys.size(); i++) {
        if (!root->children.empty()) {
            printTree(root->children[i], level + 1);
        }
        for (int j = 0; j < level; j++) {
            cout << "  ";
        }
        cout << root->keys[i] << endl;
    }

    if (!root->children.empty()) {
        printTree(root->children.back(), level + 1);
    }
}

int main() {
    Node* root = nullptr;

    insertKey(root, 10);
    insertKey(root, 20);
    insertKey(root, 30);
    insertKey(root, 5);
    insertKey(root, 15);
    insertKey(root, 25);
    insertKey(root, 35);

    cout << "Árvore B:" << endl;
    printTree(root);

    return 0;
}
