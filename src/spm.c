#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./lib/cJSON/cJSON.h"
#include "./lib/file_io/file_io.h"

int main(int argc, char **argv) {
    cJSON *json = cJSON_Parse("[{\"um\":\"1\"}]");

    save_json(json);
}
