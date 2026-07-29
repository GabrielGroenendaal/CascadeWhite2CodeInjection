using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncJump : ScriptFuncJumpBase
{
    public override string Name => "Jump";
    public override int Id => 0x48;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeLabel()
    ];

    public override bool Continue => false;
}