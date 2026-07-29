using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStatStageGT : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStatStageGT";
    public override int Id => 0x33;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypePokePos(), new ScriptArgTypeStat(), new ScriptArgTypeStatStage(), new ScriptArgTypeLabel()
    ];
}