#include <sys/time.h>
#include <fstream>
#include <iostream>
#include "TencentYoutuyun/ytopen_sdk.h"

using namespace std;
using namespace rapidjson;

int main(int argc,char * argv[])
{
    //app sign params.
    ytopen_sdk::AppSign m_app_sign = 
    {
        1000061,
        "AKIDytaL55OwoRYDMGFzols94MDrf8URHA0N",
        "RRJoPEXyvVeZtiCwthW6N6NDq888Pk0o",
        "3041722595"
    };

    ytopen_sdk m_sdk;
    m_sdk.Init(m_app_sign);

    rapidjson::Value result;
    if(0 != m_sdk.DetectFace(result, "a.jpg", 0, true))
    {
        cout << "DetectFace failed." << endl;
    }

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    result.Accept(writer);
    cout << buffer.GetString() << endl;

    return 0;
}
