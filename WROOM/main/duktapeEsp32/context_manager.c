#include <duktape.h>
/*

#include "driver/include/driver/timer.h"

#define MAX_CONTEXT_NUM 10

// timer
#define CONTEXT_MANAGER_TIMER_GROUP 0
#define CONTEXT_MANAGER_TIMER_IDX 0

////////////////////////////// Context List //////////////////////////////////
struct ContextNode {
    uint64_t resumeMsTime;
    duk_context* context;
    duk_thread_state state;

    struct ContextNode* nextNode;
};

static struct ContextNode *head = NULL;

static void contextListInit() {
    struct ContextNode* headNode = (struct ContextNode*)malloc(sizeof(struct ContextNode));
    headNode->nextNode = NULL;

    head = headNode;
}

static struct ContextNode* contextListPopFirst(uint32_t msTime) {
    struct ContextNode* res = NULL;
    if (head->nextNode && head->nextNode->resumeMsTime <= msTime) {
        res = head->nextNode;

        // delete node
        head->nextNode = res->nextNode;

        return res;
    }
    else return res;
}

static void contextListInsert(struct ContextNode* node) {
    struct ContextNode* tmp = head;
    while (tmp->nextNode && tmp->nextNode->resumeMsTime < node->resumeMsTime) tmp = tmp->nextNode;
    node->nextNode = tmp->nextNode;
    tmp->nextNode = node;
}

////////////////////////////// pause & resume //////////////////////////////////
static uint32_t getCurrentMsTime() {
    double secTime;
    timer_get_counter_value_sec(CONTEXT_MANAGER_TIMER_GROUP, CONTEXT_MANAGER_TIMER_IDX, &secTime);
    return (uint32_t)(secTime / 1000);
}

void contextPause(duk_context* ctx, uint32_t msTime) {
    struct ContextNode* newNode = (struct ContextNode*)malloc(sizeof(struct ContextNode));
    newNode->resumeMsTime = getCurrentMsTime() + msTime;
    newNode->context = ctx;
    newNode->nextNode = NULL;

    duk_suspend(ctx, &newNode->state);

    contextListInsert(newNode);
}

static void contextResume(struct ContextNode* node) {
    duk_resume(node->context, &node->state);

    free(node);
}

// execute context if has available context
void contextCheckLoop() {
    struct ContextNode* node = NULL;
    while (!node) {
        node = contextListPopFirst(getCurrentMsTime());
        if (node) {
            contextResume(node);
        }
    }
}

void initContextManager() {
    timer_start(CONTEXT_MANAGER_TIMER_GROUP, CONTEXT_MANAGER_TIMER_IDX);

    contextListInit();
}

////////////////////////////// manager context //////////////////////////////////



duk_context *ctx1, *ctx2;
static int thread1(duk_context* ctx) {
    printf("--- thread1 before pause --- \n");
    contextPause(ctx, 2000);
    printf("--- thread1 after pause --- \n");
    return 0;
}
static int thread2(duk_context* ctx) {
    printf("--- thread2 before pause --- \n");
    contextPause(ctx, 5000);
    printf("--- thread2 after pause --- \n");
    return 0;
}
void multiContextTest() {
    ctx1 = duk_create_heap_default();
    duk_push_thread(ctx1);
    ctx2 = duk_get_context(ctx1, -1);

    initContextManager();

    duk_push_c_function(ctx1, thread1, 0);
    duk_push_c_function(ctx1, thread2, 0);
    contextPause(ctx2, 0);

    duk_call(ctx1, 0);
    duk_pop(ctx1);

    duk_destroy_heap(ctx1);
}

*/