using System.Globalization;

namespace Gen5AIScript.ScriptLines;

public class ScriptLineData(int offset, string str) : ScriptLine(offset)
{
    private string Str { get; } = str;

    public override void Write(byte[] buffer, ScriptContext context)
    {
        var dataSectionType = context.GetDataSectionType(Offset);
        if (dataSectionType == null)
        {
            dataSectionType = context.GetDataSectionType(Offset - 4);
            if (dataSectionType == null)
            {
                WriteDefault(buffer);
                return;
            }
            
            context.SetDataOffsetSectionType(Offset, dataSectionType);
        }

        var value = dataSectionType.FromString(context, Offset, Str);
        
        if (value == 0xFFFFFFFF)
            context.RemoveDataOffsetSectionType(Offset);
        
        BitConverter.TryWriteBytes(buffer.AsSpan(Offset), value);
    }

    private void WriteDefault(byte[] buffer)
    {
        // Default interpretation: 0x###### (#)

        var hexStartIndex = Str.IndexOf("0x", StringComparison.Ordinal);
        
        if (hexStartIndex == -1)
            throw new FormatException();

        hexStartIndex += 2;
        var hexEndIndex = str.IndexOf(' ', hexStartIndex);
        
        var hexStr = Str.Substring(hexStartIndex, hexEndIndex - hexStartIndex);
        var value = uint.Parse(hexStr, NumberStyles.HexNumber);

        switch (hexStr.Length)
        {
            case 4:
                BitConverter.TryWriteBytes(buffer.AsSpan(Offset), (ushort)value);
                break;
            case 8:
                BitConverter.TryWriteBytes(buffer.AsSpan(Offset), value);
                break;
            default:
                throw new Exception();
        }
    }
}