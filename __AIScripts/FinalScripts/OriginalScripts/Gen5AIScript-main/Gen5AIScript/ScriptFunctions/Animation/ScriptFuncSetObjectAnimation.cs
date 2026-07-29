using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetObjectAnimation : ScriptFunc
{
    public override string Name => "SetObjectAnimation";
    public override int Id => 0x30;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("index"),
        new ScriptArgTypeInt("anim_id")
    ];
}