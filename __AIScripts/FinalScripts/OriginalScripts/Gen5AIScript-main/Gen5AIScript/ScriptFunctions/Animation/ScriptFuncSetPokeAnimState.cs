using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetPokeAnimState : ScriptFunc
{
    public override string Name => "SetPokeAnimState";
    public override int Id => 0x1A;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypePokeAnimState(),
    ];
}