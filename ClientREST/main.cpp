#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "../ServerREST/class/Data.hpp"

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

/* Proxy configuration */
web::http::client::http_client_config client_config_for_proxy()
{
    web::http::client::http_client_config client_config;

    if (const char* env_http_proxy = std::getenv("http_proxy")) {
        std::string env_http_proxy_string(env_http_proxy);

        if (env_http_proxy_string == U("auto")) {
            client_config.set_proxy(web::web_proxy::use_auto_discovery);
        }
        else {
            client_config.set_proxy(web::web_proxy(env_http_proxy_string));
        }
    }

    return client_config;
}

int main(int argc, char *argv[])
{
    std::cout << "REST client C++" << std::endl;

    utility::string_t port("34568");
    if(argc == 2) {
        port = argv[1];
    }

    utility::string_t address = U("http://127.0.0.1:");
    address.append(port);
    http::uri uri = http::uri(address);

    http::uri_builder builder(uri);
    builder.append_path(U("/MyServer/Action/")).to_uri();

    // Create http_client to send the request
    http_client client(builder.to_uri(), client_config_for_proxy());

    fprintf(stdout,"Query: %s",builder.to_string().c_str());

    while(true) {

        std::string method;
        std::cout << "Enter method: ";
        std::cin >> method;

        http_response response;
        std::string getDeveloppers("get_developers");

        if(getDeveloppers.compare(method) == 0) {
            utility::ostringstream_t buff;
            buff << U("?request=") << utility::conversions::to_string_t(method) << U("&city=Paris");

            response = client.request(methods::GET, buff.str()).get();

            std::cout << U("Response ") << response.to_string() << std::endl;

            json::value jdata = json::value::array();
            jdata = response.extract_json().get();
            DataPeople dataPeople = DataPeople::FromJSON(jdata.as_object());
        }
        else {
            std::cout << utility::conversions::to_string_t(method) << ": not understood" << std::endl;
        }
    }

    return 0;
}
