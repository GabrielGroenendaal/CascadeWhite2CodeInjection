#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	StoreBadge(0x8008, 1);
	StackPushVar(0x8008);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label0;
	StoreFlag(270);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label1;
	SetVarEqVal(0x4000, 1);
	SetVarEqVal(0x4003, 1);
	goto label2;

label1: ;
	SetVarEqVal(0x4000, 0);
	SetVarEqVal(0x4003, 0);

label2: ;
	StoreFlag(271);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label3;
	SetVarEqVal(0x4001, 1);
	goto label4;

label3: ;
	SetVarEqVal(0x4001, 0);

label4: ;
	goto label5;

label0: ;
	SetVarEqVal(0x4000, 0);
	SetVarEqVal(0x4001, 0);

label5: ;
	StoreFlag(763);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label6;
	SetVarEqVal(0x4000, 1);
	SetVarEqVal(0x4001, 1);
	SetVarEqVal(0x4002, 1);
	SetVarEqVal(0x4003, 1);

label6: ;
	End();
}

void Sequence1()
{
	StackPushVar(0x4000);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label7;
	c0x292(1);

label7: ;
	StackPushVar(0x4001);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label8;
	c0x292(2);

label8: ;
	End();
}

void Sequence2()
{
	LockAll();
	StackPushVar(0x4000);
	StackPushConst(0);
	StackCompare(1);
	StackPushVar(0x4001);
	StackPushConst(0);
	StackCompare(1);
	StackCompare(6);
	if (255) goto label9;
	PlaySound(1351);
	SetWordPlayerName(0);
	BubbleMessage(0, 2);
	WaitForButton();
	CloseAllMessageBoxes();
	goto label10;

label9: ;
	PlaySound(1351);
	FacePlayer();
	Routine0();
	StoreBadge(0x8008, 1);
	StackPushVar(0x8008);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label11;
	Routine1();
    SetVarEqVal(0x4052, 28);
    Compare(0x4051, 0);
    if (1) goto label_LevelCapsEnabled;
    goto label_LevelCapsNotEnabled;

label_LevelCapsEnabled: ; 
    EventGreyMessage(18, 2);
    CloseEventGreyMessage();

label_LevelCapsNotEnabled: ;
	goto label10;

label11: ;
	c0x291(0);
	c0x291(1);
	c0x291(2);
	StoreFlag(2400);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label12;
	Message(1024, 6, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label10;

label12: ;
	Message(1024, 8, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();

label10: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence3()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 6, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence4()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarEqVal(0x8020, 178);
	StoreFlag(270);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label13;
	Routine2();
	Routine3();
	goto label14;

label13: ;
	Routine4();
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label15;
	TrainerBattleEnd();
	Routine3();
	SetFlag(270);
	goto label16;

label15: ;
	TrainerBattleLose();

label16: ;
	DeactiveTrainerId(0x8020);

label14: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence5()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarEqVal(0x8020, 179);
	StoreFlag(271);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label17;
	Routine2();
	Routine5();
	goto label18;

label17: ;
	Routine4();
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label19;
	TrainerBattleEnd();
	Routine5();
	SetFlag(271);
	goto label20;

label19: ;
	TrainerBattleLose();

label20: ;
	DeactiveTrainerId(0x8020);

label18: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence6()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 9, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence7()
{
	LockAll();
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8027, 0);
	GetHeroPosition(0x8026, 0x8027);
	SetNPCPosition(3, 13, 0, 6, 2);
	ChangeMusic(1203);
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(1);
	if (255) goto label21;

	Movement m[] = { //3
		WalkLeft, 9,
	};

	goto label22;

label21: ;

	Movement m[] = { //3
		WalkLeft, 8,
	};


label22: ;
	WaitMovement();

	Movement m[] = { //255
		TurnRight, 1,
	};

	WaitMovement();
	Message(1024, 10, 3, 0, 0);
	CloseAllMessageBoxes();
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(1);
	if (255) goto label23;

	Movement m[] = { //3
		WalkRight, 10,
	};

	ReturnAfterDelay(10);
	goto label24;

label23: ;

	Movement m[] = { //3
		WalkRight, 9,
	};

	ReturnAfterDelay(10);

label24: ;
	FadeToDefaultMusic();
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(1);
	if (255) goto label25;
	ReturnAfterDelay(30);

	Movement m[] = { //4
		WalkLeft, 1,
		WalkDown, 1,
		WalkLeft, 3,
		WalkDown, 2,
		TurnLeft, 1,
	};

	goto label26;

label25: ;
	ReturnAfterDelay(30);

	Movement m[] = { //4
		WalkLeft, 1,
		WalkDown, 1,
		WalkLeft, 4,
		WalkDown, 2,
		TurnRight, 1,
	};


label26: ;
	WaitMovement();
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(1);
	if (255) goto label27;
	goto label28;

label27: ;

	Movement m[] = { //255
		TurnLeft, 1,
	};

	WaitMovement();

label28: ;
	Message(1024, 7, 4, 0, 0);
	CloseAllMessageBoxes();
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(1);
	if (255) goto label29;

	Movement m[] = { //4
		WalkRight, 10,
	};

	goto label30;

label29: ;

	Movement m[] = { //4
		WalkDown, 1,
		WalkRight, 10,
	};

	ReturnAfterDelay(20);

	Movement m[] = { //255
		TurnRight, 1,
	};


label30: ;
	WaitMovement();
	RemoveNPC(3);
	RemoveNPC(4);
	SetVarEqVal(0x40AD, 2);
	SetFlag(721);
	SetFlag(720);
	SetFlag(725);
    SetFlag(560);
	SetVarEqVal(0x40AC, 4);
	ClearFlag(724);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence8()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 11, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
{
	c0xA5(0x8010, 3);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label31;
	c0xA4(3);
	SetVarEqVal(0x4002, 1);

label31: ;
	Return();
}

void Routine1()
{
	Message(1024, 1, 0, 0, 1);
	CloseAllMessageBoxes();
	SetVarEqVal(0x8024, 0);
	StoreDifficulty(0x8024);
	StackPushVar(0x8024);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label32;
	StartTrainerBattle(765, 0, 0);
	goto label33;

label32: ;
	StartTrainerBattle(157, 0, 0);

label33: ;
	SetVarEqVal(0x8024, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label34;
	SetFlag(763);
	ClearFlag(721);
	RemoveNPC(0);
	AddNPC(4);
	GetPlayerDirection(0x8010);
	Compare(0x8010, 1);
	if (1) goto label35;
	goto label36;

label35: ;

	Movement m[] = { //4
		LookUp, 1,
	};

	goto label37;

label36: ;
	Compare(0x8010, 2);
	if (1) goto label38;
	goto label39;

label38: ;

	Movement m[] = { //4
		LookRight, 1,
	};

	goto label37;

label39: ;
	Compare(0x8010, 3);
	if (1) goto label40;
	goto label37;

label40: ;

	Movement m[] = { //4
		LookLeft, 1,
	};

	goto label37;

label37: ;
	WaitMovement();
	TrainerBattleEnd();
	goto label41;

label34: ;
	TrainerBattleLose();

label41: ;
	Routine0();
	c0x291(0);
	c0x291(1);
	c0x291(2);
	Message(1024, 2, 4, 0, 0);
	CloseMessageBox();
	c0x11E(1);
	GiveBadge(1);
	SetWordPlayerName(0);
	PlayFanfare(1306);
	SetVarEqVal(0x8025, 0);
	GetHeroGender(0x8025);
	StackPushVar(0x8025);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label42;
	c0x19B(4);
	goto label43;

label42: ;
	c0x19B(56);

label43: ;
	WaitFanfare();
	SetVarEqVal(0x8025, 0);
	EventGreyMessage(3, 0);
	CloseEventGreyMessage();
	Message(1024, 4, 4, 0, 0);
	CloseMessageBox();
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 336);
	SetVarEqVar2(0x8001, 1);
	CallGlobalScript(2805);
	StackPop(0x8001);
	StackPop(0x8000);
	Message(1024, 5, 4, 0, 0);
	WaitForButton();
	CloseMessageBox();
	DeactiveTrainerId(178);
	DeactiveTrainerId(179);
	SetVarEqVal(0x40AD, 1);
	SetVarEqVal(0x410A, 1);
	SetVarEqVal(0x40AC, 3);
	SetFlag(725);
	SetFlag(2415);
	Return();
}

void Routine2()
{
	c0x88(0x8021, 0x8022, 0x8023);
	c0x87(0x8020, 0x8022, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine3()
{
	c0xA5(0x8010, 1);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label44;
	c0xA4(1);
	c0xA4(4);
	c0x292(1);
	SetVarEqVal(0x4000, 1);
	SetVarEqVal(0x4003, 1);

label44: ;
	Return();
}

void Routine4()
{
	c0x88(0x8021, 0x8022, 0x8023);
	c0x87(0x8020, 0x8021, 0x8011);
	CloseMessageBox();
	StartTrainerBattle(0x8020, 0, 0);
	Return();
}

void Routine5()
{
	c0xA5(0x8010, 2);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label45;
	c0xA4(2);
	c0x292(2);
	SetVarEqVal(0x4001, 1);

label45: ;
	Return();
}