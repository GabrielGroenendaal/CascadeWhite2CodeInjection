using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMoveCamera : ScriptFunc
{
    public override string Name => "MoveCamera";
    public override int Id => 0x00;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeMoveCameraType(),
        new ScriptArgTypeCameraPos(),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("dampening")
    ];
}