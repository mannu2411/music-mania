#include <iostream>
#include <string>
#include <dirent.h>
#include <windows.h>
#include <dos.h>
#include <cstdio>
#include <time.h>
#include <conio.h>
using namespace std;

class trie_node
{
public:
    char value;
    trie_node* chars[28];
    bool EndofWord;

    trie_node();
};

trie_node::trie_node()
{
    value=false;
    for (int i=0; i<28; i++)
    {
        chars[i]=NULL;
    }
    EndofWord=false;
}

int totSng=0;

class trie
{
    trie_node* root;
public:
    trie()
    {
        root=new trie_node();
    }
    void insert(string);
    int search(string,string*);
    void suggestions(trie_node*,string,int*,string*);
    //trie_node* find(string);
};

typedef struct tree_node
{
    char name[30];
    struct tree_node* left;
    struct tree_node* right;
}Tnode;

typedef Tnode* tree;
tree root=NULL;

struct playList
{
    char name[30];
    int cnt_song;
    tree song[200];
    struct playList* nxt;
};

typedef struct playList* list;
list head=NULL;

void mainmenu();

void trie::insert(string str)
{
    int l=str.length();
    //cout << l << endl;
    trie_node* temp=root;
    //cout << "ok" << endl;
    for (int i=0; i<l; i++)
    {
        if(str[i]<91 && str[i]>64)
        {
            str[i]+=32;
        }
        for (int j=0; j<28; j++)
        {
            //cout << "ok" << endl;
            if (!temp->chars[j])
            {
                temp->chars[j]=new trie_node();
                temp=temp->chars[j];
                temp->value=str[i];
                break;
            }
            if (temp->chars[j]->value==str[i])
            {
                //cout <<str[i];
                temp=temp->chars[j];
                break;
            }
        }

    }
    //cout << "ok" << endl;
    temp->EndofWord=true;
    //cout << temp->value;
}

void trie::suggestions(trie_node* temp,string sugg,int* num,string arr[])
{
    if (temp->EndofWord)
    {
        *num=*num+1;
        cout << *num << '\t';
        cout << sugg << endl;
        arr[*num-1]=sugg;
    }
    for (int i=0; i<28; i++)
    {
        if (!temp->chars[i])
            break;
        //;
        //cout << sugg << endl;
        suggestions(temp->chars[i],sugg+temp->chars[i]->value,num,arr);
    }
}

int trie::search(string input,string arr[])
{
    int l=input.length();
    trie_node* temp=root;
    bool f=true;
    //cout << arr[1];
    //cout<< "ok";
    for (int i=0; i<l; i++)
    {
        for (int j=0; j<28; j++)
        {
            if (!temp->chars[j])
            {
                cout << "NO Results Found" << endl;
                f=false;
                break;
            }
            if (temp->chars[j]->value==input[i])
            {
                temp=temp->chars[j];
                break;
            }
        }
        if (!f)
            break;
    }

    int n=0;
    int *num=&n;
    //cout << "ok";
    if (f)
    {
        //cout << "ok";
        *num=0;
        suggestions(temp,input,num,arr);
    }
    return *num;
}


trie lib;

void read_from_directory()
{
    DIR *dir;
    struct dirent *ent;
    FILE *libFile;
    libFile=fopen("All Songs.txt","w");
    int  counter=0;

    //lib=fopen("music.txt","w");

    if((dir = opendir ("C:\\Users\\Lappy\\Desktop\\mania\\SONG\\")) != NULL)
    {
  // print all the files and directories within directory

        while ((ent = readdir (dir)) != NULL)
        {
            if(counter>=2)
            {
                string song=ent->d_name;
                song=song.substr(0,song.length()-4);
                fprintf(libFile,"%s\n",song.c_str());
                lib.insert(song);
                totSng++;
                //cout << song << endl;
            }
            counter++; //upar do dots aa rahe the
        }
        closedir (dir);
        fclose(libFile);
    }
    //fclose(lib);
}
//char str[5];
/*void gotoxy(int x,int y)
{
    static HANDLE h=NULL;
    if(!h)
    {
        h=GetStdHandle(STD_OUTPUT_HANDLE);
        COORD c={x,y};
        SetConsoleCursorPosition(h,c);
    }
}*/

COORD coord = {0, 0};

void gotoxy (int x, int y)
{
        coord.X = x; coord.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void logo()
{
    int i,j;
int c = 1, d = 1;
   for(int i=1;i<26;i++)
{
for(int j=1;j<119;j++)
{
cout<<"*";
}
cout<<endl;
}
system("cls");

gotoxy(2,3);
cout<<"  ***********************************************************************************************************"<<endl;
gotoxy(2,4);
cout<<" @@     @@  @@    @@   @@@@   @@@@@@    @@@@@       @@     @@    @@@@@@     @@@     @@   @@@@@@    @@@@@@ "<<endl;
cout<<"   @@@   @@@  @@    @@  @@        @@     @@           @@@   @@@   @@    @@    @@@@    @@     @@     @@    @@"<<endl;
cout<<"   @@ @ @ @@  @@    @@  @@        @@    @@            @@ @ @ @@   @@@@@@@@    @@ @@   @@     @@     @@@@@@@@"<<endl;
cout<<"   @@  @  @@  @@    @@   @@@@     @@    @@            @@  @  @@   @@@@@@@@    @@  @@  @@     @@     @@@@@@@@"<<endl;
cout<<"   @@     @@  @@    @@      @@    @@    @@            @@     @@   @@    @@    @@   @@ @@     @@     @@    @@"<<endl;
cout<<"   @@     @@  @@    @@      @@    @@     @@           @@     @@   @@    @@    @@    @@@@     @@     @@    @@"<<endl;
cout<<"   @@     @@   @@@@@@    @@@@   @@@@@@    @@@@@       @@     @@   @@    @@    @@     @@@   @@@@@@   @@    @@"<<endl;
gotoxy(4,13);
cout<<" *********************************************************************************************************"<<endl;

for ( c = 1 ; c <= 92767 ; c++ )
       for ( d = 1 ; d <= 3276 ; d++ )
       {}
gotoxy(5,17);

       cout<<"      PRESENTED BY :: "<<endl;
for ( c = 1 ; c <= 32767 ; c++ )
       for ( d = 1 ; d <= 3276 ; d++ )
       {}

cout<<"\n       KIRTI GODANI\n";
for ( c = 1 ; c <= 32767 ; c++ )
       for ( d = 1 ; d <= 3276 ; d++ )
       {}

cout<<"       DEEPSHI SHARMA\n";
for ( c = 1 ; c <= 32767 ; c++ )
       for ( d = 1 ; d <= 3276 ; d++ )
       {}

cout<<"       MANUBHAV JAIN\n";
for ( c = 1 ; c <= 32760 ; c++ )
       for ( d = 1 ; d <= 32760 ; d++ )
       {}

       cout<<endl;
cout<<endl;
cout<<endl;

}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void play()
{
    system("cls");
    cout<<"Enter 0 to stop searching: "<<endl<<"Enter 1 to play next"<<endl;
    char argv[]="C:\\Users\\Lappy\\Desktop\\mania\\SONG";

int result = chdir(argv);

    struct dirent *de;  // Pointer for directory entry
    DIR *dr = opendir(".");

int flag=0;
int d;

    while ((de = readdir(dr)) != NULL)
          {char add[]="C:\\Users\\Lappy\\Desktop\\mania\\SONG\\";
              int flag2=0;
              if(flag>1&&flag2==0)
          {

            cout<<"Playing"<<"  "<<de->d_name<<endl;
              strcat(add,de->d_name);
              PlaySound(TEXT(add),NULL,SND_ASYNC);
              cin>>d;
              if(d==1)
              {
               flag2=1;
              }
               if(d==0)
               {
                PlaySound(NULL, NULL, 0);

                   return;
               }
              }

          else
            {
             flag++;
            }
          }

    closedir(dr);


}
/*class playList
{
public:
    string name;
};*/
string read_password()
{
    FILE* pass=fopen("password.txt","r");
    string password;
    char p[10];
    fgets(p,10,pass);
    for (int i=0; p[i]!='`'; i++)
    {
        password+=p[i];
        //cout << password[i];
    }
    fclose(pass);
    //cout << p;
    //cout << password;
    return password;
}

int t() //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

void sound(string arr)
{

    //string ext=".wav";
    arr=arr + ".wav";
    system("cls");
        cout<<"Enter 0 to stop searching: "<<endl;
    char argv[]="C:\\Users\\Lappy\\Desktop\\mania\\SONG";

int result = chdir(argv);

    struct dirent *de;  // Pointer for directory entry
    DIR *dr = opendir(".");


int d;
//strcat(name,ext);
cout<<arr<<endl;
    while ((de = readdir(dr)) != NULL)
          {int i;
              int flag=0;
              char add[]="C:\\Users\\Lappy\\Desktop\\mania\\SONG\\";
              int flag2=0;
              char j[strlen(de->d_name)];
              for(i = 0;i<strlen(de->d_name); i++){
                        j[i] = tolower(de->d_name[i]);
                                }
                                j[i]='\0';
              //cout<<j<<endl;
              if(arr==j)
          {

            cout<<"Playing"<<"  "<<de->d_name<<endl;
              strcat(add,de->d_name);
              PlaySound(TEXT(add),NULL,SND_ASYNC);
              cout<<"Enter 0 to exit:";
              cin>>d;
               if(d==0)
               {
                PlaySound(NULL, NULL, 0);

                   return;
               }
              }
          }

    closedir(dr);
    return;
}

void playaSong()
{
    cout<<"Enter letter of song"<<endl;
    cout<<"Enter 0 to choose song"<<endl;
    string in;
    string arr[totSng];
    int n=0;
    while (1)
    {
        //
        char c;
        cin>>c;
        //cout << endl;
        if (c!='0')
        {
            system("cls");
            if (c!=8)
            {
                in+=c;
               // cout << in;
                n=lib.search(in,arr);

            }
            else
            {
              //  cout << "bvESBWU";
                in=in.substr(0,in.length()-1);
                n=lib.search(in,arr);
            }
            cout << endl;
            cout << in;
        }
        else
        {
            cout << endl;
            cout <<"Enter your Choice Or Enter 0 to mainmenu:";
            int x;
            cin >> x;
            if (x>n)
            {
                cout << "Enter Valid Choice";
                cin >> x;
            }
            if (x==0)
                mainmenu();
            cout << arr[x-1];
            sound(arr[x-1]);
        }
    }
}

void play_all()
{
    FILE *f=fopen("All Songs.txt","r");
    char str[30];
    while (fgets(str, 30, f))
    {

        str[strlen(str)-1]='\0';
        cout<<str<<endl;
        play();
        mainmenu();
//        play(str);
        /*gotoxy(20,11);
        printf("Enter 'N' for Next Song");
        gotoxy(20,13);
        printf("Enter 'S' to Stop");
        char choice[2];
        //delay(30000);

        unsigned int msec=3000;
        clock_t goal=msec+clock();
        while(goal>clock())
        {
            fflush(stdin);
            if(fgets(choice,1,stdin))
            {
                printf("%s",choice);
                switch(choice[0])
                {
                    case 'n': continue;
                              break;
                    case 'N': continue;
                              break;
                    case 's': mainmenu();
                              break;
                    case 'S': mainmenu();
                              break;
                }
            }
        }*/
    }
    fclose(f);

}


void view()
{
    system("cls");
    //char song_name[30];
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    int c=3;
    /*lib=fopen("music.txt","r");
    while(fgets(song_name,30,lib))
    {
        gotoxy(20,c+=2);
        //fgets(song_name,30,p);
        printf("\xDB\xB2 %s\n",song_name);
    }
    fclose(lib);*/
    c+=2;
    gotoxy(20,c);
    printf("------------------------------------------");
    c+=3;

    gotoxy(20,c);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Play a Song\n");
    c+=2;
    gotoxy(20,c);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Play all Songs\n");
    c+=2;
    gotoxy(20,c);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Main Menu\n");
    c+=2;
    gotoxy(20,c);
    printf("------------------------------------------");
    gotoxy(20,++c);
    t();
    c+=3;
    gotoxy(20,c);
    c+=2;
    printf("Enter your choice:");
    int choice;
    scanf(" %d",&choice);
    switch(choice)
    {
        case 1: system("cls");
                playaSong();
                mainmenu();
                break;
        case 2: system("cls");
                play();
                mainmenu();
                break;
        case 3: mainmenu();
                break;
        default:
        {
            c+=2;
        gotoxy(10,c);
        printf("\aWrong Entry!!Please re-enter correct option");
        char s;
        scanf("%c",s);
        if(s)
        view();
        }
    }
}

tree find(tree temp , char str[30])
{
    if (temp == NULL)
    {
        return temp;
    }
    else if(strcmp(temp->name,str) > 1)
    {
        if(temp->left==NULL)
        {
            return temp->left;
        }
        else
        {
            return find(temp->left,str);
        }
    }
    else
    {
        if(temp->right==NULL)
        {
            return temp->right;
        }
        else
        {
            return find(temp->right,str);
        }
    }
}

void addTreeNode(char str[30])
{
    tree t;
    t = (tree) malloc(sizeof(Tnode));
    t->left = NULL;
    t->right = NULL;
    strcpy(t->name,str);

    if (root == NULL)
    {
        root = t;
    }
    else
    {
        tree temp=root;
        while (temp!=NULL)
        {
            if(strcmp(temp->name,str) > 0)
            {
                if(temp->left==NULL)
                {
                    temp->left=t;
                    break;
                }
                else
                {
                    temp=temp->left;
                }
            }
            else
            {
                if(temp->right==NULL)
                {
                    temp->right=t;
                    break;
                }
                else
                {
                    temp=temp->right;
                }
            }
        }
    }
}

void create_BST()
{
    FILE *f=fopen("All Songs.txt","r");
    char str[30];
    while (fgets(str, 30, f))
    {
        str[strlen(str)-1]='\0';
          // printf("%s2",str);

        addTreeNode(str);
        //tot_cnt++;
        //printf("%s",str);
    }
    fclose(f);
}

tree searchLib(char name[],tree temp)//searching in lib
{
    //printf("%d",strcmp(root->name,name));
    //printf("%s2",temp->name);
    if (temp == NULL)//no song found
    {
        /*if(temp==root)
        {
            printf("wfefv");
        }*/
        //printf("yhan h");
        //printf("%s",temp->name);
        //printf("no such song found");
        return NULL;
    }
    if(strcmp(temp->name,name)>0)
    {
        return searchLib(name,temp->left);
    }
    else if(strcmp(temp->name,name)<0)
    {
        return searchLib(name,temp->right);
    }
    else//song found
    {
        //printf("%s",temp->name);
        return temp;
    }
}

void add_list(char str[30])
{
    list temp= (list) malloc(sizeof(struct playList));
    temp->nxt=NULL;
    strcpy(temp->name,str);
    //printf("%s",temp->name);
    temp->cnt_song=0;

    //printf("%s",temp->name);
    FILE* p_List=fopen(str, "r");
    int i;
    for (i=0; fgets(str,30,p_List); i++)
    {
        str[strlen(str)-1]='\0';
        //printf("%s",str);
        //printf("%s",root->name);
        //printf("%d",strcmp(root->name,str));
        tree t=searchLib(str, root);
        //printf("%s",t->name);
        if (t != NULL)
        {
            temp->song[i]=t;
            (temp->cnt_song)++;
        }
    }

    if ( head == NULL )
    {
        head = temp;
    }
    else
    {
        temp->nxt=head;
        head=temp;
    }
    fclose(p_List);
}

void init_lists()
{
    FILE* pl=fopen("playlist.txt","r");
    char plist[30];
    while( fgets(plist, 30, pl))
    {
        plist[strlen(plist)-1]='\0';
        //printf("%s",plist);
        add_list(plist);
    }
    fclose(pl);
}

void print_ll()
{
    list temp=head;
    //printf("yhan h");
    //printf("%s",temp->name);
    while (temp!=NULL)
    {
        printf("%s:-\n",temp->name);
        int i;
        for (i=0; i<temp->cnt_song; i++)
        {
            printf("%s\n",temp->song[i]->name);

        }
        temp=temp->nxt;
    }
}

int chk_List(char str[])
{
    list temp=head;
    while (temp!=NULL)
    {
        if(strcmp(str,temp->name)==0)
            return 1;
        temp=temp->nxt;
    }
    return 0;
}
string songsearch()
{
    cout<<"Enter letter of song"<<endl;
    cout<<"Enter 0 to choose song"<<endl;
    string in;
    string arr[100];
    int n=0;
    while (1)
    {
        //
        char c;
        cin>>c;
        //cout << endl;
        if (c!='0')
        {
            system("cls");
            if (c!=8)
            {
                in+=c;
               // cout << in;
                n=lib.search(in,arr);

            }
            else
            {
              //  cout << "bvESBWU";
                in=in.substr(0,in.length()-1);
                n=lib.search(in,arr);
            }
            cout << endl;
            cout << in;
        }
        else
        {
            cout << endl;
            cout <<"Enter your Choice Or Enter 0 to mainmenu:";
            int x;
            cin >> x;
            return arr[x-1];
           // if (x>n)
            {
             //   cout << "Enter Valid Choice";
               // cin >> x;
            }

           // arr[x-1];
        }
    }
}

void add_new_list(char str[])
{   system("cls");
    list temp= (list) malloc(sizeof(struct playList));
    temp->nxt=NULL;
    strcpy(temp->name,str);
    //printf("%s",temp->name);
    temp->cnt_song=0;
    //printf("%s",temp->name);
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Add Song");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Main Menu");
    gotoxy(20,9);
    printf("------------------------------------------");
    gotoxy(20,11);
    t();
    gotoxy(20,13);
    printf("Enter Choice: ");

    char ch;
    scanf(" %c",&ch);
    int i;
    int c=15;
    FILE *p_List;
    for (i=0; ch=='1'; i++)
    {
        gotoxy(20,c=c+2);
        printf("->Enter Song name-> ");
        char sng[30];
        gets(sng);
        fgets(sng,30,stdin);
        sng[strlen(sng)-1]='\0';
        p_List=fopen(str, "a");
        //cout << "ok";
        //printf("%s",str);
        //printf("%s",root->name);
        //printf("%d",strcmp(root->name,str));
        tree ts=searchLib(sng, root);

        //printf("%s",t->name);
        //printf("%s",t->name);
        if (ts != NULL)
        {
            fprintf(p_List,"%s\n",sng);
            system("cls");
            gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Add More Song");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Main Menu");
    gotoxy(20,9);
    printf("Recently Added:%s ",sng);
    gotoxy(20,11);
    printf("------------------------------------------");
    gotoxy(20,13);
    t();
    gotoxy(20,15);
    printf("Enter Choice: ");
    scanf(" %c",&ch);
            temp->song[i]=ts;
            (temp->cnt_song)++;
        }
        else{
            system("cls");
            gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Add More Song");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Main Menu");
    gotoxy(20,9);
    printf("SONG NOT FOUND IN LIBRARY");
    gotoxy(20,11);
    printf("------------------------------------------");
    gotoxy(20,13);
    t();
    gotoxy(20,15);
    printf("Enter Choice: ");
    scanf(" %c",&ch);
        }


    }
    if ( head == NULL )
    {
        head = temp;
    }
    else
    {
        temp->nxt=head;
        head=temp;
    }
    mainmenu();
    fclose(p_List);
}

void create_list()
{

    system("cls");
   gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("New List Name:");
    gotoxy(20,7);
    printf("------------------------------------------");
    gotoxy(20,8);
    //t();
    gotoxy(20,11);
    printf("Enter:");
    char new_list[30];
    cin>>new_list;
    strcat(new_list,".txt");
    FILE *fp;
    fp=fopen(new_list,"w");
    int d=1;
    while(d!=0)
    {
        string st;
        st=songsearch();
        //cout<<st<<endl;
        //st[st.length()]='/0';
        for(int i=0;i<st.length();i++)
        fprintf(fp,"%c",st[i]);
        fprintf(fp,"\n",NULL);


        cout<<"Enter 1 to add more else 0 to exit";
        cin>>d;
            }

            fclose(fp);

mainmenu();
}

void play_shuffle()
{
  char new_list[30];
    gets(new_list);
    strcat(new_list,".txt");
    FILE *fp;
    int i;
    char sd[50][50];
    fp=fopen(new_list,"r");
    while(fscanf(fp,"%s",sd[i])!=EOF)
    {
    //fscanf(fp,"%s",sd);
    i++;
   // cout<<"here";
}
int k=0;int j=0;
while(k<i-1)
{
    j=rand()%(i-1);
    sound(sd[j]);
    k++;
}

}

void play_fulllist(char str[])
{

    system("cls");
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Play in Order\n");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Shuffle\n");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Mainmenu\n");
    gotoxy(20,11);
    printf("------------------------------------------");
    gotoxy(20,12);
    t();
    gotoxy(20,14);
    printf("Enter Choice");
    int choice;
    scanf(" %d",&choice);
    //list temp=head;
    switch(choice)
    {
        case 1:
                char new_list[30];
                cout<<"enter list name";
                gets(new_list);
                strcat(new_list,".txt");
                FILE *fp;
                char sd[30];
                fp=fopen(new_list,"r");
                while(fscanf(fp,"%s",sd)!=EOF)
                {
                sound(sd);
                }
                cout<<"Press any button to go to mainmenu";
                int d;
                cin>>d;
                mainmenu();
                break;
        /*case 2: play_name(str);
                break;*/
        case 2: play_shuffle();
        break;
        case 3: mainmenu();
        break;
        default:
        {
            int c=16;
            c+=2;
            gotoxy(20,c);
            printf("\aWrong Entry!!Please re-enter correct option");
            char b;
            scanf("%c",&b);
            if(b)
            play_all();
        }
    }

}

void open_list(char str[])
{
    system("cls");
    //printf("%s",str);
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 %s",str);
    FILE *p_List=fopen(str,"r");
    char sng[30];
    int c=5;
    while (fgets(sng,30,p_List))
    {
        //gotoxy(0,0);
        //printf("%s",sng);
        gotoxy(20,c+=2);
        printf("\xDB\xB2 %s",sng);
    }

    gotoxy(20,c+=2);
    printf("------------------------------------------");
    c+=3;

    gotoxy(20,c);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Play a Song\n");
    c+=2;
    gotoxy(20,c);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Play all Songs\n");
    c+=2;
    gotoxy(20,c);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Main Menu\n");
    c+=2;
    gotoxy(20,c);
    printf("------------------------------------------");
    c+=1;
    gotoxy(20,c);
    t();
    c+=3;
    gotoxy(20,c);
    c+=2;
    printf("Enter your choice:");
    int choice;
    int d;
    scanf(" %d",&choice);
    switch(choice)
    {
        case 1: printf("Enter name of Song");
                char song[30];
                gets(song);
                sound(song);
                cout<<"Press any button to go to mainmenu";
                cin>>d;
                mainmenu();
                break;
        case 2:
               // play_fulllist(str);
                cout<<"Press any button to go to mainmenu";
                cin>>d;
                mainmenu();
                break;
        case 3: mainmenu();
                break;
        default:
        {
            int c=16;
            c+=2;
            gotoxy(20,c);
            printf("\aWrong Entry!!Please re-enter correct option");
            char m;
            scanf("%c",&m);
            if(m)
            play();
        }
    }
}

void open_playlist()
{
    system("cls");
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    list temp=head;
    int c=5;
    while (temp!=NULL)
    {
        gotoxy(20,c);
        printf("%s",temp->name);
        c+=2;
        temp=temp->nxt;
    }
    gotoxy(20,c);
    printf("------------------------------------------");
    c+=1;
    gotoxy(20,c+=2);
    printf("1. Open a List");
    gotoxy(20,c+=2);
    printf("2. Add New List");
    gotoxy(20,c+=2);
    printf("3. Mainmenu");
    gotoxy(20,c+=2);
    printf("------------------------------------------");
    c+=1;
    gotoxy(20,c);
    t();
    int choice;
    scanf(" %d",&choice);
    switch (choice)
    {
        case 1: printf("Enter Playlist Name");
                char str[30];
                gets(str);
                fgets(str,30,stdin);
                str[strlen(str)-1]='\0';
                strcat(str,".txt");
                //printf("%s",str);
                open_list(str);
                cout<<"Press any button to go to mainmenu";
                int d;
                cin>>d;
                mainmenu();
                break;
        case 2: create_list();
                cout<<"Press any button to go to mainmenu";
                cin>>d;
                mainmenu();
                break;
        case 3: mainmenu();
                break;
        default:
        {
            gotoxy(10,23);
            printf("\aWrong Entry!!Please re-enter correct option");
            char a;
            scanf("%c",&a);
            if(a)
            open_playlist();
        }
    }
}

void mainmenu()
{
    system("cls");
    int i,choice;
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MUSIC-MANIA");
    printf(" \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. View all Songs");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Play all Songs");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Create Playlist");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 4. Open Playlist");
    gotoxy(20,13);
    //printf("\xDB\xDB\xDB\xDB\xB2 5. Change Password");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 5. Exit Application");
   // gotoxy(20,17);
   // printf("\xDB\xDB\xDB\xDB\xB2 7. Close Application");
    gotoxy(20,15);
    printf("------------------------------------------");
    gotoxy(20,16);
    t();
    gotoxy(20,19);
    printf("Enter your choice:");
    scanf(" %d",&choice);
    switch(choice)
    {
        case 1: view();
                break;
        case 2: play();
                mainmenu();
                break;
        case 3: create_list();
                mainmenu();
            break;
        case 4: open_playlist();
                mainmenu();
                break;
        /*case 5: change_password();
                break;
        case 6: {
        system("cls");
        gotoxy(16,3);
        printf("Thanks for using the Program..");
        gotoxy(10,7);
        printf("Exiting in 5 second...........>");
        //flushall();
        delay(5000);
        exit(0);
        }
        default:
        {
        gotoxy(10,23);
        printf("\aWrong Entry!!Please re-enter correct option");
        if(getch())
        mainmenu();
        }*/


    }
}

/*void Password(void) //for password option
{
    string password=read_password();
    //cout << password;
    char d[19]="Password Protected";
    char ch;
    string pass;
    int i=0,j;
   //textbackground(WHITE);
   //textcolor(RED);
    gotoxy(10,10);
    for(j=0;j<20;j++)
    {
        delay(50);
        printf("*");
    }
    for(j=0;j<18;j++)
    {
        delay(50);
        printf("%c",d[j]);
    }
    for(j=0;j<20;j++)
    {
        delay(50);
        printf("*");
    }
   //gotoxy(10,10);
    gotoxy(15,12);
    printf("Enter Password:");

    while(ch!=13)
    {
        scanf("%c",&ch);
        if(ch!=13 && ch!=8)
        {
            putch('*');
            pass+= ch;
            i++;
            //cout << pass;
        }
    }
    //pass[i] = '\0';
    if(pass==password)
    {
        gotoxy(15,14);
    //textcolor(BLINK);
        printf("Password match");
        gotoxy(17,16);
        printf("Press any key to countinue.....");
        getch();
        create_BST();

    init_lists();
        mainmenu();
    }
    else
    {
        gotoxy(15,16);
        printf("\aWarning!! Incorrect Password");
        getch();
        Password();
    }
}
*/
int main()
{
   logo();
    read_from_directory();
//    Password();
    mainmenu();
    //string in;

    return 0;
}
