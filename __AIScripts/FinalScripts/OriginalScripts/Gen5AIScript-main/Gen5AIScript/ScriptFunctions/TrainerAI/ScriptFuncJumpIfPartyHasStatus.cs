using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfPartyHasStatus : ScriptFuncJumpBase
{
    public override string Name => "JumpIfPartyHasStatus";
    public override int Id => 0x2D;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeCondition(), new ScriptArgTypeLabel()];
}