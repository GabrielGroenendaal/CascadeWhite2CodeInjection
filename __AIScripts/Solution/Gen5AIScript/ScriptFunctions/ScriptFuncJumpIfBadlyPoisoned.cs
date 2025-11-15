using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfBadlyPoisoned : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfBadlyPoisoned";
    public override int Id => 0x0D;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeLabel("address")];
}