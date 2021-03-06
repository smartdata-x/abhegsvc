#include "book_logic.h"
#include "db_comm.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "common.h"

namespace booksvc_logic{

Booklogic*
Booklogic::instance_=NULL;

Booklogic::Booklogic(){
   if(!Init())
      assert(0);
}

Booklogic::~Booklogic(){
	booksvc_logic::DBComm::Dest();
}

bool Booklogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);

	booksvc_logic::DBComm::Init(config->mysql_db_list_);
    return true;
}

Booklogic*
Booklogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Booklogic();

    return instance_;
}



void Booklogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Booklogic::OnBookConnect(struct server *srv,const int socket){

    return true;
}



bool Booklogic::OnBookMessage(struct server *srv, const int socket, const void *msg,const int len){
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
		   case BOOK_TOPICS:
			   OnBookTopics(srv,socket,value);
			   break;
		   case BOOK_SEARCH:
			   OnBookSearchType(srv,socket,value);
			   break;
		   case BOOK_WANT:
			   OnWantGetBook(srv,socket,value);
			   break;
		   case BOOK_LIST:
			   OnUserBookList(srv,socket,value);
			   break;
		   case CHAPTER_LIST:
			   OnGetBookChapters(srv,socket,value);
			   break;
		   case BOOK_SUMMARY:
			 //  OnGetBookSummary(srv,socket,value);
			   //break;
		   case BOOK_COMP_INFO:
			   OnGetBookComplInfo(srv,socket,value);
			   break;
		   case BOOK_SEARCH_KEY:
			   OnBookSearchKey(srv,socket,value);
			   break;
		   case BOOK_HOT_WORD:
			   OnGetHotWordList(srv,socket,value);
			   break;

		}
    return true;
}

bool Booklogic::OnBookClose(struct server *srv,const int socket){

    return true;
}



bool Booklogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Booklogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Booklogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Booklogic::OnIniTimer(struct server *srv){

    return true;
}



bool Booklogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Booklogic::OnBookTopics(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
   		const void* msg,const int){
	scoped_ptr<netcomm_recv::BookTopics> topics(new netcomm_recv::BookTopics(netbase));
	bool r = false;
	int error_code = topics->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<base_logic::BookInfo> list;
	scoped_ptr<netcomm_send::BookTopics> booktopics(new netcomm_send::BookTopics());
	booksvc_logic::DBComm::GetBookTopics(topics->topics(),list);

	while(list.size()>0){
		base_logic::BookInfo bookinfo = list.front();
		list.pop_front();
		booktopics->set_topics(bookinfo.Release());
	}

	//获取题目和关注人数
	booktopics->set_name("豆瓣读物");
	booktopics->set_follow(512);
	send_message(socket,(netcomm_send::HeadPacket*)booktopics.get());
	return true;
}

bool Booklogic::OnBookSearchKey(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::SearchKey> search(new netcomm_recv::SearchKey(netbase));
	bool r = false;
	int error_code = search->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<base_logic::BookInfo> list;
	scoped_ptr<netcomm_send::SearchType> searchtype(new netcomm_send::SearchType());
	booksvc_logic::DBComm::GetBookSearch(search->key(),0,10,list);
	while(list.size()>0){
		base_logic::BookInfo bookinfo = list.front();
		list.pop_front();
		if(bookinfo.attr()==1)
			searchtype->SetHotBookInfo(bookinfo.Release());
		else if(bookinfo.attr()==2)
			searchtype->SetNewBookInfo(bookinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)searchtype.get());
	return true;
}

bool Booklogic::OnBookSearchType(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
       		const void* msg,const int len){
	scoped_ptr<netcomm_recv::SearchType> search(new netcomm_recv::SearchType(netbase));
	bool r = false;
	int error_code = search->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<base_logic::BookInfo> list;
	scoped_ptr<netcomm_send::SearchType> searchtype(new netcomm_send::SearchType());
	booksvc_logic::DBComm::GetBookSearch(search->btype(),list);
	while(list.size()>0){
		base_logic::BookInfo bookinfo = list.front();
		list.pop_front();
		if(bookinfo.attr()==1)
			searchtype->SetHotBookInfo(bookinfo.Release());
		else if(bookinfo.attr()==2)
			searchtype->SetNewBookInfo(bookinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)searchtype.get());
	return true;
}


bool Booklogic::OnWantGetBook(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::WantBook> book(new netcomm_recv::WantBook(netbase));
	int error_code = book->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	bool r = false;
	int32 status = 0;
	std::string booktoken;
	base_logic::LogicUnit::CreateToken(book->uid(),booktoken);
	//
	r = booksvc_logic::DBComm::OnWantGetBook(book->uid(),book->bookid(),booktoken);
	scoped_ptr<netcomm_send::WantBook> send_book(new netcomm_send::WantBook());
	send_book->SetBookToken(booktoken);
	send_message(socket,(netcomm_send::HeadPacket*)send_book.get());
	return true;
}

bool Booklogic::OnUserBookList(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
      		const void* msg,const int len){
	scoped_ptr<netcomm_recv::BookList> booklist(new netcomm_recv::BookList(netbase));
	bool r = false;
	int32 issave;
	std::string token;
	std::list<base_logic::BookInfo> list;
	int error_code = booklist->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//查询书单
	r = booksvc_logic::DBComm::OnGetBookList(booklist->uid(),list);
	scoped_ptr<netcomm_send::BookList> bookl(new netcomm_send::BookList());
	while(list.size()>0){
		base_logic::BookInfo bookinfo = list.front();
		list.pop_front();
		bookl->SetBookList(bookinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)bookl.get());
	return true;
}

bool Booklogic::OnGetBookChapters(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
       		const void* msg,const int len){
	scoped_ptr<netcomm_recv::ChapterList> chapterlist(new netcomm_recv::ChapterList(netbase));
	bool r = false;
	int error_code = chapterlist->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<booksvc_logic::ChapterInfo> list;
	//查询书单
	r = booksvc_logic::DBComm::OnGetBookChapters(chapterlist->uid(),
			chapterlist->bookid(),chapterlist->booktoken(),
			chapterlist->from(),chapterlist->count(),list);

	scoped_ptr<netcomm_send::ChapterList> bookl(new netcomm_send::ChapterList());
	while(list.size()>0){
		booksvc_logic::ChapterInfo chapterinfo = list.front();
		list.pop_front();
		bookl->SetBookList(chapterinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)bookl.get());
	return true;
}

bool Booklogic::OnGetBookComplInfo(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::BookComInfo> comminfo(new netcomm_recv::BookComInfo(netbase));
	bool r = false;
	int error_code = comminfo->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//获取单本书籍完整信息
	base_logic::BookInfo bookinfo;
	int32 issave = 0;
	r = booksvc_logic::DBComm::OnGetBookComInfo(comminfo->bookid(),bookinfo);
	scoped_ptr<netcomm_send::BookCompInfo> bookl(new netcomm_send::BookCompInfo());
	bookl->set_summary(bookinfo.Release());
	//
	bookl->set_user(issave);
	bookl->set_label("临时数据1");
	bookl->set_label("临时数据2");
	send_message(socket,(netcomm_send::HeadPacket*)bookl.get());
}

bool Booklogic::OnGetBookSummary(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
   		const void* msg,const int len ){
	scoped_ptr<netcomm_recv::BookSummary> summary(new netcomm_recv::BookSummary(netbase));
	bool r = false;
	int error_code = summary->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}


	//查询书单
	base_logic::BookInfo bookinfo;
	int32 issave = 0;
	r = booksvc_logic::DBComm::OnGetBookSummary(summary->uid(),
			summary->bookid(),issave,bookinfo);

	scoped_ptr<netcomm_send::BookSummary> bookl(new netcomm_send::BookSummary());
	bookl->set_summary(bookinfo.Release());
	//
	bookl->set_user(issave);
	bookl->set_label("临时数据1");
	bookl->set_label("临时数据2");
	send_message(socket,(netcomm_send::HeadPacket*)bookl.get());
	return true;
}

bool Booklogic::OnGetHotWordList(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::HotWord> hot(new netcomm_recv::HotWord(netbase));
	bool r = false;
	int error_code =hot->GetResult();
	if(error_code!=0){
		send_error(error_code,socket);
		return false;
	}

	//获取热词单
	scoped_ptr<netcomm_send::HotWord> hotword(new netcomm_send::HotWord());
	std::list<booksvc_logic::HotWord> list;
	booksvc_logic::DBComm::OnGetHotWork(list);
	while(list.size()>0){
		booksvc_logic::HotWord word = list.front();
		list.pop_front();
		hotword->SetHotWordList(word.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)hotword.get());
	return true;
}


}

