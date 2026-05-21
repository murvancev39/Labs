#include "avl_tree.h"

void *avl_init ()
{
    avl_tree_t *tree = (avl_tree_t *) calloc (1, sizeof (avl_tree_t));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->count = 0;
    return tree;
}

int avl_next (avl_node_t *tree, unsigned key)
{
    if (!tree) return -1;
    int avl_next = -1;
    avl_node_t *node = tree;
    while (node != NULL)
    {
        if (node->key == key) return key;
        if (node->key > key)
        {
            avl_next = node->key;
            node = node->left_node;
        }
        else 
        {
            node = node->right_node;
        }
    }
    return avl_next;
}

int avl_add (void *tree_v, unsigned key)
{
    avl_tree_t *tree = tree_v;
    if (!tree) return ERROR;

    if (avl_search (tree, key)) return OK;

    tree->root = avl_insert (tree->root, key);
    if (tree->root) tree->root->parent = NULL;
    
    tree->count++;
    return OK;
}

avl_node_t *avl_insert (avl_node_t *tree, unsigned key)
{
    if (!tree) 
    {
        avl_node_t *node = (avl_node_t *) calloc (1, sizeof (avl_node_t));
        if (!node) return NULL;
        node->key = key;
        node->avl_height = 1;
        return node;
    }
    if (tree->key == key)
    {
        return tree;
    }
    if (tree->key > key)    
    {
        avl_node_t *res = avl_insert (tree->left_node, key);
        if (!res) return NULL;
        tree->left_node = res;
        tree->left_node->parent = tree;
    }
    else
    {
        avl_node_t *res = avl_insert (tree->right_node, key);
        if (!res) return NULL;
        tree->right_node = res;
        tree->right_node->parent = tree;
    }

    avl_change_avl_height (tree);

    int balance = avl_height (tree->left_node) - avl_height (tree->right_node);
    if (!(balance >= -1 && balance <= 1))
    {
        avl_node_t *dod = tree;
        avl_node_t *son = NULL;
        if (balance == 2)
        {
            son = tree->left_node;
            if (!son) return tree;
            if (avl_height (son->left_node) - avl_height (son->right_node) >= 0)
            {
                return avl_rotate (tree, left);
            }
            else
            {
                son = avl_rotate (son, right);
                tree->left_node = son;
                return avl_rotate (dod, left);
            }
        }
        else
        {
            son = tree->right_node;
            if (!son) return tree;
            
            if (avl_height (son->left_node) - avl_height (son->right_node) <= 0)
            {
                return avl_rotate (tree, right);
            }
            else
            {
                son = avl_rotate (son, left);
                tree->right_node = son;
                return avl_rotate (dod, right);
            }
        }
    }
    return tree;
}

avl_node_t *avl_rotate (avl_node_t *node, side_t side)
{
    if (!node) return NULL;
    if (side == left)
    {
        avl_node_t *dod = node;
        avl_node_t *son = dod->left_node;
        if (!son) return dod;
        avl_node_t *sons_son = son->right_node;

        son->parent = dod->parent;
        son->right_node = dod;
        dod->parent = son;
        dod->left_node = sons_son;
        if (sons_son) sons_son->parent = dod;

        avl_change_avl_height (dod);
        avl_change_avl_height (son);
        return son;
    }

    avl_node_t *dod = node;
    avl_node_t *son = dod->right_node;
    if (!son) return dod;
    avl_node_t *sons_son = son->left_node;

    son->parent = dod->parent;
    son->left_node = dod;
    dod->right_node = sons_son;
    dod->parent = son;
    if (sons_son) sons_son->parent = dod;

    avl_change_avl_height (dod);
    avl_change_avl_height (son);
    return son;
}

void avl_change_avl_height (avl_node_t *tree)
{
    if (!tree) return;
    tree->avl_height = avl_height (tree->left_node);
    if (tree->avl_height < avl_height (tree->right_node))
    {
        tree->avl_height = avl_height (tree->right_node);
    }
    tree->avl_height++;
    return;
}

int avl_height (avl_node_t *node)
{
    if (!node) return 0;
    return (int) node->avl_height;
}

avl_node_t *avl_find_min (avl_node_t *node)
{
    if (!node) return NULL;
    while (node->left_node) node = node->left_node;
    return node;
}

int avl_delete (void *tree_v, unsigned key)
{
    avl_tree_t *tree = tree_v;
    if (!tree || !tree->root) return ERROR;

    if (avl_search (tree, key) == NULL) return OK;

    tree->root = avl_remove (tree->root, key);
    if (tree->root) tree->root->parent = NULL;
    
    tree->count--;
    return OK;
}

avl_node_t *avl_remove (avl_node_t *tree, unsigned key)
{
    if (!tree) return NULL;

    if (key < tree->key)
    {
        tree->left_node = avl_remove (tree->left_node, key);
        if (tree->left_node) tree->left_node->parent = tree;
    }
    else if (key > tree->key)
    {
        tree->right_node = avl_remove (tree->right_node, key);
        if (tree->right_node) tree->right_node->parent = tree;
    }
    else
    {
        avl_node_t *left_son = tree->left_node;
        avl_node_t *right_son = tree->right_node;
        avl_node_t *parent = tree->parent;

        if (!left_son || !right_son)
        {
            avl_node_t *temp = left_son ? left_son : right_son;
            free (tree);
            if (temp) temp->parent = parent;
            return temp;
        }
        else
        {
            avl_node_t *min = avl_find_min (right_son);
            if (min)
            {
                tree->key = min->key;
                tree->right_node = avl_remove (right_son, min->key);
                if (tree->right_node) tree->right_node->parent = tree;
            }
        }
    }

    avl_change_avl_height (tree);

    int balance = avl_height (tree->left_node) - avl_height (tree->right_node);

    if (balance > 1)
    {
        if (tree->left_node)
        {
            if (avl_height (tree->left_node->left_node) >= avl_height (tree->left_node->right_node))
            {
                return avl_rotate (tree, left);
            }
            else
            {
                tree->left_node = avl_rotate (tree->left_node, right);
                return avl_rotate (tree, left);
            }
        }
    }
    if (balance < -1)
    {
        if (tree->right_node)
        {
            if (avl_height (tree->right_node->right_node) >= avl_height (tree->right_node->left_node))
            {
                return avl_rotate (tree, right);
            }
            else
            {
                tree->right_node = avl_rotate (tree->right_node, left);
                return avl_rotate (tree, right);
            }
        }
    }

    return tree;
}

avl_node_t *avl_search (avl_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return NULL;

    avl_node_t *node = tree->root;

    while (node != NULL)
    {
        if (node->key == key)
        {
            return node;
        }

        if (key < node->key)
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

void avl_destroy_node (avl_node_t *tree)
{
    if (!tree) return;

    if (tree->left_node)  avl_destroy_node (tree->left_node);
    if (tree->right_node) avl_destroy_node (tree->right_node);

    free (tree);
}

void avl_destructor (void *tree_v)
{
    avl_tree_t *tree = tree_v;
    if (!tree) return;

    avl_destroy_node (tree->root);

    free (tree);
}
