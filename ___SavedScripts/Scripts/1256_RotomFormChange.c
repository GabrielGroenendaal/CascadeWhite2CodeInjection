#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

// 611 is the text file 

void Sequence0()
{
	LockAll();
	SetVarEqVal(0x8028, 0);
	PlaySound(1351);
	c0x114(479, 0x8028);
	StackPushVar(0x8028);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label0;
	SetVarEqVal(0x8022, 0);
	Routine0();
	goto label1;

label0: ;
	EventGreyMessage(1, 2);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label2;
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label3;
	c0x118(479, 0x8010, 0x8021);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label4;
	Routine1();

label4: ;
	goto label5;

label3: ;
	EventGreyMessage(3, 2);
	CloseEventGreyMessage();
	OpenChoosePokemonMenu(0, 0x8010, 0x8021, 0);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label6;
	Routine2();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label7;
	Routine1();

label7: ;
	goto label5;

label6: ;
	SetVarEqVal(0x8022, 2);
	Routine0();

label5: ;
	goto label1;

label2: ;
	SetVarEqVal(0x8022, 2);
	Routine0();

label1: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
{
	EventGreyMessage(0x8022, 2);
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine1()
{
	SetVarEqVal(0x802B, 0);
	SetVarEqVal(0x802C, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802C, 0);
	GetPartyForm(0x8020, 0x8021);
	SetWordPartyNickname(0, 0x8021);

label15: ;
	StackPushVar(0x802C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label8;
	EventGreyMessage(6, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x802D);
	AddDialogueOption(7, 0xFFFF, 1);
	AddDialogueOption(8, 0xFFFF, 2);
	AddDialogueOption(10, 0xFFFF, 3);
	AddDialogueOption(9, 0xFFFF, 4);
	AddDialogueOption(11, 0xFFFF, 5);
	AddDialogueOption(12, 0xFFFF, 0);
	AddDialogueOption(13, 0xFFFF, 6);
	ShowDialogueSelection();
	StackPushVar(0x802D);
	StackPushConst(6);
	StackCompare(1);
	if (255) goto label9;
	SetVarEqVal(0x8022, 25);
	Routine0();
	Return();
	goto label10;

label9: ;
	StackPushVar(0x802D);
	StackPushConst(0xFFFE);
	StackCompare(1);
	if (255) goto label10;
	SetVarEqVal(0x8022, 25);
	Routine0();
	Return();

label10: ;
	SetVarEqVar(0x802B, 0x802D);
	SetVarEqVar(0x8026, 0x802B);
	Routine3();
	SetVarEqVar(0x8024, 0x8027);
	StackPushVar(0x8020);
	StackPushVar(0x802B);
	StackCompare(1);
	if (255) goto label11;
	StackPushVar(0x8020);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label12;
	SetWordPartyNickname(0, 0x8021);
	EventGreyMessage(24, 2);
	goto label13;

label12: ;
	SetWordPartyNickname(0, 0x8021);
	EventGreyMessage(22, 2);

label13: ;
	goto label14;

label11: ;
	SetVarEqVal(0x802C, 1);

label14: ;
	goto label15;

label8: ;
	StackPushVar(0x802B);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label16;
	Routine4();
	SetWordPartyNickname(0, 0x8021);
	SetVarEqVal(0x8022, 23);
	Routine0();
	SetVarEqVal(0x8010, 1);
	goto label17;

label16: ;
	SetWordPartyNickname(0, 0x8021);
	Cry(479, 0);
	EventGreyMessage(14, 2);
	WaitCry();
	WaitMessage();
	SetVarEqVal(0x8023, 0);
	Routine5();

label17: ;
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label18;
	c0x11C(0x8021, 0x8023, 0x802B);
	goto label19;

label18: ;
	SetWordPartyNickname(0, 0x8021);
	SetWordMove(1, 0x8024);
	SetVarEqVal(0x8022, 17);
	Routine0();

label19: ;
	Return();
}

void Routine2()
{
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x8010, 0);
	GetPartyIsEgg(0x802A, 0x8021);
	StackPushVar(0x802A);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label20;
	SetVarEqVal(0x8022, 5);
	Routine0();
	SetVarEqVal(0x8010, 0);
	goto label21;

label20: ;
	GetPartySpecies(0x8029, 0x8021);
	StackPushVar(0x8029);
	StackPushConst(479);
	StackCompare(1);
	if (255) goto label22;
	SetVarEqVal(0x8010, 1);
	goto label21;

label22: ;
	SetVarEqVal(0x8022, 4);
	Routine0();
	SetVarEqVal(0x8010, 0);

label21: ;
	Return();
}

void Routine3()
{
	Compare(0x8026, 0);
	if (1) goto label23;
	goto label24;

label23: ;
	SetVarEqVal(0x8027, 84);
	goto label25;

label24: ;
	Compare(0x8026, 1);
	if (1) goto label26;
	goto label27;

label26: ;
	SetVarEqVal(0x8027, 315);
	goto label25;

label27: ;
	Compare(0x8026, 2);
	if (1) goto label28;
	goto label29;

label28: ;
	SetVarEqVal(0x8027, 56);
	goto label25;

label29: ;
	Compare(0x8026, 3);
	if (1) goto label30;
	goto label31;

label30: ;
	SetVarEqVal(0x8027, 59);
	goto label25;

label31: ;
	Compare(0x8026, 4);
	if (1) goto label32;
	goto label33;

label32: ;
	SetVarEqVal(0x8027, 403);
	goto label25;

label33: ;
	Compare(0x8026, 5);
	if (1) goto label34;
	goto label25;

label34: ;
	SetVarEqVal(0x8027, 437);
	goto label25;

label25: ;
	Return();
}

void Routine4()
{
	SetVarEqVal(0x802E, 0);
	SetVarEqVal(0x802F, 0);
	SetVarEqVar(0x8026, 0x8020);
	Routine3();
	SetVarEqVar(0x802E, 0x8027);
	StorePartyCanLearnMove(0x8010, 0x802E, 0x8021);
	c0x108(0x802F, 0x8021);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label35;
	StackPushVar(0x802F);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label36;
	SetVarEqVar(0x8025, 0x802E);
	Routine6();
	goto label35;

label36: ;
	SetWordPartyNickname(0, 0x8021);
	SetWordMove(2, 0x802E);
	EventGreyMessage(21, 2);

label35: ;
	Return();
}

void Routine5()
{
	SetVarEqVal(0x8030, 0);
	SetVarEqVar(0x8026, 0x8020);
	Routine3();
	SetVarEqVar(0x8030, 0x8027);
	StackPushVar(0x8020);
	StackPushConst(0);
	StackCompare(5);
	if (255) goto label37;
	StorePartyCanLearnMove(0x8010, 0x8030, 0x8021);
	goto label38;

label37: ;
	SetVarEqVal(0x8010, 0);

label38: ;
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label39;
	SetVarEqVar(0x8025, 0x8030);
	Routine6();
	SetVarEqVal(0x8010, 1);
	goto label40;

label39: ;
	SetVarEqVal(0x8031, 0);
	c0x108(0x8031, 0x8021);
	StackPushVar(0x8031);
	StackPushConst(4);
	StackCompare(1);
	if (255) goto label41;
	Routine7();
	goto label40;

label41: ;
	SetVarEqVal(0x8010, 1);
	SetWordPartyNickname(0, 0x8021);
	SetWordMove(2, 0x8024);
	SetVarEqVal(0x8022, 20);
	Routine8();

label40: ;
	Return();
}

void Routine6()
{
	SetWordPartyNickname(0, 0x8021);
	SetWordMove(1, 0x8025);
	SetWordMove(2, 0x8024);
	EventGreyMessage(19, 2);
	SetVarEqVal(0x8022, 20);
	Routine8();
	Return();
}

void Routine7()
{
	SetVarEqVal(0x8032, 0);
	SetVarEqVal(0x8032, 0);
	StackPushVar(0x8032);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label42;
	SetWordPartyNickname(0, 0x8021);
	SetWordMove(1, 0x8024);
	EventGreyMessage(15, 2);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label43;
	CloseEventGreyMessage();
	c0x109(0x8010, 0x8023, 0x8021, 0x8024);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label44;
	Routine9();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label45;
	CloseEventGreyMessage();
	SetVarEqVal(0x8010, 0);
	SetVarEqVal(0x8032, 1);

label45: ;
	goto label46;

label44: ;
	c0x10A(0x8025, 0x8021, 0x8023);
	SetWordMove(1, 0x8025);
	EventGreyMessage(18, 2);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label47;
	Routine6();
	SetVarEqVal(0x8010, 1);
	SetVarEqVal(0x8032, 1);
	goto label46;

label47: ;
	Routine9();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label46;
	CloseEventGreyMessage();
	SetVarEqVal(0x8010, 0);
	SetVarEqVal(0x8032, 1);

label46: ;
	goto label48;

label43: ;
	Routine9();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label48;
	CloseEventGreyMessage();
	SetVarEqVal(0x8010, 0);
	SetVarEqVal(0x8032, 1);

label48: ;

label42: ;
	Return();
}

void Routine8()
{
	EventGreyMessage(0x8022, 2);
	PlayFanfare(1301);
	WaitFanfare();
	WaitForButton();
	CloseEventGreyMessage();
	Return();
}

void Routine9()
{
	SetWordMove(1, 0x8024);
	EventGreyMessage(16, 2);
	YesNoBox(0x8010);
	Return();
}
