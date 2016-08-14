
class Assem
{
	private:
		char* A;
		FILE* fp;
	public:
		Assem();
		~Assem();
		char* Get_I();
		int Input_File(char*);
		int Completed();
};
class NODE
{
	private:
		unsigned int Loc_Counter,Hexcode;
		NODE *Next;
	public:
		NODE();
		void Set_Next(NODE *);
		NODE* Get_Next();
		void Insert(unsigned int,int);
		int Get_Address();
		void Read(unsigned int&,int&);
};
class Assem_Out
{
	private:
		FILE* fp;
		NODE* START,*END;
	public:
		Assem_Out();
		~Assem_Out();
		void Put_O(unsigned int,int);
		void Output_File(char*);
		void Store();
		void Close();
		void Modify(unsigned int,int);
};
NODE::NODE()
{
	Next=NULL;
}
void NODE::Set_Next(NODE* Next)
{
	this->Next=Next;
}
NODE* NODE::Get_Next()
{
	return Next;
}
int NODE::Get_Address()
{
	return Loc_Counter;
}
void NODE::Insert(unsigned int Loc_Counter,int Hexcode)
{
	this->Loc_Counter=Loc_Counter;
	this->Hexcode=Hexcode;
}
void NODE::Read(unsigned int& Loc_Counter,int& Hexcode)
{
	Loc_Counter=this->Loc_Counter;
	Hexcode=this->Hexcode;
}
//**************************************************
Assem::Assem()
{
	A=NULL;
}
Assem()::~Assem()
{
	fclose fp;
}
char* Assem::Get_I() //To read input file
{
	char A[80],Prev,Curr;
	int i=0;
	do
	{
		Prev=Curr;
		Curr=getc(fp);
		if(!(Curr==' '&&i==0))
		{
			if(Curr=='\t')
				Curr=' ';
			if(!(Prev==':'&&Curr==' '||Prev==' '&&Curr==' '))
			{
				A[i++]=Curr;
				if(!(Prev==' '&&Curr==':'||Prev==' '&&Curr==':'))
					A[i-1]=Curr;
			}
		}
	}
	while(Curr!='\n'&&!feof(fp));
	this->A=new char[i];
	A[--i]='\0';
	strcpy(this->A,A);
	return this->A;
}
int Assem::Input_File(char* Location)
{
	fp=fopen(Location,"r");
	if(!fp)
		return 0;
	return 1;
}
int Assem::Completed()
{
	return feof(fp);
}
//******************************************************
Assem_Out::~Assem_Out()
{
	fclose(fp);
}
Assem_Out::Assem_Out()
{
	fp=NULL;
	START=END=NULL;
}
void Assem_Out::Close()
{
	fclose(fp);
	fp=NULL;
	START=END=NULL;
}
void Assem_Out::Modify(unsigned int Loc_Counter,int Hex_Code)
{
	NODE* PTR=START;
	while(PTR&&PTR->Get_Address()!=Loc_Counter)
		PTR=PTR->Get_Next();
	if(PTR!=NULL)
		PTR->Insert(Loc_Counter,Hex_Code);
}
void Assem_Out::Put_O(unsigned int Loc_Counter,int Hex_Code)
{
	NODE* PTR=new NODE;
	PTR->Insert(Loc_Counter,Hex_Code);
	if(START)
		END->Set_Next(PTR);
	else
		START=PTR;
	END=PTR;
}
void Assem_Out::Output_File(char* Location)
{
	if(fp==NULL)
		fp=fopen(Location,"w+");
	else
	{
		fclose(fp);
		fp=fopen(Location,"w+");
		Store();
	}
}
void Assem_Out::Store()//To store the output into a file
{
	NODE* PTR=START;
	unsigned int Loc_Counter;
	int Hex_Code;
	while(PTR)
	{
		PTR->Read(Loc_Counter,Hex_Code);
		fprintf(fp,"\n %6X : %02X",Loc_Counter,Hex_Code);
		PTR=PTR->Get_Next();
	}
	fclose(fp);
}