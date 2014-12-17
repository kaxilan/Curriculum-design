#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include "lin.c"
#define MAXSIZE 100

using namespace std;

typedef struct {
        char Name[30];
        char Dec[50];
}PortName;

typedef struct EdgeNode{
        int adjvex;  //邻接点域，储存该定点对应下标；
        int weight;  //权重
        struct EdgeNode * next;  //指向下一个节点
}EdgeNode;

typedef struct VertexNode  {
        int data;  //顶点信息
        EdgeNode * first;
}VertexNode;

typedef struct {
        VertexNode Gport[MAXSIZE];
        int NumVertexes,NumEdges;
}Graph;

int flag1 = 0;

class Navigation{
        PortName port[MAXSIZE];
        Graph g;

        public:
        int StartSigh(){
                int i;
                flag1 = 0;
                cout<<"\n\nWelcome Using This Software!\n\n\n";
                cout<<"1.游客登陆\n";
                cout<<"2.管理员登陆\n";
                cout<<"3.退出\n";
                cin>>i;
                return i;     
        }

        int VisitorSigh() {
                system("clear");
                int i;               
                cout<<"1.查看全部景点\n";
                cout<<"2.查找景点\n";
                cout<<"3.查找路线\n";
                cout<<"4.景点的全部路线\n";
                cout<<"5.返回上级\n";
                cin>>i;
                return i;
        }

        int TestPasswd()  {
                fstream fout;
                char a[8],b[8];
                cout<<"请输入密码\n";
                system("stty -echo");
                cin>>b;
                system("stty echo");
                fout.open("passwd.txt",ios::in|ios::binary);
                fout>>a;
                if(string(a)==string(b))  {
                        return 1;
                }
                else
                return 0;
        }

        int AdminSigh() {
                int i,flag,j;
                if(flag1 == 0)   { 
                        for( j = 0 ; j < 3 ; j++ )  {
                                flag = TestPasswd();
                                if(flag == 0 )  {
                                        cout<<"密码错误!\n";
                                }
                                else  {
                                        flag1 = 1;
                                        break;
                                }
                                if( i == 3 )
                                return -1;
                        }        
                }
                system("clear");
                cout<<"1.增加路线\n";
                cout<<"2.增加景点\n";
                cout<<"3.删除路线\n";
                cout<<"4.删除景点\n";
                cout<<"5.更改路线长度\n";
                cout<<"6.更改景点信息\n";
                cout<<"7.查看全部景点\n";
                cout<<"8.修改密码\n";
                cout<<"9.返回上级\n";
                cin>>i;
                return i;

        }
void ChangePasswd(){
        fstream fin;
        char a[8] ;
        char b[8] ;
        cout<<"请输入更改密码:"<<endl;
        system("stty -echo");
        cin>>a;
        system("stty echo");
        cout<<"请确认密码:"<<endl;
        system("stty -echo");
        cin>>b;
        system("stty echo");
        cout<<"修改成功"<<endl;
        if( string(a) == string(b))  {
                fin.open("passwd.txt",ios::out|ios::binary);
                fin<<a;
                fin.close();

        }
}

        void PrintNO()  {
                int i = 1;
                for(;i <= g.NumVertexes ; i++)  {
                        cout<<i<<"  "<<port[i].Name <<endl;
                }
        }

        void InitGraph()  {
                int i;
                for( i = 1 ; i <= MAXSIZE ; i++ )  {
                        g.Gport[i].first = NULL;
                }
        }

        void KeepFile() {
                int i;
                fstream FileIn;
                EdgeNode * e;
                FileIn.open("MAP.txt",ios::out|ios::binary);
                FileIn<<g.NumVertexes<<" "<<g.NumEdges<<"\n";
                for( i = 1 ; i <= g.NumVertexes ; i++ )  {
                        FileIn<<port[i].Name<<" "<<port[i].Dec<<"\n";
                }
                FileIn.close();
                FileIn.open("EdgeInfo.txt",ios::out|ios::binary);
                for( i = 1 ; i <= g.NumVertexes ; i++ )  {
                        e = g.Gport[i].first;
                        while( e != NULL )  {
                                if( i < e->adjvex )
                                FileIn<<i<<" "<<e->adjvex<<" "<<e->weight<<"\n";
                                e = e->next;
                        }
                }
                FileIn.close();
        }

        void CreatGraph()  {
                int i,j,k,m,n,d;
                EdgeNode *e , *f;
                cout<<"请输入顶点数跟边数:\n";
                cin>>g.NumVertexes>>g.NumEdges;
                //        cout<<g.NumVertexes<<g.NumEdges;
                for( i = 1 ; i <= g.NumVertexes ; i++ )  {
                        cout<<"请输入顶点"<<i<<":\n";
                        cin>>port[i].Name;
                        cout<<"请输入详细信息:\n";
                        cin>>port[i].Dec;
                        g.Gport[i].data = i;
                        g.Gport[i].first = NULL;
                }
                PrintNO();
                //建立边表
                for( k = 1 ; k <= g.NumEdges ; k++ )  {
                        cout<<"请输入有关系的景点序号:\n";
                        cin>>m>>n;
                        cout<<"请输入距离?\n";
                        cin>>d;
                        e = (EdgeNode *)malloc(sizeof(EdgeNode));
                        if( e == NULL )  {
                                cout<<"e内存已满!\n";
                                return;
                        }
                        e->adjvex = n;
                        e->weight = d;
                        e->next = g.Gport[m].first;
                        g.Gport[m].first = e;

                        f = (EdgeNode *)malloc(sizeof(EdgeNode));
                        if( f == NULL )  {
                                cout<<"f内存已满!\n";
                                return;
                        }
                        f->adjvex = m;
                        f->weight = d;
                        f->next = g.Gport[n].first;
                        g.Gport[n].first = f;
                }
                KeepFile();
        }

        void GetdataFormfile()  {
                fstream fin;
                int m = 0 , n = 0, d = 0;
                fin.open("MAP.txt",ios::in|ios::binary);
                EdgeNode * e , * f;
                fin>>g.NumVertexes>>g.NumEdges;
                for( int i = 1 ; i <= g.NumVertexes ; i++ )  {
                        fin>>port[i].Name>>port[i].Dec;
                }
                fin.close();
                fin.open("EdgeInfo.txt",ios::in|ios::binary);
                while(!fin.eof())  {
                        fin>>m>>n>>d;
                        if( m == 0 && n == 0 && d == 0  )
                        break;
                        e = (EdgeNode *)malloc(sizeof(EdgeNode));
                        e->adjvex = n;
                        e->weight = d;
                        g.Gport[m].data = m;
                        e->next = g.Gport[m].first;
                        g.Gport[m].first = e;

                        f = (EdgeNode *)malloc(sizeof(EdgeNode));
                        f->adjvex = m;
                        f->weight = d;
                        g.Gport[n].data = n;
                        f->next = g.Gport[n].first;
                        g.Gport[n].first = f;
                        m = n = d = 0;
                }

                fin.close();
        }

        void PrintAll()  {
                int i = 1;
                while (g.Gport[i].first != NULL && i <= g.NumVertexes) { 
                        cout<<port[i].Name<<":   ";
                        EdgeNode * e = NULL;
                        e = g.Gport[i].first;
                        while( e != NULL )  {
                                cout<<e->adjvex<<"   ";
                                e = e->next;
                        }
                        i++;
                        cout<<endl;
                }
                cout<<endl;
        }

        void SearchPort()
        {
                cout<<"请输入要查找的景点名称:\n";
                char str[30];
                cin>>str;
                for( int i = 1 ; i <= g.NumVertexes ; i++ )  {
                        if(string(str) == string(port[i].Name))  {
                                cout<<":\n";
                                cout<<port[i].Dec<<endl;
                                return;
                        }
                }
                cout<<"没有找到!\n";
        }

        void AddEdge()  {
                cout<<"\n\n";
                PrintNO();
                cout<<"请输入有关系的景点序号:\n";
                int m,n,k;
                cin>>m>>n;
                cout<<"请输入距离:\n";
                cin>>k;
                EdgeNode * e , * f;
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                if ( e == NULL )  {
                        cout<<"内存已满!\n";
                        return;
                }
                e->adjvex = m;
                e->weight = k;
                e->next = g.Gport[n].first;
                g.Gport[n].first = e;

                f = (EdgeNode *) malloc (sizeof(EdgeNode));
                if( f == NULL )  {
                        cout<<"内存已满!\n";
                        return;
                }
                f->adjvex = n;
                f->weight = k;
                f->next = g.Gport[m].first;
                g.Gport[m].first = f;

                KeepFile();
        }

        void AddVertex()  {
                int i,j,k;
                k = g.NumVertexes + 1;
                cout<<"请输入要添加的景点名称:\n";
                cin>>port[k].Name;
                cout<<"请输入添加的景点信息:\n";
                cin>>port[k].Dec;
                g.NumVertexes++;
                g.Gport[k].data = k;
                cout<<"要添加路径吗?(y/n)\n";
        }

        void DeleteEdge()  {
                PrintAll();
                EdgeNode *e,*f;
                cout<<"要删除哪一段的路径?\n";
                int m,n;
                cin>>m>>n;
                e = g.Gport[m].first;
                if(e->adjvex == n)  {
                        g.Gport[m].first = e->next;
                        free(e);
                }
                else  {
                        while( e->next->adjvex != n )  {
                                e = e->next;
                        }
                        f = e->next;
                        e->next = f->next;
                        free(f);
                }

                f = g.Gport[n].first;
                if(f->adjvex == m)  {
                        g.Gport[n].first = f;
                        free(e);
                }
                else  {
                        while( f->next->adjvex != m )  {
                                f = f->next;
                        }
                        e = f->next;
                        f->next = e->next;
                        free(e);
                }
                KeepFile();
        }

        void DeleteVertex()  {
                PrintAll();
                cout<<"要删除哪一个景点?\n";
                int i , j , k ;
                int m;
                cin>>m;
                EdgeNode * e, * f;
                e = g.Gport[m].first;
                g.Gport[m].first = NULL;
                if(e->next == NULL) {
                        free(e);
                }
                else  {
                        f = e->next;
                        while( f != NULL )  {
                                free(e);
                                e = f;
                                f = f->next;
                        }
                }
                for( i = m ; i < g.NumVertexes ; i++ ) {
                        g.Gport[i].first = g.Gport[i+1].first;      
                }

                for ( i = m ; i <= g.NumVertexes ; i++ )  {
                        strcpy(port[i].Name,port[i+1].Name);
                        strcpy(port[i].Dec,port[i+1].Dec);
                }
                g.NumVertexes--;

                for( i = 1; i <= g.NumVertexes ;i++ )  {
                        e = g.Gport[i].first;
                        if( e->adjvex == m )  {
                                g.Gport[i].first = e->next;
                                free(e);
                        }
                        else  {
                                while ( e->next != NULL )  {
                                        if( e->next->adjvex == m )  {
                                                f = e->next;
                                                e->next = f->next;
                                                free(f);
                                        }
                                        e = e->next;
                                }
                        }
                }
                
                for( i = 1 ; i <= g.NumVertexes ; i++ )  {
                        e = g.Gport[i].first;
                        while( e != NULL )  {
                                if( e->adjvex > m ) {
                                        e->adjvex--;
                                }
                                e = e->next;
                        }
                }
        }

        void ChangeWeight()  {
                PrintAll();
                cout<<"你要修改哪条路的长度?\n";
                int m,n;
                cin>>m>>n;
                EdgeNode * e;
                e = g.Gport[m].first;
                while( e->adjvex != n ) {
                        e = e->next;
                }
                cout<<"修改为:";
                cin>>e->weight;
                cout<<endl;
                cout<<"\n修改成功!\n";
                KeepFile();
        }

        void ChangeInfo()  {
                PrintNO();
                cout<<"要修改哪个景点的信息?\n";
                int i;
                cin>>i;
                cout<<"修改为:";
                cin>>port[i].Dec;
                cout<<"\n修改成功\n";
                KeepFile();
        }

        void FindRoute()  {

        }

        void AllRoute()  {

        }
        };


int main() {
        system("clear");
        system("figlet  W e l c o m e !");
        //    sleep(2);
        system("clear");
        cout<<"\n\n\n";
        Navigation a;
        a.InitGraph();
        int flag , i = 0, j = 0 ;
        a.GetdataFormfile();
        //        a.CreatGraph();
        a.PrintAll();
        School_Map();
        while( 1 )  {
                flag = a.StartSigh();
                i = 0 ; j = 0;
                switch(flag)  {
                        case 1:i = a.VisitorSigh();break;
                        case 2:j = a.AdminSigh();break;
                        case 3:system("clear");system("figlet  b y e . b y e !");return 0;break;
                }
                if( i != 0 )  {
                        while(1)  {
                                switch(i)  {
                                        case 1:a.PrintNO();getchar();getchar();i = a.VisitorSigh();break;
                                        case 2:a.SearchPort();getchar();getchar();i = a.VisitorSigh();break;
                                        case 3:getchar();getchar();i = a.VisitorSigh();break;
                                        case 4:getchar();getchar();i = a.VisitorSigh();break;
                                        case 5:; break;
                                }
                                if( i == 5 )  {
                                        break;
                                }
                        }
                }
                if( j != 0 ) {
                        while(1) {
                                switch(j)  {
                                        case 1:a.AddEdge(); j = a.AdminSigh();break;  //增加路线
                                        case 2:a.AddVertex(); j = a.AdminSigh();break;  //增加景点
                                        case 3:a.DeleteEdge();j = a.AdminSigh();break;  //删除路线
                                        case 4:a.DeleteVertex(); j = a.AdminSigh();break;  //删除景点
                                        case 5:a.ChangeWeight(); j = a.AdminSigh();break;  //更改长度
                                        case 6:a.ChangeInfo();j = a.AdminSigh();break;  //更改景点信息
                                        case 7:a.PrintAll();getchar();getchar();j = a.AdminSigh();break;  //查看全部景点
                                        case 8:a.ChangePasswd();getchar();getchar();j = a.AdminSigh();break;
                                        case 9:;break;
                                }
                                if( j == 9 )  {
                                        break;
                                }
                        }
                }
        }
system("clear");system("figlet  b y e . b y e !");
return 0;
}
