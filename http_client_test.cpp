// http_client_test.cpp : 定义控制台应用程序的入口点。
//

#include "HttpClient.h"
#include <tchar.h>
using namespace  network;

class HttpClientTest : public Ref
{
public:
	HttpClientTest() {}

	~HttpClientTest(){}

	void post();

	//Http Response Callback
	void onHttpRequestCompleted(network::HttpClient *sender, network::HttpResponse *response);

};

void HttpClientTest::post()
{
	if(1)
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
		HttpRequest* request = new HttpRequest();
		request->setUrl("http://192.168.22.69:3000/");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(this, httpresponse_selector(HttpClientTest::onHttpRequestCompleted));

		// write the post data
		const char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
		request->setRequestData(postData, strlen(postData));

		request->setTag("POST test1");
		HttpClient::getInstance()->send(request);
		request->release();
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

int _tmain(int argc, _TCHAR* argv[])
{
	HttpClientTest* __test = new HttpClientTest();
	__test->post();
	while (true)
	{
		::_sleep(1);
	}
	return 0;
}

