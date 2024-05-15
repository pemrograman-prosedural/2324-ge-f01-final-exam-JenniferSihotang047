// 12S23009 - Dina Marlina Siagian
// 12S23047 - Jennifer Hopenes Sihotang

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include "./libs/gender.h"

struct student_t *students = NULL;
int num_students = 0;
int student_capacity = 0;

struct dorm_t *dorms = NULL;
int num_dorms = 0;
int dorm_capacity = 0;

void allocate_students(int _size) {
    students = (struct student_t *)malloc(_size * sizeof(struct student_t));
    if (students == NULL) {
        fprintf(stderr, "Failed to allocate memory for students\n");
        exit(1);
    }
    student_capacity = _size;
}

void add_student(char *_id, char *_name, char *_year, enum gender_t gender) {
    if (num_students >= student_capacity) {
        student_capacity *= 2;
        students = realloc(students, student_capacity * sizeof(struct student_t));
        if (students == NULL) {
            fprintf(stderr, "Failed to allocate memory for students\n");
            exit(1);
        }
    }

    struct student_t new_student;
    strncpy(new_student.id, _id, sizeof(new_student.id) - 1);
    new_student.id[sizeof(new_student.id) - 1] = '\0';

    strncpy(new_student.name, _name, sizeof(new_student.name) - 1);
    new_student.name[sizeof(new_student.name) - 1] = '\0';

    strncpy(new_student.year, _year, sizeof(new_student.year) - 1);
    new_student.year[sizeof(new_student.year) - 1] = '\0';

    new_student.gender = gender;
    new_student.dorm = NULL;

    students[num_students] = new_student;
    num_students++;
}

void free_students() {
    free(students);
}

void allocate_dorms(int _size) {
    dorms = (struct dorm_t *)malloc(_size * sizeof(struct dorm_t));
    if (dorms == NULL) {
        fprintf(stderr, "Failed to allocate memory for dorms\n");
        exit(1);
    }
    dorm_capacity = _size;
}

void add_dorm(char *_name, unsigned short _capacity, enum gender_t _gender) {
    if (num_dorms >= dorm_capacity) {
        dorm_capacity *= 2;
        dorms = realloc(dorms, dorm_capacity * sizeof(struct dorm_t));
        if (dorms == NULL) {
            fprintf(stderr, "Failed to allocate memory for dorms\n");
            exit(1);
        }
    }

    struct dorm_t new_dorm;
    strncpy(new_dorm.name, _name, sizeof(new_dorm.name) - 1);
    new_dorm.name[sizeof(new_dorm.name) - 1] = '\0';
    new_dorm.capacity = _capacity;
    new_dorm.gender = _gender;
    new_dorm.residents_num = 0;
    dorms[num_dorms] = new_dorm;
    num_dorms++;
}

void assign ( student *student_, dorm *dorm_ )
{
    if ( student_->gender == dorm_->gender && dorm_->residents_num < dorm_->capacity )
    {
        student_->dorm = dorm_;
        dorm_->residents_num++;
    }
    else {
        student_->dorm = NULL;
    }
}

void unassign ( student *student_, dorm* dorm_ )
{
    if ( student_->dorm == dorm_ ) {
        student_->dorm = NULL;
        dorm_->residents_num--;
    }
}

void emptyDorm ( dorm* residence, student** potentialResidents, unsigned short totalPR )
{
    for (size_t i=0; i<totalPR; i++) {
        if (potentialResidents[i]->dorm != NULL) {
            if (potentialResidents[i]->dorm == residence)
                unassign(potentialResidents[i], residence);
        }
    }
}

void free_dorms() {
    free(dorms);
}

void print_all_dorms() {
    for (int i = 0; i < num_dorms; i++) {
        printf("%s|%d|%s\n", dorms[i].name, dorms[i].capacity, dorms[i].gender == GENDER_MALE ? "male" : "female");
    }
}

int main(int argc, char **argv) {
    char input[100];
    char *token;

    allocate_students(1);
    allocate_dorms(1);

    while (1) {
        fgets(input, sizeof(input), stdin);
        token = strtok(input, "#\n");

        if (token != NULL) {
            if (strcmp(token, "student-add") == 0) {
                char id[12];
                char name[40];
                char year[5];
                enum gender_t gender;

                token = strtok(NULL, "#\n");
                strncpy(id, token, sizeof(id) - 1);
                id[sizeof(id) - 1] = '\0';

                token = strtok(NULL, "#\n");
                strncpy(name, token, sizeof(name) - 1);
                name[sizeof(name) - 1] = '\0';

                token = strtok(NULL, "#\n");
                strncpy(year, token, sizeof(year) - 1);
                year[sizeof(year) - 1] = '\0';

                token = strtok(NULL, "#\n");
                if (strcmp(token, "male") == 0) {
                    gender = GENDER_MALE;
                } else {
                    gender = GENDER_FEMALE;
                }

                add_student(id, name, year, gender);
            } else if (strcmp(token, "student-print-all") == 0) {
                for (int i = 0; i < num_students; i++) {
                    printf("%s|%s|%s|%s\n", students[i].id, students[i].name, students[i].year, students[i].gender == GENDER_MALE ? "male" : "female");
                }
            }else if (strcmp(token, "student-print-all-detail") == 0) {
                for (int i = 0; i < num_students; i++) {
                    printf("%s|%s|%s|%s|unassigned\n", students[i].id, students[i].name, students[i].year, students[i].gender == GENDER_MALE ? "male" : "female");
                }
            } else if (strcmp(token, "assign-student")==0){
                token = strtok (NULL, "#\n"); 
                token = strtok (NULL, "#\n"); 
                char *_id = token;
                char *dorm_name = token;

                short studentId = findStudentId(_id, students, num_students);
                short dormId = findDormId(dorm_name, dorms, num_dorms);

                 if ( studentId>=0 && dormId>=0 ) {
                    assign(&students[studentId], &dorms[dormId]);
                }                               
            } else if (strcmp(token, "dorm-add") == 0) {
                char name[20];
                unsigned short capacity;
                enum gender_t gender;

                token = strtok(NULL, "#\n");
                strncpy(name, token, sizeof(name) - 1);
                name[sizeof(name) - 1] = '\0';

                token = strtok(NULL, "#\n");
                capacity = (unsigned short)atoi(token);

                token = strtok(NULL, "#\n");
                if (strcmp(token, "male") == 0) {
                    gender = GENDER_MALE;
                } else {
                    gender = GENDER_FEMALE;
                }

                add_dorm(name, capacity, gender);
            } else if (strcmp(token, "dorm-print-all") == 0) {
                print_all_dorms();
            } else if (strcmp(token, "dorm-print-all-detail") == 0) {
                  for (int i = 0; i < num_dorms; i++) {
                        printf("%s|%d|%s|%d\n", dorms[i].name, dorms[i].capacity, dorms[i].gender == GENDER_MALE ? "male" : "female", dorms[i].residents_num);
                }
            } else if (strcmp( token, "student-leave")==0){
                token = strtok (NULL, "#\n");
                                for (int i = 0; i < num_students; i++) {
                    printf("%s|%s|%s|%s|left\n", students[i].id, students[i].name, students[i].year, students[i].gender == GENDER_MALE ? "male" : "female");
            }    
            } else if (strcmp(token, "---") == 0) {
                break;
            }
        }
    }

    free_students();
    free_dorms();
    
    return 0;
}