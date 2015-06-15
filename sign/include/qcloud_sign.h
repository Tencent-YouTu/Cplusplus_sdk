#ifndef __QCLOUD_SIGN_H__
#define __QCLOUD_SIGN_H__

#include "qcloud_sign_const.h"

/*
 * @func    服务端签名函数,APP级别,有效期expired内使用
 * @param   appid       腾讯云APPID 
 * @param   secret_id   Qcloud上申请到的密钥id
 * @param   secret_key  Qcloud上申请到的密钥key
 * @param   expired     过期时间(绝对时间)
 * @param   userid      业务没有账号体系填NULL
 * @param   sign        输出函数,计算得到的签名值,函数内malloc,业务使用完需要自行释放free
 * @return  0成功 <0失败
*/
int qc_app_sign(unsigned int appid, const char* secret_id, const char* secret_key, unsigned int expired, const char* userid, char*& sign);

/*
 * @func    服务端签名函数,接口级别,操作本次有效
 * @param   appid       腾讯云APPID 
 * @param   secret_id   Qcloud上申请到的密钥id
 * @param   secret_key  Qcloud上申请到的密钥key
 * @param   userid      业务没有账号体系填NULL
 * @param   url         不绑定具体的数据填NULL 
 * @param   sign        输出函数,计算得到的签名值,函数内malloc,业务使用完需要自行释放free
 * @return  0成功 <0失败
*/
int qc_app_sign_once(unsigned int appid, const char* secret_id, const char* secret_key, const char* userid, const char* url, char*& sign);

#endif
