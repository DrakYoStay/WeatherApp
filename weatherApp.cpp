#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t total_size = size * nmemb;
    data->append((char*)contents, total_size);
    return total_size;
}

int main() {
        // Initialize the curl commands
        CURL *hnd = curl_easy_init();
        std::string CALL_URL = "https://api.tomorrow.io/v4/weather/realtime?location=brasov&apikey=SQmwSrTkaHuiidqYs7KRl5kwOZABnHR1";
        std::string jsonData;

        curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(hnd, CURLOPT_URL, CALL_URL.c_str());
        
        // Function to read the callback to jsonData
        curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &jsonData);


        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "accept: application/json");
        curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

        CURLcode ret = curl_easy_perform(hnd);
        curl_easy_cleanup(hnd);

        Json::CharReaderBuilder reader;
        Json::Value data;
        Json::CharReader* jsonReader = reader.newCharReader();
        jsonReader->parse(jsonData.c_str(), jsonData.c_str() + jsonData.size(), &data, nullptr);

        //Whole json print
        std::cout << "===========================================================================================" << std::endl;
        std::cout << data << std::endl;
        std::cout << "===========================================================================================" << std::endl;

        
        std::cout << "Temperatura: " << data["data"]["values"]["temperature"].asDouble() << std::endl;
        return 0;
}
