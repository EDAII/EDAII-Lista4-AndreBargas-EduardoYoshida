#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))

using namespace std;

struct avl_node{
    int data;
    struct avl_node *left;
    struct avl_node *right;
}*root;


class avlTree{

public:
    int height(avl_node *);
    int diff(avl_node *);

    avl_node *rr_rotation(avl_node *);
    avl_node *ll_rotation(avl_node *);
    avl_node *lr_rotation(avl_node *);
    avl_node *rl_rotation(avl_node *);
    avl_node* balance(avl_node *);
    avl_node* insert(avl_node *, int );

    void display(avl_node *, int);
    void preorder(avl_node *);
    int search(avl_node *, int num);
    avlTree()
    {
        root = NULL;
    }
};


int main(){

    int choice, item;
    int resultado;

    avlTree avl;

    while (1){
        cout<<"\n---------------------"<<endl;
        cout<<"Árvore AVL"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Inserir Elemento"<<endl;
        cout<<"2.Imprimir Árvore AVL"<<endl;
        cout<<"3.PreOrder traversal"<<endl;
        cout<<"4.Busca"<<endl;
        cout<<"Selecione uma opção: ";
        cin>>choice;

        switch(choice){
        case 1:
            cout<<"Valor para ser inserido: ";
            cin>>item;
            root = avl.insert(root, item);
            break;

        case 2:
            if (root == NULL){
                cout<<"Árvore Vazia"<<endl;
                continue;
            }
            cout<<"Árvore AVL balanceada:"<<endl;
            avl.display(root, 1);
            break;

        case 3:
            cout<<"Preordem Traversal:"<<endl;
            avl.preorder(root);
            cout<<endl;
            break;

        case 5:
            cout<<"Pesquisar: ";
            cin>>item;
            resultado = avl.search(root, item);
            if(resultado == -1){
              cout << "Valor não encontrado ou árvore vazia";
            }else{
              cout<<"Valor Encontrado: "<< avl.search(root, item)<<endl;
            }
            break;
        case 4:
            exit(1);
            break;

        default:
            cout<<"Escolha inválida"<<endl;
        }
    }
    return 0;
}

int avlTree::height(avl_node *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

int avlTree::diff(avl_node *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;

    return b_factor;

}

avl_node *avlTree::rr_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;

    return temp;
}

avl_node *avlTree::ll_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;

    return temp;

}

avl_node *avlTree::lr_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);

    return ll_rotation (parent);
}

avl_node *avlTree::rl_rotation(avl_node *parent){
    avl_node *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);

    return rr_rotation (parent);
}

avl_node *avlTree::balance(avl_node *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        if (diff (temp->left) > 0)
            temp = ll_rotation (temp);
        else
            temp = lr_rotation (temp);
    }
    else if (bal_factor < -1){
        if (diff (temp->right) > 0)
            temp = rl_rotation (temp);
        else
            temp = rr_rotation (temp);
    }
    return temp;
}

avl_node *avlTree::insert(avl_node *root, int value){
    if (root == NULL){
        root = new avl_node;
        root->data = value;
        root->left = NULL;
        root->right = NULL;

        return root;
    }
    else if (value < root->data){
        root->left = insert(root->left, value);
        root = balance (root);
    }
    else if (value >= root->data){
        root->right = insert(root->right, value);
        root = balance (root);
    }
    return root;
}

int avlTree::search(avl_node *node, int value){
    if(node == NULL){
      return -1;
    }else if( value == node->data){
      return node->data;
    }else if(value < node->data){
      search(node->left, value);
    }else if(value > node->data){
      search(node->right, value);
    }else{
      return -1;
    }
}

void avlTree::display(avl_node *ptr, int level){
    int i;

    if (ptr!=NULL){
        display(ptr->right, level + 1);
        printf("\n");

        if (ptr == root)
            cout<<"Root -> ";

        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";

        cout<<ptr->data;
        display(ptr->left, level + 1);
    }
}

void avlTree::preorder(avl_node *tree){
    if (tree == NULL)
        return;
    cout<<tree->data<<"  ";
    preorder (tree->left);
    preorder (tree->right);
}
