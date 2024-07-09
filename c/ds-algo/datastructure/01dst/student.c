#include "student.h"
#include "dst.h"
int autoNo = 202400001;
typedef PDST(*FUNC)(PDST);

void input_stu(STUDENT* ps) {
    printf("请输入学生姓名:");
    scanf("%s", ps->name);
    printf("请输入学生年龄:");
    scanf("%d", &ps->age);
    printf("请输入学生性别:");
    scanf("%s", ps->sex);
    printf("请输入%d门功课成绩:", SCORE_CNT);
    int i;
    for (i = 0; i< SCORE_CNT; ++i) {
        scanf("%d", &ps->score[i]);
    }
}

void show_stu(const STUDENT* ps) {
    printf("---------------------------------\n");
    printf("学号:%d\n", ps->no);
    printf("姓名:%s\n", ps->name);
    printf("年龄:%d\n", ps->age);
    printf("性别:%s\n", ps->sex);
    printf("成绩:");
    int i;
    for (i = 0; i < SCORE_CNT; ++i) {
        printf("%d ", ps->score[i]);
    }
    printf("\n");
    printf("---------------------------------\n");
}

PDST quit(PDST dst) {
    destroy_dst(dst);
    exit(0);
}
PDST push_back_stu(PDST dst) {
    STUDENT s = {};
    s.no = autoNo++;
    input_stu(&s);
    show_stu(&s);
    if (full_dst(dst)) {
        dst = recapacity_dst(dst, 2 * dst->capacity);
        if (dst == NULL) {
            printf("Error: recapacity\n");
            return NULL;
        }
    }

    if (push_back_dst(dst, &s) == SUCCESS) {
        printf("增加学生成功\n");
    }
    else {
        printf("增加学生失败\n");
    }

    return dst;
}
PDST add_pos_stu(PDST dst) {
    return dst;
}
PDST del_stu(PDST dst) {
    return dst;
}
PDST change_stu(PDST dst) {
    return dst;
}
PDST find_stu(PDST dst) {
    return dst;
}

void show_stu_toline(void* pdata) {
    const STUDENT* ps = pdata;
    printf("%d   %s   %d   %s   ", ps->no, ps->name, ps->age, ps->sex);
    int i;
    for (i = 0; i < SCORE_CNT; ++i) {
        printf("%d ", ps->score[i]);
    }
    printf("\n");
}

PDST list_stu(PDST dst) {
    if(empty_dst(dst)) {
        printf("没有学生!\n");
        return dst;
    }
    printf("==============================================\n");
    printf("学号    姓名    年龄    性别    成绩\n");
    printf("----------------------------------------------\n");
    foreach_dst(dst, show_stu_toline);
    printf("----------------------------------------------\n");
    printf("一共%lu个学生\n", size_dst(dst));
    return dst;
}

PDST base_info(PDST dst) {
    printf("学生个数: %lu\n", size_dst(dst));
    printf("动态顺序表容量: %lu\n", capacity_dst(dst));
    return dst;
}

struct {
    const char* str;
    FUNC func;
}stof[] = {
    {"退出", quit},
    {"在末尾增加学生", push_back_stu},
    {"在指定位置增加学生", add_pos_stu},
    {"删除学生", del_stu},
    {"修改学生信息", change_stu},
    {"查找学生", find_stu},
    {"列出学生", list_stu},
    {"基本信息", base_info}
};

#define CMDCNT sizeof(stof)/sizeof(stof[0])

void show_menu() {
    printf("==========================================\n");
    printf("------学生管理系统（动态顺序表测试）------\n");
    int i;
    for (i = 0; i < CMDCNT; ++i) {
        printf("\r %d.%s\n", i, stof[i].str);
    }
    printf(">>> ");
}

void stu_sys_run() {
    PDST stu_dst = create_dst(sizeof(STUDENT), 10);
    if (stu_dst == NULL) {
        printf("");
        return;
    }
    while(1) {
        show_menu();
        int in = 0;
        scanf("%d", &in);
        if (in >= 0 && in < CMDCNT) {
            stu_dst = stof[in].func(stu_dst);
        }
        else {
            printf("Error!\n");
        }
    }
}

