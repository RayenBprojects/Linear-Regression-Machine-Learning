#include "../DataGen/DataGen.cpp"
#include <cmath>
using namespace std;

class Model{

    public:

    Model(DataGen inputSet, float threshold){ // threshold is the max allowed square difference ratio before example deletion, 0 generations means infinite tries
        mVariable = 0;
        bVariable = 0;
        trained = false;


        if (threshold > 1.1){
            limit = threshold;
        }
        else{
            limit = 1.1;
        }

        originalDataSet = inputSet;

        refinedDataSet = inputSet.copyData();

    }

    void train(){
        if (trained == true){
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
            }
        }

        mVariable = ((sumX)*sumY-sampleLength*sumXY)/(pow(sumX,2)-sampleLength*sumXSquared);
        bVariable = (1/sampleLength)*(sumY - mVariable*sumX);

        trained = true;
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

    float limit;

    DataGen originalDataSet;

    DataGen refinedDataSet;

    bool trained;

};