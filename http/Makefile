
###############################################################################
## 编译器
COMPILER = g++
COMPILERC = gcc

## 编译选项
## for debug -DROOM_DEBUG_MCACHE
CPP_FLAG = -g -Wall -w -fPIC -c -D_LINUX -DDEBUG -D_DEBUG -D_REENTRANT -D_GNU_SOURCE -D__DEBUG_CORE__ -DFCGI_STD  #-DCHECK_HEADER-DTEST
RCPP_FLAG = -g -Wall -w -fPIC -c -D_LINUX -DDEBUG -D_DEBUG -D_REENTRANT -D_GNU_SOURCE -DFCGI_STD #-DTEST
## for release
##CPP_FLAG = -O3 -Wall -s -w -fPIC -c -D_LINUX -DNDEBUG -D_REENTRANT -D_GNU_SOURCE -DFCGI_STD

## 链接选项
## for debug
LINK_FLAGS = -g  -fPIC
## for release
## LINK_FLAGS = -s -O3 -shared -fPIC

LIB_DIR = ./../../library
BASE_DIR = ./../pub
## 头文件
INCLUDE_PATHS = -I$(LIB_DIR)/public/ -I /usr/local/libmemcached-1.0.7/include\
		-I/usr/local/lib -I$(LIB_DIR)/third_party/hiredis -I$(BASE_DIR)/\
		-I$(LIB_DIR)/third_party/breakpad/src

## 库
LINK_PATHS =  -L/usr/local/libmemcached-1.0.7/lib/ -L/usr/lib64/mysql
LINK_LIBRARYS = -lmemcached -lmemcachedutil -lrt -lpthread  -liconv -lfcgi++ -lmysqlclient -lexpat -lcurl\
					./../lib/libbreakpad_client.a ./../lib/libhiredis.a $(LINK_CORE_PATH)

# 编译
COMPILE = $(COMPILER) $(CPP_FLAG) $(INCLUDE_PATHS) -o $@
RCOMPILE = $(COMPILER) $(RCPP_FLAG) $(INCLUDE_PATHS) -o $@

# 链接
LINK = $(COMPILER) $(LINK_FLAGS) $(LINK_PATHS) $? -o $(OUTPUT_FILE) $(LINK_LIBRARYS)
LINKALL = $(COMPILER) $(LINK_FLAGS) $(LINK_PATHS) $?  $(LINK_LIBRARYS)











POBJ =  mig_log.o core_interface.o http_formate.o
OUTPUT_FILE = /var/www/cgi-bin/abheg
#############################################################################################################################
all: clean proc delete-temp-file

proc: otherproc userproc findproc bookproc musicproc robotproc storeproc payproc movieporc hackproc beaconproc gameboxproc

######################movieproc###############################################
MOVIENAME = movie_
MOVIEPROC_PATH = /movie
MOVIE_OBJECT_PATH = ./obj$(MOVIEPROC_PATH)
OTJERPROC_VERSION = /v1
movieporc:$(MOVIEPROC_PATH)/summary.fcgi $(MOVIEPROC_PATH)/like.fcgi $(MOVIEPROC_PATH)/searchtype.fcgi

$(MOVIEPROC_PATH)/summary.fcgi: $(MOVIE_OBJECT_PATH)/$(MOVIENAME)summary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MOVIEPROC_PATH)$(OTJERPROC_VERSION)/summary.fcgi

$(MOVIEPROC_PATH)/like.fcgi: $(MOVIE_OBJECT_PATH)/$(MOVIENAME)like.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MOVIEPROC_PATH)$(OTJERPROC_VERSION)/like.fcgi
	
$(MOVIEPROC_PATH)/searchtype.fcgi: $(MOVIE_OBJECT_PATH)/$(MOVIENAME)searchtype.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MOVIEPROC_PATH)$(OTJERPROC_VERSION)/searchtype.fcgi
### 编译

$(MOVIE_OBJECT_PATH)/$(MOVIENAME)summary.o:
	$(COMPILE) .$(MOVIEPROC_PATH)$(OTJERPROC_VERSION)/summary/summary.cc

$(MOVIE_OBJECT_PATH)/$(MOVIENAME)like.o:
	$(COMPILE) .$(MOVIEPROC_PATH)$(OTJERPROC_VERSION)/like/like.cc

$(MOVIE_OBJECT_PATH)/$(MOVIENAME)searchtype.o:
	$(COMPILE) .$(MOVIEPROC_PATH)$(OTJERPROC_VERSION)/searchtype/searchtype.cc

######################payproc###############################################
PAYNAME = pay_
PAYPROC_PATH = /pay
PAY_OBJECT_PATH = ./obj$(PAYPROC_PATH)
OTJERPROC_VERSION = /v1
payproc:$(PAYPROC_PATH)/register.fcgi $(PAYPROC_PATH)/login.fcgi $(PAYPROC_PATH)/update.fcgi $(PAYPROC_PATH)/getchr.fcgi

$(PAYPROC_PATH)/register.fcgi: $(PAY_OBJECT_PATH)/$(PAYNAME)register.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(PAYPROC_PATH)$(OTJERPROC_VERSION)/register.fcgi
	
$(PAYPROC_PATH)/login.fcgi: $(PAY_OBJECT_PATH)/$(PAYNAME)login.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(PAYPROC_PATH)$(OTJERPROC_VERSION)/login.fcgi
	
$(PAYPROC_PATH)/update.fcgi: $(PAY_OBJECT_PATH)/$(PAYNAME)update.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(PAYPROC_PATH)$(OTJERPROC_VERSION)/update.fcgi
	
$(PAYPROC_PATH)/getchr.fcgi: $(PAY_OBJECT_PATH)/$(PAYNAME)getchr.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(PAYPROC_PATH)$(OTJERPROC_VERSION)/getchr.fcgi

### 编译

$(PAY_OBJECT_PATH)/$(PAYNAME)register.o:
	$(COMPILE) .$(PAYPROC_PATH)$(OTJERPROC_VERSION)/register/register.cc

$(PAY_OBJECT_PATH)/$(PAYNAME)login.o:
	$(COMPILE) .$(PAYPROC_PATH)$(OTJERPROC_VERSION)/login/login.cc
	
$(PAY_OBJECT_PATH)/$(PAYNAME)update.o:
	$(COMPILE) .$(PAYPROC_PATH)$(OTJERPROC_VERSION)/update/update.cc
	
$(PAY_OBJECT_PATH)/$(PAYNAME)getchr.o:
	$(COMPILE) .$(PAYPROC_PATH)$(OTJERPROC_VERSION)/getchr/getchr.cc
	
######################musicproc###############################################
MUSICNAME = music_
MUSICPROC_PATH = /music
MUSIC_OBJECT_PATH = ./obj$(MUSICPROC_PATH)
OTJERPROC_VERSION = /v1
musicproc:$(MUSICPROC_PATH)/getcltsongs.fcgi $(MUSICPROC_PATH)/getdimension.fcgi $(MUSICPROC_PATH)/collectsong.fcgi $(MUSICPROC_PATH)/delcltsong.fcgi

$(MUSICPROC_PATH)/getcltsongs.fcgi: $(MUSIC_OBJECT_PATH)/$(MUSICNAME)getcltsongs.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getcltsongs.fcgi

$(MUSICPROC_PATH)/getdimension.fcgi: $(MUSIC_OBJECT_PATH)/$(MUSICNAME)getdimension.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getdimension.fcgi

$(MUSICPROC_PATH)/collectsong.fcgi: $(MUSIC_OBJECT_PATH)/$(MUSICNAME)collectsong.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/collectsong.fcgi
	
$(MUSICPROC_PATH)/delcltsong.fcgi: $(MUSIC_OBJECT_PATH)/$(MUSICNAME)delcltsong.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/delcltsong.fcgi
### 编译

$(MUSIC_OBJECT_PATH)/$(MUSICNAME)getcltsongs.o:
	$(COMPILE) .$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getcltsongs/getcltsongs.cc

$(MUSIC_OBJECT_PATH)/$(MUSICNAME)getdimension.o:
	$(COMPILE) .$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/getdimension/getdimension.cc

$(MUSIC_OBJECT_PATH)/$(MUSICNAME)collectsong.o:
	$(COMPILE) .$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/collectsong/collectsong.cc

$(MUSIC_OBJECT_PATH)/$(MUSICNAME)delcltsong.o:
	$(COMPILE) .$(MUSICPROC_PATH)$(OTJERPROC_VERSION)/delcltsong/delcltsong.cc
	
######################gameboxproc###############################################
GAMEBOXNAME = gamebox_
GAMEBOXPROC_PATH = /gamebox
GAMEBOX_OBJECT_PATH = ./obj$(GAMEBOXPROC_PATH)
OTJERPROC_VERSION = /v1
gameboxproc:$(GAMEBOXPROC_PATH)/checkgame.fcgi $(GAMEBOXPROC_PATH)/shark.fcgi

$(GAMEBOXPROC_PATH)/checkgame.fcgi: $(GAMEBOX_OBJECT_PATH)/$(GAMEBOXNAME)checkgame.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(GAMEBOXPROC_PATH)$(OTJERPROC_VERSION)/checkgame.fcgi

$(GAMEBOXPROC_PATH)/shark.fcgi: $(GAMEBOX_OBJECT_PATH)/$(GAMEBOXNAME)shark.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(GAMEBOXPROC_PATH)$(OTJERPROC_VERSION)/shark.fcgi
	
### 编译
$(GAMEBOX_OBJECT_PATH)/$(GAMEBOXNAME)checkgame.o:
	$(COMPILE) .$(GAMEBOXPROC_PATH)$(OTJERPROC_VERSION)/checkgame/checkgame.cc
	
$(GAMEBOX_OBJECT_PATH)/$(GAMEBOXNAME)shark.o:
	$(COMPILE) .$(GAMEBOXPROC_PATH)$(OTJERPROC_VERSION)/shark/shark.cc


######################hackproc###############################################
HACKNAME = hack_
HACKPROC_PATH = /hack
HACK_OBJECT_PATH = ./obj$(HACKPROC_PATH)
OTJERPROC_VERSION = /v1
hackproc:$(HACKPROC_PATH)/wdjsummary.fcgi $(HACKPROC_PATH)/snssdk.fcgi $(HACKPROC_PATH)/PPAdvert.fcgi $(HACKPROC_PATH)/PPRecommnd.fcgi\
	$(HACKPROC_PATH)/360Recommnd.fcgi $(HACKPROC_PATH)/tianyapeacock.fcgi $(HACKPROC_PATH)/tianyaRecommend.fcgi\
	$(HACKPROC_PATH)/mmgmrecommend.fcgi

$(HACKPROC_PATH)/wdjsummary.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)wdjsummary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/wdjsummary.fcgi

$(HACKPROC_PATH)/snssdk.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)snssdk.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/snssdk.fcgi

$(HACKPROC_PATH)/PPAdvert.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)PPAdvert.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/PPAdvert.fcgi

$(HACKPROC_PATH)/PPRecommnd.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)PPRecommnd.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/PPRecommnd.fcgi
	
$(HACKPROC_PATH)/360Recommnd.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)360Recommnd.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/360Recommnd.fcgi		

$(HACKPROC_PATH)/tianyapeacock.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)tianyapeacock.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/tianyapeacock.fcgi
	
$(HACKPROC_PATH)/tianyaRecommend.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)tianyaRecommend.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/tianyaRecommend.fcgi

$(HACKPROC_PATH)/mmgmrecommend.fcgi: $(HACK_OBJECT_PATH)/$(HACKNAME)mmgmrecommend.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(HACKPROC_PATH)$(OTJERPROC_VERSION)/mmgmrecommend.fcgi
### 编译

$(HACK_OBJECT_PATH)/$(HACKNAME)wdjsummary.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/wdjsummary/wdjsummary.cc
	
$(HACK_OBJECT_PATH)/$(HACKNAME)snssdk.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/snssdk/snssdk.cc
	
$(HACK_OBJECT_PATH)/$(HACKNAME)PPAdvert.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/PPAdvert/PPAdvert.cc
	
$(HACK_OBJECT_PATH)/$(HACKNAME)PPRecommnd.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/PPRecommnd/PPRecommnd.cc

$(HACK_OBJECT_PATH)/$(HACKNAME)360Recommnd.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/360Recommnd/360Recommnd.cc

$(HACK_OBJECT_PATH)/$(HACKNAME)tianyapeacock.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/tianyapeacock/tianyapeacock.cc

$(HACK_OBJECT_PATH)/$(HACKNAME)tianyaRecommend.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/tianyaRecommend/tianyaRecommend.cc
	
$(HACK_OBJECT_PATH)/$(HACKNAME)mmgmrecommend.o:
	$(COMPILE) .$(HACKPROC_PATH)$(OTJERPROC_VERSION)/mmgmrecommend/mmgmrecommend.cc
######################beaconproc###############################################
BEACONNAME = beacon_
BEACONPROC_PATH = /beacon
BEACON_OBJECT_PATH = ./obj$(BEACONPROC_PATH)
OTJERPROC_VERSION = /v1
beaconproc:$(BEACONPROC_PATH)/shark.fcgi

$(BEACONPROC_PATH)/shark.fcgi: $(BEACON_OBJECT_PATH)/$(BEACONNAME)shark.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BEACONPROC_PATH)$(OTJERPROC_VERSION)/shark.fcgi
	
### 编译

$(BEACON_OBJECT_PATH)/$(BEACONNAME)shark.o:
	$(COMPILE) .$(BEACONPROC_PATH)$(OTJERPROC_VERSION)/shark/shark.cc
		
######################otherproc###############################################
OTHERPROC_PATH = /other
OTJERPROC_VERSION = /1
otherproc:checkapi.fcgi

checkapi.fcgi: checkapi.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(OTHERPROC_PATH)$(OTJERPROC_VERSION)/checkapi.fcgi
	
### 编译

checkapi.o:
	$(COMPILE) .$(OTHERPROC_PATH)$(OTJERPROC_VERSION)/checkapi/checkapi.cc
	
######################robotproc###############################################
ROBOTNAME = robot_
ROBOTPROC_PATH = /robot
ROBOT_OBJECT_PATH = ./obj$(ROBOTPROC_PATH)
OTJERPROC_VERSION = /1
robotproc:$(ROBOTPROC_PATH)/spiderphone.fcgi $(ROBOTPROC_PATH)/gainmovie.fcgi $(ROBOTPROC_PATH)/updatemovie.fcgi

$(ROBOTPROC_PATH)/spiderphone.fcgi: $(ROBOT_OBJECT_PATH)/$(ROBOTNAME)spiderphone.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/spiderphone.fcgi
	
$(ROBOTPROC_PATH)/gainmovie.fcgi: $(ROBOT_OBJECT_PATH)/$(ROBOTNAME)gainmovie.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/gainmovie.fcgi

$(ROBOTPROC_PATH)/updatemovie.fcgi: $(ROBOT_OBJECT_PATH)/$(ROBOTNAME)updatemovie.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/updatemovie.fcgi
		
### 编译

$(ROBOT_OBJECT_PATH)/$(ROBOTNAME)spiderphone.o:
	$(COMPILE) .$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/spiderphone/spiderphone.cc
	
$(ROBOT_OBJECT_PATH)/$(ROBOTNAME)gainmovie.o:
	$(COMPILE) .$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/gainmovie/gainmovie.cc
	
$(ROBOT_OBJECT_PATH)/$(ROBOTNAME)updatemovie.o:
	$(COMPILE) .$(ROBOTPROC_PATH)$(OTJERPROC_VERSION)/updatemovie/updatemovie.cc
######################bookproc###############################################
BOOKNAME = book_
BOOKPROC_PATH = /book
BOOK_OBJECT_PATH = ./obj$(BOOKPROC_PATH)
OTJERPROC_VERSION = /1
bookproc:$(BOOKPROC_PATH)/booklist.fcgi $(BOOKPROC_PATH)/searchtype.fcgi $(BOOKPROC_PATH)/wanted.fcgi $(BOOKPROC_PATH)/chapterlist.fcgi\
	$(BOOKPROC_PATH)/booksummary.fcgi $(BOOKPROC_PATH)/topics.fcgi $(BOOKPROC_PATH)/complete.fcgi $(BOOKPROC_PATH)/searchkey.fcgi\
	$(BOOKPROC_PATH)/hotword.fcgi

$(BOOKPROC_PATH)/topics.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)topics.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/topics.fcgi
	
$(BOOKPROC_PATH)/searchtype.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)searchtype.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchtype.fcgi
	
$(BOOKPROC_PATH)/wanted.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)wanted.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/wanted.fcgi
	
$(BOOKPROC_PATH)/booklist.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)booklist.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booklist.fcgi
	
$(BOOKPROC_PATH)/chapterlist.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)chapterlist.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/chapterlist.fcgi
	
$(BOOKPROC_PATH)/booksummary.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)booksummary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booksummary.fcgi
	
$(BOOKPROC_PATH)/complete.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)complete.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/complete.fcgi
	
$(BOOKPROC_PATH)/searchkey.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)searchkey.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchkey.fcgi
	
$(BOOKPROC_PATH)/hotword.fcgi: $(BOOK_OBJECT_PATH)/$(BOOKNAME)hotword.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/hotword.fcgi
### 编译

$(BOOK_OBJECT_PATH)/$(BOOKNAME)topics.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/topics/topics.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)searchtype.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchtype/searchtype.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)wanted.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/wanted/wanted.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)booklist.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/booklist/booklist.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)chapterlist.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/chapterlist/chapterlist.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)booksummary.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/summary/summary.cc
	
$(BOOK_OBJECT_PATH)/$(BOOKNAME)complete.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/complete/complete.cc

$(BOOK_OBJECT_PATH)/$(BOOKNAME)searchkey.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/searchkey/searchkey.cc

$(BOOK_OBJECT_PATH)/$(BOOKNAME)hotword.o:
	$(COMPILE) .$(BOOKPROC_PATH)$(OTJERPROC_VERSION)/hotword/hotword.cc
	
######################storeproc###############################################
STORENAME = store_
STOREPROC_PATH = /store
STORE_OBJECT_PATH = ./obj$(STOREPROC_PATH)
OTJERPROC_VERSION = /1
storeproc:$(STOREPROC_PATH)/summary.fcgi $(STOREPROC_PATH)/wanted.fcgi $(STOREPROC_PATH)/like.fcgi \
	$(STOREPROC_PATH)/topics.fcgi $(STOREPROC_PATH)/searchkey.fcgi $(STOREPROC_PATH)/searchtype.fcgi\
	$(STOREPROC_PATH)/strcatalog.fcgi $(STOREPROC_PATH)/strdetail.fcgi $(STOREPROC_PATH)/shark.fcgi

$(STOREPROC_PATH)/wanted.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)wanted.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/wanted.fcgi
	
$(STOREPROC_PATH)/summary.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)summary.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/summary.fcgi
	
$(STOREPROC_PATH)/like.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)like.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/like.fcgi
	
$(STOREPROC_PATH)/topics.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)topics.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/topics.fcgi
	
$(STOREPROC_PATH)/searchkey.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)searchkey.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/searchkey.fcgi

$(STOREPROC_PATH)/searchtype.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)searchtype.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/searchtype.fcgi

$(STOREPROC_PATH)/strcatalog.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)strcatalog.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/strcatalog.fcgi
	
$(STOREPROC_PATH)/strdetail.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)strdetail.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/strdetail.fcgi

$(STOREPROC_PATH)/shark.fcgi: $(STORE_OBJECT_PATH)/$(STORENAME)shark.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(STOREPROC_PATH)$(OTJERPROC_VERSION)/shark.fcgi
	
### 编译

$(STORE_OBJECT_PATH)/$(STORENAME)summary.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/summary/summary.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)wanted.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/wanted/wanted.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)like.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/like/like.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)topics.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/topics/topics.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)searchkey.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/searchkey/searchkey.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)searchtype.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/appsearchtype/appsearchtype.cc

$(STORE_OBJECT_PATH)/$(STORENAME)strcatalog.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/strcatalog/strcatalog.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)strdetail.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/strdetail/strdetail.cc
	
$(STORE_OBJECT_PATH)/$(STORENAME)shark.o:
	$(COMPILE) .$(STOREPROC_PATH)$(OTJERPROC_VERSION)/shark/shark.cc
	
######################userproc###############################################
USERNAME = user_
USERPROC_PATH = /user
USER_OBJECT_PATH = ./obj$(USERPROC_PATH)
OTJERPROC_VERSION = /1
userproc:$(USERPROC_PATH)/quicklogin.fcgi $(USERPROC_PATH)/bdbindpush.fcgi $(USERPROC_PATH)/thirdlogin.fcgi

$(USERPROC_PATH)/quicklogin.fcgi: $(USER_OBJECT_PATH)/$(USERNAME)quicklogin.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/quicklogin.fcgi

$(USERPROC_PATH)/thirdlogin.fcgi: $(USER_OBJECT_PATH)/$(USERNAME)thirdlogin.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/thirdlogin.fcgi
	
$(USERPROC_PATH)/bdbindpush.fcgi: $(USER_OBJECT_PATH)/$(USERNAME)bindpush.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(USERPROC_PATH)$(OTJERPROC_VERSION)/bdbindpush.fcgi
	
### 编译

$(USER_OBJECT_PATH)/$(USERNAME)quicklogin.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/quicklogin/quicklogin.cc
	
$(USER_OBJECT_PATH)/$(USERNAME)bindpush.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/bindpush/bindpush.cc

$(USER_OBJECT_PATH)/$(USERNAME)thirdlogin.o:
	$(COMPILE) .$(USERPROC_PATH)$(OTJERPROC_VERSION)/thirdlogin/thirdlogin.cc
	
	
######################findproc###############################################
FINDNAME = find_
FINDPROC_PATH = /find
FIND_OBJECT_PATH = ./obj$(FINDPROC_PATH)
OTJERPROC_VERSION = /1
findproc:$(FINDPROC_PATH)/appstore.fcgi $(FINDPROC_PATH)/bookstore.fcgi $(FINDPROC_PATH)/gamestore.fcgi $(FINDPROC_PATH)/main.fcgi\
	$(FINDPROC_PATH)/gamerank.fcgi $(FINDPROC_PATH)/apprank.fcgi $(FINDPROC_PATH)/moviestore.fcgi $(FINDPROC_PATH)/personal.fcgi\
	$(FINDPROC_PATH)/movierank.fcgi

$(FINDPROC_PATH)/appstore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)appstore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/appstore.fcgi
	
$(FINDPROC_PATH)/bookstore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)bookstore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/bookstore.fcgi
	
$(FINDPROC_PATH)/gamestore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)gamestore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamestore.fcgi
	
$(FINDPROC_PATH)/main.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)main.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/main.fcgi
	
$(FINDPROC_PATH)/gamerank.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)gamerank.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamerank.fcgi

$(FINDPROC_PATH)/apprank.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)apprank.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/apprank.fcgi

$(FINDPROC_PATH)/moviestore.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)moviestore.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/moviestore.fcgi

$(FINDPROC_PATH)/wandoujia.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)wandoujia.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/wandoujia.fcgi
	
$(FINDPROC_PATH)/personal.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)personal.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/personal.fcgi

$(FINDPROC_PATH)/movierank.fcgi: $(FIND_OBJECT_PATH)/$(FINDNAME)movierank.o $(POBJ)
	$(LINKALL) -o $(OUTPUT_FILE)$(FINDPROC_PATH)$(OTJERPROC_VERSION)/movierank.fcgi
### 编译

$(FIND_OBJECT_PATH)/$(FINDNAME)appstore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/appstore/appstore.cc

$(FIND_OBJECT_PATH)/$(FINDNAME)bookstore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/bookstore/bookstore.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)gamestore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamestore/gamestore.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)main.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/main/main.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)gamerank.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/gamerank/gamerank.cc

$(FIND_OBJECT_PATH)/$(FINDNAME)apprank.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/apprank/apprank.cc

$(FIND_OBJECT_PATH)/$(FINDNAME)moviestore.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/moviestore/moviestore.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)wandoujia.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/wandoujia/wandoujia.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)personal.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/personal/personal.cc
	
$(FIND_OBJECT_PATH)/$(FINDNAME)movierank.o:
	$(COMPILE) .$(FINDPROC_PATH)$(OTJERPROC_VERSION)/movierank/movierank.cc
clean:
	-rm -f *.o
	-rm -f $(OUTPUT_FILE)./*.fcgi

delete-temp-file:
	-rm -f *.o

############public###############################
mig_log.o:
	$(COMPILE) $(LIB_DIR)/public/log/mig_log.cc

core_interface.o:
	$(COMPILE) $(LIB_DIR)/public/comm/core_interface.cc
	
http_formate.o:
	$(COMPILE) $(LIB_DIR)/public/http/http_formate.cc
