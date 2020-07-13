#include "manager.h"
#include "../file_io/file_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Service *service_structify(char *login, char *password, char *other) {
    Service *new_service = (Service *)malloc(sizeof(Service));

    new_service->login = (char *)malloc(sizeof(char) * strlen(login));
    new_service->password = (char *)malloc(sizeof(char) * strlen(password));
    new_service->other = (char *)malloc(sizeof(char) * strlen(other));

    strcpy(new_service->login, login);
    strcpy(new_service->password, password);
    strcpy(new_service->other, other);

    return new_service;
}

char **service_parse(Service *service) {
    char **str_arr = (char **)malloc(sizeof(char *) * 3);

    str_arr[0] = (char*)malloc(sizeof(char) * strlen(service->login));
    str_arr[1] = (char*)malloc(sizeof(char) * strlen(service->password));
    str_arr[2] = (char*)malloc(sizeof(char) * strlen(service->other));


    strcpy(str_arr[0], service->login);
    strcpy(str_arr[1], service->password);
    strcpy(str_arr[2], service->other);

    return str_arr;
}
