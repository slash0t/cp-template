#include <random>
#include <vector>

using namespace std;

#define pb push_back


//mt19937_64 rnd = mt19937_64((chrono::high_resolution_clock::now().time_since_epoch().count()));
mt19937_64 rnd = mt19937_64(69);

struct bo4ka {
    struct pivo {
        pivo* left = nullptr, * right = nullptr;
        int size, key, priority;
        pivo(int key_, int priority_) : key(key_), priority(priority_), size(1ll) {}
    };

    pivo* root;
    bo4ka(pivo* root_) : root(root_) {}
    bo4ka(vector<int>& a) {
        int n = a.size();

        pivo* tree = nullptr;
        for (int i = 0; i < n; i++) {
            pivo* now = new pivo(a[i], rnd());
            tree = merge(tree, now);
        }

        root = tree;
    }

    void upd(pivo* tree) {
        tree->size = 1;
        if (tree->left) tree->size += tree->left->size;
        if (tree->right) tree->size += tree->right->size;
    }

    typedef pair<pivo*, pivo*> kega;

    // max a key less than min b key
    pivo* merge(pivo* a, pivo* b) {
        if (!a) return b;
        if (!b) return a;

        if (a->priority > b->priority) {
            auto right = merge(a->right, b);
            a->right = right;
            upd(a);
            return a;
        }
        else {
            auto left = merge(a, b->left);
            b->left = left;
            upd(b);
            return b;
        }
    }

    int sz(pivo* tree) {
        return tree ? tree->size : 0;
    }

    kega split(pivo* tree, int k) {
        if (!tree) return { nullptr, nullptr };

        if (sz(tree->left) + 1 <= k) {
            kega p = split(tree->right, k - 1 - sz(tree->left));

            tree->right = p.first;
            upd(tree);

            return { tree, p.second };
        }
        else {
            kega p = split(tree->left, k);

            tree->left = p.second;
            upd(tree);

            return { p.first, tree };
        }
    }

    auto apply(int l, int r, pivo* function(pivo*)) {
        kega q1 = split(root, r);
        kega q2 = split(q1.first, l);
        q2.second = function(q2.second);
        root = merge(q2.first, merge(q2.second, q1.second));
    }

    void order(pivo* tree, vector<int>& ord) {
        if (!tree) return;

        order(tree->left, ord);
        ord.pb(tree->key);
        order(tree->right, ord);
    }

    vector<int> order() {
        vector<int> ord;
        order(root, ord);
        return ord;
    }

    // 1 indexed
    pivo* ctrlx(int l, int r) {
        kega q1 = split(root, r);
        kega q2 = split(q1.first, l - 1);
        root = merge(q2.first, q1.second);
        return q2.second;
    }

    void ctrlv(pivo* v, int k) {
        kega q = split(root, k);
        root = merge(q.first, merge(v, q.second));
    }
};