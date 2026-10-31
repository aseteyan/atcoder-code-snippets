# 競技プログラミング

<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
## 数学
<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
### 切り上げ(天井関数(ceiling function))
$$
\left\lceil \frac{a}{b} \right\rceil = \left\lfloor \frac{a+b-1}{b} \right\rfloor
$$

### mod
$$
(i \bmod j) = i-\left\lfloor \frac{i}{j} \right\rfloor \times j
$$

### 組み合わせ(Combination)
$$
\binom{n}{k} = \frac{{}_n P_k}{k!} = \frac{n!}{k!(n-k)!}
= \frac{n \times (n-1) \times \cdots \times (n-k+1)}{1 \times 2 \times \cdots \times k}
$$
```cpp
for(int i=1; i<=k; ++i){
    ans*=mint(n--);
    ans*=mint(i).inv();
}
```

### エラトステネスの篩 $O(N\log\log N)$
```cpp
void sieve(vector<bool>& is_prime, int N){
    if(N<=0)return;

    is_prime.assign(N+1, true);

    is_prime[0]=false;
    if(N>=1)is_prime[1]=false;

    for(int i=4; i<=N; i+=2)is_prime[i]=false;
    for(int i=3; i*i<=N; i+=2){
        if(!is_prime[i])continue;
        for(int j=i*i; j<=N; j+=2*i)is_prime[j]=false;
    }
}
```

<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
## bit
<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
### string_to_bit
```cpp
ull string_to_bit(const string& s){
    ull res=0;
    int L=s.size();

    for(int i=0; i<L; ++i){
        if(s[i]=='1')res|=1ull<<(L-1-i);
    }
    return res;
}
```
### bit_to_string
```cpp
string bit_to_string(ull n, int L){
    string res(L, '0');

    for(int i=0; i<L; ++i){
        if((n>>i)&1)res[L-1-i]='1';
    }
    return res;
}
```

## 幾何
### 偏角ソート
[ABC 481 E - Most Brilliant Starry Sky](https://atcoder.jp/contests/abc481/tasks/abc481_e)
```cpp
// https://atcoder.jp/contests/abc442/editorial/15136
struct point{
    ll x, y;
};
ll cross(const point &a, const point &b){
    return a.x*b.y-a.y*b.x;
}
bool cmp(const point &a, const point &b){
    ll ah=(a.y<0||(a.y==0&&a.x<0));
    ll bh=(b.y<0||(b.y==0&&b.x<0));
    if(ah!=bh)return ah<bh;
    return cross(a, b)>0;
}
void argument_sort(vector<point> &points){
    sort(points.begin(), points.end(), cmp);
}

void solve(){
    int N; cin>>N;
    vector<point> A(N);
    for(int i=0; i<N; ++i){
        cin>>A[i].x>>A[i].y;
    }
    argument_sort(A);

    A.resize(2*N);
    for(int i=0; i<N; ++i)A[N+i]=A[i];

    int r=0, ans=0;
    for(int i=0; i<N; ++i){
        r=max(r, i+1);
        while(r<2*N&&cross(A[i], A[r])>0)++r;
        ans=max(ans, r-i);
    }
    cout<<ans<<endl;
}
```

## オーバーフロー対策
正整数列$A$に対して，`/` を切り捨て整数除算とすると，
$$
A[0] \times A[1] \times \cdots \times A[m] \le N
\quad\Longleftrightarrow\quad
N / A[1] / A[2] / \cdots / A[m] > 0
$$

### `__int128` [ABC 480 E - Product-Bounded Arithmetic Sequences](https://atcoder.jp/contests/abc480/tasks/abc480_e)
```cpp
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
```


### `cpp_int` [多倍長整数](https://boostjp.github.io/tips/multiprec-int.html)
```cpp
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
    string S="-12345678901234567890";
    cpp_int N(S);
    cin>>N;

    i128 M; cin>>M;
    cout<<M<<endl;
}
```

<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
## 二分探索
<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
- lower_bound：$x$以上の最初の要素
- upper_bound：$x$より大きい最初の要素
- equal_range：lower_boundとupper_boundを同時に取得

![equal_range.png](/fig/equal_range.png)
![equal_range.png](/fig/equal_range_bar.png)

```cpp
void solve(){
    //      index: 0  1  2  3  4  5  6  7
    vector<int> A={1, 2, 2, 2, 2, 2, 4, 5};
    auto l=lower_bound(A.begin(), A.end(), 2);
    auto u=upper_bound(A.begin(), A.end(), 2);
    auto e=equal_range(A.begin(), A.end(), 2);

    cout<<l-A.begin()<<endl; // index: 1
    cout<<*l<<endl;          // value: 2

    cout<<u-A.begin()<<endl; // index: 6
    cout<<*u<<endl;          // value: 4

    cout<<e.second-e.first<<endl; // element count: 5 (← 6 - 1)
}
```

### 最小値の最大化(upper_bound)
#### [ABC 463 D - Maximize the Gap](https://atcoder.jp/contests/abc463/tasks/abc463_d)
```cpp
void solve(){
    ll N, K; cin>>N>>K;
    vector<pair<ll, ll>> C(N);
    for(int i=0; i<N; ++i)cin>>C[i].second>>C[i].first;

    sort(C.begin(), C.end());

    auto check=[&](ll x){
        ll k=0, pre=-1e18;
        for(auto [r,l]:C){
            if(pre<=l){
                ++k;
                pre=r+x;
            }
        }
        return (k>=K);
    };

    ll ok=0, ng=1e9+7;
    while(ng-ok>1){
        ll mid=(ok+(ng-ok)/2);
        (check(mid)?ok:ng)=mid;
    }
    if(!ok)ok=-1;
    cout<<ok<<endl;
}
```

### 最大値の最小化(lower_bound)
#### [JOI 2021 二次予選 D - 安全点検 (Safety Inspection)](https://atcoder.jp/contests/joi2021yo2/tasks/joi2021_yo2_d)
```cpp
void solve(){
    ll N, K; cin>>N>>K;
    vector<ll> A(N), B(N);
    for(int i=N-1; i>=0; --i)cin>>A[i];
    for(int i=N-1; i>=0; --i)cin>>B[i];

    auto check=[&](ll x){
        ll k=0, spare=0;
        for(int i=0; i<N; ++i){
            if(spare>=B[i]){
                spare-=B[i];
                continue;
            }

            ll w=B[i]-spare; // 作業量
            ll e=x-A[i]; // 作業可能時間

            if(e<=0)return false;

            ll n=(w+e-1)/e; // 必要人数
            k+=n;

            spare=n*e-w; // 余分な時間
        }
        return (k<=K);
    };

    ll ng=0, ok=1e18;
    while(ok-ng>1){
        ll mid=(ng+(ok-ng)/2);
        (check(mid)?ok:ng)=mid;
    }
    cout<<ok<<endl;
}
```

## bit全探索
```cpp
for(int bit=0; bit<(1<<N); ++bit){
    for(int i=0; i<N; ++i){
        if(bit&(1<<i)){

        }
    }
}
```

## 深さ優先探索(DFS)
```cpp
vector<vector<int>> G;
vector<bool> seen;
void dfs(int v){
    seen[v]=true;

    for(const auto& nv:G[v]){
        if(seen[nv])continue;
        dfs(nv);
    }
}
```

## 幅優先探索(BFS)
#### [ABC 460 D - Repeatedly Repainting](https://atcoder.jp/contests/abc460/tasks/abc460_d)
```cpp
int dx[]={1,1,0,-1,-1,-1,0,1};
int dy[]={0,1,1,1,0,-1,-1,-1};

void solve(){
    int H, W; cin>>H>>W;
    vector<string> S(H);
    for(int i=0; i<H; ++i)cin>>S[i];

    queue<pair<int, int>> Q;
    vector A(H, vector<int>(W, -1));
    for(int y=0; y<H; ++y)for(int x=0; x<W; ++x){
        if(S[y][x]=='.')continue;

        for(int i=0; i<8; ++i){
            int nx=x+dx[i], ny=y+dy[i];
            if(0<=nx&&nx<W&&0<=ny&&ny<H&&S[ny][nx]=='.'){
                Q.emplace(ny, nx);
                A[ny][nx]=1;
            }
        }
    }

    while(!Q.empty()){
        auto [y, x]=Q.front(); Q.pop();

        for(int i=0; i<8; ++i){
            int nx=x+dx[i], ny=y+dy[i];
            if(nx<0||W<=nx||ny<0||H<=ny)continue;

            if(A[ny][nx]==-1){
                A[ny][nx]=A[y][x]+1;
                Q.emplace(ny, nx);
            }
        }
    }

    for(int y=0; y<H; ++y){
        for(int x=0; x<W; ++x)cout<<(A[y][x]%2?'.':'#');
        cout<<endl;
    }
}
```

## ダイクストラ法(Dijkstra algorithm)
#### [ABC 463 E - Roads and Gates](https://atcoder.jp/contests/abc463/tasks/abc463_e)
```cpp
const ll INF=(1LL<<60);

ll N, M, Y;
vector<vector<pair<ll, ll>>> G;
vector<ll> distances;

void dijkstra(){
    int startIndex=0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> q;
    q.emplace((distances[startIndex]=0), startIndex);

    while(!q.empty()){
        const auto [distance, from]=q.top();
        q.pop();

        if(distances[from]<distance)continue;

        for(const auto& [to, w]:G[from]){
            const ll d=(distances[from]+w);

            if(d<distances[to])q.emplace((distances[to]=d), to);
        }
    }
}

void solve(){
    cin>>N>>M>>Y;
    G.resize(N+2);
    for(int i=0; i<M; ++i){
        int u, v, t; cin>>u>>v>>t;
        u--; v--;
        G[u].push_back({v, t});
        G[v].push_back({u, t});
    }
    for(int i=0; i<N; ++i){
        int x; cin>>x;
        G[i].push_back({N, x});
        G[N+1].push_back({i, x});
    }
    G[N].push_back({N+1, Y});

    distances.resize(N+2, INF);
    dijkstra();
    for(int i=1; i<N; ++i)cout<<distances[i]<<(i+1==N?"\n":" ");
}
```

<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
## セグメント木(Segment Tree)
<!-- %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% -->
[ACL segtree](https://atcoder.github.io/ac-library/production/document_ja/segtree.html) の `prod(l, r)` は半開区間 $[l, r)$ を扱う．
`max_right<f>(int l)`, `min_left<f>(int r)`は，`f(seg.prod(l, r)) = true`を満たす最大の $r$ や最小の $l$ を返す．

### 一点更新・区間最大値取得
#### [競技プログラミングの鉄則 A58 - RMQ (Range Maximum Queries)](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bf)
```cpp
int op(int a, int b){
    return max(a, b);
}

int e() { return 0; }

void solve(){
    int N, Q; cin>>N>>Q;

    vector<int> A(N);
    segtree<int, op, e> seg(A);
    for(;Q--;){
        int q; cin>>q;
        if(q==1){
            int p, x; cin>>p>>x;
            p--;
            seg.set(p, x);
        }else{
            int l, r; cin>>l>>r;
            l--; r--;
            cout<<seg.prod(l, r)<<endl;
        }
    }
}
```

### 一点更新・区間和取得
#### [競技プログラミングの鉄則 A59 - RSQ (Range Sum Queries)](https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bg)
```cpp
int op(int a, int b){
    return a+b;
}

int e() { return 0; }

void solve(){
    int N, Q; cin>>N>>Q;

    vector<int> A(N);
    segtree<int, op, e> seg(A);
    for(;Q--;){
        int q; cin>>q;
        if(q==1){
            int p, x; cin>>p>>x;
            p--;
            seg.set(p, x);
        }else{
            int l, r; cin>>l>>r;
            l--; r--;
            cout<<seg.prod(l, r)<<endl;
        }
    }
}
```

## 遅延セグメント木
[ACL lazy_segtree](https://atcoder.github.io/ac-library/production/document_ja/segtree.html) の [チートシート](https://betrue12.hateblo.jp/entry/2020/09/23/005940)

### 区間更新・区間和取得
#### [ALPC K - Range Affine Range Sum](https://atcoder.jp/contests/practice2/tasks/practice2_k)
```cpp
/* セグメント木のための構造体
   二項演算関数 op，単位元関数 e */
struct S{
    mint v;
    ll size;
    S(mint v=0, ll size=0):v(v),size(size){}
};

// 二項演算
S op(S x, S y){
    return S(x.v+y.v, x.size+y.size);
}

// 単位元
S e() { return S(0, 0); }

/* 遅延評価のための構造体
   作用関数 mapping，作用の合成関数 composition，単位元関数 id */
struct F{
    mint b, c;
    F(mint b=0, mint c=0):b(b),c(c){}
};

// 作用関数：a_i ← b×a_i + c ⇒ a×b + c×size
S mapping(F f, S x){
    return S(f.b*x.v+f.c*x.size, x.size);
}

// 作用の合成関数：g.b((f.b)x + f.c) + g.c = (g.b f.b)x + g.b f.c + g.c
F composition(F g, F f){
    return F(g.b*f.b, g.b*f.c+g.c);
}

// 作用の単位元
F id() { return F(1, 0); }

void solve(){
    int N, Q; cin>>N>>Q;

    vector<S> A(N);
    for(int i=0; i<N; ++i){
        int x; cin>>x;
        A[i]=S(x, 1);
    }

    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);
    for(;Q--;){
        int q; cin>>q;
        if(q==0){
            int l, r, b, c; cin>>l>>r>>b>>c;
            seg.apply(l, r, F(b, c)); // 区間更新
        }else{
            int l, r; cin>>l>>r;
            cout<<seg.prod(l, r).v.val()<<endl; // 区間和取得
        }
    }
}
```

## クラスカル法
#### [典型アルゴリズム問題集 F - 最小全域木問題](https://atcoder.jp/contests/typical-algorithm/tasks/typical_algorithm_f)
```cpp
void solve(){
    int N, M; cin>>N>>M;
    vector<tuple<int, int, int>> E(M);
    for(int i=0; i<M; ++i){
        int u, v, c; cin>>u>>v>>c;
        E[i]={c, u, v};
    }
    sort(E.begin(), E.end());

    dsu UF(N);
    ll ans=0;
    for(auto [c, u, v]:E){
        if(!UF.same(u, v)){
            UF.merge(u, v);
            ans+=c;
        }
    }
    cout<<ans<<endl;
}
```

## 木の直径と中心
[ABC 482 E - Diameter Endpoint Colors](https://atcoder.jp/contests/abc482/tasks/abc482_e)
[解説](https://atcoder.jp/contests/abc482/editorial/28018)
[実装例 (C++, 偶奇で場合分け)](https://atcoder.jp/contests/abc482/submissions/80494073)

- 木の直径が __偶数__ のとき，木の中心はちょうど1個存在する．
- 木の直径が __奇数__ のとき，木の中心は2個存在し，辺で直接結ばれている．


[実装例 (C++, 中点を追加して偶数に帰着)](https://atcoder.jp/contests/abc482/submissions/80493959)
辺の中点に頂点を追加することで，木の直径は必ず偶数になることを利用．

[自分の提出](https://atcoder.jp/contests/abc482/submissions/80533092)
```cpp
// 使い方：auto [diam, centers]=diameter_and_centers(G);

// 頂点rootから全頂点への距離
vector<int> bfs_dist(const vector<vector<int>>& G, int root){
    int n=G.size();
    vector<int> dist(n, n);
    queue<int> Q;

    dist[root]=0;
    Q.push(root);
    while(!Q.empty()){
        int v=Q.front(); Q.pop();

        for(int to:G[v])if(dist[to]>dist[v]+1){
            dist[to]=dist[v]+1;
            Q.push(to);
        }
    }
    return dist;
}

// 距離が最大の頂点
int farthest_vertex(const vector<int>& dist){
    return max_element(dist.begin(), dist.end())-dist.begin();
}

// 木の直径と中心
pair<int, vector<int>> diameter_and_centers(const vector<vector<int>>& G){
    int n=G.size();
    int a=farthest_vertex(bfs_dist(G, 0));
    auto distA=bfs_dist(G, a);
    int b=farthest_vertex(distA);
    auto distB=bfs_dist(G, b);

    int diam=distA[b];
    vector<int> centers;
    if(diam%2==0){
        for(int i=0; i<n; ++i){
            if(distA[i]==diam/2&&distB[i]==diam/2)centers.push_back(i);
        }
    }else{
        for(int i=0; i<n; ++i){
            if(distA[i]==(diam-1)/2&&distB[i]==(diam+1)/2)centers.push_back(i);
            if(distA[i]==(diam+1)/2&&distB[i]==(diam-1)/2)centers.push_back(i);
        }
    }
    return {diam, centers};
}
```

## 木の重心分解
```cpp
int N;
vector<vector<int>> G;
vector<int> sz, centroid;

void dfs(ll v, ll p=-1){
    bool iscentroid=true;

    for(auto to:G[v])if(to!=p){
        dfs(to, v);

        if(sz[to]>N/2)iscentroid=false;
        sz[v]+=sz[to];
    }
    if(N-sz[v]>N/2)iscentroid=false;
    if(iscentroid)centroid.push_back(v);
}

void solve(){
    cin>>N;
    G.resize(N); sz.resize(N, 1);
    for(int i=0; i+1<N; ++i){
        int a, b; cin>>a>>b;
        --a, --b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(0);
    int g=centroid[0];
    cout<<g<<endl;
}
```

# 付録
### Markdown Preview Enhanced: Customize Preview Html Head (Workspace)
```html
<script type="text/javascript" src="./mpe-copy-btn.js"></script>
```

__mpe-copy-btn.js__
```js
(function () {
  'use strict';

  const scan = () => {
    document.querySelectorAll('pre').forEach(pre => {
      if (pre.querySelector('.copy-btn')) return;

      const btn = document.createElement('button');
      btn.className = 'copy-btn';
      btn.textContent = 'Copy';

      pre.style.position = 'relative';

      btn.style.position = 'absolute';
      btn.style.top = '5px';
      btn.style.right = '5px';
      //btn.style.zIndex = '9999';

      btn.onclick = async () => {
        const text = (pre.querySelector('code') || pre).innerText;

        try {
          await navigator.clipboard.writeText(text);

          btn.textContent = 'Copied!';
          setTimeout(() => btn.textContent = 'Copy', 1000);

        } catch (e) {
          btn.textContent = 'Error';
          setTimeout(() => btn.textContent = 'Copy', 1000);
        }
      };

      pre.appendChild(btn);
    });
  };

  scan();
  setInterval(scan, 2000);
})();
```

### 参照方法
コードをコピーして使用する際は，参照URLを添付
```cpp
// Source: [URL]
// Source: https://github.com/aseteyan/atcoder-code-snippets
```

### Git
```bash
git add .
git commit -m "内容"
git push
```