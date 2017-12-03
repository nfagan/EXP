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
#include <iostream>
#include <thread>
#include <memory>

namespace EXP {
namespace test_case {
    
namespace PATHS {
    std::string EXAMPLES;
    const std::string TEX("/res/tex1.png");
}
    
namespace IDS {
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
    
namespace TAGS {
    const std::string RECT3("rect3");
}

std::shared_ptr<Task> task;
Time::Keeper *time = new Time::Keeper();
auto gl_manager = std::make_shared<GLContextManager>();
GLPipeline pipeline(gl_manager);

std::shared_ptr<InputKeyboard> keyboard;
std::shared_ptr<InputXY> mouse;

glm::vec2 rect_pos = Positions2D::CENTER;
    
//
//  sql stuff
//

namespace ft {
    typedef sql::field<std::string> fieldstr;
    typedef sql::field<int> fieldi;
    typedef sql::field<float> fieldf;
    typedef sql::row<fieldstr, fieldf> DATA;
    
    constexpr int choice_type = 0;
    constexpr int choice_time = 1;
}
    
struct choice_times {
    typedef sql::field<std::string> fieldstr;
    typedef sql::field<int> fieldi;
    typedef sql::field<float> fieldf;
    typedef sql::row<fieldstr, fieldf> DATA;
    
    static constexpr int choice_type = 0;
    static constexpr int choice_time = 1;
    
    auto get_data_row()
    {
        using namespace ft;
        fieldstr f1("choice_type");
        fieldf f2("choice_time");
        return std::make_shared<DATA>(f1, f2);
    }
};
    
const char *test_file = "test1.db";

sql::connection conn(test_file);
    
auto get_data_row()
{
    using namespace ft;
    fieldstr f1("choice_type");
    fieldf f2("choice_time");
    return std::make_shared<DATA>(f1, f2);
}
//
//  task stuff
//

void render_loop(RenderLoop *looper)
{
    pipeline.Update();
    mouse->UpdateCoordinates();
    
    float step_amount = 0.005f;
    if (keyboard->KeyDown(GLFW_KEY_A)) rect_pos.x -= step_amount;
    if (keyboard->KeyDown(GLFW_KEY_S)) rect_pos.y += step_amount;
    if (keyboard->KeyDown(GLFW_KEY_D)) rect_pos.x += step_amount;
    if (keyboard->KeyDown(GLFW_KEY_W)) rect_pos.y -= step_amount;
    if (keyboard->KeyDown(GLFW_KEY_C))
    {
        rect_pos.x = 0.5f;
        rect_pos.y = 0.5f;
    }
    
    auto rsrc = pipeline.GetResource();
    
    auto rectangle = rsrc->Get<Model>(IDS::MAIN_RECT);
    auto circle = rsrc->Get<Model>(IDS::CIRCLE1);
    
    rectangle->SetPosition(rect_pos);
    circle->SetPosition(rect_pos);
}

void task_thread_loop()
{
    task = std::make_shared<Task>(time);
    State *state1 = task->CreateState(&IDS::STATE1);
    State *state2 = task->CreateState(&IDS::STATE2);
    State *state3 = task->CreateState(&IDS::STATE3);
    
    auto curs = conn.get_cursor();
    auto row = get_data_row();
//    curs->create(row, "table1");
    
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
        pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            looper->ClearQueue();
            auto rsrc = pipeline.GetResource();
            auto elements = rsrc->GetByTag<Model>(TAGS::RECT3);
            auto rect = rsrc->Get<Model>(IDS::MAIN_RECT);
            auto rect2 = rsrc->Get<Model>(IDS::MAIN_RECT2);
            auto circle = rsrc->Get<Model>(IDS::CIRCLE1);
            auto mat = rsrc->Get<Material>(IDS::MAT1);
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
        auto rsrc = pipeline.GetResource();
        auto render_target = pipeline.GetTarget();
        auto rectangle = rsrc->Get<Model>(IDS::MAIN_RECT);
        auto rect2 = rsrc->Get<Model>(IDS::MAIN_RECT2);
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
            state->Next(state->GetStateById(IDS::STATE1));
    });
    
    state1->SetTimeIn(Time::duration_ms(duration1));
    state1->ExitOnTimeExceeded();
    
    //  target set - state 1
    
    TargetSet &target_set = state1->GetTargetSet();
    auto target1 = target_set.Create(mouse, Time::duration_ms(500));
    auto target2 = target_set.Create(mouse, Time::duration_ms(500));
    
    target1->SetSize(50.0f);
    target2->SetSize(50.0f);
    
    //
    //  example custom bounding function
    //
    
    target1->OnBoundsCheck([] (auto target) -> bool {
        auto rsrc = pipeline.GetResource();
        auto rectangle = rsrc->Get<Model>(IDS::MAIN_RECT);
        auto render_target = pipeline.GetTarget();
        auto bounds = util::geometry::get_bounding_rect_pixels(render_target, rectangle);
        auto coordinates = mouse->GetCoordinates();
        float x = coordinates.x;
        float y = coordinates.y;
        return x >= bounds[0] && x <= bounds[2] && y >= bounds[1] && y <= bounds[3];
    });
    
    target_set.OnEllapsed([] (auto state, auto target) {
        pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            auto rsrc = pipeline.GetResource();
            auto mat = rsrc->Get<Material>(IDS::MAT1);
            std::string texture_path = PATHS::EXAMPLES + PATHS::TEX;
            auto tex = rsrc->GetTexture<Texture>(texture_path.c_str());
            mat->SetAlbedo(tex);
        });
    });
    
    target_set.OnTargetEntry([&trial_number, &row] (auto state, auto target) {
        unsigned id = target->GetId();
        row->reset();
        auto &choice_type = row->get<ft::choice_type>();
        auto &choice_time = row->get<ft::choice_time>();
        double choice_time_s = task->EllapsedTime().count();
        choice_time.commit(choice_time_s);
        if (id == 0)
        {
            choice_type.commit("right");
        }
        else
        {
            choice_type.commit("left");
        }
        auto curs = conn.get_cursor();
//        if (!curs->insert(row, trial_number, "table1"))
        if (false)
        {
            std::cout << "\n\nFailed to store data. Aborting ... \n\n" << std::endl;
            task->ExitNow();
            return;
        }
        
        pipeline.GetRenderLoop()->OnceDrawReady([id] (auto looper) {
            auto rsrc = pipeline.GetResource();
            auto rect = rsrc->Get<Model>(IDS::MAIN_RECT);
            auto mat = rsrc->Get<Material>(IDS::MAT1);
            auto tex = rsrc->Get<Material>(IDS::TEX1);
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
        pipeline.GetRenderLoop()->OnceDrawReady([id] (auto looper) {
            auto rsrc = pipeline.GetResource();
            auto rect = rsrc->Get<Model>(IDS::MAIN_RECT);
            auto mat = rsrc->Get<Material>(IDS::MAT1);
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
        pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            looper->ClearQueue();
            auto rsrc = pipeline.GetResource();
            auto elements = rsrc->GetByTag<Model>(TAGS::RECT3);
            auto mat = rsrc->Get<Material>(IDS::MAT1);
            auto rect = rsrc->Get<Model>(IDS::MAIN_RECT);
            mat->SetAlbedo(Colors::WHITE);
            rect->SetMaterial(mat);
            elements.push_back(rect);
            looper->Queue(elements);
        });
    });
    
    state2->OnExit([] (auto state) {
        state->Next(state->GetStateById(IDS::STATE3));
    });
    
    state2->ExitOnTimeExceeded();
    
    //
    //  state 3
    //
    
    int duration3 = 1000;
    state3->SetTimeIn(Time::duration_ms(duration3));
    state3->OnEntry([] (auto state) {
        std::cout << "Entering state 3!" << std::endl;
        pipeline.GetRenderLoop()->OnceDrawReady([] (auto looper) {
            looper->ClearQueue();
            auto rsrc = pipeline.GetResource();
            auto elements = rsrc->GetByTag<Model>(TAGS::RECT3);
            auto mat = rsrc->Get<Material>(IDS::MAT_ANON);
            auto rect = rsrc->Get<Model>(IDS::MAIN_RECT);
            mat->SetAlbedo(Colors::GREEN);
            rect->SetMaterial(mat);
            elements.push_back(rect);
            looper->Queue(elements);
        });
    });
    
    state3->OnExit([] (auto state) {
        state->Next(state->GetStateById(IDS::STATE1));
    });
    
    state3->ExitOnTimeExceeded();
    
    //
    //  task
    //
    
    task->SetName("Task 1");
    
    task->OnExit([] (auto task) {
        pipeline.GetRenderLoop()->CancelLoop();
    });
    
    task->ExitOnKeyPress(keyboard, GLFW_KEY_ESCAPE);
    task->Next(state1);
    task->GetTimer()->Reset();
    task->Run();
    task->LogTime();
}

bool gl_init()
{
    pipeline.Begin(0, 400, 400);
    
    if (!pipeline.IsInitialized())
    {
        return false;
    }
    
    auto rsrc = pipeline.GetResource();
    auto render_target = pipeline.GetTarget();
    auto renderer = pipeline.GetRenderer();
    
    auto mat_anon = rsrc->Create<Material>();
    auto mat = rsrc->Create<Material>();
    auto mat_tex = rsrc->Create<Material>();
    mat->SetAlbedo(Colors::RED);
    
    //  rectangle
    auto rectangle = rsrc->CreateRectangle();
    auto rectangle2 = rsrc->CreateTriangle();
    auto circle = rsrc->CreateSphere();
    
    //  globals
    auto shader = rsrc->CreateGenericShader();
    keyboard = std::make_shared<InputKeyboard>(pipeline.GetTarget());
    mouse = std::make_shared<InputXY>(pipeline.GetTarget());
    
    rectangle->SetShader(shader);
    rectangle->SetUnits(util::units::MIXED);
    rectangle->SetScale(50.0f);
    rectangle->SetMaterial(mat);
    rectangle->SetPosition(rect_pos);
    
    rectangle2->MakeLike(rectangle);
    rectangle2->SetPosition(Positions2D::RIGHT_CENTER);
    rectangle2->SetMaterial(mat_tex);
    rectangle2->SetRotation(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));
    
    circle->SetShader(shader);
    circle->SetPosition(Positions2D::CENTER);
    circle->SetUnits(util::units::MIXED);
    circle->SetScale(50.0f);
    circle->GetMaterial()->SetAlbedo(Colors::WHITE);
    
    IDS::MAIN_RECT2 = rectangle2->GetUUID();
    IDS::MAT1 = mat->GetUUID();
    IDS::MAT_ANON = mat_anon->GetUUID();
    IDS::MAIN_RECT = rectangle->GetUUID();
    IDS::TEX1 = mat_tex->GetUUID();
    IDS::CIRCLE1 = circle->GetUUID();
    
    for (unsigned i = 0; i < 500; ++i)
    {
        auto new_rect = rsrc->CreateRectangle();
        new_rect->MakeLike(rectangle);
        new_rect->SetScale(glm::vec2(10.0f, 10.0f));
        float x = (float) rand()/RAND_MAX;
        float y = (float) rand()/RAND_MAX;
        new_rect->SetPosition(glm::vec2(x, y));
        new_rect->SetTag(TAGS::RECT3);
    }
    
    return true;
}
    
void set_examples_directory()
{
#ifdef __APPLE__
    char *abs_path = realpath("../", nullptr);
    PATHS::EXAMPLES = std::string(abs_path);
    free(abs_path);
#else
    char full[_MAX_PATH];
    if (_fullpath(full, "../", _MAX_PATH) != NULL)
    {
        PATHS::EXAMPLES = std::string(full);
    }
    else
    {
        std::cout << "Invalid path" << std::endl;
    }
#endif
}


int test_states(const char *relative_exe_path)
{
    set_examples_directory();
    
    std::cout << PATHS::EXAMPLES << std::endl;
    
    time->Start();
    
    bool success = gl_init();
    
    if (!success)
    {
        std::cout << "Failed to initialize the render pipeline." << std::endl;
        return 1;
    }
    
    std::thread t1(task_thread_loop);
    while (!task || !task->IsRunning())
    {
        //
    }
    
    auto looper = pipeline.GetRenderLoop();
    looper->OnLoop(render_loop);
    looper->Loop();
    t1.join();
    return 0;
}
        
}
}

#endif /* test_threaded_states_h */


