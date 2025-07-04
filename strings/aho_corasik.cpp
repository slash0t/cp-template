#include <cstring>
#include <string>

using namespace std;

struct aho_corasik {
    const static int alphabet = 26;
    const static char al_start = 'a';

    struct node {
        node* sufflink = nullptr;
        char from_char;
        node* parent;
        node* to[alphabet];
        node* go[alphabet];
        int terminal = 0;

        node(char from, node* par) : from_char(from), parent(par) {
            memset(to, 0, sizeof(to));
            memset(go, 0, sizeof(go));
        }
    };

    node* root = new node(0, nullptr);

    node* get_go(node* now, char to) {
        to -= al_start;
        if (now->go[to]) return now->go[to];
        if (now->to[to]) now->go[to] = now->to[to];
        if (now == root && !now->to[to]) now->go[to] = root;
        if (!now->go[to]) {
            now->go[to] = get_go(get_sufflink(now), to + al_start);
        }
        return now->go[to];
    }

    node* get_sufflink(node* now) {
        if (now->sufflink) return now->sufflink;
        if (now == root || now->parent == root) now->sufflink = root;
        if (!now->sufflink) {
            now->sufflink = get_go(get_sufflink(now->parent), now->from_char);
        }
        return now->sufflink;
    }

    node* add(string& s) {
        node* now = root;
        for (char c : s) {
            c -= al_start;
            if (!now->to[c]) now->to[c] = new node(c + al_start, now);
            now = now->to[c];
        }
        now->terminal = 1;
        return now;
    }
};