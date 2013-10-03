#include <iostream>
#include <fstream>

#include "Queue.h"

using namespace std;

enum {N, S, W, E};

struct DragonPosition
{
    int x,y,step;
    char derection;
};


void gorynych()
{
    char **arr;
    bool ***brr;

    int height, width;
    DragonPosition dragon;
    ifstream fin ("input.txt");
    fin >> width >> height >> dragon.y >> dragon.x >> dragon.derection;

    dragon.x--;
    dragon.y--;

    arr = new char*[height];
    brr = new bool**[height];

    for(int i = 0; i < width; ++i)
    {
        arr[i] = new char[width];
        brr[i] = new bool*[width];

        for(int n = 0; n < width; ++n)
        {
            fin >> arr[i][n];
            brr[i][n] = new bool[4];
            for(int k = 0; k < 4; ++k)
                brr[i][n][k] = true;
        }
    }
    fin.close();

    dragon.step = 0;
    Queue<DragonPosition> queue;


    queue.push_back(dragon);
    {
        do
        {
            dragon = queue.on_front();
            queue.pop_front();
            if(arr[dragon.x][dragon.y] != '@')
            {
                switch(dragon.derection)
                {
                case 'N':
                {
                    if(brr[dragon.x][dragon.y][N])
                    {
                        brr[dragon.x][dragon.y][N] = false;
                        ++dragon.step;
                        if(dragon.y - 1 >= 0)
                        {
                            if(dragon.x - 1 >= 0 && arr[dragon.x-1][dragon.y-1] != '#' && (arr[dragon.x][dragon.y-1] != '#' || arr[dragon.x-1][dragon.y] != '#'))
                            {
                                --dragon.x;
                                --dragon.y;
                                queue.push_back(dragon);
                                ++dragon.x;
                                ++dragon.y;
                            }
                            if(arr[dragon.x][dragon.y-1] != '#')
                            {
                                --dragon.y;
                                dragon.derection = 'W';
                                queue.push_back(dragon);
                                ++dragon.y;
                            }
                        }
                        dragon.derection = 'W';
                        queue.push_back(dragon);
                    }
                }
                break;
                case 'S':
                {
                    if(brr[dragon.x][dragon.y][S])
                    {
                        brr[dragon.x][dragon.y][S] = false;
                        ++dragon.step;
                        if(dragon.y + 1 < width)
                        {
                            if(dragon.x + 1 < height && arr[dragon.x+1][dragon.y+1] != '#' && (arr[dragon.x][dragon.y+1] != '#' || arr[dragon.x+1][dragon.y] != '#'))
                            {
                                ++dragon.x;
                                ++dragon.y;
                                queue.push_back(dragon);
                                --dragon.x;
                                --dragon.y;
                            }
                            if(arr[dragon.x][dragon.y+1] != '#')
                            {
                                ++dragon.y;
                                dragon.derection = 'E';
                                queue.push_back(dragon);
                                --dragon.y;
                            }
                        }
                        dragon.derection = 'E';
                        queue.push_back(dragon);
                    }
                }
                break;
                case 'W':
                {
                    if(brr[dragon.x][dragon.y][W])
                    {
                        brr[dragon.x][dragon.y][W] = false;
                        ++dragon.step;
                        if(dragon.x + 1 < height)
                        {
                            if(dragon.y - 1 >= 0 && arr[dragon.x+1][dragon.y-1] != '#' && (arr[dragon.x][dragon.y-1] != '#' || arr[dragon.x+1][dragon.y] != '#'))
                            {
                                ++dragon.x;
                                --dragon.y;
                                queue.push_back(dragon);
                                --dragon.x;
                                ++dragon.y;
                            }
                            if(arr[dragon.x+1][dragon.y] != '#')
                            {
                                ++dragon.x;
                                dragon.derection = 'S';
                                queue.push_back(dragon);
                                --dragon.x;
                            }
                        }
                        dragon.derection = 'S';
                        queue.push_back(dragon);
                    }
                }
                break;
                case 'E':
                {
                    if(brr[dragon.x][dragon.y][E])
                    {
                        brr[dragon.x][dragon.y][E] = false;
                        ++dragon.step;
                        if(dragon.x - 1 >= 0)
                        {
                            if(dragon.y + 1 < width && arr[dragon.x-1][dragon.y+1] != '#' && (arr[dragon.x][dragon.y+1] != '#' || arr[dragon.x-1][dragon.y] != '#'))
                            {
                                --dragon.x;
                                ++dragon.y;
                                queue.push_back(dragon);
                                ++dragon.x;
                                --dragon.y;
                            }
                            if(arr[dragon.x-1][dragon.y] != '#')
                            {
                                --dragon.x;
                                dragon.derection = 'N';
                                queue.push_back(dragon);
                                ++dragon.x;
                            }
                        }
                        dragon.derection = 'N';
                        queue.push_back(dragon);
                    }
                }
                break;
                }
            }
        }
        while(!queue.is_empty() && arr[dragon.x][dragon.y] != '@');
    }

    cout << "Our dragon must make " << dragon.step <<" step";

    ofstream fout("output.txt");
    fout << dragon.step;

    fout.close();

    for(int i = 0; i < height; ++i)
        delete [] arr[i];
    delete [] arr;
}

int main()
{
    gorynych();
    return 0;
}
