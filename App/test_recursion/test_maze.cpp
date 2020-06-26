#include <iostream>
#include <stack>

using namespace std;

#define MAZE_SIZE 10

typedef struct __PosType
{
    int row;
    int col;
}PosType;

#define VALID_POS    -1
#define INVALID_POS  0

int maze[MAZE_SIZE][MAZE_SIZE] = 
{
     0,  0,  0,  0,  0,  0,  0,  0,  0, 0,
     0, -1, -1,  0, -1, -1, -1,  0, -1, 0,
     0, -1,  0,  0, -1, -1, -1,  0, -1, 0,
     0, -1, -1, -1, -1,  0,  0, -1, -1, 0,
     0, -1,  0,  0,  0, -1, -1, -1, -1, 0,
     0, -1, -1, -1,  0,  0, -1, -1, -1, 0,
     0, -1,  0, -1, -1, -1,  0, -1, -1, 0,
     0, -1,  0,  0,  0, -1,  0,  0, -1, 0,
     0, 0,  -1, -1, -1, -1, -1, -1, -1, 0,
     0, 0,   0,  0,  0,  0,  0,  0,  0, 0,
};

stack<PosType> his_pos;
PosType start_pos = {1, 1};
PosType end_pos = {8, 8};

int search_line_col(int *pdirect, PosType *pNowPos)
{ 
    int     index      = 0;
    PosType temp_pos;    
    PosType pre_pos;
    int     first_find = 0;
    int     i          = 0;
    int     ret        = -1;

    for(index = pNowPos->col + 1; index < MAZE_SIZE; index++)
    {
        if(pNowPos->row == end_pos.row && pNowPos->col == end_pos.col)
        {
            cout << "reach end success!"  << endl;
            ret = 0;
            break;
        }
        
        if(VALID_POS == maze[pNowPos->row][index])
        {
            if(0 == first_find)
            {
                his_pos.push(*pNowPos);
            }
            
            pNowPos->col = index;
            his_pos.push(*pNowPos);

            first_find = 1;
        }
        else 
        {
            temp_pos = his_pos.top();
            pNowPos->row = temp_pos.row;
            pNowPos->col = temp_pos.col;
            his_pos.pop();
                    
            break;
        }

        i++;
    }

    *pdirect = (i > 0)?0:1;

    return ret;
}

int search_line_row(int *pdirect, PosType *pNowPos)
{ 
    int      index      = 0;
    PosType  temp_pos;
    PosType  pre_pos;
    int      first_find = 0;
    int      i          = 0;
    int      ret        = -1;

    for(index = pNowPos->row+ 1; index < MAZE_SIZE; index++)
    {
        if(pNowPos->row == end_pos.row && pNowPos->col == end_pos.col)
        {
            cout << "reach end success!"  << endl;
            ret = 0;
            break;
        }
        
        if(VALID_POS == maze[index][pNowPos->col])
        {
            if(0 == first_find)
            {
                his_pos.push(*pNowPos);
            }
                    
            pNowPos->row = index;
            his_pos.push(*pNowPos);

            first_find = 1;
        }
        else 
        {
            temp_pos = his_pos.top();
            pNowPos->row = temp_pos.row;
            pNowPos->col = temp_pos.col;
            his_pos.pop();            
            
            break;
        }

        i++;
    }

    *pdirect = (i > 0)?1:0;

    return ret;
}

int search_line(int *pdirect, PosType *pNowPos)
{
    int ret = -1;

    if(1 == *pdirect)
    {
        ret = search_line_col(pdirect, pNowPos);
    }
    else if(0 == *pdirect)
    {
        ret = search_line_row(pdirect, pNowPos);
    }

    return ret;
}

int print_line()
{
    PosType        temp_pos;    
    stack<PosType> rer_pos;
    int            i              = 0;
    int            res_stack_size = 0;

    while(!his_pos.empty())
    {
        temp_pos = his_pos.top();
        his_pos.pop();
        rer_pos.push(temp_pos);
    }

    res_stack_size = rer_pos.size();
    for(i = 0; i < res_stack_size; i++)
    {
        temp_pos = rer_pos.top();
        rer_pos.pop();
        cout << "(" << temp_pos.row << ", " << temp_pos.col << ")"; 
        if(i != res_stack_size - 1)
        {
            cout << "--->";
        }
    }

    cout << endl;

    return 0;
}

int main()
{
    PosType now_pos = {0};
    
    int row = 0;
    int col = 0;
    int i   = 0;
    int j   = 0;

    int direct = 0;


    row = start_pos.row;
    col = start_pos.col;

    for(i = row; i < MAZE_SIZE; i++)
    {
        if(VALID_POS == maze[i][col])
        {
            now_pos.row = i;
            now_pos.col = col;
            his_pos.push(now_pos);
        }
        else 
        {   
            if(i != row)
            {
                now_pos = his_pos.top();
                his_pos.pop();
            }
            direct = 1;
            break;
        }
    }

    while(!his_pos.empty())
    {
        if(0 == search_line(&direct, &now_pos))
        {
            print_line();
            break;
        }
    }
    
    return 0;
}

