using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions;

public abstract class ScriptFuncConditionalJumpBase : ScriptFunc
{
    public override bool IsJump => true;
    public override int[] GetJumpAddresses(byte[] buffer, int funcOffset)
    {
        var jumpOffset = GetArgValue(buffer, funcOffset, LastArgIndex);
        return [funcOffset + Size + (int)jumpOffset];
    }
}