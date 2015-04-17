#include "hack_logic.h"
#include "hack_init.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "dic/base_dic_redis_auto.h"
#include "common.h"
#include <string>
#include <sstream>


#define TIME_TEST_GET_WANDOUJIASUAMMRY    10001//消息检测

namespace hacksvc_logic{

Hacklogic*
Hacklogic::instance_=NULL;

Hacklogic::Hacklogic(){
   if(!Init())
      assert(0);
}

Hacklogic::~Hacklogic(){
	base_dic::RedisPool::Dest();
}

bool Hacklogic::Init(){
	wandoujia_appstore_connector_engine_ = hacksvc_logic::AppStoreConnector::Create(IMPL_WANDOUJIA);
	//配置文件
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);
	base_dic::RedisPool::Init(config->redis_list_);
    return true;
}

Hacklogic*
Hacklogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Hacklogic();

    return instance_;
}



void Hacklogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Hacklogic::OnHackConnect(struct server *srv,const int socket){

    return true;
}



bool Hacklogic::OnHackMessage(struct server *srv, const int socket, const void *msg,const int len){
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
		case HACK_WANDOUJIA_SUMMARY:
			OnHackWandoujiaSuammry(srv,socket,value);
			break;
	}
    return true;
}

bool Hacklogic::OnHackClose(struct server *srv,const int socket){

    return true;
}



bool Hacklogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Hacklogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Hacklogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Hacklogic::OnIniTimer(struct server *srv){
	srv->add_time_task(srv,"hack",TIME_TEST_GET_WANDOUJIASUAMMRY,2,-1);
    return true;
}



bool Hacklogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

	switch(opcode){
		case TIME_TEST_GET_WANDOUJIASUAMMRY:
			OnQueueGetAppSummary();
			break;
	}

    return true;
}

bool Hacklogic::OnHackWandoujiaSuammry(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	//std::string message = "{\"ad\":false,\"adPosition\":null,\"adType\":null,\"alias\":\"Minik run\",\"apkObbs\":[],\"apks\":[{\"adsType\":\"EMBEDED\",\"beta\":false,\"brief\":null,\"bytes\":15409841,\"compatible\":1,\"creation\":1428770268000,\"dangerousPermissions\":null,\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":100,\"market\":\"Google Play\",\"referUrl\":\"https://play.google.com/store/apps/details?hl=zh_CN&id=com.Kiarygames.Minikrun\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"},\"downloadUrls\":[{\"aggrWeight\":100,\"market\":\"Google Play\",\"referUrl\":\"https://play.google.com/store/apps/details?hl=zh_CN&id=com.Kiarygames.Minikrun\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"},{\"aggrWeight\":1,\"market\":\"360手机助手\",\"referUrl\":\"http://zhushou.360.cn/detail/index/soft_id/2836179\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"}],\"featuresInfo\":1572866,\"gameSdkVersion\":null,\"gsfType\":2,\"id\":13589702,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"6bffebb283b319ee23949c571c97f985\",\"minSdkVersion\":14,\"official\":0,\"packageName\":\"com.doudizhu.mainhuanle\",\"paidType\":\"NONE\",\"permissionGroups\":\"照片/媒体/文件/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"NORMAL\",\"permissionStatement\":null,\"permissions\":[\"读取手机状态和身份\",\"修改或删除USB存储设备中的内容\",\"从互联网接收数据\",\"查看 Wi-Fi 状态\",\"查看网络状态\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\",\"xhdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"360\",\"status\":\"SAFE\"},{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"SAFE\"},{\"failedInfo\":null,\"provider\":\"lbe\",\"status\":\"SAFE\"}],\"securityStatus\":\"SAFE\",\"signature\":\"6e53c3cf841507806d492d78742d9e55\",\"size\":\"14.7M\",\"superior\":0,\"targetSdkVersion\":21,\"verified\":1,\"versionCode\":22,\"versionName\":\"1.08\"}],\"appType\":null,\"award\":{\"authorDesc\":null,\"authorLink\":null,\"authorName\":null,\"banner\":null,\"blogImage\":null,\"blogLink\":null,\"blogTitle\":null,\"comment\":null,\"creation\":null,\"issue\":null,\"markdownComment\":null,\"modification\":null},\"banner\":null,\"broadTerms\":null,\"categories\":[],\"changelog\":null,\"commentsCount\":8,\"cooperator\":false,\"defaultVersionCode\":22,\"description\":\"《途游斗地主》，又名《途游单机斗地主》，在传统斗地主玩法的基础上，加入了全城语聊、经典比赛等新颖且丰富的玩法。无论联网多平台海量玩家对战、还是单机个人休闲，途游《途游斗地主》都会带给您不一样的极致体验！让您的休闲生活High起来！\",\"detailParam\":\"pos=m/games/index/detail/section/999978:198412830\",\"developer\":{\"email\":null,\"id\":0,\"intro\":null,\"name\":\"Kiary games\",\"urls\":null,\"verified\":null,\"website\":null,\"weibo\":null},\"dislikesCount\":1,\"downloadCount\":5916,\"downloadCountStr\":\"5916 \",\"editorComment\":null,\"exclusiveBadge\":0,\"extensionPacks\":[],\"extra\":{},\"game\":null,\"icons\":{\"px48\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_48_48.png\",\"px100\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_100_100.png\",\"px256\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_256_256.png\",\"px78\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_78_78.png\",\"px24\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_24_24.png\",\"px68\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_68_68.png\",\"px36\":\"http://img.wdjimg.com/mms/icon/v1/1/a6/993c171c5dd16ccd1c7c26fb48baba61_36_36.png\"},\"iconsStr\":\"993c171c5dd16ccd1c7c26fb48baba61#300#300#jpeg\",\"id\":3209168,\"imprUrl\":null,\"installedCount\":3813,\"installedCountStr\":\"3813 \",\"itemStatus\":1,\"latestApk\":{\"adsType\":\"EMBEDED\",\"beta\":false,\"brief\":null,\"bytes\":15409841,\"compatible\":null,\"creation\":1428770268000,\"dangerousPermissions\":null,\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":100,\"market\":\"Google Play\",\"referUrl\":\"https://play.google.com/store/apps/details?hl=zh_CN&id=com.Kiarygames.Minikrun\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"},\"downloadUrls\":[{\"aggrWeight\":100,\"market\":\"Google Play\",\"referUrl\":\"https://play.google.com/store/apps/details?hl=zh_CN&id=com.Kiarygames.Minikrun\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"},{\"aggrWeight\":1,\"market\":\"360手机助手\",\"referUrl\":\"http://zhushou.360.cn/detail/index/soft_id/2836179\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"}],\"featuresInfo\":1572866,\"gameSdkVersion\":null,\"gsfType\":2,\"id\":13589702,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"6bffebb283b319ee23949c571c97f985\",\"minSdkVersion\":14,\"official\":0,\"packageName\":\"com.doudizhu.mainhuanle\",\"paidType\":\"NONE\",\"permissionGroups\":\"照片/媒体/文件/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"NORMAL\",\"permissionStatement\":null,\"permissions\":[\"读取手机状态和身份\",\"修改或删除USB存储设备中的内容\",\"从互联网接收数据\",\"查看 Wi-Fi 状态\",\"查看网络状态\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\",\"xhdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"360\",\"status\":\"SAFE\"},{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"SAFE\"},{\"failedInfo\":null,\"provider\":\"lbe\",\"status\":\"SAFE\"}],\"securityStatus\":\"SAFE\",\"signature\":\"6e53c3cf841507806d492d78742d9e55\",\"size\":\"14.7 M\",\"superior\":0,\"targetSdkVersion\":21,\"verified\":1,\"versionCode\":22,\"versionName\":\"1.08\"},\"likesCount\":2,\"likesRate\":67,\"negComments\":[],\"packageName\":\"com.doudizhu.mainhuanle\",\"posComments\":[],\"publishDate\":1428770264000,\"publishNoticeBean\":null,\"reputationScore\":0,\"screenshots\":{\"small\":[\"http://img.wdjimg.com/mms/screenshot/0/45/2e06be27fff1a43ba448985c6df8a450_355_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/5/dd/fd1584ed79a310954ac15e8cc4fe8dd5_355_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/6/e5/9b6b6d59c50db2a2862af7675b36ce56_355_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/e/7e/447c887edf2876b673ff5c04094487ee_355_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/a/5a/e5c3951fe34a1390aa784b10b98705aa_355_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/9/b2/aa0a7047542d0bb23363b90215138b29_355_200.jpeg\"],\"normal\":[\"http://img.wdjimg.com/mms/screenshot/0/45/2e06be27fff1a43ba448985c6df8a450_568_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/5/dd/fd1584ed79a310954ac15e8cc4fe8dd5_568_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/6/e5/9b6b6d59c50db2a2862af7675b36ce56_568_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/e/7e/447c887edf2876b673ff5c04094487ee_568_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/a/5a/e5c3951fe34a1390aa784b10b98705aa_568_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/9/b2/aa0a7047542d0bb23363b90215138b29_568_320.jpeg\"]},\"screenshotsStr\":\"2e06be27fff1a43ba448985c6df8a450#1600#900#jpeg,fd1584ed79a310954ac15e8cc4fe8dd5#1600#900#jpeg,9b6b6d59c50db2a2862af7675b36ce56#1600#900#jpeg,447c887edf2876b673ff5c04094487ee#1600#900#jpeg,e5c3951fe34a1390aa784b10b98705aa#1600#900#jpeg,aa0a7047542d0bb23363b90215138b29#1600#900#jpeg\",\"selectedExtensionPack\":0,\"snippet\":\"《途游斗地主》，又名《途游单机斗地主》，在传统斗地主玩法的基础上，加入了全城语聊、经典比赛等新颖且丰富的玩法。无论联网多平台海量玩家对战、还是单机个人休闲，途游《途游斗地主》都会带给您不一样的极致体验！让您的休闲生活High起来！\",\"stat\":{\"daily\":[{\"date\":1428768000000,\"downloadCount\":2,\"downloadCountStr\":\"2 \"},{\"date\":1428854400000,\"downloadCount\":1201,\"downloadCountStr\":\"1201 \"},{\"date\":1428940800000,\"downloadCount\":4713,\"downloadCountStr\":\"4713 \"}],\"total\":5916,\"totalStr\":\"5916 \",\"weekly\":5916,\"weeklyCommentsCount\":5,\"weeklyCommentsCountStr\":\"5 \",\"weeklyStr\":\"5916 \"},\"tagline\":null,\"tags\":[],\"title\":\"途游斗地主\",\"titleEn\":null,\"updatedDate\":null}";
	//std::string message = "{\"ad\":false,\"adPosition\":null,\"adType\":null,\"alias\":\"Hill Climb Racing\",\"apkObbs\":[],\"apks\":[{\"adsType\":\"NONE\",\"beta\":false,\"brief\":null,\"bytes\":27076638,\"compatible\":1,\"creation\":1428374717000,\"dangerousPermissions\":[\"发送短信（此操作可能需要付费）\",\"访问联系人数据\"],\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.fingersoft.hillclimb?uid=77120723\",\"url\":\"http://121.40.191.137/4.php?signature=5a97813&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=0693ae6419ed5e1f9a673cadc53c5399&apkid=13453980&vc=55&size=27076638&pos=m/games/index/detail/section/0:198412830&udid=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&tokenId=wandoujia_android&appType=GAME\"},\"downloadUrls\":[{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.fingersoft.hillclimb?uid=77120723\",\"url\":\"http://121.40.191.137/4.php?signature=5a97813&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=0693ae6419ed5e1f9a673cadc53c5399&apkid=13453980&vc=55&size=27076638&pos=m/games/index/detail/section/0:198412830&udid=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&tokenId=wandoujia_android&appType=GAME\"}],\"featuresInfo\":12885951618,\"gameSdkVersion\":null,\"gsfType\":0,\"id\":13453980,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"0693ae6419ed5e1f9a673cadc53c5399\",\"minSdkVersion\":8,\"official\":1,\"packageName\":\"com.fingersoft.hillclimb\",\"paidType\":\"NONE\",\"permissionGroups\":\"通讯录/短信/照片/媒体/文件/相机/麦克风/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"TRUSTED\",\"permissionStatement\":\"运营商短代计费\",\"permissions\":[\"显示系统级警报\",\"修改或删除USB存储设备中的内容\",\"读取手机状态和身份\",\"停用键盘锁\",\"从互联网接收数据\",\"查看 Wi-Fi 状态\",\"拍照\",\"发送短信（此操作可能需要付费）\",\"查看网络状态\",\"装载和卸载文件系统\",\"访问联系人数据\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"UNKNOWN\"}],\"securityStatus\":\"UNKNOWN\",\"signature\":\"6a4560508bcb2dae57866405fd7642b6\",\"size\":\"25.82M\",\"superior\":1,\"targetSdkVersion\":16,\"verified\":2,\"versionCode\":55,\"versionName\":\"1.25.6\"}],\"appType\":\"GAME\",\"award\":{\"authorDesc\":null,\"authorLink\":null,\"authorName\":null,\"banner\":null,\"blogImage\":null,\"blogLink\":null,\"blogTitle\":null,\"comment\":null,\"creation\":null,\"issue\":null,\"markdownComment\":null,\"modification\":null},\"banner\":\"http://img.wdjimg.com/mms/banner/0/a6/3357d0df7ccac0c3576d031955402a60_320_250.jpeg\",\"broadTerms\":null,\"categories\":[{\"alias\":\"parkour\",\"level\":1,\"name\":\"跑酷竞速\",\"type\":\"GAME\"},{\"alias\":\"casual\",\"level\":1,\"name\":\"休闲时间\",\"type\":\"GAME\"},{\"alias\":null,\"level\":2,\"name\":\"赛车\",\"type\":\"GAME\"},{\"alias\":null,\"level\":2,\"name\":\"益智\",\"type\":\"GAME\"}],\"changelog\":\"最新官方中文版V1.25.6/7 新增一个核电站地图和一辆迷你机车，带来更新更刺激的游戏体验。\",\"commentsCount\":616,\"cooperator\":false,\"defaultVersionCode\":55,\"description\":\"《登山赛车》是一款风靡全球的趣味驾车游戏，下载量已超2亿。以真实物理特性为操作基础，丰富的关卡场景和功能各异的车型，不仅增加了游戏的耐玩性，还能让玩家淋漓尽致地体验绝妙的驾驶乐趣。玩家可以对爱车的引擎、悬挂、轮胎及四驱系统进行升级，引擎升级时还能听到逼真的轰鸣音效。\",\"detailParam\":\"pos=m/games/index/detail/section/0:198412830\",\"developer\":{\"email\":\"support@fingersoft.net\",\"id\":77120723,\"intro\":null,\"name\":\"北京唯我乐园信息技术有限公司\",\"urls\":null,\"verified\":null,\"website\":\"http://www.fingersoft.net\",\"weibo\":null},\"dislikesCount\":109,\"downloadCount\":729311,\"downloadCountStr\":\"73 万\",\"editorComment\":\"一款涵盖基础物理设计的赛车竞速类游戏，挑战各种奇特的爬坡环境，通过大胆的动作来赢得奖励。\",\"exclusiveBadge\":0,\"extensionPacks\":[],\"extra\":{\"appOperatorRemark\":{\"editorName\":\"admin\",\"updateDate\":\"Oct 25, 2014 5:01:28 PM\",\"editorUid\":0,\"backgroundImage\":\"http://img.wdjimg.com/static-files/auv/banners/blue.jpg\",\"packageName\":\"com.fingersoft.hillclimb\",\"commentContent\":\"\",\"useComment\":false}},\"game\":null,\"icons\":{\"px48\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_48_48.png\",\"px100\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_100_100.png\",\"px256\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_256_256.png\",\"px78\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_78_78.png\",\"px24\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_24_24.png\",\"px68\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_68_68.png\",\"px36\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_36_36.png\"},\"iconsStr\":\"8c63e36d71d90c6ec9b1c3ab41a51d0d#512#512#png\",\"id\":401722,\"imprUrl\":null,\"installedCount\":2440993,\"installedCountStr\":\"244 万\",\"itemStatus\":1,\"latestApk\":{\"adsType\":\"BOTH\",\"beta\":false,\"brief\":null,\"bytes\":6990160,\"compatible\":null,\"creation\":1365157832000,\"dangerousPermissions\":[\"监听新安装应用\"],\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":1,\"market\":\"百度手机助手\",\"referUrl\":\"http://shouji.baidu.com/soft/item?docid=1530498\",\"url\":\"http://121.40.191.137/4.php?signature=f467472&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=1ac6d3c4cd0526491fc1431b2f6a951a&apkid=1931922&vc=15300000&size=6990160\"},\"downloadUrls\":[{\"aggrWeight\":1,\"market\":\"百度手机助手\",\"referUrl\":\"http://shouji.baidu.com/soft/item?docid=1530498\",\"url\":\"http://121.40.191.137/4.php?signature=f467472&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=1ac6d3c4cd0526491fc1431b2f6a951a&apkid=1931922&vc=15300000&size=6990160\"}],\"featuresInfo\":59244674,\"gameSdkVersion\":null,\"gsfType\":null,\"id\":1931922,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"1ac6d3c4cd0526491fc1431b2f6a951a\",\"minSdkVersion\":8,\"official\":0,\"packageName\":\"com.fingersoft.hillclimb\",\"paidType\":\"NONE\",\"permissionGroups\":\"安装应用/设备和应用历史记录/移动数据网络设置/位置信息/照片/媒体/文件/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"DANGEROUS\",\"permissionStatement\":null,\"permissions\":[\"显示系统级警报\",\"从互联网接收数据\",\"控制振动器\",\"查看 Wi-Fi 状态\",\"写入主屏幕设置和快捷方式\",\"读取主屏幕设置和快捷方式\",\"安装快捷方式\",\"监听新安装应用\",\"装载和卸载文件系统\",\"检索当前运行的应用程序\",\"修改或删除USB存储设备中的内容\",\"读取手机状态和身份\",\"读取精准的 GPS 位置\",\"读取基于网络的粗略位置\",\"更改 Wi-Fi 状态\",\"查看网络状态\",\"防止手机休眠\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"360\",\"status\":\"SAFE\"},{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"UNKNOWN\"},{\"failedInfo\":null,\"provider\":\"lbe\",\"status\":\"SAFE\"}],\"securityStatus\":\"SAFE\",\"signature\":\"ff2bab86adc4b5ed2ac77efd2c9a9996\",\"size\":\"6.67M\",\"superior\":0,\"targetSdkVersion\":16,\"verified\":0,\"versionCode\":15300000,\"versionName\":\"1.5.3\"},\"likesCount\":358,\"likesRate\":77,\"negComments\":[{\"authorName\":\"艾你的**\",\"comment\":\"差点憋出内伤,╰_╯╬。\",\"id\":8345413,\"uid\":30503513}],\"packageName\":\"com.fingersoft.hillclimb\",\"posComments\":[{\"authorName\":\"歃血龙族\",\"comment\":\"很不错。车都解锁了。很好玩的游戏,用的是八门神器解锁了…\",\"id\":6066733,\"uid\":2774973}],\"publishDate\":1348722355000,\"publishNoticeBean\":null,\"reputationScore\":78,\"screenshots\":{\"small\":[\"http://img.wdjimg.com/mms/screenshot/d/63/75a4de3cae78af2cc6e0766b440d463d_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/3/f8/21381be8fd6bed71a77a3c13e2907f83_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/a/f8/70c1f479b741a60ff38bcbedbb7a2f8a_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/b/2b/d1d7169a45488297c5a3228608c6d2bb_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/2/c1/208580c96aa225e5ae8762a9df145c12_333_200.jpeg\"],\"normal\":[\"http://img.wdjimg.com/mms/screenshot/d/63/75a4de3cae78af2cc6e0766b440d463d_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/3/f8/21381be8fd6bed71a77a3c13e2907f83_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/a/f8/70c1f479b741a60ff38bcbedbb7a2f8a_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/b/2b/d1d7169a45488297c5a3228608c6d2bb_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/2/c1/208580c96aa225e5ae8762a9df145c12_533_320.jpeg\"]},\"screenshotsStr\":\"75a4de3cae78af2cc6e0766b440d463d#800#480#jpeg,21381be8fd6bed71a77a3c13e2907f83#800#480#jpeg,70c1f479b741a60ff38bcbedbb7a2f8a#800#480#jpeg,d1d7169a45488297c5a3228608c6d2bb#800#480#jpeg,208580c96aa225e5ae8762a9df145c12#800#480#jpeg\",\"selectedExtensionPack\":0,\"snippet\":\"《登山赛车》是一款风靡全球的趣味驾车游戏，下载量已超2亿。以真实物理特性为操作基础，丰富的关卡场景和功能各异的车型，不仅增加了游戏的耐玩性，还能让玩家淋漓尽致地体验绝妙的驾驶乐趣。玩家可以对爱车的引擎、悬挂、轮胎及四驱系统进行升级，引擎升级时还能听到逼真的轰鸣音效。\",\"stat\":{\"daily\":[{\"date\":1428422400000,\"downloadCount\":1046,\"downloadCountStr\":\"1046 \"},{\"date\":1428508800000,\"downloadCount\":1096,\"downloadCountStr\":\"1096 \"},{\"date\":1428595200000,\"downloadCount\":4614,\"downloadCountStr\":\"4614 \"},{\"date\":1428681600000,\"downloadCount\":7291,\"downloadCountStr\":\"7291 \"},{\"date\":1428768000000,\"downloadCount\":7748,\"downloadCountStr\":\"7748 \"},{\"date\":1428854400000,\"downloadCount\":4739,\"downloadCountStr\":\"4739 \"},{\"date\":1428940800000,\"downloadCount\":4827,\"downloadCountStr\":\"4827 \"}],\"total\":729311,\"totalStr\":\"73 万\",\"weekly\":31361,\"weeklyCommentsCount\":18,\"weeklyCommentsCountStr\":\"18 \",\"weeklyStr\":\"3.1 万\"},\"tagline\":\"上手容易\",\"tags\":[{\"tag\":\"跑酷竞速\",\"weight\":2},{\"tag\":\"休闲时间\",\"weight\":2},{\"tag\":\"赛车\",\"weight\":2},{\"tag\":\"益智\",\"weight\":2},{\"tag\":\"跑酷\",\"weight\":0},{\"tag\":\"卡通\",\"weight\":0},{\"tag\":\"竞速\",\"weight\":0},{\"tag\":\"联运\",\"weight\":0},{\"tag\":\"物理\",\"weight\":0},{\"tag\":\"体育竞速\",\"weight\":0},{\"tag\":\"追求\",\"weight\":0},{\"tag\":\"好玩的\",\"weight\":0},{\"tag\":\"休闲益智\",\"weight\":0},{\"tag\":\"上瘾\",\"weight\":0}],\"title\":\"登山赛车\",\"titleEn\":null,\"updatedDate\":1428631277000}";
	//std::string message = "{\"ad\":false,\"adPosition\":null,\"adType\":null,\"alias\":\"Hill Climb Racing\",\"apkObbs\":[],\"apks\":[{\"adsType\":\"NONE\",\"beta\":false,\"brief\":null,\"bytes\":15409841,\"compatible\":1,\"creation\":1428374717000,\"dangerousPermissions\":[\"发送短信（此操作可能需要付费）\",\"访问联系人数据\"],\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.fingersoft.hillclimb?uid=77120723\",\"url\":\"http://121.40.191.137/4.php?signature=5a97813&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=0693ae6419ed5e1f9a673cadc53c5399&apkid=13453980&vc=55&size=27076638&pos=m/games/index/detail/section/0:198412830&udid=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&tokenId=wandoujia_android&appType=GAME\"},\"downloadUrls\":[{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.fingersoft.hillclimb?uid=77120723\",\"url\":\"http://121.40.191.137/4.php?signature=5a97813&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=0693ae6419ed5e1f9a673cadc53c5399&apkid=13453980&vc=55&size=27076638&pos=m/games/index/detail/section/0:198412830&udid=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&tokenId=wandoujia_android&appType=GAME\"}],\"featuresInfo\":12885951618,\"gameSdkVersion\":null,\"gsfType\":0,\"id\":13453980,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"6bffebb283b319ee23949c571c97f985\",\"minSdkVersion\":8,\"official\":1,\"packageName\":\"com.doudizhu.mainhuanle\",\"paidType\":\"NONE\",\"permissionGroups\":\"通讯录/短信/照片/媒体/文件/相机/麦克风/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"TRUSTED\",\"permissionStatement\":\"运营商短代计费\",\"permissions\":[\"显示系统级警报\",\"修改或删除USB存储设备中的内容\",\"读取手机状态和身份\",\"停用键盘锁\",\"从互联网接收数据\",\"查看 Wi-Fi 状态\",\"拍照\",\"发送短信（此操作可能需要付费）\",\"查看网络状态\",\"装载和卸载文件系统\",\"访问联系人数据\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"UNKNOWN\"}],\"securityStatus\":\"UNKNOWN\",\"signature\":\"6a4560508bcb2dae57866405fd7642b6\",\"size\":\"25.82M\",\"superior\":1,\"targetSdkVersion\":16,\"verified\":2,\"versionCode\":55,\"versionName\":\"1.25.6\"}],\"appType\":\"GAME\",\"award\":{\"authorDesc\":null,\"authorLink\":null,\"authorName\":null,\"banner\":null,\"blogImage\":null,\"blogLink\":null,\"blogTitle\":null,\"comment\":null,\"creation\":null,\"issue\":null,\"markdownComment\":null,\"modification\":null},\"banner\":\"http://img.wdjimg.com/mms/banner/0/a6/3357d0df7ccac0c3576d031955402a60_320_250.jpeg\",\"broadTerms\":null,\"categories\":[{\"alias\":\"parkour\",\"level\":1,\"name\":\"跑酷竞速\",\"type\":\"GAME\"},{\"alias\":\"casual\",\"level\":1,\"name\":\"休闲时间\",\"type\":\"GAME\"},{\"alias\":null,\"level\":2,\"name\":\"赛车\",\"type\":\"GAME\"},{\"alias\":null,\"level\":2,\"name\":\"益智\",\"type\":\"GAME\"}],\"changelog\":\"最新官方中文版V1.25.6/7 新增一个核电站地图和一辆迷你机车，带来更新更刺激的游戏体验。\",\"commentsCount\":616,\"cooperator\":false,\"defaultVersionCode\":55,\"description\":\"《登山赛车》是一款风靡全球的趣味驾车游戏，下载量已超2亿。以真实物理特性为操作基础，丰富的关卡场景和功能各异的车型，不仅增加了游戏的耐玩性，还能让玩家淋漓尽致地体验绝妙的驾驶乐趣。玩家可以对爱车的引擎、悬挂、轮胎及四驱系统进行升级，引擎升级时还能听到逼真的轰鸣音效。\",\"detailParam\":\"pos=m/games/index/detail/section/0:198412830\",\"developer\":{\"email\":\"support@fingersoft.net\",\"id\":77120723,\"intro\":null,\"name\":\"北京唯我乐园信息技术有限公司\",\"urls\":null,\"verified\":null,\"website\":\"http://www.fingersoft.net\",\"weibo\":null},\"dislikesCount\":109,\"downloadCount\":729311,\"downloadCountStr\":\"73 万\",\"editorComment\":\"一款涵盖基础物理设计的赛车竞速类游戏，挑战各种奇特的爬坡环境，通过大胆的动作来赢得奖励。\",\"exclusiveBadge\":0,\"extensionPacks\":[],\"extra\":{\"appOperatorRemark\":{\"editorName\":\"admin\",\"updateDate\":\"Oct 25, 2014 5:01:28 PM\",\"editorUid\":0,\"backgroundImage\":\"http://img.wdjimg.com/static-files/auv/banners/blue.jpg\",\"packageName\":\"com.fingersoft.hillclimb\",\"commentContent\":\"\",\"useComment\":false}},\"game\":null,\"icons\":{\"px48\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_48_48.png\",\"px100\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_100_100.png\",\"px256\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_256_256.png\",\"px78\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_78_78.png\",\"px24\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_24_24.png\",\"px68\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_68_68.png\",\"px36\":\"http://img.wdjimg.com/mms/icon/v1/d/d0/8c63e36d71d90c6ec9b1c3ab41a51d0d_36_36.png\"},\"iconsStr\":\"8c63e36d71d90c6ec9b1c3ab41a51d0d#512#512#png\",\"id\":401722,\"imprUrl\":null,\"installedCount\":2440993,\"installedCountStr\":\"244 万\",\"itemStatus\":1,\"latestApk\":{\"adsType\":\"BOTH\",\"beta\":false,\"brief\":null,\"bytes\":15409841,\"compatible\":null,\"creation\":1365157832000,\"dangerousPermissions\":[\"监听新安装应用\"],\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":1,\"market\":\"百度手机助手\",\"referUrl\":\"http://shouji.baidu.com/soft/item?docid=1530498\",\"url\":\"http://121.40.191.137/4.php?signature=f467472&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=1ac6d3c4cd0526491fc1431b2f6a951a&apkid=1931922&vc=15300000&size=6990160\"},\"downloadUrls\":[{\"aggrWeight\":1,\"market\":\"百度手机助手\",\"referUrl\":\"http://shouji.baidu.com/soft/item?docid=1530498\",\"url\":\"http://121.40.191.137/4.php?signature=f467472&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2836.apk&pn=com.fingersoft.hillclimb&md5=1ac6d3c4cd0526491fc1431b2f6a951a&apkid=1931922&vc=15300000&size=6990160\"}],\"featuresInfo\":59244674,\"gameSdkVersion\":null,\"gsfType\":null,\"id\":1931922,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"6bffebb283b319ee23949c571c97f985\",\"minSdkVersion\":8,\"official\":0,\"packageName\":\"com.doudizhu.mainhuanle\",\"paidType\":\"NONE\",\"permissionGroups\":\"安装应用/设备和应用历史记录/移动数据网络设置/位置信息/照片/媒体/文件/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"DANGEROUS\",\"permissionStatement\":null,\"permissions\":[\"显示系统级警报\",\"从互联网接收数据\",\"控制振动器\",\"查看 Wi-Fi 状态\",\"写入主屏幕设置和快捷方式\",\"读取主屏幕设置和快捷方式\",\"安装快捷方式\",\"监听新安装应用\",\"装载和卸载文件系统\",\"检索当前运行的应用程序\",\"修改或删除USB存储设备中的内容\",\"读取手机状态和身份\",\"读取精准的 GPS 位置\",\"读取基于网络的粗略位置\",\"更改 Wi-Fi 状态\",\"查看网络状态\",\"防止手机休眠\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"360\",\"status\":\"SAFE\"},{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"UNKNOWN\"},{\"failedInfo\":null,\"provider\":\"lbe\",\"status\":\"SAFE\"}],\"securityStatus\":\"SAFE\",\"signature\":\"ff2bab86adc4b5ed2ac77efd2c9a9996\",\"size\":\"6.67M\",\"superior\":0,\"targetSdkVersion\":16,\"verified\":0,\"versionCode\":15300000,\"versionName\":\"1.5.3\"},\"likesCount\":358,\"likesRate\":77,\"negComments\":[{\"authorName\":\"艾你的**\",\"comment\":\"差点憋出内伤,╰_╯╬。\",\"id\":8345413,\"uid\":30503513}],\"packageName\":\"com.doudizhu.mainhuanle\",\"posComments\":[{\"authorName\":\"歃血龙族\",\"comment\":\"很不错。车都解锁了。很好玩的游戏,用的是八门神器解锁了…\",\"id\":6066733,\"uid\":2774973}],\"publishDate\":1348722355000,\"publishNoticeBean\":null,\"reputationScore\":78,\"screenshots\":{\"small\":[\"http://img.wdjimg.com/mms/screenshot/d/63/75a4de3cae78af2cc6e0766b440d463d_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/3/f8/21381be8fd6bed71a77a3c13e2907f83_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/a/f8/70c1f479b741a60ff38bcbedbb7a2f8a_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/b/2b/d1d7169a45488297c5a3228608c6d2bb_333_200.jpeg\",\"http://img.wdjimg.com/mms/screenshot/2/c1/208580c96aa225e5ae8762a9df145c12_333_200.jpeg\"],\"normal\":[\"http://img.wdjimg.com/mms/screenshot/d/63/75a4de3cae78af2cc6e0766b440d463d_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/3/f8/21381be8fd6bed71a77a3c13e2907f83_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/a/f8/70c1f479b741a60ff38bcbedbb7a2f8a_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/b/2b/d1d7169a45488297c5a3228608c6d2bb_533_320.jpeg\",\"http://img.wdjimg.com/mms/screenshot/2/c1/208580c96aa225e5ae8762a9df145c12_533_320.jpeg\"]},\"screenshotsStr\":\"75a4de3cae78af2cc6e0766b440d463d#800#480#jpeg,21381be8fd6bed71a77a3c13e2907f83#800#480#jpeg,70c1f479b741a60ff38bcbedbb7a2f8a#800#480#jpeg,d1d7169a45488297c5a3228608c6d2bb#800#480#jpeg,208580c96aa225e5ae8762a9df145c12#800#480#jpeg\",\"selectedExtensionPack\":0,\"snippet\":\"《登山赛车》是一款风靡全球的趣味驾车游戏，下载量已超2亿。以真实物理特性为操作基础，丰富的关卡场景和功能各异的车型，不仅增加了游戏的耐玩性，还能让玩家淋漓尽致地体验绝妙的驾驶乐趣。玩家可以对爱车的引擎、悬挂、轮胎及四驱系统进行升级，引擎升级时还能听到逼真的轰鸣音效。\",\"stat\":{\"daily\":[{\"date\":1428422400000,\"downloadCount\":1046,\"downloadCountStr\":\"1046 \"},{\"date\":1428508800000,\"downloadCount\":1096,\"downloadCountStr\":\"1096 \"},{\"date\":1428595200000,\"downloadCount\":4614,\"downloadCountStr\":\"4614 \"},{\"date\":1428681600000,\"downloadCount\":7291,\"downloadCountStr\":\"7291 \"},{\"date\":1428768000000,\"downloadCount\":7748,\"downloadCountStr\":\"7748 \"},{\"date\":1428854400000,\"downloadCount\":4739,\"downloadCountStr\":\"4739 \"},{\"date\":1428940800000,\"downloadCount\":4827,\"downloadCountStr\":\"4827 \"}],\"total\":729311,\"totalStr\":\"73 万\",\"weekly\":31361,\"weeklyCommentsCount\":18,\"weeklyCommentsCountStr\":\"18 \",\"weeklyStr\":\"3.1 万\"},\"tagline\":\"上手容易\",\"tags\":[{\"tag\":\"跑酷竞速\",\"weight\":2},{\"tag\":\"休闲时间\",\"weight\":2},{\"tag\":\"赛车\",\"weight\":2},{\"tag\":\"益智\",\"weight\":2},{\"tag\":\"跑酷\",\"weight\":0},{\"tag\":\"卡通\",\"weight\":0},{\"tag\":\"竞速\",\"weight\":0},{\"tag\":\"联运\",\"weight\":0},{\"tag\":\"物理\",\"weight\":0},{\"tag\":\"体育竞速\",\"weight\":0},{\"tag\":\"追求\",\"weight\":0},{\"tag\":\"好玩的\",\"weight\":0},{\"tag\":\"休闲益智\",\"weight\":0},{\"tag\":\"上瘾\",\"weight\":0}],\"title\":\"登山赛车\",\"titleEn\":null,\"updatedDate\":1428631277000}";


	std::string message = "{\"ad\":false,\"adPosition\":null,\"adType\":null,\"alias\":\"\",\"apkObbs\":[],\"apks\":[{\"adsType\":\"NONE\",\"beta\":false,\"brief\":null,\"bytes\":15409841,\"compatible\":1,\"creation\":1427970464000,\"dangerousPermissions\":[\"发送短信（此操作可能需要付费）\",\"读取短信或彩信\",\"访问联系人数据\"],\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.cmge.xianjian.wdj?uid=70045767\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"},\"downloadUrls\":[{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.cmge.xianjian.wdj?uid=70045767\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"}],\"featuresInfo\":787586,\"gameSdkVersion\":null,\"gsfType\":0,\"id\":13378544,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"6e53c3cf841507806d492d78742d9e55\",\"minSdkVersion\":8,\"official\":1,\"packageName\":\"com.doudizhu.mainhuanle\",\"paidType\":\"NONE\",\"permissionGroups\":\"通讯录/短信/设备和应用历史记录/身份/照片/媒体/文件/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"TRUSTED\",\"permissionStatement\":\"短信用于验证码，通讯录用于邀请好友。\",\"permissions\":[\"显示系统级警报\",\"读取USB存储设备（例如：SD卡）中的内容\",\"查找设备上的帐户\",\"从互联网接收数据\",\"控制振动器\",\"查看 Wi-Fi 状态\",\"添加或移除帐户\",\"读取短信或彩信\",\"下载文件而不显示通知\",\"检索当前运行的应用程序\",\"访问联系人数据\",\"修改或删除USB存储设备中的内容\",\"读取手机状态和身份\",\"发送短信（此操作可能需要付费）\",\"创建帐户并设置密码\",\"修改全局系统设置\",\"查看网络状态\",\"防止手机休眠\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"SAFE\"}],\"securityStatus\":\"SAFE\",\"signature\":\"5e78932d2878f6788d866294ed6ac491\",\"size\":\"14.7M\",\"superior\":1,\"targetSdkVersion\":16,\"verified\":2,\"versionCode\":1,\"versionName\":\"1.0.3\"}],\"appType\":\"GAME\",\"award\":{\"authorDesc\":null,\"authorLink\":null,\"authorName\":null,\"banner\":null,\"blogImage\":null,\"blogLink\":null,\"blogTitle\":null,\"comment\":null,\"creation\":null,\"issue\":null,\"markdownComment\":null,\"modification\":null},\"banner\":null,\"broadTerms\":null,\"categories\":[{\"alias\":\"ol\",\"level\":1,\"name\":\"网络游戏\",\"type\":\"GAME\"},{\"alias\":\"rpg\",\"level\":1,\"name\":\"角色扮演\",\"type\":\"GAME\"},{\"alias\":null,\"level\":2,\"name\":\"武侠\",\"type\":\"GAME\"}],\"changelog\":\"无\",\"commentsCount\":461,\"cooperator\":false,\"defaultVersionCode\":1,\"description\":\"中国手游和大宇联合研发的《新仙剑奇侠传》3D重制版震撼来袭！永恒仙侠经典，全新精彩体验。李逍遥、赵灵儿、林月如等耳熟能详的角色悉数登场。仙剑系列御用配音团队倾情献声。超萌Q版3D，全程语音对白，100%原味呈现二十年爱恨情愁经典剧情。经典回合战斗、守护灵兽全程助阵。五灵炼化、剑灵锻造、御剑飞行，更有百种绝技助你仗剑江湖为红颜。新仙剑，给您新的感动。\",\"detailParam\":\"pos=m/games/index/detail/section/999978:198412400\",\"developer\":{\"email\":null,\"id\":70045767,\"intro\":null,\"name\":\"天津随悦科技有限公司\",\"urls\":null,\"verified\":null,\"website\":null,\"weibo\":null},\"dislikesCount\":68,\"downloadCount\":431039,\"downloadCountStr\":\"43 万\",\"editorComment\":\"3D官方正版手游，全程【光合积木】御用配音，百余【仙剑人物】回归，创新3D战斗【御剑飞行】。二十年仙剑情缘，感动从“新”开始！\",\"exclusiveBadge\":0,\"extensionPacks\":[],\"extra\":{},\"game\":{\"basic\":{\"crashWithoutGsf\":-1,\"gameId\":100044965,\"inAppPurchase\":-1,\"isOnlineGame\":1,\"language\":\"CHS\",\"needNetwork\":1,\"packageName\":\"com.cmge.xianjian.wdj\"},\"developer\":null,\"extraProfile\":{\"coverImage\":{\"url\":null},\"userNotice\":null},\"review\":null,\"sectionProfile\":{\"longRecommWord\":\"逍遥哥哥，灵儿正在等你呢！\",\"shortRecommWord\":\"仙剑情怀感动重温\"},\"tags\":[{\"color\":{\"normal\":\"9D23C6\",\"pressed\":\"761A94\"},\"configUrl\":\"http://games.wandoujia.com/api/v1/game/vertical/tag/game/list/config/get?tagId=100002257&sortType=UNKNOWN\",\"icon\":\"http://img.wdjimg.com/image/game/9600793d53328568540b88629c19fcaa_250_250.png\",\"tagId\":100002257,\"tagName\":\"角色扮演\",\"tagType\":0,\"weight\":2},{\"color\":{\"normal\":\"34CBD2\",\"pressed\":\"27989D\"},\"configUrl\":\"http://games.wandoujia.com/api/v1/game/vertical/tag/game/list/config/get?tagId=100002261&sortType=UNKNOWN\",\"icon\":\"http://img.wdjimg.com/image/game/32d955c0be18b5ae78aec62a3e5393d2_250_250.png\",\"tagId\":100002261,\"tagName\":\"卡牌\",\"tagType\":0,\"weight\":2},{\"color\":{\"normal\":\"FF9D52\",\"pressed\":\"BF763D\"},\"configUrl\":\"http://games.wandoujia.com/api/v1/game/vertical/tag/game/list/config/get?tagId=100002295&sortType=UNKNOWN\",\"icon\":\"http://img.wdjimg.com/image/game/9cd4d2af559935702a72f4f0d6b51f58_250_250.png\",\"tagId\":100002295,\"tagName\":\"仙侠\",\"tagType\":1,\"weight\":2},{\"color\":{\"normal\":\"E97BAC\",\"pressed\":\"AF5C81\"},\"configUrl\":\"http://games.wandoujia.com/api/v1/game/vertical/tag/game/list/config/get?tagId=100002335&sortType=UNKNOWN\",\"icon\":null,\"tagId\":100002335,\"tagName\":\"Q版\",\"tagType\":2,\"weight\":1},{\"color\":{\"normal\":\"5AE4E9\",\"pressed\":\"43ABAF\"},\"configUrl\":\"http://games.wandoujia.com/api/v1/game/vertical/tag/game/list/config/get?tagId=100002334&sortType=UNKNOWN\",\"icon\":null,\"tagId\":100002334,\"tagName\":\"3D\",\"tagType\":2,\"weight\":2}],\"trailer\":null},\"icons\":{\"px48\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_48_48.png\",\"px100\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_100_100.png\",\"px256\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_256_256.png\",\"px78\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_78_78.png\",\"px24\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_24_24.png\",\"px68\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_68_68.png\",\"px36\":\"http://img.wdjimg.com/mms/icon/v1/6/7a/a86ed39ff1d0048049665bcd466ab7a6_36_36.png\"},\"iconsStr\":\"a86ed39ff1d0048049665bcd466ab7a6#512#512#png\",\"id\":3178160,\"imprUrl\":null,\"installedCount\":204168,\"installedCountStr\":\"20 万\",\"itemStatus\":1,\"latestApk\":{\"adsType\":\"NONE\",\"beta\":false,\"brief\":null,\"bytes\":15409841,\"compatible\":null,\"creation\":1427970464000,\"dangerousPermissions\":[\"发送短信（此操作可能需要付费）\",\"读取短信或彩信\",\"访问联系人数据\"],\"developerId\":null,\"downloadUrl\":{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.cmge.xianjian.wdj?uid=70045767\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"},\"downloadUrls\":[{\"aggrWeight\":300,\"market\":\"官方\",\"referUrl\":\"http://apps.wandoujia.com/apps/com.cmge.xianjian.wdj?uid=70045767\",\"url\":\"http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android\"}],\"featuresInfo\":787586,\"gameSdkVersion\":null,\"gsfType\":0,\"id\":13378544,\"incompatibleDetail\":null,\"itemStatus\":\"SHOW\",\"langType\":null,\"language\":[],\"maxSdkVersion\":0,\"md5\":\"6bffebb283b319ee23949c571c97f985\",\"minSdkVersion\":8,\"official\":1,\"packageName\":\"com.doudizhu.mainhuanle\",\"paidType\":\"NONE\",\"permissionGroups\":\"通讯录/短信/设备和应用历史记录/身份/照片/媒体/文件/WLAN 网络连接信息/设备 ID 和通话信息/其他\",\"permissionLevel\":\"TRUSTED\",\"permissionStatement\":\"短信用于验证码，通讯录用于邀请好友。\",\"permissions\":[\"显示系统级警报\",\"读取USB存储设备（例如：SD卡）中的内容\",\"查找设备上的帐户\",\"从互联网接收数据\",\"控制振动器\",\"查看 Wi-Fi 状态\",\"添加或移除帐户\",\"读取短信或彩信\",\"下载文件而不显示通知\",\"检索当前运行的应用程序\",\"访问联系人数据\",\"修改或删除USB存储设备中的内容\",\"读取手机状态和身份\",\"发送短信（此操作可能需要付费）\",\"创建帐户并设置密码\",\"修改全局系统设置\",\"查看网络状态\",\"防止手机休眠\"],\"resolution\":[\"ldpi\",\"mdpi\",\"hdpi\"],\"securityDetail\":[{\"failedInfo\":null,\"provider\":\"tencent\",\"status\":\"SAFE\"}],\"securityStatus\":\"SAFE\",\"signature\":\"5e78932d2878f6788d866294ed6ac491\",\"size\":\"14.7 M\",\"superior\":1,\"targetSdkVersion\":16,\"verified\":2,\"versionCode\":1,\"versionName\":\"1.0.3\"},\"likesCount\":304,\"likesRate\":82,\"negComments\":[],\"packageName\":\"com.doudizhu.mainhuanle\",\"posComments\":[],\"publishDate\":1428373918000,\"publishNoticeBean\":null,\"reputationScore\":81,\"screenshots\":{\"small\":[\"http://img.wdjimg.com/mms/screenshot/c/e7/162b56ce2875ea7188487873a4390e7c_200_333.jpeg\",\"http://img.wdjimg.com/mms/screenshot/f/31/08d20d18bd8e49ba930afbe568f9d31f_200_333.jpeg\",\"http://img.wdjimg.com/mms/screenshot/4/e3/b549a25f94da647aab9ad74a3d2e1e34_200_333.jpeg\",\"http://img.wdjimg.com/mms/screenshot/e/5b/566e6625da357cdc4f8aface4befe5be_200_333.jpeg\",\"http://img.wdjimg.com/mms/screenshot/8/ad/46cbfb228a837019255f649561657ad8_200_333.jpeg\"],\"normal\":[\"http://img.wdjimg.com/mms/screenshot/c/e7/162b56ce2875ea7188487873a4390e7c_320_533.jpeg\",\"http://img.wdjimg.com/mms/screenshot/f/31/08d20d18bd8e49ba930afbe568f9d31f_320_533.jpeg\",\"http://img.wdjimg.com/mms/screenshot/4/e3/b549a25f94da647aab9ad74a3d2e1e34_320_533.jpeg\",\"http://img.wdjimg.com/mms/screenshot/e/5b/566e6625da357cdc4f8aface4befe5be_320_533.jpeg\",\"http://img.wdjimg.com/mms/screenshot/8/ad/46cbfb228a837019255f649561657ad8_320_533.jpeg\"]},\"screenshotsStr\":\"162b56ce2875ea7188487873a4390e7c#480#800#jpeg,08d20d18bd8e49ba930afbe568f9d31f#480#800#jpeg,b549a25f94da647aab9ad74a3d2e1e34#480#800#jpeg,566e6625da357cdc4f8aface4befe5be#480#800#jpeg,46cbfb228a837019255f649561657ad8#480#800#jpeg\",\"selectedExtensionPack\":0,\"snippet\":\"永恒仙侠经典，全新精彩体验。！超萌Q版3D，全程语音对白，100%原味呈现二十年爱恨情愁经典剧情。经典回合战斗、守护灵兽全程助阵。\",\"stat\":{\"daily\":[{\"date\":1428508800000,\"downloadCount\":31933,\"downloadCountStr\":\"3.2 万\"},{\"date\":1428595200000,\"downloadCount\":67205,\"downloadCountStr\":\"6.7 万\"},{\"date\":1428681600000,\"downloadCount\":91557,\"downloadCountStr\":\"9.2 万\"},{\"date\":1428768000000,\"downloadCount\":89004,\"downloadCountStr\":\"8.9 万\"},{\"date\":1428854400000,\"downloadCount\":51946,\"downloadCountStr\":\"5.2 万\"},{\"date\":1428940800000,\"downloadCount\":47959,\"downloadCountStr\":\"4.8 万\"},{\"date\":1429027200000,\"downloadCount\":48018,\"downloadCountStr\":\"4.8 万\"}],\"total\":431039,\"totalStr\":\"43 万\",\"weekly\":427622,\"weeklyCommentsCount\":453,\"weeklyCommentsCountStr\":\"453 \",\"weeklyStr\":\"43 万\"},\"tagline\":\"3D官方正版\",\"tags\":[{\"tag\":\"网络游戏\",\"weight\":2},{\"tag\":\"角色扮演\",\"weight\":2},{\"tag\":\"武侠\",\"weight\":2},{\"tag\":\"联运\",\"weight\":0}],\"title\":\"新仙剑奇侠传\",\"titleEn\":null,\"updatedDate\":1428377149000}";
	base_logic::LogicComm::SendFull(socket,message.c_str(),message.length());

	/*std::string pnname = "com.og.danjiddz";
	std::string key = ".wandoujia";
	std::string message;
	OnReplaceAppSummary(key,pnname);
	base_logic::LogicComm::SendFull(socket,message.c_str(),message.length());
	*/
	return true;
}

void Hacklogic::OnQueueGetAppSummary(){
	std::string queue_key = "GET_APPINFO_TASK_QUEUE";
	std::string key = ".wandoujia";
	bool r = false;
	char* value = NULL;
	size_t value_len = 0;
	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
	r = redis_engine_->PopListElement(queue_key.c_str(),queue_key.length(),&value,&value_len,1);
	if(!r)
		return;
	if(value){
		std::string pnname;
		pnname.assign(value,value_len);
		LOG_DEBUG2("%s",pnname.c_str());
		if(value_len<128&&value_len>4)
			OnReplaceAppSummary(key,pnname);
		delete[] value;
	}

}

bool Hacklogic::OnReplaceAppSummary(const std::string& key,const std::string& pnname){
	//com.carrot.iceworld.wandoujia
	std::string key_str;
	bool r = false;
	std::stringstream os;
	std::string result;
	os<<pnname.c_str()<<".wandoujia";
	key_str = os.str();
	r = OnReplaceAppSummaryUnit(pnname,result);
	if(r){//写入reids
		base_dic::AutoDicCommEngine auto_engine;
		base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
		LOG_DEBUG2("key:%s",key_str.c_str());
		//ßLOG_DEBUG2("value: %s",result.c_str());
		r = redis_engine_->SetValue(key_str.c_str(),key_str.length(),result.c_str(),result.length());
	}
	return true;
}

bool Hacklogic::OnReplaceAppSummaryUnit(const std::string& pnname,std::string& result){
	std::string content;
	//std::string result;
	bool r = false;
	hacksvc_logic::AppSummaryParam param;
	param.set_pnname(pnname);
	r = OnRequestAppSummary(param,content);
	if(!r)
		return false;

	//解析json
	std::string alias;
	base_logic::DictionaryValue* value = AppSummarySerialzer(content);
	OnExectReplaceSummary(value);

	//序列化数据
	AppSummaryUnSerialzer(value,result);
	return true;
}

bool Hacklogic::OnRequestAppSummary(hacksvc_logic::AppSummaryParam& param,std::string& content){
	//请求豌豆荚详细信息
	bool r = false;
	std::string url;
	std::stringstream os;
	/*
	 * http://api.wandoujia.com/v1/apps/com.og.danjiddz?timestamp=1428992136630&id=wandoujia_android&f=phoenix2&v=4.25.1&u=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&max=20&start=0&token=f0ca1ccc1a60ef3e0ce6105b353ab762&vc=7955&ch=wandoujia_wap&net=WIFI&pos=m/games/index/section/0:198412830
	 */
	os<<"http://api.wandoujia.com/v1/apps/"<<param.pnname().c_str()<<"?timestamp=1428992136630&id=wandoujia_android&f=phoenix2&v=4.25.1&u=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&max=20&start=0&token=f0ca1ccc1a60ef3e0ce6105b353ab762&vc=7955&ch=wandoujia_wap&net=WIFI&pos=m/games/index/section/0:198412830";
	url = os.str();
	return wandoujia_appstore_connector_engine_->OnRequestAppStoreInfo(url,content);
}

base_logic::DictionaryValue* Hacklogic::AppSummarySerialzer(std::string& content){
	std::string error_str;
	int jerror_code = 0;
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	base_logic::DictionaryValue*  value = (base_logic::DictionaryValue* )serializer->Deserialize(&jerror_code,&error_str);
	return value;
}

void Hacklogic::AppSummaryUnSerialzer(base_logic::DictionaryValue* value,std::string& content){
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	serializer->Serialize(*value);
}

bool Hacklogic::OnExectReplaceSummary(base_logic::DictionaryValue* value){
	bool r = false;
	/*std::string package_name = "com.doudizhu.mainhuanle";
	int64 bytes = 15409841;
	std::string down_url = "http://121.40.191.137/3.php?signature=5ff7123&url=http%3a%2f%2f121.40.191.137%2fcpa30.happy.2837.apk&pn=com.doudizhu.mainhuanle&md5=6bffebb283b319ee23949c571c97f985&apkid=13589702&vc=22&size=15409841&pos=m/games/index/detail/section/999978:198412830&udid=c8fe4ccbc270487f88efb6ff063b36c01a998309&tokenId=wandoujia_android";
	std::string md5 = "6e53c3cf841507806d492d78742d9e55";*/
	std::string package_name = "${PACKAGENAME}";
	int64 bytes = -1;
	std::string down_url = "${URL}";
	std::string md5 = "${MD5}";
	base_logic::Value* apk_list;
	r = value->GetWithoutPathExpansion(L"apks",&apk_list);
	if(!r)
		return false;

	/////apks/////////////////////////////////////////////////////////////////
	base_logic::ListValue* apks_list = (base_logic::ListValue*)apk_list;
	base_logic::DictionaryValue* apks;
	r = apks_list->GetDictionary(0,&apks);
	if(!r)
		return false;
	apks->SetBigInteger(L"bytes",bytes);

	base_logic::DictionaryValue* downloadurl;
	r = apks->GetDictionary(L"downloadUrl",&downloadurl);
	if(!r)
		return false;

	downloadurl->SetString(L"url",down_url);


	//list
	base_logic::Value* download_list;
	r = apks->GetWithoutPathExpansion(L"downloadUrls",&download_list);
	if(!r)
		return false;
	//循环替换
	base_logic::ListValue* downloads_list = (base_logic::ListValue* )download_list;
	int32 size = downloads_list->GetSize();
	int32 i = 0;
	while(i < size){
		base_logic::DictionaryValue* download_unit;
		r = downloads_list->GetDictionary(i,&download_unit);
		if(r)
			download_unit->SetString(L"url",down_url);
		i++;
	}
	apks->SetString(L"md5",md5);
	apks->SetString(L"packageName",package_name);
	/////apks/////////////////////////////////////////////////////////////////


	/////lastestApk/////////////////////////////////////////////////////////////////
	base_logic::DictionaryValue* latest_apk;
	r = value->GetDictionary(L"latestApk",&latest_apk);
	if(!r)
		return false;
	latest_apk->SetBigInteger(L"bytes",bytes);

	base_logic::DictionaryValue* latest_downloadurl;
	r = latest_apk->GetDictionary(L"downloadUrl",&latest_downloadurl);
	if(!r)
		return false;

	latest_downloadurl->SetString(L"url",down_url);


	//list
	base_logic::Value* latest_download_list;
	r = latest_apk->GetWithoutPathExpansion(L"downloadUrls",&latest_download_list);
	if(!r)
		return false;
	//循环替换
	base_logic::ListValue* latest_downloads_list = (base_logic::ListValue* )latest_download_list;
	size = latest_downloads_list->GetSize();
	i = 0;
	while(i < size){
		base_logic::DictionaryValue* latest_download_unit;
		r = downloads_list->GetDictionary(i,&latest_download_unit);
		if(r)
			latest_download_unit->SetString(L"url",down_url);
		i++;
	}
	latest_apk->SetString(L"md5",md5);
	latest_apk->SetString(L"packageName",package_name);

	/////lastestApk/////////////////////////////////////////////////////////////////
	value->SetString(L"packageName",package_name);
}

}

