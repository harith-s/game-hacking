#include <iostream>
#include <dlfcn.h>
#include <set>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include "libGameLogic.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool Player::CanJump(){
    return 1;
}
// Vector3 t = Vector3(0,0,0); 
// void Actor::SetPosition(const Vector3 &){

//     Vector3 v = Actor::GetPosition();
//     printf("%f, %f, %f", v.x, v.y, v.z);

// }

// void Player::SetJumpState(bool b){
//     if (b){
//         Vector3 v = Actor::GetPosition();
//         const Vector3 new_v = Vector3(v.x + 1000,v.y,v.z + 1000);
//         Actor::SetPosition(new_v);
//     }
// }


void Player::Chat(const char *msg){
    char *m = (char*)msg;
 
    // Returns first token
    if (not((msg != NULL) && (msg[0] == '\0')))
    {   
        char* token = strtok(m, " ");
        Vector3 v = Actor::GetPosition();
        float x = v.x;
        float y = v.y;
        float z = v.z;
        int count = 0;
        printf("%s\n", token);
        if ((strcmp(token ,"tpz") == 0) && (count == 0)){
            token = strtok(NULL, " ");
            z = z  + atof(token);
        }
        if ((strcmp(token ,"tpx") == 0) && (count == 0)){
            token = strtok(NULL, " ");
            x = x  + atof(token);
        }
        if ((strcmp(token ,"tpy") == 0) && (count == 0)){
            token = strtok(NULL, " ");
            y = y  + atof(token);
        }
        else if (strcmp(token, "a") == 0){
            ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));

            for (ActorRef<IActor> _iactor : world->m_actors) {
                
                Actor* actor = ((Actor*)(_iactor.m_object));
                Vector3 pos = actor->GetPosition();
                printf("%f ,%f, %f\n", pos.x, pos.y, pos.z); 
        }
        }
        // else if (strcmp(token, "s") == 0){
        //     const Vector3 v = Vector3(-7719.692871, 64408.019531, 2350.899414);
        //     x = -7719.692871;
        //     y = 64408.019531;
        //     z = 2350.899414;
        // }
        else if (strcmp(token, "aa") == 0){
            ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
            token = strtok(NULL, " ");
            int temp = atoi(token);
            int count = 1;
            for (ActorRef<IActor> _iactor : world->m_actors) {
                
                Actor* actor = ((Actor*)(_iactor.m_object));
                Vector3 pos = actor->GetPosition();
                printf("[actor] %s: %.2f %.2f %.2f\n", actor->GetDisplayName(), pos.x, pos.y, pos.z); 
                if (count == temp){
                    x = pos.x; y = pos.y; z = pos.z;
                }
                count++;
        }
        }
        else if (strcmp(token ,"tp") == 0){
            printf("%f, %f, %f\n", x, y, z);
        
            while (token != NULL) {
                switch(count){
                    case 1:
                        x = atof(token);
                        break;
                    case 2:
                        y = atof(token);
                        break;
                    case 3:
                        z = atof(token);
                        break;
                    default:
                        break;
                }
                token = strtok(NULL, " ");
                count++;
            }
        }
        const Vector3 new_v = Vector3(x,y,z);
        Actor::SetPosition(new_v);
    }
 
}

// bool ItemPickup::CanUse(class IPlayer* player){
//     return 1;
// }


void World::Tick(float f)
{ 
    ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
    IPlayer* iplayer = world->m_activePlayer.m_object;
    GameAPI* g = *(GameAPI **)(dlsym(RTLD_NEXT, "Game"));
    std::vector<ItemPickup*, std::allocator<ItemPickup*> > g_list =g->GetGoldenEggList();
    std::set<ActorRef<IActor> > s = world->m_actors;
    // for (auto it = s.begin(); it != s.end(); ++it){
    //     // std::cout  << typeid(*it).name()<< std:: endl;
    //     ActorRef<IActor> _actor = (ActorRef<IActor> )(it);
    //     Actor* actor = ((Actor*)(*_actor.m_object));
    // }
    
    Player* player = ((Player*)(iplayer));

    // printf("%d\n", ItemPickup::CanUse(iplayer));
    Actor* actor = ((Actor*)(iplayer));
    player->m_walkingSpeed = 99999;
    player->m_jumpSpeed = 900;
    player->m_jumpHoldTime = 99999;

    // Actor* Egg1 = ActorFactory<GoldenEggPickup<1> >::CreateActor();


}
// bool BallmerPeakEgg::CanUse(class IPlayer * player){
//     return 1;
// }
// bool ItemPickup::CanUse(class IPlayer* player){
//     return 1;
// }

// bool Actor::CanUse(class IPlayer* player){
//     return 1;
// }
// std::string Actor::GetDeathMessage(){
//     return "hello";
// }
bool Bear::CanBeArmed(){
    return 0;
}

bool BearChest::IsArmedStage(){
    return 0;
}

void Bear::AttackForChest(class IPlayer * p){
    int a = 1;
}

void Bear::OnPrepareAttack(class Actor *){
    int a = 1;
}

void Bear::OnEndAttack(){
    int a = 1;
}
void BearShootState::EnterState(class Actor *b){
    int a = 1;
}
void BearShootState::LeaveState(){
    int a = 1;
}

int32_t Bear::GetMaxHealth(){
    return -100;
}
void Bear::Init(){
    int a = 1;
}

void BearChest::AddBear(class Bear *){
    int a = 1;

}
