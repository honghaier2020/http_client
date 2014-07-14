// http_client_test.cpp : 定义控制台应用程序的入口点。
//

#include "HttpClient.h"
#include <tchar.h>
#include <thread>
#include <mutex>
#include "jansson.h"
using namespace  network;

static std::mutex       s_post_mutex;
#ifndef __CLOUD_BOX
//#define __CLOUD_BOX
#endif //__CLOUD_BOX

#ifndef __CLOUD_BOX_FORMAL
#define __CLOUD_BOX_FORMAL
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


class HttpClientTest : public Ref
{
public:
	HttpClientTest() {}

	~HttpClientTest(){}

	void initThread();

	void postThread();
	//	test http_server,http component for login
	void post1();

	void post2();

	//	test for mail
	void post3();

	void post4(int __msg_type);

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
	request->setTag("POST test1\n");
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
	json_t* __msg_title = json_string("title");
	json_t* __msg_content = json_string("content");
	json_t* __msg_channel = json_string("qihu360");
	json_t* __msg_version = json_string("1.1.1.0");
	json_object_set(__msg, "msg_id", __msg_id);
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
	request->setTag("POST test1\n");
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
	json_t* __msg_channel = json_string("qihu360");
	json_t* __msg_version = json_string("1.1.1.0");
	json_object_set(__msg, "msg_id", __msg_id);
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
	request->setTag("POST test1\n");
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

int _tmain(int argc, _TCHAR* argv[])
{
	HttpClientTest* __test = new HttpClientTest();
	if(1)
	{
		if(0)
		{
			__test->post1();
		}
		else
		{
			__test->post2();
			__test->post3();
			__test->post4(5);
			__test->post4(6);
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

