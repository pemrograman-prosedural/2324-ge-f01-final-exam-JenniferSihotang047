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

