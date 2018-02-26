# tencentyun-youtu

c++ sdk for [腾讯优图开放平台](http://open.youtu.qq.com)

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
	git clone https://github.com/Tencent-YouTu/Cplusplus_sdk.git
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

- `AppId` 平台用后分配的AppId
- `SecretId` 平台添加应用后分配的SecretId
- `SecretKey` 平台添加应用后分配的SecretKey
- `签名` 接口鉴权凭证，由AppId、SecretId、SecretKey等生成，详见<http://open.youtu.qq.com/welcome/developer#/new-authentication>


## 使用示例
```
    //app sign params.
    ytopen_sdk::AppSign m_app_sign = 
    {
        123,
        "AKIDytaL55OwoRYDMGFzols94MDrf8URHA0N",
        "RRJoPEXyvVeZtiCwthW6N6NDq888Pk0o",
        "888"
    };

    ytopen_sdk m_sdk;
    //优图开放平台初始化 
    m_sdk.Init(m_app_sign, ytopen_sdk::API_YOUTU_END_POINT);

    //优图开放平台核身服务初始化（核身服务目前仅支持核身专有接口,需要联系商务开通）
    m_sdk.Init(m_app_sign, ytopen_sdk::API_FACE_IN_YOUTU_END_POINT);

    //腾讯云初始化方式
    m_sdk.Init(m_app_sign, ytopen_sdk::API_TENCENTYUN_END_POINT);
    

    rapidjson::Document result;
    if(0 != m_sdk.DetectFace(result, "a.jpg"))
    {
        cout << "DetectFace failed." << endl;
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    result.Accept(writer);
    cout << buffer.GetString() << endl;
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
接口调用统一参数和返回值说明
- 参数
	- `imagePath` 包含个体人脸的图片路径
	- `data_type` 图片路径类型，0 本地路径 1 url路径
	- `result` 返回的接口结果，JSON结构体，字段参见API文档

- 返回值
	- `0` 成功
	- `-1` 失败，原因可能为秘钥鉴权失败、参数不合法等


##开放平台API介绍

###人脸检测
- 接口
`int DetectFace(rapidjson::Document &result, const std::string& imagePath, int data_type = 0, bool isBigFace = false);`
- 参数
	- `isBigFace` 是否大脸模式

###人脸配准
- 接口
`int FaceShape(rapidjson::Document &result, const std::string& imagePath, int data_type = 0, bool isBigFace = false);`
- 参数
	- `isBigFace` 是否大脸模式

###人脸比对
- 接口
`int FaceCompare(rapidjson::Document &result, const std::string& imagePathA, const std::string&imagePathB, int data_type = 0);`
- 参数
	- `imagePathA` 待比对的A图片路径
	- `imagePathB` 待比对的B图片路径

###人脸验证
- 接口
`int FaceVerify(rapidjson::Document &result, const std::string& person_id, const std::string& imagePath, int data_type = 0);`
- 参数
	- `person_id` 待验证的人脸id

###多人脸检索
- 接口
` int MultiFaceIdentify(rapidjson::Document &result, const std::string& group_id, const std::vector<std::string> &group_ids, const std::string& imagePath, int data_type = 0, int topn = 5, int min_size = 40);`
- 参数
	- `group_id` 识别的组id
	- `group_ids` 识别的个体存放的组id，可以指定多个组id，用户指定
	- `topn` 候选人脸数量，一般使用默认值5
	- `min_size` 人脸检测最小尺寸，一般使用默认值40

###人脸识别
- 接口
`int FaceIdentify(rapidjson::Document &result, const std::string& group_id, const std::string& imagePath, int data_type = 0);`
- 参数
	- `group_id` 识别的组id

###新建个体
- 接口
        `int NewPerson(rapidjson::Document &result, const std::string& person_id, const std::string &person_name, const std::vector<std::string> &group_ids, const std::string& imagePath, int data_type = 0, const std::string &tag = "");`
- 参数
	- `person_id` 新建的个体id，用户指定，需要保证app_id下的唯一性
	- `person_name` 新建的个体名称
	- `group_ids` 新建的个体存放的组id，可以指定多个组id，用户指定（组默认创建）
	- `tag` 备注信息，用户自解释字段

###删除个体
- 接口
`int DelPerson(rapidjson::Document &result, const std::string& person_id);`
- 参数
	- `person_id` 待删除的个体id
	- `rsp` 返回的删除状态结果，JSON字符串，字段参见API文档

###增加人脸
- 接口
`int AddFace(rapidjson::Document &result, const std::string& person_id, const std::vector<std::string>& imagePaths, int data_type = 0, const std::string &tag="");`
- 参数
	- `person_id` 新增人脸的个体身份id
	- `imagePaths` 待增加的包含人脸的图片路径，可加入多张（包体大小<2m，不超过5张）
	-  `tag` 人脸备注信息，用户自解释字段

###删除人脸
- 接口
`int DelFace(rapidjson::Document &result, const std::string& person_id, const std::vector<std::string>& face_ids);`
- 参数
	- `person_id` 待删除人脸的个体身份id
	- `face_ids` 待删除的人脸id

###获取信息
- 接口
`int GetInfo(rapidjson::Document &result, const std::string& person_id);`
- 参数
	- `person_id` 待查询的个体身份id

###设置信息
- 接口
`int SetInfo(rapidjson::Document &result, const std::string& person_id, const std::string& person_name, const std::string& tag);`
- 参数
	- `person_id` 待设置的个体身份id
	- `person_name` 新设置的个体名字
	-  `tag` 新设置的人脸备注信息

###获取组列表
- 接口
`int GetGroupIds(rapidjson::Document &result);`
- 参数

###获取个体列表
- 接口
`int GetPersonIds(rapidjson::Document &result, const std::string& group_id);`
- 参数
	- `group_id` 待查询的组id

###获取人脸列表
- 接口
`int GetFaceIds(rapidjson::Document &result, const std::string& person_id);`
- 参数
	- `person_id` 待查询的个体id

###获取人脸信息
- 接口
`int GetFaceInfo(rapidjson::Document &result, const std::string&face_id );`
- 参数
	- `face_id` 待查询的人脸id

###模糊检测
- 接口
`int FuzzyDetect(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");`
- 参数
	- `cookie ` 下载图片url的cookie

###食物检测
- 接口
`int FoodDetect(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");`
- 参数
	- `cookie ` 下载图片url的cookie

###图片分类
- 接口
`int ImageTag(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");`
- 参数
	- `cookie ` 下载图片url的cookie

###智能鉴黄
- 接口
`int ImagePorn(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");`
- 参数
	- `cookie ` 下载图片url的cookie

###暴恐图片识别
- 接口
`int ImageTerrorism(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");`
- 参数
	- `cookie ` 下载图片url的cookie

###车辆属性识别
- 接口
`int CarClassify(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, const std::string &cookie = "");`
- 参数
	- `cookie ` 下载图片url的cookie

###身份证OCR
- 接口
`int IdcardOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, int card_type = 0);`
- 参数
	- `card_type ` 身份证照片类型 0 正面 1 反面

###通用OCR
- 接口
`int GeneralOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);`
- 参数
	- `imagePath ` 待检测图片路径

###名片OCR
- 接口
`int BcOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);`
- 参数
	- `imagePath ` 待检测图片路径

###行驶证&驾驶证OCR
- 接口
`int DriverLicenseOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, int card_type = 0);`
- 参数
	- `imagePath ` 待检测图片路径
	- `card_type ` 照片类型 0 行驶证  1 驾驶证

###银行卡OCR识别
- 接口
`int CreditCardOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);`
- 参数
	- `imagePath ` 待检测图片路径

###营业执照OCR识别
- 接口
`int BizLicenseOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);`
- 参数
	- `imagePath ` 待检测图片路径
	
###车牌OCR识别
- 接口
`int PlateOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0);`
- 参数
	- `imagePath ` 待检测图片路径


##核身API介绍（核身服务目前仅支持核身专有接口,需要联系商务开通）

###身份证OCR
- 接口
`int IdcardOcr(rapidjson::Document &result, const std::string &imagePath, int data_type = 0, int card_type = 0);`
- 参数
	- `card_type ` 身份证照片类型 0 正面 1 反面

###人脸比对
- 接口
`int FaceCompare(rapidjson::Document &result, const std::string& imagePathA, const std::string&imagePathB, int data_type = 0);`
- 参数
	- `imagePathA` 待比对的A图片路径
	- `imagePathB` 待比对的B图片路径

###获取四字唇语 
- 接口
`int LiveGetFour(rapidjson::Document &result);`
- 参数
	- 无

###带数据源四字人脸核身
- 接口
`int LiveDetectFour(rapidjson::Document &result, const std::string &videoPath, const std::string &validate_data, const std::string &imagePath, bool compare_flag = 1);`
- 参数
	- `videoPath` 视频的路径
	- `validate_data` LiveGetFour获取的四字唇语
	- `imagePath_data` 对比照片的路径
	- `compare_flag`  视频与照片是否进行对比，1 对比 0不对比


###不带数据源四字人脸核身
- 接口
`int IdCardLiveDetectFour(rapidjson::Document &result, const std::string &videoPath, const std::string &validate_data, const std::string &id, const std::string &name);`
- 参数
	- `videoPath` 视频的路径
	- `validate_data` LiveGetFour获取的四字唇语
	- `id` 身份证号码
	- `name`  身份证姓名


###不带数据源人脸对比
- 接口
`int IdCardFaceCompare(rapidjson::Document &result, const std::string &id, const std::string &name, const std::string &imagePath, int data_type = 0);`
- 参数
	- `id` 身份证号码
	- `name`  身份证姓名
	- `imagePath` 照片的路径
	- `data_type` 0代表本地照片，1代表url

###实名认证
- 接口
`int ValidateIdCard(rapidjson::Document &result, const std::string &id, const std::string &name);`
- 参数
	- `id` 身份证号码
	- `name`  身份证姓名
```
```
更多详情和文档说明参见
[腾讯云智能优图服务](http://www.qcloud.com/product/fr.html)
[腾讯优图开放平台](open.youtu.qq.com)
