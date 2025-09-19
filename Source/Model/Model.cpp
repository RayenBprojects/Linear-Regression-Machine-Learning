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

        data = true;

    }

    void newInputSet(DataGen dataSet){
        trained = false;

        originalDataSet = dataSet;
        mVariable = 0;
        bVariable = 0;

        data = true;
    }

    bool train(){

        if(!data || originalDataSet.getLength() == 0){
            return false;
        }

        float sumX = 0;
        float sumXSquared = 0;
        float sumY = 0;
        float sumXY = 0;
        float length = originalDataSet.getLength();
        float sampleLength = 0;

        for (int i = 0 ; i < length ; i++){
            if (i%8 != 0){
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
        originalDataSet.resetCursor();
        return true;
    }

    bool isTrained(){
        return trained;
    }

    float evaluate(){ // returns sum of squares, the smaller the better, 0 if not trained
        if (!trained){
            return -1 ;
        }

        float sum = 0;
        for (int i = 0 ; i < originalDataSet.getLength() ; i++){
            sum += pow(originalDataSet.getFeature()*mVariable+bVariable-originalDataSet.getLabel(),2);
        }
        return sum;
    }

    float predict(float feature){
        if(trained){
            return mVariable*feature+bVariable;
        }
        else{
            return 0;
        }
    }

    private:

    float mVariable;

    float bVariable;

    DataGen originalDataSet;

    bool trained;

    bool data;

};