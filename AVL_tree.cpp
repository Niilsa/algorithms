#include <iostream>
#include <algorithm>

using namespace std;

class BinTree {
protected:
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
    virtual void Print();
    BinTree* Insert(int val);
    BinTree* Search(int val);
    BinTree* Min();
    BinTree* Max();
    virtual int Get_key() { 
        return key;
    }
    int Get_depth() {
        if (this == NULL)
            return -1;
        else {
            Update_depth();
            return depth;
        }
    }
    BinTree* Get_left() { return left; }
    BinTree* Get_right() { return right; }
    BinTree* Get_ancestor() { return ancestor; }
    virtual void Update_depth();
    virtual bool Delete(int val);
};

class AVL_Tree : private BinTree {
private:
    AVL_Tree* ancestor;
    AVL_Tree* left;
    AVL_Tree* right;
public:
    AVL_Tree() {
        depth = -1;
        key = -32597634;
        left = NULL;
        right = NULL;
        ancestor = NULL;
    }
    AVL_Tree(int val) {
        depth = 0;
        key = val;
        left = NULL;
        right = NULL;
        ancestor = NULL;
    }
    int Get_balance() {
        if (!this) return 0;
        int left_val = left ? left->depth : -1;
        int right_val = right ? right->depth : -1;
        return left_val - right_val;
    }
    AVL_Tree* Insert(int val);
    bool Delete(int val);
    void Balancing();
    void Small_left();
    void Big_left();
    void Small_right();
    void Big_right();
    AVL_Tree* Min();
    AVL_Tree* Max();
    AVL_Tree* Search(int val);
    int Get_key() {
        return key;
    }
    void Print();
    void Update_depth();
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
    depth = max(left ? left->depth : -1, right ? right->depth : -1) + 1;
}

void AVL_Tree::Update_depth() {
    depth = max(left ? left->depth : -1, right ? right->depth : -1) + 1;
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

AVL_Tree* AVL_Tree::Min() {
    if (depth == -1) return NULL;
    if (!left) return this;
    else return left->Min();
}

AVL_Tree* AVL_Tree::Max() {
    if (depth == -1) return NULL;
    if (!right) return this;
    else return right->Max();
}

AVL_Tree* AVL_Tree::Search(int val) {
    if (depth == -1) return NULL;
    if (key == val) return this;
    else if (left && val < key) return left->Search(val);
    else if (right && val > key) return right->Search(val);
    return NULL;
}

void AVL_Tree::Small_left() {
    AVL_Tree* temp = right;
    AVL_Tree* temp2 = left;
    int temp_key = key;
    key = temp->key;
    right = temp->right;
    if (right)
        right->ancestor = this;
    left = temp;
    left->ancestor = this;
    left->key = temp_key;
    left->right = left->left;
    left->left = temp2;
    if (left->left)
        left->left->ancestor = left;
    left->Update_depth();
    Update_depth();
}

void AVL_Tree::Big_left() {
    AVL_Tree* temp_left = left;
    AVL_Tree* A = right;
    AVL_Tree* C = right->left;
    int temp_key = key;
    right = A;
    left = C;
    right->left = left->right;
    key = left->key;
    left->key = temp_key;
    left->right = left->left;
    left->left = temp_left;
    left->ancestor = this;
    right->Update_depth();
    left->Update_depth();
    Update_depth();
}

void AVL_Tree::Small_right() {
    AVL_Tree* temp = left;
    AVL_Tree* temp2 = right;
    int temp_key = key;
    key = temp->key;
    left = temp->left;
    if (left)
        left->ancestor = this;
    right = temp;
    right->ancestor = this;
    right->key = temp_key;
    right->left = right->right;
    right->right = temp2;
    if (right->right)
        right->right->ancestor = right;
    right->Update_depth();
    Update_depth();
}

void AVL_Tree::Big_right() {
    AVL_Tree* temp_right = right;
    AVL_Tree* A = left;
    AVL_Tree* C = left->right;
    int temp_key = key;
    left = A;
    right = C;
    left->right = right->left;
    key = right->key;
    right->key = temp_key;
    right->left = right->right;
    right->right = temp_right;
    right->ancestor = this;
    left->Update_depth();
    right->Update_depth();
    Update_depth();
}

void AVL_Tree::Balancing() {
    int balance = Get_balance();
    if (balance == 2) {
        if (left->Get_balance() >= 0) {
            Small_right();
            Update_depth();
        }
        else {
            Big_right();
            Update_depth();
        }
    }
    else if (balance == -2) {
        if (right->Get_balance() <= 0) {
            Small_left();
            Update_depth();
        }
        else {
            Big_left();
            Update_depth();
        }
    }
    if (ancestor)
        ancestor->Balancing();
}

AVL_Tree* AVL_Tree::Insert(int val) {
    if (depth == -1) {
        depth = 0;
        key = val;
        return this;
    }
    else if (val < key) {
        if (!left) {
            left = new AVL_Tree(val);
            left->ancestor = this;
            Update_depth();
            Balancing();
            return left;
        }
        AVL_Tree* temp = left->Insert(val);
        Update_depth();
        Balancing();
        return temp;
    }
    else if (val > key) {
        if (!right) {
            right = new AVL_Tree(val);
            right->ancestor = this;
            Update_depth();
            Balancing();
            return right;
        }
        AVL_Tree* temp = right->Insert(val);
        Update_depth();
        Balancing();
        return temp;
    }
}

bool AVL_Tree::Delete(int val) {
    if (depth == -1) return false;
    if (val < key) {
        if (left) {
            bool temp = left->Delete(val);
            Update_depth();
            return temp;
        }
        else
            return false;
    }
    else if (val > key) {
        if (left) {
            bool temp = right->Delete(val);
            Update_depth();
            return temp;
        }
        else
            return false;
    }
    else {
        if (!ancestor) {
            if (!left && !right)
                depth = -1;
            else if (!left || !right) {
                AVL_Tree* temp;
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
                AVL_Tree* temp = right->Min();
                key = temp->key;
                right->Delete(key);
                Update_depth();
                //Balancing();
            }
        }
        else {
            if (!left && !right) {
                if (ancestor->left == this)
                    ancestor->left = NULL;
                else
                    ancestor->right = NULL;
                ancestor->Update_depth();
                ancestor->Balancing();
                delete this;
            }
            else if (!right) {
                if (ancestor->left == this)
                    ancestor->left = left;
                else
                    ancestor->right = left;
                left->ancestor = ancestor;
                ancestor->Update_depth();
                ancestor->Balancing();
                delete this;
            }
            else if (!left) {
                if (ancestor->left == this)
                    ancestor->left = right;
                else
                    ancestor->right = right;
                right->ancestor = ancestor;
                ancestor->Update_depth();
                ancestor->Balancing();
                delete this;
            }
            else {
                AVL_Tree* temp = right->Min();
                key = temp->key;
                right->Delete(key);
                Update_depth();
                //Balancing();
            }
        }
        return true;
    }
}

void AVL_Tree::Print() {
    if (depth == -1) return;
    if (left)
        left->Print();
    cout << "for " << key << ", ";
    if (ancestor)
        cout << "ancestor = " << ancestor->Get_key() << ", ";
    cout << "balance = " << Get_balance() << endl;
    if (right)
        right->Print();
}

int32_t main() {
    // ТЕСТЫ

    // без аргументов
    /*AVL_Tree graph;
    graph.Print();
    cout << "_________\n";
    graph.Insert(8);
    graph.Print();
    cout << "_________\n";*/
    
    // search
    /*AVL_Tree graph(8);
    graph.Insert(7);
    graph.Insert(9);
    graph.Print(); 
    cout << "_________\n";
    if (graph.Search(7)) cout << "YES" << endl;
    else cout << "NO";
    if (graph.Search(-7)) cout << "YES" << endl;
    else cout << "NO";*/
    
    // min & max
    /*AVL_Tree graph(8);
    graph.Insert(7);
    graph.Insert(9);
    graph.Print();
    cout << "_________\n";
    cout << graph.Min()->Get_key() << " " << graph.Max()->Get_key() << endl;*/
    
    // delete
    /*AVL_Tree graph(8);
    graph.Insert(7);
    graph.Delete(7);
    graph.Print();
    cout << "_________\n";
    graph.Delete(8);
    graph.Print();
    cout << "_________\n";*/
    
    // Малый левый поворот
    /*AVL_Tree graph;
    graph.Insert(8);
    graph.Insert(7);
    graph.Insert(6);
    graph.Print();
    cout << "_________\n";*/
    
    // Большой левый поворот
    /*AVL_Tree graph;
    graph.Insert(8);
    graph.Insert(6);
    graph.Insert(7);
    graph.Print();
    cout << "_________\n";*/
    
    // Малый правый поворот
    /*AVL_Tree graph;
    graph.Insert(8);
    graph.Insert(9);
    graph.Insert(10);
    graph.Print();
    cout << "_________\n";*/
    
    // Большой правый поворот
    /*AVL_Tree graph;
    graph.Insert(8);
    graph.Insert(10);
    graph.Insert(9);
    graph.Print();
    cout << "_________\n";*/

    // Больше Delete
    AVL_Tree graph;
    graph.Insert(8);
    graph.Insert(10);
    graph.Insert(9);
    graph.Insert(7);
    graph.Insert(6);
    graph.Print();
    cout << "_________\n"; 
    graph.Delete(9);
    graph.Print();
    cout << "_________\n";

    return 0;
}
