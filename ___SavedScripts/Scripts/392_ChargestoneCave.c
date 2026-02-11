#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message(1024, 0, 0, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence1()
{
	LockAll();
	SetVarFlagStatus(296, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label0;
	PlaySound(1351);
	FacePlayer();
	Message(1024, 5, 2, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	goto label1;

label0: ;
	Routine0();

label1: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence2()
{
	LockAll();
	SetVarFlagStatus(296, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label6;
	PlaySound(1351);
	FacePlayer();
	Message(1024, 6, 1, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	goto label7;

label6: ;
	Routine0();

label7: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence3()
{
	LockAll();
	SetVarFlagStatus(521, 0x8000);
	Compare(0x8000, 0);
	if (5) goto label8;
	ClearFlag(2191);
	ClearFlag(2063);
	ClearFlag(2113);
	ClearFlag(2013);
	ClearFlag(2259);
	ClearFlag(2260);
	ClearFlag(2262);
	ClearFlag(2264);
	ClearFlag(2065);
	ClearFlag(2067);
	SetFlag(522);
	QuicksandWarp(196, 44, 48);
	goto label9;

label8: ;
	QuicksandWarp(195, 59, 14);

label9: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence4()
{
	LockAll();
	QuicksandWarp(197, 24, 6);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence5()
{
	LockAll();
	QuicksandWarp(197, 20, 34);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence6()
{
	LockAll();
	SetWordPlayerName(0);
	GetHeroPosition(0x8004, 0x8005);

	Movement m[] = { //0
		Exclaimation, 1,
	};

	WaitMovement();
	NPCPathFind(0, 48, 0x8005, 1, 8, 1);

	Movement m[] = { //0
		TurnLeft, 1,
	};

	WaitMovement();
	Message(1024, 7, 0, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	StartTrainerBattle(593, 0, 0);
	TrainerBattleEnd();
	GetTrainerBattleResult(0x8000);
	SetVarEqVar(0x8007, 0x8000);
	Compare(0x8007, 1);
	if (1) goto label10;
	TrainerBattleLose();

label10: ;
	SetWordPlayerName(0);
	Message(1024, 8, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();

	Movement m[] = { //0
		TurnDown, 1,
	};

	WaitMovement();
	Message(1024, 9, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();
	Compare(0x4042, 6);
	if (5) goto label11;

	Movement m[] = { //0
		TurnLeft, 1,
	};


	Movement m[] = { //255
		Ellipses, 1,
	};

	WaitMovement();
	ReturnAfterDelay(32);

	Movement m[] = { //0
		QuestionMark, 1,
	};

	WaitMovement();
	ReturnAfterDelay(32);
	Compare(0x4043, 2);
	if (5) goto label12;
	Message(1024, 13, 0, 0, 0);
	goto label13;

label12: ;
	Message(1024, 12, 0, 0, 0);

label13: ;
	WaitForButton();
	CloseMessageBox();
	Message(1024, 14, 0, 0, 0);
	SetVarEqVar2(0x4042, 7);
	WaitForButton();
	CloseMessageBox();

label11: ;
	NPCPathFind(0, 51, 5, 1, 8, 1);
	WaitMovement();

	Movement m[] = { //0
		TurnLeft, 1,
	};

	WaitMovement();
	Compare(0x4042, 7);
	if (5) goto label14;
	Message(1024, 11, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label15;

label14: ;
	Message(1024, 10, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();

label15: ;

	Movement m[] = { //0
		WalkRight, 2,
	};

	ReturnAfterDelay(16);
	PlaySound(1369);
	RemoveNPC(0);
	SetFlag(521);
	SetVarEqVar2(0x404C, 1);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence7()
{
	SetVarFlagStatus(522, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label16;
	ClearFlag(522);

label16: ;
	SetVarFlagStatus(536, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label17;
	SetVarEqVal(0x8000, 0);
	goto label18;

label17: ;
	SetVarEqVal(0x8000, 1);

label18: ;
	Compare(0x8000, 0);
	if (1) goto label19;
	SetFlag(536);

label19: ;
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence8()
{
	LockAll();
	PlaySound(1351);

	Movement m[] = { //19
		Exclaimation, 1,
	};

	WaitMovement();
	GetHeroPosition(0x8004, 0x8005);
	SubtractVar(0x8004, 1);
	NPCPathFind(19, 0x8004, 0x8005, 1, 8, 0);
	WaitMovement();
	ReturnAfterDelay(100);
	Message(1024, 15, 19, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	StartTrainerBattle(493, 0, 0);
	GetTrainerBattleResult(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 1);
	if (1) goto label20;
	TrainerBattleLose();

label20: ;
	TrainerBattleEnd();
	Message(1024, 16, 19, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVar2(0x4067, 1);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence9()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message(1024, 16, 19, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine0()
{
	PlaySound(1351);
	GetPlayerDirection(0x8000);
	SetVarEqVar(0x8006, 0x8000);
	Compare(0x8006, 2);
	if (5) goto label2;

	Movement m[] = { //2
		TurnRight, 1,
	};

	goto label3;

label2: ;
	Compare(0x8006, 3);
	if (5) goto label3;

	Movement m[] = { //2
		TurnLeft, 1,
	};

	goto label3;

label3: ;
	WaitMovement();
	Message(1024, 1, 2, 5, 0);
	CloseAllMessageBoxes();
	Compare(0x8006, 2);
	if (5) goto label4;

	Movement m[] = { //1
		TurnRight, 1,
	};

	goto label5;

label4: ;
	Compare(0x8006, 3);
	if (5) goto label5;

	Movement m[] = { //1
		TurnLeft, 1,
	};

	goto label5;

label5: ;
	WaitMovement();
	Message(1024, 2, 1, 3, 0);
	CloseAllMessageBoxes();
	Message(1024, 3, 2, 5, 0);
	CloseAllMessageBoxes();
	StackPushVar(0x8004);
	StackPushVar(0x8005);
	StackPushVar(0x8006);
	SetVarEqVal(0x8007, 92);
	SetVarEqVal(0x8008, 1);
	SetVarEqVar(0x8000, 0x8007);
	SetVarEqVar(0x8001, 0x8008);
	CallGlobalScript(2805);
	StackPop(0x8006);
	StackPop(0x8005);
	StackPop(0x8004);
	Message(1024, 4, 1, 3, 0);
	CloseAllMessageBoxes();
	StackPushVar(0x8004);
	StackPushVar(0x8005);
	StackPushVar(0x8006);
	SetVarEqVal(0x8007, 581);
	SetVarEqVal(0x8008, 1);
	SetVarEqVar(0x8000, 0x8007);
	SetVarEqVar(0x8001, 0x8008);
	CallGlobalScript(2805);
	StackPop(0x8006);
	StackPop(0x8005);
	StackPop(0x8004);
	Message(1024, 5, 2, 5, 0);
	WaitForABInput();
	CloseAllMessageBoxes();
	Message(1024, 6, 1, 3, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetFlag(296);
	SetVarEqVal(0x8000, 0);
	Return();
}
