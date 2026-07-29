using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncShakeCamera : ScriptFunc
{
    public override string Name => "ShakeCamera";
    public override int Id => 0x03;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeShakeCameraDir(),
        new ScriptArgTypeFixedPoint("amplitude"),
        new ScriptArgTypeFixedPoint("offset"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations"),
    ];
}