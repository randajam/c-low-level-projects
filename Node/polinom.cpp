#include <iostream>

using namespace std;

struct node {    
    int koef;
    int exp;
    node* next;
};

node* create(int koef, int exp) {
    node* n = new node;
    n->koef = koef;
    n->exp = exp;
    n->next = NULL;
    return n;
}

void insert(node* head, int koef, int exp){ 
    node* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    node* n = create(koef, exp);
    temp->next = n;
    return;
}

node* create_node(int size) {
    node* head = create(0,0);
    for(int i = 0; i < size; i++){
        int koef, exp;
        cin >> koef;
        cin >> exp;
        insert(head, koef, exp);
    }
    return head;
}

void print(node* head) {
    node* temp = head;
    while(temp != NULL){
        if (temp->exp == 0){
            cout << "(" << temp->koef << ")" << "+";
        }
        else if (temp->exp == 1){
            cout << "(" << temp->koef << "x)" << "+";
        }
        else {
            cout << "(" << temp->koef << "x^" << temp->exp << ")" << "+";
        }
        temp = temp->next;
    }
    cout << "NULL" << endl;
    return;
}

void combine_like_terms(node* head) {
    node* temp = head;
    while(temp != NULL){
        node* temp2 = temp;
        while(temp2->next != NULL){
            if(temp->exp == temp2->next->exp){
                temp->koef += temp2->next->koef;
                node* to_delete = temp2->next;
                temp2->next = temp2->next->next;
                delete to_delete;
            }
            else{
                temp2 = temp2->next;
            }
        }
        temp = temp->next;
    }
    return;
}

void sort(node* head) {
   node* current_node = head;
   while(current_node != NULL) {
       node* next_node = current_node;
       while(next_node->next != NULL) {
           if(next_node->exp > next_node->next->exp){
               int temp_swap = next_node->koef;
               next_node->koef = next_node->next->koef;
               next_node->next->koef = temp_swap;

               temp_swap = next_node->exp;
               next_node->exp = next_node->next->exp;
               next_node->next->exp = temp_swap;
           }       
           next_node = next_node->next;
       }
       current_node = current_node->next;
   }
}

node* sum_sorting_node(node* head1, node* head2) {
    node* head3 = create(0,0);
    node* temp1 = head1;
    node* temp2 = head2;
    while(temp1 != NULL && temp2 != NULL){
        if(temp1->exp == temp2->exp){
            insert(head3, temp1->koef + temp2->koef, temp1->exp);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if(temp1->exp < temp2->exp){
            insert(head3, temp1->koef, temp1->exp);
            temp1 = temp1->next;
        }
        else{
            insert(head3, temp2->koef, temp2->exp);
            temp2 = temp2->next;
        }
    }
    while(temp1 != NULL){
        insert(head3, temp1->koef, temp1->exp);
        temp1 = temp1->next;
    }
    while(temp2 != NULL){
        insert(head3, temp2->koef, temp2->exp);
        temp2 = temp2->next;
    }
    return head3;
}

void multiply_on_pol(node* head, int k) {
    node* temp = head;
    while(temp != NULL){
        temp->koef *= k;
        temp = temp->next;
    }
}

node* multiply(node* head1, node* head2) {
    node* head3 = create(0,0);
    node* temp1 = head1;
    node* temp2 = head2;
    while(temp1 != NULL){
        while(temp2 != NULL){
            int koef = temp1->koef * temp2->koef;
            int exp = temp1->exp + temp2->exp;
            insert(head3, koef, exp);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
        temp2 = head2;
    }
    combine_like_terms(head3);
    sort(head3);
    return head3;
}

int main()
{
    int n = 0;
    cin >> n;
    node* head1 = create_node(n);
    node* head2 = create_node(n);
    combine_like_terms(head1);
    combine_like_terms(head2);
    sort(head1);
    sort(head2);
    print(head1);
    print(head2);
    node* head3 = multiply(head1, head2);
    print(head3);
    return 0;
}