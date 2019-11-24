#ifndef __MESSAGE__
#define __MESSAGE__

#include <vector>

class scenario;

typedef enum {
    E_Message_Literal,
    E_Message_Remote_IP,
    E_Message_Remote_Host,
    E_Message_Remote_Port,
    E_Message_Transport,
    E_Message_Local_IP,
    E_Message_Local_IP_Type,
    E_Message_Local_Port,
    E_Message_Server_IP,
    E_Message_Media_IP,
    E_Message_Auto_Media_Port,
    E_Message_Media_Port,
    E_Message_Media_IP_Type,
    E_Message_Call_Number,
    E_Message_DynamicId,   // general usage, global, autoincrementing and wrapping counter
    E_Message_Call_ID,
    E_Message_CSEQ,
    E_Message_PID,
    E_Message_Service,
    E_Message_Branch,
    E_Message_Index,
    E_Message_Next_Url,
    E_Message_Len,
    E_Message_Peer_Tag_Param,
    E_Message_Routes,
    E_Message_Variable,
    E_Message_Fill,
    E_Message_Injection,
    E_Message_Last_Header,
    E_Message_Last_Request_URI,
    E_Message_Last_CSeq_Number,
    E_Message_Last_Message,
    E_Message_TDM_Map,
    E_Message_Authentication,
    E_Message_ClockTick,
    E_Message_Users,
    E_Message_UserID,
    E_Message_Timestamp,
    E_Message_SippVersion,
    E_Message_File,
    E_Message_Custom,
#ifdef RTP_STREAM
  E_Message_RTPStream_Audio_Port,
  E_Message_RTPStream_Video_Port,
#endif
} MessageCompType;

class SendingMessage
{
public:
    SendingMessage(scenario *msg_scenario, char *msg, bool skip_sanity = false);
private:
};

#endif

