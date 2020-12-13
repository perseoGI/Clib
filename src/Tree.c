// ****************************************************************************************
/**
 * @file   Tree.c
 * @brief  Implementation of Tree data structure on C
 *
 * @details This source file includes a Tree implementation.
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
//                                     Stack API                                         //
//                                                                                       //
//=======================================================================================//

/******************************************************************************/
/***************** Private Auxiliary Functions Implementations ****************/
/******************************************************************************/


/******************************************************************************/
/*********************** Public Functions Implementations *********************/
/******************************************************************************/

// ****************************************************************************************
// create_tree
// ****************************************************************************************
/**
 *  Initialice tree structure
 * @param[in]    none
 * @param[out]   none
 * @return       valid pointer to tree structure
 */
// ****************************************************************************************
Tree* create_tree(void) {

    Tree *tree = malloc(sizeof(Tree));
    tree->deepness = 0;
    tree->size = 0;
    tree->root = NULL;
    return tree;
}


void tree_insert(Tree *tree, void *content){
    // If tree is empty, create root
    if (tree->size == 0){
        tree->root = malloc(sizeof(TreeNode));
        tree->root->content = content;
        tree->root->children = create_linked_list();
    } else {
        // Start find method in order to locate correct position
        // TODO
    }
}
