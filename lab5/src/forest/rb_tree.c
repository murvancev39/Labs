#include "rb_tree.h"

rb_node_t *rb_insert (rb_node_t *tree, rb_node_t *parent, unsigned key)
{
    if (!tree) 
    {
        rb_node_t *node = (rb_node_t *) calloc (1, sizeof (rb_node_t));
        if (!node) return NULL;
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
        tree->left_node = rb_insert (tree->left_node, tree, key);
        if (!tree->left_node) return NULL;
    } 
    else 
    {
        tree->right_node = rb_insert (tree->right_node, tree, key);
        if (!tree->right_node) return NULL;
    }

    return tree;
}

int rb_add (void *tree_v, unsigned key)
{
    rb_tree_t *tree = tree_v;
    if (!tree) return ERROR;

    rb_node_t *exists = rb_search_n (tree->root, key);
    
    rb_node_t *new_root = rb_insert (tree->root, NULL, key);
    if (!new_root && tree->root == NULL) return ERROR;
    tree->root = new_root;

    if (!exists)
    {
        rb_node_t *new_node = rb_search_n (tree->root, key);
        if (new_node)
        {
            rb_fix (tree, new_node);
            tree->count++; 
        }
        else return ERROR;
    }

    if (tree->root) tree->root->color = black;
    
    return OK;
}

void rb_fix (rb_tree_t *tree, rb_node_t *node)
{
    if (!node || !tree) return;
    
    rb_node_t *dod = node->parent;
    
    if (!dod || dod->color == black) 
    {
        if (!dod) node->color = black;
        return; 
    }

    rb_node_t *pradod = dod->parent;

    if (!pradod) 
    {
        dod->color = black;
        return;
    }

    rb_node_t *left_uncle = pradod->left_node;
    rb_node_t *right_uncle = pradod->right_node;
    rb_node_t *uncle = (dod == left_uncle) ? right_uncle : left_uncle;

    if (uncle && uncle->color == red)
    {
        dod->color = black;
        uncle->color = black;
        pradod->color = red;
        rb_fix (tree, pradod);
        return;
    }

    if (dod == left_uncle)
    {
        if (node == dod->right_node)
        {
            rb_rotate (dod, left);
            node = dod;
            dod = node->parent;
        }
        if (!dod) return;
        dod->color = black;
        pradod->color = red;
        rb_rotate (pradod, right);
    }
    else
    {
        if (node == dod->left_node)
        {
            rb_rotate (dod, right);
            node = dod;
            dod = node->parent;
        }
        if (!dod) return;
        dod->color = black;
        pradod->color = red;
        rb_rotate (pradod, left);
    }

    rb_node_t *curr = node;
    while (curr && curr->parent) curr = curr->parent;
    if (curr) tree->root = curr;
}

rb_node_t *rb_rotate (rb_node_t *node, side_t side)
{
    if (!node) return NULL;

    rb_node_t *grandfather = node;
    rb_node_t *dod = NULL;
    rb_node_t *son = NULL;
    rb_node_t *great_grandfather = grandfather->parent;

    if (side == right)
    {
        dod = grandfather->left_node;
        if (!dod) return grandfather;
        son = dod->right_node;

        dod->right_node = grandfather;
        grandfather->left_node = son;
    }
    else
    {
        dod = grandfather->right_node;
        if (!dod) return grandfather;
        son = dod->left_node;

        dod->left_node = grandfather;
        grandfather->right_node = son;
    }

    grandfather->parent = dod;
    dod->parent = great_grandfather;
    if (son) son->parent = grandfather;

    if (great_grandfather)
    {
        if (great_grandfather->left_node == grandfather) 
            great_grandfather->left_node = dod;
        else 
            great_grandfather->right_node = dod;
    }

    return dod;
}

rb_node_t *rb_search_n (rb_node_t *tree, unsigned key)
{
    rb_node_t *node = tree;
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

rb_node_t *rb_search (rb_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return NULL;
    return rb_search_n (tree->root, key);
}

int rb_delete (void *tree_v, unsigned key)
{
    rb_tree_t *tree = tree_v;
    if (!tree || !tree->root) return ERROR;

    rb_node_t *target = rb_search_n (tree->root, key);
    if (!target) return OK;

    rb_node_t *y = target;
    rb_node_t *node = NULL;
    rb_node_t *node_parent = NULL;
    color_t y_old_color = y->color;

    if (!target->left_node)
    {
        node = target->right_node;
        node_parent = target->parent;
        rb_transplant (tree, target, target->right_node);
    }
    else if (!target->right_node)
    {
        node = target->left_node;
        node_parent = target->parent;
        rb_transplant (tree, target, target->left_node);
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
            rb_transplant (tree, y, y->right_node);
            y->right_node = target->right_node;
            if (y->right_node) y->right_node->parent = y;
        }

        rb_transplant (tree, target, y);
        y->left_node = target->left_node;
        if (y->left_node) y->left_node->parent = y;
        y->color = target->color;
    }

    free (target);
    tree->count--;

    if (y_old_color == black)
    {
        rb_fix_delete (tree, node, node_parent);
    }
    return OK;
}

void rb_transplant (rb_tree_t *tree, rb_node_t *first, rb_node_t *second)
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
}

void rb_fix_delete (rb_tree_t *tree, rb_node_t *node, rb_node_t *dod)
{
    if (!tree || !dod) return;

    while (node != tree->root && (node == NULL || node->color == black))
    {
        if (node == dod->left_node)
        {
            rb_node_t *bro = dod->right_node;
            if (!bro) break;

            if (bro->color == red)
            {
                bro->color = black;
                dod->color = red;
                rb_rotate (dod, left);
                bro = dod->right_node;
                if (!bro) break;
            }

            if ((!bro->left_node || bro->left_node->color == black) &&
                (!bro->right_node || bro->right_node->color == black))
            {
                bro->color = red;
                node = dod;
                dod = node->parent;
                if (!dod) break;
            }
            else
            {
                if (!bro->right_node || bro->right_node->color == black)
                {
                    if (bro->left_node) bro->left_node->color = black;
                    bro->color = red;
                    rb_rotate (bro, right);
                    bro = dod->right_node;
                    if (!bro) break;
                }
                
                bro->color = dod->color;
                dod->color = black;
                if (bro->right_node) bro->right_node->color = black;
                rb_rotate (dod, left);
                node = tree->root; 
            }
        }
        else
        {
            rb_node_t *bro = dod->left_node;
            if (!bro) break;

            if (bro->color == red)
            {
                bro->color = black;
                dod->color = red;
                rb_rotate (dod, right);
                bro = dod->left_node;
                if (!bro) break;
            }

            if ((!bro->right_node || bro->right_node->color == black) &&
                (!bro->left_node || bro->left_node->color == black))
            {
                bro->color = red;
                node = dod;
                dod = node->parent;
                if (!dod) break;
            }
            else
            {
                if (!bro->left_node || bro->left_node->color == black)
                {
                    if (bro->right_node) bro->right_node->color = black;
                    bro->color = red;
                    rb_rotate (bro, left);
                    bro = dod->left_node;
                    if (!bro) break;
                }

                bro->color = dod->color;
                dod->color = black;
                if (bro->left_node) bro->left_node->color = black;
                rb_rotate (dod, right);
                node = tree->root;
            }
        }
    }

    if (node) node->color = black;

    rb_node_t *curr = (node) ? node : dod;
    while (curr && curr->parent) curr = curr->parent;
    if (curr) tree->root = curr;
    return;
}

void *rb_init ()
{
    rb_tree_t *tree = (rb_tree_t *) calloc (1, sizeof (rb_tree_t));
    return tree;
}

void rb_destroy_nodes (rb_node_t *node)
{
    if (!node) return;

    rb_destroy_nodes (node->left_node);
    rb_destroy_nodes (node->right_node);

    free (node);
}

void rb_destroy_tree (void *tree_v)
{
    rb_tree_t *tree = (rb_tree_t *) tree_v;
    if (!tree) return;

    rb_destroy_nodes (tree->root);
    free (tree);
}