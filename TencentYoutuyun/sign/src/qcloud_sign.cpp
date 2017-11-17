#include "qcloud_sign.h"
#include "qcloud_sign_utils.h"

#include <string.h>
#include <string>
#include <openssl/hmac.h>

static int app_sign(unsigned int appid, const std::string &secret_id,
                    const std::string &secret_key, unsigned int expired,
                    const std::string &userid, const std::string &url,
                    std::string &sign) {
    if (secret_id.empty() || !secret_id[0] || secret_key.empty() ||
        !secret_key[0]) {
        return _ERROR_QCLOUD_INVALID_PARAM;
    }

    const char *puserid = "";
    if (!userid.empty() && userid[0]) {
        if (userid.length() > _USER_ID_MAX_LEN) {
            return _ERROR_QCLOUD_USERID_TOO_LONG;
        }

        puserid = userid.c_str();
    }

    const char *fileid = "";
    if (!url.empty() && url[0]) {
        if (url.length() > _URL_MAX_LEN) {
            return _ERROR_QCLOUD_URL_TOO_LONG;
        }

        std::string domain_, fileid_;
        int ret = QCloud::qc_get_fileid_from_url(url, fileid_);
        if (ret != 0) {
            return _ERROR_QCLOUD_INVALID_URL;
        }
        fileid = fileid_.c_str();
    }

    unsigned int now = time(NULL);
    srandom(now);
    unsigned int rdm = random();

    char plain_text[_PLAIN_TEXT_MAX_LEN] = {0};
    // ret is length
    int plain_text_len = snprintf(
        plain_text, sizeof(plain_text), "a=%u&k=%s&e=%u&t=%u&r=%d&u=%s&f=%s",
        appid, secret_id.c_str(), expired, now, rdm, puserid, fileid);
    if (plain_text_len <= 0) {
        return _ERROR_QCLOUD_PLAIN_TEXT_TOO_LONG;
    }

    char bin[_CIPER_TEXT_MAX_LEN] = {0};
    unsigned int len = 0;
    HMAC(EVP_sha1(), (const void *)secret_key.c_str(), secret_key.length(),
         (const unsigned char *)plain_text, plain_text_len,
         (unsigned char *)bin, &len);

    memcpy(bin + len, plain_text, plain_text_len);
    sign = QCloud::Base64::encode(bin, len + plain_text_len);
    sign.push_back('\0');

    return 0;
}

int qc_app_sign(unsigned int appid, const std::string &secret_id,
                const std::string &secret_key, unsigned int expired,
                const std::string &userid, std::string &sign) {
    return app_sign(appid, secret_id, secret_key, expired, userid, "", sign);
}

int qc_app_sign_once(unsigned int appid, const std::string &secret_id,
                     const std::string &secret_key, const std::string &userid,
                     const std::string &url, std::string &sign) {
    return app_sign(appid, secret_id, secret_key, 0, userid, url, sign);
}
