using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfUserWillTakeLowDamage_Debuffs : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfUserWillTakeLowDamage_Debuffs";
    public override int Id => 0x3E;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}