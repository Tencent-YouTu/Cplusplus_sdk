#include <gflags/gflags.h>
#include <fstream>
#include <iostream>
#include "ytopen_sdk.h"

using namespace std;

DEFINE_string(op, "detectface", "api select");
DEFINE_string(src, "1.jpg", "filename");
DEFINE_string(pid, "person0", "person id");
DEFINE_string(fid, "", "faceid");
DEFINE_string(gid, "", "group id");

DEFINE_string(addr, "localhost", "web addr.");

DEFINE_int32(app_id, 1000061, "app id");
DEFINE_string(secret_id, "AKIDg73gcCm7J2Nw68g2dJWFXH1p93TMf3bw", "secret id");
DEFINE_string(secret_key, "HH064Ds0zArO7qe61dyKWTSDBf3adCLh", "secret key");
DEFINE_int32(expired, 1436353609, "expired");
DEFINE_string(user_id, "3041722595", "user_id");

void read_image(string filesrc,std::string& data)
{
    std::ifstream fr; 
    fr.open(filesrc.c_str(),ios::binary);

    if (!fr)
    {   
        std::cout<<"can't find left_file :"<<filesrc<<std::endl;
        return;
    }

    fr.seekg(0,ios::end);
    int length = fr.tellg();
    fr.seekg(0,ios::beg);
    char * image_data=new char[length];
    fr.read(image_data,length);
    fr.close();
    std::cout<<"image_data length is:"<<length<<std::endl;

    data.assign(image_data, length);
}


int main(int argc,char * argv[])
{
    google::ParseCommandLineFlags(&argc, &argv, true);
  
    //get app sign params.
    ytopen_sdk::AppSign m_app_sign = 
    {
        FLAGS_app_id,
        FLAGS_secret_id,
        FLAGS_secret_key,
        FLAGS_expired,
        FLAGS_user_id
    };

    string imageData;
    read_image(FLAGS_src,imageData);

    string rsp;
    ytopen_sdk m_sdk;
    m_sdk.Init(m_app_sign, FLAGS_addr);

    if(0 == FLAGS_op.compare("detectface"))
    {
        m_sdk.DetectFace(imageData, rsp);
    }
    else if(0 == FLAGS_op.compare("facecompare"))
    {
        //compare the same pic.
        m_sdk.FaceCompare(imageData, imageData, rsp);
    }
    else if(0 == FLAGS_op.compare("faceverify"))
    {
        m_sdk.FaceVerify(FLAGS_pid, imageData, rsp);
    }
    else if(0 == FLAGS_op.compare("faceidentify"))
    {
        m_sdk.FaceIdentify(FLAGS_gid, imageData, rsp);
    }
    else if(0 == FLAGS_op.compare("newperson"))
    {
        vector<string> group_ids;
        group_ids.push_back(FLAGS_gid);

        m_sdk.NewPerson(FLAGS_pid, "johnson", group_ids, imageData, "new tag", rsp);
    }
    else if(0 == FLAGS_op.compare("delperson"))
    {
        m_sdk.DelPerson(FLAGS_pid, rsp);
    }
    else if(0 == FLAGS_op.compare("addface"))
    {
        vector<string> imageDatas;
        imageDatas.push_back(imageData);

        m_sdk.AddFace(FLAGS_pid, imageDatas, "face tag", rsp);
    }
    else if(0 == FLAGS_op.compare("delface"))
    {
        vector<string> face_ids;
        face_ids.push_back(FLAGS_fid);

        m_sdk.DelFace(FLAGS_pid, face_ids, rsp);
    }
    else if(0 == FLAGS_op.compare("setinfo"))
    {
        m_sdk.SetInfo(FLAGS_pid, "mike", "new tag", rsp);
    }
    else if(0 == FLAGS_op.compare("getinfo"))
    {
        m_sdk.GetInfo(FLAGS_pid, rsp);
    }
    else if(0 == FLAGS_op.compare("getgroupids"))
    {
        m_sdk.GetGroupIds(rsp);
    }
    else if(0 == FLAGS_op.compare("getpersonids"))
    {
        m_sdk.GetPersonIds(FLAGS_gid, rsp);
    }
    else if(0 == FLAGS_op.compare("getfaceids"))
    {
        m_sdk.GetFaceIds(FLAGS_pid, rsp);
    }
    else if(0 == FLAGS_op.compare("getfaceinfo"))
    {
        m_sdk.GetFaceInfo(FLAGS_fid, rsp);
    }
    else
    {
        cout << "invalid operation." << endl;
    }

    cout << rsp << endl;

    return 0;
}
