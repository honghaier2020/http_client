// http_client_test.cpp : 定义控制台应用程序的入口点。
//

#include "HttpClient.h"
#include <tchar.h>
#include <windows.h>
#include <thread>
#include <mutex>
#include "jansson.h"
using namespace  network;

static std::mutex       s_post_mutex;
#ifndef __CLOUD_BOX
//#define __CLOUD_BOX
#endif //__CLOUD_BOX

#ifndef __CLOUD_BOX_FORMAL
//#define __CLOUD_BOX_FORMAL
#endif //__CLOUD_BOX_FORMAL

#ifdef __CLOUD_BOX
	#ifdef __CLOUD_BOX_FORMAL
	#define HTTP_URL		"server.wscs.appget.cn:20000/"
	//#define HTTP_URL		"server.wwcs.appget.cn:20100/"
	#else
	#define HTTP_URL		"http://117.121.32.94:20000/"
	//#define HTTP_URL		"http://61.91.14.68:20000/"	
	#endif //__CLOUD_BOX_FORMAL
#else
#define HTTP_URL		"http://192.168.22.66:20000/"
//#define HTTP_URL		"http://192.168.1.74:20000/"
#endif // __CLOUD_BOX

#ifndef __ALI
//#define __ALI
#endif //__ALI

#ifdef __ALI
#define HTTP_URL2	"http://115.29.42.238:5000/" 
#else
#define HTTP_URL2	"http://192.168.22.66:5000/"
#endif //__ALI


#define HTTP_URL3   "http://192.168.22.66:20003/"
//#define HTTP_URL3   "http://117.121.32.94:20003/"
//#define HTTP_URL3   "http://61.91.14.68:20003/"

std::wstring _AnsiToUnicode( const std::string& val )
{
	size_t len = 0;
	len = val.length();
	int unicodeLen = ::MultiByteToWideChar( CP_ACP, 0, val.c_str(), -1, NULL, 0 ); 
	wchar_t * unicode; 
	unicode = new wchar_t[unicodeLen+1]; 
	memset(unicode,0,(unicodeLen+1)*sizeof(wchar_t)); 
	::MultiByteToWideChar( CP_ACP, 0, val.c_str(), -1, (wchar_t*)unicode, unicodeLen ); 
	std::wstring rt; 
	rt = ( wchar_t* )unicode;
	delete unicode; 
	return rt; 
}

std::string _UnicodeToUTF8( const std::wstring& val )
{
	char* element_text;
	int    text_len;
	// wide char to multi char
	text_len = ::WideCharToMultiByte( CP_UTF8, 0, val.c_str(), -1, NULL, 0, NULL, NULL );
	element_text = new char[text_len + 1];
	memset( ( void* )element_text, 0, sizeof( char ) * ( text_len + 1 ) );
	::WideCharToMultiByte( CP_UTF8, 0, val.c_str(), -1, element_text, text_len, NULL, NULL );
	std::string strText;
	strText = element_text;
	delete[] element_text;
	return strText;
}

class HttpClientTest : public Ref
{
public:
	HttpClientTest() {}

	~HttpClientTest(){}

	void initThread();

	void postThread();
	//	test http_server,http component for login
	void post1();
	
	void post3();

	//	test for mail
	void post4();

	void post5();

	void post6();

	void post7();

	void post8();

	void post13();

	void post9();

	void post15();

	void post16();

	void post17();

	void post18();

	void post19();

	void post20();

	void post21();

	void post22();

	void post23();

	void post24();

	void post25();

	void post26();

	void post27();

	void post28();

	void post29();

	//	test for wanli
	void test_participle();

	void test_voice_query(const char* __query);

	void test_voice_query_f_wechat(const char* __query);

	void test_set_colour();

	void test_get_colour();

	void test_get_energy();

	void test_get_support_question();

	void test_give_away_bless();

	void test_get_bless();

	void test_modify_info();

	void test_modify_info_4_wechat();

	void test_feedback();

	void test_get_user_info();

	void test_set_device_token();

	void test_contracts();

	void test_attentions();

	void test_compass();

	void test_select_date();

	void test_match();

	void test_prediction();

	void test_user_query();

	void test_user_query_4_wechat();

	void test_add_bless();

	void test_reg_4_wechat();

	void test_push_4_index();

	void test_push_4_friend();

	void test_push_4_login();

	void test_get_luck();

	void test_express_register();

	void test_express_login();

	void test_pay_for_fly_flow();

	void test_pay_for_fly_flow_verify();
	
	//Http Response Callback
	void onHttpRequestCompleted(network::HttpClient *sender, network::HttpResponse *response);

};

void HttpClientTest::post1()
{
	if(0)
	{
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://httpbin.org/post");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

		// write the post data
		char postData[22] = "binary=hello\0\0cocos2d";  // including \0, the strings after \0 should not be cut in response
		request->setRequestData(postData, 22); 

		request->setTag("POST Binary test");
		HttpClient::getInstance()->send(request);
		request->release();
	}
	else
	{
		try 
		{
			s_post_mutex.lock();
			//	post data to http server
			std::string __string_account = "&account=king_lee";
			std::string __string_msg = "msg=";
			json_t* __msg = json_object();
			json_t* __msg_id = json_integer(/*MSG_ID::MSG_LOGIN*/2);
			json_t* __msg_context = json_string("context");
			json_object_set(__msg, "msg_id", __msg_id);
			json_object_set(__msg, "context", __msg_context);


			HttpRequest* request = new HttpRequest();
			request->setUrl("http://192.168.22.61:3001/");
			std::vector<std::string> __head;
			__head.push_back("Content-Type: application/json; charset=utf-8");
			request->setHeaders(__head);
			request->setRequestType(HttpRequest::Type::POST);
			request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

			// write the post data
			const char* postData = json_dumps(__msg,0);
			if(postData)
			{
				//	msg={"context": "context", "msg_id": 2}
				__string_msg  += postData;
				__string_msg += __string_account;
				request->setRequestData(__string_msg.c_str(), __string_msg.length());
			}
			request->setTag("POST test1\n");
			HttpClient::getInstance()->send(request);
			request->release();

#if 1
			json_error_t* __json_error = NULL;
			json_t* __json_loads = json_loads(postData,JSON_DECODE_ANY,__json_error);
			json_t* __json_loads_msg_id = json_object_get(__json_loads,"msg_id");
			json_t* __json_loads_msg_context = json_object_get(__json_loads,"context");
			json_int_t __json_int_msg_id = json_integer_value(__json_loads_msg_id);
			const char* __json_string_msg_context = json_string_value(__json_loads_msg_context);
#endif
			// decref for json object
			json_decref(__msg_id);
			s_post_mutex.unlock();
		}
		catch(std::exception & __exception)
		{
			printf("exception : %s\n",__exception.what());
			s_post_mutex.unlock();
		}
	}
}

void HttpClientTest::post3()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_MSG_GET_SRV_TIME:*/3);
	json_t* __flow_id = json_integer(88888888);
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test3\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
	json_decref(__flow_id);
}

void HttpClientTest::post4()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_MSG_MAIL:*/4);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_title = json_string("title");
	json_t* __msg_content = json_string("content");
	json_t* __msg_channel = json_string("qihu360");
	json_t* __msg_version = json_string("1.1.0");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "title", __msg_title);
	json_object_set(__msg, "content", __msg_content);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test4\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

static std::string __device_guid = "043ae1a1-612b-14bf-8000-19c9000018c9-31";
static int __race_time = 99745;
void HttpClientTest::post5()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_ACTIVITY*/5);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __activity_type = json_integer(3);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.0.0");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "activity_type", __activity_type);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "player_guid", __msg_device_guid);
	json_object_set(__msg, "deviceid", __msg_device_guid);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test5\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post6()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_NOTICE*/6);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.2.6");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test6\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post7()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_UPLOAD_RACE_TIME*/7);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.2.6");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_race_time = json_integer(__race_time);
	json_t* __msg_car = json_integer(1);
	json_t* __msg_car_level = json_integer(2);
	json_t* __msg_driver = json_integer(3);
	json_t* __msg_driver_level = json_integer(4);
	json_t* __msg_phone_number = json_string("18510384228");
	json_t* __msg_championship_id = json_integer(1);
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "race_time", __msg_race_time);
	json_object_set(__msg, "car", __msg_car);
	json_object_set(__msg, "car_level", __msg_car_level);
	json_object_set(__msg, "driver", __msg_driver);
	json_object_set(__msg, "driver_level", __msg_driver_level);
	json_object_set(__msg, "phone_number", __msg_phone_number);
	json_object_set(__msg, "championship_id", __msg_championship_id);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test7\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post8()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_RACE_RANK*/8);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.2.6");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_championship_id = json_integer(1);
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "championship_id", __msg_championship_id);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test8\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post9()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_PAY_FOR_FLY_FLOW*/14);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.2.8");
	json_t* __orderid = json_string("222222");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "orderid", __orderid);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test8\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post13()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_RANDOM_PRIZE*/13);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.2.8");
	json_t* __single_gacha = json_string("false");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "player_guid", __msg_device_guid);
	json_object_set(__msg, "single_gacha", __single_gacha);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test13\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post15()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_UPLOAD_RACE_TIME_FOR_RUNNING_MAN*/15);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.0.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_boss_rank = json_integer(4);
	json_t* __msg_mine_rank = json_integer(1);
	json_t* __msg_phone_number = json_string("18510384228");
	json_t* __msg_is_increase_level = json_string("true");
	json_t* __msg_is_add_score = json_string("false");
	json_t* __msg_distance_ahead_2nd = json_string("100000");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "boss_rank", __msg_boss_rank);
	json_object_set(__msg, "my_rank", __msg_mine_rank);
	json_object_set(__msg, "phone_number", __msg_phone_number);
	json_object_set(__msg, "is_increase_level", __msg_is_increase_level);
	json_object_set(__msg, "is_add_score", __msg_is_add_score);
	json_object_set(__msg, "distance_ahead_2nd", __msg_distance_ahead_2nd);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test15\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}


void HttpClientTest::post16()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_RIVAL*/16);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.2.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_boss_res = json_string("car_370z_s");
	json_t* __msg_boss_id = json_string("1");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "boss_id", __msg_boss_id);
	json_object_set(__msg, "boss_res", __msg_boss_res);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test16\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post17()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_RACE_RANK_FOR_RUNNING_MAN*/17);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.1.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test17\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post18()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_AWARD_FOR_RUNNING_MAN*/18);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.0.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test18\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post19()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_UPDATE_PHONE_FOR_RUNNING_MAN*/19);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.3.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_phone_number = json_string("185103842281");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "phone_number", __msg_phone_number);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test19\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post20()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_RANDOM_PRIZE*/20);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.2.0");
	json_t* __single_gacha = json_string("false");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "player_guid", __msg_device_guid);
	json_object_set(__msg, "single_gacha", __single_gacha);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test20\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post21()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_VERSION_UPDATE*/21);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.2.0");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST post21\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post22()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_RANK_INFO_FOR_PVP*/22);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.2.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());

#define __SET

#if defined __SET
	json_t* __msg_type = json_string("set");
#elif defined __GET
	json_t* __msg_type = json_string("get");
#elif defined __UPDATE
	json_t* __msg_type = json_string("update");
#endif
	json_t* __msg_area = json_string("Beijing2");
	json_t* __msg_phone_number = json_string("1851");
	std::string __nick_name("屏蔽卡不死你");
	__nick_name = _UnicodeToUTF8(_AnsiToUnicode(__nick_name));
	json_t* __msg_nickname = json_string(__nick_name.c_str());

	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "type", __msg_type);
#if defined __SET
	json_object_set(__msg, "nickname", __msg_nickname);
	json_object_set(__msg, "area", __msg_area);
	json_object_set(__msg, "phone_number", __msg_phone_number);
#elif defined __GET
#elif defined __UPDATE
	json_object_set(__msg, "area", __msg_area);
	json_object_set(__msg, "phone_number", __msg_phone_number);
#endif

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST post22\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post23()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_RIVAL_FOR_PVP*/23);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_strength = json_integer(450);

	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "strength", __msg_strength);


	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST post23\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post24()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_UPLOAD_SCORE_FOR_PVP*/24);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_t* __msg_car = json_integer(3);
	json_t* __msg_car_lv = json_integer(1);
	json_t* __msg_racer = json_integer(1);
	json_t* __msg_racer_lv = json_integer(1);
	json_t* __msg_strength = json_integer(200);
	json_t* __msg_my_rank = json_integer(1);
	json_t* __msg_win_flag = json_string("true");
	json_t* __msg_rivals = json_array();
	for (int __i = 0; __i < 3; ++__i)
	{
		json_t* __msg_inner = json_object();
		json_object_set(__msg_inner, "strength", json_integer((__i + 1)*100));
		json_object_set(__msg_inner, "rank", json_integer(__i + 1));
		json_array_append_new(__msg_rivals, __msg_inner);
	}

	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "car", __msg_car);
	json_object_set(__msg, "car_lv", __msg_car_lv);
	json_object_set(__msg, "racer", __msg_racer);
	json_object_set(__msg, "racer_lv", __msg_racer_lv);
	json_object_set(__msg, "strength", __msg_strength);
	json_object_set(__msg, "my_rank", __msg_my_rank);
	json_object_set(__msg, "win_flag", __msg_win_flag);
	json_object_set(__msg, "rivals", __msg_rivals);
	

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST post24\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post25()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_AWARD_FOR_PVP*/25);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test25\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post26()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_GET_RANK_PARTIAL_FOR_PVP*/26);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);

	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test26\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post27()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_RANDOM_PRIZE_THE_THIRD_PHASE*/27);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __single_gacha = json_string("false");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "player_guid", __msg_device_guid);
	json_object_set(__msg, "single_gacha", __single_gacha);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test27\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}


void HttpClientTest::post28()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_UPDATE_PHONE_FOR_RANDOM_PRIZE_THE_THIRD_PHASE*/28);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __phone_number = json_string("18510384228");
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "phone_number", __phone_number);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST test28\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post29()
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(/*TYPE_ADD_SCORE_FOR_DEBUG_PVP*/29);
	json_t* __flow_id = json_integer(88888888);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("2.3.0");
	json_t* __add_score = json_integer(1000);
	json_t* __msg_device_guid = json_string(__device_guid.c_str());
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "channel", __msg_channel);
	json_object_set(__msg, "version", __msg_version);
	json_object_set(__msg, "deviceid", __msg_device_guid);
	json_object_set(__msg, "add_score", __add_score);
	HttpRequest* request = new HttpRequest();
	request->setUrl(HTTP_URL);
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	const char* postData = json_dumps(__msg,0);
	if(postData)
	{
		__string_msg  += postData;
		__string_msg += __string_token;
		request->setRequestData(__string_msg.c_str(), __string_msg.length());
	}
	request->setTag("POST post29\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::onHttpRequestCompleted( network::HttpClient *sender, network::HttpResponse *response )
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag())) 
	{
		printf("%s completed ", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	printf("response code: %ld", statusCode);

	if (!response->isSucceed()) 
	{
		printf("response failed");
		printf("error buffer: %s", response->getErrorBuffer());
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	printf("Http Test, dump data: \n");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	printf("\n");
}

void HttpClientTest::postThread()
{
	while (true)
	{
		this->post1();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void HttpClientTest::initThread()
{
	const int __max_thread = 1;
	for(int i = 0; i < __max_thread; ++i)
	{
		auto t = std::thread(std::bind(&HttpClientTest::postThread,this));
		t.detach();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void HttpClientTest::test_participle()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "participle";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "content=轻轻的我走了，正如我轻轻的来;我轻轻的招手，作别西天的云彩";
    __str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_participle\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_voice_query(const char* __query)
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "voice_query";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1988&version=1&year=2015&month=0&date=25&voice_content=";
	__str_msg += __query;
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_voice_query\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_voice_query_f_wechat(const char* __query)
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "voice_query_4_wechat";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "openid=yushsjsiskloiuytrq25swqsdieyskwq&voice_content=";
	__str_msg += __query;
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_voice_query_f_wechat\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_get_user_info()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "userinfo";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=27&sex=1&v=1&type=0";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_user_info\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_set_device_token()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "deviceid";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&token=bc64578b96efdee682b1dab5a58008d86e951f1fddc3d89cc0646fdcfcab63f8&os=0";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_set_device_token\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_set_colour()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "set_colour";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&colour=2";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_set_colour\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_get_colour()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "get_colour";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_colour\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_get_energy()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "get_energy";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_energy\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_get_support_question()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "get_support_question";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_support_question\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_give_away_bless()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "give_away_bless";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&name=lee&target_uid=3&bless=20";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_give_away_bless\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_get_bless()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "get_bless";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_bless\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_feedback()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "feedback";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&content=我要留言";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_feedback\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_express_register()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "register";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "user=lee&password=lee&sex=1";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_express_login\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_express_login()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "login";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "user=lee&password=lee";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_express_login\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_modify_info()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "modifyInfo";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&name=King Lee1&pass=164271579&bd=1983040404&sex=1&ba=9";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_set_colour\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_modify_info_4_wechat()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "modify_info_4_wechat";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "openid=1dd23&name=King Lee1&pass=164271579&bd=1983040404&sex=1&ba=9";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_modify_info_4_wechat\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_contracts()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "contacts";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&type=get";
	//std::string __str_msg = "uid=1525&contracts_uid=1128&contracts_name=李希文&type=add";
	//std::string __str_msg = "uid=1525&contracts_uid=1123&type=del";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_contracts\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_attentions()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "attentions";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	//std::string __str_msg = "uid=1525&type=get";
	std::string __str_msg = "uid=1525&attention_uid=1128&type=add";
	//std::string __str_msg = "uid=1525&attention_uid=1123&type=del";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_attentions\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_compass()
{
		//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "compass";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3&type=1";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_compass\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_select_date()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "select_date";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3&select_date_type=0&days_type=1";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_select_date\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_match()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "match";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	//std::string __str_msg = "input_type=0&uid=1525&target_uid=1001&type=0";
	std::string __str_msg = "input_type=1&uid=3111&birthday=1990101010&birthplace=1&sex=0&type=0";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_match\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_prediction()
{
		//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "xianmiao";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&xmtype=7&num0=1&num1=1";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_prediction\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_user_query()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "user_query";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_user_query\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_user_query_4_wechat()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "user_query_4_wechat";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "openid=yushsjsiskloiuytrq25swqsdieyskwq";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_user_query_4_wechat\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_add_bless()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "add_bless";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=1525&bless=15";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_add_bless\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_reg_4_wechat()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "reg_4_wechat";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "openid=yushsjsiskloiuytrq25swqsdieyskwq";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_reg_4_wechat\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_push_4_index()
{
		//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "push_4_index";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST push_4_index\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_push_4_friend()
{
		//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "push_4_friend";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST push_4_friend\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_push_4_login()
{
		//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "push_4_login";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_push_4_login\n");
	HttpClient::getInstance()->send(request);
	request->release();	
}

void HttpClientTest::test_get_luck()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL2;
	__url += "get_luck";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "uid=3&year=2015&month=0&date=15";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_luck\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_pay_for_fly_flow()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL3;
	__url += "fly_flow";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "";
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_pay_for_fly_flow\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

void HttpClientTest::test_pay_for_fly_flow_verify()
{
	//	post data to http server
	HttpRequest* request = new HttpRequest();
	std::string __url = HTTP_URL3;
	__url += "fly_flow_verify";
	request->setUrl(__url.c_str());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

	// write the post data
	std::string __str_msg = "orderid=222222";
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_pay_for_fly_flow_verify\n");
	HttpClient::getInstance()->send(request);
	request->release();
}

int _tmain(int argc, _TCHAR* argv[])
{
	HttpClientTest* __test = new HttpClientTest();
	if(1)
	{
		if(0)
		{
			//__test->test_voice_query("今日情感如何");
			//__test->test_participle();
			//__test->test_voice_query("我今天财富如何");
			//__test->test_voice_query("我本月桃花如何");
			//__test->test_voice_query("我今日能量如何");
			//__test->test_voice_query("我先天助运如何");
			//__test->test_voice_query("我的财运如何");
			//__test->test_voice_query("我今日约会如何");
			//__test->test_voice_query("过去我十年运程如何");
			//__test->test_voice_query("我此时财运如何");
			//__test->test_voice_query("我今日身体如何");
			//__test->test_voice_query("我人生忠告");
			//__test->test_voice_query("我的主要性格特点");
			//__test->test_voice_query("我的主要不足");
			//__test->test_voice_query("我的的次要性格特点");
			//__test->test_voice_query("我的其它不足");
			/*
			__test->test_voice_query("我先天能量如何");
			__test->test_voice_query("我这辈子福报如何");
			__test->test_voice_query("我先天财富如何");

			__test->test_voice_query("我先天桃花如何");

			__test->test_voice_query("过去我十年运程如何");

			__test->test_voice_query("先天情感如何");
			
			__test->test_voice_query("我的海拔高度");
			__test->test_voice_query("今日运程如何");
			__test->test_voice_query("本月运程如何");
			__test->test_voice_query("今年运程如何");
			
			__test->test_voice_query("我本月做事如何");
			__test->test_voice_query("我今天去旅行如何");
			__test->test_voice_query("我今日健康如何");
			__test->test_voice_query("我今日财富如何");
			__test->test_voice_query("我今日破财么");
			__test->test_voice_query("我本月购物如何");
			__test->test_voice_query("我本月学业如何");
			__test->test_voice_query("我今年事业如何");
			__test->test_voice_query("我今日求财如何");
			__test->test_voice_query("我今日情感如何");
			__test->test_voice_query("我今日会友如何");
			__test->test_voice_query("我今日感情变化如何");
			__test->test_voice_query("我今日桃花如何");
			__test->test_voice_query("我今日追求好么");
			__test->test_voice_query("问点什么好呢?");
			__test->test_voice_query("我这天那个方向最顺?");
			*/
			//__test->test_voice_query_f_wechat("我的财运如何");
			//__test->test_get_user_info();
			//__test->test_set_device_token();
			//__test->test_set_colour();
			//__test->test_get_colour();
			//__test->test_get_energy();
			//__test->test_get_support_question();
			//__test->test_give_away_bless();
			//__test->test_get_bless();
			//__test->test_modify_info();
			//__test->test_modify_info_4_wechat();
			//__test->test_feedback();
			//__test->test_contracts();
			//__test->test_attentions();
			//__test->test_compass();
			//__test->test_select_date();
			//__test->test_match();
			//__test->test_prediction();
			//__test->test_user_query();
			//__test->test_user_query_4_wechat();
			//__test->test_add_bless();
			//__test->test_reg_4_wechat();
			//__test->test_push_4_index();
			//__test->test_push_4_friend();
			//__test->test_push_4_login();
			//__test->test_get_luck();
			//__test->test_express_register();
			//__test->test_express_login();
			//__test->post1();

			//	test express

		}
		else
		{
			int __loops = 1;
			for (int __i = 0; __i < __loops; ++__i)
			{

				//	mail
				//__test->post4();
			
				__test->post3();
				__test->post5();
				__test->post6();
				__test->post7();
				__test->post8();
				__test->post13();
				
				if (0)
				{
					//__test->post9();
				}
				else
				{
					//__test->test_pay_for_fly_flow();
					//__test->test_pay_for_fly_flow_verify();
				}

				__test->post15();
				__test->post16();
				__test->post17();
				__test->post18();
				__test->post19();

				__test->post20();
				__test->post21();
				
				//	for pvp
				__test->post22();
				//__test->post23();
				//__test->post24();
				//__test->post25();
				//__test->post26();
				//__test->post27();
				//__test->post28();
				//__test->post29();
			}
		}

	}
	else
	{
		__test->initThread();
	}

	while (true)
	{
		if(1)
		{
			::_sleep(1);
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
	}
	return 0;
}

