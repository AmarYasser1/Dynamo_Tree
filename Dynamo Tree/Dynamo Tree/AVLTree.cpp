#include "AVLTree.h"
AVLTree::AVLTree() : root(nullptr), mx_size(1000) {}

AVLNode* AVLTree::ROOT() { return this->root; }

bool AVLTree::isEmpty() { return !root; }

size_t AVLTree::Max_size() { return this->mx_size; }

int AVLTree::ch_height(AVLNode* node) {
    return !node ? -1 : node->height;
}

void AVLTree::update_height(AVLNode* node) {
    node->height = 1 + max(ch_height(node->left), ch_height(node->right));
}

int AVLTree::balanced_factor(AVLNode* node) {
    if (!node) return -1;

    return ch_height(node->left) - ch_height(node->right);
}

int AVLTree::hashCode(string str, int INTERNAL_NUMBER) {

    for (auto& ch : str)
        INTERNAL_NUMBER = ((INTERNAL_NUMBER << 2) + INTERNAL_NUMBER) + ch;

    return INTERNAL_NUMBER % mx_size;
}

AVLNode* AVLTree::right_rotation(AVLNode*& Q) {
    AVLNode* P = Q->left;
    Q->left = P->right;

    P->right = Q;

    update_height(Q);
    update_height(P);

    return P; // The partent
}

AVLNode* AVLTree::left_rotation(AVLNode*& Q) {
    AVLNode* P = Q->right;

    Q->right = P->left;

    P->left = Q;

    update_height(Q);
    update_height(P);

    return P; // The parent
}

AVLNode* AVLTree::balance(AVLNode* node) {

    if (balanced_factor(node) == 2) { // Left is longer

        if (balanced_factor(node->left) == -1) // Left_right rotation
            node->left = left_rotation(node->left);        // update left rotation for subtree

        node = right_rotation(node);
    }
    else if (balanced_factor(node) == -2) {  // Right is longer

        if (balanced_factor(node->right) == 1) // Right_left rotation
            node->right = right_rotation(node->right);       // update Left rotation for subtree

        node = left_rotation(node);
    }

    return node;
}

// We create node when we create user , then push the node in the tree .
AVLNode* AVLTree::insert_node(AVLNode* newNode, AVLNode* Troot) {

    if (!Troot)
        return Troot = newNode;

    if (newNode->hashValue < Troot->hashValue) {
        if (!Troot->left)
            Troot->left = newNode;
        else
            Troot->left = insert_node(newNode, Troot->left);
    }
    else if (newNode->hashValue > Troot->hashValue) {
        if (!Troot->right)
            Troot->right = newNode;
        else
            Troot->right = insert_node(newNode, Troot->right);
    }

    update_height(Troot);
    return balance(Troot);
}

AVLNode* AVLTree::delete_node(int hashCode, AVLNode* Troot) {
    Amar(!isEmpty(), "Empty tree");

    if (!Troot)
        return nullptr;

    if (hashCode < Troot->hashValue)
        Troot->left = delete_node(hashCode, Troot->left);
    else if (hashCode > Troot->hashValue)
        Troot->right = delete_node(hashCode, Troot->right);
    else {
        AVLNode* temp = Troot;

        if (!Troot->left && !Troot->right) // 0 Child
            Troot = nullptr;
        else if (!Troot->right) {
            // 1 Child
            temp = temp->left;
            delete Troot;
            return temp;
        }
        else if (!Troot->left) {
            // 1 Child
            temp = temp->right;
            delete Troot;
            return temp;
        }
        else {
            // Two children
            AVLNode* mn = min_node(Troot->right);
            Troot->hashValue = mn->hashValue;
            Troot->Activities = mn->Activities;
            Troot->user = mn->user;
            Troot->right = delete_node(Troot->hashValue, Troot->right);
            temp = nullptr;
        }

        if (temp)
            delete temp;
    }

    if (Troot) {
        update_height(Troot);
        Troot = balance(Troot);
    }

    return Troot;
}

void AVLTree::Insert(AVLNode* node) {
    root = insert_node(node, root);
}

 AVLNode* AVLTree::Delete(int hashValue) {
    return root = delete_node(hashValue, root);
 }

AVLNode* AVLTree::min_node(AVLNode* node) {
    AVLNode* cur = node;

    while (cur && cur->left)
        cur = cur->left;

    return cur;
}

AVLNode* AVLTree::search(int hashCode, AVLNode* Troot) {
    if (!Troot)
        return nullptr;

    if (hashCode == Troot->hashValue || !Troot)
        return Troot;
    else if (hashCode < Troot->hashValue)
        return search(hashCode, Troot->left);
    else
        return search(hashCode, Troot->right);
}

void AVLTree::print(AVLNode* Troot) {
    Amar(!isEmpty(), "Empty AVLTree");

    if (!Troot)
        Troot = this->root;

    if (Troot->left)
        print(Troot->left);

    cout << "CODE: " << Troot->hashValue << '\n';
    cout << *Troot->user;
    cout << "#Activities : " << endl;
    cout << "***********" << endl;
    auto print_Activity = [&]()-> void {
        Activity* arr = Troot->Activities.get_reference_arr();
        int size = Troot->Activities.getSize();
        int front = Troot->Activities.idx_front();
        int rear = Troot->Activities.idx_rear();

        for (auto i = front; i != rear; i = (i + 1) % size)
              arr[i].print();
    };
    print_Activity();
    cout << "==================================\n";

    if (Troot->right)
        print(Troot->right);
}


void AVLTree::print_Statistics(AVLNode* Troot) {
    Amar(!isEmpty(), "Empty AVLTree");

    if (!Troot)
        Troot = this->root;

    if (Troot->left)
        print_Statistics(Troot->left);

    cout << "User Name : " << Troot->user->getUserName() << "\t\t Code : " << Troot->hashValue << endl;
    Troot->act.print_statistics_activity();

    if (Troot->right)
        print_Statistics(Troot->right);

}
