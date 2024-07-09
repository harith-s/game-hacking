#include <vector>
#include <set>
#include <map>
#include <functional>
struct Vector3 {
    float x;
    float y;
    float z;
  public:
    Vector3();
    Vector3(float, float, float);
    struct Vector3 operator*(float) const;
    struct Vector3 & operator*=(float);
    struct Vector3 operator+(const struct Vector3 &) const;
    struct Vector3 & operator+=(const struct Vector3 &);
    struct Vector3 operator-(const struct Vector3 &) const;
    struct Vector3 & operator-=(const struct Vector3 &);
    float MagnitudeSquared() const;
    float Magnitude() const;
    static float DistanceSquared(const struct Vector3 &, const struct Vector3 &);
    static float Distance(const struct Vector3 &, const struct Vector3 &);
    void Normalize();
    static struct Vector3 Normalize(const struct Vector3 &);
};
struct Rotation {
    float pitch;
    float yaw;
    float roll;
  public:
    Rotation();
    Rotation(float, float, float);
};
class IPlayer {
  public:
    virtual class IActor * GetActorInterface();
    void AddRef();
    void Release();
    virtual bool IsLocalPlayer() const;
    virtual class ILocalPlayer * GetLocalPlayer() const;
    virtual const char * GetPlayerName();
    virtual const char * GetTeamName();
    virtual uint8_t GetAvatarIndex();
    virtual const uint32_t * GetColors();
    virtual bool IsPvPDesired();
    virtual void SetPvPDesired(bool);
    virtual class IInventory * GetInventory();
    virtual uint32_t GetItemCount(class IItem *);
    virtual uint32_t GetLoadedAmmo(class IItem *);
    virtual bool AddItem(class IItem *, uint32_t, bool);
    virtual bool RemoveItem(class IItem *, uint32_t);
    virtual bool AddLoadedAmmo(class IItem *, class IItem *, uint32_t);
    virtual bool RemoveLoadedAmmo(class IItem *, uint32_t);
    virtual class IItem * GetItemForSlot(size_t);
    virtual void EquipItem(size_t, class IItem *);
    virtual size_t GetCurrentSlot();
    virtual void SetCurrentSlot(size_t);
    virtual class IItem * GetCurrentItem();
    virtual int32_t GetMana();
    virtual bool UseMana(int32_t);
    virtual void SetItemCooldown(class IItem *, float, bool);
    virtual bool IsItemOnCooldown(class IItem *);
    virtual float GetItemCooldown(class IItem *);
    virtual bool HasPickedUp(const char *);
    virtual void MarkAsPickedUp(const char *);
    virtual class IQuest ** GetQuestList(size_t *);
    virtual void FreeQuestList(class IQuest **);
    virtual class IQuest * GetCurrentQuest();
    virtual void SetCurrentQuest(class IQuest *);
    virtual struct PlayerQuestState GetStateForQuest(class IQuest *);
    virtual void StartQuest(class IQuest *);
    virtual void AdvanceQuestToState(class IQuest *, class IQuestState *);
    virtual void CompleteQuest(class IQuest *);
    virtual bool IsQuestStarted(class IQuest *);
    virtual bool IsQuestCompleted(class IQuest *);
    virtual void EnterAIZone(const char *);
    virtual void ExitAIZone(const char *);
    virtual void UpdateCountdown(int32_t);
    void HideCountdown();
    virtual bool CanReload();
    virtual void RequestReload();
    virtual float GetWalkingSpeed();
    virtual float GetSprintMultiplier();
    virtual float GetJumpSpeed();
    virtual float GetJumpHoldTime();
    virtual bool CanJump();
    virtual void SetJumpState(bool);
    virtual void SetSprintState(bool);
    virtual void SetFireRequestState(bool);
    virtual void TransitionToNPCState(const char *);
    virtual void BuyItem(class IActor *, class IItem *, uint32_t);
    virtual void SellItem(class IActor *, class IItem *, uint32_t);
    virtual void EnterRegion(const char *);
    virtual void Respawn();
    virtual void Teleport(const char *);
    virtual void Chat(const char *);
    virtual class IFastTravel * GetFastTravelDestinations(const char *);
    virtual void FastTravel(const char *, const char *);
    virtual void MarkAsAchieved(class IAchievement *);
    virtual bool HasAchieved(class IAchievement *);
    virtual void SubmitDLCKey(const char *);
    virtual uint32_t GetCircuitInputs(const char *);
    virtual void SetCircuitInputs(const char *, uint32_t);
    virtual void GetCircuitOutputs(const char *, bool *, size_t);
};


enum DamageType {PhysicalDamage, FireDamage, ColdDamage, ShockDamage};
class IActor {
  public:
    virtual ~IActor();
    virtual void * GetUE4Actor();
    virtual bool IsNPC();
    virtual bool IsPlayer();
    virtual class IPlayer * GetPlayerInterface();
    virtual void AddRef();
    virtual void Release();
    virtual void OnSpawnActor(class IUE4Actor *);
    virtual void OnDestroyActor();
    virtual const char * GetBlueprintName();
    virtual bool IsCharacter();
    virtual bool CanBeDamaged(class IActor *);
    virtual int32_t GetHealth();
    virtual int32_t GetMaxHealth();
    virtual void Damage(class IActor *, class IItem *, int32_t, enum DamageType);
    virtual void Tick(float);
    virtual bool CanUse(class IPlayer *);
    virtual void OnUse(class IPlayer *);
    virtual void OnHit(class IActor *, const struct Vector3 &, const struct Vector3 &);
    virtual void OnAIMoveComplete();
    virtual const char * GetDisplayName();
    virtual bool IsElite();
    virtual bool IsPvPEnabled();
    virtual class IItem ** GetShopItems(size_t &);
    virtual void FreeShopItems(class IItem **);
    virtual int32_t GetBuyPriceForItem(class IItem *);
    virtual int32_t GetSellPriceForItem(class IItem *);
    virtual struct Vector3 GetLookPosition();
    virtual struct Rotation GetLookRotation();
    virtual class IActor * GetOwner();
};

template <class T>

class ActorRef{
  private:
    T *m_object;

  public:
    ActorRef();
    ActorRef(T *);
    ActorRef(const class ActorRef<T> &);
    class ActorRef<T> & operator=(T *);
    class ActorRef<T> & operator=(const class ActorRef<T> &);
    T * operator->() const;
    operator bool() const;
    operator T *() const;
    T * Get() const;
    bool operator<(const class ActorRef<T> &) const;
};

struct ItemAndCount {
    class IItem *item;
    uint32_t count;
    uint32_t loadedAmmo;
};


class Actor : public IActor {
  protected:
    size_t m_refs;
    uint32_t m_id;
    class IUE4Actor *m_target;
    class TimerSet *m_timers;
    std::string m_blueprintName;
    class ActorRef<IActor> m_owner;
    int32_t m_health;
    class std::map<std::string, bool, std::less<std::string>, std::allocator<std::pair<std::string const, bool> > > m_states;
    float m_forwardMovementFraction;
    float m_strafeMovementFraction;
    struct Vector3 m_remotePosition;
    struct Vector3 m_remoteVelocity;
    struct Rotation m_remoteRotation;
    float m_remoteLocationBlendFactor;
    class Spawner *m_spawner;

    virtual void OnKilled(class IActor *, class IItem *);
    virtual void OnTargetKilled(class IActor *, class IItem *);
  public:
    Actor(const std::string &);
    virtual ~Actor();
    virtual bool IsValid() const;
    virtual void * GetUE4Actor();
    virtual void AddRef();
    virtual void Release();
    void RemoveFromWorld();
    virtual void OnSpawnActor(class IUE4Actor *);
    virtual void OnDestroyActor();
    virtual std::string GetDeathMessage();
    virtual const char * GetBlueprintName();
    virtual bool IsCharacter();
    virtual bool IsNPC();
    virtual bool IsProjectile();
    virtual bool IsPlayer();
    virtual class IPlayer * GetPlayerInterface();
    virtual bool ShouldSendPositionUpdates();
    virtual bool ShouldReceivePositionUpdates();
    uint32_t GetId() const;
    void SetId(uint32_t);
    struct Vector3 GetPosition();
    struct Vector3 GetProjectilePosition();
    virtual struct Vector3 GetLookPosition();
    struct Rotation GetRotation();
    virtual struct Rotation GetLookRotation();
    struct Vector3 GetVelocity();
    float GetForwardMovementFraction() const;
    float GetStrafeMovementFraction() const;
    bool IsOnGround();
    void SetPosition(const struct Vector3 &);
    void SetRotation(const struct Rotation &);
    void SetVelocity(const struct Vector3 &);
    void SetForwardAndStrafeMovement(float, float);
    void SetRemotePositionAndRotation(const struct Vector3 &, const struct Rotation &);
    void InterpolateRemotePosition(float);
    virtual class IActor * GetOwner();
    void LocalRespawn(const struct Vector3 &, const struct Rotation &);
    bool MoveToLocation(const struct Vector3 &);
    bool MoveToRandomLocationInRadius(float);
    bool MoveToActor(class IActor *);
    bool GetState(const std::string &);
    virtual void UpdateState(const std::string &, bool);
    virtual void TriggerEvent(const std::string &, class IActor *, bool);
    const class std::map<std::string, bool, std::less<std::string>, std::allocator<std::pair<std::string const, bool> > > & GetStates();
    class IActor * LineTraceTo(const struct Vector3 &);
    void FireBullets(class IItem *, int32_t, enum DamageType, float, uint32_t, float);
    void FireBullets(class IItem *, int32_t, enum DamageType, const struct Vector3 &, float, uint32_t, float);
    virtual bool CanBeDamaged(class IActor *);
    virtual float GetMaximumDamageDistance();
    virtual int32_t GetHealth();
    virtual int32_t GetMaxHealth();
    virtual void Damage(class IActor *, class IItem *, int32_t, enum DamageType);
    void PerformSetHealth(int32_t);
    virtual void Tick(float);
    virtual bool CanUse(class IPlayer *);
    virtual void OnUse(class IPlayer *);
    virtual void PerformUse(class IPlayer *);
    virtual void OnHit(class IActor *, const struct Vector3 &, const struct Vector3 &);
    virtual void OnAIMoveComplete();
    virtual const char * GetDisplayName();
    virtual bool IsElite();
    virtual bool IsPvPEnabled();
    virtual class IItem ** GetShopItems(size_t &);
    virtual class std::vector<IItem*, std::allocator<IItem*> > GetShopItems();
    virtual void FreeShopItems(class IItem **);
    virtual class std::vector<IItem*, std::allocator<IItem*> > GetValidBuyItems();
    virtual float GetShopBuyPriceMultiplier();
    virtual float GetShopSellPriceMultiplier();
    virtual int32_t GetBuyPriceForItem(class IItem *);
    virtual int32_t GetSellPriceForItem(class IItem *);
    void SetSpawner(class Spawner *);
    void AddTimer(const std::string &, float, const class std::function<void ()> &);
    void AddTimerWithContext(const std::string &, float, const class std::function<void (Actor *)> &);
    void AddRecurringTimer(const std::string &, float, const class std::function<void ()> &);
    void AddRecurringTimerWithContext(const std::string &, float, const class std::function<void (Actor *)> &);
    void CancelTimer(const std::string &);
    void PerformReloadNotification(uint32_t);
};

enum NPCStateTransitionType {EndConversationTransition, ContinueConversationTransition, ShopTransition};

struct NPCStateTransition {
    std::string text;
    NPCStateTransitionType type;
    std::string nextState;
};

struct NPCState {
    std::string text;
    class std::vector<NPCStateTransition, std::allocator<NPCStateTransition> > transitions;
};

class NPC : public Actor {
  private:
    class std::map<std::string, NPCState, std::less<std::string>, std::allocator<std::pair<std::string const, NPCState> > > m_states;

  public:
    NPC(const std::string &);
    virtual bool IsNPC();
    void AddState(const std::string &, const std::string &);
    void AddStateTransition(const std::string &, const std::string &, const std::string &);
    void AddStateTransitionToEnd(const std::string &, const std::string &);
    void AddStateTransitionToShop(const std::string &, const std::string &);
    std::string GetTextForState(const std::string &);
    class std::vector<NPCStateTransition, std::allocator<NPCStateTransition> > GetTransitionsForState(const std::string &);
    virtual std::string GetInitialState(class IPlayer *);
    virtual void OnTransitionTaken(class IPlayer *, const std::string &, const std::string &);
    virtual bool CanUse(class IPlayer *);
    virtual void PerformUse(class IPlayer *);
    virtual int32_t GetBuyPriceForItem(class IItem *);
    virtual int32_t GetSellPriceForItem(class IItem *);
};
struct QuestStateInfo {
    std::string state;
    uint32_t count;
};
struct ItemCountInfo {
    uint32_t count;
    uint32_t loadedAmmo;
};


class Player : public Actor, public IPlayer {
  private:
    uint32_t m_characterId;
    std::string m_playerName;
    std::string m_teamName;
    uint8_t m_avatarIndex;
    uint32_t m_colors[4];
    class std::map<IItem*, ItemAndCount, std::less<IItem*>, std::allocator<std::pair<IItem* const, ItemAndCount> > > m_inventory;
    class std::set<std::string, std::less<std::string>, std::allocator<std::string> > m_pickups;
    class std::map<IItem*, float, std::less<IItem*>, std::allocator<std::pair<IItem* const, float> > > m_cooldowns;
    class std::map<std::string, unsigned int, std::less<std::string>, std::allocator<std::pair<std::string const, unsigned int> > > m_circuitInputs;
    class std::map<std::string, std::vector<class std::allocator<bool>>, std::less<std::string>, std::allocator<std::pair<std::string const, std::vector<class std::allocator<bool>> > > > m_circuitOutputs;
    bool m_admin;
    bool m_pvpEnabled;
    bool m_pvpDesired;
    float m_pvpChangeTimer;
    int32_t m_pvpChangeReportedTimer;
    bool m_changingServerRegion;
    std::string m_currentRegion;
    std::string m_changeRegionDestination;
    class std::set<std::string, std::less<std::string>, std::allocator<std::string> > m_aiZones;
    int32_t m_mana;
    float m_manaRegenTimer;
    float m_healthRegenCooldown;
    float m_healthRegenTimer;
    int32_t m_countdown;
    struct Vector3 m_remoteLookPosition;
    struct Rotation m_remoteLookRotation;
    class IItem *m_equipped[10];
    size_t m_currentSlot;
    class std::map<IQuest*, PlayerQuestState, std::less<IQuest*>, std::allocator<std::pair<IQuest* const, PlayerQuestState> > > m_questStates;
    class IQuest *m_currentQuest;
    float m_walkingSpeed;
    float m_jumpSpeed;
    float m_jumpHoldTime;
    class ActorRef<NPC> m_currentNPC;
    std::string m_currentNPCState;
    class ILocalPlayer *m_localPlayer;
    class WriteStream *m_eventsToSend;
    bool m_itemsUpdated;
    float m_itemSyncTimer;
    uint32_t m_chatMessageCounter;
    float m_chatFloodDecayTimer;
    class IItem *m_lastHitByItem;
    float m_lastHitItemTimeLeft;
    float m_circuitStateCooldownTimer;

  protected:
    virtual void OnKilled(class IActor *, class IItem *);
  public:
    Player(bool);
    virtual ~Player();
    virtual bool IsPlayer();
    virtual class IPlayer * GetPlayerInterface();
    virtual class IActor * GetActorInterface();
    virtual bool CanBeDamaged(class IActor *);
    virtual bool IsCharacter();
    virtual bool ShouldSendPositionUpdates();
    virtual bool ShouldReceivePositionUpdates();
    virtual void Tick(float);
    virtual void Damage(class IActor *, class IItem *, int32_t, enum DamageType);
    virtual void OnDestroyActor();
    void OnKillEvent(class IPlayer *, class IActor *, class IItem *);
    virtual struct Vector3 GetLookPosition();
    virtual struct Rotation GetLookRotation();
    void SetRemoteLookPosition(const struct Vector3 &);
    void SetRemoteLookRotation(const struct Rotation &);
    virtual bool CanJump();
    virtual bool IsLocalPlayer() const;
    virtual class ILocalPlayer * GetLocalPlayer() const;
    void InitLocalPlayer(class ILocalPlayer *);
    bool IsAdmin() const;
    void SetPlayerName(const std::string &);
    void SetTeamName(const std::string &);
    void SetAvatarIndex(uint8_t);
    void SetColors(const uint32_t *);
    void SetCharacterId(uint32_t);
    virtual bool IsPvPEnabled();
    virtual bool IsPvPDesired();
    virtual void SetPvPDesired(bool);
    void PerformSetPvPEnabled(bool);
    void PerformSetPvPDesired(bool);
    void PerformUpdatePvPCountdown(bool, int32_t);
    virtual void UpdateState(const std::string &, bool);
    virtual const char * GetPlayerName();
    virtual const char * GetTeamName();
    virtual uint8_t GetAvatarIndex();
    virtual const uint32_t * GetColors();
    uint32_t GetCharacterId() const;
    const class std::map<IItem*, ItemAndCount, std::less<IItem*>, std::allocator<std::pair<IItem* const, ItemAndCount> > > & GetItemList() const;
    virtual class IInventory * GetInventory();
    virtual uint32_t GetItemCount(class IItem *);
    virtual uint32_t GetLoadedAmmo(class IItem *);
    virtual bool AddItem(class IItem *, uint32_t, bool);
    virtual bool RemoveItem(class IItem *, uint32_t);
    bool PerformAddItem(class IItem *, uint32_t, bool);
    bool PerformRemoveItem(class IItem *, uint32_t);
    virtual bool AddLoadedAmmo(class IItem *, class IItem *, uint32_t);
    virtual bool RemoveLoadedAmmo(class IItem *, uint32_t);
    void PerformSetLoadedAmmo(class IItem *, uint32_t);
    virtual class IItem * GetItemForSlot(size_t);
    virtual void EquipItem(size_t, class IItem *);
    void PerformEquipItem(size_t, class IItem *);
    virtual size_t GetCurrentSlot();
    virtual class IItem * GetCurrentItem();
    virtual void SetCurrentSlot(size_t);
    void PerformSetCurrentSlot(size_t);
    void SetRemoteItem(class IItem *);
    virtual int32_t GetMana();
    virtual bool UseMana(int32_t);
    void PerformSetMana(int32_t);
    virtual void SetItemCooldown(class IItem *, float, bool);
    virtual bool IsItemOnCooldown(class IItem *);
    virtual float GetItemCooldown(class IItem *);
    virtual bool HasPickedUp(const char *);
    virtual void MarkAsPickedUp(const char *);
    void PerformMarkAsPickedUp(const std::string &);
    virtual class IQuest ** GetQuestList(size_t *);
    virtual void FreeQuestList(class IQuest **);
    virtual class IQuest * GetCurrentQuest();
    virtual struct PlayerQuestState GetStateForQuest(class IQuest *);
    virtual bool IsQuestStarted(class IQuest *);
    virtual bool IsQuestCompleted(class IQuest *);
    virtual void SetCurrentQuest(class IQuest *);
    virtual void StartQuest(class IQuest *);
    virtual void AdvanceQuestToState(class IQuest *, class IQuestState *);
    virtual void CompleteQuest(class IQuest *);
    void PerformSetCurrentQuest(class IQuest *);
    void PerformStartQuest(class IQuest *);
    void PerformAdvanceQuestToState(class IQuest *, class IQuestState *);
    void PerformCompleteQuest(class IQuest *);
    void SetInitialQuestStates(const class std::map<std::string, QuestStateInfo, std::less<std::string>, std::allocator<std::pair<std::string const, QuestStateInfo> > > &, const std::string &);
    void SetInitialItemState(const class std::map<std::string, ItemCountInfo, std::less<std::string>, std::allocator<std::pair<std::string const, ItemCountInfo> > > &, const class std::vector<std::string, std::allocator<std::string> > &, uint8_t);
    void SetInitialPickupState(const class std::set<std::string, std::less<std::string>, std::allocator<std::string> > &);
    virtual void EnterAIZone(const char *);
    virtual void ExitAIZone(const char *);
    virtual void UpdateCountdown(int32_t);
    void PerformUpdateCountdown(int32_t);
    virtual void TriggerEvent(const std::string &, class IActor *, bool);
    virtual bool CanReload();
    virtual void RequestReload();
    void PerformRequestReload();
    virtual float GetWalkingSpeed();
    virtual float GetSprintMultiplier();
    virtual float GetJumpSpeed();
    virtual float GetJumpHoldTime();
    virtual void SetJumpState(bool);
    virtual void SetSprintState(bool);
    virtual void SetFireRequestState(bool);
    void SetCurrentNPCState(class NPC *, const std::string &);
    void EndNPCConversation();
    void EnterNPCShop(class NPC *);
    class NPC * GetCurrentNPC() const;
    const std::string & GetCurrentNPCState() const;
    virtual void TransitionToNPCState(const char *);
    void PerformTransitionToNPCState(const std::string &);
    virtual void BuyItem(class IActor *, class IItem *, uint32_t);
    void PerformBuyItem(class IActor *, class IItem *, uint32_t);
    virtual void SellItem(class IActor *, class IItem *, uint32_t);
    void PerformSellItem(class IActor *, class IItem *, uint32_t);
    virtual void EnterRegion(const char *);
    bool IsChangingRegion() const;
    const std::string & GetChangeRegionDestination() const;
    void PerformEnterRegion(const std::string &);
    struct LocationAndRotation GetSpawnLocation();
    virtual void Respawn();
    void PerformRespawn();
    void PerformRespawnAtLocation(const struct Vector3 &, const struct Rotation &);
    virtual void Teleport(const char *);
    void PerformTeleport(const std::string &);
    virtual void SendEvent(const class WriteStream &);
    virtual void WriteAllEvents(class WriteStream &);
    void SyncItems();
    virtual void Chat(const char *);
    void PerformChat(const std::string &);
    void ReceiveChat(class Player *, const std::string &);
    virtual class IFastTravel * GetFastTravelDestinations(const char *);
    virtual void FastTravel(const char *, const char *);
    void PerformFastTravel(const std::string &, const std::string &);
    void OnTravelComplete(const std::string &);
    class IItem * GetLastHitByItem() const;
    void PerformSetLastHitByItem(class IItem *);
    virtual void MarkAsAchieved(class IAchievement *);
    virtual bool HasAchieved(class IAchievement *);
    virtual void SubmitDLCKey(const char *);
    void PerformSubmitDLCKey(const std::string &);
    virtual uint32_t GetCircuitInputs(const char *);
    virtual void SetCircuitInputs(const char *, uint32_t);
    void PerformSetCircuitInputs(const std::string &, uint32_t);
    virtual void GetCircuitOutputs(const char *, bool *, size_t);
    void PerformSetCircuitOutputs(const std::string &, const std::vector<class std::allocator<bool>>);
    void InitCircuitStates();
};

class Projectile : public Actor {
  protected:
    class IItem *m_item;
    float m_lifetime;

  public:
    Projectile(class IActor *, class IItem *, const std::string &);
    virtual bool ShouldSendPositionUpdates();
    virtual bool IsProjectile();
    virtual int32_t GetDirectDamage();
    virtual enum DamageType GetDamageType();
    virtual bool HasSplashDamage();
    virtual float GetSplashRadius();
    virtual int32_t GetSplashDamage();
    virtual bool DamagesOnHit();
    class IItem * GetItem() const;
    virtual void OnHit(class IActor *, const struct Vector3 &, const struct Vector3 &);
    void DealDamage(class IActor *);
    virtual void Tick(float);
    virtual void OnLifetimeEnded();
    static bool SpawnProjectile(class IActor *, class Projectile *);
};




class AIZoneListener {
  private:
    class AIZone *m_zone;

  public:
    AIZoneListener();
    virtual ~AIZoneListener();
    void SetAIZone(const std::string &);
    virtual void OnAIZoneActivated();
    virtual void OnAIZoneDeactivated();
    bool IsAIZoneActive();
};

class AIZone {
  private:
    std::string m_name;
    size_t m_playerCount;
    class std::set<AIZoneListener*, std::less<AIZoneListener*>, std::allocator<AIZoneListener*> > m_listeners;

  public:
    AIZone(const std::string &);
    const std::string & GetName() const;
    bool IsActive() const;
    void OnPlayerEntered();
    void OnPlayerLeft();
    void AddListener(class AIZoneListener *);
    void RemoveListener(class AIZoneListener *);
};








class World {
  protected:
    class std::set<ActorRef<IPlayer>, std::less<ActorRef<IPlayer> >, std::allocator<ActorRef<IPlayer> > > m_players;
    class std::set<ActorRef<IActor>, std::less<ActorRef<IActor> >, std::allocator<ActorRef<IActor> > > m_actors;
    class std::map<unsigned int, ActorRef<IActor>, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, ActorRef<IActor> > > > m_actorsById;
    class ILocalPlayer *m_localPlayer;
    uint32_t m_nextId;
    class std::map<std::string, AIZone*, std::less<std::string>, std::allocator<std::pair<std::string const, AIZone*> > > m_aiZones;

    void AddActorToWorld(class Actor *);
    void AddActorToWorldWithId(uint32_t, class Actor *);
    void SendEventToAllPlayers(const class WriteStream &);
    void SendEventToAllPlayersExcept(class Player *, const class WriteStream &);
  public:
    World();
    virtual ~World();
    virtual void Tick(float);
    virtual bool HasLocalPlayer();
    class ILocalPlayer * GetLocalPlayer();
    virtual bool IsAuthority();
    virtual void AddLocalPlayer(class Player *, class ILocalPlayer *);
    virtual void AddRemotePlayer(class Player *);
    virtual void AddRemotePlayerWithId(uint32_t, class Player *);
    virtual void RemovePlayer(class Player *);
    virtual void Use(class Player *, class Actor *);
    virtual void Activate(class Player *, class IItem *);
    virtual void Reload(class Player *);
    virtual void Jump(bool);
    virtual void Sprint(bool);
    virtual void FireRequest(bool);
    virtual void TransitionToNPCState(class Player *, const std::string &);
    virtual void BuyItem(class Player *, class Actor *, class IItem *, uint32_t);
    virtual void SellItem(class Player *, class Actor *, class IItem *, uint32_t);
    virtual void Respawn(class Player *);
    virtual void Teleport(class Player *, const std::string &);
    virtual void Chat(class Player *, const std::string &);
    virtual void FastTravel(class Player *, const std::string &, const std::string &);
    virtual void SetPvPDesired(class Player *, bool);
    virtual void SubmitDLCKey(class Player *, const std::string &);
    virtual void SetCircuitInputs(class Player *, const std::string &, uint32_t);
    virtual void SendAddItemEvent(class Player *, class IItem *, uint32_t);
    virtual void SendRemoveItemEvent(class Player *, class IItem *, uint32_t);
    virtual void SendLoadedAmmoEvent(class Player *, class IItem *, uint32_t);
    virtual void SendPickedUpEvent(class Player *, const std::string &);
    virtual void EquipItem(class Player *, uint8_t, class IItem *);
    virtual void SetCurrentSlot(class Player *, uint8_t);
    virtual void SendEquipItemEvent(class Player *, uint8_t, class IItem *);
    virtual void SendCurrentSlotEvent(class Player *, uint8_t);
    virtual void SetCurrentQuest(class Player *, class IQuest *);
    virtual void SendSetCurrentQuestEvent(class Player *, class IQuest *);
    virtual void SendStartQuestEvent(class Player *, class IQuest *);
    virtual void SendAdvanceQuestToStateEvent(class Player *, class IQuest *, class IQuestState *);
    virtual void SendCompleteQuestEvent(class Player *, class IQuest *);
    virtual void SendHealthUpdateEvent(class Actor *, int32_t);
    virtual void SendManaUpdateEvent(class Player *, int32_t);
    virtual void SendCountdownUpdateEvent(class Player *, int32_t);
    virtual void SendPvPCountdownUpdateEvent(class Player *, bool, int32_t);
    virtual void SendPvPEnableEvent(class Player *, bool);
    virtual void SendStateEvent(class Actor *, const std::string &, bool);
    virtual void SendTriggerEvent(class Actor *, const std::string &, class Actor *, bool);
    virtual void SendFireBulletsEvent(class Actor *, class IItem *, const struct Vector3 &, uint32_t, float);
    virtual void SendDisplayEvent(class Player *, const std::string &, const std::string &);
    virtual void SendNPCConversationStateEvent(class Player *, class Actor *, const std::string &);
    virtual void SendNPCConversationEndEvent(class Player *);
    virtual void SendNPCShopEvent(class Player *, class Actor *);
    virtual void SendRespawnEvent(class Player *, const struct Vector3 &, const struct Rotation &);
    virtual void SendTeleportEvent(class Actor *, const struct Vector3 &, const struct Rotation &);
    virtual void SendRelativeTeleportEvent(class Actor *, const struct Vector3 &);
    virtual void SendReloadEvent(class Player *, class IItem *, class IItem *, uint32_t);
    virtual void SendPlayerJoinedEvent(class Player *);
    virtual void SendPlayerLeftEvent(class Player *);
    virtual void SendPlayerItemEvent(class Player *);
    virtual void SendActorSpawnEvent(class Actor *);
    virtual void SendActorDestroyEvent(class Actor *);
    virtual void SendExistingPlayerEvent(class Player *, class Player *);
    virtual void SendExistingActorEvent(class Player *, class Actor *);
    virtual void SendChatEvent(class Player *, const std::string &);
    virtual void SendKillEvent(class Player *, class Actor *, class IItem *);
    virtual void SendCircuitOutputEvent(class Player *, const std::string &, uint32_t, const class std::vector<class std::allocator<bool>> &);
    virtual void SendActorPositionEvents(class Player *);
    virtual void SendRegionChangeEvent(class Player *, const std::string &);
    virtual void SendLastHitByItemEvent(class Player *, class IItem *);
    bool SpawnActor(class Actor *, const struct Vector3 &, const struct Rotation &);
    bool SpawnActorAtNamedLocation(class Actor *, const char *);
    void SpawnActorWithId(uint32_t, class Actor *, const struct Vector3 &, const struct Rotation &);
    void DestroyActor(class Actor *);
    void SendSpawnEventsForExistingActors(class Player *);
    void AddAIZone(class AIZone *);
    class AIZone * GetAIZone(const std::string &);
    void OnPlayerEnteredAIZone(const std::string &);
    void OnPlayerLeftAIZone(const std::string &);
    class std::vector<IPlayer*, std::allocator<IPlayer*> > GetPlayersInRadius(const struct Vector3 &, float);
    class std::vector<Projectile*, std::allocator<Projectile*> > GetProjectilesInRadius(const struct Vector3 &, float);
    class Actor * GetActorById(uint32_t);
    void RemoveAllActorsExceptPlayer(class Player *);
    void ChangeActorId(class Player *, uint32_t);
    bool IsPlayerAlreadyConnected(uint32_t);
};



