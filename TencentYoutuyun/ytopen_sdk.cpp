#include "ytopen_sdk.h"

using namespace std;
using namespace rapidjson;

string ytopen_sdk::host_youtu = "http://api.youtu.qq.com";
string ytopen_sdk::host_tencentyun = "https://youtu.api.qcloud.com";

int read_image(string filesrc,std::string& data)
{
    std::ifstream fr;
    fr.open(filesrc.c_str(),ios::binary);

    if (!fr)
    {
        std::cout<<"can't find left_file :"<<filesrc<<std::endl;
        return -1;
    }

    fr.seekg(0,ios::end);
    int length = fr.tellg();
    fr.seekg(0,ios::beg);
    char * image_data=new char[length];
    fr.read(image_data,length);
    fr.close();
    std::cout<<"image_data length is:"<<length<<std::endl;

    data.assign(image_data, length);
    return 0;
}

void ytopen_sdk::Init(const AppSign& t_app_sign, Domain domain)
{
    app_sign = t_app_sign;

    char t_app_id[64];
    snprintf(t_app_id, 63, "%d", t_app_sign.app_id);
    app_id.assign(t_app_id);

    if(domain == API_YOUTU_END_POINT) {
        host = host_youtu;
    }else {
        host = host_tencentyun;
    }
}

int ytopen_sdk::DetectFace(rapidjson::Value &result, const string& imagePath, int data_type, bool isBigFace)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/api/detectface";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }
    writer.String("mode"); writer.Uint(isBigFace);

    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::FaceShape(rapidjson::Value &result, const string& imagePath, int data_type, bool isBigFace)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/api/faceshape";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }
    writer.String("mode"); writer.Uint(isBigFace);

    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::FaceCompare(rapidjson::Value &result, const string& imagePathA, const string&imagePathB, int data_type)
{
    result.SetNull();

    string imageA, imageB;
    if(data_type == 0 &&
         (0 != read_image(imagePathA, imageA) || 0 != read_image(imagePathB, imageB))) {
        cout << "image not exist " << imagePathA << "," << imagePathB << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/api/facecompare";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageA);
        writer.String("imageA"); writer.String(encode_data.c_str());
        encode_data = b64_encode(imageB);
        writer.String("imageB"); writer.String(encode_data.c_str());
    }else {
        writer.String("urlA"); writer.String(imagePathA.c_str());
        writer.String("urlB"); writer.String(imagePathB.c_str());
    }
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::FaceVerify(rapidjson::Value &result, const string& person_id, const string& imagePath, int data_type)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/api/faceverify";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::FaceIdentify(rapidjson::Value &result, const string& group_id, const string& imagePath, int data_type)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/api/faceidentify";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }
    writer.String("group_id"); writer.String(group_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::NewPerson(rapidjson::Value &result, const string& person_id, const string &person_name, const std::vector<string> &group_ids, const string& imagePath, int data_type, const string &tag)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/api/newperson";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }
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
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::DelPerson(rapidjson::Value &result, const string& person_id)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/delperson";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::AddFace(rapidjson::Value &result, const string& person_id, const std::vector<string>& imagePaths, int data_type, const string &tag)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/addface";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;
    string imageData;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        writer.String("images");
        writer.StartArray();
        for(int i = 0; i < imagePaths.size(); i++)
        {
            if(0 != read_image(imagePaths[i], imageData)) {
                cout << "read image failed " << imagePaths[i] << endl;
                continue;
            }
            string encode_data = b64_encode(imageData);
            writer.String(encode_data.c_str());
        }
        writer.EndArray();

    }else {
        writer.String("urls");
        writer.StartArray();
        for(int i = 0; i < imagePaths.size(); i++)
        {
            if(!imagePaths[i].empty()) {
                writer.String(imagePaths[i].c_str());
            }else {
                cout << "url empty." <<endl;
            }
        }
        writer.EndArray();
    }
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.String("tag"); writer.String(tag.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::DelFace(rapidjson::Value &result, const string& person_id, const std::vector<string>& face_ids)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/delface";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

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
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::SetInfo(rapidjson::Value &result, const string& person_id, const string& person_name, const string& tag)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/setinfo";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    writer.String("person_id"); writer.String(person_id.c_str());
    writer.String("person_name"); writer.String(person_name.c_str());
    writer.String("tag"); writer.String(tag.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::GetInfo(rapidjson::Value &result, const string& person_id)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/getinfo";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("person_id");writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::GetGroupIds(rapidjson::Value &result)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/getgroupids";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::GetPersonIds(rapidjson::Value &result, const string& group_id)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/getpersonids";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("group_id");writer.String(group_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::GetFaceIds(rapidjson::Value &result, const string& person_id)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/getfaceids";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("person_id");writer.String(person_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::GetFaceInfo(rapidjson::Value &result, const string&face_id)
{
    std::stringstream ss;
    ss<<host<<"/youtu/api/getfaceinfo";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id");writer.String(app_id.c_str());
    writer.String("face_id");writer.String(face_id.c_str());
    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::FuzzyDetect(rapidjson::Value &result, const std::string &imagePath, int data_type, const string &cookie)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/imageapi/fuzzydetect";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }

    if(!cookie.empty()) {
        writer.String("cookie"); writer.String(cookie.c_str());
    }

    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::FoodDetect(rapidjson::Value &result, const std::string &imagePath, int data_type, const string &cookie)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/imageapi/fooddetect";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }

    if(!cookie.empty()) {
        writer.String("cookie"); writer.String(cookie.c_str());
    }

    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int ytopen_sdk::ImageTag(rapidjson::Value &result, const std::string &imagePath, int data_type, const string &cookie)
{
    string imageData;
    if(data_type == 0 && 0 != read_image(imagePath, imageData)) {
        cout << "image not exist " << imagePath << endl;
        return -1;
    }

    std::stringstream ss;
    ss<<host<<"/youtu/imageapi/imagetag";

    string addr;
    addr.assign(ss.str());

    string req;
    string rsp;

    StringBuffer sbuffer;
    Writer<StringBuffer> writer(sbuffer);

    writer.StartObject();
    writer.String("app_id"); writer.String(app_id.c_str());
    if(data_type == 0) {
        string encode_data = b64_encode(imageData);
        writer.String("image"); writer.String(encode_data.c_str());
    }else {
        writer.String("url"); writer.String(imageData.c_str());
    }

    if(!cookie.empty()) {
        writer.String("cookie"); writer.String(cookie.c_str());
    }

    writer.EndObject();

    req = sbuffer.GetString();
    int ret = curl_method(addr, req, rsp);
    if(ret == 0) {
        rapidjson::Document d;
        d.Parse<rapidjson::kParseStopWhenDoneFlag>(rsp.c_str());
        if(d.HasParseError()) {
            std::cout << "RapidJson parse error " << d.GetParseError() << endl;
            return -1;
        }

        rapidjson::Value::AllocatorType allocator;
        result.CopyFrom(d, allocator);
    }else {
        return -1;
    }

    return 0;
}

int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
     int len = size*nmemb;
     cout << "receive data len: " << len << endl;
     writerData->append(data, len);
     return len;
}

int ytopen_sdk::curl_method(const string &addr, const string &req_str, string &rsp_str)
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
            curl_easy_cleanup(curl);
            return -1;
        }

        long http_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if(http_code != 200) {
            cout << "http_code is " << http_code << endl;
            curl_easy_cleanup(curl);
            return -1;
        }

        curl_easy_cleanup(curl);
    } else
    {
        return -1;
    }

    return 0;
}

