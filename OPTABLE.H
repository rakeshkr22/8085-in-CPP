class Op_Table
{
	private:
		char OPCODE[16][16][10];
		int Length[16][16];
	public:
		Op_Table();
		int Search(char *,int&,int&);
};
int Op_Table::Search(char *OPCOD,int &Len,int& FOUND)
{
	int i,j;
	Len=0;
	for(i=0,FOUND=0;i<16;i++)
		for(j=0;j<16;j++)
			if(!strcmpi(OPCOD,OPCODE[i][j]))
			{
				FOUND=1;
				Len=Length[i][j];
				return ((i*16)+j);
			}
	return -1;
}
Op_Table::Op_Table(){

		strcpy(OPCODE[0][0],"NOP");	strcpy(OPCODE[0][1],"LXI B");	strcpy(OPCODE[0][2],"STAX B");	strcpy(OPCODE[0][3],"INX B");
		strcpy(OPCODE[0][4],"INR B");	strcpy(OPCODE[0][5],"DCR B");	strcpy(OPCODE[0][6],"MVI B");	strcpy(OPCODE[0][7],"RLC");
		strcpy(OPCODE[0][8],"DSUB");	strcpy(OPCODE[0][9],"DAD B");	strcpy(OPCODE[0][10],"LDAX B");	strcpy(OPCODE[0][11],"DCX B");
		strcpy(OPCODE[0][12],"INR C");	strcpy(OPCODE[0][13],"DCR C");	strcpy(OPCODE[0][14],"MVI C");	strcpy(OPCODE[0][15],"RRC");

		strcpy(OPCODE[1][0],"ARHL");	strcpy(OPCODE[1][1],"LXI D");	strcpy(OPCODE[1][2],"STAX D");	strcpy(OPCODE[1][3],"INX D");
		strcpy(OPCODE[1][4],"INR D");	strcpy(OPCODE[1][5],"DCR D");	strcpy(OPCODE[1][6],"MVI D");	strcpy(OPCODE[1][7],"RAL");
		strcpy(OPCODE[1][8],"RDEL");	strcpy(OPCODE[1][9],"DAD D");	strcpy(OPCODE[1][10],"LDAX D");	strcpy(OPCODE[1][11],"DCX D");
		strcpy(OPCODE[1][12],"INR E");	strcpy(OPCODE[1][13],"DCR E");	strcpy(OPCODE[1][14],"MVI E");	strcpy(OPCODE[1][15],"RAR");

		strcpy(OPCODE[2][0],"RIM");	strcpy(OPCODE[2][1],"LXI H");	strcpy(OPCODE[2][2],"SHLD");	strcpy(OPCODE[2][3],"INX H");
		strcpy(OPCODE[2][4],"INR H");	strcpy(OPCODE[2][5],"DCR H");	strcpy(OPCODE[2][6],"MVI H");	strcpy(OPCODE[2][7],"DAA");
		strcpy(OPCODE[2][8],"LDHI");	strcpy(OPCODE[2][9],"DAD H");	strcpy(OPCODE[2][10],"LHLD");	strcpy(OPCODE[2][11],"DCX H");
		strcpy(OPCODE[2][12],"INR L");	strcpy(OPCODE[2][13],"DCR L");	strcpy(OPCODE[2][14],"MVI L");	strcpy(OPCODE[2][15],"CMA");

		strcpy(OPCODE[3][0],"SIM");	strcpy(OPCODE[3][1],"LXI SP");	strcpy(OPCODE[3][2],"STA");	strcpy(OPCODE[3][3],"INX SP");
		strcpy(OPCODE[3][4],"INR M");	strcpy(OPCODE[3][5],"DCR M");	strcpy(OPCODE[3][6],"MVI M");	strcpy(OPCODE[3][7],"STC");
		strcpy(OPCODE[3][8],"LDSI");	strcpy(OPCODE[3][9],"DAD SP");	strcpy(OPCODE[3][10],"LDA");	strcpy(OPCODE[3][11],"DCX SP");
		strcpy(OPCODE[3][12],"INR A");	strcpy(OPCODE[3][13],"DCR A");	strcpy(OPCODE[3][14],"MVI A");	strcpy(OPCODE[3][15],"CMC");

		strcpy(OPCODE[4][0],"MOV B,B");	strcpy(OPCODE[4][1],"MOV B,C");	strcpy(OPCODE[4][2],"MOV B,D");	strcpy(OPCODE[4][3],"MOV B,E");
		strcpy(OPCODE[4][4],"MOV B,H");	strcpy(OPCODE[4][5],"MOV B,L");	strcpy(OPCODE[4][6],"MOV B,M");	strcpy(OPCODE[4][7],"MOV B,A");
		strcpy(OPCODE[4][8],"MOV C,B");	strcpy(OPCODE[4][9],"MOV C,C");	strcpy(OPCODE[4][10],"MOV C,D");strcpy(OPCODE[4][11],"MOV C,E");
		strcpy(OPCODE[4][12],"MOV C,H");strcpy(OPCODE[4][13],"MOV C,L");strcpy(OPCODE[4][14],"MOV C,M");strcpy(OPCODE[4][15],"MOV C,A");

		strcpy(OPCODE[5][0],"MOV D,B");	strcpy(OPCODE[5][1],"MOV D,C");	strcpy(OPCODE[5][2],"MOV D,D");	strcpy(OPCODE[5][3],"MOV D,E");
		strcpy(OPCODE[5][4],"MOV D,H");	strcpy(OPCODE[5][5],"MOV D,L");	strcpy(OPCODE[5][6],"MOV D,M");	strcpy(OPCODE[5][7],"MOV D,A");
		strcpy(OPCODE[5][8],"MOV E,B");	strcpy(OPCODE[5][9],"MOV E,C");	strcpy(OPCODE[5][10],"MOV E,D");strcpy(OPCODE[5][11],"MOV E,E");
		strcpy(OPCODE[5][12],"MOV E,H");strcpy(OPCODE[5][13],"MOV E,L");strcpy(OPCODE[5][14],"MOV E,M");strcpy(OPCODE[5][15],"MOV E,A");

		strcpy(OPCODE[6][0],"MOV H,B");	strcpy(OPCODE[6][1],"MOV H,C");	strcpy(OPCODE[6][2],"MOV H,D");	strcpy(OPCODE[6][3],"MOV H,E");
		strcpy(OPCODE[6][4],"MOV H,H");	strcpy(OPCODE[6][5],"MOV H,L");	strcpy(OPCODE[6][6],"MOV H,M");	strcpy(OPCODE[6][7],"MOV H,A");
		strcpy(OPCODE[6][8],"MOV L,B");	strcpy(OPCODE[6][9],"MOV L,C");	strcpy(OPCODE[6][10],"MOV L,D");strcpy(OPCODE[6][11],"MOV L,E");
		strcpy(OPCODE[6][12],"MOV L,H");strcpy(OPCODE[6][13],"MOV L,L");strcpy(OPCODE[6][14],"MOV L,M");strcpy(OPCODE[6][15],"MOV L,A");

		strcpy(OPCODE[7][0],"MOV M,B");	strcpy(OPCODE[7][1],"MOV M,C");	strcpy(OPCODE[7][2],"MOV M,D");	strcpy(OPCODE[7][3],"MOV M,E");
		strcpy(OPCODE[7][4],"MOV M,H");	strcpy(OPCODE[7][5],"MOV M,L");	strcpy(OPCODE[7][6],"HLT");	strcpy(OPCODE[7][7],"MOV M,A");
		strcpy(OPCODE[7][8],"MOV A,B");	strcpy(OPCODE[7][9],"MOV A,C");	strcpy(OPCODE[7][10],"MOV A,D");strcpy(OPCODE[7][11],"MOV A,E");
		strcpy(OPCODE[7][12],"MOV A,H");strcpy(OPCODE[7][13],"MOV A,L");strcpy(OPCODE[7][14],"MOV A,M");strcpy(OPCODE[7][15],"MOV A,A");

		strcpy(OPCODE[8][0],"ADD B");	strcpy(OPCODE[8][1],"ADD C");	strcpy(OPCODE[8][2],"ADD D");	strcpy(OPCODE[8][3],"ADD E");
		strcpy(OPCODE[8][4],"ADD H");	strcpy(OPCODE[8][5],"ADD L");	strcpy(OPCODE[8][6],"ADD M");	strcpy(OPCODE[8][7],"ADD A");
		strcpy(OPCODE[8][8],"ADC B");	strcpy(OPCODE[8][9],"ADC C");	strcpy(OPCODE[8][10],"ADC D");	strcpy(OPCODE[8][11],"ADC E");
		strcpy(OPCODE[8][12],"ADC H");	strcpy(OPCODE[8][13],"ADC L");	strcpy(OPCODE[8][14],"ADC M");	strcpy(OPCODE[8][15],"ADC A");

		strcpy(OPCODE[9][0],"SUB B");	strcpy(OPCODE[9][1],"SUB C");	strcpy(OPCODE[9][2],"SUB D");	strcpy(OPCODE[9][3],"SUB E");
		strcpy(OPCODE[9][4],"SUB H");	strcpy(OPCODE[9][5],"SUB L");	strcpy(OPCODE[9][6],"SUB M");	strcpy(OPCODE[9][7],"SUB A");
		strcpy(OPCODE[9][8],"SBB B");	strcpy(OPCODE[9][9],"SBB C");	strcpy(OPCODE[9][10],"SBB D");	strcpy(OPCODE[9][11],"SBB E");
		strcpy(OPCODE[9][12],"SBB H");	strcpy(OPCODE[9][13],"SBB L");	strcpy(OPCODE[9][14],"SBB M");	strcpy(OPCODE[9][15],"SBB A");

		strcpy(OPCODE[10][0],"ANA B");	strcpy(OPCODE[10][1],"ANA C");	strcpy(OPCODE[10][2],"ANA D");	strcpy(OPCODE[10][3],"ANA E");
		strcpy(OPCODE[10][4],"ANA H");	strcpy(OPCODE[10][5],"ANA L");	strcpy(OPCODE[10][6],"ANA M");	strcpy(OPCODE[10][7],"ANA A");
		strcpy(OPCODE[10][8],"XRA B");	strcpy(OPCODE[10][9],"XRA C");	strcpy(OPCODE[10][10],"XRA D");	strcpy(OPCODE[10][11],"XRA E");
		strcpy(OPCODE[10][12],"XRA H");	strcpy(OPCODE[10][13],"XRA L");	strcpy(OPCODE[10][14],"XRA M");	strcpy(OPCODE[10][15],"XRA A");

		strcpy(OPCODE[11][0],"ORA B");	strcpy(OPCODE[11][1],"ORA C");	strcpy(OPCODE[11][2],"ORA D");	strcpy(OPCODE[11][3],"ORA E");
		strcpy(OPCODE[11][4],"ORA H");	strcpy(OPCODE[11][5],"ORA L");	strcpy(OPCODE[11][6],"ORA M");	strcpy(OPCODE[11][7],"ORA A");
		strcpy(OPCODE[11][8],"CMP B");	strcpy(OPCODE[11][9],"CMP C");	strcpy(OPCODE[11][10],"CMP D");	strcpy(OPCODE[11][11],"CMP E");
		strcpy(OPCODE[11][12],"CMP H");	strcpy(OPCODE[11][13],"CMP L");	strcpy(OPCODE[11][14],"CMP M");	strcpy(OPCODE[11][15],"CMP A");

		strcpy(OPCODE[12][0],"RNZ");	strcpy(OPCODE[12][1],"POP B");	strcpy(OPCODE[12][2],"JNZ");	strcpy(OPCODE[12][3],"JMP");
		strcpy(OPCODE[12][4],"CNZ");	strcpy(OPCODE[12][5],"PUSH B");	strcpy(OPCODE[12][6],"ADI");	strcpy(OPCODE[12][7],"RST 0");
		strcpy(OPCODE[12][8],"RZ");	strcpy(OPCODE[12][9],"RET");	strcpy(OPCODE[12][10],"JZ");	strcpy(OPCODE[12][11],"RSTV");
		strcpy(OPCODE[12][12],"CZ");	strcpy(OPCODE[12][13],"CALL");	strcpy(OPCODE[12][14],"ACI");	strcpy(OPCODE[12][15],"RST 1");

		strcpy(OPCODE[13][0],"RNC");	strcpy(OPCODE[13][1],"POP D");	strcpy(OPCODE[13][2],"JNC");	strcpy(OPCODE[13][3],"OUT");
		strcpy(OPCODE[13][4],"CNC");	strcpy(OPCODE[13][5],"PUSH D");	strcpy(OPCODE[13][6],"SUI");	strcpy(OPCODE[13][7],"RST 2");
		strcpy(OPCODE[13][8],"RC");	strcpy(OPCODE[13][9],"SHLX");	strcpy(OPCODE[13][10],"JC");	strcpy(OPCODE[13][11],"IN");
		strcpy(OPCODE[13][12],"CC");	strcpy(OPCODE[13][13],"JNK");	strcpy(OPCODE[13][14],"SBI");	strcpy(OPCODE[13][15],"RST 3");

		strcpy(OPCODE[14][0],"RPO");	strcpy(OPCODE[14][1],"POP H");	strcpy(OPCODE[14][2],"JPO");	strcpy(OPCODE[14][3],"XTHL");
		strcpy(OPCODE[14][4],"CPO");	strcpy(OPCODE[14][5],"PUSH H");	strcpy(OPCODE[14][6],"ANI");	strcpy(OPCODE[14][7],"RST 4");
		strcpy(OPCODE[14][8],"RPE");	strcpy(OPCODE[14][9],"PCHL");	strcpy(OPCODE[14][10],"JPE");	strcpy(OPCODE[14][11],"XCHG");
		strcpy(OPCODE[14][12],"CPE");	strcpy(OPCODE[14][13],"LHLX");	strcpy(OPCODE[14][14],"XRI");	strcpy(OPCODE[14][15],"RST 5");

		strcpy(OPCODE[15][0],"RP");	strcpy(OPCODE[15][1],"POP PSW");strcpy(OPCODE[15][2],"JP");	strcpy(OPCODE[15][3],"DI");
		strcpy(OPCODE[15][4],"CP");	strcpy(OPCODE[15][5],"PUSH PSW");strcpy(OPCODE[15][6],"ORI");	strcpy(OPCODE[15][7],"RST 6");
		strcpy(OPCODE[15][8],"RM");	strcpy(OPCODE[15][9],"SPHL");	strcpy(OPCODE[15][10],"JM");	strcpy(OPCODE[15][11],"EI");
		strcpy(OPCODE[15][12],"CM");	strcpy(OPCODE[15][13],"JK");	strcpy(OPCODE[15][14],"CPI");	strcpy(OPCODE[15][15],"RST 7");
Length[0][0]=1;
Length[0][1]=3;
Length[0][2]=1;
Length[0][3]=1;
Length[0][4]=1;
Length[0][5]=1;
Length[0][6]=2;
Length[0][7]=1;
Length[0][8]=1;	//***********DSUB
Length[0][9]=1;
Length[0][10]=1;
Length[0][11]=1;
Length[0][12]=1;
Length[0][13]=1;
Length[0][14]=2;
Length[0][15]=1;
Length[1][0]=1;	//*****ARHL;
Length[1][1]=3;
Length[1][2]=1;
Length[1][3]=1;
Length[1][4]=1;
Length[1][5]=1;
Length[1][6]=2;
Length[1][7]=1;
Length[1][8]=1 ;	//********RDEL
Length[1][9]=1;
Length[1][10]=1;
Length[1][11]=1;
Length[1][12]=1;
Length[1][13]=1;
Length[1][14]=2;
Length[1][15]=1;
Length[2][0]=1;
Length[2][1]=3;
Length[2][2]=3;
Length[2][3]=1;
Length[2][4]=1;
Length[2][5]=1;
Length[2][6]=2;
Length[2][7]=1;
Length[2][8]=1;	//LDHI
Length[2][9]=1;
Length[2][10]=3;
Length[2][11]=1;
Length[2][12]=1;
Length[2][13]=1;
Length[2][14]=2;
Length[2][15]=1;
Length[3][0]=1;
Length[3][1]=3;
Length[3][2]=3;
Length[3][3]=1;
Length[3][4]=1;
Length[3][5]=1;
Length[3][6]=2;
Length[3][7]=1;
Length[3][8]=1;	//LDSI
Length[3][9]=1;
Length[3][10]=3;
Length[3][11]=1;
Length[3][12]=1;
Length[3][13]=1;
Length[3][14]=2;
Length[3][15]=1;
Length[4][0]=1;
Length[4][1]=1;
Length[4][2]=1;
Length[4][3]=1;
Length[4][4]=1;
Length[4][5]=1;
Length[4][6]=1;
Length[4][7]=1;
Length[4][8]=1;
Length[4][9]=1;
Length[4][10]=1;
Length[4][11]=1;
Length[4][12]=1;
Length[4][13]=1;
Length[4][14]=1;
Length[4][15]=1;
Length[5][0]=1;
Length[5][1]=1;
Length[5][2]=1;
Length[5][3]=1;
Length[5][4]=1;
Length[5][5]=1;
Length[5][6]=1;
Length[5][7]=1;
Length[5][8]=1;
Length[5][9]=;
Length[5][10]=1;
Length[5][11]=1;
Length[5][12]=1;
Length[5][13]=1;
Length[5][14]=1;
Length[5][15]=1;
Length[6][0]=1;
Length[6][1]=1;
Length[6][2]=1;
Length[6][3]=1;
Length[6][4]=1;
Length[6][5]=1;
Length[6][6]=1;
Length[6][7]=1;
Length[6][8]=1;
Length[6][9]=1;
Length[6][10]=1;
Length[6][11]=1;
Length[6][12]=1;
Length[6][13]=1;
Length[6][14]=1;
Length[6][15]=1;
Length[7][0]=1;
Length[7][1]=1;
Length[7][2]=1;
Length[7][3]=1;
Length[7][4]=1;
Length[7][5]=1;
Length[7][6]=1;
Length[7][7]=1;
Length[7][8]=1;
Length[7][9]=1;
Length[7][10]=1;
Length[7][11]=1;
Length[7][12]=;
Length[7][13]=1;
Length[7][14]=1;
Length[7][15]=1;
Length[8][0]=1;
Length[8][1]=1;
Length[8][2]=1;
Length[8][3]=1;
Length[8][4]=1;
Length[8][5]=1;
Length[8][6]=1;
Length[8][7]=1;
Length[8][8]=1;
Length[8][9]=1;
Length[8][10]=1;
Length[8][11]=1;
Length[8][12]=1;
Length[8][13]=1;
Length[8][14]=1;
Length[8][15]=1;
Length[9][0]=1;
Length[9][1]=1;
Length[9][2]=1;
Length[9][3]=1;
Length[9][4]=1;
Length[9][5]=1;
Length[9][6]=1;
Length[9][7]=1;
Length[9][8]=1;
Length[9][9]=1;
Length[9][10]=1;
Length[9][11]=1;
Length[9][12]=1;
Length[9][13]=1;
Length[9][14]=1;
Length[9][15]=1;
Length[10][0]=1;
Length[10][1]=1;
Length[10][2]=1;
Length[10][3]=1;
Length[10][4]=1;
Length[10][5]=1;
Length[10][6]=1;
Length[10][7]=1;
Length[10][8]=1;
Length[10][9]=1;
Length[10][10]=1;
Length[10][11]=1;
Length[10][12]=1;
Length[10][13]=1;
Length[10][14]=1;
Length[10][15]=1;
Length[11][0]=1;
Length[11][1]=1;
Length[11][2]=1;
Length[11][3]=1;
Length[11][4]=1;
Length[11][5]=1;
Length[11][6]=1;
Length[11][7]=1;
Length[11][8]=1;
Length[11][9]=1;
Length[11][10]=1;
Length[11][11]=1;
Length[11][12]=1;
Length[11][13]=1;
Length[11][14]=1;
Length[11][15]=1;
Length[12][0]=1;
Length[12][1]=1;
Length[12][2]=3;
Length[12][3]=3;
Length[12][4]=3;
Length[12][5]=1;
Length[12][6]=2;
Length[12][7]=1;
Length[12][8]=1;
Length[12][9]=1;
Length[12][10]=3;
Length[12][11]=1;		//RSTV
Length[12][12]=3;
Length[12][13]=3;
Length[12][14]=2;
Length[12][15]=1;
Length[13][0]=1;
Length[13][1]=1;
Length[13][2]=3;
Length[13][3]=2;
Length[13][4]=3;
Length[13][5]=1;
Length[13][6]=2;
Length[13][7]=1;
Length[13][8]=1;
Length[13][9]=3;	//SHLX
Length[13][10]=3;
Length[13][11]=2;
Length[13][12]=3;
Length[13][13]=3;		//JNK
Length[13][14]=2;
Length[13][15]=1;
Length[14][0]=1;
Length[14][1]=1;
Length[14][2]=3;
Length[14][3]=1;
Length[14][4]=3;
Length[14][5]=1;
Length[14][6]=2;
Length[14][7]=1;
Length[14][8]=1;
Length[14][9]=1;
Length[14][10]=3;
Length[14][11]=1;
Length[14][12]=3;
Length[14][13]=3;		//LHLX
Length[14][14]=2;
Length[14][15]=1;
Length[15][0]=1;
Length[15][1]=1;
Length[15][2]=3;
Length[15][3]=1;
Length[15][4]=3;
Length[15][5]=1;
Length[15][6]=2;
Length[15][7]=1;
Length[15][8]=1;
Length[15][9]=1;
Length[15][10]=3;
Length[15][11]=1;
Length[15][12]=3;
Length[15][13]=3;		//JK
Length[15][14]=2;
Length[15][15]=1;
}