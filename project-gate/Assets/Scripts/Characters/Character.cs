using Godot;

public partial class Character : Node3D
{
  private const float INTITIAL_REQUEUE_PRIORITY = 1.0f;
  [Signal]
  public delegate void UpdateMainCharacterEventHandler();

  [Export]
  public int TotalDistance = 8;

  [Export]
  public int TotalHealth = 10;

  [Export]
  public float BaseSpeedAccumulator = 2.0f;

  [Export]
  public float SpeedNeededToRequeue = 2.0f;

  [Export]
  public float StartingSpeed = 0.2f;

  [Export]
  public float HeapPriority = 1.0f;

  public int currentHealth { get; private set; }
  public float CurrentHeapPriority {get; private set;}

  [Export]
  public Weapon main_weapon { get; private set; }
  [Export]
  public Grenade grenade { get; private set; }
  private Godot.Collections.Array items;
  private float CurrentSpeed;

  private int distanceRemaining { get; set; }

  public bool isMoving { get; set; } = false;
  private Callable updateMovementCalcs;

  public override void _Ready()
  {
    SetupCharacter();
  }

  public void SetupCharacter() {
    CurrentSpeed = StartingSpeed;
    distanceRemaining = TotalDistance;
    InputHandler i_handle = GetNode<Node>("/root/Top/input_handler") as InputHandler;
    i_handle.UpdateCharacter += MakeMainCharacter;
    i_handle.ResetCharacter += ResetDistanceRemaining;
    Node3D UnitMovement = GetNodeOrNull<Node3D>("/root/Top/pivot/UnitControl");
    if (UnitMovement.HasMethod("GetUpdateCharacterSignal"))
    {
      Connect(SignalName.UpdateMainCharacter, (Callable)UnitMovement.Call("GetUpdateCharacterSignal"));
    }
    Connect(SignalName.UpdateMainCharacter, GenerationCommunicatorSingleton.Instance.GetUpdateCharacterSignal());
    EmitSignal(SignalName.UpdateMainCharacter, this);
    CharacterTurnController.Instance.AddUpdateCharacterMovementCallable(updateMovementCalcs);
    CharacterTurnController.Instance.AddCharacterToTurnController(this);
    currentHealth = TotalHealth;
    ResetPriority();
    if (main_weapon == null)
    {
      main_weapon = new Weapon();
      main_weapon.SetWeaponName("Pistol");
      main_weapon.SetMaxRange(10);
    }
    GD.Print("Character");
  }

  public void AttackCharacter(int damageAmount)
  {
    GD.Print("Current Health ", currentHealth);
    currentHealth -= damageAmount;
    if (currentHealth <= 0)
    {
    }
  }

  public void RequeueingCharacter()
  {
    if (CurrentHeapPriority < 0)
    {
      CurrentHeapPriority = INTITIAL_REQUEUE_PRIORITY;
    }
    else
    {
      CurrentHeapPriority += 1;
    }
  }

  public void ResetPriority() {
    CurrentHeapPriority = -HeapPriority;
  }

  private void KillCharacter()
  {
    CharacterTurnController.Instance.RemoveCharacterFromTurnController(this);
    CharacterTurnController.Instance.RemoveUpdateCharacterMovementCallable(updateMovementCalcs);
    Visible = false;

  }

  public void HealCharacter(int healAmount)
  {
    GD.Print("Healing ", healAmount);
    currentHealth += healAmount;
  }


  public void MakeMainCharacter()
  {
    GD.Print("Emitting Signal");
    EmitSignal(SignalName.UpdateMainCharacter, this);
  }

  public int GetDistanceRemaining()
  {
    return distanceRemaining;
  }

  public bool GetIsMoving() {
    return isMoving;
  }

  public override string ToString() {
    return this.GetType() + " character";
  }

  public void DecrementDistanceRemaining(int decrementor)
  {
    distanceRemaining -= decrementor;
  }

  public bool UpdateMovementCalcs()
  {
    bool requeue = false;
    GD.Print("CurrentHeapPriority: ", CurrentHeapPriority);
    if (CurrentHeapPriority < 0)
    {
      CurrentSpeed += BaseSpeedAccumulator;
    }
    if (CurrentSpeed >= SpeedNeededToRequeue)
    {
      CharacterTurnController.Instance.AddCharacterToMovementQueue(this);
      CurrentSpeed -= SpeedNeededToRequeue;
      if (CurrentSpeed >= SpeedNeededToRequeue)
      {
        requeue = true;
      }
    }
    return requeue;
  }

  public void SetMainWeapon(Weapon UpdatedWeapon)
  {
    main_weapon = UpdatedWeapon;
  }

  public Weapon GetMainWeapon()
  {
    return main_weapon;
  }

  public void ResetDistanceRemaining()
  {
    GD.Print("Resetting Distance");
    distanceRemaining = TotalDistance;
  }

}
