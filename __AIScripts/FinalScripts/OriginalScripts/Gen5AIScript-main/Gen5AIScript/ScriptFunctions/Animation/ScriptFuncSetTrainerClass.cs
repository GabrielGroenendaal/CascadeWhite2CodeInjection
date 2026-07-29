using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetTrainerClass : ScriptFunc
{
    public override string Name => "SetTrainerClass";
    public override int Id => 0x20;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("class"),
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeFixedPoint("x"),
        new ScriptArgTypeFixedPoint("y"),
        new ScriptArgTypeFixedPoint("z")
    ];
}