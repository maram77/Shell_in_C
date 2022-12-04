#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "shell.h"
#include "node.h"
#include "parser.h"


struct node_s *new_node(enum node_type_e type)
{
    struct node_s *node = malloc(sizeof(struct node_s));

    if(!node)
    {
        return NULL;
    }
    
    memset(node, 0, sizeof(struct node_s));
    node->type = type;
    
    return node;
}


void add_child_node(struct node_s *parent, struct node_s *child)
{
    // Error handling: absence of a parent or a child 
    if(!parent || !child)
    {
        return;
    }

    // Checking the existence of a first child
    if(!parent->first_child)
    {
        parent->first_child = child;
    }
    
    // Appended to the children list 
    else
    {
        struct node_s *sibling = parent->first_child;
    
    	while(sibling->next_sibling)
        {
            sibling = sibling->next_sibling;
        }
    
    	sibling->next_sibling = child;
        child->prev_sibling = sibling;
    }
    parent->children++;
}


void set_node_val_str(struct node_s *node, char *val)
{
 
    // Setting the val_type of the node to string   node->val_type = VAL_STR;


    // Value passed is not defined    if(!val)
    {
        node->val.str = NULL;
    }
    
    
    // Setting node value to the value passed to the functionlse
    {
        char *val2 = malloc(strlen(val)+1);
    
     
        // Memory allocation for val2 failed
           {
            node->val.str = NULL;
        }
        

        // Copying the value to val2 and setting the node value to val2lse
        {
            strcpy(val2, val);
            node->val.str = val2;
        }
    }
}


void free_node_tree(struct node_s *node)
{
 
    // Error handling   if(!node)
    {
        return;
    }

    struct node_s *child = node->first_child;
    

   // Checking the existence of children, if so, free them recursively while(child)
    {
        struct node_s *next = child->next_sibling;
        free_node_tree(child);
        child = next;
    }
    

    // Checking if the given node contains a value to free before freeing it itselfif(node->val_type == VAL_STR)
    {
        if(node->val.str)
        {
            free(node->val.str);
        }
    }
    free(node);
}