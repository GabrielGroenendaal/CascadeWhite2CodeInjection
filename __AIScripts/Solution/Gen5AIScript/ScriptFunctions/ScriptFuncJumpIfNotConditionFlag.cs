using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfNotConditionFlag : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfNotConditionFlag";
    public override int Id => 0x10;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeConditionFlag(), new ScriptArgTypeLabel()];
}