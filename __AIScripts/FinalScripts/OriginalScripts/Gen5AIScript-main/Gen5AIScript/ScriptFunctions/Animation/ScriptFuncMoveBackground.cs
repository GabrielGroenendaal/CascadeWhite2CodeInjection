using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMoveBackground : ScriptFunc
{
    public override string Name => "MoveBackground";
    public override int Id => 0x25;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeInt("x"),
        new ScriptArgTypeInt("y"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations"),
    ];
}