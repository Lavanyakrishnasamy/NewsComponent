#include <iostream>
#include "RestAPI.hpp"
#include <cstring>
#include <vector>
#include <unordered_map>
#include <thread>         
#include <chrono> 
#include "pugixml.hpp"
#include <algorithm>
#include<ctime>

using namespace std;
using namespace news::api;

unordered_map <const char*, const char*> check_duplicate;

void parseResponse(string response)
{

	pugi::xml_document doc;
  	pugi::xml_parse_result result = doc.load(response.c_str());
  	if (!result)
  	{
  		std::cout << "Nothing to parse" << std::endl;
  		return;
  	}

	for (pugi::xml_node tool: doc.child("rss").child("channel"))
	{
		std::string searchStr = "title";
		pugi::xpath_node xpathNode = tool.select_single_node(searchStr.c_str());
		if (xpathNode)
    	{
    		const char* guid = tool.child_value("guid");
    		if(check_duplicate.find(guid) == check_duplicate.end())
    		{
    			const char* title = tool.child_value("title");
	    		const char* description = tool.child_value("description");
	    		const char* pub_date = tool.child_value("pubDate");
	    		if ((strlen(title) > 0) && (strlen(description) >0 ) && (strlen(pub_date)>0))
	    		{
	    			time_t poll_time = time(NULL);
	    			cout << "New News: " << ctime(&poll_time);
		    		cout <<"Title: " <<title<<endl;    		
		    		cout << "Published Date: " <<pub_date<<endl;
		    		cout << "Description:  " <<description<<endl;
		    		cout << endl << endl;
		    		std::this_thread::sleep_for (std::chrono::seconds(15));
	    		}
	    		if(strlen(guid)>0)
	    			check_duplicate.insert(make_pair(guid,title));
    		}
    		else
    		{
    			cout<< "Duplicate found" << endl;
    		}
    		
    	}
	}
}


int main(int argc, char const *argv[])
{

  string news_url= "https://timesofindia.indiatimes.com/rssfeedstopstories.cms";
  char* url = const_cast<char*> (news_url.c_str());
  RestAPI *apiObj = new RestAPI();
  string response = apiObj->getResponse(url);
  parseResponse(response);
  return 0;
}
