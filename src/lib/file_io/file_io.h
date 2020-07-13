/**
 * \file file_io
 *
 * \author Pablo Alessandro Santos Hugen
 * \date 2020-07-12
 *
 * \brief Handles all json IO
 */

#ifndef FILE_IO_H
#define FILE_IO_H

#include "../cJSON/cJSON.h"

cJSON *get_json();

int save_json(cJSON *json);


#endif /* FILE_IO_H */
