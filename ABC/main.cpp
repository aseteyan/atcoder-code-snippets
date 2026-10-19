#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#define endl '\n'
using namespace std;
using namespace boost::multiprecision;

using ll=long long;
using ull=unsigned long long;
using i128=__int128;

std::istream& operator>>(std::istream& is, i128& x){
    int128_t tmp;
    if(is>>tmp)x=tmp.convert_to<i128>();
    return is;
}
std::ostream& operator<<(std::ostream& os, i128 x){
    return os<<int128_t(x);
}

void solve(){
    i128 N; cin>>N;

    auto check=[&](int a1, int d, int n){
        i128 p=a1;
        for(int i=1; i<n; ++i){
            p*=a1+i*d;
            if(p>N)return false;
        }
        return (p<=N);
    };

    ll ans=0;
    for(int a=1; a<=1e6; ++a){
        i128 T=(i128)a*(a+1)*(a+2);
        int n=3;
        while(T<=N){
            int ok=0, ng=1e9;
            while(ng-ok>1){
                int mid=(ok+(ng-ok)/2);

                (check(a, mid, n)?ok:ng)=mid;
            }
            ans+=ok;

            T*=(a+n);
            ++n;
        }
    }
    cout<<ans<<endl;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //cout<<fixed<<setprecision(17);
    int T=1; //cin>>T;
    while(T--)solve();
    return 0;
}