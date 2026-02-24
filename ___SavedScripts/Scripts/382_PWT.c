#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"

void Sequence0()
{
	LockAll();
	GetHeroPosition(0x8004, 0x8005);
	Compare(0x8005, 466);
	if (1) goto label0;
	Compare(0x8005, 467);
	if (1) goto label1;
	goto label2;

label1: ;

	Movement m[] = { //255
		WalkDown, 2,
		WalkRight, 6,
	};

	WaitMovement();
	goto label3;

label0: ;

	Movement m[] = { //255
		WalkDown, 3,
		WalkRight, 6,
	};

	WaitMovement();
	goto label3;

label2: ;
	Compare(0x8005, 468);
	if (1) goto label4;
	NPCPathFind(255, 197, 469, 0, 8, 0);
	WaitMovement();
	goto label3;

label4: ;

	Movement m[] = { //255
		WalkDown, 1,
		WalkRight, 6,
	};

	WaitMovement();

label3: ;

	Movement m[] = { //6
		TurnDown, 1,
	};


	Movement m[] = { //7
		TurnDown, 1,
	};

	Compare(0x8005, 469);
	if (3) goto label5;
	goto label6;

label5: ;

	Movement m[] = { //255
		TurnUp, 1,
	};


label6: ;
	WaitMovement();
	Message(1024, 0, 7, 0, 0);
	CloseAllMessageBoxes();

	Movement m[] = { //6
		TurnUp, 1,
	};


	Movement m[] = { //7
		TurnUp, 1,
	};

	StartCameraEvent();
	LockCamera();
	MoveCamera(8024, 0, 0xED000, 0xC58000, 0, 0x1CE3000, 40);
	EndCameraEvent();
	WaitMovement();
	BubbleMessage(1, 2);
	CloseBubbleMessage();
	ResetCamera(40);
	EndCameraEvent();
	ReleaseCamera();
	StopCameraEvent();

	Movement m[] = { //7
		WalkLeft, 1,
		WalkUp, 3,
	};

	WaitMovement();
	PlaySound(1369);
	RemoveNPC(7);
	WaitSound();

	Movement m[] = { //255
		WalkUp, 4,
	};

	ReturnAfterDelay(12);

	Movement m[] = { //6
		WalkRight, 1,
		WalkUp, 2,
	};

	WaitMovement();
	SetVarEqVar2(0x40C6, 1);
	SetFlag(711);
	SetFlag(713);
	SetFlag(1000);
	c0x21(8);
	MapChangeWarp(192, 15, 26, 0);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence1()
{
	LockAll();
	ClearFlag(711);
	ClearFlag(712);
	ClearFlag(710);
	StartCameraEvent();
	LockCamera();
	MoveCamera(9688, 0, 0xED000, 0xC58000, 0, 0x1D48000, 10);

	Movement m[] = { //255
		WalkDown, 4,
		TurnUp, 1,
	};

	ReturnAfterDelay(12);
	PlaySound(1369);
	AddNPC(6);
	WaitSound();

	Movement m[] = { //6
		WalkDown, 3,
		WalkLeft, 1,
		TurnRight, 1,
	};

	ReturnAfterDelay(12);
	AddNPC(8);

	Movement m[] = { //8
		WalkDown, 3,
		WalkRight, 1,
		TurnLeft, 1,
	};

	EndCameraEvent();
	WaitMovement();
	SetWordPlayerName(0);
	Message(1024, 2, 8, 0, 0);
	CreateNPC(186, 470, 2, 251, 293, 0);

	Movement m[] = { //251
		FastWalkRight, 10,
		FastWalkDown, 10,
	};

	ReturnAfterDelay(48);

	Movement m[] = { //6
		TurnDown, 1,
		Exclaimation, 1,
	};

	WaitMovement();
	CloseAllMessageBoxes();

	Movement m[] = { //255
		TurnDown, 1,
	};


	Movement m[] = { //8
		TurnDown, 1,
	};

	WaitMovement();
	SetWordRivalName(1);
	Message(1024, 3, 6, 0, 0);
	CloseAllMessageBoxes();

	Movement m[] = { //8
		TurnLeft, 1,
	};


	Movement m[] = { //255
		TurnUp, 1,
	};

	WaitMovement();
	Message(1024, 4, 6, 0, 0);
	CloseAllMessageBoxes();
	BubbleMessage(5, 1);
	CloseAllMessageBoxes();
	PlaySound(1369);
	AddNPC(9);
	WaitSound();
	ChangeMusic(1238);

	Movement m[] = { //9
		WalkDown, 1,
		WalkLeft, 1,
		TurnDown, 1,
	};

	ReturnAfterDelay(8);

	Movement m[] = { //6
		TurnUp, 1,
	};


	Movement m[] = { //8
		TurnUp, 1,
	};

	WaitMovement();
	Message(1024, 6, 9, 0, 0);
	CloseAllMessageBoxes();
	Message(1024, 7, 6, 0, 0);
	CloseAllMessageBoxes();
	NPCPathFind(6, 196, 480, 1, 4, 1);
	ReturnAfterDelay(12);

	Movement m[] = { //8
		TurnDown, 1,
	};


	Movement m[] = { //255
		TurnDown, 1,
	};

	WaitMovement();

	Movement m[] = { //255
		TurnUp, 1,
	};

	WaitMovement();
	Message(1024, 8, 8, 0, 0);
	CloseAllMessageBoxes();
	NPCPathFind(8, 196, 480, 1, 8, 1);
	ReturnAfterDelay(24);

	Movement m[] = { //255
		TurnDown, 1,
	};

	WaitMovement();

	Movement m[] = { //9
		WalkRight, 1,
		WalkDown, 2,
	};

	ReturnAfterDelay(8);

	Movement m[] = { //255
		TurnUp, 1,
	};

	WaitMovement();
	Message(1024, 9, 9, 0, 0);
	CloseAllMessageBoxes();
	ResetCamera(10);
	EndCameraEvent();
	ReleaseCamera();
	StopCameraEvent();
	FadeToDefaultMusic();
	RemoveNPC(6);
	RemoveNPC(8);
	RemoveNPC(251);
	SetVarEqVar2(0x40C6, 3);
	SetFlag(711);
	SetFlag(712);
	SetFlag(890);
	ClearFlag(830);
	ClearFlag(831);
	ClearFlag(829);
	SetVarEqVar2(0x40F0, 1);
	c0x262(1, 15);
	c0x262(2, 3);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence2()
{
	LockAll();

	Movement m[] = { //6
		TurnLeft, 1,
		TurnRight, 1,
		TurnLeft, 1,
		TurnRight, 1,
	};

	WaitMovement();
	SetWordRivalName(1);
	SetWordRivalName(1);
	Message(1024, 11, 6, 0, 0);
	CloseAllMessageBoxes();
	NPCPathFind(6, 196, 476, 1, 4, 1);
	WaitMovement();
	RemoveNPC(6);

	Movement m[] = { //8
		TurnRight, 1,
	};

	WaitMovement();
	Message(1024, 12, 8, 0, 0);
	CloseAllMessageBoxes();

	Movement m[] = { //8
		QuestionMark, 1,
	};


	Movement m[] = { //8
		TurnLeft, 1,
	};

	WaitMovement();
	GetPartyCount(0x8000, 2);
	SetVarEqVar(0x8004, 0x8000);
	AddToVar(0x8004, 1);
	SetWordNumber(0, 0x8004, 1);
	Message(1024, 39, 8, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	ReturnAfterDelay(48);

	Movement m[] = { //255
		Exclaimation, 1,
	};


	Movement m[] = { //255
		HopRight, 1,
	};

	WaitMovement();
	ReturnAfterDelay(20);
	SetWordDaycarePokemon(0, 0);
	EventGreyMessage(40, 2);
	WaitMessage();
	CloseAllMessageBoxes();

	Movement m[] = { //8
		WalkLeft, 2,
		TurnUp, 1,
	};


	Movement m[] = { //255
		TurnUp, 1,
	};

	WaitMovement();
	SetWordPlayerName(0);
	Message(1024, 41, 8, 0, 0);
	CloseAllMessageBoxes();
	ReturnAfterDelay(20);

	Movement m[] = { //8
		WalkRight, 1,
		TurnDown, 1,
	};

	WaitMovement();
	SetWordPlayerName(0);
	Message(1024, 42, 8, 0, 0);

	Movement m[] = { //8
		TurnUp, 1,
	};

	WaitMovement();
	SetWordPlayerName(0);
	Message(1024, 13, 8, 0, 0);
	CloseAllMessageBoxes();
	NPCPathFind(8, 197, 476, 1, 8, 1);
	WaitMovement();
	RemoveNPC(8);
	SetVarEqVar2(0x40C6, 5);
	SetFlag(711);
	SetFlag(712);
	ClearFlag(772);
	ClearFlag(775);
	SetVarEqVar2(0x4135, 3);
	SetVarEqVar2(0x40C9, 1);
	SetVarEqVar2(0x40CA, 1);
	SetFlag(962);
	SetFlag(515);
	c0x262(2, 5);
	c0x262(1, 17);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence3()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 10, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence4()
{
	Routine0();
	Compare(0x40C6, 3);
	if (1) goto label7;
	SetVarEqVal(0x8000, 0);
	Return();

label7: ;
	c0x1D9(9, 1, 197, 0, 468);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence5()
{
	Compare(0x40C6, 0);
	if (1) goto label9;
	Compare(0x40C6, 4);
	if (1) goto label10;
	SetVarEqVal(0x8000, 0);
	Return();

label10: ;
	SetNPCPosition(6, 196, 0xFFFF, 490, 3);
	SetNPCPosition(8, 198, 0xFFFF, 490, 2);
	SetVarEqVal(0x8000, 0);
	Return();

label9: ;
	SetNPCPosition(6, 196, 0, 468, 0);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence6()
{
	LockAll();
	SetVarEqVal(0x8004, 540);
	SetVarEqVal(0x8005, 1);
	SetVarEqVal(0x8006, 448);
	SetVarEqVal(0x8007, 14);
	SetVarEqVal(0x8008, 15);
	SetVarEqVal(0x8009, 15);
	StoreVarItem(0x8000);
	SetVarEqVar(0x800A, 0x8000);
	StackPushVar(0x8004);
	StackPushVar(0x8005);
	StackPushVar(0x8006);
	StackPushVar(0x8007);
	StackPushVar(0x8008);
	StackPushVar(0x8009);
	StackPushVar(0x800A);
	SetVarEqVar(0x800B, 0x8004);
	SetVarEqVar(0x800C, 0x8005);
	SetVarEqVar(0x800D, 0x8006);
	SetVarEqVar(0x800E, 0x8007);
	SetVarEqVar(0x800F, 0x8008);
	SetVarEqVar(0x8010, 0x8009);
	SetVarEqVar(0x8011, 0x800A);
	SetVarEqVar(0x8000, 0x800B);
	SetVarEqVar(0x8001, 0x800C);
	SetVarEqVar(0x8002, 0x800D);
	SetVarEqVar(0x8003, 0x800E);
	SetVarEqVar(0x8004, 0x800F);
	SetVarEqVar(0x8005, 0x8010);
	SetVarEqVar(0x8006, 0x8011);
	CallGlobalScript(2800);
	StackPop(0x800A);
	StackPop(0x8009);
	StackPop(0x8008);
	StackPop(0x8007);
	StackPop(0x8006);
	StackPop(0x8005);
	StackPop(0x8004);
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence7()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 17, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence8()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 21, 0, 0);
	WaitForButton();
	CloseMessageBox();
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
	Message2(1024, 22, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence10()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 23, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence11()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 24, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence12()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 25, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence13()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarFlagStatus(135, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label11;
	Message2(1024, 27, 0, 0);
	goto label12;

label11: ;
	Message2(1024, 26, 0, 0);
	SetFlag(135);

label12: ;
	YesNoBox(0x8000);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 1);
	if (1) goto label13;
	CloseMessageBox();
	StackPushVar(0x8004);
	Routine1();
	StackPop(0x8004);
	goto label14;

label13: ;
	Message2(1024, 30, 0, 0);

label14: ;
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence14()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 34, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence15()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Message2(1024, 33, 0, 0);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence16()
{
	Routine0();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence17()
{
	LockAll();
	c0x276(17, 0);
	PlaySound(1351);
	BorderedMessage(36, 2);
	CloseBorderedMessage();
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence18()
{
	LockAll();
	PlaySound(1351);
	EventGreyMessage(35, 1);
	WaitForButton();
	CloseMessageBox();
	WaitMoment();
	SetVarEqVar2(0x4157, 1);
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Sequence19()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	SetVarFlagStatus(512, 0x8000);
	Compare(0x8000, 0);
	if (1) goto label20;
	SetVarEqVal(0x8000, 0);
	goto label21;

label20: ;
	SetVarEqVal(0x8000, 1);

label21: ;
	Compare(0x8000, 0);
	if (1) goto label22;
	Message2(1024, 70, 0, 0);
	SetFlag(512);

label22: ;
	Message2(1024, 43, 0, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 0);
	if (1) goto label23;
	Message2(1024, 44, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	goto label24;

label23: ;
	CloseAllMessageBoxes();
	StoreItemCount(530, 0x8000);
	SetVarEqVar(0x8005, 0x8000);
	Compare(0x8005, 0);
	if (5) goto label25;
	Message2(1024, 45, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	goto label24;

label25: ;
	Message2(1024, 46, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	OpenChoosePokemonMenu(0, 0x800A, 0x800B, 0);
	Compare(0x800A, 1);
	if (1) goto label26;
	Message2(1024, 47, 0, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	goto label24;

label26: ;
	SetVarEqVal(0x8007, 0);

label35: ;
	Compare(0x8007, 0);
	if (5) goto label27;
	Message2(1024, 68, 2, 0);
	SetupDialogueSelection(31, 5, 0, 1, 0x8006);
	GetPokemonParam(0x8000, 0x800B, 70);
	SetVarEqVar(0x800E, 0x8000);
	Compare(0x800E, 31);
	if (4) goto label28;
	AddDialogueOption(48, 0xFFFF, 0);

label28: ;
	GetPokemonParam(0x8000, 0x800B, 71);
	SetVarEqVar(0x800E, 0x8000);
	Compare(0x800E, 31);
	if (4) goto label29;
	AddDialogueOption(49, 0xFFFF, 1);

label29: ;
	GetPokemonParam(0x8000, 0x800B, 72);
	SetVarEqVar(0x800E, 0x8000);
	Compare(0x800E, 31);
	if (4) goto label30;
	AddDialogueOption(50, 0xFFFF, 2);

label30: ;
	GetPokemonParam(0x8000, 0x800B, 74);
	SetVarEqVar(0x800E, 0x8000);
	Compare(0x800E, 31);
	if (4) goto label31;
	AddDialogueOption(51, 0xFFFF, 3);

label31: ;
	GetPokemonParam(0x8000, 0x800B, 75);
	SetVarEqVar(0x800E, 0x8000);
	Compare(0x800E, 31);
	if (4) goto label32;
	AddDialogueOption(52, 0xFFFF, 4);

label32: ;
	GetPokemonParam(0x8000, 0x800B, 73);
	SetVarEqVar(0x800E, 0x8000);
	Compare(0x800E, 31);
	if (4) goto label33;
	AddDialogueOption(53, 0xFFFF, 5);

label33: ;
	AddDialogueOption(54, 0xFFFF, 6);
	ShowDialogueSelection();
	Compare(0x8006, 6);
	if (5) goto label34;
	Message2(1024, 47, 2, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVal(0x8007, 1);
	goto label35;
	goto label27;

label34: ;
	SetVarEqVal(0x8001, 7);
	SetVarEqVar(0x8000, 0x8006);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(0);
	StackPop(0x8000);
	StackPushVar(0x8000);
	SetVarEqVal(0x8001, 0);
	SetVarEqVar(0x8000, 0x8006);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(4);
	StackPop(0x8000);
	SetVarEqVar(0x8001, 0x8000);
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 0x8001);
	Compare(0x8000, 0);
	if (1) goto label36;
	Compare(0x8006, 0);
	if (5) goto label37;
	SetVarEqVal(0x8008, 56);
	SetVarEqVal(0x8009, 0);

label37: ;
	Compare(0x8006, 1);
	if (5) goto label38;
	SetVarEqVal(0x8008, 58);
	SetVarEqVal(0x8009, 1);

label38: ;
	Compare(0x8006, 2);
	if (5) goto label39;
	SetVarEqVal(0x8008, 60);
	SetVarEqVal(0x8009, 2);

label39: ;
	Compare(0x8006, 3);
	if (5) goto label40;
	SetVarEqVal(0x8008, 62);
	SetVarEqVal(0x8009, 4);

label40: ;
	Compare(0x8006, 4);
	if (5) goto label41;
	SetVarEqVal(0x8008, 64);
	SetVarEqVal(0x8009, 5);

label41: ;
	Compare(0x8006, 5);
	if (5) goto label42;
	SetVarEqVal(0x8008, 66);
	SetVarEqVal(0x8009, 3);

label42: ;
	Message2(1024, 0x8008, 2, 0);
	YesNoBox(0x8000);
	SetVarEqVar(0x800D, 0x8000);
	Compare(0x800D, 0);
	if (5) goto label43;
	CloseAllMessageBoxes();
	SetVarEqVar(0x800F, 0x8008);
	AddToVar(0x800F, 1);
	EventGreyMessage(0x800F, 2);
	WaitMessage();
	CloseAllMessageBoxes();
	TakeItem(530, 1, 0x8000);
	SetVarEqVal(0x800F, 70);
	AddToVar(0x800F, 0x8006);
	SetPokemonIV(0x800B, 0x800F, 31);
	Message2(1024, 69, 2, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVal(0x8007, 1);
	goto label35;

label43: ;
	goto label35;
	goto label27;

label36: ;
	Message2(1024, 55, 2, 0);
	WaitForButton();
	CloseAllMessageBoxes();
	SetVarEqVal(0x8007, 1);
	goto label35;

label27: ;
	CloseAllMessageBoxes();

label24: ;
	WaitMoment();
	UnlockAll();
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine0()
{
	SetVarEqVal(0x8001, 2);
	SetVarEqVar(0x8000, 0x40C6);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(4);
	StackPop(0x8000);
	StackPushVar(0x8000);
	SetVarEqVal(0x8001, 3);
	SetVarEqVar(0x8000, 0x40C6);
	StackPushVar(0x8000);
	StackPushVar(0x8001);
	StackCompare(3);
	StackPop(0x8000);
	SetVarEqVar(0x8001, 0x8000);
	StackPop(0x8000);
	BitwiseAndVar(0x8000, 0x8001);
	Compare(0x8000, 0);
	if (1) goto label8;
	SetVarEqVal(0x8000, 0);
	Return();

label8: ;
	c0x1D8(3, 202, 0, 492);
	SetVarEqVal(0x8000, 0);
	Return();
}

void Routine1()
{
	SetVarEqVal(0x8005, 0);
	OpenChoosePokemonMenu(0, 0x8004, 0x8005, 0);
	Compare(0x8004, 0);
	if (1) goto label15;
	GetPartyIsEgg(0x8000, 0x8005);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 1);
	if (1) goto label16;
	GetHiddenPowerType(0x8000, 0x8005);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 17);
	if (4) goto label17;
	SetWordType(0, 0x8004);
	Logic06(0x8004);
	StorePartyCanLearnMove(0x8000, 237, 0x8005);
	SetVarEqVar(0x8004, 0x8000);
	Compare(0x8004, 1);
	if (1) goto label18;
	goto label19;

label18: ;
	Message2(1024, 29, 0, 0);
	SetVarEqVal(0x8000, 0);
	Return();

label17: ;
	Message2(1024, 32, 0, 0);
	SetVarEqVal(0x8000, 0);
	Return();

label16: ;
	Message2(1024, 31, 0, 0);
	SetVarEqVal(0x8000, 0);
	Return();

label15: ;
	Message2(1024, 30, 0, 0);
	SetVarEqVal(0x8000, 0);
	Return();

label19: ;
	Message2(1024, 28, 0, 0);
	SetVarEqVal(0x8000, 0);
	Return();
}
