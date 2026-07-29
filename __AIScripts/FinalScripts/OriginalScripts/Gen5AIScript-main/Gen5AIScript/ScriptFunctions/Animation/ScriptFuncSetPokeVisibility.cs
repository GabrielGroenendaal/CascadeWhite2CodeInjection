using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetPokeVisibility : ScriptFunc
{
    public override string Name => "SetPokeVisibility";
    public override int Id => 0x1C;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypePokeVisibilityState(),
    ];
}