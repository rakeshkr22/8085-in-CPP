/*
  Name			: 8085 ASSEMBLER
  Author		: Amal.P.M & Rakesh.K.R
  Date			: 12-08-2k11
  Platform		: Windows
  Compiler		: Turbo C++
  Description	: 8085 Assembler
*/
#include<iostream.h>
#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<conio.h>
#include<window.h>
#include<ioassem.h>
#include<linked~1.h>
#include<optable.h>
#include<mouse.h>
#define INDIRECT 0
#define DIRECT   1
#define HEADER_LEN 16
#define SELECTED_HEADER 4*16+11
#define NORMAL_HEADER 	5*16+15
#define INPUT_SCREEN 	1*16+11
#define OUTPUT_SCREEN 	0*16+11
#define OPEN_WINDOW 	7*16+0
#define OK_BUTTON 		8*16+0
#define OK_SHADE        7*16+0
#define FILE_NAME_COLOR 1*16+15
#define ERROR_COLOR		4*16+15
#define BOTTOM_LINE 	5*16+15
class Assembler_Prgm
{
	private:
		Assem IN;
		Assem_Out OUT;
		Linked_List Sym_Tab;//Symbol Table
		int Loc_Counter;
		Op_Table Op_Tab;   //Opcode Table
		int Hex_To_Dec(char*);
		int Direct_OR_Indirect(char *);
		Linked_List_ IMC;//To store intermediate code
		Window Input_Window,Output_Window;
		int Is_Hexa(char);
		Header Headers[5],Bottom_Line;
		void New();
	public:
		Assembler_Prgm();
		~Assembler_Prgm(){}
		void Error(int);
		void Pass_1();
		void Pass_2();
		void Output_File_Location(char*);
		void Input_File_Location(char*);
		void Set_Loc_Counter(unsigned int);
		void Assembler_Prgm::Assembler();
		void Refresh_All(int);
};
Assembler_Prgm::Assembler_Prgm():Output_Window(42,3,79,23)//Constructor which initialize menu
{
	Loc_Counter=0;
	Headers[0].Set_Values(1,1,HEADER_LEN*1+1,1,"Open");
	Headers[1].Set_Values(HEADER_LEN*1,1,HEADER_LEN*2,2,"Save");
	Headers[2].Set_Values(HEADER_LEN*2,1,HEADER_LEN*3+1,2,"Run");
	Headers[3].Set_Values(HEADER_LEN*3,1,HEADER_LEN*4+1,2,"About");
	Headers[4].Set_Values(HEADER_LEN*4,1,HEADER_LEN*5,2,"Exit");
	Bottom_Line.Set_Values(1,25,80,25,"8085 Assembler");
}
void Assembler_Prgm::Error(int error) //To display error screen
{
	if(error==1)
		;
	else
	{
		Refresh_All(0);
		Header Error;
		if(error==0)
		{
			Error.Set_Values(25,12,60,12,"Error : While opening file. . . ");
			textattr(ERROR_COLOR);
			Error.Refresh();
			getch();
			Refresh_All(0);

		}
		else if(error==-1)
		{
			Error.Set_Values(25,12,60,12,"Error : Invalid Opcode . . .    ");
			textattr(ERROR_COLOR);
			Error.Refresh();
			getch();
			Refresh_All(0);

		}
		else if(error==-2)
		{
			Error.Set_Values(25,12,60,12,"Error : Label Not Found . . .   ");
			textattr(ERROR_COLOR);
			Error.Refresh();
			getch();
			Refresh_All(0);

		}
		else if(error==2)
		{
			Error.Set_Values(25,12,60,12,"Error :  . . .   ");
			textattr(ERROR_COLOR);
			Error.Refresh();
			getch();
			Refresh_All(0);

		}
	}
}
int Assembler_Prgm::Is_Hexa(char c)
{
	return (c>='0'&&c<='9'||c>='A'&&c<='F'||c>='a'&&c<='f')?1:0;
}
int Assembler_Prgm::Direct_OR_Indirect(char *Oprand)//To check operand is direct or indirect
{
	int i,L=strlen(Oprand);
	for(i=0;i<L-1;i++)
		if(!Is_Hexa(Oprand[i]))
			return INDIRECT;
	if(Is_Hexa(Oprand[i])||Oprand[i]=='H'||Oprand[i]=='h')
		return DIRECT;
	return INDIRECT;
}
void Assembler_Prgm::Set_Loc_Counter(unsigned int Loc_Counter)
{
	this->Loc_Counter=Loc_Counter;
}
void Assembler_Prgm::New()//To close current file pointers
{
	Input_Window.Close();
	Output_Window.Close();
	OUT.Close();
	Sym_Tab.Close();
	IMC.Close();
}
void Assembler_Prgm::Pass_1()
{
	int i,Hexcode,Len,Found,N;
	char* Mnemonic_Code,Opcode[15];
	while(!IN.Completed())
	{
		Mnemonic_Code=IN.Get_I();
		 first:
		i=0;
		while(Mnemonic_Code[i]!=':' && Mnemonic_Code[i]!=',' && Mnemonic_Code[i]!='\0')
			Opcode[i++]=Mnemonic_Code[i];
		switch(Mnemonic_Code[i])
		{
			case ':':
				Opcode[i]='\0';
				Sym_Tab.Insert(Opcode,Loc_Counter);
				i++;
				for(int j=0;Mnemonic_Code[i+j];j++)
					Mnemonic_Code[j]=Mnemonic_Code[i+j];
				Mnemonic_Code[j]='\0';
				goto first;
			case '\0':
				Opcode[i]='\0';
				Hexcode=Op_Tab.Search(Opcode,Len,Found);
				if(Found)
					OUT.Put_O(Loc_Counter++,Hexcode);
				else
				{
					i=0;
					while(Opcode[i]!=' '&& Opcode[i]!='\0')
						i++;
					Opcode[i]='\0';
					Hexcode=Op_Tab.Search(Opcode,Len,Found);
					if(Found)
					{
						OUT.Put_O(Loc_Counter++,Hexcode);
						for(int j=i+1;Mnemonic_Code[j];j++)
							Opcode[j-(i+1)]=Mnemonic_Code[j];
						Opcode[j-(i+1)]='\0';
						if(Direct_OR_Indirect(Opcode)==INDIRECT)
						{
							IMC.Insert(Opcode,Loc_Counter,Len);
							for(int j=1;j<Len;j++)
								OUT.Put_O(Loc_Counter++,0xff);
						}
						else if(Len==2)
						{
							Opcode[0]=Mnemonic_Code[++i];
							Opcode[1]=Mnemonic_Code[++i];
							Opcode[2]='\0';
							OUT.Put_O(Loc_Counter++,Hex_To_Dec(Opcode));
						}
						else if(Len==3)
						{
							int Op1,Op2;
							Opcode[0]=Mnemonic_Code[++i];
							Opcode[1]=Mnemonic_Code[++i];
							Opcode[2]='\0';
							Op1=Hex_To_Dec(Opcode);
							Opcode[0]=Mnemonic_Code[++i];
							Opcode[1]=Mnemonic_Code[++i];
							Opcode[2]='\0';
							Op2=Hex_To_Dec(Opcode);
							OUT.Put_O(Loc_Counter++,Op2);
							OUT.Put_O(Loc_Counter++,Op1);
						}
					}
					else if(strcmpi(Opcode,"START")==0||strcmpi(Opcode,"ORIGIN")==0)
					{
						Opcode[0]=Mnemonic_Code[++i];
						Opcode[1]=Mnemonic_Code[++i];
						Opcode[2]=Mnemonic_Code[++i];
						Opcode[3]=Mnemonic_Code[++i];
						Opcode[4]='\0';
						Set_Loc_Counter(Hex_To_Dec(Opcode));
					}
					else if(strcmpi(Opcode,"DS")==0)
					{
						Opcode[0]=Mnemonic_Code[++i];
						Opcode[1]=Mnemonic_Code[++i];
						Opcode[2]='\0';
						N=Hex_To_Dec(Opcode);
						while(N--)
							OUT.Put_O(Loc_Counter++,0);
					}
					else if(strcmpi(Opcode,"DC")==0)
					{
						Opcode[0]=Mnemonic_Code[++i];
						Opcode[1]=Mnemonic_Code[++i];
						Opcode[2]='\0';
						N=Hex_To_Dec(Opcode);
						OUT.Put_O(Loc_Counter++,N);
					}
					else if(strcmpi(Opcode,"END")==0)
						;
					else
						Error(-1);
				}
				break;
			case ',':
				Opcode[i]='\0';
				Hexcode=Op_Tab.Search(Opcode,Len,Found);
				if(Found)
				{
					OUT.Put_O(Loc_Counter++,Hexcode);
					for(int j=i+1;Mnemonic_Code[j];j++)
						Opcode[j-i-1]=Mnemonic_Code[j];
					Opcode[j-i-1]='\0';
					if(Direct_OR_Indirect(Opcode)==INDIRECT)
					{
						IMC.Insert(Opcode,Loc_Counter,Len);
						for(int j=1;j<Len;j++)
							OUT.Put_O(Loc_Counter++,0xff);
					}
					else if(Len==2)
					{
						Opcode[0]=Mnemonic_Code[++i];
						Opcode[1]=Mnemonic_Code[++i];
						Opcode[2]='\0';
						OUT.Put_O(Loc_Counter++,Hex_To_Dec(Opcode));
					}
					else if(Len==3)
					{
							int Op1,Op2;
							Opcode[0]=Mnemonic_Code[++i];
							Opcode[1]=Mnemonic_Code[++i];
							Opcode[2]='\0';
							Op1=Hex_To_Dec(Opcode);
							Opcode[0]=Mnemonic_Code[++i];
							Opcode[1]=Mnemonic_Code[++i];
							Opcode[2]='\0';
							Op2=Hex_To_Dec(Opcode);
							OUT.Put_O(Loc_Counter++,Op2);
							OUT.Put_O(Loc_Counter++,Op1);
					}
				}
				else
				{
					while(Mnemonic_Code[i]!='\0')
						Opcode[i++]=Mnemonic_Code[i];
					Opcode[i]='\0';
					Hexcode=Op_Tab.Search(Opcode,Len,Found);
					if(Found)
						OUT.Put_O(Loc_Counter++,Hexcode);
					else
						Error(-1);
				}
				break;
		}
	}
	Pass_2();
}
void Assembler_Prgm::Pass_2()
{
	unsigned int Loc,Address;
	int Len,Found;
	char* Label;
	for(;!IMC.Is_Empty();IMC.Delete())
	{
		Loc=IMC.Find_Info(Label,Len);
		Address=Sym_Tab.Find_Address(Label,Found);
		if(Found==0)
		{
			Error(-2);
		}
		else if(Len==2)
		{
			OUT.Modify(Loc,Address);
		}
		else if(Len==3)
		{
			OUT.Modify(Loc,Address%0x100);
			OUT.Modify(Loc+1,Address/0x100);
		}
	}
	OUT.Store();
}
int Assembler_Prgm::Hex_To_Dec(char* Hex)//To convert hexadecimal string to decimal
{
	int Dec=0;
	for(int i=0;Hex[i];i++)
		if(Hex[i]>='A'&&Hex[i]<='F')
			Dec=Dec*16+(Hex[i]-55);
		else if(Hex[i]>='a'&&Hex[i]<='f')
			Dec=Dec*16+(Hex[i]-87);
		else if(Hex[i]>='0'&&Hex[i]<='9')
			Dec=Dec*16+(Hex[i]-'0');
		else
			Error(-3);
	return Dec;
}
void Assembler_Prgm::Input_File_Location(char* S)
{
	Error(IN.Input_File(S));
}
void Assembler_Prgm::Output_File_Location(char* S)
{
	OUT.Output_File(S);
}
void Assembler_Prgm::Refresh_All(int a)//To refresh all windows and menu
{

	textattr(INPUT_SCREEN);
	Input_Window.Refresh();
	textattr(OUTPUT_SCREEN);
	Output_Window.Refresh();
	for(int i=0;i<5;i++)
	{
		if(a==i+1)
			textattr(SELECTED_HEADER);
		else
			textattr(NORMAL_HEADER);
		Headers[i].Refresh();

	}
	textattr(BOTTOM_LINE);
	Bottom_Line.Refresh();
}
void Assembler_Prgm::Assembler() //The main screen
{
	clrscr();
	char IN[100],OUT[100],LC[100],choice;
	Mouse mouse;
	int l,i,j,k,IS_IP_GET=0,IS_OP_GET=0,IS_SA_GET=0,Button,X,Y;
	Refresh_All(0);
	do
	{
		if(kbhit())
			choice=getch();
		else
		{
			mouse.Get_Mouse(Button,X,Y);
			if(Button!=0&&Y>=0&&Y<=10)
			{
				delay(50);
				if(X>=0&&X<126)
					choice='o';
				else if(X>=126&&X<253)
					choice='s';
				else if(X>=253&&X<379)
					choice='r';
				else if(X>=379&&X<506)
					choice='a';
				else if(X>=506&&X<=632)
					choice='e';
			}
		}
		if(choice=='o'||choice=='O') //Open
		{
			Refresh_All(1);
			New();
			Window I_F_Window(20,6,60,13);
			textattr(OPEN_WINDOW);
			I_F_Window.Border();
			gotoxy(2,2);
			cprintf("    Input File Name");
			Header OK_Button;
			OK_Button.Set_Values(38,12,43,12," OK ");
			textattr(OK_SHADE);
			OK_Button.Shadow();
			textattr(OK_BUTTON);
			OK_Button.Refresh();
			textattr(FILE_NAME_COLOR);
			Header Input_File;
			Input_File.Set_Values(22,8,58,8,"                  ");
			Input_File.Refresh();
			gotoxy(2,2);
			cprintf("?\b");
			k=0;
			do
			{
				mouse.Get_Mouse(Button,X,Y);
				if(k<0)
					k=0;
				if(Button!=0&&X>=296&&X<=328&&Y>=80&&Y<=96)
				{
					k++;
					break;
				}
				else if(kbhit())
				{
					IN[k++]=getche();
					if(IN[k-1]=='\b')
					{
						k-=2;
						putch(' ');
						putch('\b');
					}
					else if(IN[k-1]=='/')
						IN[k++]='/';
				}
			}while(IN[k-1]!=27&&IN[k-1]!='\n'&&IN[k-1]!='\r');
			IN[k-1]='\0';
			clrscr();
			Input_Window.Set_File(IN);
			Refresh_All(0);
			Input_File_Location(IN);
			IS_IP_GET=1;
			IS_OP_GET=IS_SA_GET=0;
			choice='\0';
		}
		else if(choice=='S'||choice=='s')//Save
		{
			Refresh_All(2);
			if(IS_IP_GET==1)
			{
				Window I_F_Window(20,6,60,13);
				textattr(OPEN_WINDOW);
				I_F_Window.Border();
				gotoxy(2,2);
				cprintf("    Output File Name");
				Header OK_Button;
				OK_Button.Set_Values(38,12,43,12," OK ");
				textattr(OK_SHADE);
				OK_Button.Shadow();
				textattr(OK_BUTTON);
				OK_Button.Refresh();
				textattr(FILE_NAME_COLOR);
				Header Input_File;
				Input_File.Set_Values(22,8,58,8,"                  ");
				Input_File.Refresh();
				gotoxy(2,2);
				cprintf("?\b");
				j=0;
				do
				{
					mouse.Get_Mouse(Button,X,Y);
					if(k<0)
						k=0;
					if(Button!=0&&X>=296&&X<=328&&Y>=80&&Y<=96)
					{
						j++;
						break;
					}
					else if(kbhit())
					{
						OUT[j++]=getche();
						if(OUT[j-1]=='\b')
						{
							j-=2;
							putch(' ');
							putch('\b');
						}
						else if(OUT[j-1]=='/')
							OUT[j++]='/';
					}
				}while(OUT[j-1]!=27&&OUT[j-1]!='\n'&&OUT[j-1]!='\r');
				OUT[j-1]='\0';
				Output_File_Location(OUT);
				IS_OP_GET=1;
				Output_Window.Set_File(OUT);
				if(!IS_SA_GET)
				{
					goto RUN;
				}
				Pass_1();
				Output_Window.Set_File(OUT);
				clrscr();
				Refresh_All(0);
				IS_IP_GET=IS_OP_GET=IS_SA_GET=0;
			}
			choice='\0';
		}
		else if(choice=='R'||choice=='r')//Run
		{

			Refresh_All(3);
			if(IS_IP_GET==1)
			{
			RUN:
				unsigned int Location;
				Window I_F_Window(20,6,60,13);
				textattr(OPEN_WINDOW);
				I_F_Window.Border();
				gotoxy(2,2);
				cprintf("Starting Address");
				Header OK_Button;
				OK_Button.Set_Values(38,12,43,12," OK ");
				textattr(OK_SHADE);
				OK_Button.Shadow();
				textattr(OK_BUTTON);
				OK_Button.Refresh();
				textattr(FILE_NAME_COLOR);
				Header Input_File;
				Input_File.Set_Values(22,8,58,8,"                  ");
				Input_File.Refresh();
				gotoxy(2,2);
				cprintf("?\b");
				j=0;
				do
				{
					mouse.Get_Mouse(Button,X,Y);
					if(Button!=0&&X>=296&&X<=328&&Y>=80&&Y<=96)
					{
						j++;
						break;
					}
					else if(kbhit())
					{
						LC[j]=getche();
						if(Is_Hexa(LC[j]))
							j++;
					}

				}while(LC[j]!=27&&LC[j]!='\n'&&LC[j]!='\r');
				LC[j]='\0';
				Set_Loc_Counter(Hex_To_Dec(LC));
				if(IS_OP_GET==0)
				{
					strcpy(OUT,IN);
					for(l=strlen(IN);IN[l]!='.'&&l>0;l--);
					OUT[l+1]='O';
					OUT[l+2]='u';
					OUT[l+3]='T';
					OUT[l+4]='\0';
					Output_File_Location(OUT);
					Output_Window.Set_File(OUT);
				}
				Pass_1();
				clrscr();
				Refresh_All(0);
				IS_SA_GET=1;
			}
			choice='\0';
		}
		else if(choice=='A'||choice=='a')//About
		{
			Refresh_All(4);
			{
				Window I_F_Window(20,6,60,15);
				textattr(OPEN_WINDOW);
				I_F_Window.Border();
				gotoxy(2,2);
				cprintf("%27s\n","8085 Assembler");
				for(i=0;i<13;i++)
					cprintf("\b");
				cprintf("%s\n","Version 1.0");
				for(i=0;i<14;i++)
					cprintf("\b");
				cprintf("%s\n\n","CSE 2k9-2k13 Batch");
				for(i=0;i<25;i++)
					cprintf("\b");
				cprintf("%s\n","Guided By: Tomsy Paul (AP in CSE)");
				for(i=0;i<33;i++)
					cprintf("\b");
				cprintf("%s\n","Program developed by: Amal & Rakesh");
				for(i=0;i<36;i++)
					cprintf("\b");
				cprintf("%s\n","Government Engineering College, Idukki");
				Header OK_Button;
				OK_Button.Set_Values(38,14,43,14," OK ");

				textattr(OK_SHADE);
				OK_Button.Shadow();
				textattr(OK_BUTTON);
				OK_Button.Refresh();
				do
				{
					mouse.Get_Mouse(Button,X,Y);
					if(Button!=0&&X>=288&&X<=335&&Y>=95&&Y<=115)
						break;
					else if(kbhit())
					{
						getch();
						break;
					}
				}while(1);
			}
			clrscr();
			choice='\0';
			Refresh_All(0);
		}
		else if(choice=='E'||choice=='e')//Exit
			choice=27;
	}while(choice!=27);
}
main(int Num_Arg,char *Arg[])
{
	Assembler_Prgm ASM;

	if(Num_Arg==1)
		ASM.Assembler();
	else if(Num_Arg==2)
	{
		ASM.Input_File_Location(Arg[1]);
		char OUT[100];
		strcpy(OUT,Arg[1]);
		for(int l=strlen(Arg[1]);Arg[1][l]!='.'&&l>0;l--);
		OUT[l+1]='O';
		OUT[l+2]='u';
		OUT[l+3]='T';
		OUT[l+4]='\0';
		ASM.Output_File_Location(OUT);
		ASM.Pass_1();
	}
	else if(Num_Arg==3)
	{
		ASM.Input_File_Location(Arg[1]);
		ASM.Output_File_Location(Arg[2]);
		ASM.Pass_1();
	}
	return 0;
}