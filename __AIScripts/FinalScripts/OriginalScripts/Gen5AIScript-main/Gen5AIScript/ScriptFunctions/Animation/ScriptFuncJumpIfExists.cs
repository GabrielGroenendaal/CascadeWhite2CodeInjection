using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncJumpIfExists : ScriptFuncJumpBase
{
    public override string Name => "JumpIfExists";
    public override int Id => 0x3D;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeBool("exists"),
        new ScriptArgTypeLabel()
    ];
}