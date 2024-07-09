#include "dst.h"

#define INIT_CAPACITY 16

PDST create_dst(size_t elem_size, size_t capacity) {
    assert(elem_size != 0);
    assert(capacity != 0);
    PDST dst = malloc(sizeof(DST) + elem_size * capacity);
    if (dst != NULL) {
        dst->capacity = capacity;
        dst->elem_size = elem_size;
        dst->size = 0;
    }
    return dst;
}

PDST create_fixed_dst(size_t elem_size) {
    assert(elem_size != 0);
    return create_dst(elem_size, INIT_CAPACITY);
}

void destroy_dst(PDST dst) {
    if (dst != NULL) {
        free(dst);
    }
}

size_t capacity_dst(PDST dst) {
    assert(dst != NULL);
    return dst->capacity;
}

size_t size_dst(PDST dst) {
    assert(dst != NULL);
    return dst->size;
}

bool empty_dst(PDST dst) {
    assert(dst != NULL);
    return dst->size == 0;
}

bool full_dst(PDST dst) {
    assert(dst != NULL);
    return dst->size >= dst->capacity;
}

PDST recapacity_dst(PDST dst, size_t capacity) {
    assert(dst != NULL);
    if (capacity <= dst->capacity) {
        return dst;
    }

    dst = realloc(dst, sizeof(DST) + capacity * dst->elem_size);
    if (dst != NULL) {
        dst->capacity = capacity;
    }

    return dst;
}

int insert_dst(PDST dst, size_t pos, const void* pdata) {
    assert(dst != NULL);
    assert(pdata != NULL);
    if (pos > dst->size) {
        return FAILURE;
    }
    if (dst->size >= dst->capacity) {
        return FAILURE;
    }
    size_t i;
    for (i = dst->size; i > pos; --i) {
        memcpy(dst->data + i * dst->elem_size, dst->data + (i - 1) * dst->elem_size, dst->elem_size);
    }
    memcpy(dst->data + pos * dst->elem_size, pdata, dst->elem_size);
    ++dst->size;

    return SUCCESS;
}

int push_back_dst(PDST dst, const void* pdata) {
    assert(dst != NULL);
    assert(pdata != NULL);
    if (dst->size >= dst->capacity) {
        return FAILURE;
    }

    memcpy(dst->data + dst->size*dst->elem_size, pdata, dst->elem_size);
    ++dst->size;

    return SUCCESS;
}

int remove_pos_dst(PDST dst, size_t pos, void* pdata) {
    assert(dst != NULL);
    if (pos >= dst->size) {
        return FAILURE;
    }
    if (pdata != NULL) {
        memcpy(pdata, dst->data + pos * dst->elem_size, dst->elem_size);
    }
    size_t i;
    for (i = pos + 1; i < dst->size; ++i) {
        memcpy(dst->data + (i - 1) * dst->elem_size, dst->data + i * dst->elem_size, dst->elem_size);
    }
    --dst->size;

    return SUCCESS;
}

int pop_back_dst(PDST dst, void* pdata) {
    assert(dst != NULL);
    if (dst->size == 0) {
        return FAILURE;
    }
    if (pdata != NULL) {
        memcpy(pdata, dst->data + (dst->size-1)*dst->elem_size, dst->elem_size);
    }
    --dst->size;

    return SUCCESS;
}

int remove_value_dst(PDST dst, const void* val, int(*compare)(const void*, const void*)) {
    assert(dst != NULL);
    assert(val != NULL);
    assert(compare != NULL);

    size_t i;
    for (i = 0; i < dst->size; ++i) {
        if (compare(dst->data + i*dst->elem_size, val) == 0) {
            return remove_pos_dst(dst, i, NULL);
        }
    }

    return FAILURE;
}

int remove_value_all_dst(PDST dst, const void* val, int(*compare)(const void*, const void*)) {
    assert(dst != NULL);
    assert(val != NULL);
    assert(compare != NULL);

    size_t i;
    int cnt = 0;
    for(i = 0; i < dst->size;) {
        if (compare(dst->data + i*dst->elem_size, val) == 0) {
            remove_pos_dst(dst, i, NULL);
            ++cnt;
        }
        else {
            ++i;
        }
    }

    return cnt;
}

int remove_value_count_dst(PDST dst, const void* val, int(*compare)(const void*, const void*), size_t n) {
    assert(dst != NULL);
    assert(val != NULL);
    assert(compare != NULL);
    assert(n != 0);
    size_t i;
    for (i = 0; i < dst->size; ++i) {
        if (compare(dst->data + i * dst->elem_size, val) == 0) {
            if (--n == 0) {
                return remove_pos_dst(dst, i, NULL);
            }
        }
    }

    return FAILURE;
}

int remove_condition_dst(PDST dst, bool(*condition)(const void*)) {
    assert(dst != NULL);
    assert(condition != NULL);
    size_t i;
    for(i = 0; i < dst->size; ++i) {
        if (condition(dst->data + i * dst->elem_size)) {
            return remove_pos_dst(dst, i, NULL);
        }
    }
    return FAILURE;
}

int remove_condition_all_dst(PDST dst, bool(*condition)(const void*)) {
    assert(dst != NULL);
    assert(condition != NULL);
    size_t i;
    int cnt = 0;
    for (i = 0; i < dst->size;) {
        if (condition(dst->data + i * dst->elem_size)) {
            remove_pos_dst(dst, i, NULL);
            ++cnt;
        }
        else {
            ++i;
        }
    }
    return cnt;
}

int remove_condition_count_dst(PDST dst, bool(*condition)(const void*), size_t n) {
    assert(dst != NULL);
    assert(condition != NULL);
    assert(n != 0);
    size_t i;
    for (i = 0; i < dst->size; ++i) {
        if (condition(dst->data + i * dst->elem_size)) {
            if (--n == 0) {
                return remove_pos_dst(dst, i, NULL);
            }
        }
    }

    return FAILURE;
}

void clear_dst(PDST dst) {
    assert(dst != NULL);
    dst->size = 0;
}

int update_dst(PDST dst, size_t pos, const void* pdata) {
    assert(dst != NULL);
    assert(pdata != NULL);

    if (pos >= dst->size) {
        return FAILURE;
    }
    memcpy(dst->data + pos * dst->elem_size, pdata, dst->elem_size);

    return SUCCESS;
}

const void* index_of_dst(PDST dst, size_t pos) {
    assert(dst != NULL);

    if (pos >= dst->size) {
        return NULL;
    }
    return dst->data + pos * dst->elem_size;
}

int find_value_dst(PDST dst, const void* pdata, int(*compare)(const void*, const void*)) {
    assert(dst != NULL);
    assert(pdata != NULL);
    assert(compare != NULL);

    size_t i;
    for (i = 0; i < dst->size; ++i) {
        if (compare(dst->data + i * dst->elem_size, pdata) == 0) {
            return i;
        }
    }

    return FAILURE;
}

int find_value_count_dst(PDST dst, const void* pdata, int(*compare)(const void*, const void*), size_t n) {
    assert(dst != NULL);
    assert(pdata != NULL);
    assert(compare != NULL);
    assert(n != 0);

    size_t i;
    for (i = 0; i < dst->size; ++i) {
        if (compare(dst->data + i * dst->elem_size, pdata) == 0) {
            if (--n == 0) {
                return i;
            }
        }
    }

    return FAILURE;
}

int find_condition_dst(PDST dst, bool(*condition)(const void*)) {
    assert(dst != NULL);
    assert(condition != NULL);

    size_t i;
    for(i = 0; i < dst->size; ++i) {
        if (condition(dst->data + i * dst->elem_size) == 0) {
            return i;
        }
    }

    return FAILURE;
}

int find_condition_count_dst(PDST dst, bool(*condition)(const void*), size_t n) {
    assert(dst != NULL);
    assert(condition != NULL);
    assert(n != 0);

    size_t i;
    for(i = 0; i < dst->size; ++i) {
        if (condition(dst->data + i * dst->elem_size) == 0) {
            if (--n == 0) {
                return i;
            }
        }
    }

    return FAILURE;
}

size_t count_value_dst(PDST dst, const void* val, int(*compare)(const void*, const void*)) {
    assert(dst != NULL);
    assert(val != NULL);
    assert(compare != NULL);

    size_t i;
    size_t cnt = 0;
    for (i = 0; i < dst->size; ++i) {
        if (compare(dst->data + i * dst->elem_size, val) == 0) {
            ++cnt;
        }
    }

    return cnt;
}

size_t count_condition_dst(PDST dst, bool(*condition)(const void*)) {
    assert(dst != NULL);
    assert(condition != NULL);

    size_t i;
    size_t cnt = 0;
    for (i = 0; i < dst->size; ++i) {
        if (condition(dst->data + i * dst->elem_size) == 0) {
            ++cnt;
        }
    }

    return cnt;
}

void foreach_dst(PDST dst, void(*foreach)(void*)) {
    assert(dst != NULL);
    assert(foreach != NULL);
    size_t i;
    for(i = 0; i < dst->size; ++i) {
        foreach(dst->data + i * dst->elem_size);
    }
}

void foreach_reverse_dst(PDST dst, void(*foreach)(void*)) {
    assert(dst != NULL);
    assert(foreach != NULL);
    int i;
    for (i = dst->size - 1; i >= 0; --i) {
        foreach(dst->data + i * dst->elem_size);
    }

}