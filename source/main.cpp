#include <raylib.h>
#include <rlgl.h>
#include <rose.h>
#include <rose/event.h>
#include <rose/hash.h>
#include <roseio.h>
#include <imgui.h>
#include <components/components.h>
#include <components/padevents.h>
#include <components/roseoptions.h>
#include <components/workspace.h>

#define IMPL_SERIALIZER
#include <components/components_ser.h>
#include <serializer/imguiserializer.h>
#include <algorithm>

#include "world.h"
#include "world.serializer.h"

#include <rose/world.h>


inline Vector2 vec(float x, float y) {
    return Vector2{x,y};
}

inline Vector3 vec(float x, float y, float z) {
    return Vector3{x,y,z};
}

inline Vector3 position(const Matrix & m) {
    Vector3 v = Vector3 { m.m12, m.m13, m.m14 };
    return v;
}

inline void position(Matrix & m, Vector3 v) {
    m.m12 = v.x;
    m.m13 = v.y;
    m.m14 = v.z;
}

Camera3D camera = { 0 };
ROSE_EXPORT void postload() {
    World & world = rose::world::get<World>();

    camera.up = { 0.0f, 0.0f, 1.0f };          // Camera up vector (rotation towards target)
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    SetCameraMode(camera, CAMERA_ORBITAL); // Set a free camera mode
    Image image = GenImageGradientRadial(64, 64, .22f, WHITE, {200,200,200,255});
    
    rose::io::json::read(world, rose::io::Folder::Working, "game_state.json");
}

ROSE_EXPORT void predestroy() {
    World & world = rose::world::get<World>();
    rose::io::json::write(world, rose::io::Folder::Working, "game_state.json");
}

ROSE_EXPORT void update() {
    World & world = rose::world::get<World>();
}

// Draw a model with extended parameters
void DrawModel(Model model, Matrix transform, Color tint)
{
    model.transform = MatrixMultiply(model.transform, transform);
    DrawModel(model, {0,0,0}, 1, tint);
}

ROSE_EXPORT void draw() {    
    World & world = rose::world::get<World>();
 
    ImguiSerializer serializer;
    rose::serialize(world, serializer);

    {
        ClearBackground(SKYBLUE);

        auto pos = position(world.bikes[0].transform);

        pos.x += rose::input::stick().x;
        pos.y += rose::input::stick().y;

        camera.position = pos + Vector3 { 0.0f, -12.0f, 6.0f };
        camera.target   = pos;

        position(world.bikes[0].transform, pos);

        BeginMode3D(camera);
        {
            for(int x = -20; x != 20; ++x) {
                for(int y = -20; y != 20; ++y) {
                    int w = x+y+1000;
                    DrawCubeV(vec(x,y,-1), vec(1,1,1), (w % 2) == 0 ? BLACK : WHITE);
                }
            }
            //DrawCubeV(position(world.bikes[0].transform), vec(1,1,1), RED);
            DrawModel(world.bikes[0].bike,  world.bikes[0].transform, WHITE);
        }
        EndMode3D();
    }
}

ROSE_EXPORT void ui() {
    World & world = rose::world::get<World>();
}

ROSE_EXPORT void event(const rose::Event & ev) {
    if(auto pad = ev.get<PadEvent>()) {
        World & world = rose::world::get<World>();
    }
}

#include <rose/engine.hpp>