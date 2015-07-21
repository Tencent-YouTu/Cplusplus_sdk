#include <sys/time.h>
#include <fstream>
#include <iostream>
#include "TencentYoutuyun/ytopen_sdk.h"

using namespace std;

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

int main(int argc,char * argv[])
{
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

    return 0;
}
