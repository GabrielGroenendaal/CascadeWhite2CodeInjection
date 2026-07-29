using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfStatStageNE : ScriptFuncJumpBase
{
    public override string Name => "JumpIfStatStageNE";
    public override int Id => 0x35;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypePokePos(), new ScriptArgTypeStat(), new ScriptArgTypeStatStage(), new ScriptArgTypeLabel()
    ];
}