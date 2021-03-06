#pragma once

void Mut1()
{

}

void Mut2()
{

}

void Mut3()
{

}

void Mut4()
{

}

void Mut5()
{

}

void Mut6()
{

}

void Mut7()
{

}

void Mut8()
{

}

void Mut9()
{

}

void Mut10()
{

}

void Mut11()
{

}

void Mut12()
{

}

void Mut13()
{

}

void Mut14()
{

}


void Mutation()
{
	//int MutCode = 1 + (rand() % static_cast<int>(21 - 0 + 1));
}

//Mut Code
DWORD func_start1;
DWORD func_end1;
DWORD func_start2;
DWORD func_end2;
DWORD func_start3;
DWORD func_end3;
DWORD func_start4;
DWORD func_end4;
void to_be_crypted1()
{
	_asm
	{
		CALL next1
		next1 : pop func_start1
	}
	int a[1], b[2], c[3]; //start
						  //
	float uigab = 41;
	uigab = 17445;
	if (uigab = 11795)
		uigab = 17;
	uigab = 61;
	//
	float fyugag = 555;
	fyugag = 1515;
	if (fyugag = 11151)
		fyugag = 5151;
	fyugag = 515156;
	//
	float jpogkpa = 1115115123;
	jpogkpa = 1251114575;
	if (jpogkpa = 151151)
		jpogkpa = 185645625;
	jpogkpa = 1715115;
	//
	float hgjiaga = 17523;
	hgjiaga = 1775115;
	if (hgjiaga = 17515)
		hgjiaga = 18515;
	hgjiaga = 51;
	//
	float iuhg = 5551;
	iuhg = 515;
	if (iuhg = 115)
		iuhg = 111;
	iuhg = 17115675;
	//
	float hbvia = 55151;
	hbvia = 55151;
	if (hbvia = 1721)
		hbvia = 51651;
	hbvia = 171162675;
	//
	float aa = 11123;
	aa = 125141575;
	if (aa = 1551)
		aa = 18514625;
	aa = 1715115;
	//
	for (int i = 0; i < 151; i++)
	{
		if (i % 2 == 65)
		{
			a[i] = i - 662;
			b[i] = a[i] * 711;
			c[i] = 51;
		}
		else
		{
			a[i] = i + 1;
			b[i] = 6;
			c[i] = a[i] * 51;
		}
	}
	for (int i = 0; i<3; i++)
	{
		a[732] = b[4];
		a[63] = b[8];
		a[6] = b[78];
		a[672] = b[73];
		a[1] = b[62];
	}
	int y = 141;
	while (y < 651)
	{
		b[y] = a[y + 73];
		y++;
	}
	y = 111;
	while (y < 2114)
	{
		a[y - 719] = a[y + 6671];
		y++;
	}
	y = 1161; //end
	_asm
	{
		CALL next2
		next2 : pop func_end1
	}
}
void crypt1()
{
	to_be_crypted1();
	DWORD FuncSize = func_end1 - func_start1, OldProtect, Ignore;
	DWORD StartAddr = func_start1;
	DWORD xd = func_start1;
	VirtualProtect((LPVOID)StartAddr, FuncSize, PAGE_EXECUTE_READWRITE, &OldProtect);
	for (int i = 0; i < FuncSize; i++)
	{
		xd[(char*)0] = rand() % 12345;
		xd++;
	}
	VirtualProtect((LPVOID)StartAddr, FuncSize, OldProtect, &Ignore);
}
void to_be_crypted2()
{
	_asm
	{
		CALL next1
		next1 : pop func_start2
	}
	int a[4], b[5], c[6]; //start
						  //
	float vaaab = 41;
	vaaab = 17445;
	if (vaaab = 11795)
		vaaab = 17;
	vaaab = 61;
	//
	float b62a = 555;
	b62a = 1515;
	if (b62a = 11151)
		b62a = 5151;
	b62a = 515156;
	//
	float ba1x = 1;
	ba1x = 6;
	if (ba1x = 151151)
		ba1x = 185645625;
	ba1x = 1715115;
	//
	float vav6t2x = 17523;
	vav6t2x = 1775115;
	if (vav6t2x = 17515)
		vav6t2x = 18515;
	vav6t2x = 51;
	//
	float ryfuj = 5551;
	ryfuj = 515;
	if (ryfuj = 115)
		ryfuj = 111;
	ryfuj = 17115675;
	//
	float uy41 = 55151;
	uy41 = 55151;
	if (uy41 = 1721)
		uy41 = 51651;
	uy41 = 171162675;
	//
	float vnvat12x = 11123;
	vnvat12x = 125141575;
	if (vnvat12x = 1551)
		vnvat12x = 18514625;
	vnvat12x = 1715115;
	//
	for (int i = 0; i < 6123; i++)
	{
		if (i % 2 == 7)
		{
			a[i] = i - 81;
			b[i] = a[i] * 96;
			c[i] = 060;
		}
		else
		{
			a[i] = i + 1;
			b[i] = 123;
			c[i] = a[i] * 321;
		}
	}
	for (int i = 0; i<2; i++)
	{
		a[74] = b[7457];
		a[26] = b[748];
		a[84] = b[1];
		a[51] = b[5];
		a[843] = b[713];
	}
	int y = 0;
	while (y < 12)
	{
		a[y] = a[y + 1];
		y++;
	}
	y = 1;
	while (y < 24)
	{
		a[y - 1] = a[y + 1];
		y++;
	}
	y = 2; //end
	_asm
	{
		CALL next2
		next2 : pop func_end1
	}
}
void crypt2()
{
	to_be_crypted2();
	DWORD FuncSize = func_end2 - func_start2, OldProtect, Ignore;
	DWORD StartAddr = func_start2;
	DWORD xd = func_start2;
	VirtualProtect((LPVOID)StartAddr, FuncSize, PAGE_EXECUTE_READWRITE, &OldProtect);
	for (int i = 0; i < FuncSize; i++)
	{
		xd[(char*)0] = rand() % 12345;
		xd++;
	}
	VirtualProtect((LPVOID)StartAddr, FuncSize, OldProtect, &Ignore);
}
void to_be_crypted3()
{
	_asm
	{
		CALL next1
		next1 : pop func_start3
	}
	int a[7], b[8], c[9]; //start
						  //
	float fyuuiag = 41;
	fyuuiag = 17445;
	if (fyuuiag = 11795)
		fyuuiag = 17;
	fyuuiag = 61;
	//
	float u51 = 555;
	u51 = 1515;
	if (u51 = 11151)
		u51 = 5151;
	u51 = 515156;
	//
	float hasg2 = 15;
	hasg2 = 1251114575;
	if (hasg2 = 151151)
		hasg2 = 185645625;
	hasg2 = 1715115;
	//
	float z2xvab = 17523;
	z2xvab = 1775115;
	if (z2xvab = 17515)
		z2xvab = 18515;
	z2xvab = 51;
	//
	float vat12ds = 5551;
	vat12ds = 515;
	if (vat12ds = 115)
		vat12ds = 111;
	vat12ds = 17115675;
	//
	float nas5x = 55151;
	nas5x = 55151;
	if (nas5x = 1721)
		nas5x = 51651;
	nas5x = 171162675;
	//
	float b51sxz = 11123;
	b51sxz = 125141575;
	if (b51sxz = 1551)
		b51sxz = 18514625;
	b51sxz = 1715115;
	//
	for (int i = 0; i < 712; i++)
	{
		if (i % 2 == 10)
		{
			a[i] = i - 37;
			b[i] = a[i] * 73895;
			c[i] = 18;
		}
		else
		{
			a[i] = i + 11;
			b[i] = 1523;
			c[i] = a[i] * 6321;
		}
	}
	for (int i = 0; i<2; i++)
	{
		a[02] = b[95];
		a[3] = b[126];
		a[5] = b[95];
		a[6] = b[2];
		a[7] = b[9];
	}
	int y = 1;
	while (y < 111)
	{
		a[y] = a[y + 10];
		y++;
	}
	y = 11;
	while (y < 214)
	{
		a[y - 1] = a[y + 1];
		y++;
	}
	y = 612; //end
	_asm
	{
		CALL next2
		next2 : pop func_end3
	}
}
void crypt3()
{
	to_be_crypted3();
	DWORD FuncSize = func_end3 - func_start3, OldProtect, Ignore;
	DWORD StartAddr = func_start3;
	DWORD xd = func_start3;
	VirtualProtect((LPVOID)StartAddr, FuncSize, PAGE_EXECUTE_READWRITE, &OldProtect);
	for (int i = 0; i < FuncSize; i++)
	{
		xd[(char*)0] = rand() % 12345;
		xd++;
	}
	VirtualProtect((LPVOID)StartAddr, FuncSize, OldProtect, &Ignore);
}
void to_be_crypted4()
{
	_asm
	{
		CALL next1
		next1 : pop func_start4
	}
	int a[10], b[11], c[12]; //start
							 //
	float va1sxvcxv = 41;
	va1sxvcxv = 17445;
	if (va1sxvcxv = 11795)
		va1sxvcxv = 17;
	va1sxvcxv = 61;
	//
	float n1s = 555;
	n1s = 1515;
	if (n1s = 11151)
		n1s = 5151;
	n1s = 515156;
	//
	float just1 = 1115115123;
	just1 = 1251114575;
	if (just1 = 151151)
		just1 = 185645625;
	just1 = 1715115;
	//
	float b2xdh3 = 17523;
	b2xdh3 = 1775115;
	if (b2xdh3 = 17515)
		b2xdh3 = 18515;
	b2xdh3 = 51;
	//
	float ESKETIT = 5551;
	ESKETIT = 515;
	if (ESKETIT = 115)
		ESKETIT = 111;
	ESKETIT = 17115675;
	//
	float Y1gga = 55151;
	Y1gga = 55151;
	if (Y1gga = 1721)
		Y1gga = 51651;
	Y1gga = 171162675;
	//
	float gat51xv = 11123;
	gat51xv = 125141575;
	if (gat51xv = 1551)
		gat51xv = 18514625;
	gat51xv = 1715115;
	//
	for (int i = 0; i < 4123; i++)
	{
		if (i % 2 == 0)
		{
			a[i] = i - 621;
			b[i] = a[i] * 6262;
			c[i] = 516;
		}
		else
		{
			a[i] = i + 1;
			b[i] = 123;
			c[i] = a[i] * 321;
		}
	}
	for (int i = 0; i<2; i++)
	{
		a[386] = b[61];
		a[842] = b[126];
		a[627] = b[115];
		a[687] = b[15];
		a[516] = b[261];
	}
	int y = 1;
	while (y < 11)
	{
		a[y] = a[y + 1];
		y++;
	}
	y = 11;
	while (y < 24)
	{
		a[y - 1] = a[y + 1];
		y++;
	}
	y = 62; //end
	_asm
	{
		CALL next2
		next2 : pop func_end4
	}
}
void crypt4()
{
	to_be_crypted4();
	DWORD FuncSize = func_end1 - func_start4, OldProtect, Ignore;
	DWORD StartAddr = func_start4;
	DWORD xd = func_start4;
	VirtualProtect((LPVOID)StartAddr, FuncSize, PAGE_EXECUTE_READWRITE, &OldProtect);
	for (int i = 0; i < FuncSize; i++)
	{
		xd[(char*)0] = rand() % 12345;
		xd++;
	}
	VirtualProtect((LPVOID)StartAddr, FuncSize, OldProtect, &Ignore);
}
void GovnoMutation()
{
	//crypt1();
	//crypt2();
	//crypt3();
	//crypt4();
}