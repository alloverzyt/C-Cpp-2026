#include <bits/stdc++.h>
using namespace std;
#define N 1000005
int primes[N];
bool isprimes[N];
int m = 0;            

void getPrimes(int n) { 
    memset(isprimes, true, sizeof(isprimes));
    isprimes[1] = false;
    m = 0;
    for (int i = 2; i <= n; i++) {
        if (isprimes[i]) primes[++m] = i;
        for (int j = 1; j <= m && i * primes[j] <= n; j++) {
            isprimes[i * primes[j]] = false;
            if (i % primes[j] == 0) break;
        }
    }
}

int main() {
    getPrimes(1000);
    for (int i = 1; i <= m; i++) {
        cout << primes[i] << " ";
    }
	printf ( "\n总用时 %.3f 秒\n" , ( double ) clock () / CLOCKS_PER_SEC);
    return 0;
}
