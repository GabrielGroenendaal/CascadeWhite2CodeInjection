using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncCreateObject : ScriptFunc
{
    public override string Name => "CreateObject";
    public override int Id => 0x2D;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("index"),
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeFixedPoint("offset_x"),
        new ScriptArgTypeFixedPoint("offset_y"),
        new ScriptArgTypeFixedPoint("scale_x"),
        new ScriptArgTypeFixedPoint("scale_y")
    ];
}