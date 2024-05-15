#include "student.h"
#include <string.h>

struct student_t create_student(char *_id, char *_name, char *_year, enum gender_t _gender) {
  struct student_t student;

  strncpy(student.id, _id, sizeof(student.id) - 1);
  student.id[sizeof(student.id) - 1] = '\0';

  strncpy(student.name, _name, sizeof(student.name) - 1);
  student.name[sizeof(student.name) - 1] = '\0';

  strncpy(student.year, _year, sizeof(student.year) - 1);
  student.year[sizeof(student.year) - 1] = '\0';

  student.gender = _gender;
  student.dorm = NULL; 

  return student;
}

short findStudentIdx ( char *_id, struct student_t *list, int length ) {
    for ( short i=0; i<length; i++ ) {
        if ( strcmp(list[i].id, _id) == 0 )
            return i;
    }

    return -1;
}

