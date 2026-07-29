using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncSetCameraProjectionType : ScriptFunc
{
    public override string Name => "SetCameraProjectionType";
    public override int Id => 0x04;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeCameraProjectionType(),
        new ScriptArgTypeCameraProjectionTarget()
    ];
}