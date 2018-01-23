#include "given.h"
/***************************************************************************************************************************
Main Function( write all new functions in user.c only and call them in main.c) 
Compile   Command: make
Execution Command: ./proj2 "input file" "path file" "output file"
****************************************************************************************************************************/
int main(int argc, char **argv)
{
FILE *fisc, *path, *fout;             //file pointers used for .isc file, .path file, and output file
int Max,Bound;                        //maxnode id,Max nodes in a bdd of cct 
NODE *graph;                          //structure used to store the cct information in .isc file 


//Read the .isc file and store the information in graph structure
fisc=fopen(argv[1],"r");                           //file pointer to open .isc file 
graph=(NODE *) malloc(Mnod * sizeof(NODE));        //dynamic memory allocation for graph structure
Max=0; Max=ReadIsc(fisc,graph);                    //read .isc file and return index of last node in graph formed
fclose(fisc);                                      //close file pointer for .isc file
PrintCircuit(graph,Max);                           //print all members of graph structure
test (graph, Max, manager); //BDD user.c function declaration 
manager=Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);  //intializing CUDD package manger

path=fopen(argv[2],"r");						 //File pointer to open .path file

fout=fopen(argv[3],"w");                        //File pointer to open .out file 	

printf("\nNo of Unreferenced Bdds %d\n", Cudd_CheckZeroRef(manager));
Cudd_Quit(manager);                                           //closing the cudd package manager
ClearCircuit(graph,Mnod);                                     //clear memeory for all members of graph
fclose(path);											      //close the path file
fclose(fout);                                                 //close the output file
return 0;
}//end of main
/****************************************************************************************************************************/
