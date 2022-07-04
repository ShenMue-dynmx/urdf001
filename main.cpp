#include <iostream>
#include <fstream>
#include<cstdio>
#include "urdf/common.h"
#include "urdf/geometry.h"
#include "urdf/joint.h"
#include "urdf/model.h"

using namespace urdf;
using namespace std;


string UrdfFileFromDisk="emptyUrdf";

void LoadUrdf(string path,bool debug=false)
{
    fstream f(path);
    stringstream iss;
    iss << f.rdbuf();
    UrdfFileFromDisk=iss.str();
    if(debug)
    {
        cout<<UrdfFileFromDisk<<endl;
    }
}


int main(){
    std::cout<<"Main laucnhed"<<std::endl;
    LoadUrdf("/home/shenmu/DevStuff/Cpp/urdf001/robotarm2/urdf/arm.txt");
    shared_ptr<UrdfModel> model=UrdfModel::fromUrdfStr(UrdfFileFromDisk);
    return 0;
}
