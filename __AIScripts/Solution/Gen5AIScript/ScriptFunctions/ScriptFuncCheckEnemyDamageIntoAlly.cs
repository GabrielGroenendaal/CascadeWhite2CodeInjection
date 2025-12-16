using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncCheckEnemyDamageIntoAlly : ScriptFuncConditionalJumpBase
{
    public override string Name => "CheckEnemyDamageIntoAlly";
    public override int Id => 0x2B;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}