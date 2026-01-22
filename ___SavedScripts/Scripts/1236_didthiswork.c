#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	Sequence9();
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
	Sequence10();
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
	Sequence11();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence2()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Sequence12();
	WaitMoment();
	UnlockAll();
	End();
}

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
	Sequence13();
	WaitMoment();
	UnlockAll();
	End();
}

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
	Sequence13();
	WaitMoment();
	UnlockAll();
	End();
}

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
	Sequence13();
	WaitMoment();
	UnlockAll();
	End();
}

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
	Sequence13();
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
	Sequence10();
	ReturnGlobalScript();
	End();
}

void Sequence9()
{
	Message(1024, 17, 0x8011, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label20;
	Message(1024, 18, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label20: ;
	c0x1D1(0, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label21;
	Message(1024, 20, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label22;

label21: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label22;
	Message(1024, 19, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label22: ;
	Message(1024, 21, 0x8011, 0, 0);
	CloseMessageBox();
	c0x1D4(0, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label23;
	Message(1024, 18, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label23: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label24;
	Message(1024, 23, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label24: ;
	c0x1D2(0, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label25;
	goto label26;

label25: ;
	Message(1024, 19, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label27;

label26: ;
	Compare(0x8010, 1);
	if (1) goto label28;
	goto label29;

label28: ;
	Message(1024, 22, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label27;

label29: ;
	Compare(0x8010, 3);
	if (1) goto label30;
	goto label27;

label30: ;
	SetWordMove(0, 434);
	Message(1024, 24, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label27;

label27: ;
	SetVarEqVal(0x8021, 434);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 1);
	Sequence10();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label31;
	Message(1024, 25, 0x8011, 0, 0);
	WaitForButton();
	CloseMessageBox();

label31: ;
	Return();
}

void Sequence10()
{
	SetVarEqVal(0x8028, 0);
	c0x108(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(4);
	StackCompare(5);
	if (255) goto label32;
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	PlayFanfare(1301);
	EventGreyMessage(10, 0);
	WaitFanfare();
	StackPushVar(0x8023);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label33;
	WaitForButton();
	goto label34;

label33: ;
	WaitMessage();

label34: ;
	StackPushVar(0x400C);
	StackPushConst(2);
	StackCompare(1);
	StackPushVar(0x400F);
	StackPushConst(0);
	StackCompare(2);
	StackCompare(7);
	EventGreyMessage(44, 0);
	EventGreyMessage(44, 0);
	WaitForButton();
	SetVarEqVal(0x8029, 0);
	TakeItem(0x8024, 0x400F, 0x8029);
	SetWordPlayerName(0);
	SetWordItem2(1, 0x8024, 0x400F, 0);
	SetWordNumber(2, 0x400F, 2);
	EventGreyMessage(53, 0);
	WaitForButton();
	SetVarEqVal(0x8029, 0);
	CloseEventGreyMessage();
	c0x10B(0x8020, 0x8010, 0x8021);
	Return();

label32: ;
	SetVarEqVal(0x8027, 1);

label38: ;
	StackPushVar(0x8027);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label35;
	Sequence14();
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label36;
	SetVarEqVal(0x8010, 1);
	SetVarEqVal(0x8027, 0);
	goto label37;

label36: ;
	Sequence15();
	StackPushVar(0x8028);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label37;
	SetVarEqVal(0x8010, 0);
	SetVarEqVal(0x8027, 0);

label37: ;
	goto label38;

label35: ;
	Return();
}

void Sequence11()
{
	Message2(1024, 26, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label87;
	Message2(1024, 29, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label87: ;
	c0x1D1(1, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label39;
	Message2(1024, 28, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label40;

label39: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label40;
	Message2(1024, 33, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label40: ;
	Message2(1024, 30, 0, 0);
	CloseMessageBox();
	c0x1D4(1, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label41;
	Message2(1024, 29, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label41: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label42;
	Message2(1024, 32, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label42: ;
	c0x1D2(1, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label43;
	goto label44;

label43: ;
	Message2(1024, 33, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label45;

label44: ;
	Compare(0x8010, 1);
	if (1) goto label46;
	goto label47;

label46: ;
	Message2(1024, 31, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label45;

label47: ;
	Compare(0x8010, 3);
	if (1) goto label48;
	goto label45;

label48: ;
	Message2(1024, 34, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label45;

label45: ;
	c0x1D3(1, 0x8020, 0x8021);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	Message2(1024, 35, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label49;
	Message2(1024, 29, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label49: ;
	CloseMessageBox();
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 0);
	Sequence10();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label50;

label50: ;
	Return();
}

void Sequence12()
{
	StoreFlag(253);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label51;
	Message2(1024, 37, 0, 0);
	SetFlag(253);
	goto label52;

label51: ;
	Message2(1024, 38, 0, 0);

label52: ;
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label53;
	Message2(1024, 40, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label53: ;
	c0x1D1(2, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label54;
	Message2(1024, 39, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label55;

label54: ;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label55;
	Message2(1024, 44, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label55: ;
	Message2(1024, 41, 0, 0);
	CloseMessageBox();
	c0x1D4(2, 0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label56;
	Message2(1024, 40, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label56: ;
	GetPartyIsEgg(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label57;
	Message2(1024, 43, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label57: ;
	c0x1D2(2, 0x8020, 0x8010);
	Compare(0x8010, 2);
	if (1) goto label58;
	goto label59;

label58: ;
	Message2(1024, 44, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label60;

label59: ;
	Compare(0x8010, 1);
	if (1) goto label61;
	goto label62;

label61: ;
	Message2(1024, 42, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label60;

label62: ;
	Compare(0x8010, 3);
	if (1) goto label63;
	goto label60;

label63: ;
	Message2(1024, 45, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();
	goto label60;

label60: ;
	c0x1D3(2, 0x8020, 0x8021);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	Message2(1024, 46, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label64;
	Message2(1024, 40, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label64: ;
	CloseMessageBox();
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 0);
	Sequence10();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label65;

label65: ;
	Return();
}

void Sequence13()
{
	Message2(1024, 50, 0, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label88;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label88: ;
	Message2(1024, 51, 0, 0);
	SetVarEqVal(0x400C, 0);
	SetVarEqVal(0x400D, 0);
	SetVarEqVal(0x400E, 0);
	SetVarEqVal(0x400F, 0);
	Compare(0x8024, 72);
	if (1) goto label66;
	goto label67;

label66: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 246);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label68;

label67: ;
	Compare(0x8024, 73);
	if (1) goto label69;
	goto label70;

label69: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 245);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label68;

label70: ;
	Compare(0x8024, 74);
	if (1) goto label71;
	goto label72;

label71: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 244);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label68;

label72: ;
	Compare(0x8024, 75);
	if (1) goto label73;
	goto label68;

label73: ;
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 243);
	SetVarEqVar2(0x8001, 0);
	CallGlobalScript(10110);
	StackPop(0x8001);
	StackPop(0x8000);
	goto label68;

label68: ;
	Logic06(0x400C);
	Logic06(0x400D);
	Logic06(0x400E);
	Logic06(0x400F);
	StackPushVar(0x400C);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label74;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label74: ;
	StackPushVar(0x400C);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label75;
	Message2(1024, 54, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label75: ;
	StorePartyCanLearnMove(0x8010, 0x400D, 0x400E);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label76;
	Message2(1024, 55, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Return();

label76: ;
	SetVarEqVar(0x8021, 0x400D);
	SetVarEqVar(0x8020, 0x400E);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 1);
	Sequence10();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label77;
	SetWordItem2(0, 0x8024, 2, 0);
	Message2(1024, 52, 0, 0);
	WaitForButton();
	CloseMessageBox();

label77: ;
	Return();
}

void Sequence14()
{
	SetVarEqVal(0x8028, 0);
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	EventGreyMessage(11, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label78;
	Return();

label78: ;
	CloseEventGreyMessage();
	c0x109(0x8010, 0x8025, 0x8020, 0x8021);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label79;
	Return();

label79: ;
	c0x10A(0x8026, 0x8020, 0x8025);
	SetWordMove(0, 0x8026);
	EventGreyMessage(14, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label80;
	Return();

label80: ;
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
	if (255) goto label81;
	WaitForButton();
	goto label82;

label81: ;
	WaitMessage();

label82: ;
	StackPushVar(0x400C);
	StackPushConst(2);
	StackCompare(1);
	StackPushVar(0x400F);
	StackPushConst(0);
	StackCompare(2);
	StackCompare(7);
	if (255) goto label83;
	SetVarEqVal(0x802A, 0);
	TakeItem(0x8024, 0x400F, 0x802A);
	SetWordPlayerName(0);
	SetWordItem2(1, 0x8024, 0x400F, 0);
	SetWordNumber(2, 0x400F, 2);
	EventGreyMessage(53, 0);
	WaitForButton();
	SetVarEqVal(0x802A, 0);

label83: ;
	CloseEventGreyMessage();
	c0x10B(0x8020, 0x8025, 0x8021);
	SetVarEqVal(0x8028, 1);
	Return();
}

void Sequence15()
{
	SetWordMove(0, 0x8021);
	EventGreyMessage(12, 0);
	YesNoBox(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label84;
	SetWordPartyNickname(0, 0x8020);
	SetWordMove(1, 0x8021);
	EventGreyMessage(13, 0);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label85;
	WaitForButton();
	goto label86;

label85: ;
	WaitMessage();

label86: ;
	CloseEventGreyMessage();
	SetVarEqVal(0x8028, 1);
	Return();

label84: ;
	SetVarEqVal(0x8028, 0);
	Return();
}
