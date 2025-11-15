using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfHealthNE : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfHealthNE";
    public override int Id => 0x08;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypePokePos("poke_pos"), new ScriptArgTypeInt("value"), new ScriptArgTypeLabel("address")];

}