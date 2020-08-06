作者：Dreamgoing
链接：https://zhuanlan.zhihu.com/p/96846609
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#include <iostream>
#include <vector>
#include <string>

using namespace std;


// For skip list algorithm, please refer to https://www.geeksforgeeks.org/skip-list-set-2-insertion/
// Time complexity O(logn) (Average) O(n) worst
class Node {
public:
    int key;

    // forward: means for each level, the node next pointer to which node.
    vector<Node *> forward;

    Node(int key, int level) {
        this->key = key;
        this->forward = vector<Node *>(level + 1);
    }
};

class SkipList {
public:
    Node *head;
    int MAX_LEVEL = 10;
    float p = 0.1;
    int level = 0;

    SkipList() {
        this->head = new Node(-1, MAX_LEVEL + 1);
    }

    int randomLevel() {
        float r = (float) rand() / RAND_MAX;
        int lvl = 0;
        while (r < p && lvl < MAX_LEVEL) {
            lvl++;
            r = (float) rand() / RAND_MAX;
        }
        return lvl;
    }

    void insert(int key) {
        auto updated = vector<Node *>(MAX_LEVEL + 1);
        auto cur = this->head;
        for (int i = this->level; i >= 0; i--) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
            updated[i] = cur;
        }

        cur = cur->forward[0];

        // cur == nullptr: the end of list, cur->key!=key means found the position to insert.
        if (cur == nullptr || cur->key != key) {
            auto lvl = this->randomLevel();
            if (lvl > this->level) {
                for (int i = this->level + 1; i <= lvl; i++) {
                    updated[i] = this->head;
                }
                this->level = lvl;
            }

            Node *newNode = new Node(key, lvl);

            for (int i = 0; i <= lvl; i++) {
                newNode->forward[i] = updated[i]->forward[i];
                updated[i]->forward[i] = newNode;
            }
        }
    }

    bool search(int key) {
        auto cur = this->head;
        for (int i = this->level; i >= 0; i--) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
        }
        cur = cur->forward[0];
        return cur != nullptr && cur->key == key;

    }

    void deleteByKey(int key) {
        auto updated = vector<Node *>(MAX_LEVEL + 1);
        auto cur = this->head;
        for (int i = this->level; i >= 0; i--) {
            while (cur->forward[i] != nullptr && cur->forward[i]->key < key) {
                cur = cur->forward[i];
            }
            updated[i] = cur;
        }
        cur = cur->forward[0];
        if (cur->key != key) {
            return;
        }
        for (int i = cur->forward.size() - 1; i >= 0; i--) {
            updated[i]->forward[i] = updated[i]->forward[i]->forward[i];
        }
        delete (cur);

        while (this->level > 0 && this->head->forward[this->level] == nullptr) {
            this->level--;
        }
    }

    void showList() {
        cout << "----skip list------" << endl;
        for (int i = 0; i <= level; i++) {
            auto cur = this->head->forward[i];
            while (cur != nullptr) {
                cout << cur->key;
                if (cur->forward[i] != nullptr) {
                    cout << "->";
                }
                cur = cur->forward[i];
            }
            cout << "\n";
        }
    }
};

int main() {
    auto list = new SkipList();
    list->insert(1);
    list->insert(2);
    list->insert(5);
    list->insert(3);
    list->insert(4);
    list->insert(7);
    list->insert(6);
    list->insert(9);

    list->showList();
    list->deleteByKey(5);
    list->showList();


    cout << list->search(4) << endl;
    return 0;
}