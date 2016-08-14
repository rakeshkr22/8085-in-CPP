/*To implement mouse on program*/
class Mouse
{
	private:
		union REGS i,o; //The union REGS is used to pass information to and from the function int86
	public:
		Mouse();
		void Get_Mouse(int&,int&,int&);
};
Mouse::Mouse()
{
	i.x.ax=0;
	int86(0x33,&i,&o);
	i.x.ax=1;
	int86(0x33,&i,&o);//To show mouse pointer on screen
}
void Mouse::Get_Mouse(int &Button,int &X,int &Y)//To get status of mouse buttons & mouse pointer position
{
	i.x.ax=3;
	int86(0x33,&i,&o);
	Button=o.x.bx;
	X=o.x.cx;
	Y=o.x.dx;
}