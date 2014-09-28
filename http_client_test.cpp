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
#define __CLOUD_BOX
#endif //__CLOUD_BOX

#ifndef __CLOUD_BOX_FORMAL
//#define __CLOUD_BOX_FORMAL
#endif //__CLOUD_BOX_FORMAL

#ifdef __CLOUD_BOX
	#ifdef __CLOUD_BOX_FORMAL
	#define HTTP_URL		"server.wscs.appget.cn:20000/"
	#else
	#define HTTP_URL		"http://117.121.32.94:20000/"
	#endif //__CLOUD_BOX_FORMAL
#else
#define HTTP_URL		"http://192.168.22.61:20000/"
#endif // __CLOUD_BOX

#ifndef __ALI
#define __ALI
#endif //__ALI

#ifdef __ALI
#define HTTP_URL2	"http://115.29.42.238:5000/" 
#else
#define HTTP_URL2	"http://192.168.22.61:5000/"
#endif //__ALI

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

	//	test for faterace
	void post2();

	//	test for mail
	void post3();

	void post4(int __msg_type);

	void post5();

	void post6();

	void post7();

	void post8();

	//	test for wanli
	void test_participle();

	void test_voice_query(const char* __query);

	void test_set_colour();

	void test_modify_info();

	void test_feedback();

	void test_get_user_info();

	void test_contracts();

	void test_compass();

	void test_select_date();

	void test_express_register();

	void test_express_login();
	
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

void HttpClientTest::post2()
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
	request->setTag("POST test2\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
	json_decref(__flow_id);
}

void HttpClientTest::post3()
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
	json_t* __msg_version = json_string("1.1.1.0");
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
	request->setTag("POST test3\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}

void HttpClientTest::post4(int __msg_type)
{
	//	post data to http server
	std::string __string_token = "&token=1234567788";
	std::string __string_msg = "msg=";
	json_t* __msg = json_object();
	json_t* __msg_id = json_integer(__msg_type);
	json_t* __flow_id = json_integer(88888888);
	json_t* __activity_type = json_integer(3);
	json_t* __msg_channel = json_string("000023");
	json_t* __msg_version = json_string("1.2.8");
	json_object_set(__msg, "msg_id", __msg_id);
	json_object_set(__msg, "flowid", __flow_id);
	json_object_set(__msg, "activity_type", __activity_type);
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

void HttpClientTest::post5()
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
	request->setTag("POST test5\n");
	HttpClient::getInstance()->send(request);
	request->release();

	// decref for json object
	json_decref(__msg_id);
}
static std::string __device_guid = "6d1dc7bd3f6e38f49685167f83fe29e2lee2";
static int __race_time = 99745;
void HttpClientTest::post6()
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
	json_object_set(__msg, "deviceid", __msg_device_guid);
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
	request->setTag("POST test8\n");
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
	std::string __str_msg = "uid=1535&version=1&voice_content=";
	__str_msg += __query;
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_voice_query\n");
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
	std::string __str_msg = "uid=1525&sex=1&v=1&type=0";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_get_user_info\n");
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
	std::string __str_msg = "uid=1525&name=King Lee&pass=164271579&bd=1983040404&sex=1&ba=9";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_set_colour\n");
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
	//std::string __str_msg = "uid=1525&type=get";
	//std::string __str_msg = "uid=1525&contracts_uid=1123&contracts_name=李希文&type=add";
	std::string __str_msg = "uid=1525&contracts_uid=1123&type=del";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_contracts\n");
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
	std::string __str_msg = "uid=1525&type=1";
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
	std::string __str_msg = "uid=1525&select_date_type=8&days_type=1";
	__str_msg = _UnicodeToUTF8(_AnsiToUnicode(__str_msg));
	request->setRequestData((const char*)__str_msg.c_str(), __str_msg.length());
	request->setTag("POST test_select_date\n");
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
			//__test->test_participle();
			//__test->test_voice_query("今天运程如何");
			//__test->test_voice_query("我本月做事如何");
			//__test->test_voice_query("我今年能量如何");
			//__test->test_voice_query("我今天去旅行如何");
			//__test->test_voice_query("我今日健康如何");
			//__test->test_voice_query("我今日财富如何");
			//__test->test_voice_query("我今日破财么");
			//__test->test_voice_query("我本月购物如何");
			//__test->test_voice_query("我本月学业如何");
			//__test->test_voice_query("我今年事业如何");
			//__test->test_voice_query("我今日求财如何");
			//__test->test_voice_query("我今日情感如何");
			//__test->test_voice_query("我今日会友如何");
			//__test->test_voice_query("我今日感情变化如何");
			//__test->test_voice_query("我今日桃花如何");
			//__test->test_voice_query("我今日追求好么");
			__test->test_voice_query("我这天那个方向最顺?");
			//__test->test_voice_query("问点什么好呢?");
			//__test->test_get_user_info();
			//__test->test_set_colour();
			//__test->test_modify_info();
			//__test->test_feedback();
			//__test->test_contracts();
			//__test->test_compass();
			__test->test_select_date();
			//__test->test_express_register();
			//__test->test_express_login();
			//__test->post1();

			//	test express

		}
		else
		{
			//__test->post2();
			//__test->post3();
			__test->post4(5);
			//__test->post5();
			//__test->post6();
			//__test->post7();
			//__test->post8();
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

