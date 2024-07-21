
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
        else if (strcmp(token ,"tp") == 0){
            printf("[here]");
        
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
void World::Tick(float f)
{
    ClientWorld* world = *((ClientWorld**)(dlsym(RTLD_NEXT, "GameWorld")));
    IPlayer* iplayer = world->m_activePlayer.m_object;
    Player* player = ((Player*)(iplayer));
    Actor* actor = ((Actor*)(iplayer));
    player->m_walkingSpeed = 99999;
    player->m_jumpSpeed = 200;
    player->m_jumpHoldTime = 99999;

}
