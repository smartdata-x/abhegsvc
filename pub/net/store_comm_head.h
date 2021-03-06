/*
 * store_cmm_head.h
 *
 *  Created on: 2015年1月25日
 *      Author: kerry
 */

#ifndef _NET_STORE_CMM_HEAD_H_
#define _NET_STORE_CMM_HEAD_H_


#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

//关键字搜索
class AppSearchKey:public LoginHeadPacket{
public:
	AppSearchKey(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		//URLCODE 解码
		std::string key;
		r = m_->GetString(L"key",&key);
		if(r){
			base::BasicUtil::UrlDecode(key,key_);
		}
		if(!r) error_code_ = SEARCH_KEY_LACK;

		GETBIGINTTOINT(L"from",from_);
		if(!r) from_ = 0;

		GETBIGINTTOINT(L"count",count_);
		if(!r) count_ = 10;
	}

	//const int64 tid() const {return this->tid_;}
	const std::string& key() const {return  this->key_;}
	const int64 from() const {return this->from_;}
	const int64 count() const {return this->count_;}
private:
	std::string                  key_;
	int64                        from_;
	int64                        count_;
};

//类别搜索
class AppSearchType:public LoginHeadPacket{
public:
	AppSearchType(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"tid",tid_);
		if(!r) error_code_ = STORE_SEACH_BTYPE_LACK;

		GETBIGINTTOINT(L"from",from_);
		if(!r) from_ = 0;

		GETBIGINTTOINT(L"count",count_);
		if(!r) count_ = 10;
	}

	const int64 tid() const {return this->tid_;}
	const int64 from() const {return this->from_;}
	const int64 count() const {return this->count_;}

private:
	int64       tid_;
	int64       from_;
	int64       count_;
};


//用于商场 游戏 书城 详情
class AppSummary:public LoginHeadPacket{
public:
	AppSummary(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"appid",appid_);
		if(!r) error_code_ = APPID_LACK;
	}

	const int64 appid() const {return this->appid_;}
private:
	int64       appid_;
};

typedef AppSummary  LikePraise;

//获取地址
class WantAppUrl:public LoginHeadPacket{
public:
	WantAppUrl(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"appid",appid_);
		if(!r) error_code_ = APPID_LACK;
		GETBIGINTTOINT(L"machine",machine_);
		if(!r)machine_ = 0;
	}

	const int64 appid() const {return this->appid_;}

	const int32 machine() const {return this->machine_;}
private:
	int64       appid_;
	int32       machine_;
};

//专题获取
class AppTopics:public LoginHeadPacket{
public:
	AppTopics(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"tid",topics_);
		if(!r) error_code_ = APPID_LACK;
	}

	const int64 topics() const {return this->topics_;}

private:
	int64       topics_;
};



class GameStrategyCatalog:public LoginHeadPacket{
public:
	GameStrategyCatalog(NetBase* m)
	 :LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"gameid",game_id_);
		if(!r) error_code_ = APPID_LACK;

		GETBIGINTTOINT(L"from",from_);
		if(!r) from_ = 0;

		GETBIGINTTOINT(L"count",count_);
		if(!r) count_ = 10;
	}

	const int64 game_id() const {return this->game_id_;}

	const int64 from() const {return this->from_;}

	const int64 count() const {return this->count_;}

private:
	int64   game_id_;
	int64   from_;
	int64   count_;
};

class GameStrategyDetails:public LoginHeadPacket{
public:
	GameStrategyDetails(NetBase* m)
	 :LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"strategyid",strategy_id_);
		if(!r) error_code_ = APPID_LACK;

	}

	const int64 strategy_id() const {return this->strategy_id_;}

private:
	int64   strategy_id_;
};

class ShakStore:public LoginHeadPacket{
public:
	ShakStore(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void Init(){
		bool r = false;
		r = m_->GetReal(L"latitude",&latitude_);
		r = m_->GetReal(L"longitude",&longitude_);
	}


	const double latitude() const {return this->latitude_;}
	const double longitude() const {return this->longitude_;}

private:
	double latitude_;
	double longitude_;
};

}

namespace netcomm_send{

class AppSummary:public HeadPacket{
public:
	AppSummary(){
		base_.reset(new netcomm_send::NetBase());
		pic_.reset(new base_logic::ListValue());
		like_.reset(new base_logic::ListValue());
		intro_.reset(new base_logic::DictionaryValue());
		islike_.reset(new base_logic::FundamentalValue(0));
	}

	netcomm_send::NetBase* release(){
		if(!pic_->empty())
			this->intro_->Set(L"pic",pic_.release());
		if(!like_->empty())
			this->base_->Set(L"like",like_.release());
		if(!intro_->empty())
			this->base_->Set(L"intro",intro_.release());
		this->base_->Set(L"islike",islike_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}


	inline void set_intro(base_logic::DictionaryValue* app){
		intro_.reset(app);
	}

	inline void set_like(base_logic::DictionaryValue* app){
		like_->Append(app);
	}

	inline void set_islike(const int32 islike){
		islike_.reset(new base_logic::FundamentalValue(islike));
	}

	inline void set_pic(const std::string& pic){
		pic_->Append(base_logic::Value::CreateStringValue(pic));
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       intro_;
	scoped_ptr<base_logic::FundamentalValue>      islike_;
	scoped_ptr<base_logic::ListValue>             like_;
	scoped_ptr<base_logic::ListValue>             pic_;
};

//专题获取
class AppTopics:public HeadPacket{
public:
	AppTopics(){
		base_.reset(new netcomm_send::NetBase());
		topics_.reset(new base_logic::ListValue());
		like_num_.reset(new base_logic::FundamentalValue(0));
	}
	netcomm_send::NetBase* release(){
		if(!topics_->empty())
			this->base_->Set(L"topics",topics_.release());

		this->base_->Set(L"likenum",like_num_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_topics(base_logic::DictionaryValue* app){
		topics_->Append(app);
	}

	inline void set_like(const int64 like){
		like_num_.reset(new base_logic::FundamentalValue(like));
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             topics_;
	scoped_ptr<base_logic::FundamentalValue>      like_num_;
};

//下载地址
class WantAppUrl:public HeadPacket{
public:
	WantAppUrl(){
		base_.reset(new netcomm_send::NetBase());
		basic_.reset(new base_logic::DictionaryValue());
	}

	netcomm_send::NetBase* release(){
		if(!basic_->empty())
			this->base_->Set(L"basic",basic_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_url(const std::string& url){
		basic_->SetString(L"url",url);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       basic_;
};

//搜索结果返回
class AppSearchResult:public HeadPacket{
public:
	AppSearchResult(){
		base_.reset(new netcomm_send::NetBase());
		hot_list_.reset(new base_logic::ListValue());
		new_list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!new_list_->empty())
			this->base_->Set(L"new",new_list_.release());
		if(!hot_list_->empty())
			this->base_->Set(L"hot",hot_list_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_new_list(base_logic::DictionaryValue* app){
		new_list_->Append(app);
	}

	inline void set_hot_list(base_logic::DictionaryValue* app){
		hot_list_->Append(app);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             hot_list_;
	scoped_ptr<base_logic::ListValue>             new_list_;

};

class AppSharkResult:public HeadPacket{
public:
	AppSharkResult(){
		base_.reset(new netcomm_send::NetBase());
		list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!list_->empty())
			this->base_->Set(L"list",list_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_list(base_logic::DictionaryValue* app){
		list_->Append(app);
	}


private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             list_;

};

class GameStrategyCatalog:public HeadPacket{
public:
	GameStrategyCatalog(){
		base_.reset(new netcomm_send::NetBase());
		list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!list_->empty())
			this->base_->Set(L"list",list_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_list(base_logic::DictionaryValue* catalog){
		list_->Append(catalog);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             list_;
};


class GameStrategyDetail:public HeadPacket{
public:
	GameStrategyDetail(){
		base_.reset(new netcomm_send::NetBase());
	}

	netcomm_send::NetBase* release(){
		this->base_->Set(L"detail",detail_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_detail(const std::string& detail){
		detail_.reset(new  base_logic::StringValue(detail));
	}

private:
	scoped_ptr<netcomm_send::NetBase>               base_;
	scoped_ptr<base_logic::StringValue>             detail_;
};

}


#endif /* STORE_CMM_HEAD_H_ */
