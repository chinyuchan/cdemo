#ifndef STUDENT_H
#define STUDENT_H

#define NAME_LEN 40
#define SEX_LEN 8
#define SCORE_CNT 3

typedef struct Student {
    int no;
    char name[NAME_LEN];
    int age;
    char sex[SEX_LEN];
    int score[SCORE_CNT];
}STUDENT;

void stu_sys_run(void);


#endif
