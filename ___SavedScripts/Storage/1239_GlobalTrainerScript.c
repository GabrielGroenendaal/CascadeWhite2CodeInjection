#include "ScriptHeaders/FrostScriptCommandsBW2.h"
#include "ScriptHeaders/MovementCommands.h"


void Sequence0()
{
	SetVarEqVal(0x8020, 0);
	SetVarEqVal(0x8021, 0);
	SetVarEqVal(0x8022, 0);
	SetVarEqVal(0x8023, 0);
	SetVarEqVal(0x8024, 0);
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Routine0();
	SetVarc0x84(0x8020);
	GetTrainerIDActive(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label0;
	dvar92(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label1;
	Routine1();
	goto label2;

label1:;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label3;
	Routine2();
	goto label2;

label3:;
	Routine3();

label2:;
	goto label4;

label0:;
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8026, 0);
	c0x8A(0x8020, 0x8025);
	GetPartyCount(0x8026, 2);
	StackPushVar(0x8025);
	StackPushConst(1);
	StackCompare(1);
	StackPushVar(0x8026);
	StackPushConst(2);
	StackCompare(0);
	StackCompare(7);
	if (255) goto label5;
	Routine4();
	goto label6;

label5:;
	StackPushVar(0x8025);
	StackPushConst(2);
	StackCompare(1);
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(0);
	StackCompare(7);
	if (255) goto label7;
	Routine5();
	goto label6;

label7:;
	StackPushVar(0x8025);
	StackPushConst(3);
	StackCompare(1);
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(0);
	StackCompare(7);
	if (255) goto label8;
	Routine5();
	goto label6;

label8:;
	Routine6();
	dvar92(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label9;
	Routine1();
	goto label6;

label9:;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label6;
	Routine7();

label6:;
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8025, 0);

label4:;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence1()
{
	Sequence0();
}

void Sequence2()
{
	Sequence0();
}

void Sequence3()
{
	Sequence0();
}

void Sequence4()
{
	Sequence0();
}

void Sequence5()
{
	Sequence0();
}

void Sequence6()
{
	Sequence0();
}

void Sequence7()
{
	Sequence0();
}

void Sequence8()
{
	Sequence0();
}

void Sequence9()
{
	Sequence0();
}

void Sequence10()
{
	Sequence0();
}

void Sequence11()
{
	Sequence0();
}

void Sequence12()
{
	Sequence0();
}

void Sequence13()
{
	Sequence0();
}

void Sequence14()
{
	Sequence0();
}

void Sequence15()
{
	Sequence0();
}

void Sequence16()
{
	Sequence0();
}

void Sequence17()
{
	Sequence0();
}

void Sequence18()
{
	Sequence0();
}

void Sequence19()
{
	Sequence0();
}

void Sequence20()
{
	Sequence0();
}

void Sequence21()
{
	Sequence0();
}

void Sequence22()
{
	Sequence0();
}

void Sequence23()
{
	Sequence0();
}

void Sequence24()
{
	Sequence0();
}

void Sequence25()
{
	Sequence0();
}

void Sequence26()
{
	Sequence0();
}

void Sequence27()
{
	Sequence0();
}

void Sequence28()
{
	Sequence0();
}

void Sequence29()
{
	Sequence0();
}

void Sequence30()
{
	Sequence0();
}

void Sequence31()
{
	Sequence0();
}

void Sequence32()
{
	Sequence0();
}

void Sequence33()
{
	Sequence0();
}

void Sequence34()
{
	Sequence0();
}

void Sequence35()
{
	Sequence0();
}

void Sequence36()
{
	Sequence0();
}

void Sequence37()
{
	Sequence0();
}

void Sequence38()
{
	Sequence0();
}

void Sequence39()
{
	Sequence0();
}

void Sequence40()
{
	Sequence0();
}

void Sequence41()
{
	Sequence0();
}

void Sequence42()
{
	Sequence0();
}

void Sequence43()
{
	Sequence0();
}

void Sequence44()
{
	Sequence0();
}

void Sequence45()
{
	Sequence0();
}

void Sequence46()
{
	Sequence0();
}

void Sequence47()
{
	Sequence0();
}

void Sequence48()
{
	Sequence0();
}

void Sequence49()
{
	Sequence0();
}

void Sequence50()
{
	Sequence0();
}

void Sequence51()
{
	Sequence0();
}

void Sequence52()
{
	Sequence0();
}

void Sequence53()
{
	Sequence0();
}

void Sequence54()
{
	Sequence0();
}

void Sequence55()
{
	Sequence0();
}

void Sequence56()
{
	Sequence0();
}

void Sequence57()
{
	Sequence0();
}

void Sequence58()
{
	Sequence0();
}

void Sequence59()
{
	Sequence0();
}

void Sequence60()
{
	Sequence0();
}

void Sequence61()
{
	Sequence0();
}

void Sequence62()
{
	Sequence0();
}

void Sequence63()
{
	Sequence0();
}

void Sequence64()
{
	Sequence0();
}

void Sequence65()
{
	Sequence0();
}

void Sequence66()
{
	Sequence0();
}

void Sequence67()
{
	Sequence0();
}

void Sequence68()
{
	Sequence0();
}

void Sequence69()
{
	Sequence0();
}

void Sequence70()
{
	Sequence0();
}

void Sequence71()
{
	Sequence0();
}

void Sequence72()
{
	Sequence0();
}

void Sequence73()
{
	Sequence0();
}

void Sequence74()
{
	Sequence0();
}

void Sequence75()
{
	Sequence0();
}

void Sequence76()
{
	Sequence0();
}

void Sequence77()
{
	Sequence0();
}

void Sequence78()
{
	Sequence0();
}

void Sequence79()
{
	Sequence0();
}

void Sequence80()
{
	Sequence0();
}

void Sequence81()
{
	Sequence0();
}

void Sequence82()
{
	Sequence0();
}

void Sequence83()
{
	Sequence0();
}

void Sequence84()
{
	Sequence0();
}

void Sequence85()
{
	Sequence0();
}

void Sequence86()
{
	Sequence0();
}

void Sequence87()
{
	Sequence0();
}

void Sequence88()
{
	Sequence0();
}

void Sequence89()
{
	Sequence0();
}

void Sequence90()
{
	Sequence0();
}

void Sequence91()
{
	Sequence0();
}

void Sequence92()
{
	Sequence0();
}

void Sequence93()
{
	Sequence0();
}

void Sequence94()
{
	Sequence0();
}

void Sequence95()
{
	Sequence0();
}

void Sequence96()
{
	Sequence0();
}

void Sequence97()
{
	Sequence0();
}

void Sequence98()
{
	Sequence0();
}

void Sequence99()
{
	Sequence0();
}

void Sequence100()
{
	Sequence0();
}

void Sequence101()
{
	Sequence0();
}

void Sequence102()
{
	Sequence0();
}

void Sequence103()
{
	Sequence0();
}

void Sequence104()
{
	Sequence0();
}

void Sequence105()
{
	Sequence0();
}

void Sequence106()
{
	Sequence0();
}

void Sequence107()
{
	Sequence0();
}

void Sequence108()
{
	Sequence0();
}

void Sequence109()
{
	Sequence0();
}

void Sequence110()
{
	Sequence0();
}

void Sequence111()
{
	Sequence0();
}

void Sequence112()
{
	Sequence0();
}

void Sequence113()
{
	Sequence0();
}

void Sequence114()
{
	Sequence0();
}

void Sequence115()
{
	Sequence0();
}

void Sequence116()
{
	Sequence0();
}

void Sequence117()
{
	Sequence0();
}

void Sequence118()
{
	Sequence0();
}

void Sequence119()
{
	Sequence0();
}

void Sequence120()
{
	Sequence0();
}

void Sequence121()
{
	Sequence0();
}

void Sequence122()
{
	Sequence0();
}

void Sequence123()
{
	Sequence0();
}

void Sequence124()
{
	Sequence0();
}

void Sequence125()
{
	Sequence0();
}

void Sequence126()
{
	Sequence0();
}

void Sequence127()
{
	Sequence0();
}

void Sequence128()
{
	Sequence0();
}

void Sequence129()
{
	Sequence0();
}

void Sequence130()
{
	Sequence0();
}

void Sequence131()
{
	Sequence0();
}

void Sequence132()
{
	Sequence0();
}

void Sequence133()
{
	Sequence0();
}

void Sequence134()
{
	Sequence0();
}

void Sequence135()
{
	Sequence0();
}

void Sequence136()
{
	Sequence0();
}

void Sequence137()
{
	Sequence0();
}

void Sequence138()
{
	Sequence0();
}

void Sequence139()
{
	Sequence0();
}

void Sequence140()
{
	Sequence0();
}

void Sequence141()
{
	Sequence0();
}

void Sequence142()
{
	Sequence0();
}

void Sequence143()
{
	Sequence0();
}

void Sequence144()
{
	Sequence0();
}

void Sequence145()
{
	Sequence0();
}

void Sequence146()
{
	Sequence0();
}

void Sequence147()
{
	Sequence0();
}

void Sequence148()
{
	Sequence0();
}

void Sequence149()
{
	Sequence0();
}

void Sequence150()
{
	Sequence0();
}

void Sequence151()
{
	Sequence0();
}

void Sequence152()
{
	Sequence0();
}

void Sequence153()
{
	Sequence0();
}

void Sequence154()
{
	Sequence0();
}

void Sequence155()
{
	Sequence0();
}

void Sequence156()
{
	Sequence0();
}

void Sequence157()
{
	Sequence0();
}

void Sequence158()
{
	Sequence0();
}

void Sequence159()
{
	Sequence0();
}

void Sequence160()
{
	Sequence0();
}

void Sequence161()
{
	Sequence0();
}

void Sequence162()
{
	Sequence0();
}

void Sequence163()
{
	Sequence0();
}

void Sequence164()
{
	Sequence0();
}

void Sequence165()
{
	Sequence0();
}

void Sequence166()
{
	Sequence0();
}

void Sequence167()
{
	Sequence0();
}

void Sequence168()
{
	Sequence0();
}

void Sequence169()
{
	Sequence0();
}

void Sequence170()
{
	Sequence0();
}

void Sequence171()
{
	Sequence0();
}

void Sequence172()
{
	Sequence0();
}

void Sequence173()
{
	Sequence0();
}

void Sequence174()
{
	Sequence0();
}

void Sequence175()
{
	Sequence0();
}

void Sequence176()
{
	Sequence0();
}

void Sequence177()
{
	Sequence0();
}

void Sequence178()
{
	Sequence0();
}

void Sequence179()
{
	Sequence0();
}

void Sequence180()
{
	Sequence0();
}

void Sequence181()
{
	Sequence0();
}

void Sequence182()
{
	Sequence0();
}

void Sequence183()
{
	Sequence0();
}

void Sequence184()
{
	Sequence0();
}

void Sequence185()
{
	Sequence0();
}

void Sequence186()
{
	Sequence0();
}

void Sequence187()
{
	Sequence0();
}

void Sequence188()
{
	Sequence0();
}

void Sequence189()
{
	Sequence0();
}

void Sequence190()
{
	Sequence0();
}

void Sequence191()
{
	Sequence0();
}

void Sequence192()
{
	Sequence0();
}

void Sequence193()
{
	Sequence0();
}

void Sequence194()
{
	Sequence0();
}

void Sequence195()
{
	Sequence0();
}

void Sequence196()
{
	Sequence0();
}

void Sequence197()
{
	Sequence0();
}

void Sequence198()
{
	Sequence0();
}

void Sequence199()
{
	Sequence0();
}

void Sequence200()
{
	Sequence0();
}

void Sequence201()
{
	Sequence0();
}

void Sequence202()
{
	Sequence0();
}

void Sequence203()
{
	Sequence0();
}

void Sequence204()
{
	Sequence0();
}

void Sequence205()
{
	Sequence0();
}

void Sequence206()
{
	Sequence0();
}

void Sequence207()
{
	Sequence0();
}

void Sequence208()
{
	Sequence0();
}

void Sequence209()
{
	Sequence0();
}

void Sequence210()
{
	Sequence0();
}

void Sequence211()
{
	Sequence0();
}

void Sequence212()
{
	Sequence0();
}

void Sequence213()
{
	Sequence0();
}

void Sequence214()
{
	Sequence0();
}

void Sequence215()
{
	Sequence0();
}

void Sequence216()
{
	Sequence0();
}

void Sequence217()
{
	Sequence0();
}

void Sequence218()
{
	Sequence0();
}

void Sequence219()
{
	Sequence0();
}

void Sequence220()
{
	Sequence0();
}

void Sequence221()
{
	Sequence0();
}

void Sequence222()
{
	Sequence0();
}

void Sequence223()
{
	Sequence0();
}

void Sequence224()
{
	Sequence0();
}

void Sequence225()
{
	Sequence0();
}

void Sequence226()
{
	Sequence0();
}

void Sequence227()
{
	Sequence0();
}

void Sequence228()
{
	Sequence0();
}

void Sequence229()
{
	Sequence0();
}

void Sequence230()
{
	Sequence0();
}

void Sequence231()
{
	Sequence0();
}

void Sequence232()
{
	Sequence0();
}

void Sequence233()
{
	Sequence0();
}

void Sequence234()
{
	Sequence0();
}

void Sequence235()
{
	Sequence0();
}

void Sequence236()
{
	Sequence0();
}

void Sequence237()
{
	Sequence0();
}

void Sequence238()
{
	Sequence0();
}

void Sequence239()
{
	Sequence0();
}

void Sequence240()
{
	Sequence0();
}

void Sequence241()
{
	Sequence0();
}

void Sequence242()
{
	Sequence0();
}

void Sequence243()
{
	Sequence0();
}

void Sequence244()
{
	Sequence0();
}

void Sequence245()
{
	Sequence0();
}

void Sequence246()
{
	Sequence0();
}

void Sequence247()
{
	Sequence0();
}

void Sequence248()
{
	Sequence0();
}

void Sequence249()
{
	Sequence0();
}

void Sequence250()
{
	Sequence0();
}

void Sequence251()
{
	Sequence0();
}

void Sequence252()
{
	Sequence0();
}

void Sequence253()
{
	Sequence0();
}

void Sequence254()
{
	Sequence0();
}

void Sequence255()
{
	Sequence0();
}

void Sequence256()
{
	Sequence0();
}

void Sequence257()
{
	Sequence0();
}

void Sequence258()
{
	Sequence0();
}

void Sequence259()
{
	Sequence0();
}

void Sequence260()
{
	Sequence0();
}

void Sequence261()
{
	Sequence0();
}

void Sequence262()
{
	Sequence0();
}

void Sequence263()
{
	Sequence0();
}

void Sequence264()
{
	Sequence0();
}

void Sequence265()
{
	Sequence0();
}

void Sequence266()
{
	Sequence0();
}

void Sequence267()
{
	Sequence0();
}

void Sequence268()
{
	Sequence0();
}

void Sequence269()
{
	Sequence0();
}

void Sequence270()
{
	Sequence0();
}

void Sequence271()
{
	Sequence0();
}

void Sequence272()
{
	Sequence0();
}

void Sequence273()
{
	Sequence0();
}

void Sequence274()
{
	Sequence0();
}

void Sequence275()
{
	Sequence0();
}

void Sequence276()
{
	Sequence0();
}

void Sequence277()
{
	Sequence0();
}

void Sequence278()
{
	Sequence0();
}

void Sequence279()
{
	Sequence0();
}

void Sequence280()
{
	Sequence0();
}

void Sequence281()
{
	Sequence0();
}

void Sequence282()
{
	Sequence0();
}

void Sequence283()
{
	Sequence0();
}

void Sequence284()
{
	Sequence0();
}

void Sequence285()
{
	Sequence0();
}

void Sequence286()
{
	Sequence0();
}

void Sequence287()
{
	Sequence0();
}

void Sequence288()
{
	Sequence0();
}

void Sequence289()
{
	Sequence0();
}

void Sequence290()
{
	Sequence0();
}

void Sequence291()
{
	Sequence0();
}

void Sequence292()
{
	Sequence0();
}

void Sequence293()
{
	Sequence0();
}

void Sequence294()
{
	Sequence0();
}

void Sequence295()
{
	Sequence0();
}

void Sequence296()
{
	Sequence0();
}

void Sequence297()
{
	Sequence0();
}

void Sequence298()
{
	Sequence0();
}

void Sequence299()
{
	Sequence0();
}

void Sequence300()
{
	Sequence0();
}

void Sequence301()
{
	Sequence0();
}

void Sequence302()
{
	Sequence0();
}

void Sequence303()
{
	Sequence0();
}

void Sequence304()
{
	Sequence0();
}

void Sequence305()
{
	Sequence0();
}

void Sequence306()
{
	Sequence0();
}

void Sequence307()
{
	Sequence0();
}

void Sequence308()
{
	Sequence0();
}

void Sequence309()
{
	Sequence0();
}

void Sequence310()
{
	Sequence0();
}

void Sequence311()
{
	Sequence0();
}

void Sequence312()
{
	Sequence0();
}

void Sequence313()
{
	Sequence0();
}

void Sequence314()
{
	Sequence0();
}

void Sequence315()
{
	Sequence0();
}

void Sequence316()
{
	Sequence0();
}

void Sequence317()
{
	Sequence0();
}

void Sequence318()
{
	Sequence0();
}

void Sequence319()
{
	Sequence0();
}

void Sequence320()
{
	Sequence0();
}

void Sequence321()
{
	Sequence0();
}

void Sequence322()
{
	Sequence0();
}

void Sequence323()
{
	Sequence0();
}

void Sequence324()
{
	Sequence0();
}

void Sequence325()
{
	Sequence0();
}

void Sequence326()
{
	Sequence0();
}

void Sequence327()
{
	Sequence0();
}

void Sequence328()
{
	Sequence0();
}

void Sequence329()
{
	Sequence0();
}

void Sequence330()
{
	Sequence0();
}

void Sequence331()
{
	Sequence0();
}

void Sequence332()
{
	Sequence0();
}

void Sequence333()
{
	Sequence0();
}

void Sequence334()
{
	Sequence0();
}

void Sequence335()
{
	Sequence0();
}

void Sequence336()
{
	Sequence0();
}

void Sequence337()
{
	Sequence0();
}

void Sequence338()
{
	Sequence0();
}

void Sequence339()
{
	Sequence0();
}

void Sequence340()
{
	Sequence0();
}

void Sequence341()
{
	Sequence0();
}

void Sequence342()
{
	Sequence0();
}

void Sequence343()
{
	Sequence0();
}

void Sequence344()
{
	Sequence0();
}

void Sequence345()
{
	Sequence0();
}

void Sequence346()
{
	Sequence0();
}

void Sequence347()
{
	Sequence0();
}

void Sequence348()
{
	Sequence0();
}

void Sequence349()
{
	Sequence0();
}

void Sequence350()
{
	Sequence0();
}

void Sequence351()
{
	Sequence0();
}

void Sequence352()
{
	Sequence0();
}

void Sequence353()
{
	Sequence0();
}

void Sequence354()
{
	Sequence0();
}

void Sequence355()
{
	Sequence0();
}

void Sequence356()
{
	Sequence0();
}

void Sequence357()
{
	Sequence0();
}

void Sequence358()
{
	Sequence0();
}

void Sequence359()
{
	Sequence0();
}

void Sequence360()
{
	Sequence0();
}

void Sequence361()
{
	Sequence0();
}

void Sequence362()
{
	Sequence0();
}

void Sequence363()
{
	Sequence0();
}

void Sequence364()
{
	Sequence0();
}

void Sequence365()
{
	Sequence0();
}

void Sequence366()
{
	Sequence0();
}

void Sequence367()
{
	Sequence0();
}

void Sequence368()
{
	Sequence0();
}

void Sequence369()
{
	Sequence0();
}

void Sequence370()
{
	Sequence0();
}

void Sequence371()
{
	Sequence0();
}

void Sequence372()
{
	Sequence0();
}

void Sequence373()
{
	Sequence0();
}

void Sequence374()
{
	Sequence0();
}

void Sequence375()
{
	Sequence0();
}

void Sequence376()
{
	Sequence0();
}

void Sequence377()
{
	Sequence0();
}

void Sequence378()
{
	Sequence0();
}

void Sequence379()
{
	Sequence0();
}

void Sequence380()
{
	Sequence0();
}

void Sequence381()
{
	Sequence0();
}

void Sequence382()
{
	Sequence0();
}

void Sequence383()
{
	Sequence0();
}

void Sequence384()
{
	Sequence0();
}

void Sequence385()
{
	Sequence0();
}

void Sequence386()
{
	Sequence0();
}

void Sequence387()
{
	Sequence0();
}

void Sequence388()
{
	Sequence0();
}

void Sequence389()
{
	Sequence0();
}

void Sequence390()
{
	Sequence0();
}

void Sequence391()
{
	Sequence0();
}

void Sequence392()
{
	Sequence0();
}

void Sequence393()
{
	Sequence0();
}

void Sequence394()
{
	Sequence0();
}

void Sequence395()
{
	Sequence0();
}

void Sequence396()
{
	Sequence0();
}

void Sequence397()
{
	Sequence0();
}

void Sequence398()
{
	Sequence0();
}

void Sequence399()
{
	Sequence0();
}

void Sequence400()
{
	Sequence0();
}

void Sequence401()
{
	Sequence0();
}

void Sequence402()
{
	Sequence0();
}

void Sequence403()
{
	Sequence0();
}

void Sequence404()
{
	Sequence0();
}

void Sequence405()
{
	Sequence0();
}

void Sequence406()
{
	Sequence0();
}

void Sequence407()
{
	Sequence0();
}

void Sequence408()
{
	Sequence0();
}

void Sequence409()
{
	Sequence0();
}

void Sequence410()
{
	Sequence0();
}

void Sequence411()
{
	Sequence0();
}

void Sequence412()
{
	Sequence0();
}

void Sequence413()
{
	Sequence0();
}

void Sequence414()
{
	Sequence0();
}

void Sequence415()
{
	Sequence0();
}

void Sequence416()
{
	Sequence0();
}

void Sequence417()
{
	Sequence0();
}

void Sequence418()
{
	Sequence0();
}

void Sequence419()
{
	Sequence0();
}

void Sequence420()
{
	Sequence0();
}

void Sequence421()
{
	Sequence0();
}

void Sequence422()
{
	Sequence0();
}

void Sequence423()
{
	Sequence0();
}

void Sequence424()
{
	Sequence0();
}

void Sequence425()
{
	Sequence0();
}

void Sequence426()
{
	Sequence0();
}

void Sequence427()
{
	Sequence0();
}

void Sequence428()
{
	Sequence0();
}

void Sequence429()
{
	Sequence0();
}

void Sequence430()
{
	Sequence0();
}

void Sequence431()
{
	Sequence0();
}

void Sequence432()
{
	Sequence0();
}

void Sequence433()
{
	Sequence0();
}

void Sequence434()
{
	Sequence0();
}

void Sequence435()
{
	Sequence0();
}

void Sequence436()
{
	Sequence0();
}

void Sequence437()
{
	Sequence0();
}

void Sequence438()
{
	Sequence0();
}

void Sequence439()
{
	Sequence0();
}

void Sequence440()
{
	Sequence0();
}

void Sequence441()
{
	Sequence0();
}

void Sequence442()
{
	Sequence0();
}

void Sequence443()
{
	Sequence0();
}

void Sequence444()
{
	Sequence0();
}

void Sequence445()
{
	Sequence0();
}

void Sequence446()
{
	Sequence0();
}

void Sequence447()
{
	Sequence0();
}

void Sequence448()
{
	Sequence0();
}

void Sequence449()
{
	Sequence0();
}

void Sequence450()
{
	Sequence0();
}

void Sequence451()
{
	Sequence0();
}

void Sequence452()
{
	Sequence0();
}

void Sequence453()
{
	Sequence0();
}

void Sequence454()
{
	Sequence0();
}

void Sequence455()
{
	Sequence0();
}

void Sequence456()
{
	Sequence0();
}

void Sequence457()
{
	Sequence0();
}

void Sequence458()
{
	Sequence0();
}

void Sequence459()
{
	Sequence0();
}

void Sequence460()
{
	Sequence0();
}

void Sequence461()
{
	Sequence0();
}

void Sequence462()
{
	Sequence0();
}

void Sequence463()
{
	Sequence0();
}

void Sequence464()
{
	Sequence0();
}

void Sequence465()
{
	Sequence0();
}

void Sequence466()
{
	Sequence0();
}

void Sequence467()
{
	Sequence0();
}

void Sequence468()
{
	Sequence0();
}

void Sequence469()
{
	Sequence0();
}

void Sequence470()
{
	Sequence0();
}

void Sequence471()
{
	Sequence0();
}

void Sequence472()
{
	Sequence0();
}

void Sequence473()
{
	Sequence0();
}

void Sequence474()
{
	Sequence0();
}

void Sequence475()
{
	Sequence0();
}

void Sequence476()
{
	Sequence0();
}

void Sequence477()
{
	Sequence0();
}

void Sequence478()
{
	Sequence0();
}

void Sequence479()
{
	Sequence0();
}

void Sequence480()
{
	Sequence0();
}

void Sequence481()
{
	Sequence0();
}

void Sequence482()
{
	Sequence0();
}

void Sequence483()
{
	Sequence0();
}

void Sequence484()
{
	Sequence0();
}

void Sequence485()
{
	Sequence0();
}

void Sequence486()
{
	Sequence0();
}

void Sequence487()
{
	Sequence0();
}

void Sequence488()
{
	Sequence0();
}

void Sequence489()
{
	Sequence0();
}

void Sequence490()
{
	Sequence0();
}

void Sequence491()
{
	Sequence0();
}

void Sequence492()
{
	Sequence0();
}

void Sequence493()
{
	Sequence0();
}

void Sequence494()
{
	Sequence0();
}

void Sequence495()
{
	Sequence0();
}

void Sequence496()
{
	Sequence0();
}

void Sequence497()
{
	Sequence0();
}

void Sequence498()
{
	Sequence0();
}

void Sequence499()
{
	Sequence0();
}

void Sequence500()
{
	Sequence0();
}

void Sequence501()
{
	Sequence0();
}

void Sequence502()
{
	Sequence0();
}

void Sequence503()
{
	Sequence0();
}

void Sequence504()
{
	Sequence0();
}

void Sequence505()
{
	Sequence0();
}

void Sequence506()
{
	Sequence0();
}

void Sequence507()
{
	Sequence0();
}

void Sequence508()
{
	Sequence0();
}

void Sequence509()
{
	Sequence0();
}

void Sequence510()
{
	Sequence0();
}

void Sequence511()
{
	Sequence0();
}

void Sequence512()
{
	Sequence0();
}

void Sequence513()
{
	Sequence0();
}

void Sequence514()
{
	Sequence0();
}

void Sequence515()
{
	Sequence0();
}

void Sequence516()
{
	Sequence0();
}

void Sequence517()
{
	Sequence0();
}

void Sequence518()
{
	Sequence0();
}

void Sequence519()
{
	Sequence0();
}

void Sequence520()
{
	Sequence0();
}

void Sequence521()
{
	Sequence0();
}

void Sequence522()
{
	Sequence0();
}

void Sequence523()
{
	Sequence0();
}

void Sequence524()
{
	Sequence0();
}

void Sequence525()
{
	Sequence0();
}

void Sequence526()
{
	Sequence0();
}

void Sequence527()
{
	Sequence0();
}

void Sequence528()
{
	Sequence0();
}

void Sequence529()
{
	Sequence0();
}

void Sequence530()
{
	Sequence0();
}

void Sequence531()
{
	Sequence0();
}

void Sequence532()
{
	Sequence0();
}

void Sequence533()
{
	Sequence0();
}

void Sequence534()
{
	Sequence0();
}

void Sequence535()
{
	Sequence0();
}

void Sequence536()
{
	Sequence0();
}

void Sequence537()
{
	Sequence0();
}

void Sequence538()
{
	Sequence0();
}

void Sequence539()
{
	Sequence0();
}

void Sequence540()
{
	Sequence0();
}

void Sequence541()
{
	Sequence0();
}

void Sequence542()
{
	Sequence0();
}

void Sequence543()
{
	Sequence0();
}

void Sequence544()
{
	Sequence0();
}

void Sequence545()
{
	Sequence0();
}

void Sequence546()
{
	Sequence0();
}

void Sequence547()
{
	Sequence0();
}

void Sequence548()
{
	Sequence0();
}

void Sequence549()
{
	Sequence0();
}

void Sequence550()
{
	Sequence0();
}

void Sequence551()
{
	Sequence0();
}

void Sequence552()
{
	Sequence0();
}

void Sequence553()
{
	Sequence0();
}

void Sequence554()
{
	Sequence0();
}

void Sequence555()
{
	Sequence0();
}

void Sequence556()
{
	Sequence0();
}

void Sequence557()
{
	Sequence0();
}

void Sequence558()
{
	Sequence0();
}

void Sequence559()
{
	Sequence0();
}

void Sequence560()
{
	Sequence0();
}

void Sequence561()
{
	Sequence0();
}

void Sequence562()
{
	Sequence0();
}

void Sequence563()
{
	Sequence0();
}

void Sequence564()
{
	Sequence0();
}

void Sequence565()
{
	Sequence0();
}

void Sequence566()
{
	Sequence0();
}

void Sequence567()
{
	Sequence0();
}

void Sequence568()
{
	Sequence0();
}

void Sequence569()
{
	Sequence0();
}

void Sequence570()
{
	Sequence0();
}

void Sequence571()
{
	Sequence0();
}

void Sequence572()
{
	Sequence0();
}

void Sequence573()
{
	Sequence0();
}

void Sequence574()
{
	Sequence0();
}

void Sequence575()
{
	Sequence0();
}

void Sequence576()
{
	Sequence0();
}

void Sequence577()
{
	Sequence0();
}

void Sequence578()
{
	Sequence0();
}

void Sequence579()
{
	Sequence0();
}

void Sequence580()
{
	Sequence0();
}

void Sequence581()
{
	Sequence0();
}

void Sequence582()
{
	Sequence0();
}

void Sequence583()
{
	Sequence0();
}

void Sequence584()
{
	Sequence0();
}

void Sequence585()
{
	Sequence0();
}

void Sequence586()
{
	Sequence0();
}

void Sequence587()
{
	Sequence0();
}

void Sequence588()
{
	Sequence0();
}

void Sequence589()
{
	Sequence0();
}

void Sequence590()
{
	Sequence0();
}

void Sequence591()
{
	Sequence0();
}

void Sequence592()
{
	Sequence0();
}

void Sequence593()
{
	Sequence0();
}

void Sequence594()
{
	Sequence0();
}

void Sequence595()
{
	Sequence0();
}

void Sequence596()
{
	Sequence0();
}

void Sequence597()
{
	Sequence0();
}

void Sequence598()
{
	Sequence0();
}

void Sequence599()
{
	Sequence0();
}

void Sequence600()
{
	Sequence0();
}

void Sequence601()
{
	Sequence0();
}

void Sequence602()
{
	Sequence0();
}

void Sequence603()
{
	Sequence0();
}

void Sequence604()
{
	Sequence0();
}

void Sequence605()
{
	Sequence0();
}

void Sequence606()
{
	Sequence0();
}

void Sequence607()
{
	Sequence0();
}

void Sequence608()
{
	Sequence0();
}

void Sequence609()
{
	Sequence0();
}

void Sequence610()
{
	Sequence0();
}

void Sequence611()
{
	Sequence0();
}

void Sequence612()
{
	Sequence0();
}

void Sequence613()
{
	Sequence0();
}

void Sequence614()
{
	Sequence0();
}

void Sequence615()
{
	Sequence0();
}

void Sequence616()
{
	Sequence0();
}

void Sequence617()
{
	Sequence0();
}

void Sequence618()
{
	Sequence0();
}

void Sequence619()
{
	Sequence0();
}

void Sequence620()
{
	Sequence0();
}

void Sequence621()
{
	Sequence0();
}

void Sequence622()
{
	Sequence0();
}

void Sequence623()
{
	Sequence0();
}

void Sequence624()
{
	Sequence0();
}

void Sequence625()
{
	Sequence0();
}

void Sequence626()
{
	Sequence0();
}

void Sequence627()
{
	Sequence0();
}

void Sequence628()
{
	Sequence0();
}

void Sequence629()
{
	Sequence0();
}

void Sequence630()
{
	Sequence0();
}

void Sequence631()
{
	Sequence0();
}

void Sequence632()
{
	Sequence0();
}

void Sequence633()
{
	Sequence0();
}

void Sequence634()
{
	Sequence0();
}

void Sequence635()
{
	Sequence0();
}

void Sequence636()
{
	Sequence0();
}

void Sequence637()
{
	Sequence0();
}

void Sequence638()
{
	Sequence0();
}

void Sequence639()
{
	Sequence0();
}

void Sequence640()
{
	Sequence0();
}

void Sequence641()
{
	Sequence0();
}

void Sequence642()
{
	Sequence0();
}

void Sequence643()
{
	Sequence0();
}

void Sequence644()
{
	Sequence0();
}

void Sequence645()
{
	Sequence0();
}

void Sequence646()
{
	Sequence0();
}

void Sequence647()
{
	Sequence0();
}

void Sequence648()
{
	Sequence0();
}

void Sequence649()
{
	Sequence0();
}

void Sequence650()
{
	Sequence0();
}

void Sequence651()
{
	Sequence0();
}

void Sequence652()
{
	Sequence0();
}

void Sequence653()
{
	Sequence0();
}

void Sequence654()
{
	Sequence0();
}

void Sequence655()
{
	Sequence0();
}

void Sequence656()
{
	Sequence0();
}

void Sequence657()
{
	Sequence0();
}

void Sequence658()
{
	Sequence0();
}

void Sequence659()
{
	Sequence0();
}

void Sequence660()
{
	Sequence0();
}

void Sequence661()
{
	Sequence0();
}

void Sequence662()
{
	Sequence0();
}

void Sequence663()
{
	Sequence0();
}

void Sequence664()
{
	Sequence0();
}

void Sequence665()
{
	Sequence0();
}

void Sequence666()
{
	Sequence0();
}

void Sequence667()
{
	Sequence0();
}

void Sequence668()
{
	Sequence0();
}

void Sequence669()
{
	Sequence0();
}

void Sequence670()
{
	Sequence0();
}

void Sequence671()
{
	Sequence0();
}

void Sequence672()
{
	Sequence0();
}

void Sequence673()
{
	Sequence0();
}

void Sequence674()
{
	Sequence0();
}

void Sequence675()
{
	Sequence0();
}

void Sequence676()
{
	Sequence0();
}

void Sequence677()
{
	Sequence0();
}

void Sequence678()
{
	Sequence0();
}

void Sequence679()
{
	Sequence0();
}

void Sequence680()
{
	Sequence0();
}

void Sequence681()
{
	Sequence0();
}

void Sequence682()
{
	Sequence0();
}

void Sequence683()
{
	Sequence0();
}

void Sequence684()
{
	Sequence0();
}

void Sequence685()
{
	Sequence0();
}

void Sequence686()
{
	Sequence0();
}

void Sequence687()
{
	Sequence0();
}

void Sequence688()
{
	Sequence0();
}

void Sequence689()
{
	Sequence0();
}

void Sequence690()
{
	Sequence0();
}

void Sequence691()
{
	Sequence0();
}

void Sequence692()
{
	Sequence0();
}

void Sequence693()
{
	Sequence0();
}

void Sequence694()
{
	Sequence0();
}

void Sequence695()
{
	Sequence0();
}

void Sequence696()
{
	Sequence0();
}

void Sequence697()
{
	Sequence0();
}

void Sequence698()
{
	Sequence0();
}

void Sequence699()
{
	Sequence0();
}

void Sequence700()
{
	Sequence0();
}

void Sequence701()
{
	Sequence0();
}

void Sequence702()
{
	Sequence0();
}

void Sequence703()
{
	Sequence0();
}

void Sequence704()
{
	Sequence0();
}

void Sequence705()
{
	Sequence0();
}

void Sequence706()
{
	Sequence0();
}

void Sequence707()
{
	Sequence0();
}

void Sequence708()
{
	Sequence0();
}

void Sequence709()
{
	Sequence0();
}

void Sequence710()
{
	Sequence0();
}

void Sequence711()
{
	Sequence0();
}

void Sequence712()
{
	Sequence0();
}

void Sequence713()
{
	Sequence0();
}

void Sequence714()
{
	Sequence0();
}

void Sequence715()
{
	Sequence0();
}

void Sequence716()
{
	Sequence0();
}

void Sequence717()
{
	Sequence0();
}

void Sequence718()
{
	Sequence0();
}

void Sequence719()
{
	Sequence0();
}

void Sequence720()
{
	Sequence0();
}

void Sequence721()
{
	Sequence0();
}

void Sequence722()
{
	Sequence0();
}

void Sequence723()
{
	Sequence0();
}

void Sequence724()
{
	Sequence0();
}

void Sequence725()
{
	Sequence0();
}

void Sequence726()
{
	Sequence0();
}

void Sequence727()
{
	Sequence0();
}

void Sequence728()
{
	Sequence0();
}

void Sequence729()
{
	Sequence0();
}

void Sequence730()
{
	Sequence0();
}

void Sequence731()
{
	Sequence0();
}

void Sequence732()
{
	Sequence0();
}

void Sequence733()
{
	Sequence0();
}

void Sequence734()
{
	Sequence0();
}

void Sequence735()
{
	Sequence0();
}

void Sequence736()
{
	Sequence0();
}

void Sequence737()
{
	Sequence0();
}

void Sequence738()
{
	Sequence0();
}

void Sequence739()
{
	Sequence0();
}

void Sequence740()
{
	Sequence0();
}

void Sequence741()
{
	Sequence0();
}

void Sequence742()
{
	Sequence0();
}

void Sequence743()
{
	Sequence0();
}

void Sequence744()
{
	Sequence0();
}

void Sequence745()
{
	Sequence0();
}

void Sequence746()
{
	Sequence0();
}

void Sequence747()
{
	Sequence0();
}

void Sequence748()
{
	Sequence0();
}

void Sequence749()
{
	Sequence0();
}

void Sequence750()
{
	Sequence0();
}

void Sequence751()
{
	Sequence0();
}

void Sequence752()
{
	Sequence0();
}

void Sequence753()
{
	Sequence0();
}

void Sequence754()
{
	Sequence0();
}

void Sequence755()
{
	Sequence0();
}

void Sequence756()
{
	Sequence0();
}

void Sequence757()
{
	Sequence0();
}

void Sequence758()
{
	Sequence0();
}

void Sequence759()
{
	Sequence0();
}

void Sequence760()
{
	Sequence0();
}

void Sequence761()
{
	Sequence0();
}

void Sequence762()
{
	Sequence0();
}

void Sequence763()
{
	Sequence0();
}

void Sequence764()
{
	Sequence0();
}

void Sequence765()
{
	Sequence0();
}

void Sequence766()
{
	Sequence0();
}

void Sequence767()
{
	Sequence0();
}

void Sequence768()
{
	Sequence0();
}

void Sequence769()
{
	Sequence0();
}

void Sequence770()
{
	Sequence0();
}

void Sequence771()
{
	Sequence0();
}

void Sequence772()
{
	Sequence0();
}

void Sequence773()
{
	Sequence0();
}

void Sequence774()
{
	Sequence0();
}

void Sequence775()
{
	Sequence0();
}

void Sequence776()
{
	Sequence0();
}

void Sequence777()
{
	Sequence0();
}

void Sequence778()
{
	Sequence0();
}

void Sequence779()
{
	Sequence0();
}

void Sequence780()
{
	Sequence0();
}

void Sequence781()
{
	Sequence0();
}

void Sequence782()
{
	Sequence0();
}

void Sequence783()
{
	Sequence0();
}

void Sequence784()
{
	Sequence0();
}

void Sequence785()
{
	Sequence0();
}

void Sequence786()
{
	Sequence0();
}

void Sequence787()
{
	Sequence0();
}

void Sequence788()
{
	Sequence0();
}

void Sequence789()
{
	Sequence0();
}

void Sequence790()
{
	Sequence0();
}

void Sequence791()
{
	Sequence0();
}

void Sequence792()
{
	Sequence0();
}

void Sequence793()
{
	Sequence0();
}

void Sequence794()
{
	Sequence0();
}

void Sequence795()
{
	Sequence0();
}

void Sequence796()
{
	Sequence0();
}

void Sequence797()
{
	Sequence0();
}

void Sequence798()
{
	Sequence0();
}

void Sequence799()
{
	Sequence0();
}

void Sequence800()
{
	Sequence0();
}

void Sequence801()
{
	Sequence0();
}

void Sequence802()
{
	Sequence0();
}

void Sequence803()
{
	Sequence0();
}

void Sequence804()
{
	Sequence0();
}

void Sequence805()
{
	Sequence0();
}

void Sequence806()
{
	Sequence0();
}

void Sequence807()
{
	Sequence0();
}

void Sequence808()
{
	Sequence0();
}

void Sequence809()
{
	Sequence0();
}

void Sequence810()
{
	Sequence0();
}

void Sequence811()
{
	Sequence0();
}

void Sequence812()
{
	Sequence0();
}

void Sequence813()
{
	Sequence0();
}

void Sequence814()
{
	Sequence0();
}

void Sequence815()
{
	LockAll();
	PlaySound(1351);
	FacePlayer();
	Routine0();
	SetVarc0x84(0x8020);
	GetTrainerIDActive(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label60;
	dvar92(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label61;
	Routine1();
	goto label62;

label61:;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label63;
	Routine2();
	goto label62;

label63:;
	Routine3();

label62:;
	goto label64;

label60:;
	SetVarEqVal(0x8025, 0);
	SetVarEqVal(0x8026, 0);
	c0x8A(0x8020, 0x8025);
	GetPartyCount(0x8026, 2);
	StackPushVar(0x8025);
	StackPushConst(1);
	StackCompare(1);
	StackPushVar(0x8026);
	StackPushConst(2);
	StackCompare(0);
	StackCompare(7);
	if (255) goto label65;
	Routine4();
	goto label66;

label65:;
	StackPushVar(0x8025);
	StackPushConst(2);
	StackCompare(1);
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(0);
	StackCompare(7);
	if (255) goto label67;
	Routine5();
	goto label66;

label67:;
	StackPushVar(0x8025);
	StackPushConst(3);
	StackCompare(1);
	StackPushVar(0x8026);
	StackPushConst(3);
	StackCompare(0);
	StackCompare(7);
	if (255) goto label68;
	Routine5();
	goto label66;

label68:;
	Routine6();
	dvar92(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label69;
	Routine1();
	goto label66;

label69:;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label66;
	Routine7();

label66:;
	SetVarEqVal(0x8026, 0);
	SetVarEqVal(0x8025, 0);

label64:;
	WaitMoment();
	UnlockAll();
	End();
}

void Sequence816()
{
	LockAll();
	SetVarc0x83(0x8010);
	StackPushVar(0x8010);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label10;
	Routine8();
	goto label11;

label10:;
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label12;
	Routine9();
	goto label11;

label12:;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label13;
	Routine10();
	goto label11;

label13:;
	StackPushVar(0x8010);
	StackPushConst(3);
	StackCompare(1);
	if (255) goto label11;
	Routine11();

label11:;
	c0x7F(0, 0x8020);
	dvar92(0x8020, 0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label14;
	Routine1();
	goto label15;

label14:;
	StackPushVar(0x8010);
	StackPushConst(2);
	StackCompare(1);
	if (255) goto label15;
	Routine7();

label15:;
	WaitMoment();
	UnlockAll();
	End();
}

void Routine0()
{
	GetNPCMovementCode(0x8010, 0x8011);
	Compare(0x8010, 51);
	if (1) goto label16;
	goto label17;

label16:;
	Routine12();
	goto label18;

label17:;
	Compare(0x8010, 52);
	if (1) goto label19;
	goto label20;

label19:;
	Routine12();
	goto label18;

label20:;
	Compare(0x8010, 53);
	if (1) goto label21;
	goto label22;

label21:;
	Routine12();
	goto label18;

label22:;
	Compare(0x8010, 54);
	if (1) goto label23;
	goto label24;

label23:;
	Routine12();
	goto label18;

label24:;
	Compare(0x8010, 85);
	if (1) goto label25;
	goto label18;

label25:;
	Routine12();
	goto label18;

label18:;
	Return();
}

void Routine1()
{
	c0x87(0x8020, 13, 0x8011);
	CloseMessageBox();
	FadeScreen(3, 0, 16, 2);
	ResetScreen();
	HealPokemon();
	PlayFanfare(1300);
	WaitFanfare();
	FadeScreen(3, 16, 0, 2);
	ResetScreen();
	c0x87(0x8020, 14, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine2()
{
	c0x87(0x8020, 16, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine3()
{
	c0x88(0x8021, 0x8022, 0x8023);
	c0x87(0x8020, 0x8022, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine4()
{
	SetVarc0x84(0x8010);
	c0x88(0x8021, 0x8022, 0x8023);
	c0x87(0x8020, 0x8023, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine5()
{
	SetVarc0x84(0x8020);
	c0x88(0x8021, 0x8022, 0x8023);
	c0x87(0x8020, 0x8023, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine6()
{
	PlayTrainerMusic(0x8020);
	c0x88(0x8021, 0x8022, 0x8023);
	c0x87(0x8020, 0x8021, 0x8011);
	CloseMessageBox();
	StartTrainerBattle(0x8020, 0, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label26;
	TrainerBattleEnd();
	goto label27;

label26:;
	TrainerBattleLose();

label27:;
	DeactiveTrainerId(0x8020);
	Return();
}

void Routine7()
{
	c0x87(0x8020, 15, 0x8011);
	CloseMessageBox();
	dvar93(0x8020, 0x8000);
	SetVarEqVal(0x8001, 1);
	CallGlobalScript(2805);
	c0x87(0x8020, 16, 0x8011);
	WaitForButton();
	CloseMessageBox();
	Return();
}

void Routine8()
{
	SetVarEqVal(0x8027, 0);
	SetVarEqVal(0x8028, 0);
	c0x7F(0, 0x8027);
	PlayTrainerMusic(0x8027);
	c0x80(0);
	c0x81();
	c0x82(0, 0x8028);
	c0x87(0x8027, 0, 0x8028);
	CloseMessageBox();
	StartTrainerBattle(0x8027, 0, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label28;
	TrainerBattleEnd();
	goto label29;

label28:;
	TrainerBattleLose();

label29:;
	DeactiveTrainerId(0x8027);
	Return();
}

void Routine9()
{
	SetVarEqVal(0x8029, 0);
	SetVarEqVal(0x802A, 0);
	SetVarEqVal(0x802B, 0);
	c0x7F(0, 0x8029);
	c0x7F(1, 0x802A);
	PlayTrainerMusic(0x8029);
	c0x80(0);
	c0x80(1);
	c0x81();
	c0x82(0, 0x802B);
	c0x87(0x8029, 3, 0x802B);
	CloseMessageBox();
	c0x82(1, 0x802B);
	c0x87(0x802A, 7, 0x802B);
	CloseMessageBox();
	StartTrainerBattle(0x8029, 0x802A, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label30;
	TrainerBattleEnd();
	goto label31;

label30:;
	TrainerBattleLose();

label31:;
	DeactiveTrainerId(0x8029);
	DeactiveTrainerId(0x802A);
	Return();
}

void Routine10()
{
	SetVarEqVal(0x802C, 0);
	SetVarEqVal(0x802D, 0);
	SetVarEqVal(0x802E, 0);
	c0x7F(0, 0x802C);
	c0x7F(1, 0x802D);
	PlayTrainerMusic(0x802C);
	c0x80(0);
	c0x81();
	c0x82(0, 0x802E);
	c0x87(0x802C, 0, 0x802E);
	CloseMessageBox();
	dvar90(0x802D);
	c0x80(1);
	c0x81();
	c0x82(1, 0x802E);
	c0x87(0x802D, 0, 0x802E);
	CloseMessageBox();
	StartTrainerBattle(0x802C, 0x802D, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label32;
	TrainerBattleEnd();
	goto label33;

label32:;
	TrainerBattleLose();

label33:;
	DeactiveTrainerId(0x802C);
	DeactiveTrainerId(0x802D);
	Return();
}

void Routine11()
{
	SetVarEqVal(0x802F, 0);
	SetVarEqVal(0x8030, 0);
	SetVarEqVal(0x8031, 0);
	SetVarEqVal(0x8032, 0);
	c0x252(0x802F);
	c0x7F(0, 0x8030);
	c0x7F(1, 0x8031);
	PlayTrainerMusic(0x8030);
	c0x80(0);
	c0x81();
	c0x82(0, 0x8032);
	c0x87(0x8030, 0, 0x8032);
	CloseMessageBox();
	dvar90(0x8031);
	c0x80(1);
	c0x81();
	c0x82(1, 0x8032);
	c0x87(0x8031, 0, 0x8032);
	CloseMessageBox();
	StartMultiTrainerBattle(0x802F, 0x8030, 0x8031, 0);
	GetTrainerBattleResult(0x8010);
	StackPushVar(0x8010);
	StackPushConst(1);
	StackCompare(1);
	if (255) goto label34;
	GetPartyCount(0x8008, 2);
	StackPushVar(0x8008);
	StackPushConst(0);
	StackCompare(1);
	if (255) goto label35;
	HealPokemon();

label35:;
	TrainerBattleEnd();
	goto label36;

label34:;
	TrainerBattleLose();

label36:;
	DeactiveTrainerId(0x8030);
	DeactiveTrainerId(0x8031);
	Return();
}

void Routine12()
{

	Movement m[] = { // 32785
		0x65,
		1,
	};

	WaitMovement();
	GetPlayerDirection(0x8010);
	Compare(0x8010, 0);
	if (1) goto label37;
	goto label38;

label37:;
	c0x73(0x8011, 15);
	goto label39;

label38:;
	Compare(0x8010, 1);
	if (1) goto label40;
	goto label41;

label40:;
	c0x73(0x8011, 14);
	goto label39;

label41:;
	Compare(0x8010, 2);
	if (1) goto label42;
	goto label43;

label42:;
	c0x73(0x8011, 17);
	goto label39;

label43:;
	Compare(0x8010, 3);
	if (1) goto label44;
	goto label39;

label44:;
	c0x73(0x8011, 16);
	goto label39;

label39:;
	Return();
}
