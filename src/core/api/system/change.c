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
#include "change.h"
#include "load.h"
#include "store.h"

#include <unistd.h>

#include <sysrepo.h>
#include <srpc.h>

#include <assert.h>

static int system_change_contact_create(system_ctx_t *ctx, const char *value);
static int system_change_contact_modify(system_ctx_t *ctx, const char *old_value, const char *new_value);
static int system_change_contact_delete(system_ctx_t *ctx);

static int system_change_hostname_create(system_ctx_t *ctx, const char *value);
static int system_change_hostname_modify(system_ctx_t *ctx, const char *old_value, const char *new_value);
static int system_change_hostname_delete(system_ctx_t *ctx);

static int system_change_location_create(system_ctx_t *ctx, const char *value);
static int system_change_location_modify(system_ctx_t *ctx, const char *old_value, const char *new_value);
static int system_change_location_delete(system_ctx_t *ctx);

static int system_change_timezone_name_create(system_ctx_t *ctx, const char *value);
static int system_change_timezone_name_modify(system_ctx_t *ctx, const char *old_value, const char *new_value);
static int system_change_timezone_name_delete(system_ctx_t *ctx);

int system_change_contact(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx)
{
	int error = 0;
	const char *node_name = LYD_NAME(change_ctx->node);
	const char *node_value = lyd_get_value(change_ctx->node);

	assert(strcmp(node_name, "contact") == 0);

	SRPLG_LOG_DBG(PLUGIN_NAME, "Node Name: %s; Previous Value: %s, Value: %s; Operation: %d", node_name, change_ctx->previous_value, node_value, change_ctx->operation);

	switch (change_ctx->operation) {
		case SR_OP_CREATED:
			error = system_change_contact_create(priv, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_contact_create() error (%d)", error);
				return -1;
			}
			break;
		case SR_OP_MODIFIED:
			error = system_change_contact_modify(priv, change_ctx->previous_value, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_contact_modify() error (%d)", error);
				return -2;
			}
			break;
		case SR_OP_DELETED:
			error = system_change_contact_delete(priv);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_contact_delete() error (%d)", error);
				return -3;
			}
			break;
		case SR_OP_MOVED:
			break;
	}

	return error;
}

int system_change_hostname(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx)
{
	int error = 0;
	const char *node_name = LYD_NAME(change_ctx->node);
	const char *node_value = lyd_get_value(change_ctx->node);

	assert(strcmp(node_name, "hostname") == 0);

	SRPLG_LOG_DBG(PLUGIN_NAME, "Node Name: %s; Previous Value: %s, Value: %s; Operation: %d", node_name, change_ctx->previous_value, node_value, change_ctx->operation);

	switch (change_ctx->operation) {
		case SR_OP_CREATED:
			error = system_change_hostname_create(priv, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_hostname_create() error (%d)", error);
				return -1;
			}
			break;
		case SR_OP_MODIFIED:
			error = system_change_hostname_modify(priv, change_ctx->previous_value, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_hostname_modify() error (%d)", error);
				return -2;
			}
			break;
		case SR_OP_DELETED:
			error = system_change_hostname_delete(priv);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_hostname_delete() error (%d)", error);
				return -3;
			}
			break;
		case SR_OP_MOVED:
			break;
	}

	return error;
}

int system_change_location(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx)
{
	int error = 0;
	const char *node_name = LYD_NAME(change_ctx->node);
	const char *node_value = lyd_get_value(change_ctx->node);

	assert(strcmp(node_name, "location") == 0);

	SRPLG_LOG_DBG(PLUGIN_NAME, "Node Name: %s; Previous Value: %s, Value: %s; Operation: %d", node_name, change_ctx->previous_value, node_value, change_ctx->operation);

	switch (change_ctx->operation) {
		case SR_OP_CREATED:
			error = system_change_location_create(priv, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_location_create() error (%d)", error);
				return -1;
			}
			break;
		case SR_OP_MODIFIED:
			error = system_change_location_modify(priv, change_ctx->previous_value, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_location_modify() error (%d)", error);
				return -2;
			}
			break;
		case SR_OP_DELETED:
			error = system_change_location_delete(priv);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_location_delete() error (%d)", error);
				return -3;
			}
			break;
		case SR_OP_MOVED:
			break;
	}

	return error;
}

int system_change_timezone_name(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx)
{
	int error = 0;
	const char *node_name = LYD_NAME(change_ctx->node);
	const char *node_value = lyd_get_value(change_ctx->node);

	assert(strcmp(node_name, "timezone-name") == 0);

	SRPLG_LOG_DBG(PLUGIN_NAME, "Node Name: %s; Previous Value: %s, Value: %s; Operation: %d", node_name, change_ctx->previous_value, node_value, change_ctx->operation);

	switch (change_ctx->operation) {
		case SR_OP_CREATED:
			error = system_change_timezone_name_create(priv, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_timezone_name_create() error (%d)", error);
				return -1;
			}
			break;
		case SR_OP_MODIFIED:
			error = system_change_timezone_name_modify(priv, change_ctx->previous_value, node_value);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_timezone_name_modify() error (%d)", error);
				return -2;
			}
			break;
		case SR_OP_DELETED:
			error = system_change_timezone_name_delete(priv);
			if (error) {
				SRPLG_LOG_ERR(PLUGIN_NAME, "system_change_timezone_name_delete() error (%d)", error);
				return -3;
			}
			break;
		case SR_OP_MOVED:
			break;
	}

	return error;
}

static int system_change_contact_create(system_ctx_t *ctx, const char *value)
{
	int error = 0;
	return error;
}

static int system_change_contact_modify(system_ctx_t *ctx, const char *old_value, const char *new_value)
{
	int error = 0;
	return error;
}

static int system_change_contact_delete(system_ctx_t *ctx)
{
	int error = 0;
	return error;
}

static int system_change_hostname_create(system_ctx_t *ctx, const char *value)
{
	int error = 0;

	error = system_store_hostname(ctx, value);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "system_store_hostname() error (%d)", error);
		return -1;
	}

	return 0;
}

static int system_change_hostname_modify(system_ctx_t *ctx, const char *old_value, const char *new_value)
{
	(void) old_value;
	return system_change_hostname_create(ctx, new_value);
}

static int system_change_hostname_delete(system_ctx_t *ctx)
{
	int error = 0;

	error = system_store_hostname(ctx, "none");
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "system_store_hostname() error (%d)", error);
		return -1;
	}

	return 0;
}

static int system_change_location_create(system_ctx_t *ctx, const char *value)
{
	int error = 0;
	return error;
}

static int system_change_location_modify(system_ctx_t *ctx, const char *old_value, const char *new_value)
{
	int error = 0;
	return error;
}

static int system_change_location_delete(system_ctx_t *ctx)
{
	int error = 0;
	return error;
}

static int system_change_timezone_name_create(system_ctx_t *ctx, const char *value)
{
	int error = 0;

	error = system_store_timezone_name(ctx, value);
	if (error) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "system_store_timezone_name() error (%d)", error);
		return -1;
	}

	return 0;
}

static int system_change_timezone_name_modify(system_ctx_t *ctx, const char *old_value, const char *new_value)
{
	(void) old_value;
	return system_change_timezone_name_create(ctx, new_value);
}

static int system_change_timezone_name_delete(system_ctx_t *ctx)
{
	(void) ctx;

	int error = 0;

	error = access(SYSTEM_LOCALTIME_FILE, F_OK);
	if (error != 0) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "/etc/localtime doesn't exist");
		goto error_out;
	}

	error = unlink(SYSTEM_LOCALTIME_FILE);
	if (error != 0) {
		SRPLG_LOG_ERR(PLUGIN_NAME, "unlink() failed (%d)", error);
		goto error_out;
	}

	goto out;

error_out:
	error = -1;

out:
	return error;
}