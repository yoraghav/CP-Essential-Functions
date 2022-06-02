#include "bits/stdc++.h"
 
using namespace std;

#define int long long int
#define vi vector<int>
#define pii pair<int,int>
#define vii vector<pii>
#define vn vector<node*>
#define rep(i,a,b) for(int i=a; i<b; i++)
#define repr(b) for(int i=0; i<b; i++)
#define prin(vec) for(int i=0;i<vec.size();i++){cout<<vec[i]<<" ";}cout<<endl
#define newvec(x,n) vi x(n);rep(i,0,n){cin>>x[i];}
#define float long double
#define vip vector<int>::iterator
#define mod 10000007
#define printvn(vec) repr(vec.size()){cout<<vec[i]->data<<" ";}cout<<endl;

//cout.precision(17);

struct node{
    int data;
    struct node* left;
    struct node* right;
    node(int val){
        left = NULL;
        right = NULL;
        data = val;
    }
};

void preorder(node* k){
    if(k==NULL){return;}
    preorder(k->left);
    cout<<k->data<<" ";
    preorder(k->right);
}

void summer(node* k,int level){
    queue<node*> q;
    q.push(k);
    q.push(NULL);
    int sum=0;
    int l=0;
    while(!q.empty()){
        if(l==level){
            while(q.front()!=NULL){
                sum+= q.front()->data;
                q.pop();
            }
            break;
        }
        while(q.front()!=NULL){
            node* temp = q.front();
            q.pop();
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
        q.pop();
        q.push(NULL);
        l++;
    }
    cout<<sum<<endl;
}

int count_nodes(node* root){
    if(root==NULL){return 0;}
    return count_nodes(root->left) + count_nodes(root->right) + 1;
}

int height(node* root){
    if(root==NULL){return 0;}
    return max(height(root->left), height(root->right)) + 1;
}

int diameter(node* root, int* height){
    // to use just input a rondom int variable address for height i.e. &h
    if(root==NULL){return 0;}
    int l=0,r=0;
    int k = max(diameter(root->left,&l),diameter(root->right,&r));
    *height = max(l,r)+1;
    return max(k,l+r+1);
}

void sum_replacement(node* root){
    if(root==NULL){return;}
    sum_replacement(root->left);
    sum_replacement(root->right);
    if(root->left){root->data +=root->left->data;}
    if(root->right){root->data +=root->right->data;}
}

bool isBalanced(node* root, int* height){
    if(root == NULL){*height = 0;return true;}
    int l,r;
    if(!isBalanced(root->left,&l)||!isBalanced(root->right,&r)){return false;}
    *height = max(l,r)+1;
    if(abs(l-r)>1){return false;}return true;
}

vn right_view(node*root){
    queue<node*> q;
    q.push(root);
    q.push(NULL);
    vn x;
    while(q.front()!=NULL){
        x.push_back(q.front());
        while(q.front()!=NULL){
            node* temp = q.front();
            q.pop();
            if(temp->right){q.push(temp->right);}
            if(temp->left){q.push(temp->left);}
        }
        q.pop();
        q.push(NULL);
    }
    return x;
}

vn left_view(node*root){
    queue<node*> q;
    q.push(root);
    q.push(NULL);
    vn x;
    while(q.front()!=NULL){
        x.push_back(q.front());
        while(q.front()!=NULL){
            node* temp = q.front();
            q.pop();
            if(temp->left){q.push(temp->left);}
            if(temp->right){q.push(temp->right);}
        }
        q.pop();
        q.push(NULL);
    }
    return x;
}

bool getPath(node* root,int val,vn &path){
    if(root == NULL){return false;}
    path.push_back(root);
    if(root->data == val){return true;}
    if(getPath(root->left, val, path) || getPath(root->right, val, path)){return true;}
    path.pop_back();
    return false;
}

node* LCA(node* root,int v1, int v2){
    if(root==NULL){return NULL;}
    if(root->data == v1 || root->data == v2){return root;}
    node* a1 = LCA(root->left, v1, v2);
    node* a2 = LCA(root->right,v1,v2);
    
    
    if(a1!=NULL && a2!= NULL){
        return root;
    }
    
    if(a1!=NULL){return a1;}
    return a2;
}

int PathLength(node* root,int val){
    if(root==NULL){return -1;}
    if(root->data==val){return 0;}
    int x = PathLength(root->left, val)+PathLength(root->right, val);
    if(x>-2){
        return x+2;
    }
    return -1;
}

node* flatten(node* root){
    if(root==NULL){return NULL;}
    node* lefter = flatten(root->left);
    node* righter = flatten(root->right);
    if(lefter==NULL && righter==NULL){return root;}
    if(lefter==NULL){
        return righter;
    }
    lefter->right = root->right;
    root->right = root->left;
    root->left = NULL;
    if(righter == NULL){return lefter;}
    return righter;
}

void printDistNode(node* root,int dist,node* ban){
    if(root==NULL||root==ban||dist<0){return;}
    if(dist==0){cout<<root->data<<" ";return;}
    printDistNode(root->left, dist-1,ban);
    printDistNode(root->right, dist-1,ban);
}

int maxsumpath(node* root,int &maxm){
    if(root==NULL){return 0;}
    int ls = maxsumpath(root->left,maxm);
    int rs = maxsumpath(root->right,maxm);
    int lmaxm = max(max(max(ls,rs),max(ls+(root->data),rs+(root->data))),max(ls+rs+(root->data),root->data));
    if(lmaxm>maxm){maxm = lmaxm;}
    return root->data+max(rs,ls);
}

void boundaryleft(node* root){
    if(root->right==NULL && root->left==NULL){return;}
    cout<<root->data<<" ";
    if(root->left == NULL){boundaryleft(root->right);return;}
    boundaryleft(root->left);
}

void boundaryright(node* root){
    if(root==NULL){return;}
    if(root->right==NULL && root->left==NULL){return;}
    if(root->right == NULL){boundaryright(root->left);return;}
    boundaryright(root->right);
    cout<<root->data<<" ";
}

void boundary(node* root){
    if(root==NULL){return;}
    if(root->right==NULL && root->left==NULL){cout<<root->data<<" ";}
    boundary(root->left);
    boundary(root->right);
}

void BSTaddNode(node* root,int val){
    if(root==NULL){return;}
    if(val>root->data){
        if(root->right==NULL){
            node* v = new node(val);
            root->right = v;
            return;
        }
        BSTaddNode(root->right,val);
        return;
    }
    if(root->left==NULL){
            node* v = new node(val);
            root->left = v;
            return;
        }
    BSTaddNode(root->left,val);
    return;
}

node* BSTbuilder(vi a){
    if(!a.size()){return NULL;}
    node* root = new node(a[0]);
    rep(i,1,a.size()){
        BSTaddNode(root,a[i]);
    }
    return root;
}

node* searchInBST(node* root,int val){
    if(root==NULL){return NULL;}
    if(root->data == val){
        return root;
    }
    if(root->data>val){
        return searchInBST(root->right,val);
    }
    return searchInBST(root->left,val);
}

node* deleteInBST(node* root,int val){
    if(root==NULL){return NULL;}
    if(root->data == val){
        if(root->left==NULL){return root->right;}
        if(root->right==NULL){return root->left;}
        if(root->left->data > root->data){
            node* temp = root->right;
            node* newroot = root->left;
            root->left = newroot->left;
            root->right = newroot->right;
            newroot->left = deleteInBST(root,val);
            newroot->right = temp;
            return newroot;
        }
        node* temp = root->left;
        node* newroot = root->right;
        root->left = newroot->left;
        root->right = newroot->right;
        newroot->left = temp;
        newroot->right = deleteInBST(root,val);
        return newroot;
    }
    else if(val>root->data){
        root->right = deleteInBST(root->right,val);
    }
    else{
        root->left = deleteInBST(root->left,val);
    }
    return root;
}

node* BuildBSTfromPreorder(vi arr,int &i,int max=-1,int min=-1){
    if(i==arr.size()){return NULL;}
    if((max==-1 || arr[i]<max) && (min==-1||arr[i]>=min)){
        node* ans = new node(arr[i]);
        i++;
        ans->left = BuildBSTfromPreorder(arr,i,ans->data,min);
        ans->right = BuildBSTfromPreorder(arr,i,max,ans->data);
        return ans;
    }
    return NULL;
}

bool ifBST(node* root,int max=-1,int min=-1){
    if(root==NULL){return 1;}
    if((max==-1 || root->data<max) && (min==-1||root->data>=min)){
        return ifBST(root->left,root->data,min) && ifBST(root->right,max,root->data);
    }
    return 0;
}

void printInOrder(node* root){
    if(root==NULL){return;}
    cout<<root->data<<" ";
    printInOrder(root->left);
    printInOrder(root->right);
}
int catalan(int n){
    vi x;
    x.push_back(1);
    x.push_back(1);
    rep(a,2,n+1){
        int i=0,j=x.size()-1;
        int ans=0;
        while(i<=j){
            ans+= ((i==j?1:2)*(x[i]*x[j]));
            i++;j--;
        }
        x.push_back(ans);
    }
    return x[n];
}

void printZigZag(stack<node*> arr,bool right){

    // stack<node*> a;
    // a.push(br);
    // printZigZag(a,0);


    if(arr.empty()){return;}
    stack<node*> arr2;
    while(!arr.empty()){
        node* root = arr.top();
        arr.pop();
        if(right){
            if(root->left){arr2.push(root->left);}
            if(root->right){arr2.push(root->right);}
        }
        else{
            if(root->right){arr2.push(root->right);}
            if(root->left){arr2.push(root->left);}
        }
        cout<<root->data<<" ";
    }
    printZigZag(arr2,!right);
}

node* BuildBalancedBSTfromSorted(vi arr,int l,int r){
    if(l>r){return NULL;}
    if(l==r){
        return (new node(arr[l]));
    }
    int mid = (l+r)/2 + (l+r)%2;
    node* ans = new node(arr[mid]);
    ans->left = BuildBalancedBSTfromSorted(arr,l,mid-1);
    ans->right = BuildBalancedBSTfromSorted(arr,mid+1,r);
    return ans;
}

struct Info{
    int size;
    int min;
    int max;
    int ans;
    bool IsBST;
};

Info largestBSTinBT(node* root){
    if(root==NULL){return {0,INT_MAX,INT_MIN,0,true};}
    if(root->left==NULL && root->right==NULL){
        return {1,root->data,root->data,1,true};
    }
    Info leftInfo = largestBSTinBT(root->left);
    Info rightInfo = largestBSTinBT(root->right);
    if(leftInfo.IsBST && rightInfo.IsBST && rightInfo.min > root->data && leftInfo.max <= root->data){
        //cout<<root->data<<" "<<leftInfo.size + rightInfo.size + 1<<endl;
        return {leftInfo.size + rightInfo.size + 1,min(leftInfo.min,root->data),max(rightInfo.max,root->data),leftInfo.size + rightInfo.size + 1,true};
    }
    return {0,0,0,max(leftInfo.ans,rightInfo.ans),false};
}


signed main(){
    //              5
    //            /   \
    //           /     \
    //          /       \
    //         6         3
    //       /   \     /   \
    //      1     9   7    11
    //           /     \
    //          2       10
    //         / \      /
    //        4   5    8  
    
    struct node* br = new node(5);

    br->left = new node(6);
    br->right = new node(3);
    br->left->left = new node(1);
    br->left->right = new node(9);
    br->left->right->left = new node(2);
    br->left->right->left->left = new node(4);
    br->left->right->left->right = new node(5);
    br->right->left = new node(7);
    br->right->left->right = new node(10);
    br->right->left->right->left = new node(8);
    br->right->right = new node(11);

    int x[7] = {2,3,4,5,6,7,8};
    vi y;
    repr(7){
        y.push_back(x[i]);
    }
    int si=0,sizet=0;

    Info anse = largestBSTinBT(br);
    cout<<anse.ans<<endl;
}

