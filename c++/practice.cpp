#include<bits/stdc++.h>
using namespace std;  
struct Node{

    int data;
    Node* next;

    Node(int data1,Node*  next1){

        data = data1;
        next = next1;


    }
    Node(int data1){
        data = data1;
        next = nullptr;
    }
   
};
 Node* InsertAtBeginning(Node* &head,int val){
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        return head;
    }
Node* InsertAtEnd(Node* head, int val) {
    Node* newNode = new Node(val);

    // if (head == nullptr)
    //     return newNode;

    Node* temp = head;

    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;

    return head;
}
Node* insertAtPosition(Node* head,int pos,int val)
{
    if(pos==1)
        return insertAtBeginning(head,val);

    Node* newNode=new Node(val);

    Node* temp=head;

    for(int i=1;i<pos-1 && temp!=NULL;i++)
    {
        temp=temp->next;
    }

    if(temp==NULL)
        return head;

    newNode->next=temp->next;

    temp->next=newNode;

    return head;
}

int main() {
   int arr[5] = {1, 2, 3, 4, 5};    
   
    Node* head = new Node(2);
    head->next = new Node(5);
    head->next->next = new Node(10);
    head->next->next->next = new Node(20);
    
    
    cout<<endl;
    head = InsertAtBeginning(head,5);
    
    head= InsertAtEnd(head,90);
Node* temp = head;
    while(temp != NULL){
        cout<<temp->data<<" ";
        temp = temp->next;
    }   
    
    return 0;
}           