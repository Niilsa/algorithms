#include <iostream>
#include <algorithm>

using namespace std;

class BinTree {
private:
    int depth;
    int key;
    BinTree* left;
    BinTree* right;
    BinTree* ancestor;
public:
    BinTree() {
        depth = -1;
        key = -2365092845;
        left = NULL;
        right = NULL;
        ancestor = NULL;
    }
    BinTree(int val) {
        depth = 0;
        key = val;
        left = NULL;
        right = NULL;
        ancestor = NULL;
    }
    ~BinTree() {}
    void Print();
    BinTree* Insert(int val);
    BinTree* Search(int val);
    BinTree* Min();
    BinTree* Max();
    int Get_key() { return key; }
    int Get_depth() { return depth; }
    BinTree* Get_left() { return left; }
    BinTree* Get_right() { return right; }
    BinTree* Get_ancestor() { return ancestor; }
    void Update_depth();
    bool Delete(int val);
};

void BinTree::Print() {
    if (depth == -1) return;
    if (left)
        left->Print();
    cout << key << " ";
    if (ancestor)
        cout << ancestor->Get_key() << " ";
    cout << depth << endl;
    if (right)
        right->Print();
}

BinTree* BinTree::Insert(int val) {
    if (depth == -1) {
        depth = 0;
        key = val;
        return this;
    }
    else if (val < key) {
        if (!left) {
            left = new BinTree(val);
            left->ancestor = this;
            Update_depth();
            return left;
        }
        BinTree* temp = left->Insert(val);
        Update_depth();
        return temp;
    }
    else if (val > key) {
        if (!right) {
            right = new BinTree(val);
            right->ancestor = this;
            Update_depth();
            return right;
        }
        BinTree* temp = right->Insert(val);
        Update_depth();
        return temp;
    }
}

BinTree* BinTree::Search(int val) {
    if (depth == -1) return NULL;
    if (key == val) return this;
    else if (left && val < key) return left->Search(val);
    else if (right && val > key) return right->Search(val);
    return NULL;
}

BinTree* BinTree::Min() {
    if (depth == -1) return NULL;
    if (!left) return this;
    else return left->Min();
}

BinTree* BinTree::Max() {
    if (depth == -1) return NULL;
    if (!right) return this;
    else return right->Max();
}

void BinTree::Update_depth() {
    depth = max(left ? left->depth + 1 : 0, right ? right->depth + 1 : 0);
}

bool BinTree::Delete(int val) {
    if (depth == -1) return false;
    if (val < key) {
        if (left) {
            return left->Delete(val);
            Update_depth();
        }
        else
            return false;
    }
    else if (val > key) {
        if (left) {
            return right->Delete(val);
            Update_depth();
        }
        else
            return false;
    }
    else {
        if (!ancestor) {
            if (!left && !right)
                depth = -1;
            else if (!left || !right) {
                BinTree* temp;
                if (!right)
                    temp = left;
                else
                    temp = right;
                depth = temp->depth;
                key = temp->key;
                left = temp->left;
                right = temp->right;
                delete temp;
            }
            else {
                BinTree* temp = right->Min();
                key = temp->key;
                right->Delete(key);
                Update_depth();
            }
        }
        else {
            if (!left && !right) {
                if (ancestor->left == this)
                    ancestor->left = NULL;
                else
                    ancestor->right = NULL;
                ancestor->Update_depth();
                delete this;
            }
            else if (!right) {
                if (ancestor->left == this)
                    ancestor->left = left;
                else 
                    ancestor->right = left;
                left->ancestor = ancestor;
                ancestor->Update_depth();
                delete this;
            }
            else if (!left) {
                if (ancestor->left == this)
                    ancestor->left = right;
                else
                    ancestor->right = right;
                right->ancestor = ancestor;
                ancestor->Update_depth();
                delete this;
            }
            else {
                BinTree* temp = right->Min();
                key = temp->key;
                right->Delete(key);
                Update_depth();
            }
        }
        return true;
    }
}


int32_t main() {
    BinTree kekw2(8);
    kekw2.Insert(3);
    kekw2.Insert(2);
    kekw2.Insert(12);
    kekw2.Print(); cout << "_________\n";
    kekw2.Delete(3);
    kekw2.Print(); cout << "_________\n";
    return 0;
}
