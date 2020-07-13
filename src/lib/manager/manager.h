/**
 * \file manager
 *
 * \author Pablo Alessandro Santos Hugen
 * \date 2020-07-12
 *
 * \brief This file manages all CRUD operations on passwords
 */

#ifndef MANAGER_H
#define MANAGER_H

typedef struct {
    char *login, *password, *other;
} Service;

/*
 * Converts a service login, password and other information
 * to a Service struct
 */
Service *service_structify(char *login, char *password, char *other);

/*
 * Parse a Service struct to a array containing:
 * login, password and other information
 */
char **service_parse(Service *service);

#endif /* MANAGER_H */
