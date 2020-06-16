#ifndef GAMELOGINSERVER_LOBBY_H
#define GAMELOGINSERVER_LOBBY_H

#include "../PainterEngine Game/DEMO_Runtime.h"
#include "../PainterEngine Game/GameServer_Database.h"

#define GAMELOGINSERVER_LOBBY_MAXONLINE 256
#define GAMELOGINSERVER_LOBBY_OP_OFFLINETIME 600000//operate
#define GAMELOGINSERVER_LOBBY_HB_OFFLINETIME 15000 //heart beat
#define GAMELOGINSERVER_LOBBY_CHATCACHE_COUNT 256
#define GAMELOGINSERVER_LOBBY_MINUTE_HCAT_TIME 1000

#define GAMELOGINSERVER_TEXT_INITIALIZE_LOBBY_UDP_FAILED "��ʼ������������UDP��ʼ��ʧ��."
#define GAMELOGINSERVER_TEXT_LISTEN_LOBBY_UDP_FAILED "������������˿�ʧ��."
#define GAMELOGINSERVER_TEXT_ADD_REGISTRY_CODE_SUCCEEDED "���ע����ɹ�"
#define GAMELOGINSERVER_TEXT_ADD_REGISTRY_CODE_FAILED "���ע����ʧ��"
#define GAMELOGINSERVER_TEXT_LINKING_DATATBASE "�����������ݿ�..."
#define GAMELOGINSERVER_TEXT_LINK_DATATBASE_SUCCEEDED "�������ݿ�ɹ�"
#define GAMELOGINSERVER_TEXT_LINK_DATATBASE_FAILED "�������ݿ�ʧ��"

#define GAMELOGINSERVER_TEXT_USER_GAMEDATA_MISSING "�û�����ȱʧ"
#define GAMELOGINSERVER_TEXT_USER_PROFILE_PHOTO_MISSING "�û�ͷ������ȱʧ"
#define GAMELOGINSERVER_TEXT_USER_LOGIN "�û���¼ %s %d/%d/%d %d:%d:%d"

typedef struct  
{
	px_dword magic;
}GameLoginServer_Lobby_Packet_Header;
//////////////////////////////////////////////////////////////////////////
//sync



typedef enum
{
	DEMO_SERVERSYNC_OPCODE_GETSIZE=0,
	DEMO_SERVERSYNC_OPCODE_ACKGETSIZE,
	DEMO_SERVERSYNC_OPCODE_GETDATA,
	DEMO_SERVERSYNC_OPCODE_ACKGETDATA,
}DEMO_SERVERSYNC_OPCODE;

typedef enum
{
	DEMO_SERVERSYNC_QUERY_TYPE_USERINFO=0,
	DEMO_SERVERSYNC_QUERY_TYPE_PROFILE_PHOTO,
	DEMO_SERVERSYNC_QUERY_TYPE_USERGAME_DATA,
}DEMO_SERVERSYNC_QUERY_TYPE;





//////////////////////////////////////////////////////////////////////////
typedef struct
{
	px_dword nid;
	px_dword userid;
	px_dword usermapid;
	px_dword level;
	px_color namecolor;
	px_byte profilePhoto_data_sha256[32];
	px_char account[32];
	px_char cookie[32];
	px_dword Name[32];
	px_char Message[256];
}GameLoginServer_Lobby_ChatData;


typedef struct
{
	px_bool activated;
	DEMO_ServerDatabase_userInfo userInfo;
	px_byte *profilePhoto_data;
	px_char profilePhoto_data_sha256[32];
	px_dword profilePhoto_datasize;
	px_byte *UserGame_data;//ptr malloc data
	px_dword UserGame_datasize;
	px_byte connect_aes_code[32];
	PX_AES  aes_encoder;
	px_byte pwd[32];
	px_dword id;
	px_byte cookie[32];
	px_dword last_chat_packetid;
	px_dword last_chat_time;
	px_dword last_op_time;
	px_dword online_time;
	px_dword last_hb_elpased;
}GameLoginServer_Lobby_Client;

typedef struct  
{
	px_vector clients;

	px_dword alloc_id;
	px_int max_client;
	px_memorypool mp;
	PX_UDP udp;
	px_uint chatid;
	px_uint wchat_index;
	GameLoginServer_Lobby_ChatData chatData[GAMELOGINSERVER_LOBBY_CHATCACHE_COUNT];
	GameServer_Database *linker_Database;
}GameLoginServer_Lobby;



px_bool GameLoginServer_LobbyLogin(GameLoginServer_Lobby *plb,px_byte aes_code[32],px_char account[32],px_char pwd[32],_OUT px_byte cookie[32],_OUT px_dword *map_index,_OUT px_dword *id);

px_bool GameLoginServer_LobbyInitialize(GameLoginServer_Lobby *plb,GameServer_Database *linker_Database,px_int max_client);

px_void GameLoginServer_LobbyUpdate(GameLoginServer_Lobby *plb,px_dword elpased);

px_void GameLoginServer_LobbyFree(GameLoginServer_Lobby *plb);

px_void GameLoginServer_LobbyClientRelease(GameLoginServer_Lobby *plb,px_int index);

#endif
