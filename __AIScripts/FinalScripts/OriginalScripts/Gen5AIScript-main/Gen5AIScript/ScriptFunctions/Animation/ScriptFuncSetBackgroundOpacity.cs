using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetBackgroundOpacity : ScriptFunc
{
    public override string Name => "SetBackgroundOpacity";
    public override int Id => 0x29;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeBackgroundType(),
        new ScriptArgTypeTransformType("transform_type"),
        new ScriptArgTypeInt("opacity"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations"),
    ];
}