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
    rose::ecs::serialize(world, serializer);

    {
        ClearBackground(SKYBLUE);


        world.bikes[0].transform.m12 -= rose::input::stick().x;
        world.bikes[0].transform.m13 -= rose::input::stick().y;

        Vector3 position = Vector3 { world.bikes[0].transform.m12,  world.bikes[0].transform.m13,  world.bikes[0].transform.m14 };
        camera.position =  position + Vector3 { 0.0f, 5.0f, 5.0f };
        camera.target =  position;

        BeginMode3D(camera);
        {
            DrawModel(world.bikes[0].bike,  world.bikes[0].transform, WHITE);
            DrawGrid(10, 1.0f);
        }
        EndMode3D();
    }
}

ROSE_EXPORT void event(const rose::Event & ev) {
    if(auto pad = ev.get<PadEvent>()) {
        World & world = rose::world::get<World>();
    }
}

#include <rose/engine.hpp>