using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHealthLT : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHealthLT";
    public override int Id => 0x05;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel("address")];
}