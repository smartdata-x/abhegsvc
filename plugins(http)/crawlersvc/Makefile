# Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.


# Where to find user code.

LIB_DIR = ./../../../library
SO_DIR = ../../bin/restful/plugins/crawlersvc/

USER_DIR = ../../pub

CRAWL_DIR = ./crawl
PARSER_DIR = ./parser
STO_DIR = ./storage
PARSER_DIR = ./parser
WDJ_DIR = ./wdj
LAST_DIR = ./../

THIRD_PATH = $(LIB_DIR)/public

CUSTOM_THIRD_PATH = $(LIB_DIR)/third_party

LINK_PATHS = -L./ -L/usr/local/libmemcached-1.0.7/lib/  -L/usr/lib64/mysql

# Flags passed to the preprocessor.
CPPFLAGS += -isystem -shared -fPIC -DDEBUGNEW_CPP -D_DB_POOL_ -D_DEBUG -DUSR_LOG_MSG -D_DIC_POOL_ -D_REENTRANT -D__OLD_VERSION__ -D__BASE64_MUSIC__ -D_GNU_SOURCE -DUSR_LOG_ERROR -DUSR_LOG_MSG -DPROCESS_WORK

# Flags passed to the C++ compiler.
CXXFLAGS += -g  -Wextra -pthread -shared -fPIC

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
PLUGIN = $(SO_DIR)/crawler.so
                
INCLUDE_PATHS = -I/usr/local/libmemcached-1.0.7/include \
				-I$(LIB_DIR)/core \
				-I$(THIRD_PATH)\
				-I/usr/local/include\
				-I/usr/include/mysql\
				-I$(USER_DIR)\
				-I$(LAST_DIR)\
				-I$(LIB_DIR)/base\
				-I$(CUSTOM_THIRD_PATH)\
				-I$(CUSTOM_THIRD_PATH)/hiredis\
				-I./
				


# House-keeping build targets.

ALL_HEADERS = $(USER_HEADERS)
all : $(PLUGIN)

clean :
	rm -f $(PLUGIN)  *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
#GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
#gtest-all.o : $(GTEST_SRCS_)
#	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

#gtest_main.o : $(GTEST_SRCS_)
#	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

#gtest.a : gtest-all.o
#	$(AR) $(ARFLAGS) $@ $^

#gtest_main.a : gtest-all.o gtest_main.o
#	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

crawler_init.o : ./crawler_init.cc ./crawler_init.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./crawler_init.cc $(INCLUDE_PATHS)

crawler_logic.o : ./crawler_logic.cc ./crawler_logic.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./crawler_logic.cc $(INCLUDE_PATHS)

appstore_engine.o : ./appstore_engine.cc ./appstore_engine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./appstore_engine.cc $(INCLUDE_PATHS)

parser_wdj_engine.o : ./$(WDJ_DIR)/parser_wdj_engine.cc ./$(WDJ_DIR)/parser_wdj_engine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/parser_wdj_engine.cc $(INCLUDE_PATHS) 
	
redis_crawl_wdj_storage.o : ./$(WDJ_DIR)/redis_crawl_wdj_storage.cc ./$(WDJ_DIR)/redis_crawl_wdj_storage.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/redis_crawl_wdj_storage.cc $(INCLUDE_PATHS) 

mysql_crawl_wdj_storage.o : ./$(WDJ_DIR)/mysql_crawl_wdj_storage.cc ./$(WDJ_DIR)/mysql_crawl_wdj_storage.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/mysql_crawl_wdj_storage.cc $(INCLUDE_PATHS)
	
text_crawl_wdj_storage.o : ./$(WDJ_DIR)/text_crawl_wdj_storage.cc ./$(WDJ_DIR)/text_crawl_wdj_storage.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/text_crawl_wdj_storage.cc $(INCLUDE_PATHS)
	
wdj_crawler_engine.o : ./$(WDJ_DIR)/wdj_crawler_engine.cc ./$(WDJ_DIR)/wdj_crawler_engine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/wdj_crawler_engine.cc $(INCLUDE_PATHS)

wdj_http_api.o : ./$(WDJ_DIR)/wdj_http_api.cc ./$(WDJ_DIR)/wdj_http_api.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/wdj_http_api.cc $(INCLUDE_PATHS) 

wdj_parser.o : ./$(WDJ_DIR)/wdj_parser.cc ./$(WDJ_DIR)/wdj_parser.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/wdj_parser.cc $(INCLUDE_PATHS)
	
wdjstore_impl.o : ./$(WDJ_DIR)/wdjstore_impl.cc ./$(WDJ_DIR)/wdjstore_impl.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(WDJ_DIR)/wdjstore_impl.cc $(INCLUDE_PATHS)
	
rsp_parser.o : ./$(PARSER_DIR)/rsp_parser.cc ./$(PARSER_DIR)/rsp_parser.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(PARSER_DIR)/rsp_parser.cc $(INCLUDE_PATHS)
	
crawler_api.o : ./$(CRAWL_DIR)/crawler_api.cc ./$(CRAWL_DIR)/crawler_api.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(CRAWL_DIR)/crawler_api.cc $(INCLUDE_PATHS)

crawler_engine.o : ./$(CRAWL_DIR)/crawler_engine.cc ./$(CRAWL_DIR)/crawler_engine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(CRAWL_DIR)/crawler_engine.cc $(INCLUDE_PATHS)

http_api.o : ./$(CRAWL_DIR)/http_api.cc ./$(CRAWL_DIR)/http_api.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(CRAWL_DIR)/http_api.cc $(INCLUDE_PATHS)
	
redis_crawl_storage.o : ./$(STO_DIR)/redis_crawl_storage.cc ./$(STO_DIR)/redis_crawl_storage.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(STO_DIR)/redis_crawl_storage.cc $(INCLUDE_PATHS)

mysql_crawl_storage.o : ./$(STO_DIR)/mysql_crawl_storage.cc ./$(STO_DIR)/mysql_crawl_storage.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(STO_DIR)/mysql_crawl_storage.cc $(INCLUDE_PATHS)
	
text_crawl_storage.o : ./$(STO_DIR)/text_crawl_storage.cc ./$(STO_DIR)/text_crawl_storage.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(STO_DIR)/text_crawl_storage.cc $(INCLUDE_PATHS)
	
storage_base_engine.o : ./$(STO_DIR)/storage_base_engine.cc ./$(STO_DIR)/storage_base_engine.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(STO_DIR)/storage_base_engine.cc $(INCLUDE_PATHS)

base_parser.o : ./$(PARSER_DIR)/base_parser.cc ./$(PARSER_DIR)/base_parser.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c ./$(PARSER_DIR)/base_parser.cc $(INCLUDE_PATHS)
		
logic_infos.o :  $(USER_DIR)/logic/logic_infos.cc $(USER_DIR)/logic/logic_infos.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/logic/logic_infos.cc $(INCLUDE_PATHS)


basic_util.o: $(THIRD_PATH)/basic/basic_util.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/basic/basic_util.cc $(INCLUDE_PATHS)
	
file_path.o:$(THIRD_PATH)/file/file_path.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/file/file_path.cc $(INCLUDE_PATHS)
	
file_util.o:$(THIRD_PATH)/file/file_util.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/file/file_util.cc $(INCLUDE_PATHS)
	

zip.o:$(THIRD_PATH)/basic/zip.cc  $(THIRD_PATH)/basic/zip.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/basic/zip.cc $(INCLUDE_PATHS)
	
unzip.o:$(THIRD_PATH)/basic/unzip.cc  $(THIRD_PATH)/basic/unzip.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/basic/unzip.cc $(INCLUDE_PATHS)
	
debugnew.o:$(THIRD_PATH)/check/debugnew.cc  $(THIRD_PATH)/check/debugnew.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/check/debugnew.cc $(INCLUDE_PATHS)

rbtree.o:$(THIRD_PATH)/check/rbtree.cc  $(THIRD_PATH)/check/rbtree.h
	$(COMPILERC) -std=c99 -pedantic -c $(INCLUDE_PATHS) -O3 -fPIC  -Wall -W -Wstrict-prototypes -Wwrite-strings -g -ggdb $(THIRD_PATH)/storage/redis_warrper.c
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(THIRD_PATH)/check/rbtree.cc $(INCLUDE_PATHS)
	

$(PLUGIN) : debugnew.o rbtree.o logic_infos.o base_parser.o parser_wdj_engine.o storage_base_engine.o crawler_init.o crawler_logic.o appstore_engine.o redis_crawl_wdj_storage.o wdj_crawler_engine.o\
	wdj_http_api.o wdj_parser.o wdjstore_impl.o rsp_parser.o crawler_api.o crawler_engine.o http_api.o mysql_crawl_storage.o\
	redis_crawl_storage.o  basic_util.o mysql_crawl_wdj_storage.o text_crawl_storage.o text_crawl_wdj_storage.o file_path.o file_util.o unzip.o zip.o\
	$(CUSTOM_THIRD_PATH)/dmg_fp/lib/dmg_fp.a  $(LIB_DIR)/base/lib/mybase.a $(LIB_DIR)/lib/libhiredis.a $(LIB_DIR)/lib/robot_interface.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(LINK_PATHS) -lpthread -lexpat -lrt -lpthread -ldl -liconv -lmysqlclient -lcurl -lmemcached -lmemcachedutil \
	$^ -o $@
