using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfPartyNoStatus : ScriptFuncJumpBase
{
    public override string Name => "JumpIfPartyNoStatus";
    public override int Id => 0x2E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeCondition(), new ScriptArgTypeLabel()];
}