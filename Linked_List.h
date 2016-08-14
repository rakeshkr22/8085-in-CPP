/*To store the symbol table and intermediate code*/
class Node_
{
	private:
		char* Symbol;
		int Address;
		int Length;
		Node_* Next;
	public:
		Node_();
		void Set_Symbol(char*,int,int);
		int Get_Address();
		char* Get_Symbol();
		int Get_Length();
		void Set_Next(Node_*);
		Node_* Get_Next();
};
class Linked_List_
{
	private:
		Node_* START;
	public:
		Linked_List_();
		void Insert(char*,int,int);
		int Delete();
		int Find_Info(char*&,int &);
		int Is_Empty();
		void Close();
};
Node_::Node_()
{
	Next=NULL;
}
void Node_::Set_Symbol(char* Symbol,int Address,int Length)
{
	this->Symbol=new char[strlen(Symbol)+1];
	strcpy(this->Symbol,Symbol);
	this->Address=Address;
	this->Length=Length;
}
int Node_::Get_Length()
{
	return this->Length;
}
int Node_::Get_Address()
{
	return this->Address;
}
char* Node_::Get_Symbol()
{
	return this->Symbol;
}
void Node_::Set_Next(Node_* Next)
{
	this->Next=Next;
}
Node_* Node_::Get_Next()
{
	return this->Next;
}
Linked_List_::Linked_List_()
{
	START=NULL;
}
void Linked_List_::Insert(char* Symbol,int Address,int Length)
{
	Node_* PTR;
	PTR=new Node_;
	PTR->Set_Symbol(Symbol,Address,Length);
	PTR->Set_Next(START);
	START=PTR;

}
void Linked_List_::Close()
{
	while(!Is_Empty())
		Delete();
	START=NULL;
}
Linked_List_::~Linked_List_()
{
	Close();
}
int Linked_List_::Is_Empty()
{
	return START==NULL?1:0;
}
int Linked_List_::Delete()
{
	int key=START->Get_Address();
	Node_* PTR=START;
	START=PTR->Get_Next();
	delete PTR;
	return key;
}
int Linked_List_::Find_Info(char *&Symbol,int &Length)
{
	Symbol=START->Get_Symbol();
	Length=START->Get_Length();
	return START->Get_Address();
}
/*******************************************************************/
class Node
{
	private:
		char* Symbol;
		int Address;
		Node* Next;
	public:
		Node();
		void Set_Symbol(char*,int);
		int Get_Address();
		char* Get_Symbol();
		void Set_Next(Node*);
		Node* Get_Next();
};
class Linked_List
{
	private:
		Node* START;
	public:
		Linked_List();
		void Insert(char*,int);
		int Delete();
		int Find_Address(char*,int&);
		void Close();
		~Linked_List();
};
Linked_List::~Linked_List()
{
	Close();
}
void Linked_List::Close()
{
	while(!Is_Empty())
		Delete();
	START=NULL;
}
Node::Node()
{
	Next=NULL;
}
void Node::Set_Symbol(char* Symbol,int Address)
{
	this->Symbol=new char[strlen(Symbol)+1];
	strcpy(this->Symbol,Symbol);
	this->Address=Address;
}
int Node::Get_Address()
{
	return this->Address;
}
char* Node::Get_Symbol()
{
	return this->Symbol;
}
void Node::Set_Next(Node* Next)
{
	this->Next=Next;
}
Node* Node::Get_Next()
{
	return this->Next;
}
Linked_List::Linked_List()
{
	START=NULL;
}
void Linked_List::Insert(char* Symbol,int Address)
{
	Node* PTR;
	PTR=new Node;
	PTR->Set_Symbol(Symbol,Address);
	PTR->Set_Next(START);
	START=PTR;

}
int Linked_List::Delete()
{
	int key=START->Get_Address();
	Node* PTR=START;
	START=PTR->Get_Next();
	delete PTR;
	return key;
}
int Linked_List::Find_Address(char* Symbol,int &Found)
{
	Node* PTR=START;
	Found=0;
	while(PTR!=NULL && strcmpi(Symbol,PTR->Get_Symbol()))
		PTR=PTR->Get_Next();
	if(PTR)
		Found=1;
	return PTR?PTR->Get_Address():0;
}