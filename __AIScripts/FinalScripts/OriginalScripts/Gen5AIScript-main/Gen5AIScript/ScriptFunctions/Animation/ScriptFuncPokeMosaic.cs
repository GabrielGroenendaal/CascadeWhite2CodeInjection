using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPokeMosaic : ScriptFunc
{
    public override string Name => "PokeMosaic";
    public override int Id => 0x18;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeTransformType(),
        new ScriptArgTypeInt("amount"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations")
    ];
}