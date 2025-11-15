namespace Gen5AIScript.ScriptFunctions;

public abstract class ScriptFuncListBase : ScriptFuncConditionalJumpBase
{
    protected bool TryGetDataAddress(byte[] buffer, int funcOffset, out int address, out int length, int dataArgIndex)
    {
        var dataOffset = (int)GetArgValue(buffer, funcOffset, dataArgIndex);
        address = funcOffset + 2 + (dataArgIndex + 1) * 4 + dataOffset;

        length = 0;
        for (var i = 0; address + i < buffer.Length; i += 4)
        {
            var dataValue = BitConverter.ToUInt32(buffer, address + i);
            ++length;

            if (dataValue == 0xFFFFFFFF)
                break;
        }

        return true;
    }

    protected abstract int GetDataOffsetAddress(byte[] buffer, int funcOffset);

    public override void UpdateContext(ScriptContext context, byte[] buffer, int funcOffset)
    {
        var dataAddressOffset = GetDataOffsetAddress(buffer, funcOffset);
        var element = context.ReturnType;

        if (element != null)
        {
            context.SetDataOffsetSectionType(dataAddressOffset, element);
        }
    }
}