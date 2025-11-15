using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasConditionFlag : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasConditionFlag";
    public override int Id => 0x0F;

    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos(), new ScriptArgTypeConditionFlag(), new ScriptArgTypeLabel()];
}