#include "file_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../config.h"

cJSON *get_json() {
    cJSON *json = NULL;
    FILE *json_file = NULL;
    char *json_string = NULL, ch;
    int file_exists = 0, size;

    // FILE *whoami = NULL;
    // whoami = popen("gpg --version", "r");
    // while ((ch = fgetc(whoami)) != EOF && ch != 255) {
    //     putchar(ch);
    // }
    // putchar('\n');


    /*
     * Check if the gpg encrypted file exists
     * via shell command
     */
    file_exists = !system("test -e " PASSWORD_FILE);

    if (file_exists) {
        /* decrypt the file and gets its contents */
        if (!(json_file = popen(
                  "gpg -q --yes --batch --no-tty -d " PASSWORD_FILE, "r"))) {
            json = cJSON_Parse("[]");
        }

        /* Read char by char the popen pipe */
        size = 1;
        json_string = (char *)malloc(sizeof(char));
        while ((ch = fgetc(json_file)) != EOF && ch != 255) {
            json_string[size - 1] = ch;
            json_string =
                (char *)realloc(json_string, sizeof(char) * (size + 1));
            size++;
        }
        json_string[size] = '\0';

        json = cJSON_Parse(json_string);
        free(json_string);
        pclose(json_file);

    } else {
        /* Create and encrypt the file with an empty json array */
        system(
            "echo \"[]\" | gpg -q --yes --batch --no-tty -e -r " GPG_RECIPIENT
            " -o " PASSWORD_FILE);
        json = cJSON_Parse("[]");
    }

    return json;
}

int save_json(cJSON *json) {
    FILE *json_file = NULL;
    char *json_string = NULL;

    /* stringify and save json to gpg pipe */
    json_string = cJSON_PrintUnformatted(json);
    json_file = popen("gpg -q --yes --batch --no-tty -e -r " GPG_RECIPIENT
                      " -o " PASSWORD_FILE,
                      "w");

    if (!(json_file && json_string)) {
        pclose(json_file);
        return 1;
    }

    fputs(json_string, json_file);

    pclose(json_file);
    free(json_string);
    free(json);

    return 0;
}
