// C++ program for addition of two polynomials
// using Linked Lists
#include<bits/stdc++.h>
#include<math.h>
using namespace std;

// Node structure containing power and coefficient of variable
struct Node
{
    int coeff;
    int pow;
    struct Node *next;
};

void sort_list(Node *head)
{
     Node *p;
     Node *q;
     p=q=head;
     for(;p->next!=NULL;p=p->next)
         for(q=head;q->next!=NULL;q=q->next)
             if(q->pow>q->next->pow)
             {
                 swap(q->pow,q->next->pow);
                 swap(q->coeff,q->next->coeff);
             }

}
// Function to create new node
void create_node(int x, int y, struct Node *&temp)
{
    if(temp==NULL) {
        temp = new Node;
        temp->pow = y;
        temp->coeff = x;
        return;
    } else
    {
        Node *p=temp;
        for(p;p->next!=NULL;p=p->next);
        p->next=new Node;
        p->next->coeff=x;
        p->next->pow=y;
        p->next->next=NULL;
    }
}

void union_list(Node **p)
{
    Node *T=*p;
    Node *temp1=NULL;
    while(T!=NULL) {
        int x=T->coeff;
        int y=T->pow;
        while (1) {
            if(T->next!=NULL&&y==T->next->pow)
            {
                x=x+T->next->coeff;
                T=T->next;
            }
            else
            {
                T=T->next;
                break;
            }
        }
        create_node(x,y,temp1);
    }
    *p=temp1;
}

void mulitiple(struct Node *poly1,struct Node *poly2,struct Node **poly)
{
    int x,y;
    Node *pNew=NULL;
    Node *temp1=poly1;
    Node *temp2=poly2;
    while(temp1!=NULL)
    {
        while(temp2!=NULL)
        {
            x=temp1->coeff*temp2->coeff;
            y=temp1->pow+temp2->pow;
            create_node(x,y,pNew);
            temp2=temp2->next;
        }
        temp2=poly2;
        temp1=temp1->next;
    }
    sort_list(pNew);
    union_list(&pNew);
    *poly=pNew;
}
// Function Adding two polynomial numbers
void polyadd(struct Node *poly1, struct Node *poly2, struct Node *poly)
{
    while(poly1->next && poly2->next)
    {
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is
        // and move its pointer
        if(poly1->pow > poly2->pow)
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }

            // If power of 2nd polynomial is greater then 1st, then store 2nd as it is
            // and move its pointer
        else if(poly1->pow < poly2->pow)
        {
            poly->pow = poly2->pow;
            poly->coeff = poly2->coeff;
            poly2 = poly2->next;
        }

            // If power of both polynomial numbers is same then add their coefficients
        else
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff+poly2->coeff;
            poly1 = poly1->next;
            poly2 = poly2->next;
        }

        // Dynamically create new node
        poly->next = (struct Node *)malloc(sizeof(struct Node));
        poly = poly->next;
        poly->next = NULL;
    }
    while(poly1->next || poly2->next)
    {
        if(poly1->next)
        {
            poly->pow = poly1->pow;
            poly->coeff = poly1->coeff;
            poly1 = poly1->next;
        }
        if(poly2->next)
        {
            poly->pow = poly2->pow;
            poly->coeff = poly2->coeff;
            poly2 = poly2->next;
        }
        poly->next = (struct Node *)malloc(sizeof(struct Node));
        poly = poly->next;
        poly->next = NULL;
    }
}

// Display Linked list
void show(struct Node *node)
{
    while(node != NULL)
    {
        printf("%dx^%d", node->coeff, node->pow);
        if(node->next != NULL)
            printf(" + ");
        node=node->next;
    }
}

// Driver  program
int main()
{
    struct Node *poly1 = NULL, *poly2 = NULL, *poly = NULL;

    // Create first list of 5x^2 + 4x^1 + 2x^0
    create_node(5,2,poly1);
    create_node(4,1,poly1);
    create_node(2,0,poly1);
    // Create second list of 5x^1 + 5x^0
    create_node(5,1,poly2);
    create_node(5,0,poly2);

    printf("1st Number: ");
    show(poly1);

    printf("\n2nd Number: ");
    show(poly2);

    poly = (struct Node *)malloc(sizeof(struct Node));

    // Function add two polynomial numbers
    mulitiple(poly1, poly2, &poly);
    // Display resultant List
    printf("\nAdded polynomial: ");
    show(poly);

    return 0;
}


