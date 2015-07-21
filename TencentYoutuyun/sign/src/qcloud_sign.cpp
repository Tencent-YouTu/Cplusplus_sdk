#include "qcloud_sign.h"
#include "qcloud_sign_utils.h"

#include <string.h>
#include <string>
#include <openssl/hmac.h>

static int app_sign(unsigned int appid, const char* secret_id, const char* secret_key, unsigned int expired, const char* userid, const char* url, char*& sign)
{
    if (!secret_id || !secret_id[0] || !secret_key || !secret_key[0])
    {
        return _ERROR_QCLOUD_INVALID_PARAM;
    }
    
    const char* puserid = "";
    if (userid && userid[0])
    {
        if (strlen(userid) > _USER_ID_MAX_LEN)
        {
            return _ERROR_QCLOUD_USERID_TOO_LONG;
        }
        
        puserid = userid;
    }
    
    const char* fileid = "";
    if (url && url[0])
    {
        if (strlen(url) > _URL_MAX_LEN)
        {
            return _ERROR_QCLOUD_URL_TOO_LONG;
        }
        
        std::string domain_, fileid_;
        int ret = QCloud::qc_get_fileid_from_url(url, fileid_);
        if (ret != 0)
        {
            return _ERROR_QCLOUD_INVALID_URL;
        }
        fileid = fileid_.c_str();
    }
    
    unsigned int now = time(NULL);    
    srandom(now);
    unsigned int rdm = random();
    
    char plain_text[_PLAIN_TEXT_MAX_LEN] = {0};
    //ret is length
    int plain_text_len = snprintf(plain_text, sizeof(plain_text), "a=%u&k=%s&e=%u&t=%u&r=%d&u=%s&f=%s",
        appid, secret_id, expired, now, rdm, puserid, fileid);
    if (plain_text_len <= 0)
    {
        return _ERROR_QCLOUD_PLAIN_TEXT_TOO_LONG;
    }

	char bin[_CIPER_TEXT_MAX_LEN]= {0};
	unsigned int len = 0;
	HMAC(EVP_sha1(), (const void*)secret_key, strlen(secret_key), (const unsigned char*)plain_text, plain_text_len, (unsigned char*)bin, &len);

    memcpy(bin + len, plain_text, plain_text_len);
    std::string base64 = QCloud::Base64::encode(bin, len + plain_text_len);
    
	sign = (char*)malloc(base64.size() + 1);
	
	//force null
	sign[base64.size()] = '\0';
    strncpy(sign, base64.c_str(), base64.size());

    return 0;
}

int qc_app_sign(unsigned int appid, const char* secret_id, const char* secret_key, unsigned int expired, const char* userid, char*& sign)
{
    return app_sign(appid, secret_id, secret_key, expired, userid, NULL, sign);
}

int qc_app_sign_once(unsigned int appid, const char* secret_id, const char* secret_key, const char* userid, const char* url, char*& sign)
{
    return app_sign(appid, secret_id, secret_key, 0, userid, url, sign);
}
