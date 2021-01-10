// ****************************************************************************************
/**
 * @file   BinaryTree.c
 * @brief  Implementation of BinaryTree data structure on C
 *
 * @details This source file includes a BinaryTree implementation.
 *
 * <h2> Release History </h2>
 *
 * <hr>
 * @version 1.1
 * @author Perseo Gutierrez Izquierdo <perseo.gi98@gmail.com>
 * @date    18 Nov 2020
 * @details
 *	    - Initial release.
 * @bug	    Not known bugs.
 * @todo    Make unit tests
 *
 * <hr>
 */
// ****************************************************************************************

// ****************************************************************************************
// ********************************** Include Files
// ***************************************
// ****************************************************************************************
#include "Clib.h"

//=======================================================================================//
//                                                                                       //
//                                   BinaryTree API //
//                                                                                       //
//=======================================================================================//

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/

long int comparePointers(void *pattern, void *current) {
    return pattern - current;
}

ContentComparator COMPARE_POINTER = comparePointers;

/******************************************************************************/
/*********************** Public Functions Implementations *********************/
/******************************************************************************/

// ****************************************************************************************
// create_binary_tree
// ****************************************************************************************
/**
 *  Initialice tree structure
 * @param[in]    none
 * @param[out]   none
 * @return       valid pointer to tree structure
 */
// ****************************************************************************************
BinaryTree *create_binary_tree(void) {

    BinaryTree *tree = malloc(sizeof(BinaryTree));
    tree->deepness = 0;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

void binary_tree_insert(BinaryTree *tree, void *newContent,
        ContentComparator comparator) {

    BinaryTreeNode *newNode = malloc(sizeof(TreeNode));
    newNode->content = newContent;
    newNode->leftNode = NULL;
    newNode->rightNode = NULL;

    // If tree is empty, create root
    if (tree->size == 0) {
        // Insert first node
        tree->root = newNode;
        // Tree deepness does is 0 when only a root is available
    } else {
        BinaryTreeNode *currentNode = tree->root;
        bool found = false;
        unsigned int calcDeepness = 0;
        while (!found) {
            // If new node is tinier than current node, go to left subtree
            if (comparator(newContent, currentNode->content) < 0) {
                // If current node does not have a left child
                if (!currentNode->leftNode) {
                    // Insert new node
                    currentNode->leftNode = newNode;
                    found = true;
                }
                // If current node has a left child
                else
                    currentNode = currentNode->leftNode;
            }
            // If new node is tinier than current node, go to left subtree
            else {
                // If current node does not have a right child
                if (!currentNode->rightNode) {
                    // Insert new node
                    currentNode->rightNode = newNode;
                    found = true;
                }
                // If current node has a right child
                else
                    currentNode = currentNode->rightNode;
            }
            ++calcDeepness;
        }
        if (tree->deepness < calcDeepness)
            ++tree->deepness;
    }
    ++tree->size;
}

void binary_tree_destroy_rec(BinaryTreeNode *currentNode,
        void (*free_func)(void *)) {
    // 1. Visit left subtree
    if (currentNode->leftNode)
        binary_tree_destroy_rec(currentNode->leftNode, free_func);

    // 2. Visit right subtree
    if (currentNode->rightNode)
        binary_tree_destroy_rec(currentNode->rightNode, free_func);

    // 3. Free current node
    free_func(currentNode->content);
    free(currentNode);
}

void binary_tree_destroy(BinaryTree *tree, void (*free_func)(void *)) {
    if (tree->root)
        binary_tree_destroy_rec(tree->root, free_func);
}

BinaryTreeNode *binary_tree_search(BinaryTree *tree, void *pattern,
        ContentComparator comparator) {
    BinaryTreeNode *currentNode = tree->root;
    while (currentNode) {
        int comparatorResult = comparator(pattern, currentNode->content);
        if (comparatorResult == 0)
            return currentNode;
        else if (comparatorResult < 0)
            currentNode = currentNode->leftNode;
        else
            currentNode = currentNode->rightNode;
    }
    return NULL;
}

void binary_tree_in_order_traversal_rec(BinaryTreeNode *currentNode,
        LinkedList *inOrderNodes) {

    // 1. Visit left subtree
    if (currentNode->leftNode)
        binary_tree_in_order_traversal_rec(currentNode->leftNode, inOrderNodes);

    // 2. Visit root node
    list_push_back(inOrderNodes, currentNode->content);

    // 3. Visit right subtree
    if (currentNode->rightNode)
        binary_tree_in_order_traversal_rec(currentNode->rightNode, inOrderNodes);
}

void binary_tree_pre_order_traversal_rec(BinaryTreeNode *currentNode,
        LinkedList *preOrderNodes) {

    // 1. Visit root node
    list_push_back(preOrderNodes, currentNode->content);

    // 2. Visit left subtree
    if (currentNode->leftNode)
        binary_tree_pre_order_traversal_rec(currentNode->leftNode, preOrderNodes);

    // 3. Visit right subtree
    if (currentNode->rightNode)
        binary_tree_pre_order_traversal_rec(currentNode->rightNode, preOrderNodes);
}

void binary_tree_post_order_traversal_rec(BinaryTreeNode *currentNode,
        LinkedList *postOrderNodes) {

    // 1. Visit left subtree
    if (currentNode->leftNode)
        binary_tree_post_order_traversal_rec(currentNode->leftNode, postOrderNodes);

    // 2. Visit right subtree
    if (currentNode->rightNode)
        binary_tree_post_order_traversal_rec(currentNode->rightNode,
                postOrderNodes);

    // 3. Visit root node
    list_push_back(postOrderNodes, currentNode->content);
}

LinkedList * binary_tree_traversal(BinaryTree *tree, TraversalOrder order) {
    LinkedList *orderNodesList = create_linked_list();
    if (tree->root)
        switch (order) {
            case IN_ORDER:
                binary_tree_in_order_traversal_rec(tree->root, orderNodesList);
                break;
            case PRE_ORDER:
                binary_tree_pre_order_traversal_rec(tree->root, orderNodesList);
                break;
            case POST_ORDER:
                binary_tree_post_order_traversal_rec(tree->root, orderNodesList);
                break;
            default:
                // TODO: this should never happen
                orderNodesList = NULL;
                break;
        }
    return orderNodesList;
}

void binary_tree_traversal_print(BinaryTree *tree, PrintFunction printer, TraversalOrder order) {
    LinkedList * orderedList = binary_tree_traversal(tree, order);
    list_print(orderedList, printer);
}

// Based on https://stackoverflow.com/a/13755911/10474917
int binary_tree_print_rec(BinaryTreeNode *tree, PrintFunction printer,
        int is_left, int offset, int depth, char s[20][255]) {
    char b[20];
    int width = 5;

    if (!tree)
        return 0;

    sprintf(b, "(%03d)", *(int *)tree->content);

    int left =
        binary_tree_print_rec(tree->leftNode, printer, 1, offset, depth + 1, s);
    int right = binary_tree_print_rec(tree->rightNode, printer, 0,
            offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width / 2 + i] = '-';

        s[2 * depth - 1][offset + left + width / 2] = '+';
        s[2 * depth - 1][offset - width / 2 - 1] = '+';
    }

    return left + width + right;
}

void binary_tree_print(BinaryTree *tree, PrintFunction printer) {
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    binary_tree_print_rec(tree->root, printer, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

