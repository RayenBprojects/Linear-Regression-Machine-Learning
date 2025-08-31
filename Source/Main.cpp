#include "Model/Model.cpp"
#include "../Libs/iotools.h"
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int main(){
    IoTools::PageTool errorPage;

    IoTools::PageTool mainMenu;
    char mainMenuPrompt[] = "-->";
    char mainMenuResponse[500];
    char mainMenuError[] = "Please choose one of the displayed options";
    mainMenu.addText("MAIN MENU\n");
    mainMenu.addText("Data Generation         [1]");
    mainMenu.addText("Training and Evaluation [2]");
    mainMenu.addText("Prediction              [3]");
    mainMenu.addText("Exit                    [0]");
    mainMenu.addPrompt(mainMenuPrompt, mainMenuResponse, mainMenuError, false, true);


    IoTools::PageTool dataPage;
    dataPage.addText("DATA GENERATION\n",true);
    char genericDataError[] = "Please enter a valid input";
    char dataPrompt1[] = "Please enter coefficient m:                ";
    char dataResponse1[500];
    char dataPrompt2[] = "Please enter y at origin b:                ";
    char dataResponse2[500];
    char dataPrompt3[] = "Please enter desired dataset size:         ";
    char dataResponse3[500];
    char dataPrompt4[] = "Please enter the smallest x value:         ";
    char dataResponse4[500];
    char dataPrompt5[] = "Please enter the largest x value:          ";
    char dataResponse5[500];
    char dataPrompt6[] = "Please enter the outlier probability in %: ";
    char dataResponse6[500];
    dataPage.addPrompt(dataPrompt1, dataResponse1, genericDataError);
    dataPage.addText("",true);
    dataPage.addPrompt(dataPrompt2, dataResponse2, genericDataError);
    dataPage.addText("",true);
    dataPage.addPrompt(dataPrompt3, dataResponse3, genericDataError);
    dataPage.addText("",true);
    dataPage.addPrompt(dataPrompt4, dataResponse4, genericDataError);
    dataPage.addText("",true);
    dataPage.addPrompt(dataPrompt5, dataResponse5, genericDataError);
    dataPage.addText("",true);
    dataPage.addPrompt(dataPrompt6, dataResponse6, genericDataError);

    IoTools::PageTool dataSuccess;
    dataSuccess.addText("DATA GENERATION\n", true);
    dataSuccess.addText("Success! Press any key to continue");
    IoTools::PageTool dataFailure;
    dataFailure.addText("DATA GENERATION\n", true);
    dataFailure.addText("Failure. Press any key to continue");

    IoTools::PageTool trainingSuccess;
    trainingSuccess.addText("TRAINING AND EVALUATION\n",true);
    trainingSuccess.addText("Success! Press any key to continue");

    IoTools::PageTool trainingFailure;
    trainingFailure.addText("TRAINING AND EVALUATION\n",true);
    trainingFailure.addText("Failure. Press any key to continue");

    IoTools::PageTool prediction; //non-static page, implementation below
    char genericPredictionError[] = "Please enter a correct value";
    char predictionPrompt[] = "Please enter x value: ";
    char predictionResponse[500];




    DataGen dataSet;
    Model model;
    bool exitFlag = false;

    do{ // SOLUTION TO CRASH, give em default constructors and change the values later
        mainMenu.showPage();


        switch(atoi(mainMenuResponse)){
            case 0:
                {
                exitFlag = true;
                break;
            }

            case 1:
                {
                dataPage.showPage();
                // need input validation here
                dataSet.newData(atof(dataResponse1), atof(dataResponse2), atof(dataResponse3));
                dataSet.generateData(atof(dataResponse4), atof(dataResponse5), atoi(dataResponse6));
                if (dataSet.isGenerated()){
                    dataSuccess.showPage();
                }
                else{
                    dataFailure.showPage();
                }
                while(!kbhit()){}
                getch();
                break;
            }

            case 2:
                {
                if (dataSet.isGenerated()){
                    // somewhere after this is cause of crash
                    model.newInputSet(dataSet);
                    model.train();
                    if (model.isTrained()){
                        trainingSuccess.showPage();
                    }
                    else{
                        trainingFailure.showPage();
                    }
                }
                else{
                    // need error here
                }
                while(!kbhit()){}
                getch();
                break;
            }
            case 3:
                {
                if(model.isTrained()){
                    prediction.clearPage();
                    prediction.addText("PREDICTION\n",true);
                    prediction.addPrompt(predictionPrompt,predictionResponse,genericPredictionError,false, false);
                    // need input validation here
                    prediction.addText("\nThe model predicts y = ",false);
                    prediction.addText(to_string(model.predict(atof(predictionResponse))));
                    prediction.addText("Press any key to continue");

                }
                else{
                    // need error here
                }
                 while(!kbhit()){}
                getch();
                break;
            }
            default:
                {
                // neeed input validation here
                break;
            }
        }
    } while(exitFlag == false);
    return 0;
}