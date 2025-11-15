using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasNoStatus : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasNoStatus";
    public override int Id => 0x0A;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeLabel("address")];
}