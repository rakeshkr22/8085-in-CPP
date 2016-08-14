class Window
{
	private:
		int X1,Y1,X2,Y2;
		FILE *fp;
		char L[20];
	public:
		Window();
		void Set_File(char*);
		void Refresh();
		Window(int x1,int y1,int x2,int y2);
		void Border();
		void Close();
		~Window();
};
Window::~Window()
{
	Close();
}
void Window::Close()
{
	fclose(fp);
	fp=NULL;
}
Window::Window()//Defines active text-mode window
{
	fp=NULL;
	X1=2;
	Y1=3;
	X2=39;
	Y2=23;
}
void Window::Border()//Draw border for text-mode window
{
	int x=X1-1,y=Y1-1;
	char Array[100];
	window(X1-1,Y1-1,X2+1,Y2+2);
	cprintf("%c",201);
	for(;x<X2;x++)
		cprintf("%c",205);
	cprintf("%c",187);
	sprintf(Array,"%%c%%%dc",X2-X1+2);
	for(;y<Y2;y++)
		cprintf(Array,186,186);
	cprintf("%c",200);
	for(x=X1-1;x<X2;x++)
		cprintf("%c",205);
	cprintf("%c",188);
}
Window::Window(int x1,int y1,int x2,int y2)
{
	fp=NULL;
	X1=x1;
	Y1=y1;
	X2=x2;
	Y2=y2;
}
void Window::Set_File(char* Loc)//To connect files with window
{
		strcpy(L,Loc);
	this->fp=fopen(Loc,"r");
}
void Window::Refresh()//To display the window
{
	Border();
	window(X1,Y1,X2,Y2);
	char c;
	if(fp)
		rewind(fp);
	char  Prev,Curr;
	while(fp&&!feof(fp))
	{
		Prev=Curr;
		Curr=getc(fp);
		if(!((Curr==' '||Curr=='\n')&&Prev=='\n'))
		{
			if(Curr=='\t')
				Curr=' ';
			if(!(Prev==':'&&Curr==' '||Prev==' '&&Curr==' '))
			{
				putch(Curr);
			}
		}
		if(Curr=='\n')
			putch('\r');
	}
}
class Header
{
	private:
		int X1,X2,Y1,Y2;
		char *Name;
	public:
		Header();
		void Refresh();
		void Set_Values(int,int,int,int,char*);
		void Shadow();
		~Header();
};
Header::~Header()
{
	delete Name;
}
Header::Header()
{
	X1=1;
	X2=80;
	Y1=1;
	Y2=2;
}
void Header::Set_Values(int x1,int y1,int x2,int y2,char* name)
{
	X1=x1;
	X2=x2;
	Y1=y1;
	Y2=y2;
	Name=new char[strlen(name)+1];
	strcpy(Name,name);
}
void Header::Refresh()//To display the header(menu,buttons,etc..)
{
	window(X1,Y1,X2,Y2);
	int x,l=strlen(Name);
	l=(X2-X1-l)/2;
	for(x=0;x<l;x++)
		cprintf(" ");
	cprintf(Name);
	for(x=0;x<l;x++)
		cprintf(" ");
}
void Header::Shadow()//To give shadow to the buttons
{
	window(X1+1,Y1,X2,Y2+2);
	int x;
	for(x=X1;x<X2-2;x++)
		cprintf(" ");
	cprintf("%c ",220);
	for(x=X1;x<X2-1;x++)
		cprintf("%c",223);
}