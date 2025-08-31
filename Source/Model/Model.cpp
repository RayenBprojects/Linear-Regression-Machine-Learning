#include "../DataGen/DataGen.cpp"
#include <cmath>
#include <iostream>
using namespace std;

class Model{

    public:

    Model(){ 
        mVariable = 0;
        bVariable = 0;
        trained = false;

        data = false;

    }

    Model(DataGen inputSet){ 
        mVariable = 0;
        bVariable = 0;
        trained = false;

        originalDataSet = inputSet;

        refinedDataSet = inputSet.copyData();

        data = true;

    }

    void train(){
        if (trained == true || !data){
            return;
        }
        float sumX = 0;
        float sumXSquared = 0;
        float sumY = 0;
        float sumXY = 0;
        float length = originalDataSet.getLength();
        float sampleLength = 0;

        for (int i = 0 ; i < length ; i++){
            if (!(i%8 == 0)){
                sumX += originalDataSet.getFeature();
                sumXSquared += pow(originalDataSet.getFeature(),2);
                sumY += originalDataSet.getLabel();
                sumXY += originalDataSet.getFeature()*originalDataSet.getLabel();
                sampleLength++;
                originalDataSet.advanceCursor();
            }
            else{
                originalDataSet.advanceCursor();
            }
        }
        mVariable = ((sumX)*sumY-sampleLength*sumXY)/(pow(sumX,2)-sampleLength*sumXSquared);
        bVariable = (1/sampleLength)*(sumY - mVariable*sumX);

        trained = true;
    }

    void newInputSet(DataGen dataSet){
        trained = false;
        originalDataSet = dataSet;
        refinedDataSet = dataSet.copyData();
        data = true;
    }

    bool isTrained(){
        return trained;
    }

    float evaluate(){ // returns sum of squares, the smaller the better, 0 if not trained
        if (!trained){
            return 0 ;
        }

        float sum = 0;
        for (int i = 0 ; i < refinedDataSet.getLength() ; i++){
            sum += pow(refinedDataSet.getFeature()*mVariable+bVariable-refinedDataSet.getLabel(),2);
        }
        return sum;
    }

    float predict(float feature){
        return mVariable*feature+bVariable;
    }

    private:

    float mVariable;

    float bVariable;

    DataGen originalDataSet;

    DataGen refinedDataSet;

    bool trained;

    bool data;

};