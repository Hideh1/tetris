#include <iostream>
#include <windows.h>
#include <random>

#define block_size 4

using namespace std;

void print_arr(int x);

class Block_Base
{ 
    private:
        int x;
        int y;

        int temp_x;
        int temp_y;

    protected:
        int block_compo[block_size][block_size] ={0};
        int uno_block[block_size][block_size]={0};

    public:
        void show_shape();
        void rotate();

        int get_x()     {return x;}
        int get_y()     {return y;}

        void set_x(int x)       {this->x = x;}
        void set_y(int y)       {this->y = y;}

        void control();
        void control(int p);

        void down(){control(0);}

        int compo(int p , int q)    {return block_compo[p][q];}

        void save_compo()
        {
            for(int i = 0; i<4 ; i++)
                for(int j=0; j<4 ; j++)
                    uno_block[i][j]  = block_compo[i][j];

            temp_x = x;
            temp_y = y;
        }

        void load_compo()
        {
            for(int i = 0; i<4 ; i++)
                for(int j=0; j<4 ; j++)
                    block_compo[i][j] = uno_block[i][j];

            x = temp_x;
            y = temp_y;
            
        }
        
};

class Block_0 : public Block_Base //직선
{
    public:Block_0()
    {
        block_compo[0][2]=1;
        block_compo[1][2]=1;
        block_compo[2][2]=1;
        block_compo[3][2]=1;
    }
};

class Block_1: public Block_Base //L
{
    public:Block_1()
    {
                            block_compo[0][2]=1;
                            block_compo[1][2]=1;
        block_compo[2][1]=1;block_compo[2][2]=1;        
    }
};

class Block_2: public Block_Base //L대칭
{
    public:Block_2()
    {
        block_compo[0][1]=1;
        block_compo[1][1]=1;
        block_compo[2][1]=1;block_compo[2][2]=1;
    }
};

class Block_3: public Block_Base //s
{
    public:Block_3()
    {
        
                            block_compo[1][1]=1;block_compo[1][2]=1;
        block_compo[2][0]=1;block_compo[2][1]=1;

    }
};

class Block_4: public Block_Base //s 대칭
{
    public:Block_4()
    {
        block_compo[1][0]=1;block_compo[1][1]=1;
                            block_compo[2][1]=1;block_compo[2][2]=1;                   
    }
};

class Block_5: public Block_Base //ㅏ 
{
    public:Block_5()
    {
        block_compo[0][1]=1;
        block_compo[1][1]=1;block_compo[1][2]=1;
        block_compo[2][1]=1;
    }
};

class Block_6: public Block_Base //ㅏ 
{
    public:Block_6()
    {              
        block_compo[1][1]=1;block_compo[1][2]=1;
        block_compo[2][1]=1;block_compo[2][2]=1;
    }
};

class Map
{
    private:
        int w;
        int h;
        int** map;
        int score = 0;

    public:
        Map(int w=10 , int h=15): w(w) , h(h)
        {
            map = new int*[h];

            for(int i=0;i<h ; i++)
            {
                map[i] = new int[w];
                for(int j=0; j<w ; j++)
                    map[i][j] = 0;
            }
        }

        virtual ~Map()
        {
            for(int i =0; i<h ; i++)
                delete[] map[i];
            delete[] map;
        }
        
        int map_size_w(){return w;}
        int map_size_h(){return h;}

        int get_map_compo(int x, int y)   
        {
            if(0<=x&&x<h&&0<=y&&y<w)  return map[x][y];
            return -1 ;
        }

        void set_map_compo(int x, int y, int u)
        {
            if (u==-1) return;
            map[x][y] = u;
        }

        bool check_line(int l)
        {
            int s = 0;
            for(int j=0;j<w;j++)    s+= map[l][j];
            return (s==w); 
        }

        void remove_line(int l);

        void clear_map()
        {
            for(int p=0;p<h;p++)
                for(int q=0;q<w;q++)
                {
                    if (map[p][q]!=1) map[p][q]=0;
                }
        }


};

class game 
{

    private:
        
        bool game_over = false;
        bool block_on = false;

        
        Map* mp;


    public:
        Block_Base* new_block;
        game()
        {
            mp = new Map();
        }

        ~game()
        {
            delete mp;
        }

        bool block_valid_checker(Block_Base* block );

        void block_setter(Block_Base* block );

        void block_control(Block_Base* block , int p);

        void show_map();

        void create_block();

        void place_block();

        bool exist_block(){return block_on;}

        bool still_alive(){return !(game_over);}



};


int main()
{
    game g;
    while(g.still_alive())
    {
        
        if(g.exist_block() == false) g.create_block();
        
        g.block_setter(g.new_block);

        
        g.show_map();
        g.block_control(g.new_block,1);

        g.block_control(g.new_block,0);

        break;

    }

}


void Block_Base::rotate()
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
    
}


void Block_Base::control()
{
    int direction = 1;
    switch (direction)
    {
        case 1:             // down
            x+=5;
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

void Block_Base::control(int p)
{
    if(p==0)x++;
    else control();
}

void Block_Base::show_shape()
{
    //system("cls");
    for(int i = 0 ; i < block_size ; i++)
    {
        for(int j=0 ; j<block_size  ; j++)
            print_arr(block_compo[i][j]);
        cout << endl;
    }
}

void Map::remove_line(int l)
{
    if (check_line(l))
    {
        for(int i=h-1;i>l ; i--)
        {
            for(int j=0; j<w ; j++)
                map[i][j] = map[i-1][j];
        }
        for(int j=0;j<w;j++)
            map[0][j] = 0;   

        score++;
    }
}

void game::show_map()
{
    int h = mp->map_size_h();
    int w = mp->map_size_w();

    system("cls");

    for(int j=0;j<w+2;j++)cout<<"o";
    cout<<endl;
    
    for(int i=0; i <  h; i++)
    {
        cout<<"|";
        for(int j=0;j<w;j++)
            print_arr(mp->get_map_compo(i,j));
        cout<<"|"<<endl;
    }
    for(int j=0;j<w+2;j++)cout<<"o";
    cout<<endl;
}


void game::create_block()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0,6);

    int px = dis(gen);
    /*
    cout << px << endl;
    cout << px << endl;
    cout << px << endl;
    system("pause");
    */
    switch (px)
    {
        case 0:
            new_block = new Block_0();
            break;
        case 1:
            new_block = new Block_1();
            break;
        case 2:
            new_block = new Block_2();
            break;
        case 3:
            new_block = new Block_3();
            break;
        case 4:
            new_block = new Block_4();
            break;
        case 5:
            new_block = new Block_5();
            break;
        case 6:
            new_block = new Block_6();
            break;
            
        default:
            break;
    }
    new_block->set_x(0);
    new_block->set_y(4);
    block_on = true;
}

void game::place_block()
{
    int x = new_block->get_x();
    int y = new_block->get_y();
    for(int p=0;p<4;p++)
        for(int q=0;q<4;q++)
        {
            int u = new_block->compo(p,q);
            if(u==0) continue;
            mp->set_map_compo(x+p,y+q,u);
        }

    delete new_block;
    block_on = false;   
}


void print_arr(int x)
{
    switch (x)
    {
    case 0:
        cout<<" ";
        break;
  
    case 1:
        cout<<"o";
        break;

    case 2:
        cout<<"o";
        break;

    default:
        break;
    }
    return;
}


void game::block_control(Block_Base* block , int p=1)
{
    int h_b = block->get_x();
    int w_b = block->get_y();

    block->save_compo();
    block->control(p);

    if (!block_valid_checker(block))
        block->load_compo();
    if(p) block_setter(block);
    else place_block();
}



void game::block_setter(Block_Base* block)
{
    int h_b = block->get_x();
    int w_b = block->get_y();

    for(int p =0 ; p<4 ; p++)
        for(int q=0 ; q<4 ; q++)
            mp->set_map_compo(h_b+p,w_b+q, block->compo(p,q)*2); // 이동중인 블럭은 2 로 표시

}

bool game::block_valid_checker(Block_Base* block )
{
    int h_b = block->get_x();
    int w_b = block->get_y();

    for(int p=0;p<4;p++)
        for(int q=0;q<4;q++)
            if (block->compo(p,q) &&(mp->get_map_compo(h_b+p ,w_b+q) != 0 )) return false;
    return true;
}
