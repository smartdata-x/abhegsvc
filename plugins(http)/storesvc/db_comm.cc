/*
 * db_comm.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#include "db_comm.h"
#include "db/base_db_mysql_auto.h"
#include <sstream>
#include <mysql.h>

namespace storesvc_logic{

void DBComm::Init(std::list<base::ConnAddr>& addrlist){
#if defined (_DB_POOL_)
	base_db::MysqlDBPool::Init(addrlist);
#endif
}

void DBComm::Dest(){
#if defined (_DB_POOL_)
	base_db::MysqlDBPool::Dest();
#endif
}

bool DBComm::GetAppPicList(const int64 appid,const int32 tclass,base_logic::AppInfos& appinfo){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

	int64 tempid = 10000013;

    //call proc_GetAppPicList(20000024,0,1)
	os<<"call proc_GetAppPicList("<<tempid<<",0"<<","<<tclass<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			if(rows[0]!=NULL)
				appinfo.set_summary_pic(rows[0]);
		}
		return true;
	}
	return false;
}
bool DBComm::GetAppSummary(const int64 appid,const int32 tclass,base_logic::AppInfos& appinfo){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call proc_GetAppSummary(1)
	os<<"call proc_GetAppSummary("<<appid<<","<<tclass<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			if(rows[0]!=NULL)
				appinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atol(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_down(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_like(atoll(rows[5]));
			if(rows[6]!=NULL)
				appinfo.set_size(atof(rows[6]));
			if(rows[7]!=NULL)
				appinfo.set_version(rows[7]);
			if(rows[8]!=NULL)
				appinfo.set_ontime(rows[8]);
			if(rows[9]!=NULL)
				appinfo.set_lang(atol(rows[9]));
			if(rows[10]!=NULL)
				appinfo.set_provider(rows[10]);
			if(rows[11]!=NULL)
				appinfo.set_content(rows[11]);
		}
		return true;
	}
	return false;
}

bool DBComm::GetTopics(const int64 tid,std::list<base_logic::AppInfos>& list){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call abheg.proc_GetTopicsAppElement(1)
	os<<"call proc_GetTopicsAppElement("<<1<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			base_logic::AppInfos appinfo;
			if(rows[0]!=NULL)
				appinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_like(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_down(atoll(rows[5]));
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::SearchKeyApp(const std::string& key,std::list<base_logic::AppInfos>& list,
		const int64 from,const int64 count){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call abheg.proc_SearchAppByKey('二',0,1)
	os<<"call proc_SearchAppByKey(\'"<<key<<"\',"<<from<<","<<count<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			base_logic::AppInfos appinfo;
			if(rows[0]!=NULL)
				appinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_like(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_down(atoll(rows[5]));
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);
			if(rows[7]!=NULL)
				appinfo.set_attr(atol(rows[7]));

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}


bool DBComm::SearchTypeApp(const int32 type,const int32 tclass,std::list<base_logic::AppInfos>& list,
		const int64 from,const int64 count){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call abheg.proc_SearchAppType(2001,2,0,10)
	os<<"call proc_SearchAppType("<<type<<","<<tclass<<","<<from<<","<<count<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			base_logic::AppInfos appinfo;
			if(rows[0]!=NULL)
				appinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_like(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_down(atoll(rows[5]));
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::ShakAppInfo(const double latitude,const double longtiude,std::list<base_logic::AppInfos>& list){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call abheg.proc_ShakAppInfo(0,0)
	os<<"call proc_ShakAppInfo("<<latitude<<","<<longtiude<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			base_logic::AppInfos appinfo;
			if(rows[0]!=NULL)
				appinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_like(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_down(atoll(rows[5]));
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::GetWantUrl(const int64 appid,const int32 tclass,const int32 machine,
			std::string& url){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call proc_WantAppURL(27,2,1)
	os<<"call proc_WantAppURL("<<appid<<","<<tclass<<","<<machine<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			if(rows[0]!=NULL)
				url = rows[0];
		}
		return true;
	}
	return false;
}

bool DBComm::WantAppLike(const int64 uid,const int64 appid,const int32 tclass){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call proc_AppLikePraise(10008,13,1)
	os<<"call proc_AppLikePraise("<<uid<<","<<appid<<","<<tclass<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}
	return true;
}

bool DBComm::GetGameStrategyCatalog(const int64 gameid,const int64 from,const int64 count,
		std::list<storesvc_logic::GameStrategy>& list){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call abheg.proc_GetGameStrategyCatalog(20000024,10,10)
	os<<"call proc_GetGameStrategyCatalog("<<gameid<<","<<from<<","<<count<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}

	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			storesvc_logic::GameStrategy strategy;
			if(rows[0]!=NULL)
				strategy.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				strategy.set_name(rows[1]);
			if(rows[2]!=NULL)
				strategy.set_address(rows[2]);
			list.push_back(strategy);
		}
		return true;
	}
	return false;
}

bool DBComm::GetGameStrategyDetail(const int64 strategy_id,storesvc_logic::GameStrategy& strategy){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call abheg.proc_GetGameStrategyDetails(12)
	os<<"call proc_GetGameStrategyDetails("<<strategy_id<<");";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}

	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			if(rows[0]!=NULL)
				strategy.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				strategy.set_gameid(atoll(rows[1]));
			if(rows[2]!=NULL)
				strategy.set_details(rows[2]);
		}
		return true;
	}
	return false;
}

}
