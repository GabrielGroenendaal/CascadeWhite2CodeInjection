using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncScaleObject : ScriptFunc
{
    public override string Name => "ScaleObject";
    public override int Id => 0x2F;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("index"),
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeInt("x"),
        new ScriptArgTypeInt("y"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations")
    ];
}