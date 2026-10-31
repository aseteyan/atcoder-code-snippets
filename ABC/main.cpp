#include <bits/stdc++.h>
#define endl '\n'
using namespace std;

using ll=long long;
using ull=unsigned long long;

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

void solve(){
    int N; cin>>N;
    vector<vector<int>> G(N);
    for(int i=0; i<N-1; ++i){
        int u, v; cin>>u>>v;
        --u; --v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> C(N);
    for(int i=0; i<N; ++i)cin>>C[i], --C[i];

    auto [diam, centers]=diameter_and_centers(G);

    ll ans=0;
    if(diam%2==0){
        int c=centers[0];
        vector<int> count_total(N), count_subtree(N);
        stack<int> st;
        auto dfs=[&](auto dfs, int v, int p, int dist)->void{
            if(dist==diam/2){
                ans+=count_total[C[v]]++;
                ans-=count_subtree[C[v]]++;
                st.push(v);
            }
            for(auto to:G[v])if(to!=p){
                dfs(dfs, to, v, dist+1);
                if(v==c){
                    while(!st.empty()){
                        count_subtree[C[st.top()]]=0;
                        st.pop();
                    }
                }
            }
        };
        dfs(dfs, c, -1, 0);
    }else{
        int c1=centers[0], c2=centers[1];
        vector<int> count1(N), count2(N);
        auto dfs=[&](auto dfs, int v, int p, int dist, vector<int>& count)->void{
            if(dist==(diam-1)/2)++count[C[v]];
            for(auto to:G[v])if(to!=p)dfs(dfs, to, v, dist+1, count);
        };
        dfs(dfs, c1, c2, 0, count1);
        dfs(dfs, c2, c1, 0, count2);
        for(int i=0; i<N; ++i)ans+=(ll)count1[i]*count2[i];
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