#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int choice,track,no_req,head,head1,distance;
int dis_req[100],finish[100];
void input()
{
    printf("\nenter total no of tracks ");
    scanf("%d",&track);
    printf("\nenter total no of disk request ");
    scanf("%d",&no_req);
    printf("\n Enter disc requests ");
    int i;
    for(i=0;i<no_req;i++)
    {
        scanf("%d",&dis_req[i]);
    }
    
    printf("\nenter head position");
    scanf("%d",&head1);
    
}
void sort()
{
    int i,j;
    for(i=0;i<no_req;i++)
    {
        for(j=i+1;j<no_req;j++)
        {
            if(dis_req[i]>dis_req[j])
            {
                int temp=dis_req[i];
                dis_req[i]=dis_req[j];
                dis_req[j]=temp;
            }
        }
    }
}
void sstf()
{
    input();
    int min,diff;
    int pending=no_req;
    int i,index;
    distance=0;
    head=head1;
    
    //initiallly all the disc requests are pending
    for(i=0;i<no_req;i++)
    {
        finish[i]=0;
        
    }
    
    while(pending>0)
    {
        min=9999;//assign maximum value to min
        
        for(i=0;i<no_req;i++)
        {
            diff=abs(head-dis_req[i]);
            if(finish[i]==0 && diff<min)
            {
                min=diff;
                index=i;
            }
        }
        finish[index]=1;
        distance+=abs(head-dis_req[index]);
        head=dis_req[index];
        pending--;
        printf("%d => ",head);
    }
    printf("end");
    printf("\n total distance travelled = %d",distance);
    /*
     
     enter total no of tracks 200

     enter total no of disk request 7

      Enter disc requests 3

     enter head position50
     43 => 24 => 16 => 82 => 140 => 170 => 190 => end
      total distance travelled = 208%
     */
}
void scan()
{
    input();
    int index,dir;
    int i;
    distance=0;
    head=head1;
    printf("\n enter direction :- 1-right and 0-left");
    scanf("%d",&dir);
    sort();
    printf("sorted disc are \n");
    for(i=0;i<no_req;i++)
    {
        printf("%d \n",dis_req[i]);
    }
    
    
    //find location of current head in disc request sequence
    i=0;
    while(head>=dis_req[i])
    {
        index=i;
        i++;
    }
    printf("\n index = %d",index);
    printf("\n %d =>",head);
    
    if(dir==1) //right
    {
        //sort();
        for(i=index+1;i<no_req;i++)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
        distance+=abs(head-(track-1));
        printf("%d => ",track-1);
        head=track-1;
        
        for(i=index;i>=0;i--)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
    }
    else //left
    {
        //sort();
        for(i=index;i>=0;i--)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
        distance+=abs(head-0);
        printf("%d => ",0);
        head=0;
        
        for(i=index+1;i<no_req;i++)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
    }
    printf("end");
    printf("\n total distance travelled = %d",distance);
    
    /*
     enter total no of tracks 200

     enter total no of disk request 7

      Enter disc requests 82 170 43 140 24 16 190

     enter head position50

     Enter direction : 1

     sorted array : 16 24 43 82 140 170 190
     index = 2
     50 =>82 =>140 =>170 =>190 =>199 =>43 =>24 =>16 =>end
     Total distance = 332%
     
     
     enter total no of tracks 200

     enter total no of disk request 7

      Enter disc requests 82 170 43 140 24 16 190

     enter head position50

     Enter direction : 0

     sorted array : 16 24 43 82 140 170 190
     index = 2
     50 =>43 =>24 =>16 =>0 =>82 =>140 =>170 =>190 =>end
     Total distance = 240%
     */
}
void c_look()
{
    input();
    int index,dir;
    distance=0;
    head=head1;
    
    
    printf("\n enter direction :- 1-right and 0-left");
    scanf("%d",&dir);
    
    sort();
    int i;
    
    for(i=0;i<no_req;i++)
    {
        printf("%d \n",dis_req[i]);
    }
    
    i=0;
    
    
    while(head>=dis_req[i])
    {
        index=i;
        i++;
    }
    
    printf("\n index = %d",index);
    printf("\n %d =>",head);
    
    if(dir==1)
    {
        for(i=index+1;i<no_req;i++)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
        
        for(i=0;i<=index;i++)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
    }
    else
    {
        for(i=index;i>=0;i--)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
        
        for(i=no_req-1;i>index;i--)
        {
            printf("%d =>",dis_req[i]);
            distance+=abs(head-dis_req[i]);
            head=dis_req[i];
        }
    }
    printf("end");
    printf("\n total distance travelled = %d",distance);
    /*
     enter total no of tracks 200

     enter total no of disk request 7

      Enter disc requests 82 170 43 140 24 16 190

     enter head position50

      enter direction :- 1-right and 0-left1
     
      index = 2
      50 =>82 =>140 =>170 =>190 =>16 =>24 =>43 =>end
      total distance travelled = 341%
     
     
     enter total no of tracks 200

     enter total no of disk request 7

      Enter disc requests 82 170 43 140 24 16 190

     enter head position50

      enter direction :- 1-right and 0-left0

      index = 2
      50 =>43 =>24 =>16 =>190 =>170 =>140 =>82 =>end
      total distance travelled = 316%
     */
}
int main()
{
    printf("\nenter choice");
    printf("\nenter 1-sstf and 2-scan and 3-c-look");
    scanf("%d",&choice);
    if(choice==1)
    {
        sstf();
    }
    else if(choice==2)
    {
        scan();
    }
    else
    {
        c_look();
    }

}

