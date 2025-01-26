#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


using namespace std;

int vid=0;

class vote{
public:
    int id;
    char name[20];
    int age;
    char gender;
    int voted;   
    
    
    
}v,v1; 

void pack();
void del();
void edit();
void display();
void search();
void election();
fstream fp;
FILE *fn,*ft;
int l;
char name[20];


int main()
{
    
    
    
    cout<<"                     -------------WELCOME TO ELECTION VOTING FILE SYSTEM---------------\n";  
    
    while(1){     
        int choice;
        cout<<"\t\t\n\n\tEnter your choice\n\n\t\t\t 1. To ADD a record\n\t\t\t 2. To DELETE a Record\n\t\t\t 3. To EDIT a record\n\t\t\t 4. To display ALL the Voters' details\n\t\t\t 5. To SEARCH the details of a voter\n\t\t\t 6. Run the election\n";
        cin>>choice;
        switch(choice)
        {
            case 1:
                
                pack();
                break;
            case 2:
                del();
                break;
            case 3:
                edit();
                break;
                
            case 4:
                display();
                break;
            case 5: search();
            break;
            case 6:
                
                election();
                break;
            case 7:
                exit(0);
                break;
                
            default:
                cout<<"Invalid choice\n";
                exit(0);
                
        }   
    }
    return 0;
}

void pack(){
    fn=fopen("new.txt","a");
    
    int r,t;
    char g[1];
    
    v1.id=++vid;
    cout<<"Criteria: 1. Above 18 years of age and Moving to Bangalore\n 2. Above 18 years of age and resident of Bommanahalli, Bangalore";
    cout<<"\nEnter name\n";
    cin>>v1.name;
    cout<<"Enter age as of May 2018\n";
    cin>>v1.age;
    if(v1.age<18)
    {
        cout<<"Ineligible";
        return;
    }
    cout<<"Gender: \n M. Male\n F. Female\n O. Other\n";
    cin>>v1.gender;
    cout<<"Location: \n 1. Bommanahalli \n 2. Other\n";
    
    cin>>t;
    if(t==1)
    {
        cout<<"Aadhaar card submitted?\n 1. Yes\n 2. No\n";
        cin>>r;
        
        if(r==1){
            cout<<"Can Proceed\n";
            cout<<"\n Your name has been added to the voters list, Bommanahalli\n";
        }
        else{
            cout<<"Should submit the Aadhaar card., cannot proceed.\n";
            return;
        }
    }
    else
    {
        cout<<"\n Only for Bommanahalli Location";
        exit(0);
    }
    v1.voted=0;
    fn=fopen("new.txt","a");
    fwrite(&v1,sizeof(v1),1,fn);
    fclose(fn);
    
}
void del(){
    char name1[20];
    int f=0;
    cout<<"\n Criteria: 1. If Expired. \n OR \n 2. Moved to another city/state\n\n";
    cout<<"Enter the name of the voter to be deleted: \n";
    cin>>name1;
    fn=fopen("new.txt","r");
    ft=fopen("temp.txt","w");
    
    while(fread(&v1,sizeof(v1),1,fn)==1)
    {
        if(strcmp(name1,v1.name)==0){
            
            f=1;
            continue;
        }
        else
            
            fwrite(&v1,sizeof(v1),1,ft);
    }
    if(f==0)
    {
        cout<<"\n The name "<<name1<<" was not found\n";
        
        remove("new.txt");
        rename("temp.txt","new.txt");
        
        fclose(fn);
        fclose(ft);
    }
    if(f==1){
        remove("new.txt");
        rename("temp.txt","new.txt");
        cout<<"\n Successfully deleted the details of "<<name1;
        
        
        fclose(fn);
        fclose(ft);
    }
    
    
    
    
    
    
    
    
    
}

void edit(){
    int w=0;
    fn=fopen("new.txt","r");
    ft=fopen("temp.txt","w");
    
    cout<<"Edit the details\n";
    cout<<"Enter the name of the voter whose details you want to edit\n";
    char name2[20];
    int age;
    cin>>name2;
    
    while(fread(&v1,sizeof(v1),1,fn)==1)
    {
        if(strcmp(name2,v1.name)==0)
        {
            w=1;
            continue;
        }
        else
            
            fwrite(&v1,sizeof(v1),1,ft);
    }
    if(w==1){
        cout<<"Enter the new NAME: ";
        cin>>v1.name;
        cout<<"Enter new age";
        cin>>v1.age;
        if(v1.age<18)
        {
            cout<<"Ineligible";
            return;
        }      
        cout<<"\nEnter the Gender :";
        cin>>v1.gender;
        
        fwrite(&v1,sizeof(v1),1,ft);
        fclose(ft);
        fclose(fn);
        
        remove("new.txt");
        rename("temp.txt","new.txt");
        
        cout<<"\n Successfully edited the details of "<<name2;
    }
    
    if(w==0){
        cout<<"The name "<<name2<<" was not found\n";
        remove("new.txt");
        rename("temp.txt","new.txt");
        
        fclose(fn);
        fclose(ft);
    }
}

void display()
{
    cout<<"DISPLAY ALL VOTERS' DETAILS\n";
    
    
    fn=fopen("new.txt","r");
    int found=0;
    
    while(fread(&v1,sizeof(v1),1,fn)==1)
    {
        cout<<"\nName :" <<v1.name <<"\n Age: " <<v1.age<< "\nGender: " <<v1.gender<< "\nLocation: Bommanahalli \n";
        found++;
    }
    fclose(fn);
    
}

void search()
{
    
    int found=0;
    fn=fopen("new.txt","r");
    char name3[20];
    cout<<"\n Enter the name whose details you want to SEARCH\n";
    cin>>name3;
    l=strlen(name3);
    fn=fopen("new.txt","r");
    while(fread(&v1,sizeof(v1),1,fn)==1)
    {
        for(int i=0;i<l;i++)
            name[i]=v1.name[i];
        name[l]='\0';
        
        if(strcmp(name,name3)==0)
        {
            cout<<"\n Name: "<<v1.name<< "\n Age: "<<v1.age<< "\n Gender :"<< v1.gender<<"\n Location: Bommanahalli \n";
            found++;
            if(found%4==0)
            {
                cout<<"\n Press any key\n";
            }
        }
    }
    if(found==0)
        cout<<"\n No match found\n";
    else
        cout<<"\n Match found!";
    fclose(fn);
    
    
    
}

void election()
{
    int pass;
    cout<<"------ ELECTION DAY-------\n";
    cout<<"Enter Password\n";
    cin>>pass;
    int r1=0,r2=0,r3=0;
    int found=0;
    char name4[20];
    if(pass==1234)
    {
        while(1)
        {
            int u;
            cout<<"\n----------Welcome to the election of May 2018---------------\n ---------------Your votes are valuable------------\n";
            cout<<"Press 1. To continue\n Press 2. To exit\n";
            cin>>u;
            if(u==2){
                exit(0);
            }
            else if(u==1)
            {
                
                cout<<"\nEnter the name of the voter:  \n:";
                cin>>name4;
                
                
                int n;
                int age;
                char name[20],gender;
                
                
                l=strlen(name4);
                fn=fopen("new.txt","r");
                while(fread(&v1,sizeof(v1),1,fn)==1)
                {
                    
                    
                    if((strcmp(v1.name,name4)==0)&&(v1.voted==0))
                    {
                        v1.voted=1;
                        strcpy(name,v1.name);
                        gender=v1.gender;
                        age=v1.age;
                        cout<<"\n Cast your vote here \n";
                        cout<<"\n The Candidates are:  1. A 2.B 3.C \n Press 1 for A\n Press 2 for B \n Press 3 for C\n\n";
                        cin>>n;
                        switch(n)
                        {
                            case 1:
                                r1=r1+1;
                                break;
                            case 2:
                                r2=r2+1;
                                break;
                            case 3:
                                r3=r3+1;
                                break;
                            default:
                                cout<<"Invalid choice\n";
                                return;
                                
                        }
                        
                        found++;
                        
                        fclose(fn);
                        fn=fopen("new.txt","r");
                        ft=fopen("temp.txt","a");
                        while(fread(&v1,sizeof(v1),1,fn)==1)
                        {    if(strcmp(name4,v1.name)!=0)
                        {
                            fwrite(&v1,sizeof(v1),1,ft);
                        }
                        }
                        
                        fclose(fn);
                        fclose(ft);
                        
                        //remove("new.txt");
                        
                        //rename("new.txt","voted.txt");
                        rename("temp.txt","new1.txt");
                        
                        
                        break;
                       
                    }if(v1.voted==1){
                        cout<<"\n Cannot vote again\n";
                        exit(0); 
                    }
                    
                }
                if(found==0){
                    cout<<"\n No match found\n\n";
                    cout<<"\n NOT present in the voting list\n\n";
                }
                
            }
            int x;
            cout<<"Check the results \nPress 1 to check results currently\n Press 2 to continue\n";
            cin>>x;
            if(x==1){
                if(found!=0){
                    cout<<"A votes:" <<r1<< "\n B votes:"<<r2 << "\n C votes:"<<r3;
                    if((r1>r2)&&(r1>r3))
                    {
                        cout<<"\n A has the majority\n";
                    }
                    else if((r2>r1)&&(r2>r3)){
                        cout<<"\n B has majority\n";
                        
                    }
                    else if((r3>r1)&&(r3>r2)){
                        cout<<"\n C has majority\n";
                        
                    }
                    else{
                        cout<<"\n Pending results ";
                    }
                    
                }
            }
            fclose(fn);
        }
    }
    else
    {
        cout<<"\n Password incorrect, Cannot have access\n";
    }
    
    
}

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

n