#include "bits/stdc++.h"
#include <unordered_map>
 
using namespace std;
#define int long long int
#define vi vector<int>
#define pii pair<int,int>
#define vii vector<pii>
#define vvi vector<vi>
#define rep(i,a,b) for(int i=a; i<b; i++)
#define repr(b) for(int i=0; i<b; i++)
#define prin(vec) for(int i=0;i<vec.size();i++){cout<<vec[i]<<" ";}cout<<endl
#define newvec(x,n) vi x(n);rep(i,0,n){cin>>x[i];}
#define newvecn(x,n) int n;cin>>n;vi x(n);repr(n){cin>>x[i];}
#define float long double
#define vip vector<int>::iterator
#define mod 1000000007
#define all(a) a.begin(),a.end()
#define ff first 
#define ss second 
#define pb push_back
#define neg cout<<"NO"<<endl;return;
#define pos cout<<"YES"<<endl;return;
#define intin a int a;cin>>a
#define mii map<int,int>
#define miv map<int,vi>
#define miit mii::iterator
#define mivt miv::iterator
#define matrix(x,n,m,g) vector<vi> x(n,vi(m,g)) 
#define pqi priority_queue<int>
#define qi queue<int>

bool cui(vvi &adj,vi &vis,int j,int parent){
    if(vis[j]){return 0;}
    vis[j]++;
    repr(adj[j].size()){
        int temp = i;
        i = adj[j][i];
        if(i!=parent && !cui(adj,vis,i,j)){
            return 0;
        }
        i=temp;
    }
    return 1;
}
bool cycle_in_undirected(vvi &adj,int n){
    vi vis(n,0);
    return !cui(adj,vis,0,0);
}

bool cid(vvi &adj,int j,vi &stack,vi &vis){
    if(stack[j]){return 1;}
    if(vis[j]){return 0;}
    stack[j]=1;vis[j]=1;
    repr(adj[j].size()){
        if(cid(adj,adj[j][i],stack,vis)){return 1;}
    }
    stack[j]=0;
    return 0;
}
bool cycle_in_directed(vvi &adj,int n){
    vi stack(n),vis(n,0);
    repr(n){
        if(vis[i]==0){
            if(cid(adj,i,stack,vis)){
                return true;
            }
        }
    }
    return false;
}

void visitall(vvi &adj,vi &vis, int j){
    vis[j]=1;
    repr(adj[j].size()){
        if(vis[adj[j][i]]==0){
            visitall(adj,vis,adj[j][i]);
        }
    }
}
int number_of_connected_compo(vvi &adj,int n){
    int ans = 0;
    vi vis(n,0);
    repr(n){
        if(vis[i]==0){
            ans++;
            visitall(adj,vis,i);
        }
    }
    return ans;
}

bool colorer(vvi &adj,int j,vi &col){
    int br = -col[j];
    repr(adj[j].size()){
        int temp=i;i=adj[j][temp];
        if(col[i]==0){
            col[i]=br;
            if(!colorer(adj,i,col)){return 0;}
        }
        if(col[i]!=br){return 0;}
        i=temp;
    }
    return 1;
}   
bool ifBipartite(vvi &adj,int n){
    vi col(n,0);
    repr(n){
        if(col[i]==0){
            col[i]=1;
            if(!colorer(adj,i,col)){return 0;}
        }
    }
    return true;
}

void make_set(int v,vi &sz,vi &parent){
    parent[v] = v;
    sz[v]=1;
}
int find_parent(int v,vi &parent){
    if(parent[v]==v){return v;}
    return parent[v] = find_parent(parent[v],parent);
}
void union_sets(int a,int b,vi &parent,vi &sz){
    a = find_parent(a,parent);
    b = find_parent(b,parent);
    if(sz[a]<sz[b]){swap(a,b);}
    parent[b] = a;
    sz[a]+=sz[b];
}

vi dijkstra(vector<vii> &adj,int node,int n){
    vi dist(n+1,INT64_MAX),vis(n+1,0);
    vis[node] = 1;
    dist[node] = 0;
    priority_queue<pii,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,node});
    while(!pq.empty()){
        pii a = pq.top();
        pq.pop();
        vis[a.ss]=1;
        for(auto i:adj[a.ss]){
            if(dist[i.ff] > dist[a.ss]+i.ss){
                dist[i.ff] = dist[a.ss]+i.ss;
            }
            if(vis[i.ff]==0){
                pq.push({dist[i.ff],i.ff});
            }
        }
        while(!pq.empty() && vis[pq.top().ss]){
            pq.pop();
        }
    }
    return dist;
}

vi bellman_ford(vector<vii> &adj,int node,int n){
    vi dist(n+1,INT64_MAX);
    dist[node] = 0;
    for(int qq=1;qq<n;qq++){
        for(int i=1;i<n+1;i++){
            for(auto j : adj[i]){
                dist[j.ff] = min(dist[j.ff],dist[i]+j.ss);
            }
        }
    }
    return dist;
}

void floydwarshall(vvi &dist,int n){
    rep(k,0,n){
    repr(n){
        rep(j,0,n){
            
                dist[i][j] = min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

vi dijkstra2(vector<vii> &adj,int node,int n){
    vi dist(n,INT64_MAX),vis(n,0);
    vis[node] = 1;
    dist[node] = 0;
    priority_queue<pii,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,node});
    vi parent(n,-1);
    while(!pq.empty()){
        pii a = pq.top();
        pq.pop();
        vis[a.ss]=1;
        for(auto i:adj[a.ss]){
            if(dist[i.ff] > dist[a.ss]+i.ss){
                dist[i.ff] = dist[a.ss]+i.ss;
                parent[i.ff] = a.ss;
            }
            if(vis[i.ff]==0){
                pq.push({dist[i.ff],i.ff});
            }
        }
        while(!pq.empty() && vis[pq.top().ss]){
            pq.pop();
        }
    }
    // prin(dist);
    return parent;
}

void solve(){
    vector<vii> vec(100);
    int m;
    cin>>m;
    repr(m){
        int a,b;
        cin>>a>>b;
        vec[a-1].pb({b-1,0});
    }
    cin>>m;
    repr(m){
        int a,b;
        cin>>a>>b;
        vec[a-1].pb({b-1,0});
    }
    repr(100){
        if(vec[i].empty()){
            int a=1;
            while(a<7 && i+a<100){
                vec[i].pb({i+a,1});
                a++;
            }
        }
    }
    vi x = dijkstra2(vec,0,100);
    // prin(x);
    int a = 99;
    stack<int> path;
    while(a!=-1){
        path.push(a);
        a = x[a];
    }
    if(path.top()==0){
        while(!path.empty()){
            cout<<path.top()+1<<" ";
            path.pop();
        }
        cout<<endl;return;
    }
}


signed main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t=1,curr=1;
    // cin>>t;
    while (t--){
        //cout<<"Case #"<<curr++<<": ";
        solve();
    }
    return 0;
}
