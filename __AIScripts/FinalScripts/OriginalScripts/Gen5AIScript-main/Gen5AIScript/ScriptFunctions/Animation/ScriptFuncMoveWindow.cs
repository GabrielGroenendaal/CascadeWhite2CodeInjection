using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMoveWindow : ScriptFunc
{
    public override string Name => "MoveWindow";
    public override int Id => 0x2C;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeWindowType(),
        new ScriptArgTypeInt("width"),
        new ScriptArgTypeInt("height"),
        new ScriptArgTypeInt("in_out"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeBool("is_active")
    ];
}