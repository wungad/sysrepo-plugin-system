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
#ifndef SYSTEM_PLUGIN_API_NTP_CHANGE_H
#define SYSTEM_PLUGIN_API_NTP_CHANGE_H

#include "core/types.h"
#include "core/context.h"

#include <srpc.h>

int system_ntp_change_enabled(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);

int system_ntp_change_server_name(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
int system_ntp_change_server_address(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
int system_ntp_change_server_port(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
int system_ntp_change_server_association_type(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
int system_ntp_change_server_iburst(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);
int system_ntp_change_server_prefer(void *priv, sr_session_ctx_t *session, const srpc_change_ctx_t *change_ctx);

#endif // SYSTEM_PLUGIN_API_NTP_CHANGE_H