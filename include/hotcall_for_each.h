#ifndef _H_HOTCALL_FOR_EACH
#define _H_HOTCALL_FOR_EACH

#include "hotcall_utils.h"
#include "hotcall_function.h"

#define _FOR_EACH(SM_CTX, ID, CONFIG, ...) \
    struct parameter CAT2(FOR_EACH_ARG_,ID)[] = { \
        __VA_ARGS__\
    }; \
    struct for_each_config CAT2(FOR_EACH_CONFIG_,ID) = CONFIG;\
    struct hotcall_for_each ID = { CAT2(FOR_EACH_ARG_,ID), &CAT2(FOR_EACH_CONFIG_,ID) };\
    struct ecall_queue_item CAT2(QUEUE_ITEM_, ID) = { QUEUE_ITEM_TYPE_FOR_EACH, .call = { .tor = &ID }}; \
    CAT2(FOR_EACH_CONFIG_,ID).n_params = sizeof(CAT2(FOR_EACH_ARG_,ID))/sizeof(struct parameter);\
    hotcall_enqueue_item(SM_CTX, &CAT2(QUEUE_ITEM_, ID))


#define FOR_EACH(CONFIG, ...) \
    _FOR_EACH(_sm_ctx, UNIQUE_ID, CONFIG, __VA_ARGS__)

struct for_each_config {
    const uint8_t function_id;
    unsigned int *n_iters;
    unsigned int n_params;
};

struct hotcall_for_each {
    struct parameter *params;
    struct for_each_config *config;
};

#endif
