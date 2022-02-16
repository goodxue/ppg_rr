#include "ppg_rr_cpp.h"
#include <fstream>
#include <sstream>

using namespace std;
int main() 
{
    std::vector<double> ppg (500);
    std::vector<double> v1 (500);
    ifstream inFile("../1.csv", ios::in);
	string lineStr;

    if(!inFile){
        cout<<"failed to open the file."<<endl;
    }

    int i = 0;
    int st = 500;
	while (getline(inFile, lineStr))
	{
        i++;
        if (i<=st){
            continue;
        }
        else if(i >st+500){
            break;
        }
		// 打印整行字符串
		//cout << lineStr << endl;
		// 存成二维表结构
		stringstream ss(lineStr);
		string str;
		// 按照逗号分隔
        getline(ss, str, ',');
        int temp;
        //cout<<str<<endl;
        v1[i-st-1] = atof(str.c_str());
		getline(ss, str, ',');
        ppg[i-st-1] = atof(str.c_str());
	}
    // for (int i = 0;i < ppg.size();i++){
    //     cout<<ppg[i]<<" ";
    // }
    // cout<<endl;
    // cout<<i<<endl;


    ppg_rr(ppg,v1,true);
    return 0;
}