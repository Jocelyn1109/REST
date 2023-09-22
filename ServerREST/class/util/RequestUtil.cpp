#include <iostream>
#include <map>
#include <vector>
#include "RequestUtil.hpp"

using namespace std;

RequestUtil::RequestUtil()
{
    //ctor
}

RequestUtil::~RequestUtil()
{
    //dtor
}

utility::string_t RequestUtil::GetDataInQuery(const web::http::http_request *request, const utility::string_t data)
{
    utility::string_t request_data(U(""));
    if(request != nullptr) {
        map<utility::string_t, utility::string_t> query = web::http::uri::split_query(web::http::uri::decode(request->relative_uri().query()));
        for(auto it2 = query.begin(); it2!=query.end(); it2++) {
            cout << U("Query") << U(" ") << it2->first << U(" ") << it2->second << endl;
        }

        auto queryItr = query.find(U(data));
        request_data = queryItr->second;
        cout << U("Request") << U(" ") << request_data << endl;
    }

    return request_data;
}

void RequestUtil::DisplaySplitedRequestPath(const web::http::http_request *request)
{
    if(request != nullptr) {
        vector<utility::string_t> paths = web::http::uri::split_path(web::http::uri::decode(request->relative_uri().path()));
        for(auto it1 = paths.begin(); it1!=paths.end(); it1++) {
            cout << U("Path") << U(" ") << *it1 << endl;
        }
    }
}
