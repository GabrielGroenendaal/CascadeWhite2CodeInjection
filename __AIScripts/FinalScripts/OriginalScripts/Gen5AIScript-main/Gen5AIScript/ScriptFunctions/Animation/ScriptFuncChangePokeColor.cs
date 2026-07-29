using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncChangePokeColor : ScriptFunc
{
    public override string Name => "ChangePokeColor";
    public override int Id => 0x1B;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeInt("alpha_start"),
        new ScriptArgTypeInt("alpha_end"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeColor()
    ];
}