#ifndef _YTOPEN_SDK_
#define _YTOPEN_SDK_
#include <string>
#include <vector>

class ytopen_sdk
{
    public:
        typedef struct AppSign
        {
            uint32_t app_id;
            std::string secret_id;
            std::string secret_key;
            uint32_t expired;
            std::string user_id;

        }AppSign;

    public:
        void Init(const AppSign& t_app_sign, const std::string& t_host);
        void DetectFace(const std::string& imageData, std::string &rsp);
        void FaceCompare(const std::string& imageA, const std::string&imageB, std::string &rsp);
        void FaceVerify(const std::string& person_id, const std::string& imageData, std::string &rsp);
        void FaceIdentify(const std::string& group_id, const std::string& imageData, std::string &rsp);
        void NewPerson(const std::string& person_id, const std::string &person_name, const std::vector<std::string> &group_ids, const std::string& imageData, const std::string &tag, std::string &rsp);
        void DelPerson(const std::string& person_id, std::string &rsp);
        void AddFace(const std::string& person_id, const std::vector<std::string>& imageDatas, const std::string &tag, std::string &rsp);
        void DelFace(const std::string& person_id, const std::vector<std::string>& face_ids, std::string &rsp);
        void SetInfo(const std::string& person_id, const std::string& person_name, const std::string& tag, std::string &rsp);
        void GetInfo(const std::string& person_id, std::string &rsp);
        void GetGroupIds(std::string &rsp);
        void GetPersonIds(const std::string& group_id, std::string &rsp);
        void GetFaceIds(const std::string& person_id, std::string &rsp);
        void GetFaceInfo(const std::string&face_id , std::string &rsp);

    private:
        void curl_method(const std::string& addr, const std::string &req_str, std::string &rsp_str);
        
    private:
        std::string host;
        AppSign app_sign;
        std::string app_id;
};

#endif
