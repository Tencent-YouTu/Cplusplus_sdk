#include "qcloud_sign_utils.h"

#include <stdio.h>

namespace QCloud
{
    int qc_build_resource_url(const std::string &domain, unsigned appid, const std::string &userid
        , const std::string &fileid, std::string &url)
    {
        char buffer_[2048] = {0};
        std::string userid_(userid);

        if(userid_.size() == 0)
        {
            userid_ = "0";
        }

        if(fileid.size() == 0) // this is a upload request, so no fileid
        {
            snprintf(buffer_, 2048, "http://%s/%d/%s"
                , domain.c_str(), appid, userid_.c_str());
        }
        else
        {
            snprintf(buffer_, 2048, "http://%s/%d/%s/%s"
                , domain.c_str(), appid
                , userid_.c_str(), fileid.c_str());
        }

        url.assign(buffer_);

        return 0;
    }

    int qc_build_download_url(const std::string &domain, unsigned appid
        , const std::string &userid, const std::string &fileid, std::string &url)
    {
        char buffer_[2048] = {0};
        std::string userid_(userid);

        if(userid_.size() == 0)
        {
            userid_ = "0";
        }

        snprintf(buffer_, 2048, "http://%u.%s/%u/%s/%s/original"
            , appid, domain.c_str(), appid
            , userid_.c_str(), fileid.c_str());

        url.assign(buffer_);

        return 0;
    }

    int qc_parse_photo_url(const std::string &url, std::string& domain, std::string &appid, std::string &userid, std::string &fileid)
    {
        char domain_[256] = {0};
        char appid_[256] = {0};
        char userid_[256] = {0};
        char fileid_[256] = {0};
        char spec_[256] = {0};

        int ret = sscanf(url.c_str(), "http://%[^/]/%[^/]/%[^/]/%[^/]/%[^/?]", domain_, appid_, userid_, fileid_, spec_);
        if (ret != 5)
        {
            return -1;
        }

        domain = domain_;
        appid = appid_;
        userid = userid_;
        fileid = fileid_;

        return 0;
    }

    int qc_parse_video_url(const std::string &url, std::string& domain, std::string &vid)
    {
        char domain_[256] = {0};
        char vid_[256] = {0};
        char freq_[256] = {0};
        char type_[256] = {0};

        int ret = sscanf(url.c_str(), "http://%[^/]/%[^.].%[^.]%[^/?]", domain_, vid_, freq_, type_);
        if (ret != 4)
        {
            return -1;
        }

        domain = domain_;
        vid = vid_;

        return 0;
    }

    int qc_get_fileid_from_url(const std::string &url, std::string &fileid)
    {
        std::string domain, appid, userid, vid;
        int ret = qc_parse_photo_url(url, domain, appid, userid, fileid);
        if (ret == 0)
        {
            return 0;
        }

        ret = qc_parse_video_url(url, domain, fileid);
        if (ret == 0)
        {
            return 0;
        }

        return -1;
    }

    std::string Base64::g_base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    bool Base64::is_base64(unsigned char c)
    {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }

    unsigned char Base64::calBase64(const unsigned char ch)
    {   
        if('A' <= ch 
            && 'Z' >= ch)
        {
            return ch - 'A'; 
        }   
        else if('a' <= ch
            && 'z' >= ch)
        {       
            return ch - 'a' + 26;
        }   
        else if('0' <= ch
            && '9' >= ch)
        {       
            return ch - '0' + 52;
        }   
        else if('+' == ch)
        {       
            return 62;
        }   
        else if('/' == ch)
        {   
            return 63;
        }       

        //FATAL
        return 255;
    }           

    std::string Base64::encode(const char* bytes_to_encode, unsigned int in_len)
    {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for(i = 0; (i <4) ; i++)
                    ret += g_base64_chars[char_array_4[i]];
                i = 0;
            }
        }

        if (i)
        {
            for(j = i; j < 3; j++)
                char_array_3[j] = '\0';

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
                ret += g_base64_chars[char_array_4[j]];

            while((i++ < 3))
                ret += '=';

        }

        return ret;

    }

    std::string Base64::decode(const std::string& encoded_string) 
    {
        size_t in_len = encoded_string.size();
        size_t i = 0;
        size_t j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];
        std::string ret;

        while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) 
        {
            char_array_4[i++] = encoded_string[in_]; in_++;
            if (i ==4) 
            {
                for (i = 0; i <4; i++)
                    char_array_4[i] = calBase64(char_array_4[i]);

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++)
                    ret += char_array_3[i];
                i = 0;
            }
        }

        if (i) 
        {
            for (j = i; j <4; j++)
                char_array_4[j] = 0;

            for (j = 0; j <4; j++)
                char_array_4[j] = calBase64(char_array_4[j]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; (j < i - 1); j++)
                ret += char_array_3[j];
        }

        return ret;
    }

    std::string Base64::encode(const std::string& bytes_to_encode)
    {
        return encode(bytes_to_encode.c_str(), bytes_to_encode.size());
    }

}
