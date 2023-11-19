/*
 * @Author: shi-xingzhi 3218635958@qq.com
 * @Date: 2023-08-11 17:15:17
 * @LastEditors: shi-xingzhi 3218635958@qq.com
 * @LastEditTime: 2023-08-11 19:39:20
 * @FilePath: \C-plus-plus\data_structure\Queue\FindShortestPath.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

/*
Before coding,we should make some premise.
Here,we assume that when we resuse the array grid,there must be a conflict
We don't know number '1' represent where the position of barrier is,
or the distance away from the start.
So,to resolve it,we make all distance grid[i][j] be added 2 to represent the distance.
Then grid[i][j]=1 represents the position blocked.
*/
#include<iostream>
#include"queue.cpp"

struct position
{
    /* data */
    int row;
    int col;
};

position start={3,2};
position end={4,6};
position offset[4];
position* path;
int path_Lenth;
bool find_Path();
void show_Path();

int grid[9][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,1,0,0,0,0,0},{0,0,0,1,1,0,0,0,0},{0,0,0,0,0,1,0,0,0},
{0,0,0,0,1,1,0,0,0},{0,1,0,0,0,1,0,0,0},{0,1,1,1,0,0,0,0,0},{0,1,1,1,0,0,0,0,0}};

int main()
{
    find_Path();
    show_Path();
}

bool find_Path()
{
    if(start.row==end.row&&start.col==end.col)
    {
        path_Lenth=0;
        return true;
    }
    int option=4;
    offset[0].row=0;offset[0].col=1;  //right
    offset[1].row=1;offset[1].col=0;  //down
    offset[2].row=0;offset[2].col=-1; //left
    offset[3].row=-1;offset[3].col=0; //up
    for(int i=0;i<9;i++)
    {
        grid[0][i]=1;
        grid[8][i]=1;
        grid[i][0]=1;
        grid[i][8]=1;
    }

    position here=start;
    grid[here.row][here.col]=2;
    int numOfNbrs=4;

    arrayQueue<position> queue;
    position nbr;
    do
    {
        for(int i=0;i<numOfNbrs;++i)
        {
            nbr.row=here.row+offset[i].row;
            nbr.col=here.col+offset[i].col;

            if(grid[nbr.row][nbr.col]==0)
            {
                grid[nbr.row][nbr.col]=grid[here.row][here.col]+1;
                if(nbr.row==end.row&&nbr.col==end.col)break;
                queue.push(nbr);
            }
        }
            if(nbr.row==end.row&&nbr.col==end.col)break;

            if(queue.empty())return false;

            queue.pop(here);
        
    }while(true);

    path_Lenth=grid[end.row][end.col]-2;
    path=new position[path_Lenth];

    here=end;
    for(int j=path_Lenth-1;j>=0;--j)
    {
        path[j]=here;
        for(int i=0;i<numOfNbrs;++i)
        {
            nbr.row=here.row+offset[i].row;
            nbr.col=here.col+offset[i].col;

            if(grid[nbr.row][nbr.col]==j+2)break;
        }
        here=nbr;
    }
    return true;
}
void show_Path()
{
    for(int i=0;i<path_Lenth;++i)
    std::cout<<"("<<path[i].row<<", "
    <<path[i].col<<")"<<std::endl;
}