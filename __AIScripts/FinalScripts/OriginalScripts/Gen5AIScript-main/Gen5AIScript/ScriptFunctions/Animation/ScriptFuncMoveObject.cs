using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMoveObject : ScriptFunc
{
    public override string Name => "MoveObject";
    public override int Id => 0x2E;

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