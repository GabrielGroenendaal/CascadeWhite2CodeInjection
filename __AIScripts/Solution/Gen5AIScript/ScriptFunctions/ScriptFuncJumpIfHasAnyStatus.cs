using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHasAnyStatus : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHasAnyStatus";
    public override int Id => 0x09;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeLabel("address")];
}