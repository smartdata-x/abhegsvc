#ifndef __ABHEG__FINDSVC__FIND_LOGIC___
#define __ABHEG__FINDSVC__FIND_LOGIC___
#include "net/find_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/findsvc/findsvc_config.xml"
namespace findsvc_logic{

class Findlogic{

public:
    Findlogic();
    virtual ~Findlogic();

private:
    static Findlogic    *instance_;

public:
    static Findlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnFindConnect (struct server *srv,const int socket);

    bool OnFindMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnFindClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    bool OnFindAppStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnFindBookStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
        		const void* msg = NULL,const int len = 0);

    bool OnFindGameStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
            		const void* msg = NULL,const int len = 0);

    bool OnFindGameStoreV2(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnFindMain(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
                		const void* msg = NULL,const int len = 0);

    bool OnFindGameRank(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnFindAppRank(struct server *srv,const int socket, netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnFindMovies(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnFindPersonal(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnFindMovieRank(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

private:
    /*
    template <typename ELEMENT>
    bool FindPersonalT(const int64 uid,
    		bool (*db_get)(const int64,std::list<ELEMENT>&),
    		void (*set_info)(base_logic::DictionaryValue*));*/

    template <typename ELEMENT>
    bool FindPersonalT(const int64 uid,const int socket,int32 type,
    		bool (*db_get)(const int64,std::list<ELEMENT>&));

    bool Init();

};


}

#endif

