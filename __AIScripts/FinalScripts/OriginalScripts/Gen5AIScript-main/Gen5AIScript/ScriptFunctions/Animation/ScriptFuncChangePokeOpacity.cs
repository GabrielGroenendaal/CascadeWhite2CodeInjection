using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncChangePokeOpacity : ScriptFunc
{
    public override string Name => "ChangePokeOpacity";
    public override int Id => 0x17;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeInt("opacity"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations")
    ];
}