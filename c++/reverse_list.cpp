#include<bits/stdc++.h>
using namespace std;
struct Node{
    int data;
    Node* next;
    Node(int data1){
        data = data1;
        next = nullptr;
    }

};
void printList(Node* head){
    while(head){
        cout<<head->data<<" ";
        head = head->next;
    }
    cout<<endl;
}
Node* reverseList(Node* head){
    Node* prev = NULL;
    Node* curr  = head;
    Node* nextNode  = NULL;

    while(curr!=NULL){
        nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}
int main(){
    Node* head = new Node(10);
    head->next = new Node(20);
    head->next->next = new Node(30);
    head->next->next->next = new Node(40);
   
    cout<<"before reverse : ";
    printList(head);
    head = reverseList(head);
    cout<<"after reverse: ";
    return 0;
}