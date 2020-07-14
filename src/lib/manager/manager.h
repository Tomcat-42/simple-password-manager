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
    char *name, *login, *password, *other;
} Service;

/*
 * Converts a service login, password and other information
 * to a Service struct
 */
Service *service_structify(char *name, char *login, char *password,
                           char *other);

/*
 * Parse a Service struct to a array containing:
 * login, password and other information
 */
char **service_parse(Service *service);

/*
 * Insert a service. If exists a service with the same name update the fields
 */
int service_upsert(Service *service);

/*
 * Return a service struct by name, if found.
 */
char *service_show(const char *name);

/*
 * Return a service struct by name, if found.
 */
char *service_list();

/*
 * Delete a service by name.
 */
int service_delete(const char *name);


#endif /* MANAGER_H */
