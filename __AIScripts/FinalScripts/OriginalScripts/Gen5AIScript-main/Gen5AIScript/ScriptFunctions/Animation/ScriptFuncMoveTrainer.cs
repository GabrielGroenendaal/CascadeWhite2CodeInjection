using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMoveTrainer : ScriptFunc
{
    public override string Name => "MoveTrainer";
    public override int Id => 0x21;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeFixedPoint("x"),
        new ScriptArgTypeFixedPoint("y"),
        new ScriptArgTypeFixedPoint("z"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations")
    ];
}