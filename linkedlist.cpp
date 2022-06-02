#include <iostream>

using namespace std;

class node{
public:
    int data;
    node* next;
    
    node(int val){
        data = val;
        next = NULL;
    }
};

void insertattail(node* &head,int val){
    node* n = new node(val);
    
    if(head==NULL){
        head=n;
        return;
    }
    
    node* temp = head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=n;
}

void display(node* &head){
    node* temp = head;
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }
    cout<<endl;
}

void insertathead(node* &head,int val){
    node* n = new node(val);
    n->next = head;
    head = n;
}

bool search(node* &head,int key){
    node* temp = head;
    while(temp->next!=NULL){
        if(temp->data==key){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}



void solve(){
    int m,n;
    cin>>m>>n;
    vector<vi> x(n);
    rep(i,0,m){
        rep(j,0,n){
            int y;
            cin>>y;
            x[j].push_back(y);
        }
    }
    if(m<n){
        vi ans;
        rep(j,0,n){
            ans.push_back(*max_element(x[j].begin(),x[j].end()));
        }
        cout<<*min_element(ans.begin(),ans.end())<<endl;
    }
    
}



void solve(){
    int n;
    cin>>n;
    string a,b;
    cin>>a;
    cin>>b;
    int x = myXOR(stoi(a),stoi(b));
    if(x%2==0&&(n-x)%2==1){
        cout<<min(x, n-x)<<endl;
        return;
    }
    if(x%2==0){
        cout<<x<<endl;
        return;
    }
    if((n-x)%2==1){
        cout<<n-x<<endl;
        return;
    }
    else{
        cout<<-1<<endl;
    }
}

void deletion(node* &head,int val){
    node* temp = head;
    node* n = nullptr;
    if(temp->data==val){
        head=head->next;
        return;
    }
    
    while(temp->next!=NULL){
        if(temp->next->data==val){
            n=temp->next;
            temp->next=temp->next->next;
            break;
        }
        temp = temp->next;
    }
    
    delete n;
}

void reverse(node* &head){
    node* prev=NULL;
    node* curr = head;
    node* nex = head->next;
    while(curr!=NULL){
        curr->next = prev;
        prev=curr;
        curr=nex;
        if(nex!=NULL)
            nex=nex->next;
    }
    head=prev;
}

node* recrev(node* &head){
    if(head==NULL||head->next==NULL){
        return head;
    }
    node* newhead = recrev(head->next);
    head->next->next = head;
    head->next = NULL;
    return newhead;
}

node* reversek(node* &head,int k){
    node* prev = NULL;
    node* curr = head;
    node* nex;
    
    int count=0;
    while(curr!=NULL&&count<k){
        nex = curr->next;
        curr->next=prev;
        prev = curr;
        curr = nex;
        count++;
    }
    if(nex!=NULL)
        head->next = reversek(nex, k);
    
    return prev;
}

bool detectcycle(node* &head){
    node* fast = head;
    node* slow = head;
    while(fast!=NULL && fast->next!=NULL){
        fast = fast->next->next;
        slow = slow->next;
        
        if(fast == slow){return 1;}
    }
    return 0;
}

void makecycle(node* &head,int pos){
    node* temp;
    node* trav = head;
    int posk =0;
    while(trav->next!=NULL){
        posk++;
        if(posk==pos)
            temp = trav;
        trav = trav->next;
    }
    trav->next = temp;
}

void straight(node* &head){
    if(!detectcycle(head)){return;}
    
    node* fast = head;
    node* slow = head;
    
    do{
        slow = slow->next;
        fast = fast->next->next;
    }while(fast!=slow);
    fast = head;
    while(fast->next!=slow->next){
        slow = slow->next;
        fast = fast->next;
    }
    slow->next=NULL;
}

node* sortmerge(node* &head1,node* &head2){
    node* pt1 = head1;
    node* pt2 = head2;
    
    node* k = new node(0);
    node* ans =k;
//    k = k->next;
    
    while(pt1!=NULL&&pt2!=NULL){
        if((pt1->data)>(pt2->data)){
            k->next = pt2;
            pt2 = pt2->next;
        }
        else{
            k->next=pt1;
            pt1 = pt1->next;
        }
        
        k = k->next;
        
    }
    
    if(pt1==NULL)
        k->next=pt2;
    else
        k->next=pt1;
    
    return ans->next;
}

node* sortmergerecursive(node* &head1,node* &head2){
    
    if(head1==NULL){return head2;}
    if(head2==NULL){return head1;}
    
    if(head1->data>head2->data){
        head2->next = sortmergerecursive(head1,head2->next);
        return head2;
    }
    head1->next = sortmergerecursive(head1->next,head2);
    return head1;
    
}

int main(){
    node* head = NULL;
    
    insertattail(head, 1);
    insertattail(head, 3);
    insertattail(head, 5);
    insertattail(head, 7);
    insertattail(head, 2);
    insertattail(head, 3);
    insertattail(head, 4);
    display(head);
    
    node* con = head->next;
    node* even = head->next;
    node* odd = head;
    node* temp = head->next->next;
    
    while(temp!=NULL){
        
        odd->next = temp;
        temp = temp->next;
        odd=odd->next;
        
        if(temp == NULL)
            break;
        
        even->next = temp;
        temp = temp->next;
        even=even->next;
    }
    even->next = NULL;
    odd->next = con;
    display(head);
    
}


