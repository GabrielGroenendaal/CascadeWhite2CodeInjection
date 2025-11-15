using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHealthEQ : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHealthEQ";
    public override int Id => 0x07;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel("address")];

}