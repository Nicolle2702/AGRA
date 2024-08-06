/*
    NICOLLE RUIZ QUINTERO
    8974036

    REFERENCIAS:
    LIBRO DE PROFESORCITO: ESTRUCTURA DE DATOS YOAN PINZON, CAPTIULO: TREE DATA STRUCTURES

*/


#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
    char item;
    TreeNode* izquirda;
    TreeNode* derecha;
    TreeNode(char c) : item(c), izquirda(nullptr), derecha(nullptr) {}
};

TreeNode* buildTree(string& textocam) {
    stack<TreeNode*> nodoStack;
    for (char c : textocam) {
        if (islower(c)) {
            nodoStack.push(new TreeNode(c));
        } else {
            // Operador: crear un nodo
            TreeNode* opizquirda = nodoStack.top();
            nodoStack.pop();
            TreeNode* opderecha = nodoStack.top();
            nodoStack.pop();
            TreeNode* newNode = new TreeNode(c);
            newNode->izquirda = opizquirda;
            newNode->derecha = opderecha;
            nodoStack.push(newNode);
        }
    }
    return nodoStack.top();
}

string invertirString(string& str) {
    string resultado;
    for (int i = str.size() - 1; i >= 0; --i) {
        resultado += str[i];
    }
    return resultado;
}


string levelOrder(TreeNode* raiz) {
    string ans="";
    if (!raiz) {
        ans;
    }

    queue<TreeNode*> q;
    string x;
    string y;
    q.push(raiz);

    while (!q.empty()) {
        TreeNode* recor = q.front();
        q.pop();
        x=recor->item;
        if (recor->derecha) q.push(recor->derecha);
        if (recor->izquirda) q.push(recor->izquirda);
        y.append(x);
    }
    return y;
}

int main() {
    int T;
    cin >> T;
    string y;
    string z;
    while (T--) {
        string textoCam;
        cin >> textoCam;
        TreeNode* raiz = buildTree(textoCam);
        y=levelOrder(raiz);
        z=invertirString(y);
        cout<<z;
        cout << endl;
    }
    return 0;
}

