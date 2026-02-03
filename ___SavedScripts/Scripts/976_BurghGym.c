#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	LockAll();
	Routine0();
	TeleportWarp2(29, 4, 20, 13, 1);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence1()
{
	LockAll();
	Routine0();
	TeleportWarp2(29, 8, 0, 4, 2);
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence2()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	StoreBadge(0x8008, 2);
	StackPushVar(0x8008);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label0;
	Routine1();
	goto label1;

label0: ;
	StoreFlag(2400);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label2;
	Message(1024, 5, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();
	goto label1;

label2: ;
	Message(1024, 6, 0, 0, 0);
	WaitForButton();
	CloseMessageBox();

label1: ;
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
{
	SetVarEqVal(0x8020, 0);
	GetPlayerDirection(0x8020);
	Compare(0x8020, 0);
	if (1) goto label3;
	goto label4;

label3: ;

	Movement m[] = { //255
		JumpUp1, 1,
		Vanish, 1,
	};

	goto label5;

label4: ;
	Compare(0x8020, 1);
	if (1) goto label6;
	goto label7;

label6: ;

	Movement m[] = { //255
		JumpDown1, 1,
		Vanish, 1,
	};

	goto label5;

label7: ;
	Compare(0x8020, 2);
	if (1) goto label8;
	goto label9;

label8: ;

	Movement m[] = { //255
		JumpLeft1, 1,
		Vanish, 1,
	};

	goto label5;

label9: ;
	Compare(0x8020, 3);
	if (1) goto label10;
	goto label5;

label10: ;

	Movement m[] = { //255
		JumpRight1, 1,
		Vanish, 1,
	};

	goto label5;

label5: ;
	WaitMovement();
	FadeIntoBlack2();
	WaitFade();
	SetVarEqVal(0x8020, 0);
	Return();
}

void Routine1()
{
	Message2(1024, 0, 0, 0);
	CloseMessageBox();
	SetVarEqVal(0x8021, 0);
	StoreDifficulty(0x8021);
	StackPushVar(0x8021);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label11;
	StartTrainerBattle(766, 0, 0);
	goto label12;

label11: ;
	StartTrainerBattle(154, 0, 0);

label12: ;
	SetVarEqVal(0x8021, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label13;
	TrainerBattleEnd();
	goto label14;

label13: ;
	TrainerBattleLose();

label14: ;
	Message2(1024, 1, 0, 0);
	CloseMessageBox();
	c0x11E(2);
	GiveBadge(2);
	SetWordPlayerName(0);
	PlayFanfare(1306);
	SetVarEqVal(0x8022, 0);
	GetHeroGender(0x8022);
	StackPushVar(0x8022);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label15;
	c0x19B(5);
	goto label16;

label15: ;
	c0x19B(57);

label16: ;
	WaitFanfare();
	SetVarEqVal(0x8022, 0);
	EventGreyMessage(2, 0);
	CloseEventGreyMessage();
	Message2(1024, 3, 0, 0);
	CloseMessageBox();
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	SetVarEqVar2(0x8000, 403);
	SetVarEqVar2(0x8001, 1);
	CallGlobalScript(2805);
	StackPop(0x8001);
	StackPop(0x8000);
	Message2(1024, 4, 0, 0);
	WaitForButton();
	CloseMessageBox();
	SetFlag(2416);
	SetVarEqVal(0x40B4, 1);
	ClearFlag(756);
	c0x262(1, 5);
	SetFlag(753);
	SetVarEqVal(0x40B2, 4);
	DeactiveTrainerId(737);
	Return();
}
