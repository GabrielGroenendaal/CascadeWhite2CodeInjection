using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncPlayEmitterCircleOrthographic : ScriptFunc
{
    public override string Name => "PlayEmitterCircleOrthographic";
    public override int Id => 0x11;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeInt("file_id"),
        new ScriptArgTypeInt("emitter_id"),
        new ScriptArgTypeEmitterCirclePos(),
        new ScriptArgTypeFixedPoint("radius_horizontal"),
        new ScriptArgTypeFixedPoint("radius_vertical"),
        new ScriptArgTypeFixedPoint("y_offset"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations"),
        new ScriptArgTypeInt("rotation_delay")
    ];
}