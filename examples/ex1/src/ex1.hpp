//
//  ex1.hpp
//  EXP
//
//  Created by Nick Fagan on 11/1/17.
//  Copyright © 2017 Nick Fagan. All rights reserved.
//

#ifndef ex1_h
#define ex1_h

#include <EXPTask.hpp>
#include <EXPGL.hpp>
#include <EXPSQL/EXPSQL.hpp>
#include <EXPUtil/file/get_full_path.hpp>
#include <iostream>
#include <thread>
#include <memory>
#include <string>
#include <vector>

namespace EX1 {
    
using namespace EXP;
using std::string;
    
namespace paths {
    string examples = file::get_full_path("../");
    const string tex1("/res/textures/tex1.png");
}
    
namespace ids {
    unsigned MAIN_RECT;
    unsigned MAIN_RECT2;
    unsigned CIRCLE1;
    unsigned RECT1;
    unsigned RECT2;
    unsigned MAT1;
    unsigned MAT_ANON;
    unsigned TEX1;
    
    unsigned STATE1;
    unsigned STATE2;
    unsigned STATE3;
}
    
namespace tags {
    const string RECT3("rect3");
}
    
namespace globals {
    Time::Keeper *time = new Time::Keeper();
    
    auto gl_manager = std::make_shared<GLContextManager>();
    GLPipeline pipeline(globals::gl_manager);
    
    std::shared_ptr<Task> task;
    
    std::shared_ptr<InputKeyboard> keyboard;
    std::shared_ptr<InputXY> mouse;
}
    
//
//  sql stuff
//

namespace db {
    const char *test_file = "test1.db";
    sql::connection conn(test_file);
    
    //  build the trial data table
    EXPSQL_MAKE_FIELD(choice_type, string);
    EXPSQL_MAKE_FIELD(choice_time, double);
    EXPSQL_MAKE_TABLE(DATA, choice_type, choice_time);
    
    //  build the task errors table
    EXPSQL_MAKE_FIELD(error_no_look, int);
    EXPSQL_MAKE_FIELD(error_no_fixation, int);
    EXPSQL_MAKE_TABLE(ERRORS, error_no_look, error_no_fixation);
    
    auto error_table = std::make_shared<ERRORS>(conn.get_cursor());
    auto data_table = std::make_shared<DATA>(conn.get_cursor());
}
    
//
//  task stuff
//

void render_loop(RenderLoop *looper)
{
    static glm::vec2 rect_pos = Positions2D::CENTER;
    
    globals::pipeline.Update();
    globals::mouse->UpdateCoordinates();
    
    float step_amount = 0.005f;
    if (globals::keyboard->KeyDown(Keys::A)) rect_pos.x -= step_amount;
    if (globals::keyboard->KeyDown(Keys::S)) rect_pos.y += step_amount;
    if (globals::keyboard->KeyDown(Keys::D)) rect_pos.x += step_amount;
    if (globals::keyboard->KeyDown(Keys::W)) rect_pos.y -= step_amount;
    if (globals::keyboard->KeyDown(Keys::C))
    {
        rect_pos.x = 0.5f;
        rect_pos.y = 0.5f;
    }
    
    auto rsrc = globals::pipeline.GetResource();
    
    auto rectangle = rsrc->Get<Model>(ids::MAIN_RECT);
    auto circle = rsrc->Get<Model>(ids::CIRCLE1);
    
    rectangle->SetPosition(rect_pos);
    circle->SetPosition(rect_pos);
}

void task_thread_loop()
{    
    globals::task = std::make_shared<Task>(globals::time);
    
    auto *state1 = globals::task->CreateState(&ids::STATE1);
    auto *state2 = globals::task->CreateState(&ids::STATE2);
    auto *state3 = globals::task->CreateState(&ids::STATE3);
    
    db::data_table->drop();
    db::data_table->create();
    
    //
    //  state 1
    //
    
    int trial_number = 0;
    
    int duration1 = 3000;
    
    state1->SetName("state 1");
    
    state1->OnEntry([&trial_number] (auto state) {
        std::cout << "Entering state 1!" << std::endl;
        trial_number++;
        state->LogTime();
        globals::pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            looper->ClearQueue();
            auto rsrc = globals::pipeline.GetResource();
            auto elements = rsrc->GetByTag<Model>(tags::RECT3);
            auto rect = rsrc->Get<Model>(ids::MAIN_RECT);
            auto rect2 = rsrc->Get<Model>(ids::MAIN_RECT2);
            auto circle = rsrc->Get<Model>(ids::CIRCLE1);
            auto mat = rsrc->Get<Material>(ids::MAT1);
            for (unsigned i = 0; i < elements.size(); ++i)
            {
                elements[i]->SetMaterial(mat);
            }
            elements.push_back(rect);
            elements.push_back(rect2);
            elements.push_back(circle);
            looper->Queue(elements);
        });
    });
    
    state1->OnLoop([] (auto state) {
        auto rsrc = globals::pipeline.GetResource();
        auto render_target = globals::pipeline.GetTarget();
        auto rectangle = rsrc->Get<Model>(ids::MAIN_RECT);
        auto rect2 = rsrc->Get<Model>(ids::MAIN_RECT2);
        auto screen = render_target->GetFullRect();
        auto position = rectangle->get_units_position(screen);
        auto position_triangle = rect2->get_units_position(screen);
        auto target1 = state->GetTargetSet().GetTargetById(0);
        auto target2 = state->GetTargetSet().GetTargetById(1);
        target1->SetPosition(position);
        target2->SetPosition(position_triangle);
    });
    
    state1->OnExit([] (auto state) {
        if (!state->GetNext())
            state->Next(state->GetStateById(ids::STATE1));
    });
    
    state1->SetTimeIn(Time::duration_ms(duration1));
    state1->ExitOnTimeExceeded();
    
    //  target set - state 1
    
    TargetSet &target_set = state1->GetTargetSet();
    auto target1 = target_set.Create(globals::mouse, Time::duration_ms(500));
    auto target2 = target_set.Create(globals::mouse, Time::duration_ms(500));
    
    target1->SetSize(50.0f);
    target2->SetSize(50.0f);
    
    //
    //  example custom bounding function
    //
    
    target1->OnBoundsCheck([] (auto target) -> bool {
        auto rsrc = globals::pipeline.GetResource();
        auto rectangle = rsrc->Get<Model>(ids::MAIN_RECT);
        auto render_target = globals::pipeline.GetTarget();
        auto bounds = util::geometry::get_bounding_rect_pixels(render_target, rectangle);
        auto coordinates = globals::mouse->GetCoordinates();
        float x = coordinates.x;
        float y = coordinates.y;
        return x >= bounds[0] && x <= bounds[2] && y >= bounds[1] && y <= bounds[3];
    });
    
    target_set.OnEllapsed([&] (auto state, auto target) {
        unsigned id = target->GetId();
        double choice_time_s = globals::task->EllapsedTime().count();
        db::data_table->commit<db::choice_time>(choice_time_s);
        if (id == 0)
        {
            std::cout << "Chose left!" << std::endl;
            if (!db::data_table->commit<db::choice_type>("left"))
                std::cout << "Failed to commit data." << std::endl;
        }
        else
        {
            std::cout << "Chose right!" << std::endl;
            if (!db::data_table->commit<db::choice_type>("right"))
                std::cout << "Failed to commit data." << std::endl;
        }
        if (!db::data_table->insert())
        {
            std::cout << "\n\nFailed to store data. Aborting ... \n\n" << std::endl;
            return;
        }
        
        globals::pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            auto rsrc = globals::pipeline.GetResource();
            auto mat = rsrc->Get<Material>(ids::MAT1);
            string texture_path = paths::examples + paths::tex1;
            auto tex = rsrc->GetTexture(texture_path);
            mat->SetAlbedo(tex);
        });
    });
    
    target_set.OnTargetEntry([&] (auto state, auto target) {
        unsigned id = target->GetId();
        globals::pipeline.GetRenderLoop()->OnceDrawReady([id] (auto looper) {
            auto rsrc = globals::pipeline.GetResource();
            auto rect = rsrc->Get<Model>(ids::MAIN_RECT);
            auto mat = rsrc->Get<Material>(ids::MAT1);
            auto tex = rsrc->Get<Material>(ids::TEX1);
            if (id == 0)
            {
                mat->SetAlbedo(Colors::GREY_50);
                rect->SetMaterial(tex);
            }
            else
            {
                mat->SetAlbedo(Colors::MAGENTA);
            }
        });
    });
    
    target_set.OnTargetExit([] (auto *state, auto target) {
        unsigned id = target->GetId();
        globals::pipeline.GetRenderLoop()->OnceDrawReady([id] (auto looper) {
            auto rsrc = globals::pipeline.GetResource();
            auto rect = rsrc->Get<Model>(ids::MAIN_RECT);
            auto mat = rsrc->Get<Material>(ids::MAT1);
            mat->SetAlbedo(Colors::RED);
            rect->SetMaterial(mat);
        });
    });
    
    //
    //  state 2
    //
    
    int duration2 = 650;
    state2->SetTimeIn(Time::duration_ms(duration2));
    state2->OnEntry([] (auto state) {
        std::cout << "Entering state 2!" << std::endl;
        globals::pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            looper->ClearQueue();
            auto rsrc = globals::pipeline.GetResource();
            auto elements = rsrc->GetByTag<Model>(tags::RECT3);
            auto mat = rsrc->Get<Material>(ids::MAT1);
            auto rect = rsrc->Get<Model>(ids::MAIN_RECT);
            mat->SetAlbedo(Colors::WHITE);
            rect->SetMaterial(mat);
            elements.push_back(rect);
            looper->Queue(elements);
        });
    });
    
    state2->OnExit([] (auto state) {
        state->Next(state->GetStateById(ids::STATE3));
    });
    
    state2->ExitOnTimeExceeded();
    
    //
    //  state 3
    //
    
    int duration3 = 1000;
    state3->SetTimeIn(Time::duration_ms(duration3));
    state3->OnEntry([] (auto state) {
        std::cout << "Entering state 3!" << std::endl;
        globals::pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            looper->ClearQueue();
            auto rsrc = globals::pipeline.GetResource();
            auto elements = rsrc->GetByTag<Model>(tags::RECT3);
            auto mat = rsrc->Get<Material>(ids::MAT_ANON);
            auto rect = rsrc->Get<Model>(ids::MAIN_RECT);
            mat->SetAlbedo(Colors::GREEN);
            rect->SetMaterial(mat);
            elements.push_back(rect);
            looper->Queue(elements);
        });
    });
    
    state3->OnExit([] (auto state) {
        state->Next(state->GetStateById(ids::STATE1));
    });
    
    state3->ExitOnTimeExceeded();
    
    //
    //  task
    //
    
    globals::task->SetName("Task 1");
    
    //  When the task is finished, exit out of the render loop.
    globals::task->OnExit([] (auto task) {
        globals::pipeline.GetRenderLoop()->CancelLoop();
    });
    
    globals::task->ExitOnKeyPress(globals::keyboard, Keys::ESC);
    globals::task->Next(state1);
    globals::task->GetTimer()->Reset();
    globals::task->Run();
    std::cout << globals::task->ExitReason() << std::endl;
    globals::task->LogTime();
}

bool gl_init()
{
    using namespace globals;
    
    pipeline.Begin(0, 400, 400);
    
    if (!pipeline.IsInitialized())
    {
        return false;
    }
    
    auto rsrc = pipeline.GetResource();
    auto render_target = pipeline.GetTarget();
    auto renderer = pipeline.GetRenderer();
    
    //  main materials
    auto shader = rsrc->CreateGenericShader();
    auto mat_anon = rsrc->Create<Material>();
    auto mat = rsrc->Create<Material>();
    auto mat_tex = rsrc->Create<Material>();
    mat->SetAlbedo(Colors::RED);
    
    //  main shapes
    auto rectangle = rsrc->CreateRectangle();
    auto triangle = rsrc->CreateTriangle();
    auto circle = rsrc->CreateSphere();
    
    //  input
    globals::keyboard = std::make_shared<InputKeyboard>(pipeline.GetTarget());
    globals::mouse = std::make_shared<InputXY>(pipeline.GetTarget());
    
    // configure each stimulus
    rectangle->SetShader(shader);
    rectangle->SetUnits(util::units::MIXED);
    rectangle->SetScale(50.0f);
    rectangle->SetMaterial(mat);
    rectangle->SetPosition(Positions2D::CENTER);
    
    triangle->MakeLike(rectangle);
    triangle->SetPosition(Positions2D::RIGHT_CENTER);
    triangle->SetMaterial(mat_tex);
    triangle->SetRotation(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));
    
    auto circle_mat = circle->GetMaterial();
    circle_mat->SetAlbedo(Colors::GREEN);
    circle->MakeLike(rectangle);
    circle->SetMaterial(circle_mat);
    
    ids::MAIN_RECT2 = triangle->GetUUID();
    ids::MAT1 = mat->GetUUID();
    ids::MAT_ANON = mat_anon->GetUUID();
    ids::MAIN_RECT = rectangle->GetUUID();
    ids::TEX1 = mat_tex->GetUUID();
    ids::CIRCLE1 = circle->GetUUID();
    
    // create a bunch of rectangles
    for (unsigned i = 0; i < 500; ++i)
    {
        auto new_rect = rsrc->CreateRectangle();
        new_rect->MakeLike(rectangle);
        new_rect->SetScale(glm::vec2(10.0f, 10.0f));
        float x = (float) rand()/RAND_MAX;
        float y = (float) rand()/RAND_MAX;
        new_rect->SetPosition(glm::vec2(x, y));
        new_rect->SetTag(tags::RECT3);
    }
    
    return true;
}

int start()
{
    //  Start the OpenGL context, create stimuli. Exit if initialization failed.
    if (!gl_init())
    {
        std::cout << "Failed to initialize the render pipeline." << std::endl;
        return EXIT_FAILURE;
    }
    
    //  Start the time thread
    globals::time->Start();
    
    //  Start the task thread, and wait until setup is finished.
    std::thread t1(task_thread_loop);
    while (!globals::task || !globals::task->IsRunning());
    
    //  Start the render loop. The loop proceeds until it
    //  is canceled by the task thread (e.g., by pressing the esc key)
    auto looper = globals::pipeline.GetRenderLoop();
    looper->OnLoop(render_loop);
    looper->Loop();
    
    //  Wait for the task thread to finish
    t1.join();
    
    return EXIT_SUCCESS;
}
        
}

#endif /* test_threaded_states_h */


