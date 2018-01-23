#include"given.h"
#include <time.h>
void test( NODE *graph, int Max,DdManager *manager )

{
int i=0,j=0,k=0;
DdNode *temp0, *temp1, *temp2, *temp3,*temp4,*fun0,*fun1,*fun2,*fun3,*efun1,*efun2,*a;        //function bdds

LIST *temp;
printf("\nBDD_Demo_Start\n*************\n");	
manager = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); //intializing CUDD package manger

/*1st for loop starts*/
for ( i=1; i<= Max ; i++)
  {
	if ( graph[i].typ != 0 )
	{
	switch(graph[i].typ) 
		{
	case INPT:
		graph[i].fun=Cudd_bddIthVar(manager, j);  Cudd_Ref(graph[i].fun);
		//printf("........BDD of INPT=%d........ \n",i); 
		//Cudd_PrintMinterm(manager,graph[i].fun);
		j++;
		break;

	case NAND:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddAnd(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1);  
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2);  
		temp=temp-> nxt;	
		
		temp3=Cudd_ReadOne(manager);	Cudd_Ref(temp1);  
		fun3=Cudd_ReadLogicZero(manager);              Cudd_Ref(fun1);   
		}

		graph[i].fun=Cudd_Not(temp1);	Cudd_Ref(graph[i].fun); Cudd_RecursiveDeref(manager,temp1);
		printf("\nFor Node %d minterms:\n",i);
		Cudd_PrintMinterm(manager,graph[i].fun);
		
		Cudd_RecursiveDeref(manager,temp3);
		Cudd_RecursiveDeref(manager,fun3);
		break;

	case FROM:	
		temp=NULL;
		temp=graph[i].fin;
		graph[i].fun=graph[temp->id].fun; Cudd_Ref(graph[i].fun);
		
		break;

	case AND: 
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddAnd(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1); 
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2); 
		temp=temp-> nxt;	
		}
		graph[i].fun=temp1; Cudd_Ref(graph[i].fun); Cudd_RecursiveDeref(manager,temp1);  
		
		break; 

	case OR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddOr(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1);  
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2); 
		temp=temp-> nxt;	
		}		
		graph[i].fun=temp1; Cudd_Ref(graph[i].fun); Cudd_RecursiveDeref(manager,temp1);  
		
		break; 

	case NOR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);
						
		while(temp !=NULL)
		{
		temp2=Cudd_bddOr(manager,temp1,graph[temp->id].fun); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1); 
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2);  
		temp=temp-> nxt;	
		}
		graph[i].fun=Cudd_Not(temp1);	Cudd_Ref(graph[i].fun);	Cudd_RecursiveDeref(manager,temp1);
		
		break; 

	case XOR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager); Cudd_Ref(temp1);
		while (temp!= NULL) {
		temp2=Cudd_bddAnd(manager, temp1, Cudd_Not(graph[temp->id].fun) ); Cudd_Ref(temp2); 
		temp3=Cudd_bddAnd(manager, Cudd_Not(temp1),  graph[temp->id].fun ); Cudd_Ref(temp3); Cudd_RecursiveDeref (manager, temp1);
		temp1=Cudd_bddOr(manager, temp2, temp3); Cudd_Ref(temp1); Cudd_RecursiveDeref (manager, temp2); Cudd_RecursiveDeref (manager, temp3);
		temp=temp->nxt;
		}
		graph[i].fun=temp1; Cudd_Ref( graph[i].fun );	Cudd_RecursiveDeref (manager, temp1);	
		
		break; 
	
	case XNOR:
		temp=NULL;
		temp=graph[i].fin;
		temp1=Cudd_ReadOne(manager); Cudd_Ref(temp1);
		while (temp!= NULL) {
		temp2=Cudd_bddAnd(manager, temp1, Cudd_Not(graph[temp->id].fun) ); Cudd_Ref(temp2); 
		temp3=Cudd_bddAnd(manager, Cudd_Not(temp1),  graph[temp->id].fun ); Cudd_Ref(temp3); Cudd_RecursiveDeref (manager, temp1);
		temp1=Cudd_bddOr(manager, temp2, temp3); Cudd_Ref(temp1); Cudd_RecursiveDeref (manager, temp3); Cudd_RecursiveDeref (manager, temp2);
		temp=temp->nxt;
		}
		graph[i].fun=Cudd_Not(temp1); Cudd_Ref( graph[i].fun );	Cudd_RecursiveDeref (manager, temp1);	
		
		break;  

	case BUFF:
		temp=NULL;
		temp=graph[i].fin;
		graph[i].fun=graph[temp->id].fun; Cudd_Ref(graph[i].fun);
		
		break; 

	case NOT:
		temp=NULL;
		temp=graph[i].fin;
		graph[i].fun=Cudd_Not( graph[temp->id].fun );	Cudd_Ref(graph[i].fun);
		
		break;  
		
		} /*end of switch*/

	} /*end of if*/

 } /*end of 1st for loop*/

//	---------------------my code starts here ------------------------------------
//	reading the .path file and stores in path[i] 

int path[100];
FILE *file = fopen("c880.path", "r");

    i=0;
    while( fscanf ( file, "%d", & path[i] ) != EOF ) 
	{
		i++;
   	}
    fclose(file);
	
	j=i--;
	for ( i=0 ; i<j ; i++ )
	{
		//printf("for path[%d] =%d \n",i , path[i] );
	}


for ( i=1; i<= Max ; i++)
{
	if ( graph[i].typ !=0 ) //eleminating other not used input such as 4 , 5 etc...
	{
		graph[i].p1=Cudd_bddXor( manager, graph[i].fun, Cudd_ReadLogicZero(manager) );
		Cudd_Ref (graph[i].p1);
		graph[i].p2=Cudd_bddXor( manager, graph[i].fun, Cudd_ReadOne(manager) );
		Cudd_Ref (graph[i].p2);
		//printf("for node %d the logic '0' minterms:\n", i ) ;
		//Cudd_PrintMinterm(manager,graph[i].p1);
		//printf("for node %d the logic '1' minterms:\n", i ) ;
		//Cudd_PrintMinterm(manager,graph[i].p2);
	}
} 

//new section 
double min_count;
j=1;
for ( j = 1 ; j <= 5 ; j++)
{
	i = path[j];
	//printf("for j=%d my i value = %d where i = path[j];\n",j,i);
	//graph[i].mark=1;  //to mark the node 14,16,20,22
	if( graph[i].typ != 10 ) // NAND or from any gate
	{
	temp=NULL;
	temp=graph[i].fin;
	temp1=Cudd_ReadOne(manager);	Cudd_Ref(temp1);	
	temp3=Cudd_ReadOne(manager);	Cudd_Ref(temp3);	
	while(temp !=NULL)
		{
		temp2=Cudd_bddAnd(manager,temp1,graph[temp->id].p1); 
		Cudd_Ref(temp2);   	Cudd_RecursiveDeref(manager,temp1); 
		temp1=temp2; Cudd_Ref(temp1);  	Cudd_RecursiveDeref(manager,temp2); 
		
		temp4=Cudd_bddAnd(manager,temp3,graph[temp->id].p2); 
		Cudd_Ref(temp4);   	Cudd_RecursiveDeref(manager,temp3); 
		temp3=temp4; Cudd_Ref(temp3);  	Cudd_RecursiveDeref(manager,temp4); 
		temp=temp-> nxt;	
		}
	graph[i].p1=temp1; Cudd_Ref(graph[i].p1); Cudd_RecursiveDeref(manager,temp1);  
	graph[i].p2=temp3; Cudd_Ref(graph[i].p2); Cudd_RecursiveDeref(manager,temp3); 
	printf("\nFor node %d, OFF inpupt minterms P1:\n", i );
	Cudd_PrintMinterm(manager,graph[i].p1);
	printf("For node %d, ON inpupt minterms P2:\n", i );
	Cudd_PrintMinterm(manager,graph[i].p2);
	//break; 
	}

	if( graph[i].typ == 10 ) // FROM
	{
	temp=NULL;
	temp=graph[i].fin;
	graph[i].p1=graph[temp->id].p1; Cudd_Ref(graph[i].p1);
	graph[i].p2=graph[temp->id].p2; Cudd_Ref(graph[i].p2);

	printf("\nFor node %d, OFF inpupt minterms P1:\n", i );
	Cudd_PrintMinterm(manager,graph[i].p1);
	printf("For node %d, ON inpupt minterms P2:\n", i );
	Cudd_PrintMinterm(manager,graph[i].p2);
	//break;
	}
	//to count my min terms
	//min_count = Cudd_CountMinterm(manager, graph[i].p1, 4);
	//printf("at node %d minterms counts= %lf \n", i, min_count );
	//printf(" my max_path_value = %d",max_path_value);
}


//---------------------my code ends here ------------------------------------


//dereferencing all the created BDDs
for ( i=1; i<= Max ; i++)
{
	if ( graph[i].typ != 0 )
	{
		Cudd_RecursiveDeref (manager, graph[i].fun);
		Cudd_RecursiveDeref (manager, graph[i].p1);
		Cudd_RecursiveDeref (manager, graph[i].p2);
	}
}
printf("\nNo of Unreferenced Bdds %d\n", Cudd_CheckZeroRef(manager));	
return;	
}




