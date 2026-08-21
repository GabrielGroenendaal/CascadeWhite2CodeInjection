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
	Routine0();
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

	Routine0();
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

// void Sequence7()
// {
// 	LockAll();
// 	PlaySound(1351);
// 	FacePlayer();
// 	StoreBadge(0x8008, 2);
// 	StackPushVar(0x8008);
// 	StackPushConst(0);
// 	StackCompare(1);
// 	if (255) goto label17;
// 	StoreFlag(109);
// 	StackPushConst(0);
// 	StackCompare(1);
// 	if (255) goto label18;
// 	Message2(1024, 5, 0, 0);
// 	CloseMessageBox();
// 	StackPushVar(0x8000);
// 	StackPushVar(0x8001);
// 	SetVarEqVar2(0x8000, 30);
// 	SetVarEqVar2(0x8001, 1);
// 	CallGlobalScript(2805);
// 	StackPop(0x8001);
// 	StackPop(0x8000);
// 	Message2(1024, 6, 0, 0);
// 	WaitForButton();
// 	CloseMessageBox();
// 	SetFlag(109);
// 	goto label19;

// label18: ;
// 	Message2(1024, 6, 0, 0);
// 	WaitForButton();
// 	CloseMessageBox();

// label19: ;
// 	goto label20;

// label17: ;
// 	Message2(1024, 7, 0, 0);
// 	WaitForButton();
// 	CloseMessageBox();

// label20: ;
// 	WaitMoment();
// 	UnlockAll();
// 	End();
// }

void Sequence7()
{
	SetVarEqVal(0x8007, 0);
	LockAll();
	PlaySound(1351);
	FacePlayer();
	StoreBadge(0x8000, 2);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 0);
	if (1) goto label101;
	Message2(1024, 7, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label111;

label101: ;
	SetVarFlagStatus(109, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label121;
	SetVarEqVal(0x8007, 0);
	SetVarFlagStatus(1620, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label131;
	SetVarEqVal(0x8000, 0);
	goto label141;

label131: ;
	SetVarEqVal(0x8000, 1);

label141: ;
	Compare(0x8000, 0);
	if (1) goto label151;
	AddToVar(0x8007, 1);

label151: ;
	SetVarEqVal(0x8008, 0x4065);
	Compare(0x8008, 0);
	if (5) goto label161;
	AddToVar(0x8007, 1);

label161: ;
	SetVarFlagStatus(2378, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label171;
	SetVarEqVal(0x8000, 0);
	goto label181;

label171: ;
	SetVarEqVal(0x8000, 1);

label181: ;
	Compare(0x8000, 0);
	if (1) goto label191;
	AddToVar(0x8007, 1);

label191: ;
	SetVarFlagStatus(2286, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label201;
	SetVarEqVal(0x8000, 0);
	goto label211;

label201: ;
	SetVarEqVal(0x8000, 1);

label211: ;
	Compare(0x8000, 0);
	if (1) goto label221;
	AddToVar(0x8007, 1);

label221: ;
	Compare(0x8007, 0);
	if (3) goto label231;
	Message2(1024, 13, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetVarFlagStatus(1620, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label241;
	SetVarEqVal(0x8000, 0);
	goto label251;

label241: ;
	SetVarEqVal(0x8000, 1);

label251: ;
	Compare(0x8000, 0);
	if (1) goto label261;
	EventGreyMessage(15, 2);

label261: ;
	SetVarEqVal(0x8008, 0x4065);
	Compare(0x8008, 0);
	if (5) goto label271;
	EventGreyMessage(16, 2);

label271: ;
	SetVarFlagStatus(2378, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label281;
	SetVarEqVal(0x8000, 0);
	goto label291;

label281: ;
	SetVarEqVal(0x8000, 1);

label291: ;
	Compare(0x8000, 0);
	if (1) goto label301;
	EventGreyMessage(17, 2);

label301: ;
	SetVarFlagStatus(2286, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label311;
	SetVarEqVal(0x8000, 0);
	goto label321;

label311: ;
	SetVarEqVal(0x8000, 1);

label321: ;
	Compare(0x8000, 0);
	if (1) goto label331;
	EventGreyMessage(18, 2);

label331: ;
	CloseAllMessageBoxes();
	goto label341;

label231: ;
	Message2(1024, 14, 0, 0);
	WaitForButton();
	CloseMessageBox();

label341: ;
	goto label111;

label121: ;
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

label111: ;
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
	if (255) goto label21;
	SetWordPlayerName(0);
	BubbleMessage(8, 2);
	goto label22;

label21: ;
	StoreFlag(2477);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label23;
	BubbleMessage(9, 2);
	goto label22;

label23: ;
	BubbleMessage(10, 2);

label22: ;
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
	if (255) goto label24;
	SetNPCPosition(0, 25, 20, 17, 2);
	goto label25;

label24: ;
	StoreFlag(266);
	StackPushConst(1);
	StackCompare(1);
	StackPushVar(0x409D);
	StackPushConst(1);
	StackCompare(1);
	StackCompare(7);
	if (255) goto label25;
	SetNPCPosition(0, 27, 20, 16, 1);

label25: ;
	End();
}

void Sequence10()
{
	SetVarFlagStatus(109, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label40;
	SetVarEqVal(0x8000, 0);
	goto label41;

label40: ;
	SetVarEqVal(0x8000, 1);

label41: ;
	Compare(0x8000, 0);
	if (1) goto label42;
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

label42: ;
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine0()
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