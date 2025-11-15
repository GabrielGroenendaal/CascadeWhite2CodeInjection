using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHealthGT : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHealthGT";
    public override int Id => 0x06;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel("address")];

}