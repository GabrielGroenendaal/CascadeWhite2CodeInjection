namespace Gen5AIScript.ScriptFunctions.TrainerAI;

public class ScriptFuncDuplicate(ScriptFunc baseFunc, int id) : ScriptFunc
{
    public override string Name { get; } = baseFunc.Name;
    public override int Id { get; } = id;
    public override ScriptArgType[] ArgTypes { get; } = baseFunc.ArgTypes;
}