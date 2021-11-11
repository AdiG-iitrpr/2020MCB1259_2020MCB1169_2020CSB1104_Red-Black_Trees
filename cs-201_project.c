#include <stdio.h>
#include <stdlib.h>
#define RED 1
#define BLACK 0
struct tree
{
    int color;
    int key;
    struct tree *left;
    struct tree *right;
    struct tree *p;
};
struct tree *NIL = NULL;
struct tree *newNode(int val)
{
    struct tree *temp = (struct tree *)malloc(sizeof(struct tree));
    temp->key = val;
    temp->left = NIL;
    temp->right = NIL;
    temp->p = NIL;
    temp->color = RED;
    return temp;
}
struct tree *left_rotate(struct tree *root, struct tree *x)
{
    struct tree *y;
    y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NIL)
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
    return root;
}
struct tree *right_rotate(struct tree *root, struct tree *x)
{
    struct tree *y;
    y = x->left;
    x->left = y->right;
    if (y->right != NIL)
    {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == NIL)
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
    return root;
}
struct tree *insert_fixup(struct tree *root, struct tree *z)
{
    while (z->p->color == RED)
    {
        if (z->p == z->p->p->left)
        {
            struct tree *y = z->p->p->right;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->right)
            {
                z = z->p;
                root = left_rotate(root, z);
            }
            if (z->p != NIL && z->p->p != NIL)
            {
                z->p->color = BLACK;
                z->p->p->color = RED;
                root = right_rotate(root, z->p->p);
            }
        }
        else
        {
            struct tree *y = z->p->p->left;
            if (y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else if (z == z->p->left)
            {
                z = z->p;
                root = right_rotate(root, z);
            }
            if (z->p != NIL && z->p->p != NIL)
            {
                z->p->color = BLACK;
                z->p->p->color = RED;
                root = left_rotate(root, z->p->p);
            }
        }
    }
    root->color = BLACK;
    return root;
}
struct tree *insert(struct tree *root, int key)
{
    if (root == NULL)
    {
        return newNode(key);
    }
    else
    {
        struct tree *y = NIL;
        struct tree *x = root;
        struct tree *z = newNode(key);
        while (x != NIL)
        {
            y = x;
            if (key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        z->p = y;
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        root = insert_fixup(root, z);
        return root;
    }
}
/*void Transplant(struct tree *t, struct tree *u, struct tree *v)
{
    if (u->p == NULL)
    {
        t = v;
    }
    else if (u == u->p->left)
    {
        u->p->left = v;
    }
    else
    {
        u->p->right = v;
    }
    v->p = u->p;
}
void delete (struct tree*root,struct tree *t, struct tree *z)
{
    struct tree *y = z;
    struct tree *x;
    int original = y->color;
    if (z->left == NULL)
    {
        x = z->right;
        Transplant(t, z, z->right);
    }
    else if (z->right == NULL)
    {
        x = z->left;
        Transplant(t, z, z->left);
    }
    else
    {
        y = minimum(z->right); //we have to add function
        original = y->color;
        x = y->right;
        if (y->p == z)
        {
            x->p = y;
        }
        else
        {
            Transplant(t, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        Transplant(t, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if (original == BLACK)
    {
        delete_fixup(root,t, x);
    }
}
delete_fixup(struct tree *root,struct tree *t, struct tree *x)
{
    struct tree* w = (struct tree*)malloc(sizeof(struct tree));
    while (x != t && x->color == BLACK)
    {
        if (x == x->p->left)
            w = x->p->right;
        if (w->color == RED)
        {
            w->color = BLACK;
            x->p->color = RED;
            left_rotate(root,x->p);
            w = x->p->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK)
        {
            w->color = RED;
            x = x->p;
        }
        else if (w->right->color == BLACK)
        {
            w->left->color = BLACK;
            w->color = RED;
            right_rotate(root,w);
            w = x->p->right;
        }
        w->color = x->p->color;
        x->p->color = BLACK;
        w->right->color = BLACK;
        left_rotate(root,x->p);
        x = t;
    }
    x->color = BLACK;
}*/
void display(struct tree *root)
{
    struct tree *temp = root;
    if (temp != NIL)
    {
        display(temp->left);
        printf("%d ", temp->key);
        if (temp->color == BLACK)
        {
            printf("Black\n");
        }
        else
        {
            printf("Red\n");
        }
        display(temp->right);
    }
}
struct tree *search(struct tree *root, int val)
{
    if (root == NULL || root->key == val)
        return root;

    if (root->key < val)
        return search(root->right, val);

    return search(root->left, val);
}
int main()
{
    NIL = (struct tree *)malloc(sizeof(struct tree));
    NIL->color = BLACK;
    struct tree *root = NULL;
    printf("Enter number of terms: ");
    int n, val;
    scanf("%d", &n);
    printf("Enter value to insert\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &val);
        if (i == 0)
        {
            root = insert(root, val);
            root->color = BLACK;
        }
        else
        {
            root = insert(root, val);
        }
    }
    display(root);
    printf("%d\n", root->key);
    return 0;
}