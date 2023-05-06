#include "bstree.h"

#include <stdio.h>
#include <stdlib.h>

/* START [_BSTNode] */
typedef struct _BSTNode
{
  void *info;
  struct _BSTNode *left;
  struct _BSTNode *right;
} BSTNode;
/* END [_BSTNode] */

/* START [_BSTree] */
struct _BSTree
{
  BSTNode *root;
  P_ele_print print_ele;
  P_ele_cmp cmp_ele;
};
/* END [_BSTree] */

/*** BSTNode TAD private functions ***/
BSTNode *_bst_node_new()
{
  BSTNode *pn = NULL;

  pn = malloc(sizeof(BSTNode));
  if (!pn)
  {
    return NULL;
  }

  pn->left = NULL;
  pn->right = NULL;
  pn->info = NULL;

  return pn;
}

void _bst_node_free(BSTNode *pn)
{
  if (!pn)
  {
    return;
  }

  free(pn);
}

void _bst_node_free_rec(BSTNode *pn)
{
  if (!pn)
  {
    return;
  }

  _bst_node_free_rec(pn->left);
  _bst_node_free_rec(pn->right);
  _bst_node_free(pn);

  return;
}

int _bst_depth_rec(BSTNode *pn)
{
  int depth_l, depth_r;

  if (!pn)
  {
    return 0;
  }

  depth_l = _bst_depth_rec(pn->left);
  depth_r = _bst_depth_rec(pn->right);

  if (depth_r > depth_l)
  {
    return depth_r + 1;
  }
  else
  {
    return depth_l + 1;
  }
}

int _bst_size_rec(BSTNode *pn)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += _bst_size_rec(pn->left);
  count += _bst_size_rec(pn->right);

  return count + 1;
}

int _bst_preOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += print_ele(pf, pn->info);
  count += _bst_preOrder_rec(pn->left, pf, print_ele);
  count += _bst_preOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_inOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += _bst_inOrder_rec(pn->left, pf, print_ele);
  count += print_ele(pf, pn->info);
  count += _bst_inOrder_rec(pn->right, pf, print_ele);

  return count;
}

int _bst_postOrder_rec(BSTNode *pn, FILE *pf, P_ele_print print_ele)
{
  int count = 0;

  if (!pn)
  {
    return count;
  }

  count += _bst_postOrder_rec(pn->left, pf, print_ele);
  count += _bst_postOrder_rec(pn->right, pf, print_ele);
  count += print_ele(pf, pn->info);

  return count;
}

/*** BSTree TAD functions ***/
BSTree *tree_init(P_ele_print print_ele, P_ele_cmp cmp_ele)
{
  BSTree *tree;

  if (!print_ele || !cmp_ele)
  {
    return NULL;
  }

  tree = malloc(sizeof(BSTree));
  if (!tree)
  {
    return NULL;
  }

  tree->root = NULL;
  tree->print_ele = print_ele;
  tree->cmp_ele = cmp_ele;

  return tree;
}

void tree_destroy(BSTree *tree)
{
  if (!tree)
  {
    return;
  }

  _bst_node_free_rec(tree->root);
  free(tree);

  return;
}

Bool tree_isEmpty(const BSTree *tree)
{
  if (!tree || !tree->root)
  {
    return TRUE;
  }
  return FALSE;
}

int tree_depth(const BSTree *tree)
{
  if (!tree)
  {
    return RET_ERROR;
  }

  return _bst_depth_rec(tree->root);
}

size_t tree_size(const BSTree *tree)
{
  if (!tree)
  {
    return RET_ERROR;
  }

  return _bst_size_rec(tree->root);
}

int tree_preOrder(FILE *f, const BSTree *tree)
{
  if (!f || !tree)
  {
    return RET_ERROR;
  }

  return _bst_preOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_inOrder(FILE *f, const BSTree *tree)
{
  if (!f || !tree)
  {
    return RET_ERROR;
  }

  return _bst_inOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

int tree_postOrder(FILE *f, const BSTree *tree)
{
  if (!f || !tree)
  {
    return RET_ERROR;
  }

  return _bst_postOrder_rec(tree->root, f, tree->print_ele) + fprintf(f, "\n");
}

/**** TODO: find_min, find_max, insert, contains, remove ****/
/* Implementaciones privadas */

BSTNode *_tree_find_min_node(BSTNode *node)
{
  if (!node || !node->left)
    return node;

  return _tree_find_min_node(node->left);
}

BSTNode *_tree_find_max_node(BSTNode *node)
{
  if (!node || !node->right)
    return node;

  return _tree_find_max_node(node->right);
}

Bool _tree_contains(BSTNode *node, const void *elem, P_ele_cmp cmp_ele)
{
  int cmp;

  if (!node)
    return FALSE;

  cmp = cmp_ele(elem, node->info);

  if (cmp == 0)
  {
    return TRUE;
  }
  else if (cmp < 0)
  {
    return _tree_contains(node->left, elem, cmp_ele);
  }
  else
  {
    return _tree_contains(node->right, elem, cmp_ele);
  }
}

static BSTNode *_bst_insert_rec(BSTNode *pn, const void *elem, P_ele_cmp cmp_ele)
{

  int cmp;

  if (!pn)
  {
    pn = _bst_node_new();
    if (!pn)
    {
      return NULL;
    }
    pn->info = (void *)elem;
    return pn;
  }

  cmp = cmp_ele(elem, pn->info);
  if (cmp < 0)
  {
    pn->left = _bst_insert_rec(pn->left, elem, cmp_ele);
  }
  else if (cmp > 0)
  {
    pn->right = _bst_insert_rec(pn->right, elem, cmp_ele);
  }

  return pn;
}

BSTNode *_bst_remove_rec(BSTNode *node, const void *elem, P_ele_cmp cmp_ele)
{
  BSTNode *right_child = NULL;
  BSTNode *left_child = NULL;
  BSTNode *min_right = NULL;
  int cmp;

  if (!node)
    return NULL;

  cmp = cmp_ele(elem, node->info);
  if (cmp < 0)
  {
    node->left = _bst_remove_rec(node->left, elem, cmp_ele);
  }
  else if (cmp > 0)
  {
    node->right = _bst_remove_rec(node->right, elem, cmp_ele);
  }
  else
  {
    if (!node->left && !node->right)
    {
      _bst_node_free(node);
      return NULL;
    }
    else if (!node->left)
    {
      right_child = node->right;
      _bst_node_free(node);
      return right_child;
    }
    else if (!node->right)
    {
      left_child = node->left;
      _bst_node_free(node);
      return left_child;
    }
    else
    {
      min_right = _tree_find_min_node(node->right);
      node->info = min_right->info;
      node->right = _bst_remove_rec(node->right, min_right->info, cmp_ele);
    }
  }
  return node;
}

/* Implementaciones públicas */

void *tree_find_min(BSTree *tree)
{
  BSTNode *min_node = NULL;
  if (!tree)
    return NULL;

  min_node = _tree_find_min_node(tree->root);
  return min_node ? min_node->info : NULL;
}

void *tree_find_max(BSTree *tree)
{
  BSTNode *max_node = NULL;
  if (!tree)
    return NULL;

  max_node = _tree_find_max_node(tree->root);
  return max_node ? max_node->info : NULL;
}

Bool tree_contains(BSTree *tree, const void *elem)
{
  if (!tree || !elem)
    return FALSE;

  return _tree_contains(tree->root, elem, tree->cmp_ele);
}

Status tree_insert(BSTree *tree, const void *elem)
{
  if (!tree || !elem)
    return ERROR;

  tree->root = _bst_insert_rec(tree->root, elem, tree->cmp_ele);
  return OK;
}

Status tree_remove(BSTree *tree, const void *elem)
{
  size_t size;
  if (!tree || !elem)
    return ERROR;

  size = tree_size(tree);
  tree->root = _bst_remove_rec(tree->root, elem, tree->cmp_ele);
  return (size > tree_size(tree)) ? OK : ERROR;
}
