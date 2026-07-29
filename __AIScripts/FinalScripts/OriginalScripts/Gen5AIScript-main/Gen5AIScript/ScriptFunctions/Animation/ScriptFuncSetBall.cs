using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetBall : ScriptFunc
{
    public override string Name => "SetBall";
    public override int Id => 0x45;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("index"),
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeFixedPoint("offset_x"),
        new ScriptArgTypeFixedPoint("offset_y"),
        new ScriptArgTypeFixedPoint("scale_x"),
        new ScriptArgTypeFixedPoint("scale_y")
    ];
}