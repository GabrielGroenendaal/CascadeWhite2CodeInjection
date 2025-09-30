#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	LockAll();
	Sequence10();
	Sequence12();
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8020, 0);
	SetVarEqVal(0x8021, 0);
	SetVarFlagStatus(2411, 0x8025);
	SetVarFlagStatus(2402, 0x8026);
	SetVarFlagStatus(2400, 0x8022);
	StoreEA(0x8023);
	PlaySound(1371);
	SetWordPlayerName(0);
	EventGreyMessage(0, 2);

label32: ;
	StackPushVar(0x8020);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label0;
	PlaySound(1372);
	EventGreyMessage(1, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);
	SetVarFlagStatus(2401, 0x8028);
	Compare(0x8028, 1);
	if (0) goto label1;
	StackPushVar(0x8025);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label2;
	AddDialogueOption(2, 0xFFFF, 2);
	goto label1;

label2: ;
	AddDialogueOption(3, 0xFFFF, 3);

label1: ;
	SetWordPlayerName(0);
	AddDialogueOption(4, 0xFFFF, 4);
	StackPushVar(0x8026);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label3;
	AddDialogueOption(5, 0xFFFF, 5);
	SetVarFlagStatus(3063, 0x8028);
	Compare(0x8028, 1);
	if (1) goto label4;
	goto label5;

label5: ;
	AddDialogueOption(42, 0xFFFF, 42);
	goto label6;

label4: ;
	AddDialogueOption(59, 0xFFFF, 42);
	goto label6;

label6: ;
	Storec0xD3(0x8028);
	Compare(0x8028, 337);
	if (1) goto label7;
	Compare(0x8028, 345);
	if (1) goto label7;
	Compare(0x8028, 368);
	if (1) goto label7;
	Compare(0x8028, 448);
	if (1) goto label7;
	Compare(0x8028, 456);
	if (1) goto label7;
	Compare(0x8028, 107);
	if (1) goto label7;
	Compare(0x8028, 113);
	if (1) goto label7;
	Compare(0x8028, 198);
	if (1) goto label7;
	Compare(0x8028, 199);
	if (1) goto label7;
	Compare(0x8028, 205);
	if (1) goto label7;
	Compare(0x8028, 206);
	if (1) goto label7;
	Compare(0x8028, 439);
	if (1) goto label7;
	Compare(0x8028, 444);
	if (1) goto label7;
	Compare(0x8028, 445);
	if (1) goto label7;
	Compare(0x8028, 446);
	if (1) goto label7;
	Compare(0x8028, 96);
	if (1) goto label8;
	Compare(0x8028, 331);
	if (1) goto label8;
	goto label3;

label7: ;
	SetVarEqVal(0x8027, 2);
	AddDialogueOption(75, 0xFFFF, 75);
	goto label3;

label8: ;
	SetVarEqVal(0x8027, 5);
	AddDialogueOption(75, 0xFFFF, 75);
	goto label3;

label3: ;
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label9;
	AddDialogueOption(6, 0xFFFF, 6);

label9: ;
	AddDialogueOption(7, 0xFFFF, 7);
	AddDialogueOption(8, 0xFFFF, 8);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	ReturnAfterDelay(3);
	Compare(0x8024, 2);
	if (1) goto label10;
	goto label11;

label10: ;
	Sequence1();
	goto label12;

label11: ;
	Compare(0x8024, 3);
	if (1) goto label13;
	goto label14;

label13: ;
	Sequence1();
	goto label12;

label14: ;
	Compare(0x8024, 4);
	if (1) goto label15;
	goto label16;

label15: ;
	Sequence2();
	goto label12;

label16: ;
	Compare(0x8024, 42);
	if (1) goto label17;
	goto label18;

label17: ;
	Sequence8();
	goto label12;

label18: ;
	Compare(0x8024, 5);
	if (1) goto label19;
	goto label20;

label19: ;
	Sequence3();
	goto label12;

label20: ;
	Compare(0x8024, 6);
	if (1) goto label21;
	goto label22;

label21: ;
	Sequence4();
	goto label12;

label22: ;
	Compare(0x8024, 75);
	if (1) goto label23;
	goto label24;

label23: ;
	Sequence14();
	goto label12;

label24: ;
	Compare(0x8024, 7);
	if (1) goto label25;
	goto label26;

label25: ;
	Sequence5();
	goto label12;

label26: ;
	Compare(0x8024, 8);
	if (1) goto label27;
	goto label28;

label27: ;
	SetVarEqVal(0x8020, 1);
	goto label12;

label28: ;
	Compare(0x8024, 0xFFFE);
	if (1) goto label29;
	goto label30;

label29: ;
	SetVarEqVal(0x8020, 1);
	goto label12;

label30: ;
	Compare(0x8024, 0xFFFD);
	if (1) goto label31;
	goto label12;

label31: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	goto label12;

label12: ;
	goto label32;

label0: ;
	PlaySound(1373);
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8024, 0);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence1()
{
	SetVarEqVal(0x8027, 0);
	SetVarEqVal(0x8028, 0);
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x802B, 0);
	SetVarFlagStatus(2400, 0x802A);
	SetVarFlagStatus(249, 0x802B);
	PlaySound(1372);
	EventGreyMessage(14, 2);
	StackPushVar(0x802A);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label33;
	SetVarFlagStatus(246, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label33;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(12, 2);
	SetFlag(246);

label33: ;
	StackPushVar(0x802B);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label34;
	SetVarFlagStatus(247, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label34;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(13, 2);
	SetFlag(247);

label34: ;
	SetVarEqVal(0x8027, 0);

label64: ;
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label35;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8028);
	AddDialogueOption(15, 21, 15);
	AddDialogueOption(16, 22, 16);
	AddDialogueOption(17, 23, 17);
	AddDialogueOption(20, 26, 20);
	AddDialogueOption(18, 24, 18);
	AddDialogueOption(43, 44, 43);
	AddDialogueOption(45, 46, 45);
	AddDialogueOption(71, 72, 71);
	SetVarFlagStatus(124, 0x802B);
	Compare(0x802B, 1);
	if (0) goto label36;
	AddDialogueOption(47, 48, 47);

label36: ;
	AddDialogueOption(19, 25, 19);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x8028, 19);
	if (1) goto label37;
	goto label38;

label37: ;
	Return();
	goto label39;

label38: ;
	Compare(0x8028, 0xFFFE);
	if (1) goto label40;
	goto label41;

label40: ;
	Return();
	goto label39;

label41: ;
	Compare(0x8028, 0xFFFD);
	if (1) goto label42;
	goto label39;

label42: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label39;

label39: ;
	Compare(0x8028, 45);
	if (0) goto label43;
	goto label44;

label43: ;
	FadeIntoBlack2();
	WaitFade();
	Compare(0x8028, 15);
	if (1) goto label45;
	goto label44;

label45: ;
	c0x14F(0x8029, 0);
	goto label46;

label44: ;
	Compare(0x8028, 16);
	if (1) goto label47;
	goto label48;

label47: ;
	c0x14F(0x8029, 1);
	goto label46;

label48: ;
	Compare(0x8028, 17);
	if (1) goto label49;
	goto label50;

label49: ;
	c0x14F(0x8029, 2);
	goto label46;

label50: ;
	Compare(0x8028, 20);
	if (1) goto label51;
	goto label52;

label51: ;
	c0x14F(0x8029, 4);
	goto label46;

label52: ;
	Compare(0x8028, 18);
	if (1) goto label53;
	goto label54;

label53: ;
	c0x14F(0x8029, 3);
	goto label46;

label54: ;
	Compare(0x8028, 43);
	if (1) goto label55;
	goto label56;

label55: ;
	Sequence6();
	goto label57;

label56: ;
	Compare(0x8028, 45);
	if (1) goto label58;
	goto label59;

label58: ;
	Sequence7();
	goto label57;

label59: ;
	Compare(0x8028, 47);
	if (1) goto label60;
	goto label61;

label60: ;
	Sequence9();
	PlaySound(1372);
	goto label57;

label61: ;
	Compare(0x8028, 71);
	if (1) goto label62;
	goto label46;

label62: ;
	EventGreyMessage(73, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label57;
	Sequence13();
	goto label57;

label46: ;
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x8029);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label63;
	PlaySound(1372);
	goto label57;

label63: ;
	SetVarEqVal(0x8027, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label57: ;
	goto label64;

label35: ;
	SetVarEqVal(0x802B, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x8028, 0);
	SetVarEqVal(0x8027, 0);
	Return();
}

void Sequence2()
{
	SetVarEqVal(0x802C, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802E, 0);
	PlaySound(1372);
	SetWordPlayerName(0);
	EventGreyMessage(27, 2);
	CloseEventGreyMessage();
	SetVarEqVal(0x802C, 0);

label74: ;
	StackPushVar(0x802C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label65;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x802D);
	AddDialogueOption(28, 30, 28);
	AddDialogueOption(29, 31, 29);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x802D, 29);
	if (1) goto label66;
	goto label67;

label66: ;
	Return();
	goto label68;

label67: ;
	Compare(0x802D, 0xFFFE);
	if (1) goto label69;
	goto label70;

label69: ;
	Return();
	goto label68;

label70: ;
	Compare(0x802D, 0xFFFD);
	if (1) goto label71;
	goto label68;

label71: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label68;

label68: ;
	FadeIntoBlack2();
	WaitFade();
	c0x150(0x802E);
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x802E);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label72;
	PlaySound(1372);
	goto label73;

label72: ;
	SetVarEqVal(0x802C, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label73: ;
	goto label74;

label65: ;
	SetVarEqVal(0x802E, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802C, 0);
	Return();
}

void Sequence3()
{
	PlaySound(1372);
	EventGreyMessage(39, 2);
	CallGlobalScript(10382);
	Return();
}

void Sequence4()
{
	SetVarEqVal(0x802F, 0);
	SetVarEqVal(0x8030, 0);
	PlaySound(1372);
	EventGreyMessage(35, 2);
	CloseEventGreyMessage();
	StackPushVar(0x8023);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label84;
	c0x14D(1, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label75;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label75: ;
	goto label76;

label84: ;
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();

label76: ;
	SetVarEqVal(0x8030, 0);
	SetVarEqVal(0x802F, 0);
	Return();
}

void Sequence5()
{
	PlaySound(1372);
	EventGreyMessage(40, 2);
	CloseEventGreyMessage();
	c0x231(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label77;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label77: ;
	Return();
}

void Sequence6()
{
	HealPokemon();
	PlayFanfare(1300);
	WaitFanfare();
	PC_131();
	FadeFromBlack2();
	WaitFade();
	EventGreyMessage(50, 2);
	CloseEventGreyMessage();
	PlaySound(1372);
	Return();
}

void Sequence7()
{
	EventGreyMessage(51, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);
	AddDialogueOption(53, 0xFFFF, 53);
	AddDialogueOption(54, 0xFFFF, 54);
	AddDialogueOption(55, 0xFFFF, 55);
	AddDialogueOption(56, 0xFFFF, 56);
	AddDialogueOption(57, 0xFFFF, 57);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x8024, 0xFFFE);
	if (1) goto label78;
	Compare(0x8024, 57);
	if (1) goto label78;
	Compare(0x8024, 53);
	if (1) goto label79;
	Compare(0x8024, 54);
	if (1) goto label80;
	Compare(0x8024, 55);
	if (1) goto label81;
	Compare(0x8024, 56);
	if (1) goto label82;
	goto label78;

label79: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 5);
	PlaySound(1372);
	goto label78;

label80: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 1);
	PlaySound(1372);
	goto label78;

label81: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 2);
	PlaySound(1372);
	goto label78;

label82: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 4);
	PlaySound(1372);
	goto label78;

label78: ;
	Return();
}

void Sequence8()
{
	SetVarFlagStatus(3063, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label85;
	goto label83;

label85: ;
	EventGreyMessage(60, 2);
	CloseEventGreyMessage();
	ClearFlag(3063);
	Return();

label83: ;
	EventGreyMessage(49, 2);
	CloseEventGreyMessage();
	SetFlag(3063);
	Return();
}

void Sequence9()
{
	EventGreyMessage(66, 2);
	CloseEventGreyMessage();
	OpenChoosePokemonMenu(0, 0x8028, 0x8024, 0);
	StackPushVar(0x8028);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label86;
	Return();

label86: ;
	GetPartyIsEgg(0x8028, 0x8024);
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label87;
	EventGreyMessage(64, 2);
	CloseEventGreyMessage();
	Return();

label87: ;
	c0x1D5(0x8028, 0x8024);
	StackPushVar(0x8028);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label88;
	EventGreyMessage(65, 2);
	CloseEventGreyMessage();
	Return();

label88: ;
	SetWordPartyNickname(0, 0x8024);
	EventGreyMessage(67, 2);
	CloseEventGreyMessage();
	c0x1D6(0x802B, 0x8024);
	Compare(0x802B, 0);
	if (1) goto label89;
	SetVarEqVal(0x8024, 0);
	WaitMoment();
	Return();

label89: ;
	WaitMoment();
	EventGreyMessage(69, 2);
	CloseEventGreyMessage();
	Return();
}

void Sequence10()
{
	SetVarEqVal(0x8027, 50);
	SetVarEqVal(0x8028, 499);
	Sequence11();
	SetVarEqVal(0x8028, 249);
	Sequence11();
	SetVarEqVal(0x8028, 124);
	Sequence11();
	SetVarEqVal(0x8028, 62);
	Sequence11();
	SetVarEqVal(0x8028, 31);
	Sequence11();
	SetVarEqVal(0x8028, 15);
	Sequence11();
	SetVarEqVal(0x8028, 7);
	Sequence11();
	SetVarEqVal(0x8028, 3);
	Sequence11();
	SetVarEqVal(0x8028, 1);
	Sequence11();
	Return();
}

void Sequence11()
{

label91: ;
	GiveItem(0x8027, 0x8028, 0x8029);
	Compare(0x8029, 1);
	if (1) goto label91;
	Return();
}

void Sequence12()
{
	Storec0xD3(0x8027);
	Compare(0x8027, 137);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 138);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 139);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 140);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 141);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 142);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 143);
	if (1) goto label90;
	Storec0xD3(0x8027);
	Compare(0x8027, 144);
	if (1) goto label90;
	Return();

label90: ;
	EventGreyMessage(68, 2);
	CloseEventGreyMessage();
	UnlockAll();
	End();
}

void Sequence13()
{
	Return();
}

void Sequence14()
{
	SetVarFlagStatus(3062, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label92;
	goto label93;

label92: ;
	ClearFlag(3062);
	SetWeather(0, 0);
	Return();

label93: ;
	SetFlag(3062);
	SetWeather(2, 2);
	Return();
}

void Sequence15()
{
	SetVarFlagStatus(3062, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label95;
	goto label94;

label95: ;
	SetWeather(0, 0);
	ClearFlag(3062);
	Return();

label94: ;
	SetFlag(3062);
	SetWeather(5, 5);
	Return();
}
