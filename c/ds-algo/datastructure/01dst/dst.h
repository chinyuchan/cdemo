#ifndef DST_H
#define DST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define SUCCESS 0
#define FAILURE -1

// size_t主要用于表示对象的大小或者数组的索引，而 int 则用于一般的整数运算
typedef struct DynamicSequencetable {
    size_t capacity;
    size_t size;
    size_t elem_size;
    char data[];
}DST, *PDST;

PDST create_dst(size_t elem_size, size_t capacity);
PDST create_fixed_dst(size_t elem_size);
void destroy_dst(PDST dst);
size_t capacity_dst(PDST dst);
size_t size_dst(PDST dst);
bool empty_dst(PDST dst);
bool full_dst(PDST dst);
PDST recapacity_dst(PDST dst, size_t capacity);
int insert_dst(PDST dst, size_t pos, const void* pdata);
int push_back_dst(PDST dst, const void* pdata);
int remove_pos_dst(PDST dst, size_t pos, void* pdata);
int pop_back_dst(PDST dst, void* pdata);
int remove_value_dst(PDST dst, const void* val, int(*compare)(const void*, const void*));
int remove_value_all_dst(PDST dst, const void* key, int(*compare)(const void*, const void*));
int remove_value_count_dst(PDST dst, const void* val, int(*conmpare)(const void*, const void*), size_t n);
int remove_condition_dst(PDST dst, bool(*condition)(const void*));
int remove_condition_all_dst(PDST dst, bool(*condition)(const void*));
int remove_condition_count_dst(PDST dst, bool(*condition)(const void*), size_t n);
void clear_dst(PDST dst);
int update_dst(PDST dst, size_t pos, const void* pdata);
const void* index_of_dst(PDST dst, size_t pos);
int find_value_dst(PDST dst, const void* pdata, int(*compare)(const void*, const void*));
int find_value_count_dst(PDST dst, const void* pdata, int(*compare)(const void*, const void*), size_t n);
int find_condition_dst(PDST dst, bool(*condition)(const void*));
int find_condition_count_dst(PDST dst, bool(*condition)(const void*), size_t n);
size_t count_value_dst(PDST dst, const void* value, int(*compare)(const void*, const void*));
size_t count_condition_dst(PDST dst, bool(*condition)(const void*));
void foreach_dst(PDST dst, void(*foreach)(void*));
void foreach_reverse_dst(PDST dst, void(*foreach)(void*));

#endif //DST_H
