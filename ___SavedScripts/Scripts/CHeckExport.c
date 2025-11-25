#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"
#include "ScriptHeaders/CommandOverlay65.h"

void Sequence0()
{
	LockAll();
	Sequence12();
	Sequence16();
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
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label0;
	EventGreyMessage(0, 2);
	goto label1;

label0: ;
	EventGreyMessage(84, 2);

label1: ;
	StackPushVar(0x8020);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label2;
	PlaySound(1372);
	EventGreyMessage(1, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);
	Sequence16();
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label3;
	SetVarFlagStatus(2401, 0x8028);
	Compare(0x8028, 1);
	if (0) goto label4;
	StackPushVar(0x8025);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label5;
	AddDialogueOption(2, 0xFFFF, 2);
	goto label4;

label3: ;
	AddDialogueOption(85, 0xFFFF, 2);
	goto label4;

label5: ;
	AddDialogueOption(3, 0xFFFF, 3);

label4: ;
	Sequence16();
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(2);
	if (255) goto label6;
	SetWordPlayerName(0);
	AddDialogueOption(4, 0xFFFF, 4);
	StackPushVar(0x8026);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label7;
	AddDialogueOption(5, 0xFFFF, 5);

label6: ;
	SetVarFlagStatus(3063, 0x8028);
	Compare(0x8028, 1);
	if (1) goto label8;
	goto label9;

label9: ;
	AddDialogueOption(42, 0xFFFF, 42);
	goto label7;

label8: ;
	AddDialogueOption(59, 0xFFFF, 42);
	goto label7;
	Storec0xD3(0x8028);
	Compare(0x8028, 337);
	if (1) goto label10;
	Compare(0x8028, 345);
	if (1) goto label10;
	Compare(0x8028, 368);
	if (1) goto label10;
	Compare(0x8028, 448);
	if (1) goto label10;
	Compare(0x8028, 456);
	if (1) goto label10;
	Compare(0x8028, 107);
	if (1) goto label10;
	Compare(0x8028, 113);
	if (1) goto label10;
	Compare(0x8028, 198);
	if (1) goto label10;
	Compare(0x8028, 199);
	if (1) goto label10;
	Compare(0x8028, 205);
	if (1) goto label10;
	Compare(0x8028, 206);
	if (1) goto label10;
	Compare(0x8028, 439);
	if (1) goto label10;
	Compare(0x8028, 444);
	if (1) goto label10;
	Compare(0x8028, 445);
	if (1) goto label10;
	Compare(0x8028, 446);
	if (1) goto label10;
	Compare(0x8028, 96);
	if (1) goto label11;
	Compare(0x8028, 331);
	if (1) goto label11;
	goto label7;

label10: ;
	SetVarEqVal(0x8027, 2);
	goto label7;

label11: ;
	SetVarEqVal(0x8027, 5);
	goto label7;

label7: ;
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label12;
	AddDialogueOption(6, 0xFFFF, 6);

label12: ;
	SetVarEqVar(0x8022, 0x4177);
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(2);
	if (255) goto label13;
	AddDialogueOption(86, 0xFFFF, 86);

label13: ;
	AddDialogueOption(87, 0xFFFF, 87);
	AddDialogueOption(7, 0xFFFF, 7);
	AddDialogueOption(8, 0xFFFF, 8);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	ReturnAfterDelay(3);
	Compare(0x8024, 2);
	if (1) goto label14;
	goto label15;

label14: ;
	GetPartyCount(0x8022, 0);
	Compare(0x8022, 0);
	if (1) goto label16;
	Sequence1();
	goto label17;

label15: ;
	Compare(0x8024, 3);
	if (1) goto label18;
	goto label19;

label18: ;
	Sequence1();
	goto label17;

label19: ;
	Compare(0x8024, 4);
	if (1) goto label20;
	goto label21;

label20: ;
	Sequence2();
	goto label17;

label21: ;
	Compare(0x8024, 42);
	if (1) goto label22;
	goto label23;

label22: ;
	Sequence8();
	goto label17;

label23: ;
	Compare(0x8024, 5);
	if (1) goto label24;
	goto label25;

label24: ;
	Sequence3();
	goto label17;

label25: ;
	Compare(0x8024, 6);
	if (1) goto label26;
	goto label27;

label26: ;
	Sequence4();
	goto label17;

label27: ;
	Compare(0x8024, 75);
	if (1) goto label28;
	goto label29;

label28: ;
	Sequence14();
	goto label17;

label29: ;
	Compare(0x8024, 7);
	if (1) goto label30;
	goto label31;

label30: ;
	Sequence5();
	goto label17;

label31: ;
	Compare(0x8024, 8);
	if (1) goto label32;
	goto label33;

label32: ;
	SetVarEqVal(0x8020, 1);
	goto label17;

label33: ;
	Compare(0x8024, 0xFFFE);
	if (1) goto label34;
	goto label35;

label34: ;
	SetVarEqVal(0x8020, 1);
	goto label17;

label35: ;
	Compare(0x8024, 0xFFFD);
	if (1) goto label36;
	goto label37;

label36: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	goto label17;

label37: ;
	Compare(0x8024, 86);
	if (1) goto label38;
	goto label39;

label38: ;
	Sequence17();
	goto label17;

label39: ;
	Compare(0x8024, 87);
	if (1) goto label40;
	goto label17;

label40: ;
	Sequence18();
	goto label17;

label17: ;
	goto label1;

label16: ;
	EventGreyMessage(170, 2);
	goto label1;

label2: ;
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
	if (255) goto label41;
	SetVarFlagStatus(246, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label41;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(12, 2);
	SetFlag(246);

label41: ;
	StackPushVar(0x802B);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label42;
	SetVarFlagStatus(247, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label42;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(13, 2);
	SetFlag(247);

label42: ;
	SetVarEqVal(0x8027, 0);

label74: ;
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label43;
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
	AddDialogueOption(171, 172, 171);
	SetVarFlagStatus(124, 0x802B);
	Compare(0x802B, 1);
	if (0) goto label44;
	AddDialogueOption(47, 48, 47);

label44: ;
	AddDialogueOption(19, 25, 19);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x8028, 19);
	if (1) goto label45;
	goto label46;

label45: ;
	Return();
	goto label47;

label46: ;
	Compare(0x8028, 0xFFFE);
	if (1) goto label48;
	goto label49;

label48: ;
	Return();
	goto label47;

label49: ;
	Compare(0x8028, 0xFFFD);
	if (1) goto label50;
	goto label47;

label50: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label47;

label47: ;
	Compare(0x8028, 45);
	if (0) goto label51;
	goto label52;

label51: ;
	FadeIntoBlack2();
	WaitFade();
	Compare(0x8028, 15);
	if (1) goto label53;
	goto label52;

label53: ;
	c0x14F(0x8029, 0);
	goto label54;

label52: ;
	Compare(0x8028, 16);
	if (1) goto label55;
	goto label56;

label55: ;
	c0x14F(0x8029, 1);
	goto label54;

label56: ;
	Compare(0x8028, 17);
	if (1) goto label57;
	goto label58;

label57: ;
	c0x14F(0x8029, 2);
	goto label54;

label58: ;
	Compare(0x8028, 20);
	if (1) goto label59;
	goto label60;

label59: ;
	c0x14F(0x8029, 4);
	goto label54;

label60: ;
	Compare(0x8028, 18);
	if (1) goto label61;
	goto label62;

label61: ;
	c0x14F(0x8029, 3);
	goto label54;

label62: ;
	Compare(0x8028, 43);
	if (1) goto label63;
	goto label64;

label63: ;
	Sequence6();
	goto label65;

label64: ;
	Compare(0x8028, 45);
	if (1) goto label66;
	goto label67;

label66: ;
	Sequence7();
	goto label65;

label67: ;
	Compare(0x8028, 47);
	if (1) goto label68;
	goto label69;

label68: ;
	Sequence9();
	PlaySound(1372);
	goto label65;

label69: ;
	Compare(0x8028, 71);
	if (1) goto label70;
	goto label71;

label70: ;
	EventGreyMessage(73, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label65;
	Sequence20();
	goto label65;

label71: ;
	Compare(0x8028, 171);
	if (1) goto label72;
	goto label54;

label72: ;
	EventGreyMessage(173, 2);
	YesNoBox(0x8000);
	Compare(0x8000, 1);
	if (1) goto label65;
	Sequence19();
	goto label65;

label54: ;
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x8029);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label73;
	PlaySound(1372);
	goto label65;

label73: ;
	SetVarEqVal(0x8027, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label65: ;
	goto label74;

label43: ;
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

label84: ;
	StackPushVar(0x802C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label75;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x802D);
	AddDialogueOption(28, 30, 28);
	AddDialogueOption(29, 31, 29);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x802D, 29);
	if (1) goto label76;
	goto label77;

label76: ;
	Return();
	goto label78;

label77: ;
	Compare(0x802D, 0xFFFE);
	if (1) goto label79;
	goto label80;

label79: ;
	Return();
	goto label78;

label80: ;
	Compare(0x802D, 0xFFFD);
	if (1) goto label81;
	goto label78;

label81: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label78;

label78: ;
	FadeIntoBlack2();
	WaitFade();
	c0x150(0x802E);
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x802E);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label82;
	PlaySound(1372);
	goto label83;

label82: ;
	SetVarEqVal(0x802C, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label83: ;
	goto label84;

label75: ;
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
	if (255) goto label94;
	c0x14D(1, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label85;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label85: ;
	goto label86;

label94: ;
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();

label86: ;
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
	if (255) goto label87;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label87: ;
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
	if (1) goto label88;
	Compare(0x8024, 57);
	if (1) goto label88;
	Compare(0x8024, 53);
	if (1) goto label89;
	Compare(0x8024, 54);
	if (1) goto label90;
	Compare(0x8024, 55);
	if (1) goto label91;
	Compare(0x8024, 56);
	if (1) goto label92;
	goto label88;

label89: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 5);
	PlaySound(1372);
	goto label88;

label90: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 1);
	PlaySound(1372);
	goto label88;

label91: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 2);
	PlaySound(1372);
	goto label88;

label92: ;
	OpenChoosePokemonMenu(0, 0x8000, 0x8004, 0);
	SetPokemonIV(0x8004, 157, 4);
	PlaySound(1372);
	goto label88;

label88: ;
	Return();
}

void Sequence8()
{
	SetVarFlagStatus(3063, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label95;
	goto label93;

label95: ;
	EventGreyMessage(60, 2);
	CloseEventGreyMessage();
	ClearFlag(3063);
	Return();

label93: ;
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
	if (255) goto label96;
	Return();

label96: ;
	GetPartyIsEgg(0x8028, 0x8024);
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label97;
	EventGreyMessage(64, 2);
	CloseEventGreyMessage();
	Return();

label97: ;
	c0x1D5(0x8028, 0x8024);
	StackPushVar(0x8028);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label98;
	EventGreyMessage(65, 2);
	CloseEventGreyMessage();
	Return();

label98: ;
	SetWordPartyNickname(0, 0x8024);
	EventGreyMessage(67, 2);
	CloseEventGreyMessage();
	c0x1D6(0x802B, 0x8024);
	Compare(0x802B, 0);
	if (1) goto label99;
	SetVarEqVal(0x8024, 0);
	WaitMoment();
	Return();

label99: ;
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

label103: ;
	GiveItem(0x8027, 0x8028, 0x8029);
	Compare(0x8029, 1);
	if (1) goto label103;
	Return();
}

void Sequence12()
{
	Storec0xD3(0x8027);
	Compare(0x8027, 137);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 138);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 139);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 140);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 141);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 142);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 143);
	if (1) goto label100;
	Storec0xD3(0x8027);
	Compare(0x8027, 144);
	if (1) goto label100;
	Storec0xD3(0x8031);
	Compare(0x8031, 195);
	if (1) goto label101;
	Storec0xD3(0x8031);
	Compare(0x8031, 196);
	if (1) goto label101;
	Storec0xD3(0x8031);
	Compare(0x8031, 197);
	if (1) goto label101;
	Storec0xD3(0x8031);
	Compare(0x8031, 253);
	if (1) goto label101;
	Storec0xD3(0x8031);
	Compare(0x8031, 490);
	if (1) goto label101;

label102: ;
	Return();

label101: ;
	SetVarFlagStatus(522, 0x8024);
	Compare(0x8024, 1);
	if (0) goto label102;
	EventGreyMessage(68, 2);
	CloseEventGreyMessage();
	UnlockAll();
	End();

label100: ;
	EventGreyMessage(68, 2);
	CloseEventGreyMessage();
	UnlockAll();
	End();
}

void Sequence13()
{
	EventGreyMessage(69, 2);
	Return();
}

void Sequence14()
{
	SetVarFlagStatus(3062, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label104;
	goto label105;

label104: ;
	ClearFlag(3062);
	SetWeather(0, 0);
	Return();

label105: ;
	SetFlag(3062);
	SetWeather(2, 2);
	Return();
}

void Sequence15()
{
	SetVarFlagStatus(3062, 0x8024);
	Compare(0x8024, 1);
	if (1) goto label209;
	goto label106;

label209: ;
	SetWeather(0, 0);
	ClearFlag(3062);
	Return();

label106: ;
	SetFlag(3062);
	SetWeather(5, 5);
	Return();
}

void Sequence16()
{
	Storec0xD3(0x8027);
	Compare(0x8027, 435);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 454);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 443);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 41);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 65);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 99);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 109);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 460);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 413);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 407);
	if (1) goto label107;
	Storec0xD3(0x8027);
	Compare(0x8027, 122);
	if (1) goto label107;
	SetVarEqVal(0x8027, 0);
	Return();

label107: ;
	Storec0xD3(0x8027);
	Return();
}

void Sequence17()
{
	PlaySound(1351);
	SetVarEqVal(0x8034, 0);

label119: ;
	StackPushVar(0x8034);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label130;
	EventGreyMessage(102, 2);
	WaitForButton();
	SetupDialogueSelection(31, 1, 0, 1, 0x8029);
	AddDialogueOption(88, 0xFFFF, 427);
	Compare(0x40A5, 0);
	if (1) goto label108;
	AddDialogueOption(89, 0xFFFF, 439);

label108: ;
	Compare(0x40AC, 0);
	if (1) goto label109;
	AddDialogueOption(90, 0xFFFF, 448);

label109: ;
	SetVarFlagStatus(748, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label110;
	AddDialogueOption(91, 0xFFFF, 28);

label110: ;
	Compare(0x415D, 0);
	if (1) goto label111;
	AddDialogueOption(92, 0xFFFF, 551);

label111: ;
	Compare(0x415D, 0);
	if (1) goto label112;
	AddDialogueOption(93, 0xFFFF, 62);

label112: ;
	Compare(0x40C3, 0);
	if (1) goto label113;
	AddDialogueOption(94, 0xFFFF, 96);

label113: ;
	Compare(0x40C6, 0);
	if (1) goto label114;
	AddDialogueOption(95, 0xFFFF, 191);

label114: ;
	SetVarFlagStatus(521, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label115;
	AddDialogueOption(96, 0xFFFF, 107);

label115: ;
	SetVarFlagStatus(777, 0x8030);
	Compare(0x8030, 0);
	if (1) goto label116;
	AddDialogueOption(97, 0xFFFF, 458);

label116: ;
	AddDialogueOption(112, 0xFFFF, 112);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	ReturnAfterDelay(3);
	Compare(0x8029, 0);
	if (1) goto label117;
	Compare(0x8029, 0xFFFE);
	if (1) goto label117;
	Compare(0x8029, 112);
	if (1) goto label117;
	EventGreyMessage(101, 2);
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label118;
	goto label119;

label117: ;
	SetVarEqVal(0x8034, 1);
	goto label119;

label118: ;
	CloseAllMessageBoxes();
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8034, 1);
	Compare(0x8029, 427);
	if (1) goto label120;
	Compare(0x8029, 439);
	if (1) goto label121;
	Compare(0x8029, 448);
	if (1) goto label122;
	Compare(0x8029, 28);
	if (1) goto label123;
	Compare(0x8029, 551);
	if (1) goto label124;
	Compare(0x8029, 62);
	if (1) goto label125;
	Compare(0x8029, 96);
	if (1) goto label126;
	Compare(0x8029, 191);
	if (1) goto label127;
	Compare(0x8029, 107);
	if (1) goto label128;
	Compare(0x8029, 458);
	if (1) goto label129;
	goto label130;

label120: ;
	c0x28A(427, 1);
	goto label119;

label121: ;
	c0x28A(439, 1);
	goto label119;

label122: ;
	c0x28A(448, 1);
	goto label119;

label123: ;
	RailWarp(28, 3, 8, 8, 1);
	goto label119;

label124: ;
	c0x28A(551, 1);
	goto label119;

label125: ;
	c0x28A(62, 1);
	goto label119;

label126: ;
	c0x28A(96, 1);
	goto label119;

label127: ;
	c0x28A(191, 1);
	goto label119;

label128: ;
	c0x28A(107, 1);
	goto label119;

label129: ;
	c0x28A(458, 1);
	goto label119;

label130: ;
	Return();
}

void Sequence18()
{
	PlaySound(1351);
	EventGreyMessage(103, 2);
	WaitForButton();

label135: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8004);
	AddDialogueOption(104, 0xFFFF, 0);
	AddDialogueOption(105, 0xFFFF, 1);
	AddDialogueOption(106, 0xFFFF, 6);
	AddDialogueOption(107, 0xFFFF, 2);
	AddDialogueOption(108, 0xFFFF, 3);
	AddDialogueOption(109, 0xFFFF, 4);
	AddDialogueOption(110, 0xFFFF, 5);
	AddDialogueOption(111, 0xFFFF, 9);
	AddDialogueOption(400, 0xFFFF, 10);
	AddDialogueOption(112, 0xFFFF, 7);
	AddDialogueOption(113, 0xFFFF, 8);
	ShowDialogueSelection2();
	Compare(0x8004, 0);
	if (5) goto label131;
	Compare(0x401F, 0);
	if (5) goto label132;
	EventGreyMessage(114, 2);
	goto label133;

label132: ;
	EventGreyMessage(115, 2);

label133: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label134;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label134: ;
	Compare(0x401F, 0);
	if (5) goto label136;
	EventGreyMessage(117, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 1);
	goto label137;

label136: ;
	EventGreyMessage(118, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

label137: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label131: ;
	Compare(0x8004, 1);
	if (5) goto label138;
	Compare(0x4031, 0);
	if (5) goto label139;
	EventGreyMessage(120, 2);
	goto label140;

label139: ;
	Compare(0x4031, 1);
	if (5) goto label141;
	EventGreyMessage(124, 2);
	goto label140;

label141: ;
	EventGreyMessage(121, 2);

label140: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(125, 0xFFFF, 0);
	AddDialogueOption(126, 0xFFFF, 1);
	AddDialogueOption(127, 0xFFFF, 2);
	AddDialogueOption(112, 0xFFFF, 3);
	ShowDialogueSelection2();
	Compare(0x8006, 0);
	if (5) goto label142;
	EventGreyMessage(123, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label142: ;
	Compare(0x8006, 1);
	if (5) goto label143;
	EventGreyMessage(128, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 1);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label143: ;
	Compare(0x8006, 2);
	if (5) goto label144;
	EventGreyMessage(122, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 2);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label144: ;
	Compare(0x8006, 3);
	if (5) goto label145;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label145: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label138: ;
	Compare(0x8004, 2);
	if (5) goto label146;
	Compare(0x4032, 0);
	if (5) goto label147;
	EventGreyMessage(129, 2);
	goto label148;

label147: ;
	Compare(0x4032, 1);
	if (5) goto label149;
	EventGreyMessage(130, 2);
	goto label148;

label149: ;
	Compare(0x4032, 2);
	if (5) goto label150;
	EventGreyMessage(131, 2);
	goto label148;

label150: ;
	EventGreyMessage(132, 2);

label148: ;
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	AddDialogueOption(133, 0xFFFF, 0);
	AddDialogueOption(134, 0xFFFF, 1);
	AddDialogueOption(135, 0xFFFF, 2);
	AddDialogueOption(136, 0xFFFF, 3);
	AddDialogueOption(112, 0xFFFF, 4);
	ShowDialogueSelection2();
	Compare(0x8006, 0);
	if (5) goto label151;
	EventGreyMessage(137, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label151: ;
	Compare(0x8006, 1);
	if (5) goto label152;
	EventGreyMessage(138, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 1);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label152: ;
	Compare(0x8006, 2);
	if (5) goto label153;
	EventGreyMessage(139, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 2);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label153: ;
	Compare(0x8006, 3);
	if (5) goto label154;
	EventGreyMessage(140, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 4);
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label154: ;
	Compare(0x8006, 4);
	if (5) goto label155;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label155: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label146: ;
	Compare(0x8004, 3);
	if (5) goto label156;
	Compare(0x4033, 0);
	if (5) goto label157;
	EventGreyMessage(142, 2);
	goto label158;

label157: ;
	EventGreyMessage(143, 2);

label158: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label159;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label159: ;
	Compare(0x4033, 0);
	if (5) goto label160;
	EventGreyMessage(144, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 1);
	goto label161;

label160: ;
	EventGreyMessage(145, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 0);

label161: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label156: ;
	Compare(0x8004, 4);
	if (5) goto label162;
	Compare(0x4034, 0);
	if (5) goto label163;
	EventGreyMessage(146, 2);
	goto label164;

label163: ;
	EventGreyMessage(147, 2);

label164: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label165;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label165: ;
	Compare(0x4034, 0);
	if (5) goto label166;
	EventGreyMessage(149, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 1);
	goto label167;

label166: ;
	EventGreyMessage(148, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 0);

label167: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label162: ;
	Compare(0x8004, 5);
	if (5) goto label168;
	Compare(0x4035, 0);
	if (5) goto label169;
	EventGreyMessage(150, 2);
	goto label170;

label169: ;
	EventGreyMessage(151, 2);

label170: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label171;
	EventGreyMessage(61, 2);
	WaitForButton();
	goto label135;

label171: ;
	Compare(0x4035, 0);
	if (5) goto label172;
	EventGreyMessage(153, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 1);
	goto label173;

label172: ;
	EventGreyMessage(152, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 0);

label173: ;
	EventGreyMessage(19, 2);
	WaitForButton();
	goto label135;

label168: ;
	Compare(0x8004, 6);
	if (5) goto label174;
	SetVarFlagStatus(525, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label175;
	SetVarEqVal(0x8000, 0);
	goto label175;

label175: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label176;
	EventGreyMessage(154, 2);
	goto label177;

label176: ;
	SetVarFlagStatus(524, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(525, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label178;
	SetVarEqVal(0x8000, 0);
	goto label178;

label178: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label179;
	EventGreyMessage(155, 2);
	goto label177;

label179: ;
	EventGreyMessage(158, 2);
	WaitForButton();
	goto label135;

label177: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label180;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label180: ;
	SetVarFlagStatus(525, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label181;
	SetVarEqVal(0x8000, 0);
	goto label181;

label181: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label182;
	EventGreyMessage(156, 2);
	WaitForButton();
	ClearFlag(525);
	SetFlag(524);
	goto label183;

label182: ;
	SetVarFlagStatus(524, 0x8000);
	StackPushVar(0x8000);
	SetVarFlagStatus(525, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label184;
	SetVarEqVal(0x8000, 0);
	goto label184;

label184: ;
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 1);
	Compare(0x8000, 0);
	if (1) goto label185;
	EventGreyMessage(157, 2);
	WaitForButton();
	ClearFlag(524);
	SetFlag(525);
	goto label183;

label185: ;
	EventGreyMessage(158, 2);
	WaitForButton();
	goto label135;

label183: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label174: ;
	Compare(0x8004, 9);
	if (5) goto label186;
	Compare(0x4036, 0);
	if (5) goto label187;
	EventGreyMessage(160, 2);
	goto label188;

label187: ;
	EventGreyMessage(161, 2);

label188: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label189;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label189: ;
	Compare(0x4036, 0);
	if (5) goto label190;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(0x4036, 1);
	goto label191;

label190: ;
	EventGreyMessage(163, 2);
	WaitForButton();
	SetVarEqVar2(0x4036, 0);

label191: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label186: ;
	Compare(0x8004, 9);
	if (5) goto label192;
	Compare(0x4037, 0);
	if (5) goto label193;
	EventGreyMessage(160, 2);
	goto label194;

label193: ;
	EventGreyMessage(161, 2);

label194: ;
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label195;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label195: ;
	Compare(0x4036, 0);
	if (5) goto label196;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(0x4036, 1);
	goto label197;

label196: ;
	EventGreyMessage(163, 2);
	WaitForButton();
	SetVarEqVar2(0x4036, 0);

label197: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label192: ;
	Compare(0x8004, 8);
	if (5) goto label198;
	EventGreyMessage(159, 2);
	WaitForButton();
	YesNoBox(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (5) goto label199;
	EventGreyMessage(116, 2);
	WaitForButton();
	goto label135;

label199: ;
	Compare(0x401F, 0);
	if (1) goto label200;
	EventGreyMessage(118, 2);
	WaitForButton();
	SetVarEqVar2(0x401F, 0);

label200: ;
	Compare(0x4031, 0);
	if (1) goto label201;
	EventGreyMessage(123, 2);
	WaitForButton();
	SetVarEqVar2(0x4031, 0);

label201: ;
	Compare(0x4032, 0);
	if (1) goto label202;
	EventGreyMessage(137, 2);
	WaitForButton();
	SetVarEqVar2(0x4032, 0);

label202: ;
	Compare(0x4033, 0);
	if (1) goto label203;
	EventGreyMessage(145, 2);
	WaitForButton();
	SetVarEqVar2(0x4033, 0);

label203: ;
	Compare(0x4034, 0);
	if (1) goto label204;
	EventGreyMessage(148, 2);
	WaitForButton();
	SetVarEqVar2(0x4034, 0);

label204: ;
	Compare(0x4035, 0);
	if (1) goto label205;
	EventGreyMessage(152, 2);
	WaitForButton();
	SetVarEqVar2(0x4035, 0);

label205: ;
	SetVarFlagStatus(524, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label206;
	EventGreyMessage(157, 2);
	WaitForButton();
	ClearFlag(524);
	SetFlag(525);

label206: ;
	Compare(0x4036, 0);
	if (1) goto label207;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(0x4036, 0);

label207: ;
	Compare(0x4037, 0);
	if (1) goto label208;
	EventGreyMessage(162, 2);
	WaitForButton();
	SetVarEqVar2(0x4037, 0);

label208: ;
	EventGreyMessage(119, 2);
	WaitForButton();
	goto label135;

label198: ;
	WaitMoment();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence19()
{
	Error
	EventGreyMessage(69, 2);
	Return();
}

void Sequence20()
{
	Error
	EventGreyMessage(69, 2);
	Return();
}
