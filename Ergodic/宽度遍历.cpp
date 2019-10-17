#include <iostream>
#include <queue>
#include "conio.c"
#include <stdio.h>
#define EnterKey      0x0d
#define UpCursor      38
#define LeftCursor    37
#define RightCursor   39
#define DownCursor    40
#define AltXKey       18
#define EscKey        27
#define SelectAttr    0x20        //选中的属性
#define NoSelectAttr  0x70       //未选中的属性
#define SystemBorder  0x17       //未选中的属性
#define BorderColor   0x30       //未选中的属性
#define MainMenuLine  1          //主菜单显示的开始行
#define MainMenuCount 8          //主菜单项的数目
#define MaxWindowWidth 80        //屏幕宽度


using namespace std;
typedef signed short int ShortInt;

//菜单结构体定义
typedef struct MenuItemStru{
  ShortInt SubMenuItemCount;          //子菜单的数目
  ShortInt SubMenuItemWidth;          //子菜单的宽度
  MenuItemStru * SubMenuItemAddr;     //子菜单数据结构地址
  ShortInt MenuItemStrWidth;          //主菜单项字符串长度
  char *   MenuItemStrAddr;           //主菜单项的字符串地址
  };

typedef struct MenuSelectStru{
 ShortInt MenuIndex,MenuItemTotal;     //选择菜单中的哪项
 MenuItemStru * pMenu;                 //对应主菜单/子菜单的数据结构地址
 PCHAR_INFO AddrOfSaveText;            //备份下拉菜单区域的空间
 bool  PullDownMenu;                   //下拉菜单有否显示
 ShortInt left,top,right,bottom;
};

//char * S_S_Box  ="谀砍渤滥";
char * S_S_Box  ="谀砍 忱馁";
char * T_S_Box  ="履鲁 忱馁";
char * B_S_Box  ="谀砍 忱馁";

//     File子菜单字符串
char * LoadStr    = "Load     F3";
char * PickStr    = "Pick Alt-F3";
char * NewStr     = "New";
char * SaveStr    = "Save     F2";
char * WriteStr   = "Write to";
char * DirStr     = "Diretory";
char * ChangeStr  = "Change Dir";
char * OsStr      = "Os Shell";
char * QuitStr    = "Quit  Alx-X";
//     Run 子菜单字符串
char * RunSubStr  = "Run           Ctrl-F9";
char * ProgStr    = "Program reset Ctrl-F2";
char * GotoStr    = "Go To cursor       F4";
char * TraceStr   = "Trace into         F7";
char * StepStr    = "Step over          F8";
char * UserStr    = "User Screen    Alt-F5";
//    Compile子菜单字符串
char * CompileStr = "Compile to OBJ";
char * MakeStr    = "Make EXE file";
char * LinkStr    = "Link EXE file";
char * BuildStr   = "Build all";
char * PrimaryStr = "Primary C file";
char * GetInfoStr = "Get info";
//    project子菜单字符串
char * ProjectStr = "Project name";
char * BreakStr   = "Break make on";
char * AutoStr    = "Auto dependencies";
char * ClearStr   = "Clear project";
char * RemoveStr  = "Remove messages";
//    Options子菜单字符串
char * CompilerStr = "Compiler";
char * LinkerStr   = "Linker";
char * EnvironStr  = "Environment";
char * DirectStr   = "Directories";
char * ArgumentStr = "Arguments";
//    comiler parameter子菜单字符串
char * ModelStr   = "Model";
char * DefinesStr = "Defines";
char * CodeStr    = "Code generation";
char * OptimStr   = "Optimization";
char * SourceStr  = "Source";
char * ErrorsStr  = "Errors";
char * NamesStr   = "Names";
//    Link子菜单字符串
char * MapStr     = "Map file";
char * InitialStr = "Initialize segments";
char * DefaultStr = "Default library";
char * WarnStr    = "Warn duplicate symbols";
char * StackStr   = "Stack warning";
char * CaseStr    = "Case-sensitive link";
//   Environment子菜单字符串
char * MessageStr ="Message Tracking";
char * KeepStr    ="Keep messages";
char * ConfigStr  ="Config auto save";
char * EditAutoStr="Edit auto save";
char * BackupStr  ="Backup files";
char * TabSizeStr ="Tab Size";
char * ZoomedStr  ="Zoomed windows";
char * ScreenStr  ="Screen size";
//   Directory子菜单字符串
char * IncludeStr ="Include directories";
char * LibraryStr ="Library directories";
char * OutputStr  ="Output directories";
char * TurboCStr  ="Turbo C directory";
char * PickFStr   ="Pick file name";
char * CurrentPStr="Current pick file";
//   Argument子菜单字符串
char * SaveOptStr="Save options";
char * RetriStr  ="Retrieve options";
//   Debug子菜单字符串
char * EvaluteStr="Evalute    Ctrl-F4";
char * CallStkStr="Call stack Ctrl-F3";
char * FindFunStr="Find function";
char * RefreshStr="Refresh display";
char * DisplayStr="Display swapping";
char * SourceDStr="Source debugging";
//   Break/Watch子菜单字符串
char * AddWatStr ="Add watch Ctrl-F7";
char * DeleteStr ="Delete watch";
char * EditWatStr="Edit watch" ;
char * RemAllStr ="Remove all watches";
char * ToggleStr ="Toggle breakpoint Ctrl-F8";
char * ClrAllStr ="Clear all breakpoints";
char * ViewStr   ="View next breakpoint";


//////////////////////////////////////
//     File子菜单结构             //
//////////////////////////////////////
MenuItemStru FileSubM[9] ={{0,0,0,PickStr-LoadStr-1,LoadStr},
                {0,0,0,NewStr-PickStr-1,PickStr},
                {0,0,0,SaveStr-NewStr-1,NewStr},
                {0,0,0,WriteStr-SaveStr-1,SaveStr},
                {0,0,0,DirStr-WriteStr-1,WriteStr},
                {0,0,0,ChangeStr-DirStr-1,DirStr},
                {0,0,0,OsStr-ChangeStr-1,ChangeStr},
                {0,0,0,QuitStr-OsStr-1,OsStr},
                {0,0,0,RunSubStr-QuitStr-1,QuitStr}};

//////////////////////////////////////
//     Run 子菜单结构              //
//////////////////////////////////////
MenuItemStru RunSubM[6] ={{0,0,0,ProgStr-RunSubStr-1,RunSubStr},
           {0,0,0,GotoStr-ProgStr-1,ProgStr},
           {0,0,0,TraceStr-GotoStr-1,GotoStr},
           {0,0,0,StepStr-TraceStr-1,TraceStr},
           {0,0,0,UserStr-StepStr-1,StepStr},
           {0,0,0,CompileStr-UserStr-1,UserStr}};

//////////////////////////////////////
//    Compile子菜单数据结构定义     //
//////////////////////////////////////
MenuItemStru CompSubM[6]={{0,0,0,MakeStr-CompileStr-1,CompileStr},
           {0,0,0,LinkStr-MakeStr-1,MakeStr},
           {0,0,0,BuildStr-LinkStr-1,LinkStr},
           {0,0,0,PrimaryStr-BuildStr-1,BuildStr},
           {0,0,0,GetInfoStr-PrimaryStr-1,PrimaryStr},
           {0,0,0,ProjectStr-GetInfoStr-1,GetInfoStr}};

//////////////////////////////////////
//    project子菜单数据结构定义     //
//////////////////////////////////////
MenuItemStru ProjSubM[5]={{0,0,0,BreakStr-ProjectStr-1,ProjectStr},
           {0,0,0,AutoStr-BreakStr-1,BreakStr},
           {0,0,0,ClearStr-AutoStr-1,AutoStr},
           {0,0,0,RemoveStr-ClearStr-1,ClearStr},
           {0,0,0,CompilerStr-RemoveStr-1,RemoveStr}};

///////////////////////////////////////////////////////////////////////
// Options子菜单数据结构定义                                         //
//该菜单项包含：comiler parameter                                    //
//              Link                                                 //
//              Environment                                          //
//              Directory                                            //
//              Argument                                             //
///////////////////////////////////////////////////////////////////////
//    comiler parameter子菜单数据结构定义     //
MenuItemStru CompPSubM[7]={{0,0,0,DefinesStr-ModelStr-1,ModelStr},
           {0,0,0,CodeStr-DefinesStr-1,DefinesStr},
           {0,0,0,OptimStr-CodeStr-1,CodeStr},
           {0,0,0,SourceStr-OptimStr-1,OptimStr},
           {0,0,0,ErrorsStr-SourceStr-1,SourceStr},
           {0,0,0,NamesStr-ErrorsStr-1,ErrorsStr},
           {0,0,0,MapStr-NamesStr-1,NamesStr}};

//    Link子菜单数据结构定义     //
MenuItemStru LinkerSubM[6]  ={{0,0,0,InitialStr-MapStr-1,MapStr},
           {0,0,0,DefaultStr-InitialStr-1,InitialStr},
           {0,0,0,WarnStr-DefaultStr-1,DefaultStr},
           {0,0,0,StackStr-WarnStr-1,WarnStr},
           {0,0,0,CaseStr-StackStr-1,StackStr},
           {0,0,0,MessageStr-CaseStr-1,CaseStr}};

//   Environment子菜单数据结构定义  //
MenuItemStru EnvironSubM[8]  ={{0,0,0,KeepStr-MessageStr-1,MessageStr},
            {0,0,0,ConfigStr-KeepStr-1,KeepStr},
            {0,0,0,EditAutoStr-ConfigStr-1,ConfigStr},
            {0,0,0,BackupStr-EditAutoStr-1,EditAutoStr},
            {0,0,0,TabSizeStr-BackupStr-1,BackupStr},
            {0,0,0,ZoomedStr-TabSizeStr-1,TabSizeStr},
            {0,0,0,ScreenStr-ZoomedStr-1,ZoomedStr},
            {0,0,0,ScreenStr-ScreenStr-1,ScreenStr}};

//   Directory子菜单数据结构定义   //
MenuItemStru DirectSubM[6]  ={{0,0,0,LibraryStr-IncludeStr-1,IncludeStr},
            {0,0,0,OutputStr-LibraryStr-1,LibraryStr},
            {0,0,0,TurboCStr-OutputStr-1,OutputStr},
            {0,0,0,PickFStr-TurboCStr-1,TurboCStr},
            {0,0,0,CurrentPStr-PickFStr-1,PickFStr},
            {0,0,0,SaveOptStr-CurrentPStr-1,CurrentPStr}};

//   Argument  子菜单数据结构定义   //
MenuItemStru ArgumentSubM[2] ={{0,0,0,RetriStr-SaveOptStr-1,SaveOptStr},
             {0,0,0,EvaluteStr-RetriStr-1,RetriStr}};

//////////////////////////////////////
//    Option子菜单数据结构定义      //
//////////////////////////////////////
MenuItemStru OptSubM[5]={{7,OptimStr-CodeStr-1,CompPSubM,LinkerStr-CompilerStr-1,CompilerStr},
           {5,StackStr-WarnStr-1,LinkerSubM,EnvironStr-LinkerStr-1,LinkerStr},
           {5,EditAutoStr-ConfigStr-1,EnvironSubM,DirectStr-EnvironStr-1,EnvironStr},
           {5,OutputStr-LibraryStr-1,DirectSubM,ArgumentStr-DirectStr-1,DirectStr},
           {2,EvaluteStr-RetriStr-1,ArgumentSubM,ModelStr-ArgumentStr-1,ArgumentStr}};

//////////////////////////////////////
//   Debug  子菜单数据结构定义     //
//////////////////////////////////////
MenuItemStru DebSubM[6]={{0,0,0,CallStkStr-EvaluteStr-1,EvaluteStr},
           {0,0,0,FindFunStr-CallStkStr-1,CallStkStr},
           {0,0,0,RefreshStr-FindFunStr-1,FindFunStr},
           {0,0,0,DisplayStr-RefreshStr-1,RefreshStr},
           {0,0,0,SourceDStr-DisplayStr-1,DisplayStr},
           {0,0,0,AddWatStr-SourceDStr-1,SourceDStr}};

//////////////////////////////////////
//   Break/Watch子菜单数据结构定义  //
//////////////////////////////////////
MenuItemStru WatSubM[7] ={{0,0,0,DeleteStr-AddWatStr-1,AddWatStr},
           {0,0,0,EditWatStr-DeleteStr-1,DeleteStr},
           {0,0,0,RemAllStr-EditWatStr-1,EditWatStr},
           {0,0,0,ToggleStr-RemAllStr-1,RemAllStr},
           {0,0,0,ClrAllStr-ToggleStr-1,ToggleStr},
           {0,0,0,ViewStr-ClrAllStr-1,ClrAllStr},
           {0,0,0,20,ViewStr}};//

//////////////////////////////////////
//         主菜单数据结构定义       //
//////////////////////////////////////
char * FileStr="File";
char * EditStr="Edit";
char * RunStr ="Run";
char * CompStr="Compile";
char * ProjStr="Project";
char * OptStr ="Options";
char * DebStr ="Debug";
char * WatStr ="Break/Watch";
int MainMenuItemCol[MainMenuCount]={0x03,0x0b,0x13,0x19,0x25,0x30,0x3a,0x42};         //主菜单待显示的列位置

//实训三的主菜单数组,MyMenu是实验临时用数组，该数组其实可从下文MainMenu数组中得到
char * MyMenu[MainMenuCount]={FileStr,EditStr,RunStr,CompStr,ProjStr,OptStr,DebStr,WatStr};

MenuItemStru MainMenu[MainMenuCount]={{0x09,NewStr-PickStr-1,FileSubM,EditStr-FileStr-1,FileStr},
                                      {0x0 ,00, 0,RunStr-EditStr-1,EditStr},
                                      {0x06,GotoStr-ProgStr-1,RunSubM ,CompStr-RunStr-1,RunStr},
                                      {0x06,GetInfoStr-PrimaryStr-1,CompSubM,ProjStr-CompStr-1,CompStr},
                                      {0x05,ClearStr-AutoStr-1,ProjSubM,OptStr-ProjStr-1,ProjStr},
                                      {0x07,ClrAllStr-ToggleStr-1,WatSubM,11,WatStr},
                                      {0x06,FindFunStr-CallStkStr-1,DebSubM ,WatStr-DebStr-1,DebStr},
                                      {0x05,ArgumentStr-DirectStr-1,OptSubM ,DebStr-OptStr-1,OptStr}};
MenuItemStru RootMenu={8,0,MainMenu,0,0};//根节点 

//选择历史缓冲区
CHAR_INFO SecondSave[300],FirstSave[300];
MenuSelectStru His[3]={{0,8,MainMenu,0,false,0,0,0,0},
               {0,0,0,FirstSave,false,0,0,0,0},
               {0,0,0,SecondSave,false,0,0,0,0}};
int Layer=0;  //当前菜单操作的层 
ShortInt SelectLayer=0;
KeyValueStru CurrentKey; 
         
void MenuBFS(MenuItemStru RootMenu){
	queue<MenuItemStru *> q;
	q.push(&RootMenu);
	MenuItemStru *node;
	int i,cur;
	while(!q.empty()){
		node=q.front();
		q.pop();
		for(int i=0;i<node->SubMenuItemCount;i++)
		{
			printf("%s\n",(node->SubMenuItemAddr+i)->MenuItemStrAddr) ;
			if(node->SubMenuItemAddr+i!=NULL)
			q.push(node->SubMenuItemAddr+i);
		}
	}
}

int main()
{
	clrscr();
 	MenuBFS(RootMenu);
 	kbhit();
}
