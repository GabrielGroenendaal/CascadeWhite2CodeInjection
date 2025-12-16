using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncCheckOwnDamageIntoAlly : ScriptFuncConditionalJumpBase
{
    public override string Name => "CheckOwnDamageIntoAlly";
    public override int Id => 0x3F;
    public override ScriptArgType[] ArgTypes => [new ScriptArgTypeLabel()];
}