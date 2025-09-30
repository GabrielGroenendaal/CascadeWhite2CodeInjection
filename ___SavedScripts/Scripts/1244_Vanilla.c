#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	LockAll();
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8020, 0);
	SetVarEqVal(0x8021, 0);
	SetVarFlagStatus(2411, 0x8025);
	SetVarFlagStatus(2402, 0x8026);
	SetVarFlagStatus(2400, 0x8022);
	StoreEA(0x8023);
	BootPCSound();
	SetWordPlayerName(0);
	EventGreyMessage(0, 2);

label23: ;
	StackPushVar(0x8020);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label0;
	EventGreyMessage(1, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8024);
	StackPushVar(0x8025);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label1;
	AddDialogueOption(2, 0xFFFF, 2);
	goto label2;

label1: ;
	AddDialogueOption(3, 0xFFFF, 3);

label2: ;
	SetWordPlayerName(0);
	AddDialogueOption(4, 0xFFFF, 4);
	StackPushVar(0x8026);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label3;
	AddDialogueOption(5, 0xFFFF, 5);

label3: ;
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label4;
	AddDialogueOption(6, 0xFFFF, 6);

label4: ;
	AddDialogueOption(7, 0xFFFF, 7);
	AddDialogueOption(8, 0xFFFF, 8);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	ReturnAfterDelay(3);
	Compare(0x8024, 2);
	if (1) goto label5;
	goto label6;

label5: ;
	Routine0();
	goto label7;

label6: ;
	Compare(0x8024, 3);
	if (1) goto label8;
	goto label9;

label8: ;
	Routine0();
	goto label7;

label9: ;
	Compare(0x8024, 4);
	if (1) goto label10;
	goto label11;

label10: ;
	Routine1();
	goto label7;

label11: ;
	Compare(0x8024, 5);
	if (1) goto label12;
	goto label13;

label12: ;
	Routine2();
	goto label7;

label13: ;
	Compare(0x8024, 6);
	if (1) goto label14;
	goto label15;

label14: ;
	Routine3();
	goto label7;

label15: ;
	Compare(0x8024, 7);
	if (1) goto label16;
	goto label17;

label16: ;
	Routine4();
	goto label7;

label17: ;
	Compare(0x8024, 8);
	if (1) goto label18;
	goto label19;

label18: ;
	SetVarEqVal(0x8020, 1);
	goto label7;

label19: ;
	Compare(0x8024, 0xFFFE);
	if (1) goto label20;
	goto label21;

label20: ;
	SetVarEqVal(0x8020, 1);
	goto label7;

label21: ;
	Compare(0x8024, 0xFFFD);
	if (1) goto label22;
	goto label7;

label22: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	goto label7;

label7: ;
	goto label23;

label0: ;
	c0x132(0x8021);
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8024, 0);
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
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
	if (255) goto label24;
	SetVarFlagStatus(246, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label24;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(12, 2);
	SetFlag(246);

label24: ;
	StackPushVar(0x802B);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label25;
	SetVarFlagStatus(247, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label25;
	PlayFanfare(1308);
	WaitFanfare();
	EventGreyMessage(13, 2);
	SetFlag(247);

label25: ;
	SetVarEqVal(0x8027, 0);

label45: ;
	StackPushVar(0x8027);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label26;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x8028);
	AddDialogueOption(15, 21, 15);
	AddDialogueOption(16, 22, 16);
	AddDialogueOption(17, 23, 17);
	AddDialogueOption(20, 26, 20);
	AddDialogueOption(18, 24, 18);
	AddDialogueOption(19, 25, 19);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x8028, 19);
	if (1) goto label27;
	goto label28;

label27: ;
	Return();
	goto label29;

label28: ;
	Compare(0x8028, 0xFFFE);
	if (1) goto label30;
	goto label31;

label30: ;
	Return();
	goto label29;

label31: ;
	Compare(0x8028, 0xFFFD);
	if (1) goto label32;
	goto label29;

label32: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label29;

label29: ;
	FadeIntoBlack2();
	WaitFade();
	Compare(0x8028, 15);
	if (1) goto label33;
	goto label34;

label33: ;
	c0x14F(0x8029, 0);
	goto label35;

label34: ;
	Compare(0x8028, 16);
	if (1) goto label36;
	goto label37;

label36: ;
	c0x14F(0x8029, 1);
	goto label35;

label37: ;
	Compare(0x8028, 17);
	if (1) goto label38;
	goto label39;

label38: ;
	c0x14F(0x8029, 2);
	goto label35;

label39: ;
	Compare(0x8028, 20);
	if (1) goto label40;
	goto label41;

label40: ;
	c0x14F(0x8029, 4);
	goto label35;

label41: ;
	Compare(0x8028, 18);
	if (1) goto label42;
	goto label35;

label42: ;
	c0x14F(0x8029, 3);
	goto label35;

label35: ;
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x8029);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label43;
	PlaySound(1372);
	goto label44;

label43: ;
	SetVarEqVal(0x8027, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label44: ;
	goto label45;

label26: ;
	SetVarEqVal(0x802B, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x8028, 0);
	SetVarEqVal(0x8027, 0);
	Return();
}

void Routine1()
{
	SetVarEqVal(0x802C, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802E, 0);
	PlaySound(1372);
	SetWordPlayerName(0);
	EventGreyMessage(27, 2);
	CloseEventGreyMessage();
	SetVarEqVal(0x802C, 0);

label55: ;
	StackPushVar(0x802C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label46;
	EventGreyMessage(41, 2);
	SetupDialogueSelection(31, 1, 0, 1, 0x802D);
	AddDialogueOption(28, 30, 28);
	AddDialogueOption(29, 31, 29);
	ShowDialogueSelection2();
	CloseEventGreyMessage();
	Compare(0x802D, 29);
	if (1) goto label47;
	goto label48;

label47: ;
	Return();
	goto label49;

label48: ;
	Compare(0x802D, 0xFFFE);
	if (1) goto label50;
	goto label51;

label50: ;
	Return();
	goto label49;

label51: ;
	Compare(0x802D, 0xFFFD);
	if (1) goto label52;
	goto label49;

label52: ;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);
	Return();
	goto label49;

label49: ;
	FadeIntoBlack2();
	WaitFade();
	c0x150(0x802E);
	PC_131();
	FadeFromBlack2();
	WaitFade();
	StackPushVar(0x802E);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label53;
	PlaySound(1372);
	goto label54;

label53: ;
	SetVarEqVal(0x802C, 1);
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label54: ;
	goto label55;

label46: ;
	SetVarEqVal(0x802E, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802C, 0);
	Return();
}

void Routine2()
{
	PlaySound(1372);
	EventGreyMessage(39, 2);
	CallGlobalScript(10382);
	Return();
}

void Routine3()
{
	SetVarEqVal(0x802F, 0);
	SetVarEqVal(0x8030, 0);
	PlaySound(1372);
	EventGreyMessage(35, 2);
	CloseEventGreyMessage();
	StackPushVar(0x8023);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label56;
	c0x14D(1, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label57;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label57: ;
	goto label58;

label56: ;
	EventGreyMessage(10, 2);
	CloseEventGreyMessage();

label58: ;
	SetVarEqVal(0x8030, 0);
	SetVarEqVal(0x802F, 0);
	Return();
}

void Routine4()
{
	PlaySound(1372);
	EventGreyMessage(40, 2);
	CloseEventGreyMessage();
	c0x231(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label59;
	SetVarEqVal(0x8020, 1);
	SetVarEqVal(0x8021, 1);

label59: ;
	Return();
}
