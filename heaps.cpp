#include "bits/stdc++.h"
 
using namespace std;
#define int long long int
#define vi vector<int>
#define pii pair<int,int>
#define vii vector<pii>
#define rep(i,a,b) for(int i=a; i<b; i++)
#define repr(b) for(int i=0; i<b; i++)
#define prin(vec) for(int i=0;i<vec.size();i++){cout<<vec[i]<<" ";}cout<<endl
#define newvec(x,n) vi x(n);rep(i,0,n){cin>>x[i];}
#define newvecn(x,n) int n;cin>>n;vi x(n);repr(n){cin>>x[i];}
#define float long double
#define vip vector<int>::iterator
#define mod 10000007
#define all(a) a.begin(),a.end()
#define ff first 
#define ss second 
#define pb push_back
#define neg cout<<"NO"<<endl;return;
#define pos cout<<"YES"<<endl;return;
#define pow(a,b) (int)pow(a,b)

void swap(vi &arr,int x,int y){
    int a=arr[x];arr[x]=arr[y];arr[y]=a;return;
}

void heapify(vi &arr,int i,int start){
    if(i+start>=arr.size()){return;}
    int r=start+2*i+2,l=start+2*i+1;
    i+=start;
    int maxm = i;
    heapify(arr,r-start,start);
    heapify(arr,l-start,start);
    if(r<arr.size() && arr[r]>arr[maxm]){
        maxm = r;
    }
    if(l<arr.size() && arr[l]>arr[maxm]){
        maxm = l;
    }
    if(maxm!=i){
        swap(arr,i,maxm);
        heapify(arr,maxm-start,start);
    }
}

void heapsort(vi &arr){
    repr(arr.size()){
        heapify(arr,0,i);
    }
}

void solve(){
    newvec(x,n);
    int k;cin>>k
}

bool sudoku_solver(vector<string> &arr,int i,int j,int n,vector<vi> &h,vector<vi> &v,vector<vi> &b){
    //cout<<i<<j<<endl;
    if(j==n){return 1;}
    if(arr[i][j]!='.'){
        return sudoku_solver(arr,((i==(n-1))?0:(i+1)),j+(i/(n-1)),n,h,v,b);
    }
    rep(q,0,9){
        if(h[i][q] + v[j][q] + b[(floor(j/3))*3 + floor(i/3)][q] == 0){
            h[i][q]=1;
            v[j][q]=1;
            b[(floor(j/3))*3 + floor(i/3)][q]=1;
            arr[i][j] = '1'+q;
            if(sudoku_solver(arr,((i==(n-1))?0:(i+1)),j+(i/(n-1)),n,h,v,b)){return 1;}
            h[i][q]=0;
            v[j][q]=0;
            b[(floor(j/3))*3 + floor(i/3)][q]=0;
            arr[i][j]='.';
        }
    }
    return 0;
}

void sudoku_filler(vector<string> arr,int n){
    vector<vi> h(9),v(9),b(9);
    repr(n){
        rep(j,0,9){
            h[i].pb(0);
            v[i].pb(0);
            b[i].pb(0);
        }
    }
    repr(n){
        rep(j,0,n){
            if(arr[i][j]!='.'){
                int x = arr[i][j]-'1';
                h[i][x]=1;v[j][x]=1;b[(floor(j/3))*3 + floor(i/3)][x]=1;
            }
        }
    }
    sudoku_solver(arr,0,0,n,h,v,b);
    repr(n){
        cout<<arr[i]<<endl;
    }
}

signed main(){
    
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int t=1,curr=1;
    cin>>t;
    while (t--){
        //cout<<"Case #"<<curr++<<": ";
        solve();
    }
    return 0;
}



