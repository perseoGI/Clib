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
// ********************************** Include Files ***************************************
// ****************************************************************************************
#include "Clib.h"

//=======================================================================================//
//                                                                                       //
//                                   BinaryTree API                                      //
//                                                                                       //
//=======================================================================================//

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/


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
BinaryTree* create_binary_tree(void) {

    BinaryTree *tree = malloc(sizeof(BinaryTree));
    tree->deepness = 0;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

/*void binary_tree_insert_rec(BinaryTreeNode *currentNode, void *newContent, ContentComparator comparator){*/

/*if (comparator(newContent, currentNode->content) < 0) {*/
/*// Replace current node*/
/*binary_tree_insert_rec(currentNode->leftNode, newContent, comparator);*/

/*} else {*/
/*// New node is greater or equal current node*/
/*if (currentNode->rightNode){*/
/*if (comparator(newContent, currentNode->rightNode) < 0){*/
/*// Replace current node*/

/*} else {*/
/*binary_tree_insert_rec(currentNode->rightNode, newContent, comparator);*/
/*}*/
/*} else {*/
/*// Insert as right leaf for current node*/
/*BinaryTreeNode *newNode = malloc(sizeof(TreeNode));*/
/*currentNode->rightNode = newNode;*/
/*newNode->content = newContent;*/
/*newNode->leftNode = NULL;*/
/*newNode->rightNode = NULL;*/
/*}*/
/*}*/
/*}*/

/*else {*/
/*// Start find method in order to locate correct position*/
/*BinaryTreeNode *currentNode = tree->root;*/
/*binary_tree_insert_rec(currentNode, newContent, comparator);*/
/*++tree->size;*/
/*}*/

void binary_tree_insert(BinaryTree *tree, void *newContent, ContentComparator comparator){

    BinaryTreeNode *newNode = malloc(sizeof(TreeNode));
    newNode->content = newContent;
    newNode->leftNode = NULL;
    newNode->rightNode = NULL;

    // If tree is empty, create root
    if (tree->size == 0){
        // Insert first node
        tree->root = newNode;
        // Tree deepness does is 0 when only a root is available
    }
    else {
        BinaryTreeNode *currentNode = tree->root;
        bool found = false;
        unsigned int calcDeepness = 0;
        while (!found){
            // If new node is tinier than current node, go to left subtree
            if (comparator(newContent, currentNode->content) < 0) {
                // If current node does not have a left child
                if (!currentNode->leftNode){
                    // Insert new node
                    currentNode->leftNode = newNode;
                    found = true;
                }
                // If current node has a left child
                else currentNode = currentNode->leftNode;
            }
            // If new node is tinier than current node, go to left subtree
            else {
                // If current node does not have a right child
                if (!currentNode->rightNode){
                    // Insert new node
                    currentNode->rightNode = newNode;
                    found = true;
                }
                // If current node has a right child
                else currentNode = currentNode->rightNode;
            }
            ++calcDeepness;
        }
        if (tree->deepness < calcDeepness)
            ++tree->deepness;
    }
    ++tree->size;
}


BinaryTreeNode * binary_tree_search(BinaryTree *tree, void *pattern, ContentComparator comparator){
    BinaryTreeNode *currentNode = tree->root;
    while (currentNode){
        int comparatorResult = comparator(pattern, currentNode->content);
        if (comparatorResult == 0)
            return currentNode;
        else if (comparatorResult < 0)
            currentNode = currentNode->leftNode;
        else currentNode = currentNode->rightNode;
    }
    return NULL;
}

long int comparePointers(void *pattern, void *current){
    return pattern - current;
}

ContentComparator COMPARE_POINTER = comparePointers;


/*LinkedList * binary_tree_traversal_in_order(BinaryTree *tree){*/
    /*BinaryTreeNode *currentNode = tree->root;*/
    /*Stack *previousNodes = create_stack();*/
    /*LinkedList *preOrderNodes = create_linked_list();*/
    /*while(currentNode){*/
        /*// If current node has been visited and added, check right subtree*/
        /*if (list_find_node(preOrderNodes, currentNode->content, NULL)){*/
            /*if (currentNode->rightNode){*/
                /*// If right node has been already visited, ascend to parent of current node*/
                /*if (list_find_node(preOrderNodes, currentNode->rightNode->content, COMPARE_POINTER)){*/
                    /*currentNode = stack_pop(previousNodes);*/
                /*}*/
                /*else {*/
                    /*stack_push(previousNodes, currentNode);*/
                    /*currentNode = currentNode->rightNode;*/
                /*}*/
            /*}*/
            /*// There is no right subtree*/
            /*else {*/
                /*currentNode = stack_pop(previousNodes);*/
            /*}*/

        /*}*/
        /*// If current node has not been added yet, check left subtree*/
        /*else {*/
            /*// If currentNode has a left subtree*/
            /*if (currentNode->leftNode){*/
                /*// If left subtree has already been added, visit parent*/
                /*if (list_find_node(preOrderNodes, currentNode->leftNode->content, COMPARE_POINTER)){*/
                    /*// Add current node to visited nodes*/
                    /*list_push_back(preOrderNodes, currentNode->content);*/
                /*}*/
                /*else {*/
                    /*stack_push(previousNodes, currentNode);*/
                    /*currentNode = currentNode->leftNode;*/
                /*}*/

            /*}*/
            /*// There is no left subtree*/
            /*else {*/
                /*// Add current node to visited nodes*/
                /*list_push_back(preOrderNodes, currentNode->content);*/
            /*}*/
        /*}*/
    /*}*/
    /*return preOrderNodes;*/
/*}*/


void binary_tree_in_order_traversal_rec(BinaryTreeNode *currentNode, LinkedList *inOrderNodes){

    // 1. Visit left subtree
    if (currentNode->leftNode)
        binary_tree_in_order_traversal_rec(currentNode->leftNode, inOrderNodes);

    // 2. Visit root node
    list_push_back(inOrderNodes, currentNode->content);

    // 3. Visit right subtree
    if (currentNode->rightNode)
        binary_tree_in_order_traversal_rec(currentNode->rightNode, inOrderNodes);
}

LinkedList * binary_tree_in_order_traversal(BinaryTree *tree){
    LinkedList *inOrderNodes = create_linked_list();
    if (tree->root)
        binary_tree_in_order_traversal_rec(tree->root, inOrderNodes);
    return inOrderNodes;
}

void binary_tree_pre_order_traversal_rec(BinaryTreeNode *currentNode, LinkedList *preOrderNodes){

    // 1. Visit root node
    list_push_back(preOrderNodes, currentNode->content);

    // 2. Visit left subtree
    if (currentNode->leftNode)
        binary_tree_pre_order_traversal_rec(currentNode->leftNode, preOrderNodes);

    // 3. Visit right subtree
    if (currentNode->rightNode)
        binary_tree_pre_order_traversal_rec(currentNode->rightNode, preOrderNodes);
}

LinkedList * binary_tree_pre_order_traversal(BinaryTree *tree){
    LinkedList *preOrderNodes = create_linked_list();
    if (tree->root)
        binary_tree_pre_order_traversal_rec(tree->root, preOrderNodes);
    return preOrderNodes;
}

void binary_tree_print(BinaryTree *tree, PrintFunction printer, TraversalOrder order){
    LinkedList *orderedList;
    switch (order){
        case IN_ORDER:
           orderedList = binary_tree_in_order_traversal(tree);
           break;
        case PRE_ORDER:
           orderedList = binary_tree_pre_order_traversal(tree);
           break;
        case POST_ORDER:
           /*orderedList = binary_tree_in_order_traversal(tree);*/
           break;
        default:
           break;
           // TODO
    }
    list_print(orderedList, printer);

}

