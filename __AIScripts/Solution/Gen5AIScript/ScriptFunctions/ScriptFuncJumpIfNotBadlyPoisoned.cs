using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfNotBadlyPoisoned : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfNotBadlyPoisoned";
    public override int Id => 0x0E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeLabel("address")];
}