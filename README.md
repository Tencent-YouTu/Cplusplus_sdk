# tencentyun-youtu

c++ sdk for [腾讯云智能优图服务](http://www.qcloud.com/product/fr.html)

## 安装
####运行环境
- `Linux`

####依赖项
```
- curl-7.40.0，获取更新版本
	https://github.com/bagder/curl
- openssl-1.0.1k，获取更新版本
	https://github.com/openssl/openssl
```
####构建工程
```
工程采用CMake构建
1. 下载sdk到您的目录${Cplusplus_sdk}
	git clone https://github.com/TencentYouTu/Cplusplus_sdk.git
2. 进入${Cplusplus_sdk}/thirdparty，执行
	sh install_first.sh
3. 构建CMake编译工程,在${Cplusplus_sdk}/build中生成二进制sample程序
	mkdir ${Cplusplus_sdk}/build
	cd ${Cplusplus_sdk}/build
	cmake ../
	make
4. sdk_test.cpp中有您想调用的接口示例，可以仿照${Cplusplus_sdk}/sample/CMakeLists.txt将sdk放入您的工程当中。
```

## 名词

- `AppId` 平台添加应用后分配的AppId
- `SecretId` 平台添加应用后分配的SecretId
- `SecretKey` 平台添加应用后分配的SecretKey
- `签名` 接口鉴权凭证，由AppId、SecretId、SecretKey等生成，详见<http://open.youtu.qq.com/welcome/authentication>

## 使用示例
```
    //app sign params.
    ytopen_sdk::AppSign m_app_sign = 
    {
        1000061,
        "AKID4Bhs9vqYT6mHa9TkIrAe7w5oijOCEjql",
        "P2VTKNvTAnYNwBrqXbgxRSFQs6FTEhNJ",
        "3041722595"
    };

    string imageData;
    if(0 != read_image("a.jpg",imageData)) {
        return -1;
    }

    string rsp;
    ytopen_sdk m_sdk;
    m_sdk.Init(m_app_sign);

    if(0 != m_sdk.DetectFace(imageData, true, rsp))
    {
        cout << "DetectFace failed." << endl;
    }

    cout << rsp << endl;
```

##初始化
- 示例
- `m_sdk.Init(m_app_sign);`

- 参数`ytopen_sdk::AppSign`
	- `app_id` 业务中的应用标识AppId
	- `secret_id` 秘钥SecretId
	- `secret_key` 秘钥SecretKey
	- `user_id` 业务中的用户标识
- 返回值 无

##接口说明
接口调用统一返回值说明
- 返回值
	- `0` 成功
	- `-1` 失败，原因可能为秘钥鉴权失败、参数不合法等

###人脸检测
- 接口
`int DetectFace(const std::string& imageData, bool isBigFace, std::string &rsp);`
- 参数
	- `imageData` 待检测的图片数据，base64编码
	- `isBigFace` 是否大脸模式
	- `rsp` 返回的检测结果，JSON字符串，字段参见API文档

###人脸配准
- 接口
`int FaceShape(const std::string& imageData, bool isBigFace, std::string &rsp);`
- 参数
	- `imageData` 待检测的图片数据，base64编码
	- `isBigFace` 是否大脸模式
	- `rsp` 返回的配准结果，JSON字符串，字段参见API文档

###人脸比对
- 接口
`int FaceCompare(const std::string& imageA, const std::string&imageB, std::string &rsp);`
- 参数
	- `imageA` 待比对的A图片数据，base64编码
	- `imageB` 待比对的B图片数据，base64编码
	- `rsp` 返回的比对结果，JSON字符串，字段参见API文档

###人脸验证
- 接口
`int FaceVerify(const std::string& person_id, const std::string& imageData, std::string &rsp);`
- 参数
	- `person_id` 待验证的人脸id
	- `imageData` 待验证的图片数据，base64编码
	- `rsp` 返回的人脸验证匹配结果，JSON字符串，字段参见API文档

###人脸识别
- 接口
`int FaceIdentify(const std::string& group_id, const std::string& imageData, std::string &rsp);`
- 参数
	- `group_id` 识别的组id
	- `imageData` 待识别的图片数据，base64编码
	- `rsp` 返回的top5识别结果，JSON字符串，字段参见API文档

###新建个体
- 接口
        `int NewPerson(const std::string& person_id, const std::string &person_name, const std::vector<std::string> &group_ids, const std::string& imageData, const std::string &tag, std::string &rsp);`
- 参数
	- `person_id` 新建的个体id，用户指定，需要保证app_id下的唯一性
	- `person_name` 待验证的图片数据，base64编码
	- `group_ids` 新建的个体存放的组id，可以指定多个组id，用户指定（组默认创建）
	- `imageData` 包含个体人脸的图片数据，base64编码
	- `tag` 备注信息，用户自解释字段
	- `rsp` 返回的新建状态结果，JSON字符串，字段参见API文档

###删除个体
- 接口
`int DelPerson(const std::string& person_id, std::string &rsp);`
- 参数
	- `person_id` 待删除的个体id
	- `rsp` 返回的删除状态结果，JSON字符串，字段参见API文档

###增加人脸
- 接口
`int AddFace(const std::string& person_id, const std::vector<std::string>& imageDatas, const std::string &tag, std::string &rsp);`
- 参数
	- `person_id` 新增人脸的个体身份id
	- `imageDatas` 待增加的包含人脸的图片数据，可加入多张（包体大小<2m），base64编码
	-  `tag` 人脸备注信息，用户自解释字段
	- `rsp` 返回的人脸增加状态结果，JSON字符串，字段参见API文档

###删除人脸
- 接口
`int DelFace(const std::string& person_id, const std::vector<std::string>& face_ids, std::string &rsp);`
- 参数
	- `person_id` 待删除人脸的个体身份id
	- `face_ids` 待删除的人脸id
	- `rsp` 返回的人脸删除状态结果，JSON字符串，字段参见API文档

###获取信息
- 接口
`int GetInfo(const std::string& person_id, std::string &rsp);`
- 参数
	- `person_id` 待查询的个体身份id
	- `rsp` 返回的查询结果，JSON字符串，字段参见API文档

###设置信息
- 接口
`int SetInfo(const std::string& person_id, const std::string& person_name, const std::string& tag, std::string &rsp);`
- 参数
	- `person_id` 待设置的个体身份id
	- `person_name` 新设置的个体名字
	-  `tag` 新设置的人脸备注信息
	- `rsp` 返回的状态结果，JSON字符串，字段参见API文档

###获取组列表
- 接口
`int GetGroupIds(std::string &rsp);`
- 参数
	- `rsp` 返回的组列表查询结果，JSON字符串，字段参见API文档

###获取个体列表
- 接口
`int GetPersonIds(const std::string& group_id, std::string &rsp);`
- 参数
	- `group_id` 待查询的组id
	- `rsp` 返回的个体列表查询结果，JSON字符串，字段参见API文档

###获取人脸列表
- 接口
`int GetFaceIds(const std::string& person_id, std::string &rsp);`
- 参数
	- `person_id` 待查询的个体id
	- `rsp` 返回的人脸列表查询结果，JSON字符串，字段参见API文档

###获取人脸信息
- 接口
`int GetFaceInfo(const std::string&face_id , std::string &rsp);`
- 参数
	- `face_id` 待查询的人脸id
	- `rsp` 返回的人脸信息查询结果，JSON字符串，字段参见API文档

```
```
更多详情和文档说明参见
[腾讯云智能优图服务](http://www.qcloud.com/product/fr.html)
[腾讯优图开放平台](open.youtu.qq.com)