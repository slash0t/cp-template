#include <map>
#include <random>
#include <chrono>

using namespace std;

struct factorization {
    mt19937_64 rnd;
    map<int, int> mp;

    factorization() {
        rnd = mt19937_64((chrono::high_resolution_clock::now().time_since_epoch().count()));
    }

    int mult(int a, int b, int mod) {
        return ((__int128)a * b) % mod;
    }

    int bitPow(int num, int pow, int mod) {
        if (pow == 0) return 1;
        if (pow % 2 == 0) {
            int res = bitPow(num, pow / 2, mod);
            return mult(res, res, mod) % mod;
        }
        return mult(num % mod, bitPow(num, pow - 1, mod), mod);
    }

    bool prime(int num) {
        for (int i : {2, 3, 7, 11, 13, 17}) {
            if (num == i) return 1;
            if (num % i == 0) return 0;
        }

        for (int i = 0; i < 30; i++) {
            int a = rnd() % (num - 3) + 2;

            int n = num - 1;
            int s = 0;
            while (n % 2 == 0) {
                n /= 2;
                s++;
            }

            int x = bitPow(a, n, num);
            if (x == 1 || x == num - 1) continue;
            bool ok = 0;
            for (int i = 0; i < s - 1; i++) {
                x = mult(x, x, num);
                if (x == 1) return 0;
                if (x == num - 1) {
                    ok = 1;
                    break;
                }
            }
            if (!ok) return 0;
        }
        return 1;
    }


    void div_simple(int n) {
        for (int i = 2; i * i <= n; i++) {
            while (n % i == 0) {
                mp[i]++;
                n /= i;
            }
        }
        if (n > 1) mp[n]++;
    }

    int f(int x, int mod) {
        return (mult(x, x, mod) + 1) % mod;
    }

    int gcd(int a, int b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    int rho(int n) {
        for (int i : {2, 3, 5, 7, 11, 13, 17, 19}) {
            if (n % i == 0) return i;
        }

        int x = rnd() % (n - 2) + 2;
        int y = x;
        int d = 1;

        while (d == 1) {
            x = f(x, n);
            y = f(f(y, n), n);
            d = gcd(abs(x - y), n);
        }

        return d;
    }

    void div(int n, int flag = 1) {
        if (flag) mp.clear();

        if (n < 1e10) {
            div_simple(n);
            return;
        }
        if (prime(n))mp[n]++;
        else {
            int temp = rho(n);
            div(n / temp, 0);
            div(temp, 0);
        }
    }
};