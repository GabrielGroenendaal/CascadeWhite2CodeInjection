using Gen5AIScript.ScriptArgTypes;

namespace Gen5AIScript;

public abstract class ScriptFunc
{
    public abstract string Name { get; }
    public virtual string Description { get; } = "";
    public abstract int Id { get; }
    public abstract ScriptArgType[] ArgTypes { get; }
    public int ArgCount => ArgTypes.Length;
    public int LastArgIndex => ArgCount - 1;
    public virtual ScriptArgType? ReturnType { get; protected init; }
    public virtual bool AddSpaceBelow => false;

    public virtual void UpdateContext(ScriptContext context, byte[] buffer, int funcOffset)
    {
    }

    protected uint GetArgValue(byte[] buffer, int funcOffset, int argIndex)
    {
        if (funcOffset < 0 || funcOffset + 2 + ArgCount * 4 > buffer.Length)
            throw new ArgumentOutOfRangeException(nameof(funcOffset));

        if (argIndex < 0 || argIndex > ArgCount)
            throw new ArgumentOutOfRangeException(nameof(argIndex));

        var argOffset = funcOffset + 2 + argIndex * 4;
        return BitConverter.ToUInt32(buffer, argOffset);
    }

    public virtual bool IsJump { get; protected init; }

    public virtual int[] GetJumpAddresses(byte[] buffer, int funcOffset)
    {
        return [];
    }

    public virtual bool TryGetDataAddress(byte[] buffer, int funcOffset, out int address, out int length, out ScriptArgType? dataType)
    {
        address = -1;
        length = -1;
        dataType = null;
        return false;
    }

    public virtual bool Continue => true;

    public int Size => 2 + ArgTypes.Length * 4;
}