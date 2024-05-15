#ifndef STUDENT_H
#define STUDENT_H

#include "gender.h"
#include "dorm.h"

typedef struct student_t
{
    char id[12];
    char name[40];
    char year[5];
    enum gender_t gender;
    struct dorm_t *dorm;
} student;

student create_student(char *_id, char *_name, char *_year,enum gender_t _gender);
void assign ( student *student_, dorm *dorm_ );
void unassign ( student *student_, dorm* dorm_ );
void moveStudent ( student *migrant, dorm *newResidence , dorm *oldResidence );
void emptyDorm ( dorm* residence, student** potentialResidents, unsigned short totalPR );
#endif
