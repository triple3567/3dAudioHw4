#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

class HRTFContainer{
    public:

    const string HRIR_L_DIR = "./data/hrir_l.txt";
    const string HRIR_R_DIR = "./data/hrir_r.txt";
    const string ITD_DIR = "./data/ITD.txt";

    HRTFContainer();

    int load_data(string hrir_l_dir, string hrir_r_dir, string ITD_dir);
    float* get_hrir_l(int az, int elevation);
    float* get_hrir_r(int az, int elevation);
    float get_ITD(int az, int elevations);

    private:

    int load_hrir_l(string hrir_l_dir);
    int load_hrir_r(string hrir_l_dir);
    int load_ITD(string ITD_dir);

    float hrir_l[25][50][200];
    float hrir_r[25][50][200];
    float ITD[25][50];
};