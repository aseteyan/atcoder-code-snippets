#include <stdio.h>
#define ll long long

int main(int argc, char const *argv[]){
    ll n; scanf("%ld", &n);

    int ans=1;
    while(n!=1){
        n/=ans;
        ans++;
    }
    printf("%d\n", ans-1);
    return 0;
}