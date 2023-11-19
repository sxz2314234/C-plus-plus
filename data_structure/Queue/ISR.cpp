// Image Source Recognition
#include<iostream>
#include"queue.cpp"

struct position
{
    /* data */
    int row;
    int col;
};

const int size=7;
int pixel[size+2][size+2]={{0,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0},{0,0,0,1,1,0,0,0,0},
{0,0,0,0,0,1,0,0,0},{0,0,0,0,1,1,0,0,0},{0,0,1,0,0,1,0,1,0},{0,1,1,1,0,0,0,1,0},
{0,1,1,1,0,0,1,1,0}};
arrayQueue<position> Queue;

void labelComponents();
void show_Pixel();

int main()
{
    labelComponents();
    show_Pixel();
}

void labelComponents()
{
    for(int i=0;i<size+2;i++)
    {
        pixel[0][i]=pixel[size+1][0]=0;
        pixel[i][0]=pixel[i][size+1]=0;
    }
    position offset[4];
    offset[0].row=0;offset[0].col=1;   //right
    offset[1].row=1;offset[1].col=0;   //down
    offset[2].row=0;offset[2].col=-1;  //left
    offset[3].row=-1;offset[3].col=0;  //up

    int id=1;
    position here,nbr;
    for(int r=1;r<size+1;++r)
    for(int c=1;c<size+1;++c)
    {
        if(pixel[r][c]==1)
        {
            here.col=c;
            here.row=r;

            pixel[r][c]=++id;
            while(true)
            {
                for(int i=0;i<4;++i)
            {
                nbr.row=here.row+offset[i].row;
                nbr.col=here.col+offset[i].col;

                if(pixel[nbr.row][nbr.col]==1)
                {
                    pixel[nbr.row][nbr.col]=id;
                    Queue.push(nbr);
                }
            }
            if(Queue.empty())break;
            Queue.pop(here);
            }            
        }
    }
}

void show_Pixel()
{
    for(int i=1;i<size+1;++i)
    {
        for(int j=1;j<size+1;++j)
        std::cout<<pixel[i][j]<<" ";
        std::cout<<std::endl;
    }
    
}