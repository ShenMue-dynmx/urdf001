#include <iostream>
#include <fstream>
#include <cstdio>
#include <filesystem>
#include <unistd.h>

#include "urdf/common.h"
#include "urdf/geometry.h"
#include "urdf/joint.h"
#include "urdf/model.h"

using namespace urdf;
using namespace std;
using std::filesystem::current_path;

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

string GetCurrentDir(bool debug=false)
{
    char tmp[256];
    getcwd(tmp, 256);
    // return tmp; //Would return the build folder
    //lets trim 6 chars from the end (/build) 
    string _tmp=tmp;
    string mainf=_tmp.substr(0, _tmp.size()-6);
    if (debug) cout<<"Executing Dir:" << tmp<<endl<<"Main Dir:"<<mainf<<endl;
    return mainf;
}

//TODO cycle from root to end of chain
// create arrays for origins and axis
//create methods to get rotation
void Starter()
{
    LoadUrdf(GetCurrentDir(false)+"/robotarm2/urdf/arm.urdf");
    shared_ptr<UrdfModel> model=UrdfModel::fromUrdfStr(UrdfFileFromDisk);
    map<string, std::shared_ptr<Joint>> jntmap=model->joint_map;
    auto root= model->root_link->parent_joint;
    Joint rt=(*root);
    for(map<string,shared_ptr<Joint>>::iterator iter=jntmap.begin();iter!=jntmap.end();iter++)
    {
        //cout<<iter->first << "  :  " << iter->second.get()->parent_to_joint_transform.rotation.x<<endl;

    }
}


int main(){
    
    Starter();
    
    
    return 0;
}
