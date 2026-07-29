namespace Gen5AIScript;

public class ScriptContext
{
    private Dictionary<string, int> LabelOffsets { get; } = new();

    private Dictionary<int, string> Labels { get; } = new();

    private Dictionary<int, ScriptArgType?> SectionTypes { get; set; } = [];
    public ScriptArgType? ReturnType { get; set; }

    public bool TryGetLabelOffset(string label, out int offset) => LabelOffsets.TryGetValue(label, out offset);

    public bool TryGetLabel(int offset, out string? label) => Labels.TryGetValue(offset, out label);

    public void AddLabel(string name, int offset)
    {
        LabelOffsets.TryAdd(name, offset);
        Labels.TryAdd(offset, name);
    }

    public void SetDataOffsetSectionType(int offset, ScriptArgType? argType)
    {
        SectionTypes.TryAdd(offset, argType);
    }

    public void RemoveDataOffsetSectionType(int offset)
    {
        SectionTypes.Remove(offset);
    }

    public ScriptArgType? GetDataSectionType(int offset)
    {
        return SectionTypes.GetValueOrDefault(offset);
    }
}