// http_client_test.cpp : 定义控制台应用程序的入口点。
//

#include "HttpClient.h"
#include <tchar.h>
#include <thread>
#include <mutex>
#include "jansson.h"
using namespace  network;

static std::mutex       s_post_mutex;

class HttpClientTest : public Ref
{
public:
	HttpClientTest() {}

	~HttpClientTest(){}

	void initThread();

	void postThread();

	void post();

	//Http Response Callback
	void onHttpRequestCompleted(network::HttpClient *sender, network::HttpResponse *response);

};

void HttpClientTest::post()
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
			json_t* __msg = json_object();
			json_t* __msg_id = json_integer(/*MSG_ID::MSG_LOGIN*/2);
			json_t* __msg_context = json_string("context");
			json_object_set(__msg, "msg_id", __msg_id);
			json_object_set(__msg, "context", __msg_context);


			HttpRequest* request = new HttpRequest();
			request->setUrl("http://192.168.22.69:3000/");
			request->setRequestType(HttpRequest::Type::POST);
			request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

			// write the post data
			const char* postData = json_dumps(__msg,0);
			if(postData)
			{
				//	"{'context': 'context', 'msg_id': 2}";
				request->setRequestData(postData, strlen(postData));
			}
			request->setTag("POST test1");
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

void HttpClientTest::onHttpRequestCompleted( network::HttpClient *sender, network::HttpResponse *response )
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag())) 
	{
		printf("%s completed", response->getHttpRequest()->getTag());
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
	printf("Http Test, dump data: ");
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
		this->post();
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
	if(0)
	{
		__test->post();
	}
	else
	{
		__test->initThread();
	}

	while (true)
	{
		if(0)
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

