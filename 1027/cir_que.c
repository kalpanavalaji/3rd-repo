#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#define SIZE 20
pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;
void *enqueue(int);
void *dequeue();
void *display();
int cqueue[SIZE], front = -1, rear = -1,NMSG;

int main()
{
   int choice, value,i;
	pthread_t thread1, thread2;
   while(1){
      printf("\n****** MENU ******\n");
      printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
      printf("Enter your choice: ");
      scanf("%d",&choice);
      switch(choice){
	 case 1:printf("how many values u want to enqueue\n");
		scanf("%d",&NMSG);
		for(i=0;i<NMSG;i++)
		{ 
		printf("\nEnter the value to be insert:  ");
		 scanf("%d",&value);
		int iret1=pthread_create( &thread1, NULL,enqueue(value),NULL);
		if(iret1)
		{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
	 	exit(EXIT_FAILURE);

	 	}
		}
		pthread_exit(0);
		 break;
	 case 2:printf("how many values u want to dequeue\n");
                scanf("%d",&NMSG);
                for(i=0;i<NMSG;i++)
                {
                int iret1=pthread_create( &thread2, NULL,dequeue,NULL);
		if(iret1)
		{
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
	 	exit(EXIT_FAILURE);
		}
	}
		pthread_exit(0);
                
		break;
	 case 3: display();
		 break;
	 case 4: exit(0);
	 default: printf("\nPlease select the correct choice!!!\n");
	

      }
   
}

	pthread_join( thread1, NULL);
        pthread_join( thread2, NULL);
}

void *enqueue(int value)
{
	pthread_mutex_lock( &count_mutex );
	
   if(cqueue[rear]>=(SIZE-NMSG)||(front == 0 && rear == SIZE - 1))
	{
      printf("\nCircular Queue is Full! Insertion not possible!!!\n");
	pthread_cond_wait( &condition_var, &count_mutex );
	}
   else{
      if(rear == SIZE-1 && front != 0)
	 rear = -1;
      cqueue[++rear] = value;
      printf("\nInsertion Success!!!\n");
      if(front == -1)
	 front = 0;
	pthread_cond_signal( &condition_var );
   }
pthread_mutex_unlock( &count_mutex );
//pthread_exit(0);
}
void *dequeue()
{
	 pthread_mutex_lock( &count_mutex );
   if(cqueue[front]>=(SIZE-NMSG)||(front == -1 && rear == -1))
	{
      printf("\nCircular Queue is Empty! Deletion is not possible!!!\n");
	pthread_cond_wait( &condition_var, &count_mutex );
	}
   else{
      printf("\nDeleted element : %d\n",cqueue[front++]);
      if(front == SIZE)
	 front = 0;
      if(front-1 == rear)
	 front = rear = -1;
	pthread_cond_signal( &condition_var );
   }

	pthread_mutex_unlock( &count_mutex );
//	pthread_exit(0);

}

void *display()
{
   if(front == -1)
      printf("\nCircular Queue is Empty!!!\n");
   else{
      int i = front;
      printf("\nCircular Queue Elements are : \n");
      if(front <= rear){
	 while(i <= rear)
	    printf("%d\t",cqueue[i++]);
      }
      else{
	 while(i <= SIZE - 1)
	    printf("%d\t", cqueue[i++]);
	 i = 0;
	 while(i <= rear)
	    printf("%d\t",cqueue[i++]);
      }
   }
}
