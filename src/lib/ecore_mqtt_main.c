#include "Ecore_Mqtt.h"

typedef struct _Ecore_MQTTSN_Msg_Desc Ecore_MQTTSN_Msg_Desc;
typedef enum _ECORE_MQTTSN_MSG_TYPE ECORE_MQTTSN_MSG_TYPE;

enum _ECORE_MQTTSN_MSG_TYPE
  {
    ECORE_MQTTSN_ADVERTISE, 
    ECORE_MQTTSN_SEARCHGW,
    ECORE_MQTTSN_GWINFO,
    ECORE_MQTTSN_RESERVED1,
    ECORE_MQTTSN_CONNECT,
    ECORE_MQTTSN_CONNACK,
    ECORE_MQTTSN_WILLTOPICREQ,
    ECORE_MQTTSN_WILLTOPIC, 
    ECORE_MQTTSN_WILLMSGREQ,
    ECORE_MQTTSN_WILLMSG,
    ECORE_MQTTSN_REGISTER,
    ECORE_MQTTSN_REGACK,
    ECORE_MQTTSN_PUBLISH,
    ECORE_MQTTSN_PUBACK,
    ECORE_MQTTSN_PUBCOMP,
    ECORE_MQTTSN_PUBREC,
    ECORE_MQTTSN_PUBREL,
    ECORE_MQTTSN_RESERVED2,
    ECORE_MQTTSN_SUBSCRIBE,
    ECORE_MQTTSN_SUBACK,
    ECORE_MQTTSN_UNSUBSCRIBE,
    ECORE_MQTTSN_UNSUBACK,
    ECORE_MQTTSN_PINGREQ,
    ECORE_MQTTSN_PINGRESP,
    ECORE_MQTTSN_DISCONNECT,
    ECORE_MQTTSN_RESERVED3,
    ECORE_MQTTSN_WILLTOPICUPD,
    ECORE_MQTTSN_WILLTOPICRESP, 
    ECORE_MQTTSN_WILLMSGUPD,
    ECORE_MQTTSN_WILLMSGRESP
  };

struct _Ecore_MQTTSN_Msg_Desc
{
  ECORE_MQTTSN_MSG_TYPE val;
  char *name;
};

const Ecore_MQTTSN_Msg_Desc mqttsn_msg_desc[] = 
  {
    {ECORE_MQTTSN_ADVERTISE,"ADVERTISE" },
    {ECORE_MQTTSN_SEARCHGW,"SEARCHGW"},
    {ECORE_MQTTSN_GWINFO,"GWINFO"},
    {ECORE_MQTTSN_RESERVED1,"RESERVED1"},
    {ECORE_MQTTSN_CONNECT,"CONNECT"},
    {ECORE_MQTTSN_CONNACK,"CONNACK"},
    {ECORE_MQTTSN_WILLTOPICREQ,"WILLTOPICREQ"},
    {ECORE_MQTTSN_WILLTOPIC, "WILLTOPIC"},
    {ECORE_MQTTSN_WILLMSGREQ,"WILLMSGREQ"},
    {ECORE_MQTTSN_WILLMSG,"WILLMSG"},
    {ECORE_MQTTSN_REGISTER,"REGISTER"},
    {ECORE_MQTTSN_REGACK,"REGACK"},
    {ECORE_MQTTSN_PUBLISH,"PUBLISH"},
    {ECORE_MQTTSN_PUBACK,"PUBACK"},
    {ECORE_MQTTSN_PUBCOMP,"PUBCOMP"},
    {ECORE_MQTTSN_PUBREC,"PUBREC"},
    {ECORE_MQTTSN_PUBREL,"PUBREL"},
    {ECORE_MQTTSN_RESERVED2,"RESERVED2"},
    {ECORE_MQTTSN_SUBSCRIBE,"SUBSCRIBE"},
    {ECORE_MQTTSN_SUBACK,"SUBACK"},
    {ECORE_MQTTSN_UNSUBSCRIBE,"UNSUBSCRIBE"},
    {ECORE_MQTTSN_UNSUBACK,"UNSUBACK"},
    {ECORE_MQTTSN_PINGREQ,"PINGREQ"},
    {ECORE_MQTTSN_PINGRESP,"PINGRESP"},
    {ECORE_MQTTSN_DISCONNECT,"DISCONNECT"},
    {ECORE_MQTTSN_RESERVED3,"RESERVED3"},
    {ECORE_MQTTSN_WILLTOPICUPD,"WILLTOPICUPD"},
    {ECORE_MQTTSN_WILLTOPICRESP,"WILLTOPICRESP"},
    {ECORE_MQTTSN_WILLMSGUPD,"WILLMSGUPD"},
    {ECORE_MQTTSN_WILLMSGRESP, "WILLMSGRESP"},
  };

struct _Ecore_Mqtt_Sn_Server
{
  const char *addr;
  unsigned short port;
  Ecore_Con_Server *econ_srv;
  Eina_Hash *subscribers;
};

typedef enum _ECORE_MQTT_SN_RETURN_CODE ECORE_MQTT_SN_RETURN_CODE;
typedef struct _Ecore_Mqtt_Sn_Small_Header Ecore_Mqtt_Sn_Small_Header;
typedef struct _Ecore_Mqtt_Sn_Advertise_Msg Ecore_Mqtt_Sn_Advertise_Msg;
typedef struct _Ecore_Mqtt_Sn_Searchgw_Msg Ecore_Mqtt_Sn_Searchgw_Msg;
typedef struct _Ecore_Mqtt_Sn_Gwinfo_Msg Ecore_Mqtt_Sn_Gwinfo_Msg;
typedef struct _Ecore_Mqtt_Sn_Connect_Msg Ecore_Mqtt_Sn_Connect_Msg;
typedef struct _Ecore_Mqtt_Sn_Connack_Msg Ecore_Mqtt_Sn_Connack_Msg;
typedef struct _Ecore_Mqtt_Sn_Willtopicreq_Msg Ecore_Mqtt_Sn_Willtopicreq_Msg;
typedef struct _Ecore_Mqtt_Sn_Willtopic_Msg Ecore_Mqtt_Sn_Willtopic_Msg;
typedef struct _Ecore_Mqtt_Sn_Willmsgreq_Msg Ecore_Mqtt_Sn_Willmsgreq_Msg;
typedef struct _Ecore_Mqtt_Sn_Willmsg_Msg Ecore_Mqtt_Sn_Willmsg_Msg;
typedef struct _Ecore_Mqtt_Sn_Register_Msg Ecore_Mqtt_Sn_Register_Msg;
typedef struct _Ecore_Mqtt_Sn_Regack_Msg Ecore_Mqtt_Sn_Regack_Msg;
typedef struct _Ecore_Mqtt_Sn_Publish_Msg Ecore_Mqtt_Sn_Publish_Msg;
typedef struct _Ecore_Mqtt_Sn_Puback_Msg Ecore_Mqtt_Sn_Puback_Msg;
typedef struct _Ecore_Mqtt_Sn_Pubcomp_Msg Ecore_Mqtt_Sn_Pubcomp_Msg;
typedef struct _Ecore_Mqtt_Sn_Pubrec_Msg Ecore_Mqtt_Sn_Pubrec_Msg;
typedef struct _Ecore_Mqtt_Sn_Pubrel_Msg Ecore_Mqtt_Sn_Pubrel_Msg;
typedef struct _Ecore_Mqtt_Sn_Subscribe_Msg Ecore_Mqtt_Sn_Subscribe_Msg;
typedef struct _Ecore_Mqtt_Sn_Suback_Msg Ecore_Mqtt_Sn_Suback_Msg;
typedef struct _Ecore_Mqtt_Sn_Unsbuback_Msg Ecore_Mqtt_Sn_Unsbuback_Msg;
typedef struct _Ecore_Mqtt_Sn_Pingreq_Msg Ecore_Mqtt_Sn_Pingreq_Msg;
typedef struct _Ecore_Mqtt_Sn_Pingresp_Msg Ecore_Mqtt_Sn_Pingresp_Msg;
typedef struct _Ecore_Mqtt_Sn_Disconnect_Msg Ecore_Mqtt_Sn_Disconnect_Msg;
typedef struct _Ecore_Mqtt_Sn_Willtopicupd_Msg Ecore_Mqtt_Sn_Willtopicupd_Msg;
typedef struct _Ecore_Mqtt_Sn_Willtopicresp_Msg Ecore_Mqtt_Sn_Willtopicresp_Msg;
typedef struct _Ecore_Mqtt_Sn_Willmsgupd_Msg Ecore_Mqtt_Sn_Willmsgupd_Msg;
typedef struct _Ecore_Mqtt_Sn_Willmsgresp_Msg Ecore_Mqtt_Sn_Willmsgresp_Msg;    

enum _ECORE_MQTT_SN_RETURN_CODE
{
  ECORE_MQTT_SN_RETURN_CODE_ACCEPTED,
  ECORE_MQTT_SN_RETURN_CODE_CONGESTION,
  ECORE_MQTT_SN_RETURN_CODE_INVALID_TOPIC_ID,
  ECORE_MQTT_SN_RETURN_CODE_NOT_SUPPORTED,
  ECORE_MQTT_SN_RETURN_CODE_SENTINEL,
};

struct _Ecore_Mqtt_Sn_Small_Header
{
  uint8_t len;
  uint8_t msg_type;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Advertise_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t gw_id;
  uint16_t duration;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Searchgw_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t radius;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Gwinfo_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t radius;
  char *data;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Connect_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  uint8_t protocol_id;
  uint16_t duration;
} __attribute__((packed));


struct _Ecore_Mqtt_Sn_Connack_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t ret_code;
} __attribute__((packed));


struct _Ecore_Mqtt_Sn_Willtopicreq_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willtopic_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  char *will_topic;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willmsgreq_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willmsg_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  char *will_msg;
} __attribute__((packed));


struct _Ecore_Mqtt_Sn_Register_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t topic_id;
  uint16_t msg_id;
  char *topic_name;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Regack_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t topic_id;
  uint16_t msg_id;
  uint8_t ret_code;
} __attribute__((packed));


struct _Ecore_Mqtt_Sn_Publish_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  uint16_t topic_id;
  uint16_t msg_id;
  char *data;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Puback_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t topic_id;
  uint16_t msg_id;
  uint8_t ret_code;
} __attribute__((packed));


struct _Ecore_Mqtt_Sn_Pubrec_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t msg_id;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Pubrel_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t msg_id;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Pubcomp_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t msg_id;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Subscribe_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  uint16_t msg_id;
  uint16_t topic_id;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Suback_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  uint16_t topic_id;
  uint16_t msg_id;
  uint8_t ret_code;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Unubscribe_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  uint16_t msg_id;
  char *topic_name;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Unsuback_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t msg_id;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Pingreq_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  char* client_id;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Pingresp_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Disconnect_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint16_t duration;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willtopicupd_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t flags;
  char* will_topic;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willmsgcupd_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  char* will_msg;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willtopicresp_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t ret_code;
} __attribute__((packed));

struct _Ecore_Mqtt_Sn_Willmsgresp_Msg
{
  Ecore_Mqtt_Sn_Small_Header header;
  uint8_t ret_code;
} __attribute__((packed));

static int _ecore_mqtt_init_count = 0;


typedef struct _Server Server;

struct _Server
{
  int sdata;
};


static Eina_Bool
_mqtt_ecore_conn_add(void *data, int type EINA_UNUSED, Ecore_Con_Event_Client_Add *ev)
{
  Ecore_Mqtt_Sn_Server *srv  = data;
  if (srv->econ_srv !=  ecore_con_client_server_get(ev->client))
    return ECORE_CALLBACK_RENEW;

  printf("New connection : ip %s, port %d, connected = %d\n",
         ecore_con_client_ip_get(ev->client),
	 ecore_con_client_port_get(ev->client),
	 ecore_con_client_connected_get(ev->client));

  return ECORE_CALLBACK_RENEW;
}

static Eina_Bool
_mqtt_ecore_conn_del(void *data EINA_UNUSED, int type EINA_UNUSED, Ecore_Con_Event_Client_Del *ev)
{
  Ecore_Mqtt_Sn_Server *srv  = data;
  if (srv->econ_srv !=  ecore_con_client_server_get(ev->client))
    return ECORE_CALLBACK_RENEW;

  printf("Connection close\n");
  return ECORE_CALLBACK_RENEW;
}

static Eina_Bool
_mqtt_ecore_conn_data(void *data, int type EINA_UNUSED, Ecore_Con_Event_Client_Data *ev)
{
  Ecore_Mqtt_Sn_Server *srv  = data;
  char *d;
  size_t header_size = 0;
  int i;
  size_t data_size;
  char fmt[32];
  char response[7];
  int pos = 0;
  printf("Connection data\n");

  if (srv->econ_srv !=  ecore_con_client_server_get(ev->client))
    return ECORE_CALLBACK_RENEW;
  
  d = ev->data;
  printf("Data : ");
  for (i = 0; i < ev->size; i++)
    printf("0x%02X ", d[i]);
  printf("\n");

  // Header
  if (d[0] == 0x01)
    {
      header_size = 4;
      data_size = d[1] << 8 | d[2];
      printf("Header size : 4, data_size = %d, msg_type : %s(%d)\n", data_size, mqttsn_msg_desc[d[3]].name, d[3]);
    }
  else
    {
      header_size = 2;
      data_size = d[0];
      printf("Header size : 2, data_size = %d, msg_type : %s(%d)\n", data_size,  mqttsn_msg_desc[d[1]].name, d[1]);

    }

  switch(d[header_size - 1])
    {
    case ECORE_MQTTSN_CONNECT:
      {
        Ecore_Mqtt_Sn_Connect_Msg *msg;
        Ecore_Mqtt_Sn_Connack_Msg resp;
        char *client_id;
        size_t s;

        msg = (Ecore_Mqtt_Sn_Connect_Msg *)ev->data;
        s = msg->header.len - (sizeof(Ecore_Mqtt_Sn_Connect_Msg));
        client_id = calloc(1, s + 1);
        memcpy(client_id, ev->data + sizeof(Ecore_Mqtt_Sn_Connect_Msg) , s);

        printf("flags %d, protocolId : %d, Duration : %d, ClientId : %s\n", msg->flags,
               msg->protocol_id, ntohs(msg->duration), client_id);

        resp.header.len = 0x03;
        resp.header.msg_type = ECORE_MQTTSN_CONNACK;
        resp.ret_code = ECORE_MQTT_SN_RETURN_CODE_ACCEPTED;

	ecore_con_client_send(ev->client, (char*)&resp, sizeof(resp));
	ecore_con_client_flush(ev->client);
      }
      break;
    case ECORE_MQTTSN_REGISTER:
      {

	memset(&fmt, 0, sizeof(fmt));
	memcpy(&fmt, &d[header_size+4], data_size - 4 - header_size);
	printf("TopicId: %d, MsgId: %d, TopicName : %s\n", d[header_size] << 8 | d[header_size+1], d[header_size + 2] << 8 | d[header_size+3], fmt);
        pos = 0;
	response[pos++] = 0x07;
	response[pos++] = ECORE_MQTTSN_REGACK;
	response[pos++] = d[header_size];
	response[pos++] = d[header_size+1];
	response[pos++] = d[header_size+2];
	response[pos++] = d[header_size+3];
	response[pos++] = 0;

	ecore_con_client_send(ev->client, response, pos);
	ecore_con_client_flush(ev->client);
      }
      break;
    case ECORE_MQTTSN_PUBLISH:
      {
	char response[7];
	memset(&fmt, 0, sizeof(fmt));
	memcpy(&fmt, &d[header_size+5], data_size - 5 - header_size);
	printf("flags: %d, TopicId: %d, MsgId : %d, Data : %s\n", d[header_size], d[header_size + 1] << 8 | d[header_size+2], d[header_size + 3] << 8 | d[header_size+4], fmt);
        pos = 0;
	response[pos++] = 0x07;
	response[pos++] = ECORE_MQTTSN_PUBACK;
	response[pos++] = d[header_size+1];
	response[pos++] = d[header_size+2];
	response[pos++] = d[header_size+3];
	response[pos++] = d[header_size+4];
	response[pos++] = 0;
	
	ecore_con_client_send(ev->client, response, pos);
	ecore_con_client_flush(ev->client);
      }
      break;
    case ECORE_MQTTSN_PINGREQ:
      {
        Ecore_Mqtt_Sn_Pingresp_Msg resp;
        
        resp.header.len = 2;
        resp.header.msg_type = ECORE_MQTTSN_PINGRESP;
        ecore_con_client_send(ev->client, &resp, 2);
        ecore_con_client_flush(ev->client);
        break;

      }
    case ECORE_MQTTSN_SUBSCRIBE:
      {
         Ecore_Mqtt_Sn_Subscribe_Msg *msg;
         Ecore_Mqtt_Sn_Suback_Msg resp;
         uint8_t topic_id_type;
         char *topic_name = NULL;
         uint16_t topic_id;
         msg = (Ecore_Mqtt_Sn_Subscribe_Msg *)ev->data;
         topic_id_type = msg->flags & 0x03;
         switch(topic_id_type)
           {
           case 0:
             {
               /* Topic name */
               size_t s;
               
               s = msg->header.len - ((sizeof(Ecore_Mqtt_Sn_Subscribe_Msg) - sizeof(uint16_t)));
               printf("S : %d, %d, %d, %d \n", s, sizeof(Ecore_Mqtt_Sn_Subscribe_Msg), sizeof(uint16_t), msg->header.len);
               topic_name = calloc(1, s + 1);
               memcpy(topic_name, ev->data + sizeof(Ecore_Mqtt_Sn_Subscribe_Msg) - sizeof(uint16_t) , s);
             }
             break;
           case 1:
             /* pre-define Topic id */
             break;
           case 2:
             /* Short Topic name */
             break;
           default:
             break;
           }
         
         printf("flags %d, MsgId : %d,", msg->flags,
                msg->msg_id);
         if (topic_name)
           printf(" Topic Name : %s\n", topic_name);
         else
           printf(" Topic Id : %d\n", msg->topic_id);

         printf("resp len : %d\n", sizeof(Ecore_Mqtt_Sn_Suback_Msg));

         resp.header.len = sizeof(Ecore_Mqtt_Sn_Suback_Msg);
         resp.header.msg_type = ECORE_MQTTSN_SUBACK;
         resp.flags = 0x00;
         resp.topic_id = 0x00;
         resp.msg_id = msg->msg_id;
         resp.ret_code = ECORE_MQTT_SN_RETURN_CODE_ACCEPTED;
         ecore_con_client_send(ev->client, &resp, resp.header.len);
         ecore_con_client_flush(ev->client);

      }
      break;
    default:
      printf("Unknown message\n");
      break;
    }
}
int ecore_mqtt_init(void)
{
  if (++_ecore_mqtt_init_count != 1)
    return _ecore_mqtt_init_count;


  if (!eina_init ())
    return --_ecore_mqtt_init_count;

  if (!ecore_init ())
    return --_ecore_mqtt_init_count;

  if (!ecore_con_init ())
    return --_ecore_mqtt_init_count;

  return _ecore_mqtt_init_count;

}

int ecore_mqtt_shutdown(void)
{
  if (--_ecore_mqtt_init_count != 0)
    return _ecore_mqtt_init_count;

  ecore_con_shutdown();
  ecore_shutdown();
  eina_shutdown();

  return _ecore_mqtt_init_count;
}

Ecore_Mqtt_Sn_Server *ecore_mqtt_sn_server_add(char *addr, unsigned short port)
{
  Ecore_Mqtt_Sn_Server *srv;
   
  if (!addr || !port)
    return NULL;

  srv = calloc(1, sizeof(Ecore_Mqtt_Sn_Server));
  srv->addr = eina_stringshare_add(addr);
  srv->port = port;

  if (!(srv->econ_srv = ecore_con_server_add(ECORE_CON_REMOTE_UDP, addr, port, NULL)))
    {
      ecore_mqtt_sn_server_del(srv);
      return NULL;
    }

  ecore_con_server_data_set(srv->econ_srv, srv);
   
  ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_ADD,
                          (Ecore_Event_Handler_Cb)_mqtt_ecore_conn_add, srv);
  ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_DEL,
                          (Ecore_Event_Handler_Cb)_mqtt_ecore_conn_del, srv);
  ecore_event_handler_add(ECORE_CON_EVENT_CLIENT_DATA,
                          (Ecore_Event_Handler_Cb)_mqtt_ecore_conn_data, srv);


  return srv;

}

void ecore_mqtt_sn_server_del(Ecore_Mqtt_Sn_Server *srv)
{
  if (!srv)
    return;

  if (srv->addr)
    eina_stringshare_del(srv->addr);
  if (srv->econ_srv)
    ecore_con_server_del(srv->econ_srv);
  
  free(srv);
}
