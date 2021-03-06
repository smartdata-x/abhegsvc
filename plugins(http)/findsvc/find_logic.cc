#include "find_logic.h"
#include "find_cache_mgr.h"
#include "db_comm.h"
#include "personal_recommend.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "common.h"

namespace findsvc_logic{

Findlogic*
Findlogic::instance_=NULL;

Findlogic::Findlogic(){
   if(!Init())
      assert(0);
}

Findlogic::~Findlogic(){
	findsvc_logic::DBComm::Dest();
	findsvc_logic::CacheManagerOp::FreeCacheManagerOp();
	findsvc_logic::CacheManagerOp::FreeFindCacheManager();
	findsvc_logic::PersonalRecommend::FreeInstance();
}

bool Findlogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);

	findsvc_logic::PersonalRecommend::GetInstance();
	findsvc_logic::DBComm::Init(config->mysql_db_list_);

	findsvc_logic::CacheManagerOp::GetCacheManagerOp();
	findsvc_logic::CacheManagerOp::GetFindCacheManager();
	//读取APP商城信息
	findsvc_logic::CacheManagerOp::FetchDBFindAppStore();
	findsvc_logic::CacheManagerOp::FetchDBFindBookStore();
	findsvc_logic::CacheManagerOp::FetchDBFindGameStore();
	findsvc_logic::CacheManagerOp::FetchDBFindMoviesStore();
	findsvc_logic::CacheManagerOp::FetchDBFindMain();
    return true;
}


Findlogic*
Findlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Findlogic();

    return instance_;
}



void Findlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Findlogic::OnFindConnect(struct server *srv,const int socket){

    return true;
}



bool Findlogic::OnFindMessage(struct server *srv, const int socket, const void *msg,const int len){
	const char* packet_stream = (char*)(msg);
	std::string http_str(packet_stream,len);
	std::string error_str;
	int error_code = 0;

	LOG_MSG2("%s",packet_stream);

	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP,&http_str));


	netcomm_recv::NetBase*  value = (netcomm_recv::NetBase*)(serializer.get()->Deserialize(&error_code,&error_str));
	if(value==NULL){
		error_code = STRUCT_ERROR;
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	scoped_ptr<netcomm_recv::HeadPacket> packet(new netcomm_recv::HeadPacket(value));
	int32 type = packet->GetType();
	switch(type){
	   case FIND_STORE_APP:
		   OnFindAppStore(srv,socket,value);
		   break;
	   case FIND_STORE_BOOK:
		   OnFindBookStore(srv,socket,value);
		   break;
	   case FIND_STORE_GAME:
		   OnFindGameStoreV2(srv,socket,value);
		   break;
	   case FIND_STORE_MAIN:
		   OnFindMain(srv,socket,value);
		   break;
	   case FIND_GAME_RANK:
		   OnFindGameRank(srv,socket,value);
		   break;
	   case FIND_APP_RANK:
		   OnFindAppRank(srv,socket,value);
		   break;
	   case FIND_STORE_MOVIE:
		   OnFindMovies(srv,socket,value);
		   break;
	   case FIND_PERSONAL:
		   OnFindPersonal(srv,socket,value);
		   break;
	   case FIND_MOVIE_RANK:
		   OnFindMovieRank(srv,socket,value);
		   break;
	}

	return true;
}

bool Findlogic::OnFindClose(struct server *srv,const int socket){

    return true;
}



bool Findlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Findlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Findlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Findlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Findlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Findlogic::OnFindAppStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> findapp(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = findapp->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}


	//构造发送数据
	scoped_ptr<netcomm_send::FindAppStore> appstore(new netcomm_send::FindAppStore());

	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendFindAppInfos(appstore.get());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendAdverAppInfos(appstore.get());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendTopicsAppInfos(appstore.get());

	send_message(socket,(netcomm_send::HeadPacket*)appstore.get());
	return true;
}

bool Findlogic::OnFindBookStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
        		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> findbook(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = findbook->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}


	//构造发送数据
	scoped_ptr<netcomm_send::FindBookStore> bookstore(new netcomm_send::FindBookStore());

	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendAdverBookInfos(bookstore.get());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendFindBookInfos(bookstore.get());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendTopicsBookInfos(bookstore.get());

	send_message(socket,(netcomm_send::HeadPacket*)bookstore.get());
	return true;
}

bool Findlogic::OnFindGameStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
            		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> findbook(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = findbook->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//构造发送数据
	scoped_ptr<netcomm_send::FindGameStore> gamestore(new netcomm_send::FindGameStore());

	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendFindGameInfos(gamestore.get());

	send_message(socket,(netcomm_send::HeadPacket*)gamestore.get());
	return true;
}

//use game app
bool Findlogic::OnFindGameStoreV2(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> findbook(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = findbook->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//构造发送数据
	scoped_ptr<netcomm_send::FindGameStoreV2> gamestore(new netcomm_send::FindGameStoreV2());

	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendFindGameInfosV2(gamestore.get());

	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendAdverGameInfos(gamestore.get());

	send_message(socket,(netcomm_send::HeadPacket*)gamestore.get());
	return true;
}


bool Findlogic::OnFindMain(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
            		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> findbook(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = findbook->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//构造发送数据
	scoped_ptr<netcomm_send::FindMain> mainstore(new netcomm_send::FindMain());

	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendFindMain(mainstore.get());

	send_message(socket,(netcomm_send::HeadPacket*)mainstore.get());
	return true;
}

bool Findlogic::OnFindGameRank(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> rank(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = rank->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	//构造发送数据
		scoped_ptr<netcomm_send::FindGameRank> game_rank(new netcomm_send::FindGameRank());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendGameRank(game_rank.get());

	send_message(socket,(netcomm_send::HeadPacket*)game_rank.get());
	return true;
}

bool Findlogic::OnFindMovieRank(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::MovieRank> rank(new netcomm_recv::MovieRank(netbase));
	bool r = false;
	int error_code = rank->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	scoped_ptr<netcomm_send::MovieRank> movie_rank(new netcomm_send::MovieRank());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendMovieRank(rank->category(),movie_rank.get());
	send_message(socket,(netcomm_send::HeadPacket*)movie_rank.get());
	return true;
}

bool Findlogic::OnFindAppRank(struct server *srv,const int socket, netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> rank(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = rank->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	//构造发送数据
	scoped_ptr<netcomm_send::FindAppRank> app_rank(new netcomm_send::FindAppRank());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendAppRank(app_rank.get());
	send_message(socket,(netcomm_send::HeadPacket*)app_rank.get());
	return true;
}

bool Findlogic::OnFindMovies(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> movies(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = movies->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//构造发送数据
	scoped_ptr<netcomm_send::FindMovies> movies_rank(new netcomm_send::FindMovies());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendAdverMoviesInfos(movies_rank.get());
	findsvc_logic::CacheManagerOp::GetFindCacheManager()->SendFindMoviesInfos(movies_rank.get());
	send_message(socket,(netcomm_send::HeadPacket*)movies_rank.get());
	return true;
}

bool Findlogic::OnFindPersonal(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindPersonal> find(new netcomm_recv::FindPersonal(netbase));
	bool r = false;
	int error_code = find->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	switch(find->category()){
	case 1:
		/*r = FindPersonalT<base_logic::AppInfos>(find->uid(),findsvc_logic::DBComm::GetPersonalApp,
			result->set_app_list);*/
		r = FindPersonalT<base_logic::AppInfos>(find->uid(),socket,find->category(),
				findsvc_logic::DBComm::GetPersonalApp);
		break;

	case 2:
		r = FindPersonalT<base_logic::AppInfos>(find->uid(),socket,find->category(),
						findsvc_logic::DBComm::GetPersonalGame);
		/*
		r = FindPersonalT<base_logic::AppInfos>(find->uid(),findsvc_logic::DBComm::GetPersonalGame,
				result->set_game_list);*/
		break;
	case 3:
		r = FindPersonalT<base_logic::BookInfo>(find->uid(),socket,find->category(),
						findsvc_logic::DBComm::GetPersonalBook);
		/*
		r = FindPersonalT<base_logic::BookInfo>(find->uid(),findsvc_logic::DBComm::GetPersonalBook,
				result->set_book_list);*/
		break;
	case 4:
		r = FindPersonalT<base_logic::Movies>(find->uid(),socket,find->category(),
						findsvc_logic::DBComm::GetPersonalMovie);
		/*
		r = FindPersonalT<base_logic::Movies>(find->uid(),findsvc_logic::DBComm::GetPersonalMovie,
				result->set_movie_list);*/
		break;
	default:
		break;
	}

	//send_message(socket,(netcomm_send::HeadPacket*)result.get());
	return true;
}


template <typename ELEMENT>
bool  Findlogic::FindPersonalT(const int64 uid,const int socket,int32 type,
 		bool (*db_get)(const int64,std::list<ELEMENT>&)){
	bool r = false;
	scoped_ptr<netcomm_send::FindPersonal> result(new netcomm_send::FindPersonal());
	std::list<ELEMENT> list;
	r = db_get(uid,list);
	if(!r||list.size()<=0)
		return false;
	while(list.size()>0){
		ELEMENT info = list.front();
		list.pop_front();
		if(type==1)
			result->set_app_list(info.Release());
		else if(type==2)
			result->set_game_list(info.Release());
		else if(type==3)
			result->set_book_list(info.Release());
		else if(type==4)
			result->set_movie_list(info.Release());
	}
	result->set_category(type);
	send_message(socket,(netcomm_send::HeadPacket*)result.get());
	return true;
}
/*
template <typename ELEMENT>
bool  Findlogic::FindPersonalT(const int64 uid,
    		bool (*db_get)(const int64,std::list<ELEMENT>&),
    		void (*set_info)(base_logic::DictionaryValue*)){
	bool r = false;
	std::list<ELEMENT> list;
	r = db_get(uid,list);
	if(!r||list.size()<=0)
		return false;
	while(list.size()>0){
		ELEMENT info = list.front();
		list.pop_front();
		//set_info(info.Release());
	}
	return true;
}*/

}

