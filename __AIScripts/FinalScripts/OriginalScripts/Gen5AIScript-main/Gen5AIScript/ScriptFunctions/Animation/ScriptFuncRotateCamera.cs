using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncRotateCamera : ScriptFunc
{
    public override string Name => "RotateCamera";
    public override int Id => 0x02;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeMoveCameraType(),
        new ScriptArgTypeInt("pitch"),
        new ScriptArgTypeInt("yaw"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("dampening")
    ];
}