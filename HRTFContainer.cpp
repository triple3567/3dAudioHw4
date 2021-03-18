#include "HRTFContainter.h"

HRTFContainer::HRTFContainer(){
    if(load_data(HRIR_L_DIR, HRIR_R_DIR, ITD_DIR) != 0){
        cout << "Error loading HRTF Data" << endl;
    }
}

int HRTFContainer::load_data(string hrir_l_dir, string hrir_r_dir, string ITD_DIR){
    int success = 0;
    success += load_hrir_l(hrir_l_dir);
    success += load_hrir_r(hrir_r_dir);
    success += load_ITD(ITD_DIR);

    return success;
}

int HRTFContainer::load_hrir_l(string hrir_l_dir){
    fstream file;
    file.open(hrir_l_dir, ios::in);
    string open_bracket = "";
    string closed_bracket = "";
    string value = "";

    if(!file){
        cout << "hrir_l file not found" << endl;
        return -1;
    }
    else{
        for(int i = 0; i < 25; i++){
            getline(file, open_bracket, '[');
            for(int j = 0; j < 50; j++){
                getline(file, open_bracket, '[');
                for(int k = 0; k < 200; k++){
                    getline(file, open_bracket, '[');
                    getline(file, value, ']');

                    stringstream ss(value);

                    ss >> hrir_l[i][j][k];
                    //cout << hrir_l[i][j][k] << endl;
                }
                getline(file, closed_bracket, ']');
            }
            getline(file, closed_bracket, ']');
        }
    }
    return 0;
}

int HRTFContainer::load_hrir_r(string hrir_r_dir){
    fstream file;
    file.open(hrir_r_dir, ios::in);
    string open_bracket = "";
    string closed_bracket = "";
    string value = "";

    if(!file){
        cout << "hrir_l file not found" << endl;
        return -1;
    }
    else{
        for(int i = 0; i < 25; i++){
            getline(file, open_bracket, '[');
            for(int j = 0; j < 50; j++){
                getline(file, open_bracket, '[');
                for(int k = 0; k < 200; k++){
                    getline(file, open_bracket, '[');
                    getline(file, value, ']');

                    stringstream ss(value);

                    ss >> hrir_r[i][j][k];
                    //cout << hrir_l[i][j][k] << endl;
                }
                getline(file, closed_bracket, ']');
            }
            getline(file, closed_bracket, ']');
        }
    }

    return 0;
}

int HRTFContainer::load_ITD(string ITD_dir){
    fstream file;
    file.open(ITD_dir, ios::in);
    string open_bracket = "";
    string closed_bracket = "";
    string value = "";

    if(!file){
        cout << "hrir_l file not found" << endl;
        return -1;
    }
    else{
        for(int i = 0; i < 25; i++){
            getline(file, open_bracket, '[');
            for(int j = 0; j < 50; j++){
                getline(file, open_bracket, '[');
                getline(file, value, ']');

                stringstream ss(value);
                ss >> ITD[i][j];
            }
            getline(file, closed_bracket, ']');
        }
    }

    return 0;
}

float* HRTFContainer::get_hrir_l(int az, int elevation){
    float* value = hrir_l[az][elevation];
    return value;
}

float* HRTFContainer::get_hrir_r(int az, int elevation){
    float* value = hrir_r[az][elevation];
    return value;
}

float HRTFContainer::get_ITD(int az, int elevation){
    float value = ITD[az][elevation];
    return value;
}