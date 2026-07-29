using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncJumpToScript : ScriptFunc
{
    public override string Name => "JumpToScript";
    public override int Id => 0x4A;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("script_id")
    ];

    public override bool AddSpaceBelow => true;
    public override bool Continue => false;
}