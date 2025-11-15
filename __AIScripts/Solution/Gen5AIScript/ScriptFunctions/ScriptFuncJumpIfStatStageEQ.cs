using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfStatStageEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfStatStageEQ";
    public override int Id => 0x34;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypePokePos(), new ScriptArgTypeStat(), new ScriptArgTypeStatStage(), new ScriptArgTypeLabel()
    ];
}