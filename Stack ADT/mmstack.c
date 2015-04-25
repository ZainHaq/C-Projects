#include "mmstack.h"
#include <stdlib.h>
#include <assert.h>

// Programmer: Zain Haq

struct lnode {
    int item;
    int curr_max;
    int curr_min;
    struct lnode *next;
    
};  

struct mmstack {
    struct lnode *top;
    int length;
};

// see "mmstack.h" for more detail
MMStack create_MMStack(void) {
    MMStack new = malloc(sizeof(struct mmstack));
    new->top = NULL;
    new->length = 0;
    return new;
}

// see "mmstack.h" for more detail
int mms_length(MMStack mms) {
    assert(mms);
    return mms->length;
}

// see "mmstack.h" for more detail
void mms_push(MMStack mms, int i) { 
    assert(mms);
    struct lnode *new = malloc(sizeof(struct lnode));
    new->item = i;
    new->next = mms->top;
    if (mms->length == 0) {
        new->curr_max = i;
        new->curr_min = i;
    } else {
        if (i > mms->top->curr_max) {
            new->curr_max = i;
        } else {
            new->curr_max = mms->top->curr_max;
        }
        if (i < mms->top->curr_min) {
            new->curr_min = i;
        } else {
            new->curr_min = mms->top->curr_min;
        }
    }
    mms->top = new;       
    mms->length++;
}

// see "mmstack.h" for more detail
int mms_pop(MMStack mms) {
    assert(mms);
    assert(mms->length > 0);
    struct lnode *temp = mms->top;
    int popped = mms->top->item;
    mms->top = mms->top->next;
    mms->length--;    
    free(temp);    
    return popped;
}

// see "mmstack.h" for more detail
int mms_min(MMStack mms){
    assert(mms);
    assert(mms->length > 0);
    return mms->top->curr_min;
}

// see "mmstack.h" for more detail
int mms_max(MMStack mms) {
    assert(mms);
    assert(mms->length > 0);
    return mms->top->curr_max;
};

// see "mmstack.h" for more detail
void destroy_MMStack(MMStack mms) {
    assert(mms);
    while (mms->length > 0) {
        mms_pop(mms);
    }
    free(mms);
}


