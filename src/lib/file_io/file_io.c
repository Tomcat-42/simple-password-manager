#include "file_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../config.h"

cJSON *get_json() {
    FILE *json_file = NULL;
    char *json_string = NULL;
    cJSON *json = NULL;
    size_t file_size = 0;

    if (!(json_file = fopen(PASSWORD_FILE, "r"))) {
        json_string = (char *)malloc(sizeof(char) * 3);
        strcpy(json_string, "[]");
    } else {
        fseek(json_file, 0, SEEK_END);
        file_size = ftell(json_file);
        json_string = (char *)malloc(sizeof(char) * file_size);

        rewind(json_file);
        fgets(json_string, file_size, json_file);
        fclose(json_file);
    }

    json = cJSON_Parse(json_string);

    free(json_string);

    return json;
}

int save_json(cJSON *json) {
    FILE *json_file = NULL;
    char *json_string = NULL;
    size_t file_size = 0;

    json_string = cJSON_PrintUnformatted(json);
    json_file = fopen(PASSWORD_FILE, "w");

    if (!(json_file && json_string)) {
        fclose(json_file);
        return 1;
    }

    fputs(json_string, json_file);

    fclose(json_file);
    return 0;
}
