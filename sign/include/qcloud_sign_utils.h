#ifndef __QCLOUD_SIGN_UTILS_H__
#define __QCLOUD_SIGN_UTILS_H__

#include <string>
#include <sstream>


namespace QCloud
{
	int qc_build_resource_url(const std::string &domain, unsigned appid
		, const std::string &userid, const std::string &fileid, std::string &url);

	int qc_build_download_url(const std::string &domain, unsigned appid
		, const std::string &userid, const std::string &fileid, std::string &url);

	int qc_parse_photo_url(const std::string &url, std::string& domain
			, std::string &appid, std::string &userid, std::string &fileid);

	int qc_parse_video_url(const std::string &url, std::string& domain
			, std::string &vid);

	int qc_get_fileid_from_url(const std::string &url, std::string &fileid);

	class Base64
	{
	public:
	    static std::string decode(const std::string& encoded_string);
	    static std::string encode(const char* bytes_to_encode, unsigned int in_len);
	    static std::string encode(const std::string& bytes_to_encode);
	    
	private:
	    static bool is_base64(unsigned char c);
	    static unsigned char calBase64(const unsigned char ch);
	    
	private:
	    static std::string g_base64_chars;
	};

}

#include "qcloud_sign_utils.hpp"

#endif