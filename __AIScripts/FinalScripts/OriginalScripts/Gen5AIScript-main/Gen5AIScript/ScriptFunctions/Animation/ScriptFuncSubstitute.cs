using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSubstitute : ScriptFunc
{
    public override string Name => "Substitute";
    public override int Id => 0x41;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeBool("is_enabled"),
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeBool("clear_flag")
    ];
}