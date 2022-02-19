#include <iostream>
#include <windows.h>

#define block_size 4
#define kind_of_shape 7

#define print_arr(x) x ? cout << "o" : cout <<" "

using namespace std;

int block_shape[kind_of_shape][4][2] = 
{
    {{block_size/2,block_size/2-2}, {block_size/2,block_size/2-1},  {block_size/2,block_size/2},        {block_size/2,block_size/2+1}},     // I 자 블럭,   kind = 0;
    {{block_size/2,block_size/2},   {block_size/2,block_size/2+1},  {block_size/2+1,block_size/2},      {block_size/2+1,block_size/2+1}},   // ㅁ 자 블럭,  kind = 1;
    {{block_size/2,block_size/2-1}, {block_size/2,block_size/2},    {block_size/2,block_size/2+1},      {block_size/2+1,block_size/2}},     // ㅗ 자 블럭 , kind = 2;
    {{block_size/2,block_size/2},   {block_size/2,block_size/2+1},  {block_size/2+1,block_size/2+1},    {block_size/2-1,block_size/2}},     // s 자  블럭.  kind = 3;
    {{block_size/2,block_size/2},   {block_size/2,block_size/2+1},  {block_size/2-1,block_size/2+1},    {block_size/2+1,block_size/2}},     //s자 블럭2,    kind = 4;
    {{block_size/2,block_size/2},   {block_size/2+1,block_size/2},  {block_size/2-1,block_size/2},      {block_size/2+1,block_size/2-1}},   //L자 블럭,     kind = 5;
    {{block_size/2,block_size/2},   {block_size/2+1,block_size/2},  {block_size/2-1,block_size/2},      {block_size/2+1,block_size/2+1}},   //L자 블럭2,    Kind = 6;
};

class Map;
class Blocks
{ 
    friend Map;

    private:
        int x;
        int y;
    protected:
        int block_compo[block_size][block_size] = {0};

    public:
        void show_shape();
        void rotate();

        int get_x()     {return x;}
        int get_y()     {return y;}

        void set_x(int x)       {this->x = x;}
        void set_y(int y)       {this->y = y;}

        void control(int direction);
        
};

class Block : public Blocks // 대문자
{
    private:
        int kind;
    public:
        Block(int kind , int x = 5, int y= 5) :kind(kind)
        {
            set_x(x);
            set_y(y);
            for(int i=0; i<4; i++)
                block_compo[block_shape[kind][i][0]][block_shape[kind][i][1] ] = 1;
        }
        
        void set_kind(int kind) {this->kind = kind;}
        int get_kind()  {return kind;}
};

class Map
{
    private:
        int N;
        int** map;

    public:
        Map(int N):N(N)
        {
            map = new int*[N];

            for(int i=0;i<N ; i++)
                map[i] = new int[N];

            for(int i=0;i<N ; i++)
                for(int j=0; j<N ; j++)
                    map[i][j] = 0;
        }

        virtual ~Map()
        {
            for(int i =0; i<N ; i++)
                delete[] map[i];
            delete[] map;
        }
        void show_map();
        void blocks_on_map(Blocks& block , int x , int y){/**/} 

        int get_map_compo(int x, int y)   
        {
            if(0<=x&&x<N&&0<=y&&y<N) return map[x][y] ;
            else return -1;                                 
        }

        void set_map_compo(int x, int y, int u)
        {
            if (u==-1) return;
            map[x][y] = u;
        }
        bool validation(Block* block );         //Block이 지정한 위치에 존재할 수 있는지 검사
        void set_block_at_map(Block* block);   //Block을 지정한 위치에 놓음
};

bool Map::validation(Block* block)
{

    
}


class  Block_List
{
    int block_numbers;
    Block** block_list;
    int current;

    public:
        Block_List(int block_numbers) : block_numbers(block_numbers)
        {
            block_list = new Block*[block_numbers];
            current = 0;
        }

        void add_Block(Block* blocks)
        {
            block_list[current] = blocks;
            current++;
        }


        int current_blocks() { return current;}

        ~Block_List()
        {
            for(int i =0 ; i< current ; i++)
                delete block_list[i]; 
            delete[] block_list;
        }

        Blocks& operator[](const int index) {return *block_list[index];}
};

int main()
{
    Block_List Blist(kind_of_shape);


    //system("cls");
    
    for(int i = 0 ; i<kind_of_shape ; i++)
    {
        cout << i+1 << endl;
        Blist.add_Block(new Block(i));
        //Blist[i].show_shape();
        
    }

    Blist[3].show_shape();
    cout<< "rotate"<<endl;
    Blist[3].rotate();
    cout<< "show" << endl;
    Blist[3].show_shape();

    Map table(10);
    table.show_map();

}

void Blocks::rotate()
{
    int temp;
    for(int i=0; i<=block_size/2 ; i++)
    {
        for(int j=i ; j<block_size-i-1 ; j++)
        {
            temp = block_compo[block_size-j-1][i];
            block_compo[block_size-j-1][i]                = block_compo[block_size-i-1][block_size-j-1];
            block_compo[block_size-i-1][block_size-j-1]   = block_compo[j][block_size-i-1];
            block_compo[j][block_size-i-1]                = block_compo[i][j];
            block_compo[i][j]                             = temp;
        }        
    }
    Map m(10);
}


void Blocks::control(int direction= 0)
{
    switch (direction)
    {
        case 1:             // down
            y+=5;
            break;
        case 2:             // right
            x++;
            break;
        case 3:             // left
            x--;
            break;         
        case 4:             // rotate
            rotate();
            break;         

        default:            // nothing input
            y++;
            break;
    }
}

void Blocks::show_shape()
{
    //system("cls");
    for(int i = 0 ; i < block_size ; i++)
    {
        for(int j=0 ; j<block_size  ; j++)
            print_arr(block_compo[i][j]);
        cout << endl;
    }
}

void Map::show_map()
{
    system("cls");
    cout<<" ---------- "<<endl;
    for(int i=0; i <N ; i++)
    {
        cout<<"|";
        for(int j=0;j<N;j++)
            print_arr(map[i][j]);
        cout<<"|"<<endl;
    }
    cout<<" ---------- "<<endl;
}
