#include <iostream>
#include <fstream>
#include <string>
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
        int NumVertexs; //顶点数
        int NumEdges; //边数
}Graph;

class Navigation{
        PortName PortInfo[MAXSIZE];
        Graph AllRoutes;

        public:
        int StartSigh(){
                int i;
                cout<<"Welcome Using This Software!\n\n\n";
                cout<<"1.游客登陆\n";
                cout<<"2.管理员登陆\n";
                cin>>i;
                return i;     
        }

        int VisitorSigh() {
                int i;
                cout<<"1.查看全部景点\n";
                cout<<"2.查看景点\n";
                cout<<"3.查找路线\n";
                cout<<"4.景点的全部路线\n";
                cin>>i;
                return i;
        }
        
        int TestPasswd()  {
                fstream fout;
                char a[8],b[8];
                cout<<"请输入密码\n";
                cin>>b;
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
                for( j = 0 ; j < 3 ; j++ )  {
                        flag = TestPasswd();
                        if(flag == 0 )  {
                                cout<<"密码错误!\n";
                        }
                        else  {
                                cout<<"1.增加路线景点\n";
                                cout<<"2.删除路线景点\n";
                                cout<<"3.更改路线景点\n";
                                cout<<"4.查看全部景点\n";
                                cout<<"5.修改密码\n";
                                cin>>i;
                                return i;
                        }
                }
                return -1;
        }
        void ChangePasswd(){
                fstream fin;
                char a[8] ;
                cout<<"请输入你要更改的密码:\n";
                cin>>a;
                fin.open("passwd.txt",ios::out|ios::binary);
                fin<<a;
                fin.close();
        }
        
        void CreatGraph()  {
                
        }

        void PrintAll()  {

        }

};

int main() {
        Navigation a;
        int flag , i , j;
        flag = a.StartSigh();
        switch(flag)  {
                case 1:i = a.VisitorSigh();break;
                case 2:j = a.AdminSigh();cout<<j;break;
        }
        switch(i)  {
                case 1:;break;
                case 2:;break;
                case 3:;break;
                case 4:;break;
        }
        switch(j)  {
                case 1:;break;
                case 2:;break;
                case 3:;break;
                case 4:;break;
                case 5:a.ChangePasswd();break;
        }
        return 0;
}
