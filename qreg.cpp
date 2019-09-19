#include<iostream>
#include"qreg.h"
#include<string>
#include<math.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

qreg::qreg(){
    size = 1;
    static bool seeded = false;

    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    for (int i = 0; i < static_cast<int>(pow(2,size)); i++){
        reg[i] = rand();
    }
}

qreg::qreg(int s){
    size = s;
    double sum = 0;
    reg = new double[static_cast<int>(pow(2,size))];

    static bool seeded = false;
    if(!seeded) {
        srand(time(NULL));
        seeded = true;
    }

    for (int i = 0; i < static_cast<int>(pow(2,size)); i++){
        reg[i] = rand();
        sum += reg[i];
    }

    if (sum!= 100){
        for (int i = 0; i < static_cast<int>(pow(2,size)); i++){
            reg[i] *= 1/sum;
        }
    }
}

int qreg::Size(){
    return size;
}

void qreg::setSize(int s){
    size = s;
}

void qreg::setState(int state){
    /*for (int i = 0; i < static_cast<int>(pow(2,size)); i++){
        if(x == state){
            reg[i] = 1;
            continue;
        }
        reg[i]=0;
    }*/
}

void qreg::qMeasure(){
    srand (time(NULL));
    double n = rand() % 100;
    n /= 100;
    double x = 0;

    for (int i = 0; i < static_cast<int>(pow(2,size)); i++){
        if(n >= x && n < (reg[i] + x)){
            reg[i] = 1;
            continue;
        }
        x += reg[i];
        reg[i]=0;
    }
}

void qreg::CNOT(){
    if (size != 2){
        cout << "ERROR: register size out of bounds" << endl;
        return;
    }

    int cnotMat [4][4] = {{1,0,0,0},
                          {0,1,0,0},
                          {0,0,0,1},
                          {0,0,1,0}};
    double regCopy [4];

    for (int i = 0; i < 4; i++){
        regCopy[i] = reg[i];
        reg[i]=0;
    }

    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            reg[i] += (cnotMat[i][j] * regCopy[j]);
        }
    }
}

void qreg::Hadamard(){
    if (size != 1){
        cout << "ERROR: register size out of bounds" << endl;
        return;
    }

    double hadMat [2][2] = {{1/sqrt(2),1/sqrt(2)},
                            {1/sqrt(2),(-1)/sqrt(2)}};
    double regCopy [2];

    for (int i = 0; i < 2; i++){
        regCopy[i] = reg[i];
        reg[i]=0;
    }

    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            reg[i] += (hadMat[i][j] * regCopy[j]);
        }
    }
}

void qreg::qCombine(qreg q1, qreg q2){
    if (size != q1.size + q2.size){
        cout << "ERROR: register size out of bounds" << endl;
        return;
    }
    
    else{
        int k = 0;
        while (k < static_cast<int>(pow(2,size))){
            for (int i = 0; i < static_cast<int>(pow(2,q1.size)); i++){
                for (int j = 0; j < static_cast<int>(pow(2,q2.size)); j++){ 
                    reg[k] = q1.reg[i] * q2.reg[j];
                    k++;
                }
            }
        }
    }
}

qreg * qSeparate(){
    
}

void qreg::qEntangle(qreg x, qreg y){
    x.Hadamard();
    qCombine(x, y);
    CNOT();
}

void qreg::qPrint(){
    int numberOfBits = size;
    for (int n = 0; n < static_cast<int>(pow(2,size)); n++){
        cout << reg[n];
        cout << "|";
        for (int i=numberOfBits-1; i>=0; i--) {
            bool isBitSet = (n & (1<<i));
            if (isBitSet) {
                cout << "1";
            } else {
                cout << "0";
            }
        }
        cout << ">";
        if (n < static_cast<int>(pow(2,size))-1){
            cout << " + ";
        }
    }
    cout << endl;
}