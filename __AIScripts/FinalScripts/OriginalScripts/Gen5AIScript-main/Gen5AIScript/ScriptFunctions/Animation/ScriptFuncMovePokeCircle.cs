using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncMovePokeCircle : ScriptFunc
{
    public override string Name => "MovePokeCircle";
    public override int Id => 0x13;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeObjectPos(),
        new ScriptArgTypeCircleAxis(),
        new ScriptArgTypeCircleShift(),
        new ScriptArgTypeFixedPoint("horizontal_radius"),
        new ScriptArgTypeFixedPoint("vertical_radius"),
        new ScriptArgTypeFixedPoint("frames"),
        new ScriptArgTypeFixedPoint("delay"),
        new ScriptArgTypeFixedPoint("iterations"),
        new ScriptArgTypeInt("rotation_delay")
    ];
}