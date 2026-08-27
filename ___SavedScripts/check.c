#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	SetVarEqVal(0x8020, 0);
	GetPlayerDirection(0x8020);
	c0x269();
	Compare(0x8020, 0);
	if (1) goto label0;
	goto label1;

label0: ;

	Movement m[] = { //255
		Exclaimation, 1,
		FastestTurnUp, 2,
		LockDirection, 1,
		PauseAnim, 1,
		FastestWalkUp, 2,
		UnlockDirection, 1,
		UnpauseAnim, 1,
	};

	goto label2;

label1: ;
	Compare(0x8020, 2);
	if (1) goto label3;
	goto label4;

label3: ;

	Movement m[] = { //255
		Exclaimation, 1,
		FastestTurnLeft, 2,
		LockDirection, 1,
		PauseAnim, 1,
		FastestWalkLeft, 2,
		UnlockDirection, 1,
		UnpauseAnim, 1,
	};

	goto label2;

label4: ;
	Compare(0x8020, 3);
	if (1) goto label5;
	goto label2;

label5: ;

	Movement m[] = { //255
		Exclaimation, 1,
		FastestTurnRight, 2,
		LockDirection, 1,
		PauseAnim, 1,
		FastestWalkRight, 2,
		UnlockDirection, 1,
		UnpauseAnim, 1,
	};

	goto label2;

label2: ;
	WaitMovement();

	Movement m[] = { //255
		Vanish, 1,
	};

	WaitMovement();
	SetVarEqVal(0x8020, 0);
	End();
}

void Sequence1()
{
	SetVarEqVal(0x8021, 0);
	SetVarEqVal(0x8022, 0);
	SetVarEqVar(0x8021, 0x8000);
	SetVarEqVar(0x8022, 0x8001);

	Movement m[] = { //255
		Reappear, 1,
	};

	WaitMovement();
	Compare(0x8022, 1);
	if (1) goto label6;
	goto label7;

label6: ;

	Movement m[] = { //255
		JumpDown2, 1,
	};

	goto label8;

label7: ;
	Compare(0x8022, 2);
	if (1) goto label9;
	goto label10;

label9: ;

	Movement m[] = { //255
		JumpLeft2, 1,
	};

	goto label8;

label10: ;
	Compare(0x8022, 3);
	if (1) goto label11;
	goto label8;

label11: ;

	Movement m[] = { //255
		JumpRight2, 1,
	};

	goto label8;

label8: ;
	PlaySound(2068);
	WaitMovement();
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8021, 0);
	End();
}

void Sequence2()
{
	SetVarEqVal(0x8023, 0);
	SetVarEqVal(0x8024, 0);
	SetVarEqVar(0x8023, 0x8000);
	StackPushVar(0x8023);
	StackPushConst(14);
	StackCompare(1);
	if (255) goto label12;
	TeleportWarp2(488, 15, 0xFFFF, 20, 0);
	goto label13;

label12: ;
	TeleportWarp2(488, 9, 0xFFFF, 13, 0);

label13: ;
	FadeFromBlack2();
	WaitFade();

	Movement m[] = { //255
		JumpUp1, 1,
	};

	PlaySound(2068);
	WaitMovement();
	SetVarEqVal(0x8024, 0);
	SetVarEqVal(0x8023, 0);
	End();
}

void Sequence3()
{

	Movement m[] = { //255
		Reappear, 1,
	};

	WaitMovement();
	StoreFlag(265);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label14;
	c0x268(0);
	Sequence11();
	SetFlag(265);

label14: ;

	Movement m[] = { //255
		Reappear, 1,
		JumpDown2, 1,
	};

	PlaySound(2068);
	WaitMovement();
	End();
}

void Sequence4()
{

	Movement m[] = { //255
		Reappear, 1,
		JumpLeft2, 1,
	};

	PlaySound(2068);
	WaitMovement();
	End();
}

void Sequence5()
{
	LockAll();
	c0x268(1);

	Movement m[] = { //255
		Exclaimation, 1,
	};

	Sequence11();
	WaitMovement();
	SetFlag(266);
	PlayTrainerMusic(735);

	Movement m[] = { //0
		WalkDown, 2,
		TurnLeft, 1,
	};

	WaitMovement();
	Message(1024, 0, 0, 0, 0);
	CloseMessageBox();
	StartTrainerBattle(735, 0, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label15;
	TrainerBattleEnd();
	goto label16;

label15: ;
	ClearFlag(266);
	TrainerBattleLose();

label16: ;
	Message(1024, 1, 0, 0, 0);
	CloseMessageBox();

	Movement m[] = { //0
		WalkRight, 2,
		WalkUp, 1,
		TurnDown, 1,
	};

	WaitMovement();
	SetVarEqVal(0x409D, 1);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence6()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message(1024, 2, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence7()
{
	SetVarEqVal(0x8007, 0);
	LockAll();
	PlaySound(1351);
	FacePlayer();
	StoreBadge(0x8000, 2);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 0);
	if (1) goto label17;
	Message2(1024, 7, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label18;

label17: ;
	SetVarFlagStatus(109, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label19;
	SetVarEqVal(0x8007, 0);
	SetVarFlagStatus(1620, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label20;
	SetVarEqVal(0x8000, 0);
	goto label21;

label20: ;
	SetVarEqVal(0x8000, 1);

label21: ;
	Compare(0x8000, 0);
	if (1) goto label22;
	AddToVar(0x8007, 1);

label22: ;
	SetVarEqVal(0x8008, 0x4065);
	Compare(0x8008, 0);
	if (5) goto label23;
	AddToVar(0x8007, 1);

label23: ;
	SetVarFlagStatus(2378, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label24;
	SetVarEqVal(0x8000, 0);
	goto label25;

label24: ;
	SetVarEqVal(0x8000, 1);

label25: ;
	Compare(0x8000, 0);
	if (1) goto label26;
	AddToVar(0x8007, 1);

label26: ;
	SetVarFlagStatus(2286, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label27;
	SetVarEqVal(0x8000, 0);
	goto label28;

label27: ;
	SetVarEqVal(0x8000, 1);

label28: ;
	Compare(0x8000, 0);
	if (1) goto label29;
	AddToVar(0x8007, 1);

label29: ;
	Compare(0x8007, 0);
	if (3) goto label30;
	Message2(1024, 13, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarFlagStatus(1620, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label31;
	SetVarEqVal(0x8000, 0);
	goto label32;

label31: ;
	SetVarEqVal(0x8000, 1);

label32: ;
	Compare(0x8000, 0);
	if (1) goto label33;
	EventGreyMessage(15, 2);

label33: ;
	SetVarEqVal(0x8008, 0x4065);
	Compare(0x8008, 0);
	if (5) goto label34;
	EventGreyMessage(16, 2);

label34: ;
	SetVarFlagStatus(2378, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label35;
	SetVarEqVal(0x8000, 0);
	goto label36;

label35: ;
	SetVarEqVal(0x8000, 1);

label36: ;
	Compare(0x8000, 0);
	if (1) goto label37;
	EventGreyMessage(17, 2);

label37: ;
	SetVarFlagStatus(2286, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label38;
	SetVarEqVal(0x8000, 0);
	goto label39;

label38: ;
	SetVarEqVal(0x8000, 1);

label39: ;
	Compare(0x8000, 0);
	if (1) goto label40;
	EventGreyMessage(18, 2);

label40: ;
	CloseAllMessageBoxes();
	goto label41;

label30: ;
	Message2(1024, 15, 0, 0);
	WaitForButton();
	CloseMessageBox();

label41: ;
	goto label18;

label19: ;
	Message2(1024, 5, 0, 0);
	CloseMessageBox();
	StackPushVar(0x8004);
	StackPushVar(0x8005);
	StackPushVar(0x8006);
	StackPushVar(0x8007);
	SetVarEqVal(0x8008, 194);
	SetVarEqVal(0x8009, 3);
	SetVarEqVar(0x8000, 0x8008);
	SetVarEqVar(0x8001, 0x8009);
	CallGlobalScript(2805);
	StackPop(0x8007);
	StackPop(0x8006);
	StackPop(0x8005);
	StackPop(0x8004);
	Message2(1024, 6, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Message2(1024, 12, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetFlag(109);

label18: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence8()
{
	LockAll();
	PlaySound(1351);
	StoreBadge(0x8008, 2);
	SetWordPlayerName(0);
	SetWordRivalName(1);
	StackPushVar(0x8008);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label42;
	SetWordPlayerName(0);
	BubbleMessage(8, 2);
	goto label43;

label42: ;
	StoreFlag(2477);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label44;
	BubbleMessage(9, 2);
	goto label43;

label44: ;
	BubbleMessage(10, 2);

label43: ;
	WaitForButton();
	CloseBubbleMessage();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence9()
{
	StoreFlag(266);
	StackPushConst(1);
	StackCompare(1);
	StackPushVar(0x409D);
	StackPushConst(0);
	StackCompare(1);
	StackCompare(7);
	if (255) goto label45;
	SetNPCPosition(0, 25, 20, 17, 2);
	goto label46;

label45: ;
	StoreFlag(266);
	StackPushConst(1);
	StackCompare(1);
	StackPushVar(0x409D);
	StackPushConst(1);
	StackCompare(1);
	StackCompare(7);
	if (255) goto label46;
	SetNPCPosition(0, 27, 20, 16, 1);

label46: ;
	End();
}

void Sequence10()
{
	SetVarFlagStatus(109, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label47;
	SetVarEqVal(0x8000, 0);
	goto label48;

label47: ;
	SetVarEqVal(0x8000, 1);

label48: ;
	Compare(0x8000, 0);
	if (1) goto label49;
	SetVarEqVal(0x8004, 4);
	LockAll();
	PlaySound(1351);
	Message(1024, 5, 0x8004, 0, 0);

	Movement m[] = { //255
		TurnRight, 1,
	};

	SetVarEqVar(0x8000, 0x8004);

	Movement m[] = { //32768
		TurnLeft, 1,
	};

	WaitMovement();
	Message(1024, 21, 0x8004, 0, 0);
	CloseMessageBox();
	StackPushVar(0x8004);
	SetVarEqVal(0x8005, 194);
	SetVarEqVal(0x8006, 3);
	SetVarEqVar(0x8000, 0x8005);
	SetVarEqVar(0x8001, 0x8006);
	CallGlobalScript(2805);
	StackPop(0x8004);
	Message(1024, 6, 0x8004, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Message(1024, 12, 0x8004, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetFlag(109);
	WaitMoment();
	UnlockAll();

label49: ;
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence11()
{
	PlaySound(2069);
	ReturnAfterDelay(5);
	PlaySound(2069);
	ReturnAfterDelay(5);
	PlaySound(2069);
	ReturnAfterDelay(7);
	PlaySound(2070);
	ReturnAfterDelay(28);
	PlaySound(2071);
	Return();
}
