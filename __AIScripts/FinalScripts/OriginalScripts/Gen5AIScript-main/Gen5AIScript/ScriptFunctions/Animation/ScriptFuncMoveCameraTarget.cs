using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMoveCameraTarget : ScriptFunc
{
    public override string Name => "MoveCameraTarget";
    public override int Id => 0x01;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeMoveCameraType(),
        new ScriptArgTypeFixedPoint("pos_x"), new ScriptArgTypeFixedPoint("pos_y"), new ScriptArgTypeFixedPoint("pos_z"),
        new ScriptArgTypeFixedPoint("tgt_x"), new ScriptArgTypeFixedPoint("tgt_y"), new ScriptArgTypeFixedPoint("tgt_z"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("dampening")
    ];
}