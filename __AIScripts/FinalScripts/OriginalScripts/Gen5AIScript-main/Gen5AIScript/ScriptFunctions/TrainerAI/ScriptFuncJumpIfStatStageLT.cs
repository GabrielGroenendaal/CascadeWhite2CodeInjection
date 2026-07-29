using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStatStageLT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStatStageLT";
    public override int Id => 0x32;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypePokePos(), new ScriptArgTypeStat(), new ScriptArgTypeStatStage(), new ScriptArgTypeLabel()
    ];
}