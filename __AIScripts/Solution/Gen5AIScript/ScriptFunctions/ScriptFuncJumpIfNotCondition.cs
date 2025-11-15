using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfNotCondition : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfNotCondition";
    public override int Id => 0x0C;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeConditionFlag("condition"), new ScriptArgTypeLabel("address")];
}