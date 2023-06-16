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
#include "local_user.h"
#include "core/data/system/authentication/authorized_key/list.h"

#include <stdlib.h>
#include <string.h>

void system_local_user_init(system_local_user_t *user)
{
	*user = (system_local_user_t){0};
}

int system_local_user_set_name(system_local_user_t *user, const char *name)
{
	if (user->name) {
		free(user->name);
		user->name = 0;
	}

	if (name) {
		user->name = strdup(name);
		return user->name == NULL;
	}

	return 0;
}

int system_local_user_set_password(system_local_user_t *user, const char *password)
{
	if (user->password) {
		free(user->password);
		user->password = 0;
	}

	if (password) {
		user->password = strdup(password);
		return user->password == NULL;
	}

	return 0;
}

void system_local_user_free(system_local_user_t *user)
{
	if (user->name) {
		free(user->name);
	}

	if (user->password) {
		free(user->password);
	}

	if (user->key_head) {
		system_authorized_key_list_free(&user->key_head);
	}

	system_local_user_init(user);
}

int system_local_user_cmp_fn(const void *e1, const void *e2)
{
	system_local_user_t *u1 = (system_local_user_t *) e1;
	system_local_user_t *u2 = (system_local_user_t *) e2;

	return strcmp(u1->name, u2->name);
}