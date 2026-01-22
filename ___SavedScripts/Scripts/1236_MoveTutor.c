#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

// DRAYDEN MOVE TUTOR 
void Sequence0()
{
	Routine0();
	ReturnGlobalScript();
	Message(1024, 17, 0x8011, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label0;
	Message(1024, 18, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label0: ;
	c0x1D1(0, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label1;
	Message(1024, 20, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label2;

label1: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label2;
	Message(1024, 19, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label2: ;
	Message(1024, 21, 0x8011, 0, 0);
	CloseMessageBox();
	c0x1D4(0, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label3;
	Message(1024, 18, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label3: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label4;
	Message(1024, 23, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label4: ;
	c0x1D2(0, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label5;
	goto label6;

label5: ;
	Message(1024, 19, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label7;

label6: ;
	Compare(0x8010, 1);
	if (1) goto label8;
	goto label9;

label8: ;
	Message(1024, 22, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label7;

label9: ;
	Compare(0x8010, 3);
	if (1) goto label10;
	goto label7;

label10: ;
	SetWordMove(0, 434);
	Message(1024, 24, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label7;

label7: ;
	SetVarEqVal(0x8021, 434);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 1);
	Routine1();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label11;
	Message(1024, 25, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();

label11: ;
	Return();
}


void Sequence1()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Routine2();
	WaitMoment();
	UnlockAll();
	End();
}

// PWT STARTER MOVES 
void Sequence2()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Routine3();
	WaitMoment();
	UnlockAll();
	End();
}


// RED SHARD TUTOR 
void Sequence3()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarEqVal(0x8024, 72);
	StoreFlag(325);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label12;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 48, 0, 0);
	SetFlag(325);
	goto label13;

label12: ;
	Message2(1024, 49, 0, 0);

label13: ;
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

// BLUE SHARD TUTOR 
void Sequence4()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarEqVal(0x8024, 73);
	StoreFlag(326);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label14;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 48, 0, 0);
	SetFlag(326);
	goto label15;

label14: ;
	Message2(1024, 49, 0, 0);

label15: ;
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

// YELLOW SHARD TUTOR
void Sequence5()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarEqVal(0x8024, 74);
	StoreFlag(327);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label16;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 48, 0, 0);
	SetFlag(327);
	goto label17;

label16: ;
	Message2(1024, 49, 0, 0);

label17: ;
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

// GREEN SHARD TUTOR 
void Sequence6()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarEqVal(0x8024, 75);
	StoreFlag(328);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label18;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 48, 0, 0);
	SetFlag(328);
	goto label19;

label18: ;
	Message2(1024, 49, 0, 0);

label19: ;
	Routine4();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence7()
{
	LockAll();
	c0x276(17, 0);
	PlaySound(1351);
	BorderedMessage(47, 1);
	CloseBorderedMessage();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence8()
{
	SetVarEqVar(0x8020, 0x8000);
	SetVarEqVar(0x8021, 0x8001);
	SetVarEqVal(0x8022, 1);
	SetVarEqVal(0x8023, 1);
	Routine1();
	ReturnGlobalScript();
	End();
}

// DRAYDEN SCRIPT
void Routine0()
{
	Message(1024, 17, 0x8011, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label0_0;
	Message(1024, 18, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label0_0: ;
	c0x1D1(0, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label1_1;
	Message(1024, 20, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label2_2;

label1_1: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label2_2;
	Message(1024, 19, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label2_2: ;
	Message(1024, 21, 0x8011, 0, 0);
	CloseMessageBox();
	c0x1D4(0, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label3_3;
	Message(1024, 18, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label3_3: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label4_4;
	Message(1024, 23, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label4_4: ;
	c0x1D2(0, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label5_5;
	goto label6_6;

label5_5: ;
	Message(1024, 19, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label7_7;

label6_6: ;
	Compare(0x8010, 1);
	if (1) goto label8_8;
	goto label9_9;

label8_8: ;
	Message(1024, 22, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label7_7;

label9_9: ;
	Compare(0x8010, 3);
	if (1) goto label10_10;
	goto label7_7;

label10_10: ;
	SetWordMove(0, 434);
	Message(1024, 24, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label7_7;

label7_7: ;
	SetVarEqVal(0x8021, 434);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 1);
	Routine1();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label11_11;
	Message(1024, 25, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();

label11_11: ;
	Return();
}

// LEARNING A MOVE AND PAYING THE PRICE
void Routine1()
{
	SetVarEqVal(0x8028, 0);
	c0x108(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(4);
	StackCompare(5);
	if (255) goto label20;
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	PlayFanfare(1301);
	EventGreyMessage(10, 0);
	WaitFanfare();
	StackPushVar(0x8023);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label21;
	WaitForButton();
	goto label22;

label21: ;
	WaitMessage();

label22: ;
	SetWordNumber(0, 0x400C, 4);
	SetWordNumber(1, 0x400F, 4);
	EventGreyMessage(56, 0);
	WaitForButton();
	StackPushVar(0x400C);
	StackPushConst(2);
	StackCompare(1);
	StackPushVar(0x400F);
	StackPushConst(0);
	StackCompare(2);
	StackCompare(7);
	if (255) goto label23;
	SetVarEqVal(0x8029, 0);
	TakeItem(0x8024, 0x400F, 0x8029);
	SetWordPlayerName(0);
	SetWordItem2(1, 0x8024, 0x400F, 0);
	SetWordNumber(2, 0x400F, 2);
	EventGreyMessage(53, 0);
	WaitForButton();
	SetVarEqVal(0x8029, 0);

label23: ;
	CloseEventGreyMessage();
	c0x10B(0x8020, 0x8010, 0x8021);
	Return();

label20: ;
	SetVarEqVal(0x8027, 1);

label27: ;
	StackPushVar(0x8027);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label24;
	Routine5();
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label25;
	SetVarEqVal(0x8010, 1);
	SetVarEqVal(0x8027, 0);
	goto label26;

label25: ;
	Routine6();
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label26;
	SetVarEqVal(0x8010, 0);
	SetVarEqVal(0x8027, 0);

label26: ;
	goto label27;

label24: ;
	Return();
}

// ULTIMATE STARTER MOVES 
void Routine2()
{
	Message2(1024, 26, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label28;
	Message2(1024, 29, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label28: ;
	c0x1D1(1, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label29;
	Message2(1024, 28, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label30;

label29: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label30;
	Message2(1024, 33, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label30: ;
	Message2(1024, 30, 0, 0);
	CloseMessageBox();
	c0x1D4(1, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label31;
	Message2(1024, 29, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label31: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label32;
	Message2(1024, 32, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label32: ;
	c0x1D2(1, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label33;
	goto label34;

label33: ;
	Message2(1024, 33, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label35;

label34: ;
	Compare(0x8010, 1);
	if (1) goto label36;
	goto label37;

label36: ;
	Message2(1024, 31, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label35;

label37: ;
	Compare(0x8010, 3);
	if (1) goto label38;
	goto label35;

label38: ;
	Message2(1024, 34, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label35;

label35: ;
	c0x1D3(1, 0x8020, 0x8021);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	Message2(1024, 35, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label39;
	Message2(1024, 29, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label39: ;
	CloseMessageBox();
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 0);
	Routine1();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label40;

label40: ;
	Return();
}

// PLEDGE MOVES
void Routine3()
{
	StoreFlag(253);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label41;
	Message2(1024, 37, 0, 0);
	SetFlag(253);
	goto label42;

label41: ;
	Message2(1024, 38, 0, 0);

label42: ;
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label43;
	Message2(1024, 40, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label43: ;
	c0x1D1(2, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label44;
	Message2(1024, 39, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label45;

label44: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label45;
	Message2(1024, 44, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label45: ;
	Message2(1024, 41, 0, 0);
	CloseMessageBox();
	c0x1D4(2, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label46;
	Message2(1024, 40, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label46: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label47;
	Message2(1024, 43, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label47: ;
	c0x1D2(2, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label48;
	goto label49;

label48: ;
	Message2(1024, 44, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label50;

label49: ;
	Compare(0x8010, 1);
	if (1) goto label51;
	goto label52;

label51: ;
	Message2(1024, 42, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label50;

label52: ;
	Compare(0x8010, 3);
	if (1) goto label53;
	goto label50;

label53: ;
	Message2(1024, 45, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label50;

label50: ;
	c0x1D3(2, 0x8020, 0x8021);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	Message2(1024, 46, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label54;
	Message2(1024, 40, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label54: ;
	CloseMessageBox();
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 0);
	Routine1();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label55;

label55: ;
	Return();
}

// MOVE TUTOR MOVES 
void Routine4()
{
	Message2(1024, 50, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label56;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label56: ;
	Message2(1024, 51, 0, 0);
	SetVarEqVal(0x400C, 0);
	SetVarEqVal(0x400D, 0);
	SetVarEqVal(0x400E, 0);
	SetVarEqVal(0x400F, 0);
	Compare(0x8024, 72);
	if (1) goto label57;
	goto label58;

label57: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 246);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label59;

label58: ;
	Compare(0x8024, 73);
	if (1) goto label60;
	goto label61;

label60: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 245);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label59;

label61: ;
	Compare(0x8024, 74);
	if (1) goto label62;
	goto label63;

label62: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 244);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label59;

label63: ;
	Compare(0x8024, 75);
	if (1) goto label64;
	goto label59;

label64: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 243);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label59;

label59: ;
	Logic06(0x400C);
	Logic06(0x400D);
	Logic06(0x400E);
	Logic06(0x400F);
	StackPushVar(0x400C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label65;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label65: ;
	StackPushVar(0x400C);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label66;
	Message2(1024, 54, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label66: ;
	StorePartyCanLearnMove(0x8010, 0x400D, 0x400E);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label67;
	Message2(1024, 55, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label67: ;
	SetVarEqVar(0x8021, 0x400D);
	SetVarEqVar(0x8020, 0x400E);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 1);
	Routine1();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label68;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();

label68: ;
	Return();
}

// PROMPTING THE USER IF THEY WANT TO LEARN THE MOVE
void Routine5()
{
	SetVarEqVal(0x8028, 0);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	EventGreyMessage(11, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label69;
	Return();

label69: ;
	CloseEventGreyMessage();
	c0x109(0x8010, 0x8025, 0x8020, 0x8021);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label70;
	Return();

label70: ;
	c0x10A(0x8026, 0x8020, 0x8025);
	SetWordMove(0, 0x8026);
	EventGreyMessage(14, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label71;
	Return();

label71: ;
	c0x10A(0x8026, 0x8020, 0x8025);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8026);
	SetWordMove(2, 0x8021);
	EventGreyMessage(15, 0);
	EventGreyMessage(16, 0);
	PlayFanfare(1301);
	WaitFanfare();
	StackPushVar(0x8023);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label72;
	WaitForButton();
	goto label73;

label72: ;
	WaitMessage();

label73: ;
	SetWordNumber(0, 0x400C, 4);
	SetWordNumber(1, 0x400F, 4);
	EventGreyMessage(56, 0);
	WaitForButton();
	StackPushVar(0x400C);
	StackPushConst(2);
	StackCompare(1);
	StackPushVar(0x400F);
	StackPushConst(0);
	StackCompare(2);
	StackCompare(7);
	if (255) goto label74;

	// This is the part where the player pays the price to Learn a move if they had to replace a move to learn it 
	// This part of the script fails in Pokemon Centers for some reason. 
	SetVarEqVal(0x802A, 0);
	TakeItem(0x8024, 0x400F, 0x802A);
	SetWordPlayerName(0);
	SetWordItem2(1, 0x8024, 0x400F, 0);
	SetWordNumber(2, 0x400F, 2);
	EventGreyMessage(53, 0);
	WaitForButton();
	SetVarEqVal(0x802A, 0);

label74: ;
	CloseEventGreyMessage();
	c0x10B(0x8020, 0x8025, 0x8021);
	SetVarEqVal(0x8028, 1);
	Return();
}

// PROMPTING THE USER IF THEY WANT TO GIVE UP ON THE MOVE
void Routine6()
{
	SetWordMove(0, 0x8021);
	EventGreyMessage(12, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label75;
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	EventGreyMessage(13, 0);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label76;
	WaitForButton();
	goto label77;

label76: ;
	WaitMessage();

label77: ;
	CloseEventGreyMessage();
	SetVarEqVal(0x8028, 1);
	Return();

label75: ;
	SetVarEqVal(0x8028, 0);
	Return();
}
