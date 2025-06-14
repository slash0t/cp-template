#include <cstring>

struct bor {
    const static int sz = 30;
    const static int al = 2;
    const static int a = 0;

    struct node {
        node* to[al];
        int visited;

        node() {
            memset(to, 0, sizeof(to));
            visited = 0;
        }

        node* go(int goal) {
            if (this->to[goal] == nullptr) {
                this->to[goal] = new node();
            }
            return this->to[goal];
        }
    };

    node* root;

    bor() {
        root = new node();
    }

    node* add(int num, int index) {
        node* now = root;
        for (int i = sz - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            now = now->go(bit);
            now->visited = index;
        }
        return now;
    }
};