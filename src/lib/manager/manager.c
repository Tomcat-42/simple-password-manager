#include "manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cJSON/cJSON.h"
#include "../file_io/file_io.h"

Service *service_structify(char *name, char *login, char *password,
                           char *other) {
    Service *new_service = (Service *)malloc(sizeof(Service));

    new_service->name = (char *)malloc(sizeof(char) * strlen(name));
    new_service->login = (char *)malloc(sizeof(char) * strlen(login));
    new_service->password = (char *)malloc(sizeof(char) * strlen(password));
    new_service->other = (char *)malloc(sizeof(char) * strlen(other));

    strcpy(new_service->name, name);
    strcpy(new_service->login, login);
    strcpy(new_service->password, password);
    strcpy(new_service->other, other);

    return new_service;
}

char **service_parse(Service *service) {
    char **str_arr = (char **)malloc(sizeof(char *) * 4);

    str_arr[0] = (char *)malloc(sizeof(char) * strlen(service->name));
    str_arr[1] = (char *)malloc(sizeof(char) * strlen(service->login));
    str_arr[2] = (char *)malloc(sizeof(char) * strlen(service->password));
    str_arr[4] = (char *)malloc(sizeof(char) * strlen(service->other));

    strcpy(str_arr[0], service->name);
    strcpy(str_arr[1], service->login);
    strcpy(str_arr[2], service->password);
    strcpy(str_arr[3], service->other);

    return str_arr;
}

int service_upsert(Service *service) {
    cJSON *json_array = NULL;
    cJSON *it = NULL;
    cJSON *item = NULL;
    cJSON *new_item = NULL;
    char *name = NULL;
    int updated = 0, index = 0;

    json_array = get_json();
    new_item = cJSON_CreateObject();
    cJSON_AddStringToObject(new_item, "name", service->name);
    cJSON_AddStringToObject(new_item, "login", service->login);
    cJSON_AddStringToObject(new_item, "password", service->password);
    cJSON_AddStringToObject(new_item, "other", service->other);

    for (it = json_array->child, index = 0; it != NULL;
         it = it->next, index++) {
        item = cJSON_GetObjectItem(it, "name");
        name = cJSON_GetStringValue(item);
        if (!strcmp(name, service->name)) {
            updated = 1;
            break;
        }
    }

    if (updated) {
        cJSON_ReplaceItemInArray(json_array, index, new_item);
    } else {
        cJSON_AddItemToArray(json_array, new_item);
    }

    save_json(json_array);

    return 0;
}

char *service_show(const char *name) {
    cJSON *json_array = NULL;
    cJSON *it = NULL;
    cJSON *item = NULL;

    json_array = get_json();
    char *tgt_name = NULL;

    for (it = json_array->child; it != NULL;
         it = it->next) {
        item = cJSON_GetObjectItem(it, "name");
        tgt_name = cJSON_GetStringValue(item);
        if (!strcmp(name, tgt_name)) {
            return cJSON_PrintUnformatted(it);
        }
    }

    return "[]";
}

char *service_list() {
    cJSON *json_array = NULL;
    cJSON *it = NULL;
    cJSON *item = NULL;

    json_array = get_json();

    return cJSON_PrintUnformatted(json_array);
}

int service_delete(const char *name) {
    cJSON *json_array = NULL;
    cJSON *it = NULL;
    cJSON *item = NULL;

    char *tgt_name = NULL;
    int deleted = 0, index = 0;

    json_array = get_json();

    for (it = json_array->child, index = 0; it != NULL;
         it = it->next, index++) {
        item = cJSON_GetObjectItem(it, "name");
        tgt_name = cJSON_GetStringValue(item);
        if (!strcmp(name, tgt_name)) {
            deleted = 1;
            break;
        }
    }

    if (deleted) {
        cJSON_DeleteItemFromArray(json_array, index);
        save_json(json_array);
        return 0;
    }

    return 1;
}
