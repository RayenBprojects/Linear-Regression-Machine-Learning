#ifndef IOTOOLS_H //HEADER_FILE_IOTOOLS_H
#define IOTOOLS_H //HEADER_FILE_IOTOOLS_H

#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;


class IoTools{ // Common class for various projects
	
	public:

		static void upLine(int jumps = 1){
			for (int i = 0 ; i < jumps ; i++){
				cout<<"\x1b[1F";
				//cout<<"\033[A";  This break some stuff, this bad, can't find info on what the difference is
			}
		}

		static void downLine(int jumps =1){
			for (int i = 0 ; i < jumps ; i++){
				cout<<endl;
			}
		}

		static void clearLine(){
			cout<<"\x1b[2K";
		}

		static void lineTool(int size, char lineChar = '-', bool returnLine = false){
			for (int i = 0 ; i < size ; i++){
				cout<<lineChar;
			}
			if (returnLine){
				cout<<endl;
			}
		}

		static void barTool(float nominator = 0 , float denominator = 1 , int barLength = 100 , bool percentDisplay = true, bool returnLine = false){
			float tempLengthFloat = (nominator/denominator)*((float)barLength);
			int tempLength = tempLengthFloat;
			if (tempLengthFloat - tempLength > 0.5){
				tempLength++;
			}
	
			cout<<'['; lineTool(tempLength, '|', false); lineTool(barLength - tempLength, '-', false) ; cout<<']';
	
			if (percentDisplay){
				float tempPercent = (nominator/denominator)*100;
				cout<<' '<<fixed<<setprecision(1)<<setw(5)<<tempPercent<<'%';
			}

			if (returnLine){
				cout<<endl;
			}
	} 

	// CONCERN: COULD BREAK IF FED NEWLINES, PLEASE ADD FIX
		static void promptTool(char prompt[500] , char result[500] , char error[500],bool doError = false, bool isNumber = false){

			if (!doError){
				bool errorFlag;
				bool lengthFlag;
				do{
					errorFlag = false;
					lengthFlag = false;
			
					cout<<prompt;
					cin>>result;
			
					for (int i = 0 ; i < 500 ; i++){
						if (result[i] == '\0'){
							lengthFlag = true;
							break;
						}
				
						if (isNumber && (result[i] != '0') && (result[i] != '1') && (result[i] != '2') && (result[i] != '3') && (result[i] != '4') && (result[i] != '5') && (result[i] != '6') && (result[i] != '7') && (result[i] != '8') && (result[i] != '9')){
							errorFlag = true;
							break;
						}
					}
			
					if (!lengthFlag){
						errorFlag = true;
					}
			
					if (errorFlag){
						cout<<error;
				
						while(!kbhit()){}
						getch();
				
						cout<<"\x1b[2K"<<"\x1b[1F"<<"\x1b[2K";
				
					}
			
				} while(errorFlag);
			}
			else{
				cout<<error;
				getch();
				while(!kbhit()){}
				getch();
				cout<<"\x1b[2K"<<"\x1b[1F"<<"\x1b[2K";
			}

		}

	// CONCERN: COULD BREAK IF FED NEWLINES, PLEASE ADD FIX
		static void graphTool(char xName[20], char yName[20], float xMinMax[2], float yMinMax[2], int pointNum, float points[100][2], int xIncr = 10, int yIncr = 5){
			if (yMinMax[0] >= 0){
				// Sectioned off the code that prints the graph without points
				{
					cout<<"          "<<yName<<endl;
					for (int i = 0 ; i < yIncr*6+1 ; i++){
						if (i % 6 == 0){
							cout<<"         -|"<<endl;
						}
						else{
							cout<<"          |"<<endl;
						}
					}

					cout<<"          ";
					lineTool(xIncr*11,'=',false);
					cout<<"== "<<xName<<endl;

					cout<<"           ";
					for (int i =0 ; i < xIncr+1 ; i++){
						cout<<"|          ";
					}

					upLine(2 + 6*yIncr);

					for (int i = 0 ; i <= yIncr ; i++){
						cout<<setw(9)<<fixed<<setprecision(2)<<(yMinMax[1]-i*(yMinMax[1]-yMinMax[0])/yIncr)<<endl;
						if (i != yIncr ){
							for (int n =0 ; n < 5 ; n++){
								cout<<endl;
							}
						}
						else{
							cout<<endl<<endl;
						}
					}

					cout<<"      ";
					for (int i = 0 ; i <= xIncr ; i++){
						cout<<setw(9)<<fixed<<setprecision(2)<<(xMinMax[0]+i*(xMinMax[1]-xMinMax[0])/xIncr);
						if (i != xIncr ){
							cout<<"  ";
						}
					}
				}
				upLine(3+6*yIncr);

				for (int i = 0 ; i <= 6*yIncr ; i++){
					int displayCoords[100];
					int tempPointNum = 0;
					int travel = 0;
					cout<<"\x1b[11C";
					for (int n = 0 ; n < pointNum ; n++){
						if ((points[n][1] <= (yMinMax[1]-i*(yMinMax[1]/(6*yIncr)))) && (points[n][1] > (yMinMax[1]-(i+1)*(yMinMax[1]/(6*yIncr)))) && (points[n][0] <= xMinMax[1]) && (points[n][0] >= xMinMax[0])){
							if ((points[n][0])*(11*xIncr/xMinMax[1]) - (int)((points[n][0])*(11*xIncr/xMinMax[1])) >= 0.5){
								displayCoords[tempPointNum] = (int)((points[n][0])*(11*xIncr/xMinMax[1])) + 1;
							}
							else{
								displayCoords[tempPointNum] = (int)((points[n][0])*(11*xIncr/xMinMax[1]));
							}
							tempPointNum++;
						}
					}
					for (int n = 0 ; n < tempPointNum ; n++){
						for (int j = travel ; j <= displayCoords[n] ; j++){
							if (j == displayCoords[n]){
								cout<<'*';
								//cout<<n;
								travel = displayCoords[n]+1;
								break;
							}
							else{
								cout<<' ';
							}
						}
					}
					cout<<endl;
				}
				cout<<endl<<endl<<endl;
			}
			cout<<endl;
		}

		class PageTool{

			public:

				string *entry;

				PageTool(){
					commandNum = 0;
					textNum = 0;
					returnNum = 0;
					lineNum = 0;
					barNum = 0;
					promptNum = 0;
					graphNum = 0;

					entry = NULL;
					commands = NULL;
					textArgs = NULL;
					returnLineArgs = NULL;
					lineArgs = NULL;
					barArgs = NULL;
					promptArgs = NULL;
					graphArgs = NULL;
				}

				~PageTool(){
					delete[] entry;
					delete[] commands;
					delete[] textArgs;
					delete[] returnLineArgs;

				}

				void showPage(){

					system("cls");

					int count[6] = {0};
					int dropCount = 0; // counts how many lines were added, especially necessary for prompts

					int* promptPositions;
					bool allocFlag;
					do{
						allocFlag = true;
						promptPositions = new int[promptNum];
						if (promptPositions == NULL){
							allocFlag = false;
						}
						else{
							for (int i = 0 ; i < promptNum ; i++){
								promptPositions[i] = 0;
							}
						}
					} while(allocFlag == false);

					for (int i = 0 ; i < commandNum ; i++){

						switch (commands[i]){

							case 0: // addText

								cout<<textArgs[count[TEXT]].text;
								if (textArgs[count[TEXT]].returnLine){
									cout<<endl;
									dropCount++;
								}
								
								for (int i = 0 ; i < textArgs[count[TEXT]].text.length() ; i++){
									if (textArgs[count[TEXT]].text[i] == '\n'){
										dropCount++;
									}
								}
								count[TEXT]++;
								break;

							case 1: // addReturnLine
								for (int n = 0 ; n < returnLineArgs[count[RETURNLINE]].returns ; n++){
									cout<<endl;
									dropCount++;
								}

								count[RETURNLINE]++;
								break;

							case 2: // addLine
								lineTool(lineArgs[count[LINE]].size, lineArgs[count[LINE]].lineChar, lineArgs[count[LINE]].returnLine);

								if (lineArgs[count[LINE]].returnLine){
									dropCount++;
								}
								count[LINE]++;
								break;

							case 3: //  addBarArgs
								barTool(barArgs[count[BAR]].nominator, barArgs[count[BAR]].denominator, barArgs[count[BAR]].barLength, barArgs[count[BAR]].percentDisplay, barArgs[count[BAR]].returnLine);

								if (barArgs[count[BAR]].returnLine){
									dropCount++;
								}
								count[BAR]++;
								break;
							
							case 4: // addPrompt
								cout<<promptArgs[count[PROMPT]].prompt<<endl;

								
								promptPositions[count[PROMPT]] = dropCount;
								dropCount++;
								count[PROMPT]++;
								break;
							
							case 5: // addGraph
								graphTool(graphArgs[count[GRAPH]].xName, graphArgs[count[GRAPH]].yName, graphArgs[count[GRAPH]].xMinMax, graphArgs[count[GRAPH]].yMinMax, graphArgs[count[GRAPH]].pointNum, graphArgs[count[GRAPH]].points, graphArgs[count[GRAPH]].xIncr, graphArgs[count[GRAPH]].yIncr);

								dropCount += 6 + 6*graphArgs[count[GRAPH]].yIncr;
								count[GRAPH]++;
								break;
						}
					}

					int n = 0;
					for (int i = 0 ; i < commandNum ; i++){
						if (commands[i] == PROMPT){
							upLine(dropCount-promptPositions[n]);
							clearLine();
							promptTool(promptArgs[n].prompt, promptArgs[n].result, promptArgs[n].error, promptArgs[n].doError, promptArgs[n].isNumber);
							downLine(dropCount-promptPositions[n]-1);

							n++;
						}
					}

					delete[] promptPositions;
				}

				void clearPage(){
					
					delete[] entry;
					entry = NULL;

					delete[] commands;
					commands = NULL;
					commandNum = 0;
					
					delete[] textArgs;
					textArgs = NULL;
					textNum = 0;

					delete[] returnLineArgs;
					returnLineArgs = NULL;
					returnNum = 0;

					delete[] lineArgs;
					lineArgs = NULL;
					lineNum = 0;

					delete[] barArgs;
					barArgs = NULL;
					barNum = 0;

					delete[] promptArgs;
					promptArgs = NULL;
					promptNum = 0;

					delete[] graphArgs;
					graphArgs = NULL;
					graphNum = 0;
				}

				void addText(string text , bool returnLine = true){

					commandAdd(TEXT);

					textArgs[textNum-1].text = text;
					textArgs[textNum-1].returnLine = returnLine;
				}

				void addReturnLine(int returns = 1){

					commandAdd(RETURNLINE);

					returnLineArgs[returnNum-1].returns = returns;
				}

				void addLine(int size, char lineChar = '-', bool returnLine = true){

					commandAdd(LINE);
					lineArgs[lineNum-1].size = size;
					lineArgs[lineNum-1].lineChar = lineChar;
					lineArgs[lineNum-1].returnLine = returnLine; // unrelated to returnLine functionality, horrible naming I know
				}

				void addBar(float nominator = 0, float denominator = 1, int barLength = 100, bool percentDisplay = true, bool returnLine = true){
					commandAdd(BAR);

					barArgs[barNum-1].nominator = nominator;
					barArgs[barNum-1].denominator = denominator;
					barArgs[barNum-1].barLength = barLength;
					barArgs[barNum-1].percentDisplay = percentDisplay;
					barArgs[barNum-1].returnLine = returnLine;
				}

				void addPrompt( char prompt[500], char result[500], char error[500], bool doError = false, bool isNumber = false ){
					commandAdd(PROMPT);

					promptArgs[promptNum-1].prompt = prompt;
					promptArgs[promptNum-1].result = result;
					promptArgs[promptNum-1].error = error;
					promptArgs[promptNum-1].doError = doError;
					promptArgs[promptNum-1].isNumber = isNumber;
				}

				void addGraph(char xName[20], char yName[20], float xMinMax[2], float yMinMax[2], int pointNum, float points[100][2], int xIncr = 10, int yIncr = 5){
					commandAdd(GRAPH);

					graphArgs[graphNum-1].xName = xName;
					graphArgs[graphNum-1].yName = yName;
					graphArgs[graphNum-1].xMinMax = xMinMax;
					graphArgs[graphNum-1].yMinMax = yMinMax;
					graphArgs[graphNum-1].pointNum = pointNum;
					for (int i = 0 ; i < 100 ; i++){
						for (int n = 0 ; n < 100 ; n++){
							graphArgs[graphNum-1].points[i][n] = points[i][n];
						}
					}
					graphArgs[graphNum-1].yIncr = yIncr;
					graphArgs[graphNum-1].xIncr = xIncr;
				}
			private:

				int *commands;

				int commandNum;

				int textNum;

				int returnNum;

				int lineNum;

				int barNum;

				int promptNum;

				int graphNum;

				struct Text{
					string text;
					bool returnLine;
				};

				struct ReturnLine{
					int returns;
				};

				
				struct Line{
					int size;
					char lineChar;
					bool returnLine;
				};

				struct Bar{
					float nominator;
					float denominator;
					int barLength;
					bool percentDisplay;
					bool returnLine;
				};

				struct Prompt{
					char* prompt;
					char* result;
					char* error;
					bool doError;
					bool isNumber;
				};

				struct Graph{
					char* xName;
					char* yName;
					float* xMinMax;
					float* yMinMax;
					int pointNum;
					float points[100][2];
					int xIncr;
					int yIncr;
				};

				Text *textArgs;

				ReturnLine *returnLineArgs;

				Line *lineArgs;

				Bar *barArgs;

				Prompt *promptArgs;

				Graph *graphArgs;

				const short TEXT = 0;

				const short RETURNLINE = 1;

				const short LINE = 2;

				const short BAR = 3;

				const short PROMPT = 4;

				const short GRAPH = 5;

				void commandAdd(short newCommand){

					commandNum++;

					bool allocFlag;
					do{
						allocFlag = true;

						int *tempAlloc = new int[commandNum];

						if (tempAlloc == NULL){
							allocFlag = false;
						}
						else{
							for (int i = 0 ; i < commandNum-1 ; i++){
								tempAlloc[i] = commands[i];
							}
							delete[] commands;
							commands = tempAlloc;
						}
					} while(allocFlag == false);

					commands[commandNum-1] = newCommand;

					do{
						allocFlag = true;

						void* tempAlloc;

						Text *textAlloc;
						ReturnLine *returnLineAlloc;
						Line *lineAlloc;
						Bar *barAlloc;
						Prompt *promptAlloc;
						Graph *graphAlloc;

						switch(newCommand){
							case 0:
								textNum++;
								textAlloc = new Text[commandNum];

								if (textAlloc == NULL){
									allocFlag = false;
								}
								else{
									for (int i = 0 ; i < textNum-1 ; i++){
										textAlloc[i] = textArgs[i];
									}
									delete[] textArgs;
									textArgs = textAlloc;
								}
								break;
							
							case 1:
								returnNum++;
								returnLineAlloc = new ReturnLine[commandNum];

								if (returnLineAlloc == NULL){
									allocFlag = false;
								}
								else{
									for (int i = 0 ; i < returnNum-1 ; i++){
										returnLineAlloc[i] = returnLineArgs[i];
									}
									delete[] returnLineArgs;
									returnLineArgs = returnLineAlloc;
								}
								break;

							case 2:
								lineNum++;
								lineAlloc = new Line[commandNum];

								if (lineAlloc == NULL){
									allocFlag = false;
								}
								else{
									for (int i = 0 ; i < lineNum-1 ; i++){
										lineAlloc[i] = lineArgs[i];
									}
									delete[] lineArgs;
									lineArgs = lineAlloc;
								}
								break;
							
							case 3:
								barNum++;
								barAlloc = new Bar[commandNum];

								if (barAlloc == NULL){
									allocFlag = false;
								}
								else{
									for (int i = 0 ; i < lineNum-1 ; i++){
										barAlloc[i] = barArgs[i];
									}
									delete[] barArgs;
									barArgs = barAlloc;
								}
								break;
							
							case 4:
								promptNum++;
								promptAlloc = new Prompt[commandNum];

								if (promptAlloc == NULL){
									allocFlag = false;
								}
								else{
									for (int i = 0 ; i < promptNum-1 ; i++){
										promptAlloc[i] = promptArgs[i];
									}
									delete[] barArgs;
									promptArgs = promptAlloc;
								}
								break;

							case 5:
								graphNum++;
								graphAlloc = new Graph[commandNum];

								if (graphAlloc == NULL){
									allocFlag = false;
								}
								else{
									for (int i = 0 ; i < graphNum-1 ; i++){
										graphAlloc[i] = graphArgs[i];
									}
									delete[] graphArgs;
									graphArgs = graphAlloc;
								}
								break;
						}
					} while (allocFlag == false);

				}

		};

	};

#endif