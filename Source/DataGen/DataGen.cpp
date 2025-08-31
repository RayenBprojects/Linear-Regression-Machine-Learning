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

    DataGen(float m = 0, float b = 0, int size = 1){
        mVariable = m;
        bVariable = b;
        if (size>1){
            length = size;
        }
        else{
            length = 1;
        }

        dataGenerated = false;

        firstExample = NULL;
        cursor = NULL;

        while (firstExample == NULL){
            firstExample = new DataList();
        }
        cursor = firstExample;
    }

    ~DataGen(){
        if (dataGenerated != false){
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

    void newData(float m, float b, float size){// must add way to delete old data and refresh, this is temporary
        mVariable = m;
        bVariable = b;
        length = size;
    }

    DataGen copyData(){
        DataGen copyData(mVariable, bVariable, length);
        DataList *tempCursor = NULL;
        DataList *copyCursor = NULL;

        if(!dataGenerated){
            return copyData;
        }

        tempCursor = firstExample->nextExample;
        while(copyCursor == NULL){
            copyCursor = new DataList;
        }

        copyData.firstExample->xFeature=firstExample->xFeature;
        copyData.firstExample->yLabel=firstExample->yLabel;
        copyData.firstExample->nextExample=copyCursor;
        

        for (int i = 0 ; i < length-1 ; i++){
            copyCursor->xFeature=tempCursor->xFeature;
            copyCursor->yLabel=tempCursor->yLabel;

            if (i == length -2){
                while(copyCursor->nextExample == NULL){
                    copyCursor->nextExample= new DataList;
                }
                copyCursor = copyCursor->nextExample;
                tempCursor=tempCursor->nextExample;
            }
        }
        return copyData;
    }

    float getFeature(){
        return cursor->xFeature;
    }

    float getLabel(){
        return cursor->yLabel;
    }

    int getLength(){
        return length;
    }

    void removeExample(float feature){
        if(!dataGenerated && length <= 1){
            return;
        }
        DataList *tempCursor = firstExample;
        DataList *tempCursor2 = firstExample->nextExample;

        if(tempCursor->xFeature == feature){
            delete tempCursor;
        }
        else{
            while(tempCursor2 != NULL){
                if (tempCursor2-> xFeature == feature){
                    tempCursor->nextExample=tempCursor2->nextExample;
                    if (cursor == tempCursor2){
                        if (tempCursor2->nextExample != NULL){ // if cursor happens to be on the example that's getting deleted, it will try to move forward. If not possible, it will move back
                            cursor = tempCursor2->nextExample;
                        }
                        else{
                            cursor = tempCursor;
                        }
                    }
                    delete tempCursor2;
                    tempCursor2 = NULL;
                }
                else{
                    tempCursor2=tempCursor2->nextExample;
                    tempCursor=tempCursor->nextExample;
                }
            }
        }

        length--;
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

    bool isGenerated(){
        return dataGenerated;
    }

    private:

    float mVariable; // as in y = mx + b

    float bVariable; // as in y = mx + bw

    DataList *firstExample;

    DataList *cursor;

    int length;

    bool dataGenerated;

};

