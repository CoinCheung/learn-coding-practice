
#include <curl/curl.h>
#include <stdio.h>
#include <string>

using namespace std;

int main() {
    string url = "http://10.128.61.9:28889/03/A29/facepic/2019/6/1/800421020102000378/800521020101000441201906010000013295.jpg";

    // FILE* out_file = fopen("tmp.jpg", "wb");
    // CURL *curl = curl_easy_init();
    // curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    // curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    // curl_easy_setopt(curl, CURLOPT_WRITEDATA, out_file);
    //
    // CURLcode res = curl_easy_perform(curl);
    //
    // curl_easy_cleanup(curl);
    // fclose(out_file);


    FILE* out_file = fopen("tmp.jpg", "wb");
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, out_file);

    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    fclose(out_file);

    return 0;
}
