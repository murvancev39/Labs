#include "RB_tree.h"

RB_node_t *RB_insert (RB_node_t *tree, RB_node_t *parent, unsigned key)
{
    if (!tree) 
    {
        RB_node_t *node = (RB_node_t *) calloc (1, sizeof (RB_node_t));
        node->key = key;
        node->color = red;
        node->parent = parent;
        return node;
    }

    if (tree->key == key) 
    {
        return tree;
    }

    if (tree->key > key) 
    {
        tree->left_node = RB_insert (tree->left_node, tree, key);
    } 
    else 
    {
        tree->right_node = RB_insert (tree->right_node, tree, key);
    }

    return tree;
}

int RB_add (void *tree_v, unsigned key)
{
    RB_tree_t *tree = tree_v;
    if (!tree) return 1;

    RB_node_t *exists = RB_search_n (tree->root, key);
    
    tree->root = RB_insert (tree->root, NULL, key);

    if (!exists)
    {
        RB_node_t *new_node = RB_search_n (tree->root, key);
        if (new_node)
        {
            RB_fix (tree, new_node);
            tree->count++; 
        }
        else return 1;
    }

    if (tree->root) tree->root->color = black;
    
    return 0;
}

void RB_fix (RB_tree_t *tree, RB_node_t *node)
{
    if (!node || !tree) return;
    
    RB_node_t *dod = node->parent;
    
    if (!dod || dod->color == black) 
    {
        if (!dod) node->color = black;
        return; 
    }

    RB_node_t *pradod = dod->parent;

    if (!pradod) 
    {
        dod->color = black;
        return;
    }

    RB_node_t *left_uncle = pradod->left_node;
    RB_node_t *right_uncle = pradod->right_node;
    RB_node_t *uncle = (dod == left_uncle) ? right_uncle : left_uncle;

    if (uncle && uncle->color == red)
    {
        dod->color = black;
        uncle->color = black;
        pradod->color = red;
        RB_fix (tree, pradod);
        return;
    }

    if (dod == left_uncle)
    {
        if (node == dod->right_node)
        {
            RB_rotate (dod, left);
            node = dod;
            dod = node->parent;
        }
        dod->color = black;
        pradod->color = red;
        RB_rotate (pradod, right);
    }
    else
    {
        if (node == dod->left_node)
        {
            RB_rotate (dod, right);
            node = dod;
            dod = node->parent;
        }
        dod->color = black;
        pradod->color = red;
        RB_rotate (pradod, left);
    }

    RB_node_t *curr = node;
    while (curr->parent) curr = curr->parent;
    tree->root = curr;
}

RB_node_t *RB_rotate (RB_node_t *node, side_t side)
{
    if (!node) return NULL;

    RB_node_t *A = node;
    RB_node_t *B = NULL;
    RB_node_t *C = NULL;
    RB_node_t *P = A->parent;

    if (side == right)
    {
        B = A->left_node;
        if (!B) return A;
        C = B->right_node;

        B->right_node = A;
        A->left_node = C;
    }
    else
    {
        B = A->right_node;
        if (!B) return A;
        C = B->left_node;

        B->left_node = A;
        A->right_node = C;
    }

    A->parent = B;
    B->parent = P;
    if (C) C->parent = A;

    if (P)
    {
        if (P->left_node == A) P->left_node = B;
        else P->right_node = B;
    }

    return B;
}

RB_node_t *RB_search_n (RB_node_t *tree, unsigned key)
{
    RB_node_t *node = tree;
    while (node != NULL)
    {
        if (node->key == key) 
        {
            return node;
        }

        if (node->key > key)
        {
            node = node->left_node;
        }
        else 
        {
            node = node->right_node;
        }
    }
    return NULL;
}

RB_node_t *RB_search (RB_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return NULL;
    return RB_search_n (tree->root, key);
}

int RB_delete (void *tree_v, unsigned key)
{
    RB_tree_t *tree = tree_v;
    if (!tree || !tree->root) return 1;

    RB_node_t *target = RB_search_n (tree->root, key);
    if (!target) return 0;

    RB_node_t *y = target;
    RB_node_t *node = NULL;
    RB_node_t *node_parent = NULL;
    color_t y_old_color = y->color;

    if (!target->left_node)
    {
        node = target->right_node;
        node_parent = target->parent;
        RB_transplant (tree, target, target->right_node);
    }
    else if (!target->right_node)
    {
        node = target->left_node;
        node_parent = target->parent;
        RB_transplant (tree, target, target->left_node);
    }
    else
    {
        y = target->right_node;
        while (y->left_node) y = y->left_node;
        
        y_old_color = y->color;
        node = y->right_node;

        if (y->parent == target)
        {
            node_parent = y; 
        }
        else
        {
            node_parent = y->parent;
            RB_transplant (tree, y, y->right_node);
            y->right_node = target->right_node;
            y->right_node->parent = y;
        }

        RB_transplant (tree, target, y);
        y->left_node = target->left_node;
        y->left_node->parent = y;
        y->color = target->color;
    }

    free (target);
    tree->count--;

    if (y_old_color == black)
    {
        RB_fix_delete (tree, node, node_parent);
    }
    return 0;
}

void RB_transplant (RB_tree_t *tree, RB_node_t *first, RB_node_t *second)
{
    if (!first->parent) 
    {
        tree->root = second;
    }
    else if (first == first->parent->left_node)
    {
        first->parent->left_node = second;
    }
    else
    {
        first->parent->right_node = second;
    }

    if (second)
    {
        second->parent = first->parent;
    }
    return;
}
void RB_fix_delete (RB_tree_t *tree, RB_node_t *node, RB_node_t *dod)
{
    while (node != tree->root && (node == NULL || node->color == black))
    {
        if (node == dod->left_node)
        {
            RB_node_t *bro = dod->right_node;

            if (bro && bro->color == red)
            {
                bro->color = black;
                dod->color = red;
                RB_rotate (dod, left);
                bro = dod->right_node;
            }

            if ((!bro->left_node || bro->left_node->color == black) &&
                (!bro->right_node || bro->right_node->color == black))
            {
                if (bro) bro->color = red;
                node = dod;
                dod = node->parent;
            }
            else
            {
                if (!bro->right_node || bro->right_node->color == black)
                {
                    if (bro->left_node) bro->left_node->color = black;
                    bro->color = red;
                    RB_rotate (bro, right);
                    bro = dod->right_node;
                }
                
                bro->color = dod->color;
                dod->color = black;
                if (bro->right_node) bro->right_node->color = black;
                RB_rotate (dod, left);
                node = tree->root; 
            }
        }
        else
        {
            RB_node_t *bro = dod->left_node;

            if (bro && bro->color == red)
            {
                bro->color = black;
                dod->color = red;
                RB_rotate (dod, right);
                bro = dod->left_node;
            }

            if ((!bro->right_node || bro->right_node->color == black) &&
                (!bro->left_node || bro->left_node->color == black))
            {
                if (bro) bro->color = red;
                node = dod;
                dod = node->parent;
            }
            else
            {
                if (!bro->left_node || bro->left_node->color == black)
                {
                    if (bro->right_node) bro->right_node->color = black;
                    bro->color = red;
                    RB_rotate (bro, left);
                    bro = dod->left_node;
                }

                bro->color = dod->color;
                dod->color = black;
                if (bro->left_node) bro->left_node->color = black;
                RB_rotate (dod, right);
                node = tree->root;
            }
        }
    }

    if (node) node->color = black;

    RB_node_t *curr = (node) ? node : dod;
    while (curr && curr->parent) curr = curr->parent;
    tree->root = curr;
    return;
}

void *RB_init ()
{
    RB_tree_t *tree = (RB_tree_t *) calloc (1, sizeof (RB_tree_t));
    
    if (!tree)
    {
        return NULL;
    }

    return tree;
}

void RB_destroy_nodes (RB_node_t *node)
{
    if (!node) return;

    RB_destroy_nodes (node->left_node);
    RB_destroy_nodes (node->right_node);

    free (node);
}

void RB_destroy_tree (void *tree_v)
{
    RB_tree_t *tree = tree_v;
    if (!tree) return;

    RB_destroy_nodes (tree->root);

    free (tree);
}