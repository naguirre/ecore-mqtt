/******************************************************************************
** Copyright (c) 2014, emqtt. All Rights Reserved.
**
** Authors: Nicolas Aguirre, Julien Masson
**
** This file is part of emqtt.
**
** emqtt is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2.1 of the License, or
** (at your option) any later version.
**
** emqtt is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Foobar; if not, write to the Free Software
** Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
**
******************************************************************************/
#ifndef __EMQTT_H__
#define __EMQTT_H__

#include <sys/socket.h>
#include <netinet/in.h>

#include <Ecore.h>

#ifdef EAPI
# undef EAPI
#endif

#ifdef _WIN32
# ifdef EFL_ECORE_CON_BUILD
#  ifdef DLL_EXPORT
#   define EAPI __declspec(dllexport)
#  else
#   define EAPI
#  endif
# else
#  define EAPI __declspec(dllimport)
# endif
#else
# ifdef __GNUC__
#  if __GNUC__ >= 4
#   define EAPI __attribute__ ((visibility("default")))
#  else
#   define EAPI
#  endif
# else
#  define EAPI
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif /* ifdef __cplusplus */

#define EMQTT_MAX_RETRY 6
#define EMQTT_TIMEOUT_CONNECT 5

typedef struct _EMqtt_Sn_Client EMqtt_Sn_Client;
typedef struct _EMqtt_Sn_Server EMqtt_Sn_Server;

enum _EMQTT_SN_CONNECTION_STATE
{
    EMQTT_SN_CONNECTION_CLOSED,
    EMQTT_SN_CONNECTION_ACCEPTED,
    EMQTT_SN_CONNECTION_IN_PROGRESS,
    EMQTT_SN_CONNECTION_ERROR
};
typedef enum _EMQTT_SN_CONNECTION_STATE EMQTT_SN_CONNECTION_STATE;

enum _EMQTT_SN_REGISTER_STATE
{
    EMQTT_SN_REGISTER_ACCEPTED,
    EMQTT_SN_REGISTER_IN_PROGRESS,
    EMQTT_SN_REGISTER_ERROR
};
typedef enum _EMQTT_SN_REGISTER_STATE EMQTT_SN_REGISTER_STATE;

enum _EMQTT_SN_ERROR_TYPE
{
    EMQTT_SN_ACCEPTED,
    EMQTT_SN_ERROR
};
typedef enum _EMQTT_SN_ERROR_TYPE EMQTT_SN_ERROR_TYPE;

typedef void (*EMqtt_Sn_Client_Connect_Cb) (void *data, EMqtt_Sn_Client *client, EMQTT_SN_CONNECTION_STATE connection_state);
typedef void (*EMqtt_Sn_Client_Topic_Received_Cb) (void *data, EMqtt_Sn_Client *client, const char *topic, const char *value);
typedef void (*EMqtt_Sn_Client_Subscribe_Error_Cb) (void *data, EMQTT_SN_ERROR_TYPE state);
typedef void (*EMqtt_Sn_Client_Suback_Received_Cb) (void *data, EMqtt_Sn_Client *client);

  /* General */

EAPI int emqtt_init(void);
EAPI int emqtt_shutdown(void);

  /* Server/Broker */

EAPI EMqtt_Sn_Server *emqtt_sn_server_add(char *addr, unsigned short port, unsigned char gw_id);
EAPI void             emqtt_sn_server_del(EMqtt_Sn_Server *srv);

  /* Client */

EAPI EMqtt_Sn_Client *emqtt_sn_client_add(char *addr, unsigned short port, char *client_name);
EAPI void             emqtt_sn_client_del(EMqtt_Sn_Client *srv);

EAPI void             emqtt_sn_client_connect(EMqtt_Sn_Client *client, EMqtt_Sn_Client_Connect_Cb connected_cb, void *data, double keepalive);

EAPI void             emqtt_sn_client_subscribe(EMqtt_Sn_Client *client, const char *topic_name, EMqtt_Sn_Client_Topic_Received_Cb topic_received_cb, EMqtt_Sn_Client_Subscribe_Error_Cb subscribe_error_cb, void *data);

EAPI void             emqtt_sn_client_publish(EMqtt_Sn_Client *client, const char *topic_name, const char *publish_data, EMqtt_Sn_Client_Suback_Received_Cb suback_received_cb, void *data);

#ifdef __cplusplus
}
#endif /* ifdef __cplusplus */

#endif
