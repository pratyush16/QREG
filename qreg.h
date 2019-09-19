#include<iostream>
#include<string>
#include<math.h>

using namespace std;

class qreg{
    private:
        int size;
    public:
        double * reg;
        qreg(); //default constructor
        qreg(int s); //full constructor
        int Size(); //gets size of register
        void setSize(int s); //sets size of register
        void setState(int state); //sets the state of the qreg
        void qMeasure(); //measures the qreg
        void CNOT(); //applies CNOT gate to 2-qubit register
        void Hadamard(); //applies Hadamard gate to 1-qubit register
        void qCombine(qreg q1, qreg q2); //combines two qregs into 1 bigger qreg
        qreg * qSeparate(); //separates a register into an array of single qubits
        void qEntangle(qreg x, qreg y); //places two qubits into a bell state 
        void qPrint(); //displays qreg
};