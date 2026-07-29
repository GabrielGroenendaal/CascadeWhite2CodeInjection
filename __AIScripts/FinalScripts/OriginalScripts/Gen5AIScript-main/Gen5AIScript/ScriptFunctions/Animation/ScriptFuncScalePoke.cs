using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncScalePoke : ScriptFunc
{
    public override string Name => "ScalePoke";
    public override int Id => 0x15;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeFixedPoint("x"),
        new ScriptArgTypeFixedPoint("y"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations")
    ];
}