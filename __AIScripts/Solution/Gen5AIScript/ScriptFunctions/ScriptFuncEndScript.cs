using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public class ScriptFuncEndScript : ScriptFunc
{
    public override string Name => "EndScript";
    public override int Id => 0x4D;
    public override ScriptArgType[] ArgTypes => [];
    public override bool AddSpaceBelow => true;
    public override bool Continue => false;
}