#include <stdio.h>
#include <stdlib.h>
struct tree
{
    int color;
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *p;
};
struct tree *root = NULL;
void left_rotate(struct tree *x)
{
    struct tree *y;
    y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NULL)
    {
        root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
}
void right_rotate(struct tree *x)
{
    struct tree *y;
    y = x->left;
    x->left = y->right;
    if (y->right != NULL)
    {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == NULL)
    {
        root = y;
    }
    else if (x == x->p->left)
    {
        x->p->left = y;
    }
    else
    {
        x->p->right = y;
    }
    y->right = x;
    x->p = y;
}
void insert_fixup(struct tree *z)
{
    while (z->p->color == 1)
    {
        if (z->p == z->p->p->left)
        {
            struct tree *y = z->p->p->right;
            if (y->color == 1)
            {
                z->p->color = 0;
                y->color = 0;
                z->p->p->color = 1;
                z = z->p->p;
            }
            else if (z == z->p->right)
            {
                z = z->p;
                left_rotate(z);
            }
            z->p->color = 0;
            z->p->p->color = 1;
            right_rotate(z->p->p);
        }
        else
        {
            struct tree *y = z->p->p->left;
            if (y->color == 1)
            {
                z->p->color = 0;
                y->color = 0;
                z->p->p->color = 1;
                z = z->p->p;
            }
            else if (z == z->p->left)
            {
                z = z->p;
                right_rotate(z);
            }
            z->p->color = 0;
            z->p->p->color = 1;
            left_rotate(z->p->p);
        }
    }
    root->color = 0;
}
struct tree *insert(struct tree *t,struct tree *z)
{
    if (t == NULL)
        return z;
    struct tree *y = NULL;
    struct tree *x = t;
    while (x != NULL)
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NULL)
    {
        t = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    return t;
}
void display()
{
    display(root->left);
    printf("%d ", root->key);
    if (root->color == 0)
    {
        printf("Black\n");
    }
    else
    {
        printf("Red\n");
    }
    display(root->right);
}
int main()
{
    printf("Enter number of terms: ");
    int n, val;
    scanf("%d", &n);
    printf("Enter value to insert\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
        temp->key = val;
        temp->color = 1;
        temp->left = NULL;
        temp->right = NULL;
        temp->p = NULL;
        root = insert(root,temp);
        insert_fixup(temp);
    }
    display();
    return 0;
}