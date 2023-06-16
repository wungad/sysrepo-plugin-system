/*
 * telekom / sysrepo-plugin-system
 *
 * This program is made available under the terms of the
 * BSD 3-Clause license which is available at
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * SPDX-FileCopyrightText: 2022 Deutsche Telekom AG
 * SPDX-FileContributor: Sartura Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "server.h"
#include <stdlib.h>
#include <string.h>

void system_ntp_server_init(system_ntp_server_t *server)
{
	*server = (system_ntp_server_t){0};
}

int system_ntp_server_set_name(system_ntp_server_t *server, const char *name)
{
	int error = 0;

	if (server->name) {
		free(server->name);
	}

	if (name) {
		server->name = strdup(name);
	}

	return error;
}

int system_ntp_server_set_address(system_ntp_server_t *server, const char *address)
{
	int error = 0;

	if (server->address) {
		free(server->address);
	}

	if (address) {
		server->address = strdup(address);
	}

	return error;
}

int system_ntp_server_set_port(system_ntp_server_t *server, const char *port)
{
	int error = 0;

	if (server->port) {
		free(server->port);
	}

	if (port) {
		server->port = strdup(port);
	}

	return error;
}

int system_ntp_server_set_association_type(system_ntp_server_t *server, const char *association_type)
{
	int error = 0;

	if (server->association_type) {
		free(server->association_type);
	}

	if (association_type) {
		server->association_type = strdup(association_type);
	}

	return error;
}

int system_ntp_server_set_iburst(system_ntp_server_t *server, const char *iburst)
{
	int error = 0;
	if (server->iburst) {
		free(server->iburst);
	}

	if (iburst) {
		server->iburst = strdup(iburst);
	}

	return error;
}

int system_ntp_server_set_prefer(system_ntp_server_t *server, const char *prefer)
{
	int error = 0;

	if (server->prefer) {
		free(server->prefer);
	}

	if (prefer) {
		server->prefer = strdup(prefer);
	}

	return error;
}

void system_ntp_server_free(system_ntp_server_t *server)
{
	if (server->name) {
		free(server->name);
	}

	if (server->address) {
		free(server->address);
	}

	if (server->port) {
		free(server->port);
	}

	if (server->association_type) {
		free(server->association_type);
	}

	if (server->iburst) {
		free(server->iburst);
	}

	if (server->prefer) {
		free(server->prefer);
	}

	system_ntp_server_init(server);
}