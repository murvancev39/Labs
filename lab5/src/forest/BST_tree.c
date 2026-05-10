#include <BST_tree.h>

static void BST_destroy_nodes (BST_node_t *node)
{
    if (!node) return;
    BST_destroy_nodes (node->left_node);
    BST_destroy_nodes (node->right_node);
    free (node);
}

void BST_destructor (void *tree_v)
{
    BST_tree_t *tree = tree_v;
    if (!tree) return;
    if (tree->root) 
    {
        BST_destroy_nodes (tree->root);
    }
    free (tree);
}

int BST_add (void *tree_v, unsigned key)
{
    BST_tree_t *tree = tree_v;
    if (!tree) return 1;

    BST_node_t *node = tree->root;
    BST_node_t *parent = NULL;

    while (node != NULL)
    {
        parent = node;
        if (node->key == key) return 0;
        
        node = (node->key > key) ? node->left_node : node->right_node;
    }

    BST_node_t *new_node = (BST_node_t *) calloc (1, sizeof (BST_node_t));
    if (!new_node) return 1;

    new_node->key = key;
    new_node->parent = parent;

    if (parent == NULL)
    {
        tree->root = new_node;
    }
    else if (parent->key > key)
    {
        parent->left_node = new_node;
    }
    else
    {
        parent->right_node = new_node;
    }

    tree->count++;
    return 0;
}

BST_node_t *BST_find (BST_tree_t *tree, unsigned key)
{
    if (!tree || !tree->root) return NULL;

    BST_node_t *node = tree->root;

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

void *BST_init ()
{
    BST_tree_t *tree = (BST_tree_t *) calloc (1, sizeof (BST_tree_t));
    if (!tree) return NULL;
    
    tree->root = NULL;
    tree->count = 0;
    return tree;
}

void BST_replace_node (BST_node_t **tree, BST_node_t *first, BST_node_t *second)
{
    if (first->parent == NULL)
    {
        *tree = second;
    }
    else if (first == first->parent->left_node)
    {
        first->parent->left_node = second;
    }
    else
    {
        first->parent->right_node = second;
    }

    if (second != NULL)
    {
        second->parent = first->parent;
    }
}

int BST_delete (void *tree_v, unsigned key)
{
    BST_tree_t *tree = tree_v;
    if (!tree || !tree->root) return 0;

    BST_node_t *node = tree->root;

    while (node != NULL && node->key != key)
    {
        node = (key < node->key) ? node->left_node : node->right_node;
    }

    if (node == NULL) return 0;

    if (node->left_node == NULL)
    {
        BST_replace_node (&tree->root, node, node->right_node);
    }
    else if (node->right_node == NULL)
    {
        BST_replace_node (&tree->root, node, node->left_node);
    }
    else
    {
        BST_node_t *el_priemnik = node->right_node;
        while (el_priemnik->left_node != NULL)
        {
            el_priemnik = el_priemnik->left_node;
        }

        if (el_priemnik->parent != node)
        {
            BST_replace_node (&tree->root, el_priemnik, el_priemnik->right_node);
            el_priemnik->right_node = node->right_node;
            el_priemnik->right_node->parent = el_priemnik;
        }

        BST_replace_node (&tree->root, node, el_priemnik);
        el_priemnik->left_node = node->left_node;
        el_priemnik->left_node->parent = el_priemnik;
    }

    free (node);
    tree->count--;
    return 0;
}