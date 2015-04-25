#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


// see list.h for documentation
struct llist *create_list(void) {
	struct llist *lst = malloc(sizeof(struct llist));
	lst->first = NULL;
	lst->last = NULL;
	lst->len=0;
 	return lst;
}

// see list.h for documentation
void destroy_list(struct llist *lst) {
	assert(lst);
	struct llnode *current = lst->first; 
	struct llnode *next;
	while (current != NULL) {
		next = current->next; // note the next pointer
		free(current); // delete the node
		current = next; // advance to the next node
	}
	free(lst); 
}


// see list.h for documentation
int list_length(struct llist *lst) {
  	assert(lst);
	return lst->len;
}




// see list.h for documentation
void print_list(struct llist *lst) {
  	assert(lst);
	struct llnode *current;
	for (current = lst->first; current != NULL; current = current->next)
		printf("  %d", current->item);
	printf("\n");
}
	

// see list.h for documentation
void add_first(int n, struct llist *lst) {
    assert(lst);
    struct llnode *new = malloc(sizeof(struct llnode));
    new->item = n;
    new->next = NULL;
    if (lst->len == 0) {
        lst->first = new;
        lst->last = new;
    } else {
        new->next = lst->first;
        lst->first = new;
    }
    lst->len++;    
}

// see list.h for documentation
void add_last(int n, struct llist *lst) {
    assert(lst);
    struct llnode *new = malloc(sizeof(struct llnode));
    new->item = n;
    new->next = NULL;
    if (lst->len == 0) {
        lst->first = new;
        lst->last = new;
    } else {
        lst->last->next = new;
        lst->last = new;
    }
    lst->len++; 
}

// see list.h for documentation
int delete_first(struct llist *lst) {
    assert(lst && lst->len > 0);
    struct llnode *new = lst->first;
    int deleted_num = lst->first->item;    
    lst->first = new->next;
    free(new);
    lst->len--;
    if (lst->len == 0){
        lst->last = NULL;
    }
    return deleted_num;
    
}

// see list.h for documentation
int get_ith(struct llist *lst, int index) {
    assert(lst && index >= 0 && index < lst->len);
    int i = 0;
    struct llnode *curr = lst->first;
    while (curr != NULL) {
        if (i == index) {
            return curr->item;
        }
        curr = curr->next;
        i++;
    }
    return i;
}


// see list.h for documentation
void insert_ith(struct llist *lst, int index, int data) {
    assert(lst && index >= 0 && index <= lst->len);
    int i = 0;
    struct llnode *new = malloc(sizeof(struct llnode));
    new->item = data;
    new->next = NULL;
    struct llnode *curr = lst->first;
    struct llnode *prev = NULL;
    while (curr != NULL) {
        if (index == 0) {
            add_first(data, lst);
            free(new);
            break;
        }
        if (index == lst->len) {
            add_last(data, lst);
            free(new);
            break;
        }
        if (i == index) {
            prev->next = new;
            new->next = curr;
            lst->len++;
            break;
        }
        prev = curr;
        curr = curr->next;
        i++;
    }      
}

// see list.h for documentation
void lst_append(struct llist *lst1, struct llist *lst2) {
    assert(lst1 != NULL && lst2 != NULL);
    if (lst1 == NULL) {
        lst1 = lst2;
        lst2->first = NULL;
        lst2->last = NULL;
        lst2->len = 0; 
        lst1->len = lst2->len;
    }
    if (lst2 == NULL) {
        return;
    }
    if (lst1->len == 0 && lst2->len == 0){
        return;
    }
    if (lst1->len == 0 && lst2->len != 0){
        lst1->first = lst2->first;
        lst1->last = lst2->last;
        lst1->len = lst2->len;
        lst2->first = NULL;
        lst2->last = NULL;
        lst2->len = 0;
    }
    if (lst1->len != 0 && lst2->len == 0){
        return;
    }
    if (lst1->len != 0 && lst2->len != 0) {
        lst1->last->next = lst2->first;
        lst2->first = NULL;
        lst2->last = NULL;
        lst1->len += lst2->len;
        lst2->len = 0; 
    } 	
}

// see list.h for documentation
bool eq_list(struct llist *lst1, struct llist *lst2) {
    assert(lst1 != NULL && lst2 != NULL);
    if (lst1 == NULL || lst2 == NULL) {
        return false;
    } else if (lst1->len != lst2->len){       
        return false;
    } else if (lst1->len == 0) {
        return true;
    } else {
        struct llnode *curr_lst1 = lst1->first;
        struct llnode *curr_lst2 = lst2->first;
        
        while (curr_lst2 != NULL) {
            if (curr_lst1->item != curr_lst2->item) {
                return false;
            }
            curr_lst1 = curr_lst1->next; 
            curr_lst2 = curr_lst2->next;
        }
        return true;
    }
}

// see list.h for documentation
int maxminlist(struct llist *lst, int *max, int *min) {
    assert(lst != NULL);
    if (lst->len == 0) {
        return 0;
    } else {
        struct llnode *curr = lst->first;
        *max = curr->item;
        *min = curr->item;
        while (curr != NULL) {
            if (curr->item > *max) {
                *max = curr->item;
            }
            if (curr->item < *min) {
                *min = curr->item;
            }
            curr = curr->next; 
        }
        return 1;
    }
   
}

// see list.h for documentation
void list_map( struct llist *lst, int (*function_ptr)( int) ) {
    assert(lst != NULL);
    if (lst->len > 0) {
        struct llnode *curr = lst->first;
        while (curr != NULL) {
            curr->item = function_ptr(curr->item);
            curr = curr->next;
        }
    } else {
        return;
    }
}