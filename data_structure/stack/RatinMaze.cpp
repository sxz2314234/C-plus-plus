#include <iostream>
#include "Stack.cpp"

using std::cin;
using std::cout;
using std::endl;

int Maze[12][12] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1}, {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1}, {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1}, {1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
class coordinate
{
public:
    int x;
    int y;
    coordinate(int X = 1, int Y = 1) : x(X), y(Y){};
    coordinate operator+(const coordinate &) const;
};

arrayStack<coordinate> stack(30);
arrayStack<coordinate> path(30);

void show_Maze();
bool find_path();
bool find_path2();
void display_path();
bool if_blocked(const coordinate &, const coordinate &);

int main()
{
    show_Maze();
    find_path2();
    display_path();
}

void show_Maze()
{
    for (int i = 0; i < 12; ++i)
    {
        for (int j = 0; j < 12; ++j)
            cout << Maze[i][j] << " ";
        cout << endl;
    }
}

bool find_path()
{
    coordinate start(1, 1);
    coordinate up(-1, 0);
    coordinate down(1, 0);
    coordinate left(0, -1);
    coordinate right(0, 1);
    coordinate path = start;
    stack.push(start);
    Maze[path.x][path.y] = 1;
    while (!(path.x == 10 && path.y == 10))
    {
        if (!if_blocked(path, up))
        {
            path = path + up;
            stack.push(path);
            Maze[path.x][path.y] = 1;
            continue;
        }
        else if (!if_blocked(path, down))
        {
            path = path + down;
            stack.push(path);
            Maze[path.x][path.y] = 1;
            continue;
        }
        else if (!if_blocked(path, left))
        {
            path = path + left;
            stack.push(path);
            Maze[path.x][path.y] = 1;
            continue;
        }
        else if (!if_blocked(path, right))
        {
            path = path + right;
            stack.push(path);
            Maze[path.x][path.y] = 1;
            continue;
        }
        else
        {
            if (stack.empty())
                return false;
            else
            {
                stack.pop();
                path = stack.top();
            }
        }
    }
    return true;
}

bool if_blocked(const coordinate &path, const coordinate &director)
{
    coordinate result = path + director;
    return Maze[result.x][result.y] == 1;
}

coordinate coordinate::operator+(const coordinate &co) const
{
    coordinate temp;
    temp.x = x + co.x;
    temp.y = y + co.y;
    return temp;
}

void display_path()
{
    coordinate coor;
    while (!path.empty())
    {
        coor = path.top();
        path.pop();
        cout << "(" << coor.x << ", " << coor.y << ")" << endl;
    }
}

bool find_path2()
{
    coordinate offset[3];
    offset[0].x=0; offset[0].y=1;   //right
    offset[1].x=1; offset[1].y=0;   //down
    offset[2].x=0; offset[2].y=-1;  //left
    offset[3].x=-1; offset[3].y=0;  //up

    coordinate here;
    here.x=1;
    here.y=1;
    Maze[1][1]=1;
    int option=0;
    int lastoption=3;

    while(!(here.x==10&&here.y==10))
    {
        int r,c;
        while(option<=lastoption)
        {
            r=here.x+offset[option].x;
            c=here.y+offset[option].y;
            if(Maze[r][c]==0)break;
            option++;
        }
        if(option<=lastoption)
        {
            path.push(here);
            here.x=r;
            here.y=c;
            Maze[r][c]=1;
            option=0;
        }
        else
        {
            if(path.empty())
            return false;
            else
            {
                coordinate next=path.top();
                path.pop();
                if(next.x==here.x)
                option=2+next.y-here.y;
                else option=3+next.x-here.x;
                here=next;
            }
        }
    }
    return true;
}