using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.Animation;

public class ScriptFuncChangeSoundProperty : ScriptFunc
{
    public override string Name => "ChangeSoundProperty";
    public override int Id => 0x37;

    public override ScriptArgType[] ArgTypes =>
    [
        new ScriptArgTypeSoundChannel(allowAll: true),
        new ScriptArgTypeChangeSoundPropertyType(),
        new ScriptArgTypeSoundProperty(),
        new ScriptArgTypeInt("start"),
        new ScriptArgTypeInt("end"),
        new ScriptArgTypeInt("start_delay"),
        new ScriptArgTypeInt("frames"),
        new ScriptArgTypeInt("delay"),
        new ScriptArgTypeInt("iterations"),
    ];
}