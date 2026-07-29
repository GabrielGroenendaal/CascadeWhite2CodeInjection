using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfHasCondition : ScriptFuncJumpBase
{
    public override string Name => "JumpIfHasCondition";
    public override int Id => 0x0B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeCondition(), new ScriptArgTypeLabel()];
}