using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public sealed class ScriptFuncUnknown : ScriptFunc
{
    public override string Name { get; }
    public override int Id { get; }
    public override ScriptArgType[] ArgTypes { get; }

    public ScriptFuncUnknown(int id, ScriptArgType[] argTypes, ScriptArgType? returnType = null, string? suffix = null)
    {
        IsJump = argTypes.Length > 0 && argTypes.Last() is ScriptArgTypeLabel;
        var hasSuffix = suffix != null;
        Name = $"UNKNOWN{(IsJump ? "_JUMP" : "")}{(hasSuffix ? "_" + suffix : "")}_{id:X2}";
        Id = id;
        ArgTypes = argTypes;

        ReturnType = returnType;
        if (returnType == null)
            ReturnType = new ScriptArgTypeInt("result");
    }

    public override int[] GetJumpAddresses(byte[] buffer, int funcOffset)
    {
        if (!IsJump)
            return [];

        // Assume conditional jump as last arg
        var jumpOffset = GetArgValue(buffer, funcOffset, LastArgIndex);
        return [funcOffset + Size + (int)jumpOffset];
    }
}