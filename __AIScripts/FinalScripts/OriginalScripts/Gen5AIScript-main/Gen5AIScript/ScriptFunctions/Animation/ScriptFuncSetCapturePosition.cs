using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetCapturePosition : ScriptFunc
{
    public override string Name => "SetCapturePosition";
    public override int Id => 0x44;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeCapturePos()
    ];
}