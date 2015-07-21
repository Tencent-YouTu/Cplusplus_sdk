#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <curl/curl.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "bin2ascii.h"
#include "sign/include/qcloud_sign.h"
#include "ytopen_sdk.h"

using namespace std;
using namespace rapidjson;

string ytopen_sdk::host = "api.youtu.qq.com";

void ytopen_sdk::Init(const AppSign& t_app_sign)
{
    app_sign = t_app_sign;

    char t_app_id[64];
    snprintf(t_app_id, 63, "%d", t_app_sign.app_id);
    app_id.assign(t_app_id);
}

int ytopen_sdk::DetectFace(const string& imageData, bool isBigFace, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/detectface";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    string encode_data = b64_encode(imageData);
    writer.String("image"); writer.String(encode_data.c_str());
    writer.String("mode"); writer.Uint(isBigFace);

    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::FaceShape(const string& imageData, bool isBigFace, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/faceshape";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    string encode_data = b64_encode(imageData);
    writer.String("image"); writer.String(encode_data.c_str());
    writer.String("mode"); writer.Uint(isBigFace);

    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::FaceCompare(const string& imageA, const string&imageB, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/facecompare";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    string encode_data = b64_encode(imageA);
    writer.String("imageA"); writer.String(encode_data.c_str());
    encode_data = b64_encode(imageB);
    writer.String("imageB"); writer.String(encode_data.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::FaceVerify(const string& person_id, const string& imageData, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/faceverify";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    string encode_data = b64_encode(imageData);
    writer.String("image"); writer.String(encode_data.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::FaceIdentify(const string& group_id, const string& imageData, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/faceidentify";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    string encode_data = b64_encode(imageData);
    writer.String("image"); writer.String(encode_data.c_str());
    writer.String("group_id"); writer.String(group_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::NewPerson(const string& person_id, const string &person_name, const std::vector<string> &group_ids, const string& imageData, const string &tag, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/newperson";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    string encode_data = b64_encode(imageData);
    writer.String("image"); writer.String(encode_data.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.String("person_name"); writer.String(person_name.c_str());
    writer.String("group_ids");
    writer.StartArray();
    for(int i = 0; i < group_ids.size(); i++)
        writer.String(group_ids[i].c_str());
    writer.EndArray();
    writer.String("tag"); writer.String(tag.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::DelPerson(const string& person_id, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/delperson";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::AddFace(const string& person_id, const std::vector<string>& imageDatas, const string &tag, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/addface";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    writer.String("images");
    writer.StartArray();
    for(int i = 0; i < imageDatas.size(); i++)
    {
        string encode_data = b64_encode(imageDatas[i]);
        writer.String(encode_data.c_str());
    }
    writer.EndArray();
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.String("tag"); writer.String(tag.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::DelFace(const string& person_id, const std::vector<string>& face_ids, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/delface";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.String("face_ids");
    writer.StartArray();
    for(int i = 0; i < face_ids.size(); i++)
    {
        writer.String(face_ids[i].c_str());
    }
    writer.EndArray();
    writer.EndObject();
    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::SetInfo(const string& person_id, const string& person_name, const string& tag, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/setinfo";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.String("person_name"); writer.String(person_name.c_str());
    writer.String("tag"); writer.String(tag.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::GetInfo(const string& person_id, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/getinfo";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("person_id");writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::GetGroupIds(string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/getgroupids";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::GetPersonIds(const string& group_id, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/getpersonids";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("group_id");writer.String(group_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::GetFaceIds(const string& person_id, string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/getfaceids";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("person_id");writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int ytopen_sdk::GetFaceInfo(const string&face_id , string &rsp)
{
    std::stringstream ss;
    ss<<"http://"<<host<<"/youtu/api/getfaceinfo";

    string addr;
    addr.assign(ss.str());

    string req;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("face_id");writer.String(face_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    return curl_method(addr, req, rsp);
}

int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
     int len = size*nmemb;
     cout << "receive data len: " << len << endl;
     writerData->append(data, len);
     return len;
}

int ytopen_sdk:: curl_method(const string &addr, const string &req_str, string &rsp_str)
{
    rsp_str.clear();

    CURL *curl = curl_easy_init();
    CURLcode res_code;

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, addr.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req_str.c_str());   
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, req_str.size());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);  
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &rsp_str);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60);

        struct curl_slist *headers=NULL; /* init to NULL is important */
        headers = curl_slist_append(headers, "Content-Type: text/json");
        headers = curl_slist_append(headers, "Expect: ");

        //produce the sign for Authorization.
        char *sign = NULL;

        //get current time(s), add by 1000s as the expired time.
        time_t t;
        uint64_t cur_time = time(&t);
        qc_app_sign(app_sign.app_id, 
                    app_sign.secret_id.c_str(), 
                    app_sign.secret_key.c_str(), 
                    1000 + cur_time,
                    app_sign.user_id.c_str(), 
                    sign);

        string authstr = "Authorization: "+ string(sign);
        if(sign) {
            delete sign;
        }

        headers = curl_slist_append(headers, authstr.c_str());

        /* pass our list of custom made headers */
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res_code = curl_easy_perform(curl);
        if(CURLE_OK != res_code) {
            std::cout<<"res_code is "<<res_code<<std::endl;
            return -1;
        }

        long http_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if(200 != http_code) {
            std::cout << "http_code is "<<http_code<<std::endl;
            return -1;
        }

        curl_easy_cleanup(curl);
    } else
    {
        return -1;
    }

    return 0;
}

