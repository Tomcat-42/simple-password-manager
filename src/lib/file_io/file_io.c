#include "file_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../config.h"

cJSON *get_json() {
    cJSON *json = NULL;
    FILE *json_file = NULL;
    char *json_string = NULL;
    size_t file_size = 0;

    /*
     * Open the password file, or create it
     * if not exists
     */
    if (!(json_file = fopen(PASSWORD_FILE, "a+"))) {
        json = cJSON_Parse("[]");
    } else {
        fseek(json_file, 0, SEEK_END);
        file_size = ftell(json_file);

        /* if file size is zero write an empty
         * json array to it
         */
        if (!file_size) {
            fputs("[]", json_file);
            file_size = 2;
        }

        /* else allocate and get the json string */
        json_string = (char *)malloc(sizeof(char) * (file_size));
        rewind(json_file);
        fgets(json_string, file_size + 1, json_file);

        /* Parse and return the json */
        json = cJSON_Parse(json_string);

        free(json_string);
        fclose(json_file);
    }

    return json;
}

int save_json(cJSON *json) {
    FILE *json_file = NULL;
    char *json_string = NULL;

    /* stringify and save json to file */
    json_string = cJSON_PrintUnformatted(json);
    json_file = fopen(PASSWORD_FILE, "w");

    if (!(json_file && json_string)) {
        fclose(json_file);
        return 1;
    }

    fputs(json_string, json_file);

    fclose(json_file);
    free(json_string);
    free(json);

    return 0;
}
