using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncJumpIfNotCondition : ScriptFuncJumpBase
{
    public override string Name => "JumpIfNotCondition";
    public override int Id => 0x0C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeConditionFlag("condition"), new ScriptArgTypeLabel()];
}