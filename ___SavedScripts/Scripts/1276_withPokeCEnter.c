#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"
#include "ScriptHeaders/CommandOverlay65.h"

void Sequence0()
{
	Routine0();
	End();
}

void Sequence1()
{
	c0x22(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label0;
	Routine0();

label0: ;
	End();
}

void Sequence2()
{
	LockAll();
	// RemoveNPC(1);
	Movement m[] = { //255
		WalkDown, 1,
	};

	WaitMovement();

	// Movement m[] = { //1
	// 	Exclaimation, 1,
	// 	TurnUp, 1,
	// };

	// WaitMovement();
	// NPCPathFind(1, 107, 664, 1, 8, 1);
	// WaitMovement();
	// Routine1();

	// Movement m[] = { //1
	// 	WalkDown, 4,
	// 	WalkRight, 6,
	// 	WalkDown, 5,
	// };

	WaitMovement();
	RemoveNPC(1);
	SetFlag(730);
	ClearFlag(731);
	AddNPC(0);
	c0x127(0x8029, 1, 107, 661);
	c0x129(0x8029, 0);
	c0x12A(0x8029);
	PlaySound(1369);
	SetNPCPosition(0, 107, 2, 661, 1);
	WaitSound();
	NPCPathFind(0, 107, 662, 1, 8, 0);

	Movement m[] = { //255
		TurnUp, 1,
	};

	WaitMovement();
	c0x129(0x8029, 1);
	c0x12A(0x8029);
	c0x128(0x8029);
	SetWordPlayerName(0);
	Message(1024, 61, 0, 0, 0);
	CloseAllMessageBoxes();

	Movement m[] = { //0
		TurnUp, 1,
	};

	WaitMovement();
	c0x127(0x8029, 1, 107, 661);
	c0x129(0x8029, 0);
	c0x12A(0x8029);

	Movement m[] = { //0
		WalkUp, 1,
	};

	WaitMovement();
	PlaySound(1369);
	RemoveNPC(0);
	WaitSound();
	c0x129(0x8029, 1);
	c0x12A(0x8029);
	c0x128(0x8029);
	SetFlag(731);
	SetVarEqVal(0x40A5, 6);
	SetFlag(267);
	SetVarEqVal(0x40A8, 1);
	SetVarEqVal(0x409E, 1);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence3()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Compare(0x409E, 0);
	if (1) goto label1;
	goto label2;

label1: ;
	Routine1();
	SetVarEqVal(0x409E, 1);
	goto label3;

label2: ;
	Compare(0x409E, 2);
	if (1) goto label4;
	goto label5;

label4: ;
	SetWordLocation(0, 28);
	Message2(1024, 3, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label3;

label5: ;
	Compare(0x409E, 4);
	if (1) goto label6;
	goto label7;

label6: ;
	SetWordPlayerName(0);
	Message2(1024, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label3;

label7: ;
	Compare(0x409E, 1);
	if (1) goto label8;
	goto label9;

label8: ;
	Routine2();
	Routine3();
	CountMedals26E(3, 0x8022);
	CountMedals26E(4, 0x8023);
	StackPushVar(0x8022);
	StackPushVar(0x8023);
	StackCompare(4);
	if (255) goto label10;
	SetVarEqVal(0x409E, 2);
	SetWordPlayerName(0);
	SetWordLocation(1, 28);
	Message2(1024, 4, 0, 0);
	goto label11;

label10: ;
	Routine4();

label11: ;
	WaitForButton();
	CloseMessageBox();
	goto label3;

label9: ;
	Compare(0x409E, 3);
	if (1) goto label12;
	goto label3;

label12: ;
	Routine2();
	Routine3();
	Routine5();
	Routine4();
	WaitForButton();
	CloseMessageBox();
	goto label3;

label3: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
{
	c0x3E8(1000);
	Routine6();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label13;
	ClearFlag(746);
	c0x272(0x8010, 0x8024);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label14;
	AddNPC(0x8024);

label14: ;
	Routine7();
	goto label15;

label13: ;
	c0x272(0x8010, 0x8024);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label16;
	RemoveNPC(0x8024);

label16: ;
	SetFlag(746);

label15: ;
	Return();
}

void Routine1()
{
	Message(1024, 11, 1, 0, 0);
	CloseMessageBox();
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 627);
	SetVarEqVar2(0x8001, 1);
	CallGlobalScript(2805);
	StackPop(0x8001);
	StackPop(0x8000);
	Message(1024, 12, 1, 0, 0);
	YesNoBox(0x8010);
	Message(1024, 13, 1, 0, 0);
	CloseMessageBox();
	SetVarEqVal(0x8020, 0);
	Routine8();
	Message(1024, 14, 1, 0, 0);
	CloseMessageBox();
	c0x2E1();
	CountMedals26E(1, 0x8022);
	SetWordPlayerName(0);
	SetWordNumber(1, 0x8022, 3);
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(5);
	if (255) goto label17;
	EventGreyMessage(9, 0);
	goto label18;

label17: ;
	EventGreyMessage(10, 0);

label18: ;
	CloseEventGreyMessage();
	Message(1024, 15, 1, 0, 0);
	CloseMessageBox();
	Return();
}

void Routine2()
{
	CountMedals26E(2, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label19;
	Return();

label19: ;
	SetWordPlayerName(0);
	Message2(1024, 20, 0, 0);
	CloseMessageBox();
	c0x3E9(0x8010, 0x8020);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label20;
	Routine8();

label20: ;
	c0x3E9(0x8010, 0x8020);

label22: ;
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label21;
	Message2(1024, 21, 0, 0);
	CloseMessageBox();
	Routine8();
	c0x3E9(0x8010, 0x8020);
	goto label22;

label21: ;
	Return();
}

void Routine3()
{
	CountMedals26E(0, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label23;
	Return();

label23: ;
	SetWordPlayerName(0);
	SetWordNumber(1, 0x8010, 3);
	Message2(1024, 5, 0, 0);
	CloseMessageBox();
	CountMedals26E(0, 0x8022);
	SetWordPlayerName(0);
	SetWordNumber(1, 0x8022, 3);
	StackPushVar(0x8022);
	StackPushConst(1);
	StackCompare(5);
	if (255) goto label24;
	EventGreyMessage(9, 0);
	goto label25;

label24: ;
	EventGreyMessage(10, 0);

label25: ;
	CloseEventGreyMessage();
	c0x3E8(1002);
	CountMedals26E(5, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(5);
	if (255) goto label26;
	Message2(1024, 6, 0, 0);

label26: ;
	Return();
}

void Routine4()
{
	CountMedals26E(6, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(3);
	if (255) goto label27;
	SetVarEqVal(0x409E, 4);
	SetWordPlayerName(0);
	Message2(1024, 0, 0, 0);
	Return();

label27: ;
	CountMedals26E(7, 0x8021);
	StackPushVar(0x8021);
	StackPushConst(4);
	StackCompare(1);
	if (255) goto label28;
	Message2(1024, 2, 0, 0);
	Return();

label28: ;
	CountMedals26E(4, 0x8023);
	SetWordNumber(0, 0x8023, 3);
	Message2(1024, 1, 0, 0);
	Return();
}

void Routine5()
{
	Routine9();
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label29;
	Return();

label29: ;
	SetWordPlayerName(0);
	Message2(1024, 16, 0, 0);
	CloseMessageBox();

label41: ;
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label30;
	c0x3E8(1003);
	CountMedals26E(7, 0x8021);
	StoreMedals26D(1, 0x8021);
	EventGreyMessage(19, 0);
	PlayFanfare(1335);
	WaitFanfare();
	WaitMessage();
	CloseEventGreyMessage();
	Message2(1024, 17, 0, 0);
	CloseMessageBox();
	Compare(0x8021, 1);
	if (1) goto label31;
	goto label32;

label31: ;
	SetVarEqVal(0x8020, 2);
	goto label33;

label32: ;
	Compare(0x8021, 2);
	if (1) goto label34;
	goto label35;

label34: ;
	SetVarEqVal(0x8020, 3);
	goto label33;

label35: ;
	Compare(0x8021, 3);
	if (1) goto label36;
	goto label37;

label36: ;
	SetVarEqVal(0x8020, 4);
	goto label33;

label37: ;
	Compare(0x8021, 4);
	if (1) goto label38;
	goto label39;

label38: ;
	SetVarEqVal(0x8020, 5);
	goto label33;

label39: ;
	SetVarEqVal(0x8020, 1);

label33: ;
	Routine8();
	Routine9();
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label40;
	Message2(1024, 18, 0, 0);
	CloseMessageBox();

label40: ;
	goto label41;

label30: ;
	Return();
}

void Routine6()
{
	CheckItemBagNumber(627, 1, 0x8010);
	Logic06(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label42;
	SetVarEqVal(0x8010, 0);
	Return();

label42: ;
	CountMedals26E(2, 0x8022);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(5);
	if (255) goto label43;
	SetVarEqVal(0x8010, 1);
	Return();

label43: ;
	CountMedals26E(0, 0x8022);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(5);
	if (255) goto label44;
	SetVarEqVal(0x8010, 1);
	Return();

label44: ;
	Routine9();
	Return();
}

void Routine7()
{
	GetNPCPosition(0x8024, 0x8025, 0x8026);
	GetHeroPosition(0x8027, 0x8028);
	StackPushVar(0x8027);
	StackPushVar(0x8025);
	StackCompare(1);
	StackPushVar(0x8028);
	StackPushVar(0x8026);
	StackCompare(1);
	StackCompare(7);
	if (255) goto label45;
	AddToVar(0x8025, 1);
	SetNPCPosition(0x8024, 0x8025, 0, 0x8026, 1);

label45: ;
	Return();
}

void Routine8()
{
	SetVarEqVal(0x802A, 0);
	c0x29E(0x8020, 0x802A);
	Logic06(0x802A);
	c0x19B(0x802A);
	c0x271(0x8020, 1);
	SetWordPlayerName(0);
	StoreMedals26C(1, 0x8020);
	EventGreyMessage(22, 0);
	CloseEventGreyMessage();
	Return();
}

void Routine9()
{
	CountMedals26E(7, 0x8021);
	StackPushVar(0x8021);
	StackPushConst(4);
	StackCompare(1);
	if (255) goto label46;
	SetVarEqVal(0x8010, 0);
	Return();

label46: ;
	CountMedals26E(3, 0x8022);
	CountMedals26E(4, 0x8023);
	StackPushVar(0x8022);
	StackPushVar(0x8023);
	StackCompare(4);
	if (255) goto label47;
	SetVarEqVal(0x8010, 1);
	Return();

label47: ;
	SetVarEqVal(0x8010, 0);
	Return();
}
