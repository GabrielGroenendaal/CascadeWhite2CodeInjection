using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasCondition : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasCondition";
    public override int Id => 0x0B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeCondition("condition"), new ScriptArgTypeLabel("address")];
}