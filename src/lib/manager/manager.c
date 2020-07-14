#include "manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cJSON/cJSON.h"
#include "../file_io/file_io.h"

Service *service_structify(const char *name, const char *login,
                           const char *password, const char *other) {
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

int service_upsert(Service *service) {
    char *name = NULL;
    int updated = 0, index = 0;
    cJSON *json_array, *it, *item, *new_item;

    json_array = it = item = new_item = NULL;

    /* Get previous services json and create new entry */
    json_array = get_json();
    new_item = cJSON_CreateObject();
    cJSON_AddStringToObject(new_item, "name", service->name);
    cJSON_AddStringToObject(new_item, "login", service->login);
    cJSON_AddStringToObject(new_item, "password", service->password);
    cJSON_AddStringToObject(new_item, "other", service->other);

    /* Search if the service exists */
    for (it = json_array->child, index = 0; it != NULL;
         it = it->next, index++) {
        item = cJSON_GetObjectItem(it, "name");
        name = cJSON_GetStringValue(item);

        /* If exists, flag it for update */
        if (!strcmp(name, service->name)) {
            updated = 1;
            break;
        }
    }

    /* Update or add service */
    if (updated) {
        cJSON_ReplaceItemInArray(json_array, index, new_item);
    } else {
        cJSON_AddItemToArray(json_array, new_item);
    }

    /* Save new array to file */
    save_json(json_array);

    free(new_item);

    /* Zero means inserted and one updated */
    return updated;
}

char *service_show(const char *name) {
    cJSON *json_array, *it, *item;
    char *tgt_name, *json_string, *ret_string;
    int found = 0;

    json_array = it = item = NULL;
    tgt_name = json_string = NULL;

    /* Get the json array and searches for name */
    json_array = get_json();

    for (it = json_array->child; it != NULL; it = it->next) {
        item = cJSON_GetObjectItem(it, "name");
        tgt_name = cJSON_GetStringValue(item);

        /* If found flag as true */
        if (!strcmp(name, tgt_name)) {
            found = 1;
            break;
        }
    }

    /*
     * Copy the result into ret_string, or if not found
     * copy an empty json object
     */
    if (found) {
        json_string = cJSON_PrintUnformatted(it);
        ret_string = (char *)malloc(sizeof(char) * (strlen(json_string) + 1));
        strcpy(ret_string, json_string);
        free(json_string);
    } else {
        ret_string = (char *)malloc(sizeof(char) * (3));
        strcpy(ret_string, "{}");
    }

    free(json_array);

    return ret_string;
}

char *service_list() {
    cJSON *json_array = NULL;

    /* Get the json and returns his string */
    json_array = get_json();
    return cJSON_PrintUnformatted(json_array);
}

int service_delete(const char *name) {
    cJSON *json_array, *it, *item;
    ;
    char *tgt_name = NULL;
    int deleted, index;

    json_array = it = item = NULL;
    deleted = index = 0;

    /* Get the json and search by name*/
    json_array = get_json();

    for (it = json_array->child, index = 0; it != NULL;
         it = it->next, index++) {
        item = cJSON_GetObjectItem(it, "name");
        tgt_name = cJSON_GetStringValue(item);
        /* If found flag as deleted */
        if (!strcmp(name, tgt_name)) {
            deleted = 1;
            break;
        }
    }

    /* Delete the service, if necessary */
    if (deleted) {
        cJSON_DeleteItemFromArray(json_array, index);
        save_json(json_array);
        return 0;
    } else {
        free(json_array);
        return 1;
    }
}
