#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./lib/cJSON/cJSON.h"
#include "./lib/file_io/file_io.h"
#include "./lib/manager/manager.h"

int add(const char *name, const char *login, const char *password,
        const char *other) {
    Service *service = service_structify(name, login, password, other);
    const int ret = service_upsert(service);

    free(service);
    return ret;
}

int show(const char *name) {
    char *json_string = NULL, *tmp_string = NULL;
    cJSON *json_obj = NULL, *item = NULL;

    json_string = service_show(name);
    if (strcmp(json_string, "{}")) {
        json_obj = cJSON_Parse(json_string);

        item = cJSON_GetObjectItem(json_obj, "name");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s ", tmp_string);

        item = cJSON_GetObjectItem(json_obj, "login");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s ", tmp_string);

        item = cJSON_GetObjectItem(json_obj, "password");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s ", tmp_string);

        item = cJSON_GetObjectItem(json_obj, "other");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s\n", tmp_string);

        free(json_obj);
        free(json_string);
        return 1;

    } else {
        free(json_string);
        return 0;
    }
}

int list() {
    char *json_string = NULL, *tmp_string = NULL;
    cJSON *json_array = NULL, *it = NULL, *item = NULL;
    int size = 0;

    json_string = service_list();
    json_array = cJSON_Parse(json_string);
    size = cJSON_GetArraySize(json_array);

    for (it = json_array->child; it != NULL; it = it->next) {
        item = cJSON_GetObjectItem(it, "name");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s ", tmp_string);

        item = cJSON_GetObjectItem(it, "login");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s ", tmp_string);

        item = cJSON_GetObjectItem(it, "password");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s ", tmp_string);

        item = cJSON_GetObjectItem(it, "other");
        tmp_string = cJSON_GetStringValue(item);
        printf("%s\n", tmp_string);
    }

    free(json_array);
    free(json_string);

    return (size != 0);
}

int delete (const char *name) {
    const int ret = service_delete(name);

    return ret;
}

int help() {
    printf(
        "Simple password manager\n\n"
        "Add a service:\n"
        "    spm -a|--add name login [password] [other]\n"
        "Show a service:\n"
        "    spm -s|--show name\n"
        "List services:\n"
        "    spm -l|--list\n"
        "Delete a service:\n"
        "    spm -d|--delete name\n");

    return 0;
}

int main(int argc, char **argv) {
    int ret = 0;

    if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
        ret = help();
    } else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--add")) {
        switch (argc) {
            case 4:
                ret = add(argv[2], argv[3], "", "");
                break;
            case 5:
                ret = add(argv[2], argv[3], argv[4], "");
                break;
            case 6:
                ret = add(argv[2], argv[3], argv[4], argv[5]);
                break;
            default:
                ret = help();
        }
    } else if (!strcmp(argv[1], "-s") || !strcmp(argv[1], "--show")) {
        switch (argc) {
            case 3:
                ret = show(argv[2]);
                break;
            default:
                ret = help();
        }
    } else if (!strcmp(argv[1], "-l") || !strcmp(argv[1], "--list")) {
        ret = list();
    } else if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "--delete")) {
        switch (argc) {
            case 3:
                ret = delete (argv[2]);
                break;
            default:
                ret = help();
        }
    } else {
        ret = help();
    }

    return ret;
}
