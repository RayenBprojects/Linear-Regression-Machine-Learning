#include <stdlib.h>
#include <ctime>
#include <cmath>

class DataList{
    private: 

    friend class DataGen;

    DataList(float x = 0, float y = 0, DataList *next= NULL){
        xFeature = x;

        yLabel = y;

        nextExample = next;
    }

    float xFeature;

    float yLabel;

    DataList *nextExample;
};

class DataGen{
    public:

    DataGen(float m, float b, int size){
        mVariable = m;
        bVariable = b;
        length = size;

        dataGenerated = false;

        firstExample = NULL;
        cursor = NULL;

        while (firstExample == NULL){
            firstExample = new DataList();
        }
        cursor = firstExample;
    }

    ~DataGen(){
        if (dataGenerated != NULL){
            cursor = firstExample;
            DataList *temp = cursor;

            do{
                cursor = cursor->nextExample;
                delete temp;
                temp = cursor;
            } while (cursor != NULL);
        }
        else{
            delete firstExample;
        }
    }

    void generateData(float firstFeature, float lastFeature, float outlierProb = 1){
        if (dataGenerated || firstFeature > lastFeature){
            return;
        }

        cursor = firstExample;

        float range = fabs(((mVariable * lastFeature + bVariable)-(mVariable * firstFeature + bVariable)));
        srand(time(NULL));

        float i=firstFeature;;
        for (int n = 0 ; n < length ; n++){

            cursor->xFeature = i;
            if (float(rand()%101) >= (101-outlierProb)){
                if (rand()%2 == 1){
                    cursor->yLabel = mVariable * i + bVariable + range * ((float(rand()%6) + 5)/100);
                }
                else{
                    cursor->yLabel = mVariable * i + bVariable - range * ((float(rand()%6) + 5)/100);
                }
            }
            else{
                if (rand()%2 == 1){
                    cursor->yLabel = mVariable * i + bVariable + range * ((float(rand()%3))/100);
                }
                else{
                    cursor->yLabel = mVariable * i + bVariable - range * ((float(rand()%3))/100);
                }
            }

            if (n+1 != length){
                cursor->nextExample = new DataList();
                cursor = cursor ->nextExample;
            }
            i+= (lastFeature-firstFeature)/((float)(length-1));
        }
        
        cursor = firstExample;
        dataGenerated = true;
    }

    float getFeature(){
        return cursor->xFeature;
    }

    float getLabel(){
        return cursor->yLabel;
    }

    void advanceCursor(){
        if (cursor->nextExample != NULL){
            cursor = cursor->nextExample;
        }
    }

    void resetCursor(){
        cursor = firstExample;
    }

    bool endOfData(){
        if (cursor->nextExample == NULL){
            return true;
        }
        else{
            return false;
        }
    }

    private:

    float mVariable; // as in y = mx + b

    float bVariable; // as in y = mx + bw

    DataList *firstExample;

    DataList *cursor;

    int length;

    bool dataGenerated;

};

