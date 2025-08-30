#include "Model/Model.cpp"
#include "Libs/iotools.h"
#include <iostream>
#include <stdlib.h>
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
    mainMenu.addPrompt(mainMenuPrompt, mainMenuResponse, mainMenuError, false, true);


    IoTools::PageTool dataPage;
    dataPage.addText("DATA GENERATION\n",true);
    char genericDataError[] = "Please enter a valid input";
    char dataPrompt1[] = "Please enter coefficient m:        ";
    char dataResponse1[500];
    char dataPrompt2[] = "Please enter y at origin b:        ";
    char dataResponse2[500];
    char dataPrompt3[] = "Please enter desired dataset size: ";
    char dataResponse3[500];
    char dataPrompt4[] = "Please enter the smallest x value: ";
    char dataResponse4[500];
    char dataPrompt5[] = "Please enter the largest x value:  ";
    char dataResponse5[500];
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


    bool exitFlag = false;
    return 0;
}