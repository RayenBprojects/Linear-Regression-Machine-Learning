#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

struct DataList{
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

/*
NEVER pass DataGen object by value, use the getCopy() method instead. 
Passing by value will cause the deconstructor to delete all data examples when out of scope.
This is a problem because even if passed by value, the data example addresses are the same.
getCopy() returns another dataset with examples copied from the first.
*/
class DataGen{
    public:

    DataGen(){
        mVariable = 0;
        bVariable = 0;
        length = 0;

        dataGenerated = false;

        firstExample = NULL;
        cursor = NULL;
    }

    ~DataGen(){
        if (dataGenerated == true){
            cursor = firstExample;

            while(cursor != NULL){
                DataList *temp = cursor;
                cursor = cursor->nextExample;
                delete temp;
            }
        }
    }

    bool generateData(float firstFeature, float lastFeature, float m, float b, int size, float outlierProb = 0){
        if (dataGenerated || firstFeature >= lastFeature || size < 2 || outlierProb < 0){
            return false;
        }

        DataList *cursor2; //trails behind cursor
        length = size;
        mVariable= m;
        bVariable = b;
        float range = fabs(((mVariable * lastFeature + bVariable)-(mVariable * firstFeature + bVariable)));
        srand(time(NULL));
        
        float i=firstFeature;
        for (int n = 0 ; n < length ; n++){
            cursor = NULL;
            while (cursor == NULL){
                cursor = new DataList;
            }
            if (n == 0){
                firstExample = cursor;
                cursor2 =cursor;
            }
            else{
                cursor2->nextExample = cursor;
                cursor2 = cursor;
            }

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

            i+= (lastFeature-firstFeature)/((float)(length-1));
            
        }
        
        cursor = firstExample;

        dataGenerated = true;

        return true;
    }

    bool deleteData(){
        if (dataGenerated == true){
            cursor = firstExample;

            while(cursor != NULL){
                DataList *temp = cursor;
                cursor = cursor->nextExample;
                delete temp;
            }

            cursor = NULL;
            firstExample = NULL;
            dataGenerated = false;
            return true;
        }
        else{
            return false;
        }
    }

    int getLength(){
        return length;
    }

    bool advanceCursor(){
        if (dataGenerated == true && cursor->nextExample != NULL){
            cursor = cursor->nextExample;
            return true;
        }
        else{
            return false;
        }
    }

    void resetCursor(){
        cursor = firstExample;
    }

    float getFeature(){
        return cursor->xFeature;
    }

    float getLabel(){
        return cursor->yLabel;
    }

    bool endOfData(){
        if (cursor->nextExample == NULL){
            return true;
        }
        else{
            return false;
        }
    }

    bool isGenerated(){
        return dataGenerated;
    }

    DataGen getCopy(){
        DataGen copy;
        if(!dataGenerated){
            return copy;
        }
        else{
                DataList* cursor2 = firstExample;
                while(cursor2 != NULL){
                    DataList* temp = NULL;
                    while(temp == NULL){
                        temp = new DataList(cursor2->xFeature,cursor2->yLabel);
                    }
                    copy.addExample(temp);

                    cursor2 = cursor2->nextExample;
                }
                copy.mVariable = mVariable;
                copy.bVariable = bVariable;
                return copy;
        }
    }

    private:

    void addExample(DataList* newExample){
        if(!dataGenerated){
            firstExample = newExample;
            cursor = firstExample;
            length = 1;
            dataGenerated = true;
        }
        else{
            DataList* cursor2 = firstExample;
            while(cursor2->nextExample != NULL){
                cursor2 = cursor2->nextExample;
            }
            cursor2->nextExample = newExample;
            length++;
            dataGenerated = true;
        }

    }

    float mVariable; // as in y = mx + b

    float bVariable; // as in y = mx + b

    DataList *firstExample;

    DataList *cursor;

    int length;

    bool dataGenerated;

};

