using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncRotatePoke : ScriptFunc
{
    public override string Name => "RotatePoke";
    public override int Id => 0x16;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeFixedPoint("angle"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations")
    ];
}