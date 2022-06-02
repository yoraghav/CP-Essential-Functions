#include <iostream>

using namespace std;

class node{
public:
    int data;
    node* prev;
    node* next;
    node(int val){
        prev = NULL;
        next = NULL;
        data =val;
    }
};

void insertattail(node* &head,int val){
    node* n = new node(val);
    if(head == NULL){
        head = n;
        return;
    }
    node* trav = head;
    while(trav->next!=NULL){
        trav = trav->next;
    }
    trav->next = n;
    n->prev = trav;
}

void display(node* &head){
    node* trav = head;
    while(trav->next!=NULL){
        cout<<trav->data<<" ";
        trav = trav->next;
    }
    cout<<trav->data<<" "<<endl;
}

void deletenode(node* &head,int pos){
    node* temp =head;
    int posk=1;
    while(posk<pos){
        temp = temp->next;
        posk++;
    }
    if(temp->prev!=NULL)
        temp->prev->next = temp->next;
    
    else
        head = head->next;
        head->prev=NULL;
    
    if(temp->next!=NULL)
        temp->next->prev = temp->prev;
    
    delete temp;
}

int main(){
    node* head = NULL;
    insertattail(head, 2);
    insertattail(head, 3);
    insertattail(head, 4);
    insertattail(head, 5);
    display(head);
    deletenode(head, 1);
    display(head);
}



