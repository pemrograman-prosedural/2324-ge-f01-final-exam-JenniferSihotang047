#include "dorm.h"
#include "string.h"

struct dorm_t create_dorm(char *_name, unsigned short _capacity, enum gender_t _gender) {
  struct dorm_t dorm;

  strncpy(dorm.name, _name, sizeof(dorm.name) - 1);
  dorm.name[sizeof(dorm.name) - 1] = '\0';

  dorm.capacity = _capacity;
  dorm.gender = _gender;
  dorm.residents_num = 0;

  return dorm;
}

short findDormId (char *_name, dorm *list, int length ){
    for (short i = 0; i<length; i++){
        if (strcmp(list[i].name, _name)==0)
            return i;
    }

    return -1;
}
