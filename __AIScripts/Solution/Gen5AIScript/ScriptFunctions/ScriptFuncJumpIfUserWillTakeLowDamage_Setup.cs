using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncJumpIfUserWillTakeLowDamage_Setup : ScriptFuncConditionalJumpBase
{
    public override string Name => "JumpIfUserWillTakeLowDamage_Setup";
    public override int Id => 0x64;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}